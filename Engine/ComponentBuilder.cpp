#include "ComponentBuilder.h"
#include "Scene.h"

xml_node<>* _node;
shared_ptr<Scene> _scene;

map<string, GUID>* depdendecies;
IComponent * dependencyComponent;

#pragma region Core component function declarations

inline IComponent * BuildTransformComponent();

inline IComponent * BuildSpriteRendererComponent();
inline void FetchSpriteRendererDependencies();

inline IComponent * BuildSpriteAnimatedComponent();
inline void FetchSpriteAnimatedDependencies();

inline IComponent * BuildTextRendererComponent();
inline void FetchTextRendererDependencies();

inline IComponent * BuildRigidbodyComponent();

inline IComponent * BuildCircleColliderComponent();
inline void FetchCircleColliderDependencies();

inline IComponent * BuildBoxColliderComponent();
inline void FetchBoxColliderDependencies();

inline IComponent * BuildAudioSourceComponent();

#pragma endregion

#pragma region AlexGame component function declarations

inline IComponent * BuildAlexController();
inline void FetchAlexControllerDependencies();

inline IComponent * BuildAlexPlatformManager();
inline void FetchAlexPlatformManagerDependencies();

inline IComponent * BuildAlexGameManager();
inline void FetchAlexGameManagerDependencies();

#pragma endregion

#pragma region MGame inline methods

inline IComponent * BuildMCharacterComponent();
inline void FetchMCharacterDependencies();

inline IComponent * BuildMBackgroundComponent();
inline void FetchMBackgroundDependencies();

inline IComponent * BuildMPhantomComponent();
inline void FetchMPhantomDependencies();

inline IComponent * BuildMChestComponent();
inline void FetchMChestDependencies();

inline IComponent * BuildMIntroComponent();
inline void FetchMIntroDependencies();

#pragma endregion

ComponentBuilder::ComponentBuilder(shared_ptr<Scene> scene)
{
	_scene = scene;

#pragma region Core component function mapping

	_buildMapper.Insert("TransformComponent", BuildTransformComponent);

	_buildMapper.Insert("SpriteRendererComponent", BuildSpriteRendererComponent);
	_dependencyBuildMapper.Insert("SpriteRendererComponent", FetchSpriteRendererDependencies);

	_buildMapper.Insert("SpriteAnimatedComponent", BuildSpriteAnimatedComponent);
	_dependencyBuildMapper.Insert("SpriteAnimatedComponent", FetchSpriteAnimatedDependencies);

	_buildMapper.Insert("TextRendererComponent", BuildTextRendererComponent);
	_dependencyBuildMapper.Insert("TextRendererComponent", FetchTextRendererDependencies);

	_buildMapper.Insert("RigidbodyComponent", BuildRigidbodyComponent);

	_buildMapper.Insert("CircleColliderComponent", BuildCircleColliderComponent);
	_dependencyBuildMapper.Insert("CircleColliderComponent", FetchCircleColliderDependencies);

	_buildMapper.Insert("BoxColliderComponent", BuildBoxColliderComponent);
	_dependencyBuildMapper.Insert("BoxColliderComponent", FetchBoxColliderDependencies);

	_buildMapper.Insert("AudioSourceComponent", BuildAudioSourceComponent);

#pragma endregion

#pragma region AlexGame component function mapping

	_buildMapper.Insert("AControllerComponent", BuildAlexController);
	_dependencyBuildMapper.Insert("AControllerComponent", FetchAlexControllerDependencies);

	_buildMapper.Insert("APlatformManagerComponent", BuildAlexPlatformManager);
	_dependencyBuildMapper.Insert("APlatformManagerComponent", FetchAlexPlatformManagerDependencies);

	_buildMapper.Insert("AGameManagerComponent", BuildAlexGameManager);
	_dependencyBuildMapper.Insert("AGameManagerComponent", FetchAlexGameManagerDependencies);

#pragma endregion	

#pragma region MGame 

	_buildMapper.Insert("MCharacterComponent", BuildMCharacterComponent);
	_dependencyBuildMapper.Insert("MCharacterComponent", FetchMCharacterDependencies);

	_buildMapper.Insert("MBackgroundComponent", BuildMBackgroundComponent);
	_dependencyBuildMapper.Insert("MBackgroundComponent", FetchMBackgroundDependencies);

	_buildMapper.Insert("MPhantomComponent", BuildMPhantomComponent);
	_dependencyBuildMapper.Insert("MPhantomComponent", FetchMPhantomDependencies);

	_buildMapper.Insert("MChestComponent", BuildMChestComponent);
	_dependencyBuildMapper.Insert("MChestComponent", FetchMChestDependencies);

	_buildMapper.Insert("MIntroComponent", BuildMIntroComponent);
	_dependencyBuildMapper.Insert("MIntroComponent", FetchMIntroDependencies);

#pragma endregion	

}

