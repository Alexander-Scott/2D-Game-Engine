#include "ComponentBuilder.h"

xml_node<>* _node;

// Define component functions here
inline IComponent * BuildTransformComponent();
inline IComponent * BuildSpriteRendererComponent();
inline IComponent * BuildTextRendererComponent();


// List component functions against string types found in the XML files
ComponentBuilder::ComponentBuilder()
{
	functionMapper.Insert("TransformComponent", BuildTransformComponent);
	functionMapper.Insert("TextRendererComponent", BuildTextRendererComponent);
	functionMapper.Insert("SpriteRendererComponent", BuildSpriteRendererComponent);
}

IComponent * ComponentBuilder::BuildComponent(xml_node<>* node)
{
	_node = node;

	// Call the function listed in the function mapper
	return functionMapper.CallFunction<IComponent*>(string(node->first_attribute("type")->value()));
}

//TODO : delete when sure that we don't use it anymore - we should only be using TextRendererComponent or SpriteRendererComponent
IComponent * BuildTransformComponent()
{
	float xPos = (float)atof(_node->first_attribute("xpos")->value());
	float yPos = -(float)atof(_node->first_attribute("ypos")->value());
	float rot = (float)atof(_node->first_attribute("rotation")->value());
	float scale = (float)atof(_node->first_attribute("scale")->value());

	return ComponentFactory::MakeTransformComponent(Vec2(xPos, yPos), rot, scale);
}
//END - TODO

IComponent * BuildSpriteRendererComponent()
{
	float xPos = (float)atof(_node->first_attribute("xpos")->value());
	float yPos = -(float)atof(_node->first_attribute("ypos")->value());
	float rot = (float)atof(_node->first_attribute("rotation")->value());
	float scale = (float)atof(_node->first_attribute("scale")->value());

	LONG rectTop = (LONG)atof(_node->first_attribute("rectTop")->value());
	LONG rectBottom = (LONG)atof(_node->first_attribute("rectBottom")->value());
	LONG rectLeft = (LONG)atof(_node->first_attribute("rectLeft")->value());
	LONG rectRight = (LONG)atof(_node->first_attribute("rectRight")->value());

	float offset1 = (float)atof(_node->first_attribute("offset1")->value());
	float offset2 = (float)atof(_node->first_attribute("offset2")->value());

	RECT *rect = new RECT(); rect->top = rectTop; rect->left = rectLeft; rect->right = rectRight; rect->bottom = rectBottom;
	Vec2 offset = Vec2(offset1, offset2);
	
	std::string text = (std::string)(_node->first_attribute("text")->value()); //path to texture "file"
	std::string name = (std::string)(_node->first_attribute("name")->value()); //name of the object (ex : PlayerGreen,etc.)
	std::string animation = (std::string)(_node->first_attribute("animation")->value()); //name of animation (ex : walk, crawl, etc)

	return ComponentFactory::MakeSpriteRendererComponent(Vec2(xPos, yPos), rot, scale, rect, offset, text, name, animation);
}

IComponent * BuildTextRendererComponent()
{
	float xPos = (float)atof(_node->first_attribute("xpos")->value());
	float yPos = -(float)atof(_node->first_attribute("ypos")->value());
	float rot = (float)atof(_node->first_attribute("rotation")->value());
	float scale = (float)atof(_node->first_attribute("scale")->value());

	LONG rectTop = (LONG)atof(_node->first_attribute("rectTop")->value());
	LONG rectBottom = (LONG)atof(_node->first_attribute("rectBottom")->value());
	LONG rectLeft = (LONG)atof(_node->first_attribute("rectLeft")->value());
	LONG rectRight = (LONG)atof(_node->first_attribute("rectRight")->value());
	
	float offset1 = (float)atof(_node->first_attribute("offset1")->value());
	float offset2 = (float)atof(_node->first_attribute("offset2")->value());

	std::string text = (std::string)(_node->first_attribute("text")->value());
	RECT *rect = new RECT(); rect->top = rectTop; rect->left = rectLeft; rect->right = rectRight; rect->bottom = rectBottom; 
	Vec2 offset = Vec2(offset1, offset2); 
	
	float rgb1 = (float)atof(_node->first_attribute("rgb1")->value());
	float rgb2 = (float)atof(_node->first_attribute("rgb2")->value());
	float rgb3 = (float)atof(_node->first_attribute("rgb3")->value());
	float rgb4 = (float)atof(_node->first_attribute("rgb4")->value());

	float4 *_rgb3 = new float4(rgb1, rgb2, rgb3, rgb4);

	return ComponentFactory::MakeTextRendererComponent(Vec2(xPos, yPos), rot, scale, rect, offset, text, _rgb3);
}
