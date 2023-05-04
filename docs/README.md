# TASK QUEUE: Project Research

## Introduction
Tasks refer to work that may take a long time to complete and can be processed asynchronously. Waiting until a task completes before proceeding with the game is not feasible. To manage these tasks effectively, a Task Queue is utilized, where all the tasks are added and executed in the background. There are two types of Task Queues available: Push Queues and Pull Queues. Push Queues automatically handle the actions that are added to them, whereas Pull Queues contain a list of actions that can be executed at any time.

For instance, Push Queues are useful in messaging systems such as WhatsApp. One can continue to send messages even if the previously sent messages have not been delivered yet. In video games, Push Queues are often used to handle events that happen in real time. For example, in a racing game, events that occur on the track, such as the collision of two cars, can be automatically added to a background task queue to be processed in the order they occurred.

On the other hand, Pull Queues are typically used in RPG games where a character is assigned tasks, and the game processes them in a sequential order. For example, in a real-time strategy game, the player may give specific orders to a group of units, and these orders are added to a task queue that is executed in the order they were received.

## Task Queue in videogames
A great way to learn how to use task queues in video games is by observing how other games have implemented them. Here are some examples of task queues that are easy to identify at first glance.

### Age of Empires
In games like Age of Empires, constructing a building takes time and resources. The game adds the construction task to a queue and processes it in the background while allowing the player to continue managing their empire.

