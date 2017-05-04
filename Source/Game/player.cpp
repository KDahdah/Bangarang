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
#include "player.h"
#include "LightWallManager.h"
#include "CollisionManager.h"
#include "inputmanager.h"
#include "SoundManager.h"


PlayerC::PlayerC(float_t initPosX,float_t initPosY,int32_t id, char* path)
{
	orientation = ORIENTATION::DOWN;
	cycleIndex = 0;
	lives = 3;
	startingX = initPosX+BOUNDING_WIDTH_OFFSET;
	startingY = initPosY-1;
	mPosition.x = startingX;
	mPosition.y = startingY;
	lightWallSpawn.x = (int32_t)startingX/32;
	lightWallSpawn.y = (int32_t)startingY/32;
	mID = id;
	mSpriteMap = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	alive = true;
}
PlayerC::PlayerC()
{
    mEnabled = true;
};
PlayerC::~PlayerC()
{
};

void PlayerC::killPlayer()
{
	alive = false;
	cycleIndex = 0;
	SoundManagerC::GetInstance()->playSound(SoundManagerC::SOUND::PLAYER_DEATH);
}

bool8_t PlayerC::isDead()
{
	bool8_t returnValue = false;
	if (lives == 0)
	{
		returnValue = true;
	}
	return returnValue;
}
void PlayerC::update(DWORD milliseconds)
{
	if (alive)
	{
		float_t yAdjust = 0.0f;
		float_t xAdjust = 0.0f;
		if (mVelocity.x > 0)
		{
			orientation = ORIENTATION::RIGHT;
			++cycleIndex;
		}
		else if (mVelocity.x < 0)
		{
			orientation = ORIENTATION::LEFT;
			++cycleIndex;
		}
		else if (mVelocity.y > 0)
		{
			orientation = ORIENTATION::DOWN;
			++cycleIndex;
		}
		else if (mVelocity.y < 0)
		{
			orientation = ORIENTATION::UP;
			++cycleIndex;
		}
		else
		{
			cycleIndex = 0;
		}
		cycleIndex = cycleIndex%(NUM_CYCLES*CYCLE_LAG);
		Coord2D testPos;
		testPos.x = mPosition.x + mVelocity.x*milliseconds;
		testPos.y = mPosition.y;
		if (!CollisionManagerC::GetInstance()->checkCollisionsWithWalls(testPos))
		{
			mPosition.x = testPos.x;
		}
		else
		{
			testPos.x = mPosition.x;
			float_t midPoint = mPosition.y-16;
			int32_t mod = (int32_t)midPoint%32;
			mod-=16;
			if (mod >= 0)
			{
				yAdjust = -1;
			}
			else if (mod < 0)
			{
				yAdjust = 1;
			}
		}
		testPos.y = mPosition.y + mVelocity.y*milliseconds;
		if (!CollisionManagerC::GetInstance()->checkCollisionsWithWalls(testPos))
		{
			mPosition.y = testPos.y;
		}
		else
		{
			float_t midPoint = mPosition.x-16;
			int32_t mod = (int32_t)midPoint%32;
			mod-=16;
			if (mod > 0)
			{
				xAdjust = -1;
			}
			else if (mod < 0)
			{
				xAdjust = 1;
			}
		}
		if (CollisionManagerC::GetInstance()->checkCollisionsWithLightWalls(mPosition))
		{
			killPlayer();
		}
		else
		{
			tryToSpawnLightWall();
		}
		mPosition.y+=yAdjust;
		mPosition.x+=xAdjust;
	}
	else
	{
		++cycleIndex;
		if (cycleIndex >= 64)
		{
			alive = true;
			mPosition.x = startingX;
			mPosition.y = startingY;
			lightWallSpawn.x = (int32_t)startingX/32;
			lightWallSpawn.y = (int32_t)startingY/32;
			LightWallManagerC::GetInstance()->deletePlayerWalls(0);
			LightWallManagerC::GetInstance()->deletePlayerWalls(1);
			cycleIndex = 0;
			--lives;
		}
	}

}

