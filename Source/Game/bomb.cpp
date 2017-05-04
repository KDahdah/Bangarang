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
#include "player.h"
#include "TronCycle.h"
#include "bomb.h"
#include "CollisionManager.h"
#include "inputmanager.h"
#include "SoundManager.h"

/* 
*  The BombManager class instantiates bombs by providing it with the parameters of:
*	an initial position (x,y)
*	an id
*	a string to reference the sprite file name
*/

BombC::BombC(float_t initPosX,float_t initPosY,int32_t id, char *path)
{
	timer = new TimerC(2);
	cycleIndex = 0;
	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mID = id;
	mSpriteMap = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	active = false;
	mTronCycleUp = NULL;
	mTronCycleDown = NULL;
	mTronCycleLeft = NULL;
	mTronCycleRight = NULL;
	mTronCycleSpeed = 10;
}
BombC::BombC()
{
    mEnabled = true;
};
BombC::~BombC()
{
	delete timer;
};

/*
*Update the state of the bomb
*/

void BombC::update(DWORD milliseconds)
{
	//run the timer which will trigger the bomb
	timer->RunTimer();
	if(timer->isFinished())
	{
		detonate();
	}

	//update the tron cycles that spawn from bomb detonation since they are essentailly the bomb "explosion"
	updateTronCycles();
}

void BombC::updateTronCycles()
{
	//if given tron cycle exists
	//  chack to see if each tron cycle spawned from a bomb explosion exist within the bounds of the map
	//	if so then update the tron cycle
	//	else delete it and set pointer to NULL
	if(mTronCycleUp)
	{
		if(mTronCycleUp->mPosition.y > MAP_BOUND_TOP)
		{
			mTronCycleUp->move();
		}
		else
		{
			delete mTronCycleUp;
			mTronCycleUp = NULL;
		}
	}
	if(mTronCycleDown)
	{
		if(mTronCycleDown->mPosition.y < MAP_BOUND_BOTTOM)
		{
			mTronCycleDown->move();
		}
		else
		{
			delete mTronCycleDown;
			mTronCycleDown = NULL;
		}
	}
	if(mTronCycleLeft)
	{
		if(mTronCycleLeft->mPosition.x >= MAP_BOUND_LEFT)
		{
			mTronCycleLeft->move();
		}
		else
		{
			delete mTronCycleLeft;
			mTronCycleLeft = NULL;
		}
	}
	if(mTronCycleRight)
	{
		if(mTronCycleRight->mPosition.x < MAP_BOUND_RIGHT)
		{
			mTronCycleRight->move();
		}
		else
		{
			delete mTronCycleRight;
			mTronCycleRight = NULL;
		}
	}
}


void BombC::render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, mSpriteMap);
	glBegin (GL_QUADS);

    float_t leftTextCoord = 0;
	float_t rightTextCoord = 1;
	glColor4ub(0xFF, 0xFF, 0xFF,0xFF);
	glTexCoord2f (leftTextCoord, 0.0f);
	glVertex2f ((int32_t)mPosition.x,(int32_t)mPosition.y); 
	glTexCoord2f (rightTextCoord, 0.0f); 
	glVertex2f ((int32_t)mPosition.x+(BOMB_SPRITE_WIDTH), (int32_t)mPosition.y);
	glTexCoord2f (rightTextCoord, 1.0f);
	glVertex2f ((int32_t)mPosition.x+(BOMB_SPRITE_WIDTH), (int32_t)mPosition.y-BOMB_SPRITE_HEIGHT);
	glTexCoord2f (leftTextCoord, 1.0f);
	glVertex2f ((int32_t)mPosition.x, (int32_t)mPosition.y-BOMB_SPRITE_HEIGHT);

	glEnd ();
	glDisable(GL_TEXTURE_2D);

	//render the troncycles after bomb detonation if they exist;
	if(mTronCycleUp)
	{
		mTronCycleUp->render();
	}
	if(mTronCycleDown)
	{
		mTronCycleDown->render();
	}
	if(mTronCycleLeft)
	{
		mTronCycleLeft->render();
	}
	if(mTronCycleRight)
	{
		mTronCycleRight->render();
	}

}

void BombC::activate(float_t xPos, float_t yPos, ORIENTATION orientation)
{
	if(!active)
	{
		active = true;
		mPosition.x =  xPos+16;
		mPosition.x = (mPosition.x - (int)(mPosition.x)%32);
		mPosition.y = (yPos - (int)yPos%32)+32;

		//run timer then detonate
		timer->StartTimer();
		//timer.GetTime();
	}
}

void BombC::detonate()
{
	SoundManagerC::GetInstance()->playSound(SoundManagerC::SOUND::BOMB_EXPLOSION);
	if(mTronCycleUp)
	{
		delete mTronCycleUp;
		mTronCycleUp = NULL;
	}
	if(mTronCycleDown)
	{
		delete mTronCycleDown;
		mTronCycleDown = NULL;
	}
	if(mTronCycleLeft)
	{
		delete mTronCycleLeft;
		mTronCycleLeft = NULL;
	}
	if(mTronCycleRight)
	{
		delete mTronCycleRight;
		mTronCycleRight = NULL;
	}

	printf("BOOM");
	active = false;
	mTronCycleUp	= new TronCycleC(mPosition.x,mPosition.y,mID,mTronCycleSpeed,UP);
	mTronCycleDown	= new TronCycleC(mPosition.x,mPosition.y,mID,mTronCycleSpeed,DOWN);
	mTronCycleLeft	= new TronCycleC(mPosition.x,mPosition.y,mID,mTronCycleSpeed,LEFT);
	mTronCycleRight = new TronCycleC(mPosition.x,mPosition.y,mID,mTronCycleSpeed,RIGHT);
	mPosition.x = 0;
	mPosition.y = 0;
}

void BombC::reset()
{
	if(mTronCycleUp)
	{
		delete mTronCycleUp;
		mTronCycleUp = NULL;
	}
	if(mTronCycleDown)
	{
		delete mTronCycleDown;
		mTronCycleDown = NULL;
	}
	if(mTronCycleLeft)
	{
		delete mTronCycleLeft;
		mTronCycleLeft = NULL;
	}
	if(mTronCycleRight)
	{
		delete mTronCycleRight;
		mTronCycleRight = NULL;
	}
	active = false;
	mPosition.x = 0;
	mPosition.y = 0;
}