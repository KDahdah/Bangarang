#include <stdio.h>
#include <stdlib.h>
#include "baseTypes.h"
#include "soundSystem.h"

SoundSystemC::SoundSystemC(char* soundFilePath, char8_t isLoop)
{
	initSystem();
	loadSound(soundFilePath, isLoop);
}

void SoundSystemC::initSystem()
{
	result = FMOD::System_Create(&system);		// Create the main system object.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = system->init(100, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void SoundSystemC::loadSound(char* filePath, char8_t isLoop)
{
	char8_t soundMode = FMOD_DEFAULT;
	if(isLoop)
	{
		soundMode = FMOD_LOOP_NORMAL;
	}
	result = system->createStream(filePath, soundMode, 0, &sound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
	//FMOD_DEFAULT
	//FMOD_LOOP_NORMAL
}

void SoundSystemC::playSound()
{
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel); //FMOD_CHANNEL_FREE 
}

void SoundSystemC::stopSound()
{
	printf("stop the fucking music\n");
	channel->stop();
}

void SoundSystemC::shutdown()
{
	printf("shuting down SoundSystem");
}
