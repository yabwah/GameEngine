#include "GameEngine.h"


void fatalError(std::string a_err)
{
	std::cout << a_err << std::endl;

	//cleanup
	SDL_Quit();
	system("pause");

}
GameEngine::GameEngine():m_window(nullptr),m_screenWidth(1024),m_screenHeight(768), m_gameState(GameState::PLAY)
{
}


GameEngine::~GameEngine()
{
}

void GameEngine::run()
{
	initSystems();

	gameLoop();
}

void GameEngine::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL);

	if (m_window == nullptr)
	{
		fatalError("SDL window could not be created!");
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);

	if (glContext == nullptr)
	{
		fatalError("GL Context could not be created!");
	}

	GLenum glEnum = glewInit();

	if (glEnum != GLEW_OK)
	{
		fatalError("GLEW could not be initialized!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

}

void GameEngine::gameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}

}

void GameEngine::processInput()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION:
			std::cout << sdlEvent.motion.x << " " << sdlEvent.motion.y << std::endl;
			break;
		}
	}

}

void GameEngine::drawGame()
{

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);

	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 500.0f);
	glVertex2f(500.0f, 500.0f);

	glEnd();



	SDL_GL_SwapWindow(m_window);
}
