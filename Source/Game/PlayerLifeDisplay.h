class PlayerLifeDisplayC : public ObjectC
{
	public:
		PlayerLifeDisplayC();
		PlayerLifeDisplayC(float_t initPosX,float_t initPosY,int32_t id, char *path);
		~PlayerLifeDisplayC();
		void update(DWORD milliseconds);
		virtual void render();
		void disable() {mEnabled = false;};
		void enable() {mEnabled = true;};
		void updateLife();
		void reset();
	private:
		int32_t mSpriteCycle;
		float_t mSpriteIndex;
		char8_t mNumLives;
		bool8_t mEnabled;
		GLuint mSpriteMap;

		
};
#define LIFE_SPRITE_WIDTH			150
#define LIFE_SPRITE_HEIGHT			42
#define LIFE_SPRITE_TEXTURE_HEIGHT	42.0f
#define LIFE_NUM_SPRITES				4
#define LIFE_BOTTOM_TEXT_COORD		(SPRITE_TEXTURE_HEIGHT-SPRITE_HEIGHT)/SPRITE_TEXTURE_HEIGHT
#define LIFE_BOUNDING_WIDTH_OFFSET	(SPRITE_WIDTH-BOUNDING_BOX_WIDTH)/2
#define LIFE_BOUNDING_HEIGHT_OFFSET	(SPRITE_HEIGHT-BOUNDING_BOX_HEIGHT)/2

/*
//used for creating a quad with the correct bottom portion of the sprite
#define BOTTOM_TEXT_COORD		(SPRITE_TEXTURE_HEIGHT-SPRITE_HEIGHT)/SPRITE_TEXTURE_HEIGHT
#define BOTTOM_DEATH_TEXT_COORD	(SPRITE_TEXTURE_HEIGHT-(SPRITE_HEIGHT+64))/SPRITE_TEXTURE_HEIGHT
//used for adjusting the bounding box in relation to the sprite
#define BOUNDING_WIDTH_OFFSET	(SPRITE_WIDTH-BOUNDING_BOX_WIDTH)/2
#define BOUNDING_HEIGHT_OFFSET	(SPRITE_HEIGHT-BOUNDING_BOX_HEIGHT)/2

//used for adjusting the walk cycles
#define NUM_CYCLES				4
#define	CYCLE_LAG				8
*/
