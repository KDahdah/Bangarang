class BombManagerC
{
public:
	static BombManagerC	*CreateInstance();
	static BombManagerC	*GetInstance() {return sInstance;};
	~BombManagerC(){};

	int32_t	getNumBombs() {return mNumBombs;};
	void	init();
	void	shutdown();
	void	updateBombs(DWORD milliseconds);
	BombC *	getBombPtr(int32_t index);
	void	renderBombs();
	void reset();
private:
	BombC **BombPtrs;
	static BombManagerC *sInstance;
	int32_t mNumBombs;
	BombManagerC(){};
};

#define NUM_BOMBS 2