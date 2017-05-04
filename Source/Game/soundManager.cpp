#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"
#include "soundManager.h"


SoundManagerC* SoundManagerC::sInstance = NULL;

SoundManagerC* SoundManagerC::GetInstance()
{
	return sInstance;
}

SoundManagerC* SoundManagerC::CreateInstance()
{
	if(sInstance != NULL)
	{
		return sInstance;
	}
	else
	{
		sInstance = new SoundManagerC();
		return sInstance;
	}
}

void SoundManagerC::init()
{
	soundFilePath = (char**)malloc(NUM_SOUNDS*FILE_PATH_LENGTH);
	soundFilePath[0] = NULL;
	soundFilePath[1] = BANGARANG_GAME_MUSIC;
	soundFilePath[2] = BANGARANG_MENU_MUSIC;
	soundFilePath[3] = BANGARANG_PLAYER_DEATH;
	soundFilePath[4] = BANGARANG_BOMB_EXPLOSION;

	printf("Hey initing the sound manager!\n");
	soundPtrs = (SoundSystemC**)malloc(NUM_SOUNDS*sizeof(SoundSystemC*));

	char8_t isLoop = false;
	for(int i = 0; i < NUM_SOUNDS; i++)
	{
		isLoop = false;
		if(i == 1 || i == 2) //if sound is a song, then loop it.
		{
			isLoop = true;
		}
		soundPtrs[i] = new SoundSystemC(soundFilePath[i],isLoop);
	}

}

void SoundManagerC::setSound(int32_t sounds)
{

}

void SoundManagerC::playSound(SOUND sound)
{
	soundPtrs[(int)sound]->playSound();
}

void SoundManagerC::stopSound(SOUND sound)
{
	soundPtrs[(int)sound]->stopSound();
}


void SoundManagerC::shutDown()
{
	printf("shutting down sound manager");
}

