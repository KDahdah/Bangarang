//linked list node for light wall linked list
struct lwNode
{
	lwNode* next;
	LightWallC* wall;
};

class LightWallManagerC
{
public:
	static LightWallManagerC	*CreateInstance();
	static LightWallManagerC	*GetInstance() {return sInstance;};
	~LightWallManagerC(){};

	void	init();
	void	shutdown();
	void	addLightWall(Int2D wallCoord, char8_t playerID, float_t time);
	void	updateLightWalls(DWORD milliseconds);
	void	renderLightWalls();
	void	deletePlayerWalls(char8_t playerID);
	void	reset();
private:
	lwNode* lightWallListBegin;
	lwNode* lightWallListEnd;
	uint16_t mNumLightWalls;
	GLuint lwTexture;
	static LightWallManagerC *sInstance;
	LightWallManagerC(){};
	void renderWall(char8_t xCoord, char8_t yCoord, char8_t playerID);
	void removeLightWall(LightWallC* wallToDelete);
};
#define WALL_WIDTH  32
#define WALL_HEIGHT 32
#define TEXTURE_WIDTH 64
#define MAP_GRID_ROW_COORD 27
#define MAP_GRID_COL_COORD 24
#define LW_TEXTURE "content\\images\\lightWall2.png"