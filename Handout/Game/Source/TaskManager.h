#ifndef _TASKMANAGER_H__
#define _TASKMANAGER_H__

#include "Point.h"
#include <queue>
#include "Player.h"
#include "Module.h"

class Player;

class Task: public Module
{
public:
	//TODO 0 Understand what how works the nex class Task Manager
	Task() {};
	virtual ~Task() {};

	virtual bool Execute(Player* actor) { return true; };

	bool Update(float dt);
	bool CleanUp();

	bool AddTask(Task* task);
	bool DoTask();

private:
	//TODO 1 Create a queue of tasks
	
	
public:
	Task * aux_task = nullptr;
};

//TODO 2 Create a class for each task you want to do (one for each direction)

class MoveLeft : public Task
{
public:
	
};

class MoveRight : public Task
{
public:
	
};

class MoveForward : public Task
{
public:
	
};

class MoveBackWard : public Task
{
public:
	
};
#endif // !_TASKMANAGER_H__

