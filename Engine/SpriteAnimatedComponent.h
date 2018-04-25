#pragma once
#include "IRenderableComponent.h"
#include "ISpriteComponent.h"

class SpriteAnimatedComponent : public IComponent, public ISpriteComponent
{
public:
	SpriteAnimatedComponent();
	SpriteAnimatedComponent(RECT *rect, Vec2 offset, string text, string name, string animation);

	~SpriteAnimatedComponent();

	void Draw(float deltaTime) override;

	std::string GetAnimation(); 
	void SetAnimation(std::string animation) { _animation = animation; };

private:
	std::string _animation;
};