#pragma region Core component functions

IComponent * ComponentBuilder::BuildComponent(xml_node<>* node)
{
	_node = node;

	// Call the function listed in the function mapper
	return _buildMapper.CallFunction<IComponent*>(string(node->first_attribute("type")->value()));
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

inline IComponent * BuildSpriteRendererComponent()
{
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
	//std::string animation = (std::string)(_node->first_attribute("animation")->value()); //name of animation (ex : walk, crawl, etc)

	return ComponentFactory::MakeSpriteRendererComponent(rect, offset, text, name);
}

inline IComponent * BuildSpriteAnimatedComponent()
{
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

	return ComponentFactory::MakeSpriteAnimatedComponent(rect, offset, text, name, animation);
}

IComponent * BuildTextRendererComponent()
{
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

	return ComponentFactory::MakeTextRendererComponent(rect, offset, text, _rgb3);
}

IComponent * BuildRigidbodyComponent()
{
	float staticF = (float)atof(_node->first_attribute("staticfriction")->value());
	float dynamicF = (float)atof(_node->first_attribute("dynamicfriction")->value());
	float restitution = (float)atof(_node->first_attribute("restitution")->value());
	float density = (float)atof(_node->first_attribute("density")->value());

	bool isStatic = false;
	if (bool(atoi(_node->first_attribute("static")->value())))
		isStatic = true;

	bool lockRotation = false;
	if (bool(atoi(_node->first_attribute("lockrotation")->value())))
		lockRotation = true;

	bool isKinematic = false;
	if (bool(atoi(_node->first_attribute("kinematic")->value())))
		isKinematic = true;

	return ComponentFactory::MakeRigidbodyComponent(staticF, dynamicF, restitution, density, isStatic, lockRotation, isKinematic);
}

IComponent * BuildCircleColliderComponent()
{
	float radius = (float)atof(_node->first_attribute("radius")->value());

	return ComponentFactory::MakeCircleColliderComponent(radius);
}

IComponent * BuildBoxColliderComponent()
{
	float width = (float)atof(_node->first_attribute("width")->value());
	float height = (float)atof(_node->first_attribute("height")->value());

	return ComponentFactory::MakeBoxCollider(width, height);
}

inline IComponent * BuildAudioSourceComponent()
{
	return ComponentFactory::MakeAudioSourceComponent();
}

void ComponentBuilder::BuildComponentDependecies(IComponent * component, map<string, GUID>* dependecies)
{
	depdendecies = dependecies;
	dependencyComponent = component;

	// Call the function listed in the function mapper
	_dependencyBuildMapper.CallFunction<void>(component->GetType());
}

void FetchCircleColliderDependencies()
{
	CircleColliderComponent* collider = static_cast<CircleColliderComponent*>(dependencyComponent);

	TransformComponent* transform;
	RigidBodyComponent* rigidbody;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
		}
		else if (it->first == "rigidbodycomponent")
		{
			rigidbody = _scene->GetGameObject(it->second)->GetComponent<RigidBodyComponent>();
		}
	}

	collider->SetDependencies(transform, rigidbody);
}

void FetchBoxColliderDependencies()
{
	BoxColliderComponent* collider = static_cast<BoxColliderComponent*>(dependencyComponent);

	TransformComponent* transform;
	RigidBodyComponent* rigidbody;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
		}
		else if (it->first == "rigidbodycomponent")
		{
			rigidbody = _scene->GetGameObject(it->second)->GetComponent<RigidBodyComponent>();
		}
	}

	collider->SetDependencies(transform, rigidbody);
}

void FetchSpriteRendererDependencies()
{
	SpriteRendererComponent* renderer = static_cast<SpriteRendererComponent*>(dependencyComponent);
	TransformComponent* transform;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
			break;
		}
	}

	renderer->SetDependencies(transform);
}

void FetchSpriteAnimatedDependencies()
{
	SpriteAnimatedComponent* renderer = static_cast<SpriteAnimatedComponent*>(dependencyComponent);
	TransformComponent* transform;
	SpriteAnimatedComponent *spriteanimatedcomponent;
	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
			break;
		}
		if (it->first == "spriteanimatedcomponent")
		{
			spriteanimatedcomponent = _scene->GetGameObject(it->second)->GetComponent<SpriteAnimatedComponent>(); 
			break;
		}

	}

	renderer->SetDependencies(transform);
}

inline void FetchTextRendererDependencies()
{
	TextRendererComponent* renderer = static_cast<TextRendererComponent*>(dependencyComponent);
	TransformComponent* transform;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
			break;
		}
	}

	renderer->SetDependencies(transform);
}

