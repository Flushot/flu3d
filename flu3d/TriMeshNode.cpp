#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "TriMeshNode.h"
#include "Log/Log.h"
#include "GLHelper.h"
#include "Exceptions.h"
#include <fstream>
using namespace std;

/* 
MS3D STRUCTURES 
*/

// byte-align structures
#ifdef _MSC_VER
#	pragma pack( push, packing )
#	pragma pack( 1 )
#	define PACK_STRUCT
#elif defined( __GNUC__ )
#	define PACK_STRUCT	__attribute__((packed))
#else
#	error you must byte-align these structures with the appropriate compiler directives
#endif

typedef unsigned char byte;
typedef unsigned short word;

// File header
struct MS3DHeader {
	char m_ID[10];
	int m_version;
} PACK_STRUCT;

// Vertex information
struct MS3DVertex {
	byte m_flags;
	float m_vertex[3];
	char m_boneID;
	byte m_refCount;
} PACK_STRUCT;

// Triangle information
struct MS3DTriangle {
	word m_flags;
	word m_vertexIndices[3];
	float m_vertexNormals[3][3];
	float m_s[3], m_t[3];
	byte m_smoothingGroup;
	byte m_groupIndex;
} PACK_STRUCT;

// Material information
struct MS3DMaterial {
	char m_name[32];
	float m_ambient[4];
	float m_diffuse[4];
	float m_specular[4];
	float m_emissive[4];
	float m_shininess;	// 0.0f - 128.0f
	float m_transparency;	// 0.0f - 1.0f
	byte m_mode;	// 0, 1, 2 is unused now
	char m_texture[128];
	char m_alphamap[128];
} PACK_STRUCT;

//	Joint information
struct MS3DJoint {
	byte m_flags;
	char m_name[32];
	char m_parentName[32];
	float m_rotation[3];
	float m_translation[3];
	word m_numRotationKeyframes;
	word m_numTranslationKeyframes;
} PACK_STRUCT;

// Keyframe data
struct MS3DKeyframe {
	float m_time;
	float m_parameter[3];
} PACK_STRUCT;

// Default alignment
#ifdef _MSC_VER
#	pragma pack( pop, packing )
#endif

#undef PACK_STRUCT

