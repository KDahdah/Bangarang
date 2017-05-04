#include "soundSystem.h"

#define FILE_PATH_LENGTH 32
#define BANGARANG_GAME_MUSIC "content\\sound\\Bangarang_Game_Music.mp3"
#define BANGARANG_MENU_MUSIC "content\\sound\\Bangarang_Menu_Music.mp3"
#define BANGARANG_PLAYER_DEATH "content\\sound\\Bangarang_Game_Death.wav"
#define BANGARANG_BOMB_EXPLOSION "content\\sound\\Bangarang_Game_Explosion.wav"
#define NUM_SOUNDS 5

class SoundManagerC
{
	public:
		
		enum SOUND
		{
			NONE,
			GAME_MUSIC,
			MENU_MUSIC,
			PLAYER_DEATH,
			BOMB_EXPLOSION
		};

		static SoundManagerC *CreateInstance();
		static SoundManagerC *GetInstance();
		~SoundManagerC(){};
		void init();
		void playSound(SOUND sound);
		void stopSound(SOUND sound);
		void setSound(int32_t sound);
		void shutDown();

	private:
		static SoundManagerC *sInstance;
		SoundSystemC **soundPtrs;
		SoundManagerC(){};
		int32_t currentSound;
		char** soundFilePath;

};
