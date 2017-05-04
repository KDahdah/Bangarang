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

#include "CollisionManager.h"
#include "inputmanager.h"
#include "LightWallManager.h"
#include "player.h"
#include "TronCycle.h"


TronCycleC::TronCycleC(float_t initPosX, float_t initPosY, int32_t id, float_t velocity, ORIENTATION orientation)
{
	mSpritePath = "content\\images\\tronCycle.png";
	cycleIndex = 0;
	mPosition.x = initPosX;
	mPosition.y = initPosY;
	lightWallSpawn.x = (int32_t)initPosX/32;
	lightWallSpawn.y = (int32_t)initPosY/32;
	mID = id;
	mSpriteMap = SOIL_load_OGL_texture(mSpritePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	setDirection(orientation);
	setVelocity(velocity);
}

void TronCycleC::setDirection(ORIENTATION orientation)
{
	mDirection = orientation;
}

void TronCycleC::setVelocity(float_t velocity)
{
	mVelocity = velocity;
}

void TronCycleC::move()
{
	switch(mDirection)
	{
		case UP:
			mPosition.y -= mVelocity;
			break;

		case DOWN:
			mPosition.y += mVelocity;
			break;

		case LEFT:
			mPosition.x -= mVelocity;
			break;

		case RIGHT:
			mPosition.x += mVelocity;
			break;
	}
	tryToSpawnLightWall();
}

void TronCycleC::destroy()
{

}

void TronCycleC::render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, mSpriteMap);
	glBegin (GL_QUADS);

    float_t leftTextCoord;
	float_t rightTextCoord;
	float_t upperTextCoord;
	float_t lowerTextCoord;
	glColor4ub(0xFF, 0xFF, 0xFF,0xFF);
	//check to see orientation
	switch(mDirection)
	{
	case UP: //0,1 0,0 1,0 1,1
		leftTextCoord  = 1;
		rightTextCoord = 1;
		upperTextCoord = 1;
		lowerTextCoord = 1;
		glTexCoord2f (0.0f, 1.0f);
		glVertex2f ((int32_t)mPosition.x,(int32_t)mPosition.y);
		glTexCoord2f (0.0f, 0.0f);
		glVertex2f ((int32_t)mPosition.x+(TRONCYCLE_SPRITE_WIDTH), (int32_t)mPosition.y);
		glTexCoord2f (1.0f, 0.0f);
		glVertex2f ((int32_t)mPosition.x+(TRONCYCLE_SPRITE_WIDTH), (int32_t)mPosition.y-TRONCYCLE_SPRITE_HEIGHT);
		glTexCoord2f (1.0f, 1.0f);
		glVertex2f ((int32_t)mPosition.x, (int32_t)mPosition.y-TRONCYCLE_SPRITE_HEIGHT);
		break;

	case DOWN:
		leftTextCoord  = 0;
		rightTextCoord = 1;
		upperTextCoord = 1;
		lowerTextCoord = 0;
		glTexCoord2f (0.0f, 0.0f);
		glVertex2f ((int32_t)mPosition.x,(int32_t)mPosition.y);
		glTexCoord2f (0.0f, 1.0f);
		glVertex2f ((int32_t)mPosition.x+(TRONCYCLE_SPRITE_WIDTH), (int32_t)mPosition.y);
		glTexCoord2f (1.0f, 1.0f);
		glVertex2f ((int32_t)mPosition.x+(TRONCYCLE_SPRITE_WIDTH), (int32_t)mPosition.y-TRONCYCLE_SPRITE_HEIGHT);
		glTexCoord2f (1.0f, 0.0f);
		glVertex2f ((int32_t)mPosition.x, (int32_t)mPosition.y-TRONCYCLE_SPRITE_HEIGHT);
		break;

	case LEFT: //0,0 1,0 1,1 0,1
		leftTextCoord  = 0;
		rightTextCoord = 1;
		upperTextCoord = 0;
		lowerTextCoord = 1;
		glTexCoord2f (0.0f, 0.0f);
		glVertex2f ((int32_t)mPosition.x,(int32_t)mPosition.y); //bottom left point
		glTexCoord2f (1.0f, 0.0f);
		glVertex2f ((int32_t)mPosition.x+(TRONCYCLE_SPRITE_WIDTH), (int32_t)mPosition.y);
		glTexCoord2f (1.0f, 1.0f);
		glVertex2f ((int32_t)mPosition.x+(TRONCYCLE_SPRITE_WIDTH), (int32_t)mPosition.y-TRONCYCLE_SPRITE_HEIGHT);
		glTexCoord2f (0.0f, 1.0f);
		glVertex2f ((int32_t)mPosition.x, (int32_t)mPosition.y-TRONCYCLE_SPRITE_HEIGHT);
		break;

	case RIGHT:
		leftTextCoord  = 1;
		rightTextCoord = 0;
		upperTextCoord = 0;
		lowerTextCoord = 1;
		glTexCoord2f (1.0f, 0.0f);
		glVertex2f ((int32_t)mPosition.x,(int32_t)mPosition.y);
		glTexCoord2f (0.0f, 0.0f);
		glVertex2f ((int32_t)mPosition.x+(TRONCYCLE_SPRITE_WIDTH), (int32_t)mPosition.y);
		glTexCoord2f (0.0f, 1.0f);
		glVertex2f ((int32_t)mPosition.x+(TRONCYCLE_SPRITE_WIDTH), (int32_t)mPosition.y-TRONCYCLE_SPRITE_HEIGHT);
		glTexCoord2f (1.0f, 1.0f);
		glVertex2f ((int32_t)mPosition.x, (int32_t)mPosition.y-TRONCYCLE_SPRITE_HEIGHT);
		break;
	}

	glEnd ();
	glDisable(GL_TEXTURE_2D);
}

void TronCycleC::tryToSpawnLightWall()
{
	//flag for if we want to spawn lightWall
	bool8_t spawnLightWall = true;

	//we want to check through all corners of our hit box
	//so we check if any combination of rightX/leftX and UpY/DownY are in the grid position where we are trying to spawn a light wall.
	//if not, or flag never gets set to false, and we don't spawn a light wall. Otherwise we spawn one.
	for (char8_t row = 0; row <= 16; row+=16)
	{
		for (char8_t col = 0; col <= 16; col+=16)
		{
			if ((lightWallSpawn.x) == (((int32_t)mPosition.x+row)/32) && (lightWallSpawn.y == (((int32_t)mPosition.y-col)/32)))
			{
				spawnLightWall = false;
			}
		}
	}
	if (spawnLightWall)
	{
		lightWallSpawn.y-=1;
		LightWallManagerC::GetInstance()->addLightWall(lightWallSpawn, mID, 1.5f);
		lightWallSpawn.x = (int32_t)(mPosition.x/32);
		lightWallSpawn.y = (int32_t)(mPosition.y/32);
	}
}