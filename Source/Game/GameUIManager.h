#define NUM_PLAYERS 2
#define LIVES_SPRITESHEET_1 "content\\images\\lives1.png"
#define LIVES_SPRITESHEET_2 "content\\images\\lives2.png"

class GameUIManagerC
{
	public:
		static GameUIManagerC *CreateInstance();
		static GameUIManagerC *GetInstance();
		~GameUIManagerC(){};
		void init();
		void shutDown();
		void render();
		void renderLife();
		void reset();
		PlayerLifeDisplayC *getLifePtr(int32_t playerIndex);

	private:
		static GameUIManagerC *sInstance;
		PlayerLifeDisplayC **lifePtrs;
		GameUIManagerC(){};
		char** spriteFilePath;
		int32_t mNumPlayers;
		int32_t mNumLives;
};
