#include "AControllerComponent.h"

#include "InputHandlerToGameObjectMessage.h"
#include "AddForceMessage.h"
#include "SetVelocityMessage.h"
#include "CollisionMessage.h"

AControllerComponent::AControllerComponent() : IComponent("AControllerComponent")
{
	_leftPressed = false;
	_rightPressed = false;
	_upPressed = false;
	_downPressed = false;
	_previousBounceTimer = 0;
}

AControllerComponent::~AControllerComponent()
{
}

void AControllerComponent::Update(float deltaTime)
{
	Vec2 force = Vec2(0.0f, 0.0f);

	if (_upPressed)
	{
		force.y += 1;
	}
	if (_downPressed)
	{
		force.y -= 1;
	}
	if (_leftPressed)
	{
		force.x -= 1;
	}
	if (_rightPressed)
	{
		force.x += 1;
	}

	if (force.x != 0 || force.y != 0)
	{
		AddForceMessage addForceMsg(force, 1000000);
		_rigidbody->RecieveMessage(addForceMsg);
	}

	_previousBounceTimer += deltaTime;
}

void AControllerComponent::RecieveMessage(IComponentMessage & message)
{
	switch (message.MessageType)
	{
		case ComponentMessageType::eInputHandlerToGameObjectMessage:
		{
			InputHandlerToGameObjectMessage& msg = static_cast<InputHandlerToGameObjectMessage&>(message);
			ProcessCommand(msg.MessageType, msg.Command, msg.Range);
			break;
		}

		case ComponentMessageType::eCollisionMessage:
		{
			// This prevents any double jumps
			if (_previousBounceTimer < 0.1f)
				return;

			// This only allows jumps to happen if the player is falling downward
			if (_rigidbody->GetVelocity().y < -1.0f)
				return;

			CollisionMessage& msg = static_cast<CollisionMessage&>(message);
			if (msg.CollidedObjectTag == "Platform")
			{
				Vec2 velocity = Vec2(_rigidbody->GetVelocity().x, -JUMP_VELOCITY);
				SetVelocityMessage setVelMsg(velocity);
				_rigidbody->RecieveMessage(setVelMsg);

				_audioSource->PlayAudioFile("Bounce");

				_previousBounceTimer = 0;
			}
			break;
		}
	}
}

void AControllerComponent::ProcessCommand(InputGenericStateMessageType type, sCommand command, float range)
{
	/*
	<Command key="A" name="move_left" ID="3"/>
	<Command key="D" name="move_right" ID="4"/>
	<Command key="S" name="move_down" ID="2"/>
	<Command key="W" name="move_up" ID="1"/>
	*/

	bool setValue;

	if (type == InputGenericStateMessageType::eKeyPressed)
	{
		setValue = true;
	}
	else
	{
		setValue = false;
	}

	switch (command._ID)
	{
		case 1: // UP
		{
			_upPressed = setValue;
			break;
		}
		case 2: // DOWN
		{
			_downPressed = setValue;
			break;
		}
		case 3: // LEFT
		{
			_leftPressed = setValue;
			break;
		}
		case 4: // RIGHT
		{
			_rightPressed = setValue;
			break;
		}
	}
}
