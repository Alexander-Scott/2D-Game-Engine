#pragma once

class IDrawable
{
public:
	// Draw function must be overriden
	virtual void Draw() = 0;

	int			RenderLayer;
};