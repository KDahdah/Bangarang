class TronCycleC : public ObjectC
{
	public:
		TronCycleC(float_t initPosX, float_t initPosY, int32_t id, float_t velocity, ORIENTATION direction);
		TronCycleC();
		~TronCycleC(){};
		void setDirection(ORIENTATION direction);
		void setVelocity(float_t velocity);
		void move();
		void destroy();
		void render();

	private:
		Int2D	lightWallSpawn;
		ORIENTATION mDirection;
		float_t mVelocity;
		int32_t cycleIndex;
		GLuint mSpriteMap;
		bool8_t mActive;
		char* mSpritePath;
		void tryToSpawnLightWall();
};

#define TRONCYCLE_SPRITE_PATH				"content\\images\\tronCycle.png"
#define TRONCYCLE_SPRITE_WIDTH				32
#define TRONCYCLE_SPRITE_HEIGHT				32
#define TRONCYCLE_SPRITE_TEXTURE_HEIGHT		32.0f
#define TRONCYCLE_NUM_SPRITES				1
#define TRONCYCLE_BOTTOM_TEXT_COORD			(SPRITE_TEXTURE_HEIGHT-SPRITE_HEIGHT)/SPRITE_TEXTURE_HEIGHT
#define TRONCYCLE_BOUNDING_WIDTH_OFFSET		(SPRITE_WIDTH-BOUNDING_BOX_WIDTH)/2
#define TRONCYCLE_BOUNDING_HEIGHT_OFFSET	(SPRITE_HEIGHT-BOUNDING_BOX_HEIGHT)/2