void PlayerC::tryToSpawnLightWall()
{
	//flag for if we want to spawn lightWall
	bool8_t spawnLightWall = true;

	//we want to check through all corners of our hit box
	//so we check if any combination of rightX/leftX and UpY/DownY are in the grid position where we are trying to spawn a light wall.
	//if not, or flag never gets set to false, and we don't spawn a light wall. Otherwise we spawn one.
	for (char8_t row = 0; row <= BOUNDING_BOX_WIDTH; row+=BOUNDING_BOX_WIDTH)
	{
		for (char8_t col = 0; col <= BOUNDING_BOX_HEIGHT; col+=BOUNDING_BOX_HEIGHT)
		{
			if ((lightWallSpawn.x) == (((int32_t)mPosition.x+row)/32) && (lightWallSpawn.y == (((int32_t)mPosition.y-col)/32)))
			{
				spawnLightWall = false;
			}
		}
	}
	if (spawnLightWall)
	{
		LightWallManagerC::GetInstance()->addLightWall(lightWallSpawn, (mID-1), 2.0f);
		lightWallSpawn.x = (int32_t)(mPosition.x/32);
		lightWallSpawn.y = (int32_t)(mPosition.y/32);
	}
}


void PlayerC::render()
{
   glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, mSpriteMap);
	glBegin (GL_QUADS);
		if (alive)
	{
		float_t leftTextCoord = (((float_t)orientation*4)+(cycleIndex/CYCLE_LAG))/NUM_SPRITES;
		float_t rightTextCoord = leftTextCoord+(1.0f/NUM_SPRITES);

		glColor4ub(0xFF, 0xFF, 0xFF,0xFF);
		glTexCoord2f (leftTextCoord, BOTTOM_TEXT_COORD);
		glVertex2f ((int32_t)mPosition.x-BOUNDING_WIDTH_OFFSET,(int32_t)mPosition.y);
		glTexCoord2f (rightTextCoord, BOTTOM_TEXT_COORD);
		glVertex2f ((int32_t)mPosition.x+(SPRITE_WIDTH-BOUNDING_WIDTH_OFFSET), (int32_t)mPosition.y);
		glTexCoord2f (rightTextCoord, 1.0f);
		glVertex2f ((int32_t)mPosition.x+(SPRITE_WIDTH-BOUNDING_WIDTH_OFFSET), (int32_t)mPosition.y-SPRITE_HEIGHT);
		glTexCoord2f (leftTextCoord, 1.0f);
		glVertex2f ((int32_t)mPosition.x-BOUNDING_WIDTH_OFFSET, (int32_t)mPosition.y-SPRITE_HEIGHT);
	}
	else
	{
		float_t leftTextCoord = ((float_t)(cycleIndex/CYCLE_LAG))/NUM_SPRITES;
		float_t rightTextCoord = leftTextCoord+(1.0f/NUM_SPRITES);
		glColor4ub(0xFF, 0xFF, 0xFF,0xFF);
		glTexCoord2f (leftTextCoord, BOTTOM_DEATH_TEXT_COORD);
		glVertex2f ((int32_t)mPosition.x-BOUNDING_WIDTH_OFFSET,(int32_t)mPosition.y);
		glTexCoord2f (rightTextCoord, BOTTOM_DEATH_TEXT_COORD);
		glVertex2f ((int32_t)mPosition.x+(SPRITE_WIDTH-BOUNDING_WIDTH_OFFSET), (int32_t)mPosition.y);
		glTexCoord2f (rightTextCoord, 0.5f);
		glVertex2f ((int32_t)mPosition.x+(SPRITE_WIDTH-BOUNDING_WIDTH_OFFSET), (int32_t)mPosition.y-SPRITE_HEIGHT);
		glTexCoord2f (leftTextCoord, 0.5f);
		glVertex2f ((int32_t)mPosition.x-BOUNDING_WIDTH_OFFSET, (int32_t)mPosition.y-SPRITE_HEIGHT);
	}


	glEnd ();
	glDisable(GL_TEXTURE_2D);
}

ORIENTATION PlayerC::getOrientation()
{
	return orientation;
}

void PlayerC::reset()
{
	alive = true;
	mPosition.x = startingX;
	mPosition.y = startingY;
	lightWallSpawn.x = (int32_t)startingX/32;
	lightWallSpawn.y = (int32_t)startingY/32;
	cycleIndex = 0;
	lives = 3;
}

char8_t PlayerC::getLives()
{
	return lives;
}