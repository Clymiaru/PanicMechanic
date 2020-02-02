#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  
#include "Game.h"
#include <random>
int main()
{
	std::srand(std::time(nullptr));
	auto game = CreateScope<Game>();
	game->Run();
	return 0;
}