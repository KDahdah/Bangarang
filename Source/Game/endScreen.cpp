#define END_SCREEN_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "openGLStuff.h"
#include "endScreen.h"
#include "game.h"
#include "SOIL.h"
#include "SoundManager.h"

// Declarations
CEndScreen* CEndScreen::sInstance=NULL;

void CEndScreen::init()
{
	/* load an image file directly as a new OpenGL texture */
	mEndScreenP1Texture = SOIL_load_OGL_texture("content\\images\\p1WinScreen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	mEndScreenP2Texture = SOIL_load_OGL_texture("content\\images\\p2WinScreen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	winningPlayer = 0;
}

void CEndScreen::setWinner(char8_t playerID)
{
	winningPlayer = playerID;
}
void CEndScreen::DrawScreen(void)											
{
	startOpenGLDrawing();
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, mEndScreenP1Texture+winningPlayer);
	glBegin (GL_QUADS);

	glColor4ub(0xFF, 0xFF, 0xFF,0xFF);
	glTexCoord2f (0.0f, 0.0f);
	glVertex2f (0.0f, ORTHOGRAPHIC_HEIGHT);
	glTexCoord2f (1.0f, 0.0f);
	glVertex2f (ORTHOGRAPHIC_WIDTH,ORTHOGRAPHIC_HEIGHT);
	glTexCoord2f (1.0f, 1.0f);
	glVertex2f (ORTHOGRAPHIC_WIDTH, 0.0f);
	glTexCoord2f (0.0f, 1.0f);
	glVertex2f (0.0f, 0.0f);


	glEnd ();
	glDisable(GL_TEXTURE_2D);
}
bool CEndScreen::exitScreen()
{
	if (g_keys->keyDown[VK_ESCAPE])								// Is ESC Being Pressed?
	{
		TerminateApplication (g_window);						// Terminate The Program
	}

	if (g_keys->keyDown[VK_F1])									// Is F1 Being Pressed?
	{
		ToggleFullscreen (g_window);							// Toggle Fullscreen Mode
	}
	if (g_keys->keyDown[VK_SPACE])
	{
		SoundManagerC::GetInstance()->stopSound(SoundManagerC::SOUND::GAME_MUSIC);
		SoundManagerC::GetInstance()->playSound(SoundManagerC::SOUND::MENU_MUSIC);
		return true;
		//CGame::GetInstance()->reset();
	}
	return false;
}


CEndScreen *CEndScreen::CreateInstance()
{
	sInstance = new CEndScreen();
	return sInstance;
}
void CEndScreen::shutdown()
{

}
void CEndScreen::DestroyMenu(void)
{

}
