#include "Timer.h"
class LightWallC : public ObjectC
{
public:
    LightWallC();
	LightWallC(float_t initPosX,float_t initPosY,int32_t id, GLuint textureIndex, float_t time);
    ~LightWallC();
    void render();
	bool8_t isTimeUp();
	void moveUp();
	void killLightWall();
	bool8_t isDead();
	char8_t getIdOfPlayer();
private:
	GLuint mSpriteMap;
	TimerC* mTimer;
};
#define WALL_WIDTH  32
#define WALL_HEIGHT 32
#define TEXTURE_WIDTH 64