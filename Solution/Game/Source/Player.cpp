#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "TaskManager.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"

#include <iostream>

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() {

}

bool Player::Awake() {

	pos.x = parameters.attribute("x").as_int();
	pos.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Player::Start() {

	//initilize textures
	speed.x = 2;
	speed.y = 2;
	texture = app->tex->Load(texturePath);

	buttonD = new MoveRight;
	buttonA = new MoveLeft;
	buttonW = new MoveForward;
	buttonS = new MoveBackWard;
	return true;
}

bool Player::Update()
{
	Movement();
	app->render->DrawTexture(texture, pos.x, pos.y);

	return true;
}

bool Player::CleanUp()
{
	//TODO 4 Remember to delete the new Tasks
	delete buttonD;
	delete buttonA;
	delete buttonW;
	delete buttonS;
	return true;
}

bool Player::Movement()
{
	//TODO 4 Add the task to the queque 
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