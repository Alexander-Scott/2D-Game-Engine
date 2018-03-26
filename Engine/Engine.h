#pragma once

#include "ISystem.h"
#include "Logger.h"

#include <chrono>

class MainWindow;

class Engine
{
public:
	Engine();
	Engine(HWND hWnd);
	Engine(HINSTANCE hInst, wchar_t * pArgs);
	~Engine();

	void StartUpdateLoop();

	std::shared_ptr<ISystem> GetSystem(SystemType type);

protected:
	void Initalise();

	void InitaliseSystems();
	void InitaliseListeners();
	void SystemsInitalised();

	bool UpdateLoop();

	std::shared_ptr<SystemMessageDispatcher>			_messageDispatcher;

	std::shared_ptr<MainWindow>							_mainWindow;
	std::map<SystemType,std::shared_ptr<ISystem>>		_systems;

	float												_deltaTime;
	std::chrono::steady_clock::time_point				_lastTime;
};