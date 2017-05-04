#include "Timer.h"

class BombC : public ObjectC
{
	public:
		BombC();
		BombC(float_t initPosX,float_t initPosY,int32_t id, char *path);
		~BombC();
		void update(DWORD milliseconds);
		virtual void render();
		//void DoCollisions();
		void disable() {mEnabled = false;};
		void enable() {mEnabled = true;};
		void reduceVelocity(float_t factor);
		void moveUp();
		void detonate();
		void activate(float_t xPos, float_t yPos, ORIENTATION orientation);
		void updateTronCycles();
		void reset();
	private:
		//void CollideField();
		//a timer of some sort to trigger detonations
		int32_t spriteCycle;
		int32_t cycleIndex;
		int32_t mPlayerColor;
		bool8_t mEnabled;
		float_t mRadius;
		bool8_t mAtRest;
		GLuint mSpriteMap;
		bool8_t active;
		TimerC* timer;
		TronCycleC *mTronCycleUp;
		TronCycleC *mTronCycleDown;
		TronCycleC *mTronCycleLeft;
		TronCycleC *mTronCycleRight;
		int32_t mTronCycleSpeed;

		
};
#define BOMB_SPRITE_WIDTH			32
#define BOMB_SPRITE_HEIGHT			34
#define BOMB_SPRITE_TEXTURE_HEIGHT	34.0f
#define BOMB_NUM_SPRITES				1
#define BOMB_BOTTOM_TEXT_COORD		(SPRITE_TEXTURE_HEIGHT-SPRITE_HEIGHT)/SPRITE_TEXTURE_HEIGHT
#define BOMB_BOUNDING_WIDTH_OFFSET	(SPRITE_WIDTH-BOUNDING_BOX_WIDTH)/2
#define BOMB_BOUNDING_HEIGHT_OFFSET	(SPRITE_HEIGHT-BOUNDING_BOX_HEIGHT)/2

#define MAP_BOUND_LEFT   0
#define MAP_BOUND_RIGHT	 32*(27-1)
#define MAP_BOUND_TOP	 32
#define MAP_BOUND_BOTTOM 32*(25)

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
