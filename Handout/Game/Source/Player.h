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
	
	SDL_Texture* texture;
	const char* texturePath;

	//TODO 3 Add new task for each button
	

};

#endif // __PLAYER_H__