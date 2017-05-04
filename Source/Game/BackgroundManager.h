struct VertexFormatPos3Tex2
{   // Custom vertex format for position+normal
	float tu , tv ;             ///< texture coordinates	
	float px , py , pz ;        ///< untransformed (world-space) position
};

	class BackgroundManagerC
{
public:
	static BackgroundManagerC	*CreateInstance();
	static BackgroundManagerC	*GetInstance() {return sInstance;};
	~BackgroundManagerC(){};

	void		init(int width, int height);
	void		renderSprites();
	void		shutdown();

	int			getWidth() {return mWidth;}
	int			getHeight() {return mHeight;}

private:
	static BackgroundManagerC *sInstance;
	BackgroundManagerC(){};

	GLuint mSpriteTextureMap;
	int mWidth;
	int mHeight;

	DWORD mLastUpdateTime;
	DWORD mCurrentTime;
};