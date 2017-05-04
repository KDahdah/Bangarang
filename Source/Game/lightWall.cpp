#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "object.h"
#include "SOIL.h"
#include "lightWall.h"
#include "CollisionManager.h"
#include "inputmanager.h"


LightWallC::LightWallC(float_t initPosX,float_t initPosY,int32_t id, GLuint textureIndex, float_t time)
{
	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mSpriteMap = textureIndex;
	mID = id;
	mTimer = new TimerC(time);
	mTimer->StartTimer();
}
LightWallC::~LightWallC()
{
	delete mTimer;
};

void LightWallC::render()
{
	int32_t posX = mPosition.x*32;
	int32_t posY = (mPosition.y+1)*32;
    glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, mSpriteMap);
	glBegin (GL_QUADS);

	float_t leftTextCoord = ((float_t)mID*WALL_WIDTH)/TEXTURE_WIDTH;
	float_t rightTextCoord = leftTextCoord+((float_t)WALL_WIDTH/TEXTURE_WIDTH);

	glColor4ub(0xFF, 0xFF, 0xFF,0xFF);
	glTexCoord2f (leftTextCoord, 0.0f);
	glVertex2f (posX,posY);
	glTexCoord2f (rightTextCoord, 0.0f);
	glVertex2f (posX+(WALL_WIDTH), posY);
	glTexCoord2f (rightTextCoord, 1.0f);
	glVertex2f (posX+(WALL_WIDTH), posY-WALL_HEIGHT);
	glTexCoord2f (leftTextCoord, 1.0f);
	glVertex2f (posX, posY-WALL_HEIGHT);

	glEnd ();
	glDisable(GL_TEXTURE_2D);
}

bool8_t LightWallC::isTimeUp()
{
	bool8_t timeUp = false;
	mTimer->RunTimer();
	if(mTimer->isFinished())
	{
		timeUp = true;
	}
	return timeUp;
}

char8_t LightWallC::getIdOfPlayer()
{
	return mID;
}

void shutdown()
{
}