class BallC;
class PlayerC;
class BombC;
class FieldC;
class TronCycleC;
class LightWallC;
class PlayerLifeDisplayC;
class ObjectC
{
	friend class PlayerC;
	friend class BombC;
    friend class BallC;
	friend class FieldC;
	friend class TronCycleC;
	friend class LightWallC;
	friend class PlayerLifeDisplayC;
public:
    ObjectC(float initPosX, float initPosY, float initVelX, float initVelY);
    ObjectC();
    ~ObjectC();
    void setPosition(Coord2D *posToSet) {mPosition.x = posToSet->x;mPosition.y = posToSet->y;};
    Coord2D *getPosition() {return &mPosition;};
    void setVelocity(Coord2D *velToSet) {mVelocity.x = velToSet->x;mVelocity.y = velToSet->y;};
    void setVelocity(float x, float y) {mVelocity.x = x;mVelocity.y = y;};
    Coord2D *getVelocity() {return &mVelocity;};
	int32_t getID() {return mID;};
	void setID(int32_t id) {mID = id;};
	virtual void render()=0;
private:
    Coord2D mPosition;
    Coord2D mVelocity;
	int32_t mID;
};