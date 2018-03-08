#include "InputHandler.h"

#include "InputKeyboardMessage.h"
#include "InputMouseMessage.h"
#include "ISystemToGameObjectMessage.h"

InputHandler::InputHandler(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	:ISystem(SystemType::eInputHandler, dispatcher)
{ 
	_gamePadP1 = std::make_unique<DirectX::GamePad>();
}

void InputHandler::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eInputKeyboardMessage);
	SubscribeToMessageType(SystemMessageType::eInputMouseMessage);
	SubscribeToMessageType(SystemMessageType::eInputUpdateGamePad);

	TestKeyboardInitialCommands();
	LoadKeyboardGameMapping();
}

void InputHandler::TestKeyboardInitialCommands() //to remove after I have a function to load commands list from a file at initialization
{
	MoveUpCommand* move_up = new MoveUpCommand();
	MoveLeftCommand* move_left = new MoveLeftCommand();
	MoveRightCommand* move_right = new MoveRightCommand();
	MoveDownCommand* move_down = new MoveDownCommand();

	_keyboardGameCommandMap['W'] = move_up;
	_keyboardGameCommandMap['A'] = move_left;
	_keyboardGameCommandMap['S'] = move_down;
	_keyboardGameCommandMap['D'] = move_right;
}

void InputHandler::LoadKeyboardGameMapping()
{
	_keyboardCurrentCommandMap = _keyboardGameCommandMap;
}
void InputHandler::RecieveMessage(ISystemMessage & message)
{
	switch (message.Type)
	{
		case SystemMessageType::eInputKeyboardMessage:
		{
			//TODO Input: Write code to handle keyboard messages
			InputKeyboardMessage& msg = static_cast<InputKeyboardMessage&>(message);
			if (_keyboardCurrentCommandMap[msg.Key] != nullptr)
			{
				SendMessageToScene(_keyboardCurrentCommandMap[msg.Key]->Execute());
			}
			break;
		}
		case SystemMessageType::eInputMouseMessage:
		{
			//TODO Input: Write code to handle mouse messages
			InputMouseMessage& msg = static_cast<InputMouseMessage&>(message);
		}
		case SystemMessageType::eInputUpdateGamePad:
		{
			_stateGamePadP1 = _gamePadP1->GetState(0);
		}
	}
}

// ISystemToGameObjectMessage must be initalised with an instance of IComponentMessage.
// IComponentMessage has a ComponentMessageType that you must set (such as eMoveForward, eMoveBackward)
// which specific GameObject components can listen for. The GameObject component must also 
// inherit IMessageableComponent.
void InputHandler::SendMessageToScene(ISystemToGameObjectMessage& message)
{
	SendMessageToDispatcher(message);
}
