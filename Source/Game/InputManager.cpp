#include <windows.h>													// Header File For the Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include "glut.h"
#include "openglframework.h"
#include "baseTypes.h"
#include "InputManager.h"
#include "Object.h"
#include "player.h"
#include "PlayerManager.h"
#include "BombManager.h"
#include "bomb.h"
InputManagerC* InputManagerC::sInstance = NULL;

InputManagerC *InputManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new InputManagerC();
	return sInstance;
}

void InputManagerC::update(DWORD milliseconds)
{
	Coord2D player1Vel;
	Coord2D player2Vel;
	player1Vel.x = 0.0f;
	player1Vel.y = 0.0f;
	player2Vel.x = 0.0f;
	player2Vel.y = 0.0f;

	Coord2D *player1Position;
	Coord2D *player2Position;
	ORIENTATION player1Orientation;
	ORIENTATION player2Orientation;
	//
	if (g_keys->keyDown[VK_ESCAPE])								// Is ESC Being Pressed?
	{
		TerminateApplication (g_window);						// Terminate The Program
	}

	if (g_keys->keyDown[VK_F1])									// Is F1 Being Pressed?
	{
		ToggleFullscreen (g_window);							// Toggle Fullscreen Mode
	}


	if (g_keys->keyDown['A'])
	{
		player1Vel.x -= PLAYER_SPEED;
	}
	if (g_keys->keyDown['D'])
	{
		player1Vel.x += PLAYER_SPEED;
	}
	if (g_keys->keyDown['W'])
	{
		player1Vel.y -= PLAYER_SPEED;
	}
	if (g_keys->keyDown['S'])
	{
		player1Vel.y += PLAYER_SPEED;
	}
	if (g_keys->keyDown[VK_LEFT])
	{
		player2Vel.x -= PLAYER_SPEED;
	}
	if (g_keys->keyDown[VK_RIGHT])
	{
		player2Vel.x += PLAYER_SPEED;
	}
	if (g_keys->keyDown[VK_UP])
	{
		player2Vel.y -= PLAYER_SPEED;
	}
	if (g_keys->keyDown[VK_DOWN])
	{
		player2Vel.y += PLAYER_SPEED;
	}
	if (g_keys->keyDown[VK_SHIFT])
	{
		PlayerManagerC::GetInstance()->getPlayerPtr(0)->killPlayer();
	}

	//keys for placing bombs
	if(g_keys->keyDown['E'])
	{
		//get position of the player
		player1Position = PlayerManagerC::GetInstance()->getPlayerPtr(0)->getPosition();
		player1Orientation = PlayerManagerC::GetInstance()->getPlayerPtr(0)->getOrientation();
		BombManagerC::GetInstance()->getBombPtr(0)->activate(player1Position->x,player1Position->y,player1Orientation);
	}
	if(g_keys->keyDown['P'])
	{
		//get position of the player
		player2Position = PlayerManagerC::GetInstance()->getPlayerPtr(1)->getPosition();
		player2Orientation = PlayerManagerC::GetInstance()->getPlayerPtr(1)->getOrientation();
		BombManagerC::GetInstance()->getBombPtr(1)->activate(player2Position->x,player2Position->y,player2Orientation);
	}

	PlayerManagerC::GetInstance()->getPlayerPtr(0)->setVelocity(&player1Vel); //set velocity of player1
	PlayerManagerC::GetInstance()->getPlayerPtr(1)->setVelocity(&player2Vel); //set velocity of player2
}