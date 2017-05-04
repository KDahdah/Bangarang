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
#include "BombManager.h"
#include "bomb.h"



BombManagerC* BombManagerC::sInstance=NULL;


BombManagerC *BombManagerC::CreateInstance()
{
	assert(sInstance==NULL);
	sInstance = new BombManagerC();
	return sInstance;
}

void BombManagerC::init()
{
	printf("Hey initing the BOMB manager!\n");
	mNumBombs = NUM_BOMBS;
	BombPtrs = (BombC**)malloc(mNumBombs*sizeof(BombC*));

	
	BombPtrs[0] = new BombC(0.0f, 0.0f, 0, "content\\images\\tronBomb.png");
	BombPtrs[1] = new BombC(0.0f, 0.0f, 1, "content\\images\\tronBomb.png");
}
void BombManagerC::updateBombs(DWORD milliseconds)
{
	
    for(int32_t i=0;i<mNumBombs;++i)
    {
       BombPtrs[i]->update(milliseconds);
    }
	
}

BombC *BombManagerC::getBombPtr(int32_t index)
{
	
	return BombPtrs[index];
	

}

void BombManagerC::renderBombs()
{
    for(int32_t i=0;i<mNumBombs;++i)
    {
       BombPtrs[i]->render();
    }
}
void BombManagerC::shutdown()
{
	for(int32_t i=0;i<mNumBombs;++i)
    {
		delete BombPtrs[i];
	}
	free(BombPtrs);
}

void BombManagerC::reset()
{
	for(int32_t i=0;i<mNumBombs;++i)
    {
       BombPtrs[i]->reset();
    }
}