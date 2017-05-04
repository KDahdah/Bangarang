class CEndScreen
{
public:
	static CEndScreen	*CreateInstance();
	static CEndScreen	*GetInstance() {return sInstance;};
	~CEndScreen();
	void DrawScreen();
	void setWinner(char8_t playerID);
	bool exitScreen();
	void DestroyMenu();
	void init();
	void shutdown();
	static const uint32_t mScreenWidth = 1024;
	static const uint32_t mScreenHeight = 768;
	static const uint32_t mBitsPerPixel = 32;
private:
	GLuint mEndScreenP1Texture;
	GLuint mEndScreenP2Texture;
	int16_t winningPlayer;
	static CEndScreen *sInstance;
	CEndScreen(){};
};