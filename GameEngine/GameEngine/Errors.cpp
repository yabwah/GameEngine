#include "Errors.h"


void fatalError(std::string a_err)
{
	std::cout << a_err << std::endl;

	//cleanup
	SDL_Quit();
	system("pause");

}