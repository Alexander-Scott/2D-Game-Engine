#pragma once

#include "ISystem.h"
#include "TestCommand.h"
#include "DirectXTK\Inc\GamePad.h"
#include "Logger.h"
#include "rapidxml_print.hpp"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class ISystemToGameObjectMessage;

class InputHandler : public ISystem
{
public:
	InputHandler(std::shared_ptr<SystemMessageDispatcher> dispatcher);

	void InitaliseListeners() override;
	void LoadKeyboardGameMapping();
	void LoadGamePadGameMapping();
	void RecieveMessage(ISystemMessage& message) override;

	void SwapCommands(std::vector<unsigned char>& rebindQueue);

	void SendGamePadButtonState(DirectX::GamePad::ButtonStateTracker & buttonState,
		DirectX::GamePad::ButtonStateTracker::ButtonState enumState);
	void SendGamePadAnalogStickState(DirectX::GamePad::State & state);
	void SendGamePadAnalogTriggerState(DirectX::GamePad::State & state);
	void SendGamePadNeutralState();

	void AddMapToVectorOfCommands();
	void SaveMapsInput();
	void LoadMapFromXMLFile(std::string fileName);

	void SendMessageToScene(ISystemToGameObjectMessage& message);
private:
	std::string _listOfAvailableGamepadButtons[18] =
	{ "A","B","X","Y","BACK","START","LEFT_STICK_CLICK","RIGHT_STICK_CLICK","LEFT_BUMPER", "RIGHT_BUMPER",
		"DPAD_UP","DPAD_DOWN","DPAD_LEFT", "DPAD_RIGHT",
		"LEFT_TRIGGER", "RIGHT_TRIGGER", "LEFT_STICK_ANALOG", "RIGHT_STICK_ANALOG"};
	std::unique_ptr <DirectX::GamePad> _gamePadP1;
	DirectX::GamePad::State _stateGamePadP1;
	bool _connectedGamePadP1;
	DirectX::GamePad::ButtonStateTracker _buttonStateTrackerP1;

	bool _bKeyboardSwapCommands;
	bool _debugSwap = true; 
	//std::map <unsigned char, ICommand*> _keyboardCurrentCommandMap;
	//std::map <unsigned char, ICommand*> _keyboardGameCommandMap;
	map <unsigned char, sCommand> _keyboardCurrentCommandMap;
	vector< std::map <unsigned char, sCommand> > _keyboardListOfCommandMap;
	map < std::string, sCommand > _gamePadCurrentCommandMap;
	vector< std::map <std::string, sCommand> > _gamePadListOfCommandMap;
	//holds which map in the vector is active
	int _keyboardCurrentActivatedMap;
	int _gamePadCurrentActivatedMap;

	vector<unsigned char> _rebindKeyboardQueue;
};

