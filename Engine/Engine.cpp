#include "pch.h"
#include "Engine.h"
#include <iostream>
namespace EngineGame
{
	Engine::Engine() {}
	void Engine::Initialize()
	{
		std::cout << "Engine initialize" << std::endl;
	}
	void Engine::Run()
	{
		std::cout << "Engine run" << std::endl;
	}
}