#pragma endregion

#pragma region AlexGame component functions

IComponent * BuildAlexController()
{
	return ComponentFactory::MakeAlexControllerComponent();
}

void FetchAlexControllerDependencies()
{
	AControllerComponent* alexController = static_cast<AControllerComponent*>(dependencyComponent);
	TransformComponent* transform;
	RigidBodyComponent* rigidbody;
	AudioSourceComponent* audioSource;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
		}
		else if (it->first == "rigidbodycomponent")
		{
			rigidbody = _scene->GetGameObject(it->second)->GetComponent<RigidBodyComponent>();
		}
		else if (it->first == "audiosourcecomponent")
		{
			audioSource = _scene->GetGameObject(it->second)->GetComponent<AudioSourceComponent>();
		}
	}

	alexController->SetDependencies(transform, rigidbody, audioSource);
}

inline IComponent * BuildAlexPlatformManager()
{
	int platformCount = atoi(_node->first_attribute("platformcount")->value());
	std::string platformTag = string(_node->first_attribute("platformtag")->value());
	std::string parentGameObjectID = string(_node->first_attribute("parentgameobjectid")->value());

	vector<shared_ptr<GameObject>> platforms;
	for (int i = 0; i < platformCount; i++)
	{
		auto platformGO = GameObject::MakeGameObject(platformTag);

		TransformComponent* platformTrans = ComponentFactory::MakeTransformComponent(Vec2(0, 0), 0, 1.2f);
		platformGO->AddComponent(platformTrans);

		RigidBodyComponent* platformRB = ComponentFactory::MakeRigidbodyComponent(0.5f, 0.3f, 0.5f, 1, true, false, true);
		platformGO->AddComponent(platformRB);

		BoxColliderComponent* platformCollider = ComponentFactory::MakeBoxCollider(50, 20);
		platformCollider->SetDependencies(platformTrans, platformRB);
		platformGO->AddComponent(platformCollider);

		RECT* rect = new RECT();
		rect->left = 0; rect->right = 64; rect->top = 0; rect->bottom = 20;
		SpriteRendererComponent* platformRenderer = ComponentFactory::MakeSpriteRendererComponent(rect, Vec2(0, 0), "/Sprites/AlexGame/Platform.dds", "PlayerGreen");
		platformRenderer->SetDependencies(platformTrans);
		platformGO->AddComponent(platformRenderer);

		platformGO->SetParent(_scene->GetGameObject(ComponentBuilder::StringToGUID(parentGameObjectID)));
		platformGO->SetActive(false); // Set to inactive as it is not being used yet
		platforms.push_back(platformGO);
		_scene->AddGameObject(platformGO); // Add this to the scene here as it is being built outside of the normal process
	}

	return ComponentFactory::MakeAlexPlatformManagerComponent(platforms);
}

inline void FetchAlexPlatformManagerDependencies()
{
	APlatformManagerComponent* platformManager = static_cast<APlatformManagerComponent*>(dependencyComponent);
	TransformComponent* transform;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
		}
	}

	platformManager->SetDependencies(transform);
}

inline IComponent * BuildAlexGameManager()
{
	return ComponentFactory::MakeAlexGameManagerComponent();
}

inline void FetchAlexGameManagerDependencies()
{
	AGameManagerComponent* alexController = static_cast<AGameManagerComponent*>(dependencyComponent);
	AControllerComponent* controller;
	APlatformManagerComponent* platformManager;
	TextRendererComponent* text;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "controllercomponent")
		{
			controller = _scene->GetGameObject(it->second)->GetComponent<AControllerComponent>();
		}
		else if (it->first == "platformmanagercomponent")
		{
			platformManager = _scene->GetGameObject(it->second)->GetComponent<APlatformManagerComponent>();
		}
		else if (it->first == "textrenderercomponent")
		{
			text = _scene->GetGameObject(it->second)->GetComponent<TextRendererComponent>();
		}
	}

	alexController->SetDependencies(controller, platformManager, text);
}

#pragma endregion

#pragma region MGame methods definitions

IComponent * BuildMCharacterComponent()
{
	return ComponentFactory::MakeMCharacterComponent();
}

