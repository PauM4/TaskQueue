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
	Task() {};
	virtual ~Task() {};

	virtual bool Execute(Player* actor) { return true; };

	bool Update(float dt);
	bool CleanUp();

	bool AddTask(Task* task);
	bool DoTask();

private:
	//TODO 1 Create a queue of tasks
	std::queue<Task*> TaskQueue;
	
public:
	Task * aux_task = nullptr;
};


class MoveLeft : public Task
{
public:
	MoveLeft() {};
	virtual  ~MoveLeft() {};

	bool Execute(Player* actor);
};
//TODO 2 Create a class for each task you want to do (one for each direction)
//TODO 6 Add the parameter "Actor" to all Execute() functions 

class MoveRight : public Task
{
public:
	MoveRight() {};
	virtual  ~MoveRight() {};

	bool Execute(Player* actor);
};

class MoveForward : public Task
{
public:
	MoveForward() {};
	virtual  ~MoveForward() {};

	bool Execute(Player* actor);
};

class MoveBackWard : public Task
{
public:
	MoveBackWard() {};
	virtual  ~MoveBackWard() {};

	bool Execute(Player* actor);
};
#endif // !_TASKMANAGER_H__

