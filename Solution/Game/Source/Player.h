#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "Module.h"
#include "TaskManager.h"
#include "SDL/include/SDL.h"

class Task;

struct SDL_Texture;

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update();

	bool Movement();

	bool CleanUp();

public:
	iPoint pos;
	iPoint posaux;
	iPoint speed;

private:
	//L02: DONE 1: Declare player parameters
	
	SDL_Texture* texture;
	const char* texturePath;

	Task* buttonW = nullptr;
	Task* buttonA = nullptr;
	Task* buttonS = nullptr;
	Task* buttonD = nullptr;

};

#endif // __PLAYER_H__