#include "GameEngine.h"


GameEngine::GameEngine():m_window(nullptr),m_screenWidth(1024),m_screenHeight(768), m_gameState(GameState::PLAY),m_time(0)
{
}


GameEngine::~GameEngine()
{
}

void GameEngine::run()
{
	initSystems();

	m_sprite.init({-1,-1},2,2);

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

	initShaders();

}

void GameEngine::gameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		processInput();

		m_time += 0.01;

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

	m_colorProgram.use();

	GLuint timeLocation = m_colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation,m_time);

	m_sprite.draw();

	m_colorProgram.unUse();

	SDL_GL_SwapWindow(m_window);
}

void GameEngine::initShaders()
{
	m_colorProgram.compileshaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_colorProgram.addAttribute("vertexPosition");
	m_colorProgram.addAttribute("vertexColor"); 
	m_colorProgram.linkShaders();
}
