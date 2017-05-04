#define BG_MANAGER_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include <assert.h>
#include "baseTypes.h"
#include "openglframework.h"	
#include "backgroundManager.h"


#include "soil.h"

BackgroundManagerC* BackgroundManagerC::sInstance=NULL;


BackgroundManagerC *BackgroundManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new BackgroundManagerC();
	return sInstance;
}
void BackgroundManagerC::init(int width, int height)
{
	mWidth = width;
	mHeight = height;

/* load an image file directly as a new OpenGL texture */
	mSpriteTextureMap = SOIL_load_OGL_texture("content\\images\\bombermanMap2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

}
void BackgroundManagerC::shutdown()
{
	//
}
void BackgroundManagerC::renderSprites()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, mSpriteTextureMap);
	glBegin (GL_QUADS);

	glColor4ub(0xFF, 0xFF, 0xFF,0xFF);
	glTexCoord2f (0.0f, 0.0f);
	glVertex2f (0.0f, mHeight);
	glTexCoord2f (1.0f, 0.0f);
	glVertex2f (mWidth, mHeight);
	glTexCoord2f (1.0f, 1.0f);
	glVertex2f (mWidth, 0.0f);
	glTexCoord2f (0.0f, 1.0f);
	glVertex2f (0.0f, 0.0f);


	glEnd ();
	glDisable(GL_TEXTURE_2D);
}