TriMeshNode::~TriMeshNode() {
	for (vector<Mesh *>::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
		delete (*it);
}

void TriMeshNode::applyFixed(const Material &material, const char *textureFile) {
	for (std::vector<Mesh *>::iterator meshIt = _meshes.begin(); meshIt != _meshes.end(); ++meshIt) {
		Mesh *mesh = (*meshIt);
		mesh->material = material;
		mesh->material.textureFile = (string)textureFile;
	}
	reloadTextures();
}

void TriMeshNode::loadFile(const char *fileName, bool useFixed) {
	ifstream inputFile(fileName, ios::in | ios::binary);
	if ( inputFile.fail() )
		throw new SceneFileException("Can't open model file");

	inputFile.seekg(0, ios::end);
	long fileSize = inputFile.tellg();
	inputFile.seekg(0, ios::beg);

	byte *pBuffer = new byte[fileSize];
	inputFile.read((char *)pBuffer, fileSize);
	inputFile.close();

	const byte *pPtr = pBuffer;
	MS3DHeader *pHeader = (MS3DHeader *)pPtr;
	pPtr += sizeof(MS3DHeader);

	if ( strncmp(pHeader->m_ID, "MS3D000000", 10) != 0 )
		throw new SceneFileException("No a valid Milkshape 3D model file");

	if ( pHeader->m_version < 3 || pHeader->m_version > 4 )
		throw new SceneFileException("Unsupported file version. Only versions 1.3 and 1.4 are supported.");

	int nVertices = *(word *)pPtr; 
	Vector *pVectors = new Vector[nVertices];
	pPtr += sizeof(word);

	int i;
	for (i = 0; i < nVertices; ++i) {
		MS3DVertex *pVertex = (MS3DVertex *)pPtr;
		pVectors[i].x = pVertex->m_vertex[0];
		pVectors[i].y = pVertex->m_vertex[1];
		pVectors[i].z = pVertex->m_vertex[2];
		pVectors[i].boneId = pVertex->m_boneID;
		pPtr += sizeof(MS3DVertex);
	}

	int nTriangles = *(word *)pPtr;
	Triangle *pTriangles = new Triangle[nTriangles];
	pPtr += sizeof(word);

	for (i = 0; i < nTriangles; ++i) {
		MS3DTriangle *pTriangle = (MS3DTriangle *)pPtr;
		// vertices
		pTriangles[i].a = pVectors[pTriangle->m_vertexIndices[0]];
		pTriangles[i].b = pVectors[pTriangle->m_vertexIndices[1]];
		pTriangles[i].c = pVectors[pTriangle->m_vertexIndices[2]];
		// tex coords
		pTriangles[i].t = Vector(1.0f - pTriangle->m_t[0], 1.0f - pTriangle->m_t[1], 1.0f - pTriangle->m_t[2]);
		pTriangles[i].s = Vector(pTriangle->m_s[0], pTriangle->m_s[1], pTriangle->m_s[2]);
		// normals
		pTriangles[i].aN = Vector(pTriangle->m_vertexNormals[0][0], pTriangle->m_vertexNormals[0][1], pTriangle->m_vertexNormals[0][2]);
		pTriangles[i].bN = Vector(pTriangle->m_vertexNormals[1][0], pTriangle->m_vertexNormals[1][1], pTriangle->m_vertexNormals[1][2]);
		pTriangles[i].cN = Vector(pTriangle->m_vertexNormals[2][0], pTriangle->m_vertexNormals[2][1], pTriangle->m_vertexNormals[2][2]);
		pPtr += sizeof(MS3DTriangle);
	}

	int nGroups = *(word *)pPtr;
	int *meshMatMap = new int[nGroups];
	pPtr += sizeof(word);
	for (i = 0; i < nGroups; ++i) {
		pPtr += sizeof(byte); // flags
		pPtr += 32; // name

		Mesh *mesh = new Mesh();
		word nTriangles = *(word *)pPtr;
		pPtr += sizeof(word);
		for (int j = 0; j < nTriangles; ++j) {
			mesh->triangles.push_back(pTriangles[*(word *)pPtr]);
			pPtr += sizeof(word);
		}

		meshMatMap[i] = *(char *)pPtr;
		pPtr += sizeof(char);
		_meshes.push_back(mesh);
	}

	if (! useFixed) {
		int nMaterials = *(word *)pPtr;
		Material *pMaterials = new Material[nMaterials];
		pPtr += sizeof(word);
		for (i = 0; i < nMaterials; ++i) {
			MS3DMaterial *pMat = (MS3DMaterial *)pPtr;
			memcpy(&pMaterials[i].ambient, &pMat->m_ambient, sizeof(float) * 4);
			memcpy(&pMaterials[i].diffuse, &pMat->m_diffuse, sizeof(float) * 4);
			memcpy(&pMaterials[i].specular, &pMat->m_specular, sizeof(float) * 4);
			memcpy(&pMaterials[i].emissive, &pMat->m_emissive, sizeof(float) * 4);
			pMaterials[i].shininess = pMat->m_shininess;
			pMaterials[i].textureFile = (char *)&pMat->m_texture;
			Log::info(pMat->m_texture);
			pPtr += sizeof(MS3DMaterial);
		}

		// Map materials to meshes
		for (i = 0; i < nGroups; ++i)
			_meshes[i]->material = pMaterials[meshMatMap[i]];

		reloadTextures();
		delete [] pMaterials;
	}

	delete [] meshMatMap;
	delete [] pTriangles;
	delete [] pVectors;
	delete [] pBuffer;
}

void TriMeshNode::reloadTextures() {
	for (vector<Mesh *>::iterator it = _meshes.begin(); it != _meshes.end(); ++it) {
		Mesh *mesh = (*it);
		if (! mesh->material.textureFile.empty() ) {
			mesh->material.textureId = 
				loadGLTexture(mesh->material.textureFile.c_str());
		}
		else
			mesh->material.textureId = 0;
	}
}

void TriMeshNode::bake() {
	Log::debug("Baking TriMeshNode");
	for (std::vector<Mesh *>::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
		(*it)->bake();

	SceneNode::bake();
}

void TriMeshNode::render() {
	//Log::debug("Rendering TriMeshNode " + (string)getName());
	glPushMatrix();
	matrixTransform();
	
	GLboolean isTextureEnabled = glIsEnabled(GL_TEXTURE_2D);
	if (! isTextureEnabled)
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	for (std::vector<Mesh *>::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
		(*it)->render();

	if (isTextureEnabled)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);

	renderChildren();
}
