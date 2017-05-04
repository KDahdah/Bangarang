#include <fmod.hpp>
#include <fmod_codec.h>
#include <fmod_dsp.h>
#include <fmod_errors.h>
#include <fmod_memoryinfo.h>
#include <fmod_output.h>

class SoundSystemC
{
	public: 
		FMOD_RESULT result;
		FMOD::System *system;
		FMOD::Sound *sound;
		FMOD::Channel *channel;
		SoundSystemC(char* soundFilePath, char8_t isLoop);
		~SoundSystemC();

		void initSystem();
		void loadSound(char* filePath, char8_t isLoop);
		void playSound();
		void stopSound();
		void shutdown();
	private:
};
