#include "MCharacterComponent.h"



MCharacterComponent::MCharacterComponent() : IComponent("MCharacterComponent")
{
	//_transformComponent = nullptr;
	//_rigidBodyComponent = nullptr;
	_goesBot = false;
	_goesTop = false;
	_goesLeft = false;
	_goesRight = false;
}


MCharacterComponent::~MCharacterComponent()
{
}

void MCharacterComponent::Update(float deltaTime)
{
	if (_goesRight) {
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x+1.0f, _transformComponent->GetWorldPosition().y ));
	}
	if (_goesLeft) {
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x - 1.0f, _transformComponent->GetWorldPosition().y));
	}
	if (_goesTop) {
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x, _transformComponent->GetWorldPosition().y-1.0f));
	}
	if (_goesBot) {
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x, _transformComponent->GetWorldPosition().y + 1.0f));
	}
}

void MCharacterComponent::RecieveMessage(IComponentMessage & msg)
{
	switch (msg.MessageType) {
	case ComponentMessageType::eInputHandlerToGameObjectMessage:
	{
		InputHandlerToGameObjectMessage &msgHandler = static_cast<InputHandlerToGameObjectMessage&>(msg);
		ProcessInput(msgHandler.MessageType, msgHandler.Command, msgHandler.Range);
	}
	}
}

void MCharacterComponent::ProcessInput(InputGenericStateMessageType msgType, sCommand msgCommand, float msgRange)
{
	bool keyPressed;
	if (msgType == InputGenericStateMessageType::eKeyPressed) {
		keyPressed = true;
	}
	else
		keyPressed = false;

	switch (msgCommand._ID) {
	case 1: //W
	{
		_goesTop = keyPressed;
		_spriteAnimatedComponent->SetAnimation("WalkTop"); 
		break;
	}
	case 2://S
	{
		_goesBot = keyPressed;
		_spriteAnimatedComponent->SetAnimation("WalkBot");
		break;
	}
	case 3://A
	{
		_goesLeft = keyPressed;
		_spriteAnimatedComponent->SetAnimation("WalkLeft");
		break;
	}
	case 4://D
	{
		_goesRight = keyPressed;
		_spriteAnimatedComponent->SetAnimation("WalkRight");
		break;
	}
	}
}

