#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "object.h"
#include "openGLStuff.h"
#include "game.h"
#include "player.h"
#include "LightWallManager.h"
#include "PlayerManager.h"
#include "BombManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "BackgroundManager.h"
#include "soundManager.h"
#include "GameUIManager.h"
#include "endScreen.h"
//#include "SpriteDemoManager.h"

// Declarations
const char8_t CGame::mGameTitle[]="Bangarang";
CGame* CGame::sInstance=NULL;

void CGame::init()
{
	gameOver = false;
	//StateManagerC::CreateInstance();
	InputManagerC::CreateInstance();
	BackgroundManagerC::CreateInstance();
	CollisionManagerC::CreateInstance();
	PlayerManagerC::CreateInstance();
	LightWallManagerC::CreateInstance();
	SoundManagerC::CreateInstance();
	BombManagerC::CreateInstance();
	GameUIManagerC::CreateInstance();

	SoundManagerC::GetInstance()->init();
	SoundManagerC::GetInstance()->playSound(SoundManagerC::SOUND::MENU_MUSIC);

	GameUIManagerC::GetInstance()->init();
	InputManagerC::GetInstance()->init();
	//StateManagerC::GetInstance()->setState(StateManagerC::HALF_BALLS_FILLED);
	BackgroundManagerC::GetInstance()->init(ORTHOGRAPHIC_WIDTH,ORTHOGRAPHIC_HEIGHT);
	CollisionManagerC::GetInstance()->init("content\\LevelData\\bmLevel1.dat");
	PlayerManagerC::GetInstance()->init(2);
	LightWallManagerC::GetInstance()->init();
	InputManagerC::GetInstance()->init();

	BombManagerC::GetInstance()->init();
}
void CGame::playMusic()
{
	SoundManagerC::GetInstance()->stopSound(SoundManagerC::SOUND::MENU_MUSIC);
	SoundManagerC::GetInstance()->playSound(SoundManagerC::SOUND::GAME_MUSIC);
}
void CGame::UpdateFrame(DWORD milliseconds)			
{
	bool8_t returnValue = false;
	InputManagerC::GetInstance()->update(milliseconds);
	BombManagerC::GetInstance()->updateBombs(milliseconds); //max
	PlayerManagerC::GetInstance()->updatePlayers(milliseconds);
	LightWallManagerC::GetInstance()->updateLightWalls(milliseconds);
	if (PlayerManagerC::GetInstance()->getPlayerPtr(0)->isDead())
	{
		gameOver = true;
		CEndScreen::GetInstance()->setWinner(1);
	}
	else if (PlayerManagerC::GetInstance()->getPlayerPtr(1)->isDead())
	{
		gameOver = true;
		CEndScreen::GetInstance()->setWinner(0);
	}
}

bool8_t CGame::isGameOver()
{
	return gameOver;
	//shutdown();	
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();
	BackgroundManagerC::GetInstance()->renderSprites();
	LightWallManagerC::GetInstance()->renderLightWalls();
	PlayerManagerC::GetInstance()->renderPlayers();
	BombManagerC::GetInstance()->renderBombs();
	GameUIManagerC::GetInstance()->render();
}


CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
	//StateManagerC::GetInstance()->shutdown();
	BackgroundManagerC::GetInstance()->shutdown();
}
void CGame::reset()
{
	gameOver = false;
	CollisionManagerC::GetInstance()->reset();
	PlayerManagerC::GetInstance()->reset();
	LightWallManagerC::GetInstance()->reset();
	//SoundManagerC::GetInstance()->reset();
	BombManagerC::GetInstance()->reset();
}
void CGame::DestroyGame(void)
{
	//delete StateManagerC::GetInstance();	
}
