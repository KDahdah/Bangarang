#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl/GL.h>											// Header File For The OpenGL32 Library
#include <gl/GLU.h>										// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "object.h"
#include "SOIL.h"
#include "player.h"
#include "TronCycle.h"
#include "CollisionManager.h"
#include "inputmanager.h"
#include "PlayerManager.h"
#include "PlayerLifeDisplay.h"

PlayerLifeDisplayC::PlayerLifeDisplayC(float_t initPosX,float_t initPosY,int32_t id, char *path)
{
	mSpriteIndex = 0;
	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mID = id;
	mSpriteMap = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	mNumLives = 3; //link this to players health later
}
PlayerLifeDisplayC::PlayerLifeDisplayC()
{
    mEnabled = true;
};

PlayerLifeDisplayC::~PlayerLifeDisplayC()
{
};

void PlayerLifeDisplayC::update(DWORD milliseconds)
{
	updateLife();
}

void PlayerLifeDisplayC::updateLife()
{
	mNumLives = PlayerManagerC::GetInstance()->getPlayerPtr(mID)->getLives();
	//set mNumLives to the actual number of lives of the player
}


void PlayerLifeDisplayC::render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, mSpriteMap);
	glBegin (GL_QUADS);

	switch(mNumLives)
	{
	case 3:
		printf("THREE\n");
		mSpriteIndex = 0;
		break;

	case 2:
		printf("TWO\n");
		mSpriteIndex = 1;
		break;

	case 1:
		printf("ONE\n");
		mSpriteIndex = 2;
		break;

	case 0:
		printf("ZERO\n");
		mSpriteIndex = 3;
		break;
	}

    float_t leftTextCoord = ((mSpriteIndex))/LIFE_NUM_SPRITES;
	float_t rightTextCoord = leftTextCoord+(1.0f/LIFE_NUM_SPRITES);
	glColor4ub(0xFF, 0xFF, 0xFF,0xFF);
	glTexCoord2f (leftTextCoord, 0.0f);
	glVertex2f ((int32_t)mPosition.x,(int32_t)mPosition.y); //bottom left point
	glTexCoord2f (rightTextCoord, 0.0f); //take x and add width to it for right bottom
	glVertex2f ((int32_t)mPosition.x+(LIFE_SPRITE_WIDTH), (int32_t)mPosition.y);
	glTexCoord2f (rightTextCoord, 1.0f);
	glVertex2f ((int32_t)mPosition.x+(LIFE_SPRITE_WIDTH), (int32_t)mPosition.y-LIFE_SPRITE_HEIGHT);
	glTexCoord2f (leftTextCoord, 1.0f);
	glVertex2f ((int32_t)mPosition.x, (int32_t)mPosition.y-LIFE_SPRITE_HEIGHT);

	glEnd ();
	glDisable(GL_TEXTURE_2D);

}

void PlayerLifeDisplayC::reset()
{

}