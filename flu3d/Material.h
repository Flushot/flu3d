#pragma once

#include <string>

class Material {
public:
	/* Light that comes from all directions equally and is scattered in all directions equally
	   by the polygons in your scene. This isn't quite true of the real world - but it's a good
	   first approximation for light that comes pretty much uniformly from the sky and arrives
	   onto a surface by bouncing off so many other surfaces that it might as well be uniform. */
	float ambient[4];

	/* Light that comes from a particular point source (like the Sun) and hits surfaces with an 
	   intensity that depends on whether they face towards the light or away from it. However, 
	   once the light radiates from the surface, it does so equally in all directions. It is 
	   diffuse lighting that best defines the shape of 3D objects. */
	float diffuse[4];

	/* As with diffuse lighting, the light comes from a point souce, but with specular lighting, 
	   it is reflected more in the manner of a mirror where most of the light bounces off in a 
	   particular direction defined by the surface shape. Specular lighting is what produces the 
	   shiney highlights and helps us to distinguish between flat, dull surfaces such as plaster 
	   and shiney surfaces like polished plastics and metals. */
	float specular[4];

	/* In this case, the light is actually emitted by the polygon - equally in all directions. */
	float emissive[4];

	float shininess;

	// OpenGL texture id
	unsigned int textureId;

	std::string textureFile;

	Material() {
		memset(&ambient, 0, sizeof(float) * 4);
		memset(&diffuse, 0, sizeof(float) * 4);
		memset(&specular, 0, sizeof(float) * 4);
		memset(&emissive, 0, sizeof(float) * 4);
		shininess = 0.0f;
		textureId = 0;
	}
	Material(
			float ambientA, float ambientB, float ambientC, float ambientD,
			float diffuseA, float diffuseB, float diffuseC, float diffuseD,
			float specularA, float specularB, float specularC, float specularD,
			float emissiveA, float emissiveB, float emissiveC, float emissiveD,
			float shininess = 0.0f,
			int textureId = 0) {
		Material();
		setAmbient(ambientA, ambientB, ambientC, ambientD);
		setDiffuse(diffuseA, diffuseB, diffuseC, diffuseD);
		setSpecular(specularA, specularB, specularC, specularD);
		setEmissive(emissiveA, emissiveB, emissiveC, emissiveD);
		this->shininess = shininess;
		this->textureId = textureId;
	}

	void setAmbient(float a, float b, float c, float d) {
		ambient[0] = a;
		ambient[1] = b;
		ambient[2] = c;
		ambient[3] = d;
	}
	void setDiffuse(float a, float b, float c, float d) {
		diffuse[0] = a;
		diffuse[1] = b;
		diffuse[2] = c;
		diffuse[3] = d;
	}
	void setSpecular(float a, float b, float c, float d) {
		specular[0] = a;
		specular[1] = b;
		specular[2] = c;
		specular[3] = d;
	}
	void setEmissive(float a, float b, float c, float d) {
		emissive[0] = a;
		emissive[1] = b;
		emissive[2] = c;
		emissive[3] = d;
	}
};
