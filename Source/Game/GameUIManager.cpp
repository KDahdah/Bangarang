#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "object.h"
#include "PlayerLifeDisplay.h"
#include "GameUIManager.h"


GameUIManagerC* GameUIManagerC::sInstance = NULL;

GameUIManagerC* GameUIManagerC::GetInstance()
{
	return sInstance;
}

GameUIManagerC* GameUIManagerC::CreateInstance()
{
	if(sInstance != NULL)
	{
		return sInstance;
	}
	else
	{
		sInstance = new GameUIManagerC();
		return sInstance;
	}
}

void GameUIManagerC::init()
{
	mNumPlayers = NUM_PLAYERS;

	lifePtrs = (PlayerLifeDisplayC**)malloc(sizeof(PlayerLifeDisplayC*)*mNumPlayers); //2 players currently
	lifePtrs[0] = new PlayerLifeDisplayC(32*27.25,32*2,0,LIVES_SPRITESHEET_1);
	lifePtrs[1] = new PlayerLifeDisplayC(32*27.25,32*6,1,LIVES_SPRITESHEET_2);
}

PlayerLifeDisplayC *GameUIManagerC::getLifePtr(int32_t playerIndex)
{
	
	return lifePtrs[playerIndex];
}

void GameUIManagerC::render()
{
    renderLife();
}

void GameUIManagerC::renderLife()
{
    for(int32_t i=0;i<mNumPlayers;++i)
    {
       lifePtrs[i]->render();
	   lifePtrs[i]->updateLife();
    }
}

void GameUIManagerC::shutDown()
{
	printf("shutting down UI manager");
	for(int32_t i=0;i<mNumPlayers;++i)
    {
		delete lifePtrs[i];
	}
	free(lifePtrs);
}

void GameUIManagerC::reset()
{
	for(int32_t i=0;i<mNumPlayers;++i)
    {
       lifePtrs[i]->reset();
    }
}

