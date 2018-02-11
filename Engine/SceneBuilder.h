#pragma once

#include "IScene.h"

#include "ISystem.h"
#include "SystemMessageDispatcher.h"

class SceneBuilder : public ISystem
{
public:
	SceneBuilder();

	void RecieveMessage(ISystemMessage& message) override;

private:
	shared_ptr<IScene> BuildScene();
};