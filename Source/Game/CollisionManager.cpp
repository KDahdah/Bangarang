#define COLLISION_MANAGER_CPP
#include <assert.h>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>	// Header File For Variable Argument Routines
#include <math.h>	// Header File For Math Operations
#include <gl\gl.h>	// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"
#include "object.h"
#include "player.h"
#include "CollisionManager.h"



CollisionManagerC* CollisionManagerC::sInstance=NULL;


CollisionManagerC *CollisionManagerC::CreateInstance()
{
	assert(sInstance==NULL);
	sInstance = new CollisionManagerC();
	return sInstance;
}

void CollisionManagerC::init(char8_t* path)
{
	FILE* collisionMapFile;
	errno_t err = fopen_s(&collisionMapFile, path, "rb");
	if (err != 0)
	{
		printf("Error! Could not open collision map file\n");
		exit(1);
	}
	for (uint32_t col = 0; col < COLLISION_COL_SIZE; ++col)
	{
		for (uint32_t row = 0; row < COLLISION_ROW_SIZE; ++row)
		{
			fread_s(&CollisionMap[row][col], sizeof(char8_t), sizeof(char8_t), 1, collisionMapFile);
		}
	}
	fclose(collisionMapFile);
	
}
cMapState CollisionManagerC::getStateOfCoord(char8_t xCoord, char8_t yCoord)
{
	return (cMapState)CollisionMap[xCoord][yCoord];
}

bool8_t CollisionManagerC::checkCollisionsWithWalls(Coord2D position)
{

	bool8_t hasCollidedWithWall = false;



	//take the position and divide it by the size of the square each section of the table represents
	//basically, convert from ortho space to table space
	int32_t xPosInTable = ((int32_t)position.x)/COLLISION_UNIT;
	int32_t yPosInTable = ((int32_t)position.y)/COLLISION_UNIT;



		//This is checking the bottom left boundary
	if (CollisionMap[xPosInTable][yPosInTable] == cMapState::WALL)
	{
		hasCollidedWithWall = true;
	}



	//by adding the width of the bounding box before dividing by the size of each collision unit
	//you find the right most part of the bounding box
	xPosInTable = ((int32_t)position.x+BOUNDING_BOX_WIDTH)/COLLISION_UNIT;



		//this is checking the bottom right boundary
	if (CollisionMap[xPosInTable][yPosInTable] == cMapState::WALL)
	{
		hasCollidedWithWall = true;
	}



	//by subtracting the height of the bounding box before dividing by the size of each collision unit
	//you find the top most part of the bounding box
	yPosInTable = ((int32_t)position.y-BOUNDING_BOX_HEIGHT)/COLLISION_UNIT;



		//this is checking the top right boundary
	if (CollisionMap[xPosInTable][yPosInTable] == cMapState::WALL)
	{
		hasCollidedWithWall = true;
	}



	//switch back to using the left most part of the bounding box
	xPosInTable = ((int32_t)position.x)/COLLISION_UNIT;



			//this is checking the top left boundary
	if (CollisionMap[xPosInTable][yPosInTable] == cMapState::WALL)
	{
		hasCollidedWithWall = true;
	}



	//look Tom, no early outs
	return hasCollidedWithWall;
}

//nearly the same as check collision with walls
//these could be combined with some kind of contextual identifier of which to check for
bool8_t	CollisionManagerC::checkCollisionsWithLightWalls(Coord2D position)
{

	bool8_t hasCollided = false;



	//take the position and divide it by the size of the square each section of the table represents
	//basically, convert from ortho space to table space
	int32_t xPosInTable = ((int32_t)position.x)/COLLISION_UNIT;
	int32_t yPosInTable = ((int32_t)position.y)/COLLISION_UNIT;



		//This is checking the bottom left boundary
	if (CollisionMap[xPosInTable][yPosInTable] == cMapState::P1_LIGHT_WALL || 
			CollisionMap[xPosInTable][yPosInTable] == cMapState::P2_LIGHT_WALL)
	{
		hasCollided = true;
	}



	//by adding the width of the bounding box before dividing by the size of each collision unit
	//you find the right most part of the bounding box
	xPosInTable = ((int32_t)position.x+BOUNDING_BOX_HEIGHT)/COLLISION_UNIT;



		//this is checking the bottom right boundary
	if (CollisionMap[xPosInTable][yPosInTable] == cMapState::P1_LIGHT_WALL ||
			CollisionMap[xPosInTable][yPosInTable] == cMapState::P2_LIGHT_WALL)
	{
		hasCollided = true;
	}



	//by subtracting the height of the bounding box before dividing by the size of each collision unit
	//you find the top most part of the bounding box
	yPosInTable = ((int32_t)position.y-BOUNDING_BOX_HEIGHT)/COLLISION_UNIT;



		//this is checking the top right boundary
	if (CollisionMap[xPosInTable][yPosInTable] == cMapState::P1_LIGHT_WALL ||
			CollisionMap[xPosInTable][yPosInTable] == cMapState::P2_LIGHT_WALL)
	{
		hasCollided = true;
	}



	//switch back to using the left most part of the bounding box
	xPosInTable = ((int32_t)position.x)/COLLISION_UNIT;



	//this is checking the top left boundary
	if (CollisionMap[xPosInTable][yPosInTable] == cMapState::P1_LIGHT_WALL ||
			CollisionMap[xPosInTable][yPosInTable] == cMapState::P1_LIGHT_WALL)
	{
		hasCollided = true;
	}



	return hasCollided;
}

bool8_t CollisionManagerC::addLightWall(Int2D coords, char8_t playerID)
{
	bool8_t returnValue = false;
	if (CollisionMap[coords.x][coords.y] == cMapState::EMPTY)
	{
		returnValue = true;
		CollisionMap[coords.x][coords.y] = ((char8_t)cMapState::P1_LIGHT_WALL+playerID);
	}
	return returnValue;
}

void CollisionManagerC::removeLightWalls(char8_t playerID)
{
	for (char8_t row = 0; row < COLLISION_ROW_SIZE; ++row)
	{
		for (char8_t col = 0; col < COLLISION_COL_SIZE; ++col)
		{
			if (CollisionMap[row][col] == ((char8_t)cMapState::P1_LIGHT_WALL+playerID))
			{
				CollisionMap[row][col] = (char8_t)cMapState::EMPTY;
			}
		}
	}
}

void CollisionManagerC::removeLightWall(Coord2D wallCoord)
{
	if ((CollisionMap[(char8_t)wallCoord.x][ (char8_t)wallCoord.y] == cMapState::P1_LIGHT_WALL) ||
			(CollisionMap[(char8_t)wallCoord.x][ (char8_t)wallCoord.y] == cMapState::P2_LIGHT_WALL))
	{
		CollisionMap[(char8_t)wallCoord.x][ (char8_t)wallCoord.y] = cMapState::EMPTY;
	}
}


void CollisionManagerC::shutdown()
{
}

void CollisionManagerC::reset()
{
	removeLightWalls(0);
	removeLightWalls(1);
}