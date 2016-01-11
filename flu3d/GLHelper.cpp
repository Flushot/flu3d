#include "GLHelper.h"

#include <fstream>

AUX_RGBImageRec *loadBMP(const char *fileName) {
	if (! fileName)
		return NULL;

	FILE *fp = NULL;
	fopen_s(&fp, fileName, "r");
	if (fp) {
		fclose(fp);
		return auxDIBImageLoad(fileName);
	}

	return NULL;
}

GLuint loadGLTexture(const char *fileName) {
	GLuint texture = 0;

	AUX_RGBImageRec *pImage = loadBMP(fileName);
	if (pImage != NULL && pImage->data != NULL) {
		glGenTextures(1, &texture);
		
		glBindTexture(GL_TEXTURE_2D, texture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // added
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // added
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // added
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, /*GL_DECAL*/ GL_MODULATE); // added
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pImage->sizeX, pImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
		
		free(pImage->data);
		free(pImage);
	}
	
	return texture;
}
