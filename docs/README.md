# TASK QUEUE: Project Research

## Introduction
Tasks refer to work that may take a long time to complete and can be processed asynchronously. Waiting until a task completes before proceeding with the game is not feasible. To manage these tasks effectively, a Task Queue is utilized, where all the tasks are added and executed in the background. There are two types of Task Queues available: Push Queues and Pull Queues. Push Queues automatically handle the actions that are added to them, whereas Pull Queues contain a list of actions that can be executed at any time.

For instance, Push Queues are useful in messaging systems such as WhatsApp. One can continue to send messages even if the previously sent messages have not been delivered yet. In video games, Push Queues are often used to handle events that happen in real time. For example, in a racing game, events that occur on the track, such as the collision of two cars, can be automatically added to a background task queue to be processed in the order they occurred.

On the other hand, Pull Queues are typically used in RPG games where a character is assigned tasks, and the game processes them in a sequential order. For example, in a real-time strategy game, the player may give specific orders to a group of units, and these orders are added to a task queue that is executed in the order they were received.

## Task Queue in videogames
A great way to learn how to use task queues in video games is by observing how other games have implemented them. Here are some examples of task queues that are easy to identify at first glance.

### Age of Empires
In games like Age of Empires, constructing a building takes time and resources. The game adds the construction task to a queue and processes it in the background while allowing the player to continue managing their empire.

### World of Warcraft
In games with RPG mechanics, players can use powerful abilities that have a cooldown period before they can be used again. These abilities are added to a task queue and cannot be used again until the cooldown has completed.
Also, completing a quest involves multiple steps and requires the player to interact with various NPCs or objects. The game uses a task queue to manage the quest progression and ensure that the player completes each step in the correct order.

### Civilitzation
In games like Civilization, combat is turn-based, meaning that each player or character takes turns making moves. The game uses a task queue to manage the turn order and ensure that each player or character gets their turn in the correct order.

## Command Pattern
In order to implement task queues, we utilize what is known as the command pattern. According to the book "Game Programming Patterns", "commands are an object-oriented replacement for callbacks". By treating tasks as objects rather than functions, we can apply the command pattern to redefine keys and change the actor of the action.

To apply the command pattern, you typically define a Command interface or abstract class that specifies a method for executing the command. You then create concrete command classes that implement the Command interface and encapsulate a specific request or action. The command objects are usually created by a client and passed to an invoker object, which maintains a queue of commands and executes them in order.

In video games, the command pattern can be used to implement task queues, as mentioned earlier. By treating tasks as objects and encapsulating them within command objects, you can easily add them to a task queue and execute them in the background, while allowing the player to continue interacting with the game world. This approach enables you to create complex gameplay mechanics that can be managed seamlessly and efficiently, without disrupting the player's experience.

## Selected approach

For my Task Queue research, I have chosen to focus on the combat of RPG games. In this type of combat, the task queue or the task manager is very useful due to the fact that multiple actions are performed in one turn and these must be ordered and executed in a certain way.

In simple turn-based RPGs, the order in which the different abilities and attacks will be executed has to be organized. On the other hand, in tactical RPGs, the possibility of choosing where to move our character is added. All this added up, makes the task queue or task manager essential for the combat to develop correctly.

## Exercise

For this practical part we will learn how to implement a simple task manager and the basic commands to make a player move after indicate him what moves to make.

### TODO 0

```
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
	std::queue<Task*> TaskQueue;
	
public:
	Task * aux_task = nullptr;
};
```

### TODO 1

```
private:
	//TODO 1 Create a queue of tasks
	std::queue<Task*> TaskQueue;
```

### TODO 2

```
//TODO 2 Create a class for each task you want to do (one for each direction)

class MoveLeft : public Task
{
public:
	MoveLeft() {};
	virtual  ~MoveLeft() {};

	bool Execute(Player* actor);
};
```

### TODO 3

```
private:
	
	SDL_Texture* texture;
	const char* texturePath;

	//TODO 3 Add new task for each button
	Task* buttonW = nullptr;
	Task* buttonA = nullptr;
	Task* buttonS = nullptr;
	Task* buttonD = nullptr;

};
```

### TODO 4

```
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
```

### TODO 5

```
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
```

### TODO 6

```
bool Task::AddTask(Task * task)
{
	//TODO 6 Add the new task to the list
	TaskQueue.push(task);

	return true;
}
```

### TODO 7

```
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
```

### TODO 8

```
bool Player::Start() {

	//initilize textures
	speed.x = 2;
	speed.y = 2;
	texture = app->tex->Load(texturePath);

	//TODO 8 Initialize the task that we will use
	buttonD = new MoveRight;
	buttonA = new MoveLeft;
	buttonW = new MoveForward;
	buttonS = new MoveBackWard;
	return true;
}
```

### TODO 9

```
bool Player::CleanUp()
{
	//TODO 9 Remember to delete the new Tasks
	delete buttonD;
	delete buttonA;
	delete buttonW;
	delete buttonS;
	return true;
}
```

### TODO 10

```
bool Player::Movement()
{
	//TODO 10 Add the task to the queque 
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		posaux = pos;
		app->task->AddTask(buttonA);
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		posaux = pos;
		app->task->AddTask(buttonD);

	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
	{
		posaux = pos;
		app->task->AddTask(buttonW);
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		posaux = pos;
		app->task->AddTask(buttonS);
	}
	
	return true;
}
```

## Conclusion
