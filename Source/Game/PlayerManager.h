class PlayerManagerC
{
public:
	static PlayerManagerC	*CreateInstance();
	static PlayerManagerC	*GetInstance() {return sInstance;};
	~PlayerManagerC(){};

	int32_t	getNumPlayers() {return mNumPlayers;};
	void	init(int32_t numPlayers);
	void	shutdown();
	void	updatePlayers(DWORD milliseconds);
	PlayerC *	getPlayerPtr(int32_t index);
	void	renderPlayers();
	void	reset();
private:
	PlayerC **PlayerPtrs;
	static PlayerManagerC *sInstance;
	uint32_t mNumPlayers;
	PlayerManagerC(){};
};

#define MAP_GRID_ROW_COORD 27
#define MAP_GRID_COL_COORD 24