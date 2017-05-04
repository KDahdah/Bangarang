#define COLLISION_ROW_SIZE 27
#define COLLISION_COL_SIZE 24

#define COLLISION_UNIT 32
enum cMapState
{
	EMPTY = 0,
	WALL = 1,
	DESTRUCTABLE,
	P1_LIGHT_WALL,
	P2_LIGHT_WALL
};

class CollisionManagerC
{
public:
	static CollisionManagerC	*CreateInstance();
	static CollisionManagerC	*GetInstance() {return sInstance;};
	~CollisionManagerC(){};


	void	init(char8_t* path);
	void	shutdown();
	cMapState getStateOfCoord(char8_t xCoord, char8_t yCoord);
	bool8_t	checkCollisionsWithWalls(Coord2D position);
	bool8_t	checkCollisionsWithLightWalls(Coord2D position);
	bool8_t	addLightWall(Int2D coords, char8_t playerID);
	void removeLightWalls(char8_t playerID);
	void removeLightWall(Coord2D wallCoord);
	void reset();
private:
	char8_t CollisionMap[COLLISION_ROW_SIZE][COLLISION_COL_SIZE];
	static CollisionManagerC *sInstance;
	CollisionManagerC(){};
};