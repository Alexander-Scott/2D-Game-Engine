#pragma once

#include <chrono>

#include "ISystem.h"

using namespace std;

class Engine : public ISystem
{
public:
	Engine();
	Engine(int width, int height);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void RecieveMessage(ISystemMessage& message) override;
	void InitaliseListeners() override;
	void SystemsInitalised() override;

	~Engine();

private:
	void UpdateEngine();

	float									_lag;
	std::chrono::steady_clock::time_point	_lastTime;
};