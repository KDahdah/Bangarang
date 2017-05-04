#define PLAYER_MANAGER_CPP
#include <assert.h>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>	// Header File For Variable Argument Routines
#include <math.h>	// Header File For Math Operations
#include <gl\gl.h>	// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "object.h"
#include "Player.h"
#include "PlayerManager.h"



PlayerManagerC* PlayerManagerC::sInstance=NULL;


PlayerManagerC *PlayerManagerC::CreateInstance()
{
	assert(sInstance==NULL);
	sInstance = new PlayerManagerC();
	return sInstance;
}

void PlayerManagerC::init(int32_t numPlayers)
{
	printf("Hey initing the Player manager!\n");
	mNumPlayers = numPlayers;
	PlayerPtrs = (PlayerC**)malloc(mNumPlayers*sizeof(PlayerC*));
	switch(mNumPlayers)
	{
	case 2:
		PlayerPtrs[0] = new PlayerC(1*32, 2*32, 1, "content\\images\\bManSpriteSheet1.png");
		PlayerPtrs[1] = new PlayerC((MAP_GRID_ROW_COORD-2)*32, (MAP_GRID_COL_COORD-1)*32, 2, "content\\images\\bManSpriteSheet2.png");
		break;
	}
}
void PlayerManagerC::updatePlayers(DWORD milliseconds)
{
    for(uint32_t i=0;i<mNumPlayers;++i)
    {
       PlayerPtrs[i]->update(milliseconds);
    }
}

PlayerC *PlayerManagerC::getPlayerPtr(int32_t index)
{
	return PlayerPtrs[index];
}
void PlayerManagerC::renderPlayers()
{
    for(uint32_t i=0;i<mNumPlayers;++i)
    {
       PlayerPtrs[i]->render();
    }
}
void PlayerManagerC::shutdown()
{
	for(uint32_t i=0;i<mNumPlayers;++i)
    {
		delete PlayerPtrs[i];
	}
	free(PlayerPtrs);
}

void PlayerManagerC::reset()
{
	for(uint32_t i=0;i<mNumPlayers;++i)
    {
		PlayerPtrs[i]->reset();
	}
}