![(https://github.com/PauM4/TaskQueue/blob/main/docs/images/AG_II.jpeg)]([https://youtu.be/wtOxx2zixrQ](https://youtu.be/wtOxx2zixrQ?t=3990))
*Gameplay no commentary - Age of Empires II, Definitive Edition (2019)*

### World of Warcraft
In games with RPG mechanics, players can use powerful abilities that have a cooldown period before they can be used again. These abilities are added to a task queue and cannot be used again until the cooldown has completed.
Also, completing a quest involves multiple steps and requires the player to interact with various NPCs or objects. The game uses a task queue to manage the quest progression and ensure that the player completes each step in the correct order.

[![](https://github.com/PauM4/TaskQueue/blob/main/docs/images/WOW.jpg)]([https://youtu.be/Qce3IqbTiJM](https://youtu.be/Qce3IqbTiJM?t=4099))
*Battle for Azeroth - World of Warcraft (2004)*

### Civilitzation
In games like Civilization, combat is turn-based, meaning that each player or character takes turns making moves. The game uses a task queue to manage the turn order and ensure that each player or character gets their turn in the correct order.

[![](https://github.com/PauM4/TaskQueue/blob/main/docs/images/CV_VI.jpg)]([https://youtu.be/0geOdVTDBFk](https://youtu.be/0geOdVTDBFk?t=5092))
*Gameplay no commentary - Civilization VI (2016)*

## Command Pattern
In order to implement task queues, we utilize what is known as the command pattern. According to the book "Game Programming Patterns", "commands are an object-oriented replacement for callbacks". By treating tasks as objects rather than functions, we can apply the command pattern to redefine keys and change the actor of the action.

To apply the command pattern, you typically define a Command interface or abstract class that specifies a method for executing the command. You then create concrete command classes that implement the Command interface and encapsulate a specific request or action. The command objects are usually created by a client and passed to an invoker object, which maintains a queue of commands and executes them in order.

In video games, the command pattern can be used to implement task queues, as mentioned earlier. By treating tasks as objects and encapsulating them within command objects, you can easily add them to a task queue and execute them in the background, while allowing the player to continue interacting with the game world. This approach enables you to create complex gameplay mechanics that can be managed seamlessly and efficiently, without disrupting the player's experience.

## Selected approach

For my Task Queue research, I have chosen to focus on the combat of RPG games. In this type of combat, the task queue or the task manager is very useful due to the fact that multiple actions are performed in one turn and these must be ordered and executed in a certain way.

In simple turn-based RPGs, the order in which the different abilities and attacks will be executed has to be organized. On the other hand, in tactical RPGs, the possibility of choosing where to move our character is added. All this added up, makes the task queue or task manager essential for the combat to develop correctly.

[![](https://github.com/PauM4/TaskQueue/blob/main/docs/images/GS_II.jpg)](https://youtu.be/rn34B4XhJ4I)
*Battle against Dullahan - Golden Sun 2 (2002)*

## Exercise

For this practical part we will learn how to implement a simple task manager and the basic commands to make a player move after indicate him what moves to make.

### TODO 0 - TaskManager.h

In this first TODO what we will do will be to understand how this new Task Manager module called Task is built. Like every module inherited from Module, it has its constructor and its update and cleanup functions. In addition, it will have a function that will allow us to add tasks to the task queue and another to execute them.

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

### TODO 1 - TaskManager.h

To be able to save all the tasks, we create a list of the Task class. In this we will be adding all the tasks so that later, when we call the function to execute them, we will know where we saved them.

```
private:
	//TODO 1 Create a queue of tasks
	std::queue<Task*> TaskQueue;
```

### TODO 2 - TaskManager.h

In this section, what we will do is declare a class for each of the tasks we want in our video game.

For this case, we will declare a class for each of the directions in which the player can move, that is, four in total. These classes will have their constructor and a function to execute them, to which we will pass the "actor" on which they have to be performed, in our case the player.

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

### TODO 3 - Player.h

In TODO 3 our goal is to create the number of tasks we will need for our game. In this exercise, we will create 4 for each of the directions, which will be added to the task queue by pressing the keys W, A, S, and D.

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

### TODO 4 - TaskManager.cpp

Once we have declared and created the 4 functions that we will use, it's time to define what they do. In our case, we will code how will move. That is, for how long it should move and at what speed.

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

### TODO 5 - TaskManager.cpp

In this section, we will define when the task queue is executed. In our case, it will be executed when the spacebar is pressed. When it's pressed, we will check if the aux_task is null (this stores the task at the front of the queue). If it's not null and the queue is not empty, we will start emptying the queue as tasks are executed.

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

### TODO 6 - TaskManager.cpp

For TODO 6, our goal is to define how the AddTask function works. In this case, we will simply make sure that every time it's called, a push is made to the task list with the new task to be added.

```
bool Task::AddTask(Task * task)
{
	//TODO 6 Add the new task to the list
	TaskQueue.push(task);

	return true;
}
```

### TODO 7 - TaskManager.cpp

For this section, we will define how the DoTask function works, which will be responsible for executing the tasks. This function checks the "actor" that we have passed to it and begins to execute the tasks it has stored. At the same time, during execution, it also removes the tasks that have already been completed from the queue.

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

### TODO 8 - Player.cpp

We initialize the different tasks that we will use and that we have previously declared in TODO 2.

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

### TODO 9 - Player.cpp

For TODO 9, as in all classes, we must not forget to delete the tasks that we created in the start function in the cleanup function, in this case, in the player module.

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

### TODO 10 - Player.cpp

Finally, for our new TaskManager module to work, we will define when tasks should be added to the task queue. In our case, each of the keys we defined earlier corresponds to one of the four movements the player can make.

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

The Task Queue or Task Manager are very useful tools for controlling the various actions that can happen simultaneously or not in a video game. Also, the fact that these tasks can be developed asynchronously provides even more freedom.

Therefore, all in all, these tools provide endless possibilities for developing your video game.

In our case, for RPG games, we can get the most out of this utility. On the one hand, we can apply it to combat; how turns are managed, the order of skills and attacks... Also outside of combat, to manage missions or actions that the player can perform.

Finally, the Task Queue or Task Manager are very simple tools that can become more complex as we give them more uses or complement them with other mechanisms such as the Command Pattern.

## Relevant Links

![Command [Wiki]. Code Programming Patterns](http://gameprogrammingpatterns.com/command.html)
![Command in C++, Designs Patterns [Wiki]. Source Making](https://sourcemaking.com/design_patterns/command/cpp/2)
![Patrón COMMAND [Vídeo]. YouTube, The power ups - Learning](https://youtu.be/rtAz08XfTz0)
![What You Need To Know About The COMMAND PATTERN [Vídeo]. YouTube, BMo](https://youtu.be/mSZuEbAkJCo)
![How to Program in Unity: Command Pattern Explained [Vídeo]. YouTube, iHeartGameDev](https://youtu.be/oLRINAn0cuw)
