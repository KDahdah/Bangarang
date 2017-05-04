#define MENU_CPP
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
#include "menu.h"
#include "SOIL.h"
#include "game.h"

// Declarations
CMenu* CMenu::sInstance=NULL;

void CMenu::init()
{
	/* load an image file directly as a new OpenGL texture */
	mMenuTexture = SOIL_load_OGL_texture("content\\images\\Bangarang.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}
void CMenu::UpdateMenu(DWORD milliseconds)			
{
	//exitMenu();
}

void CMenu::DrawMenu(void)											
{
	startOpenGLDrawing();
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, mMenuTexture);
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
bool CMenu::exitMenu()
{
	if (g_keys->keyDown[VK_ESCAPE])								// Is ESC Being Pressed?
	{
		TerminateApplication (g_window);						// Terminate The Program
	}

	if (g_keys->keyDown[VK_F1])									// Is F1 Being Pressed?
	{
		ToggleFullscreen (g_window);							// Toggle Fullscreen Mode
	}
	if (g_keys->keyDown[VK_RETURN])
	{
		CGame::GetInstance()->playMusic();
		CGame::GetInstance()->reset();
		return false;
	}
	return true;
}


CMenu *CMenu::CreateInstance()
{
	sInstance = new CMenu();
	return sInstance;
}
void CMenu::shutdown()
{

}
void CMenu::DestroyMenu(void)
{

}