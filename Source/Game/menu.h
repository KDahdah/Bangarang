class CMenu
{
public:
	static CMenu	*CreateInstance();
	static CMenu	*GetInstance() {return sInstance;};
	~CMenu();
	void DrawMenu();
	void UpdateMenu(DWORD milliseconds);
	bool exitMenu();
	void DestroyMenu();
	void init();
	void shutdown();
	static const uint32_t mScreenWidth = 1024;
	static const uint32_t mScreenHeight = 768;
	static const uint32_t mBitsPerPixel = 32;
private:
	GLuint mMenuTexture;
	static CMenu *sInstance;
	CMenu(){};
};