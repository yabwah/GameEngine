#pragma once
#include<Windows.h>
#include<iostream>
#include <SDL/SDL.h>
#include<GL/glew.h>
#include<string>

#include "Sprite.h"


enum class GameState{PLAY,EXIT};

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	void run();


private:
	SDL_Window * m_window;
	int m_screenWidth;
	int m_screenHeight;
	GameState m_gameState;

	Sprite m_sprite;

	void initSystems();
	void gameLoop();
	void processInput();
	void drawGame();
};

