enum ORIENTATION
{
	DOWN,
	LEFT,
	RIGHT,
	UP
};

class PlayerC : public ObjectC
{
public:
    PlayerC();
	PlayerC(float_t initPosX,float_t initPosY,int32_t id, char* path);
    ~PlayerC();
	void setPlayerColor(long color) {mPlayerColor = color;};
    long getPlayerColor() {return mPlayerColor;};
    void update(DWORD milliseconds);
    void render();
    void disable() {mEnabled = false;};
    void enable() {mEnabled = true;};
	void reduceVelocity(float_t factor);
	void killPlayer();
	bool8_t isDead();
	ORIENTATION getOrientation();
	void reset();
	char8_t getLives();
	//Coord2D getPosition();
private:
	//void CollideField();
	Int2D	lightWallSpawn;
	ORIENTATION orientation;
	float_t startingX;
	float_t startingY;
	char8_t lives;
	int32_t cycleIndex;
	int32_t mPlayerColor;
    bool8_t mEnabled;
    float_t mRadius;
	bool8_t mAtRest;
	GLuint mSpriteMap;
	bool8_t alive;

	void tryToSpawnLightWall();
};
#define BOUNDING_BOX_WIDTH		26
#define BOUNDING_BOX_HEIGHT		26
#define SPRITE_WIDTH			32
#define SPRITE_HEIGHT			48
#define SPRITE_TEXTURE_HEIGHT	128.0f
#define NUM_SPRITES				16

//used for creating a quad with the correct bottom portion of the sprite
#define BOTTOM_TEXT_COORD		(SPRITE_TEXTURE_HEIGHT-SPRITE_HEIGHT)/SPRITE_TEXTURE_HEIGHT
#define BOTTOM_DEATH_TEXT_COORD	(SPRITE_TEXTURE_HEIGHT-(SPRITE_HEIGHT+64))/SPRITE_TEXTURE_HEIGHT
//used for adjusting the bounding box in relation to the sprite
#define BOUNDING_WIDTH_OFFSET	(SPRITE_WIDTH-BOUNDING_BOX_WIDTH)/2
#define BOUNDING_HEIGHT_OFFSET	(SPRITE_HEIGHT-BOUNDING_BOX_HEIGHT)/2

//used for adjusting the walk cycles
#define NUM_CYCLES				4
#define	CYCLE_LAG				8