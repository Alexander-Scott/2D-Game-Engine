#include "InputHandler.h"

#include "InputKeyboardMessage.h"
#include "InputMouseMessage.h"

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

	MoveUpCommand* move_up = new MoveUpCommand();
	_keyboardCommands['Z'] = move_up;
}

void InputHandler::RecieveMessage(ISystemMessage & message)
{
	switch (message.Type)
	{
		case SystemMessageType::eInputKeyboardMessage:
		{
			//TODO Input: Write code to handle keyboard messages
			InputKeyboardMessage& msg = static_cast<InputKeyboardMessage&>(message);
			if (_keyboardCommands[msg.Key] != nullptr)
			{
				_keyboardCommands[msg.Key]->Execute();
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