void FetchMCharacterDependencies()
{
	MCharacterComponent* mCharacter = static_cast<MCharacterComponent*>(dependencyComponent);
	TransformComponent* transform;
	RigidBodyComponent* rigidbody;
	SpriteAnimatedComponent *spriteanimatedcomponent = new SpriteAnimatedComponent();
	SpriteAnimatedComponent *spriteanimatedcomponent2 = new SpriteAnimatedComponent();
	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
		}
		else if (it->first == "rigidbodycomponent")
		{
			rigidbody = _scene->GetGameObject(it->second)->GetComponent<RigidBodyComponent>();
		}
		else if (it->first == "spriteanimatedcomponent")
		{
			spriteanimatedcomponent = _scene->GetGameObject(it->second)->GetComponent<SpriteAnimatedComponent>();
		}
		/*else if (it->first == "spriteanimatedcomponent2")
		{
			spriteanimatedcomponent2 = _scene->GetGameObject(it->second)->GetComponent<SpriteAnimatedComponent>();
		}*/
	}

	mCharacter->SetDependencies(transform, rigidbody, spriteanimatedcomponent/*, spriteanimatedcomponent2*/ ); //TODO - define method - see if i need to add any other dependency
}

inline IComponent * BuildMBackgroundComponent()
{
	return ComponentFactory::MakeMBackgroundComponent();
}

void FetchMBackgroundDependencies()
{
	MBackgroundComponent* mBackground = static_cast<MBackgroundComponent*>(dependencyComponent);
	TransformComponent* transform;
	RigidBodyComponent* rigidbody;
	BoxColliderComponent* boxCollider;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
		}
		else if (it->first == "rigidbodycomponent")
		{
			rigidbody = _scene->GetGameObject(it->second)->GetComponent<RigidBodyComponent>();
		}
		else if (it->first == "boxcollidercomponent")
		{
			boxCollider = _scene->GetGameObject(it->second)->GetComponent<BoxColliderComponent>();
		}

	}

	mBackground->SetDependencies(transform, rigidbody, boxCollider); //TODO - define method - see if i need to add any other dependency
}

inline IComponent * BuildMPhantomComponent()
{
	return ComponentFactory::MakeMPhantomComponent();
}

void FetchMPhantomDependencies()
{
	MPhantomComponent* mPhantom = static_cast<MPhantomComponent*>(dependencyComponent);
	TransformComponent* transform;
	RigidBodyComponent* rigidbody;
	SpriteAnimatedComponent* spriteAnimatedComponent;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
		}
		else if (it->first == "rigidbodycomponent")
		{
			rigidbody = _scene->GetGameObject(it->second)->GetComponent<RigidBodyComponent>();
		}
		else if (it->first == "spriteanimatedcomponent")
		{
			spriteAnimatedComponent = _scene->GetGameObject(it->second)->GetComponent<SpriteAnimatedComponent>();
		}

	}

	mPhantom->SetDependencies(transform, rigidbody, spriteAnimatedComponent); //TODO - define method - see if i need to add any other dependency
}

inline IComponent * BuildMChestComponent()
{
	return ComponentFactory::MakeMChestComponent();
}

void FetchMChestDependencies()
{
	MChestComponent* mChest = static_cast<MChestComponent*>(dependencyComponent);
	TransformComponent* transform;
	RigidBodyComponent* rigidbody;
	SpriteAnimatedComponent* spriteAnimatedComponent;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
		}
		else if (it->first == "rigidbodycomponent")
		{
			rigidbody = _scene->GetGameObject(it->second)->GetComponent<RigidBodyComponent>();
		}
		else if (it->first == "spriteanimatedcomponent")
		{
			spriteAnimatedComponent = _scene->GetGameObject(it->second)->GetComponent<SpriteAnimatedComponent>();
		}

	}

	mChest->SetDependencies(transform, rigidbody, spriteAnimatedComponent); //TODO - define method - see if i need to add any other dependency
}

inline IComponent * BuildMIntroComponent()
{
	return ComponentFactory::MakeMIntroComponent();
}

void FetchMIntroDependencies()
{
	MIntroComponent* mIntro = static_cast<MIntroComponent*>(dependencyComponent);
	TransformComponent* transform;
	SpriteAnimatedComponent* spriteAnimatedComponent;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
		}

		else if (it->first == "spriteanimatedcomponent")
		{
			spriteAnimatedComponent = _scene->GetGameObject(it->second)->GetComponent<SpriteAnimatedComponent>();
		}

	}

	mIntro->SetDependencies(transform, spriteAnimatedComponent);
}

#pragma endregion


GUID ComponentBuilder::StringToGUID(const std::string& guid) {
	GUID output;
	unsigned long p0;
	int p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;

	int err = sscanf_s(guid.c_str(), "%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10);

	if (err != 11)
		throw std::logic_error("Invalid GUID, format should be {00000000-0000-0000-0000-000000000000}");

	// Set the data like this to avoid corrupting the stack
	output.Data1 = p0;
	output.Data2 = p1;
	output.Data3 = p2;
	output.Data4[0] = p3;
	output.Data4[1] = p4;
	output.Data4[2] = p5;
	output.Data4[3] = p6;
	output.Data4[4] = p7;
	output.Data4[5] = p8;
	output.Data4[6] = p9;
	output.Data4[7] = p10;
	return output;
}