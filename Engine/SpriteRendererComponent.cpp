#include "SpriteRendererComponent.h"


SpriteRendererComponent::SpriteRendererComponent() : IComponent("SpriteRendererComponent")
{
}

SpriteRendererComponent::SpriteRendererComponent(RECT *rect, Vec2 offset, string name) : IComponent("SpriteRendererComponent")
{
	Type = eSprite;
	//SetPosition(position);
	//SetRotation(rotation);
	//SetScale(scale);

	SetRect(rect);
	SetOffset(offset);
	_name = name;
}

SpriteRendererComponent::~SpriteRendererComponent()
{
}

void SpriteRendererComponent::SetDependencies(TransformComponent * transform)
{
	_transformComponent = transform;
}

//Draw : passes data to the message sent to draw function in Graphics System
void SpriteRendererComponent::Draw(float deltaTime)
{
	//TODO
}

void SpriteRendererComponent::SetName(std::string name)
{
	_name = name;
}

std::string SpriteRendererComponent::GetName()
{
	return _name;
}
