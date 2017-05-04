#define LW_MANAGER_CPP
#include <assert.h>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>	// Header File For Variable Argument Routines
#include <math.h>	// Header File For Math Operations
#include <gl\gl.h>	// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "SOIL.h"
#include "CollisionManager.h"
#include "openglframework.h"	
#include "object.h"
#include "lightWall.h"
#include "LightWallManager.h"



LightWallManagerC* LightWallManagerC::sInstance=NULL;


LightWallManagerC *LightWallManagerC::CreateInstance()
{
	assert(sInstance==NULL);
	sInstance = new LightWallManagerC();
	return sInstance;
}

void LightWallManagerC::init()
{
	lwTexture = SOIL_load_OGL_texture(LW_TEXTURE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	printf("Hey initing the LightWall manager!\n");
	lightWallListBegin = NULL;
	//lightWallListBegin->next = NULL;
	//lightWallListBegin->wall = NULL;
	lightWallListEnd = NULL;
	mNumLightWalls = 0;
}

void LightWallManagerC::addLightWall(Int2D wallCoord, char8_t playerID, float_t time)
{
	lwNode* newNode = NULL;
	if (CollisionManagerC::GetInstance()->addLightWall(wallCoord, playerID))
	{
		newNode = new lwNode;
		if (lightWallListEnd == NULL)
		{
			lightWallListBegin = newNode;
			lightWallListEnd = lightWallListBegin;
		}
		else
		{
			lightWallListEnd->next = newNode;
			lightWallListEnd = lightWallListEnd->next;
		}
		lightWallListEnd->next = NULL;
		lightWallListEnd->wall = new LightWallC(wallCoord.x, wallCoord.y, playerID, lwTexture, time);
		mNumLightWalls++;
	}
}

void LightWallManagerC::updateLightWalls(DWORD milliseconds)
{
	lwNode* lastNode = NULL;
	lwNode* testNode = lightWallListBegin;
	while(testNode != NULL)
	{
		if (testNode->wall->isTimeUp())
		{
			if (lastNode != NULL)
			{
				lastNode->next = testNode->next;
				removeLightWall(testNode->wall);
				delete testNode;
				testNode = lastNode->next;
			}
			else
			{
				lwNode* tempNode = testNode->next;
				removeLightWall(testNode->wall);
				delete testNode;
				testNode = tempNode;
				lightWallListBegin = testNode;
			}
		}
		else
		{
			lastNode = testNode;
			testNode = testNode->next;
		}
	}
	lightWallListEnd = lastNode;
}
void LightWallManagerC::removeLightWall(LightWallC* wallToDelete)
{
	CollisionManagerC::GetInstance()->removeLightWall(*wallToDelete->getPosition());
	delete wallToDelete;
}
void LightWallManagerC::renderLightWalls()
{
	lwNode* tempNode = lightWallListBegin;
	while(tempNode != NULL)
	{
		tempNode->wall->render();
		tempNode = tempNode->next;
	}
}

void LightWallManagerC::renderWall(char8_t xCoord, char8_t yCoord, char8_t playerID)
{
	int32_t posX = xCoord*32;
	int32_t posY = (yCoord+1)*32;

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, lwTexture);
	glBegin (GL_QUADS);

	float_t leftTextCoord = ((float_t)playerID*WALL_WIDTH)/TEXTURE_WIDTH;
	float_t rightTextCoord = leftTextCoord+((float_t)WALL_WIDTH/TEXTURE_WIDTH);

	glColor4ub(0xFF, 0xFF, 0xFF,0xFF);
	glTexCoord2f (leftTextCoord, 0.0f);
	glVertex2f (posX,posY);
	glTexCoord2f (rightTextCoord, 0.0f);
	glVertex2f (posX+(WALL_WIDTH), posY);
	glTexCoord2f (rightTextCoord, 1.0f);
	glVertex2f (posX+(WALL_WIDTH), posY-WALL_HEIGHT);
	glTexCoord2f (leftTextCoord, 1.0f);
	glVertex2f (posX, posY-WALL_HEIGHT);


	glEnd ();
	glDisable(GL_TEXTURE_2D);
}

void LightWallManagerC::deletePlayerWalls(char8_t playerID)
{
	lwNode* testNode = lightWallListBegin;
	lwNode* lastNode = NULL;

	while (testNode != NULL)
	{
		if (testNode->wall->getIdOfPlayer() == playerID)
		{
			if (lastNode != NULL)
			{
				lastNode->next = testNode->next;
				delete testNode->wall;
				delete testNode;
				testNode = lastNode->next;
			}
			else
			{
				lwNode* tempNode = testNode->next;
				delete testNode->wall;
				delete testNode;
				testNode = tempNode;
				lightWallListBegin = testNode;
			}
		}
		else
		{
			lastNode = testNode;
			testNode = testNode->next;
		}

	}
	lightWallListEnd = lastNode;
	CollisionManagerC::GetInstance()->removeLightWalls(playerID);
}
void LightWallManagerC::shutdown()
{
	deletePlayerWalls(0);
	deletePlayerWalls(1);
}

void LightWallManagerC::reset()
{
	deletePlayerWalls(0);
	deletePlayerWalls(1);
}