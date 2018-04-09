#pragma once

#include "ISystem.h"
#include "AudioSoundFileManager.h"

#include "DirectXTK\Inc\Audio.h"

class AudioSystem : public ISystem
{
public:
	AudioSystem(std::shared_ptr<SystemMessageDispatcher> dispatcher);
	~AudioSystem();

	void InitaliseListeners() override;
	void RecieveMessage(ISystemMessage& message) override;

private:
	void PlaySoundEffect(std::string fileName);
	void Suspend();
	void Resume();

	std::unique_ptr<AudioSoundFileManager>		_audioFileManager;
	std::shared_ptr<DirectX::AudioEngine>		_audioEngine;
	bool										_retryAudio;
};

