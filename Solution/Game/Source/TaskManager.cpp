#include "TaskManager.h"
#include "App.h"
#include "Player.h"
#include "EntityManager.h"
#include "Scene.h"
#include "Input.h"

#include <iostream>

//TODO 4 Let's fill the function Execute command for each class. In these case, how should the player move
bool MoveLeft::Execute(Player* actor)
{
	bool ret = false;
	if (actor->pos.x == actor->posaux.x - 30)
	{
		actor->posaux.x = actor->pos.x;

 		ret = true;
	}
	else
	{
		actor->pos.x -= actor->speed.x;
	}
	return ret;
}

bool MoveRight::Execute(Player* actor)
{
	bool ret = false;
	if (actor->pos.x == actor->posaux.x + 30)
	{
		actor->posaux.x = actor->pos.x;
		
		ret = true;
	}
	else
	{
		actor->pos.x += actor->speed.x;
	}
	return ret;
}

bool MoveForward::Execute(Player* actor)
{
	bool ret = false;
	if (actor->pos.y == actor->posaux.y - 30)
	{
		actor->posaux.y = actor->pos.y;

		ret = true;
	}
	else
	{
		actor->pos.y -= actor->speed.y;
	}
	return ret;
}

bool MoveBackWard::Execute(Player* actor)
{
	bool ret = false;
	if (actor->pos.y == actor->posaux.y + 30)
	{
		actor->posaux.y = actor->pos.y;
		
		ret = true;
	}
	else
	{
		actor->pos.y += actor->speed.y;
	}
	return ret;
}

bool Task::Update(float dt)
{
	bool ret = false; 
	//TODO 5 Pop the first task of the list
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		if (aux_task == nullptr && TaskQueue.size() != 0)
		{
			aux_task = TaskQueue.front();
			TaskQueue.pop();
		}
	}

	ret = DoTask();

	return ret;
}

bool Task::CleanUp()
{
	while (TaskQueue.size() != 0)
	{
		TaskQueue.pop();
	}
	return true;
}

bool Task::AddTask(Task * task)
{
	//TODO 6 Add the new task to the list
	TaskQueue.push(task);

	return true;
}

bool Task::DoTask()
{
	if (aux_task != nullptr)
	{
		//TODO 7 If the task is finished, pop the next task until the queue is empty
		if (aux_task->Execute(app->scene->player))
		{
			if (TaskQueue.size() != 0)
			{
				aux_task = TaskQueue.front();
				TaskQueue.pop();
			}
			else aux_task = nullptr;

		}
	}
	return true;
}
