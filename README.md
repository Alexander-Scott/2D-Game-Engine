# GEPAA Game Engine #

This repository contains the source code for the GEPAA Game Engine, a team-developed Game Engine built for the 
Game Engine Programming and Architecture module at Staffordshire University. 

Created by: Alex Scott, Myriam Sarah, Paul-Emile Kim.

## Useful Links ##

* [Module Page](http://www.staffs.ac.uk/current/student/modules/showmodule.php?code=COSE70635)
* [Private Trello Board](https://trello.com/b/jZPgM3R2/gepaa-group-1)

## Running the application ##
Ideally run the solution in Visual Studio 2017. Make sure the build configuration is set to StandaloneDebug
and the platform is any CPU or x64. If you want to run tests make sure the test processor architecture is
set to x64.

### Scenes and GameObjects ###
At any one time there is a single active scene, managed by the SceneManager system and built by the 
SceneBuilder system. Scenes must inherit from IScene and are esentially used to store all GameObjects 
and update/draw them. In the future multiple scene types will be added but for now there's no implementation
of it. GameObjects stored in scenes are used to hold components. 

Components are classes with custom functionality that is applied to the GameObject. Components must inherit 
from IComponent and can optionally inherit IDrawableComponent, IUpdateableComponent, IMessageableComponent
and IEditable. These additional interfaces are called at certain times and require the component to do certain things. 
For example, IDrawableComponent components are required to send drawing information to the Graphics system. 
IUpdateableComponent components have an Update function  that is called every frame. 
IMessageableComponent components can recieve messages from other GameObjects/components. IEditableComponent
components are fetched by the external editor and allow component values to be edited by it.

When creating a component there are a few steps you must do. Firstly, create the class and
include IComponent.h and inherit from it and in the constructor call IComponent's constructor
and specify the name of the new component. This will allow this new class to be added to GameObjects.
Secondly a few functions need to be implemented so that the component follows various design
patterns exhibited in the engine. In the ComponentFactory namespace your new class must be included
and a function that returns an instance of your class must be added. 

In the ComponentSaver.cpp define an inline function and then map that function to your components
name in the ComponentSaver constructor. In the actual function dynamically cast _component to your
component and then allocate all variables you want to persist to the _componentNode.
In the ComponentBuilder.cpp file you must define an inline function that returns an IComponent* which will point to an instance
of your class. Then in the ComponentBuilder constructor map your components name to the inline function.
And then in the function itself read the xml_node attributes and parse them into variables. Then,
using the ComponentFactory, build an instance of your component and return it.

### Systems and Messaging ###
Every significant part of the engine is classed as a system, and must inherit from ISystem. 
This includes things suchs as Graphics, Input, Networking, file I/O etc. Currently there's only a 
few systems implemented, mainly to demonstrate their usage. To register a new system, make sure it 
inherits ISystem and also make sure it is initalised in the SystemManager class. 

Systems can communicate with other systems by sending messages through the SystemMessageDispatcher, a 
instance injected into every ISystem that has a job of delivering messages to the correct recipiants. 
To do this, systems must subscribe to a certain message type (an enum) with the SystemMessageDispatcher. 
This is done by calling SubscribeToMessageType() in the overriden InitaliseListeners() function.
Once doing this the SystemMessageDispatcher will deliver the messages to the system by calling the RecieveMessage() 
method in ISystem (which needs to be overriden). From here, the recieved message can be statically cast 
to any other message type and data can be extracted from it.

## Code Flow ##
The application is initalised in Main.cpp. Here an instance of SystemManager is created. The purpose
of SystemManager is simply to initalise all other systems and the SystemMessageDispatcher instance, 
which is done in the SystemManager constructor. All systems are created as shared_ptr's, with the 
SystemMessageDispatcher instance injected into their constructors. Then all their message listeners 
are initalised with the InitaliseListeners() function, then an optional function, SystemsInitalised(), 
is called on each system after everything has been set up. 

The Engine system is probably the highest level system. Its purpose is to oversee operations
and provide a gateway to the rest of the engine. It's SystemsInitalised() function sends a message to
the SceneBuilder system with a filePath detailing which scene it should build. It listens for the
SystemUpdate message type, which is sent from the SystemManager class every iteration of the while loop
keeping the program alive. Once the Engine system recieves this message it calls the UpdateEngine() 
function which has a controlled update loop in it. This function sends out messages to other systems
such as update scene, draw scene, prepare graphics frame, end graphics frame and in the future will
have physics and input update messages. However because this is a controlled update loop, certain messages
won't be sent out every time the function is called. Instead they will sent out at defined intervals, such
as 60 times a second. 

The MainWindow system deals with creating an application window and recieving application level messages,
such as move mouse or key pressed. Its SystemsInitalised() function sends a message to the Graphics
system with a reference to the HWND of the application window, which is used to initalise the Graphics. 
It also sends regular messages input to the SMDSingleton, such as mouse move and keyboard key pressed, with
the messages containg relevant data such as position of the mouse and what key was pressed.

The Graphics system deals with what to draw each frame. It recieves start and end frame messages from
the Engine system and in the future will recieve drawing data from IDrawableComponent components.

The SceneBuilder system deals with parsing scene XML files from disk and building a scene instance from it.

The SceneManagement system holds and stores the current scene and recieves draw/update messages from the engine.

## Future Features ##
### Input ###
An Input system will need to be created in the future. This system will inherit from ISystem and will need to
be added to the SystemManager initalisation function. Currently, the MainWindow system is sending input messages
to the SystemMessageDispatcher instance when it recieves them from the windows application, 
such as key or mouse press. The Input system will need to subscribe to this message type and then 
perform logic based on what it recieves. The MainWindow system can also be improved to translate 
more message types and then also send those to the SystemMessageDispatcher instance, such as Xbox conntroller 
inputs or distinction between input methods (to allow for multiplayer).

Currently, the InputHandler class can recieve the raw inputs from a keyboard, a mouse or Xbox controller. 
It also holds the inputs map. A key can be binded with a sCommand which hold an ID integer. 
This sCommand structure serves as a communication message between the InputHandler class and the game logic classes: 
the game logic will trigger a certain command depending on which ID it recieves. The game logic will need to react 
differently depending if the command is an single action (ex: selecting something in the main menu) or a state 
(ex: moving in a certain direction). If it's an single action, the command must be executed on keydown 
and deactivated provisionnaly to avoid this action to be repeated multiple times. It will be reactivated on keyup.
A state will be executed on keydown, and will continue to be executed until keyup is sent (ie, the key binded 
to this command state is not held anymore). Ranges commands which take an analog stick or an analog trigger as an input 
will also send how much they're pushed in the message to the game logic. 
Commands can be swaped by pressing spacebar and by pressing two binded keys successively.
The inputs maps are saved and loaded via a xml file.

### Graphics ###
The Graphics system can be extended to implement different graphics APIs such as DirectX or OpenGL. These new
APIs would need to inherit from IGraphics and implement all the required virtual functions. And in SystemsManager
the Graphics system instance would be created from this new API such as DX11Graphics.

The way the Graphics system gets drawing data from the current scene is through a message sent to it
from the SceneManager system: DrawSceneMessage. This message contains two vectors of two structs
which represent the sprites to be drawn in the scene and the text to be draw in the scene. In the Draw()
function in SceneManager the scene is asked to populate the DrawSceneMessage with drawing information and then
the system sends that to the Graphics system, full of drawing information.

However there is currently nothing adding to this message when it passed around the scene. To fix this a drawing
GameObject component, such as SpriteRendererComponent needs to be created. This component would inherit 
IDrawableComponent and override the Draw virtual function. Inside this function the component would add
its drawing data to the message that is passed to the Draw function. This way the data will be sent to 
the Graphics system to be drawn.

The Graphics system would need to be extended to recieve this message and then add the sprite to the 
graphic API's draw list (sprite batch in DX11). This would be done in the DrawSprite() and DrawText2D() functions.

## Building a game running on the engine ##

To build a game that runs on the engine you need to do a few things. Firstly create a scene XML file and put it
in the resources/scenes folder and name it appropiately. In this file add a scene name, done by adding the following:
<scene name="AlexGame"></scene>. In the Engine class in the engine, edit the RequestBuildSceneMessage contents so
that it has the relative path to the new scene XML file. The engine should now run your game.

###Creating custom components/scripts

To create and register a new component that only serves a purpose in your game you will need to do a few things. 
Firstly, within the Game/YourGame filter, create a new class called YourGameComponentFactory. This component factory
is an extension of the default component factory and will be used to create your custom components. In here you can
create functions that instantiate and return your custom components. Next you will need to register the component
within the ComponentBuilder system so that it can be built from the scene XML file. In ComponentBuilder.h, make sure
you are #including YourGameComponentFactory. Then at the top of ComponentBuilder.cpp define the build functions for
your custom component, making sure it returns a IComponent*. In the ComponentBuilder constructors, insert into 
_buildMapper the string name of your component and a pointer to the build function. In the actual build function,
parse the XML node to extract any attributes your component needs. Then call the relevant function in
YourGameComponentFactory to actual have the component instanstiated. These steps will parse, build and then add
an instance of your component defined in XML to a GameObject.

###Fetching component dependencies

If your component requires a pointer to another component, either on the same GameObject or different object, you will
need to use the dependency fetching feature. To do this you must configure your custom component in XML. Before the closing
tag of the component, add a <Dependency></Dependency> tag. Add as attributes to this tag, the ID of the GameObject that
has the component you require. The second step needs to be done in ComponentBuilder.cpp. At the top define function
that will fetch the dependency and then in the ComponentBuilder constructor link that function to the component's name.
In the actual fetch function, iterate through the 'dependencies' global variable. At each iteration, fetch the GameObject
with the listed ID from the scene by using the following: _scene->GetGameObject(it->second). From here you can then
use GetComponent<> to fetch a certain type of component from this GameObject. To pass it to the component with the dependency,
statically cast the 'dependencyComponent' global variable into the component type and then pass it to it through a custom function,
such as SetDependencies().

## Troubleshooting ##

###Adding new file to project and referencing it in a test

You will need to include the new file in the tests project under the source filter. The testing 
framework needs a local copy of the file in order to perform the tests. To do this simply right
click the source filter and add the existing item.