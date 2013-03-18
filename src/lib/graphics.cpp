#include <OpenGL/OpenGL.h>
#include <irrlicht/irrlicht.h>
#include "graphics.hpp"

class MyEventReceiver : public ::irr::IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const ::irr::SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		return false;
	}
	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(::irr::EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}
	MyEventReceiver()
	{
		for (::irr::u32 i=0; i< ::irr::KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}
private:
	// We use this array to store the current state of each key
	bool KeyIsDown[::irr::KEY_KEY_CODES_COUNT];
};
#define driverType ::irr::video::EDT_OPENGL
namespace Graphical {
	class EngineInternals {
	public:
		MyEventReceiver receiver;
		::irr::IrrlichtDevice * device;
		::irr::video::IVideoDriver * driver;
		::irr::scene::ISceneManager * smgr;
		::irr::scene::ICameraSceneNode * cam;
		::irr::scene::IMesh * plane_mesh;
		::irr::scene::ISceneNode * plane_node;
		int lastFPS;
	};
	void Engine::setup(){
		_internals = new EngineInternals();
		_internals->device = createDevice(driverType,
			irr::core::dimension2d<irr::u32>(640, 480), 16, false, false, false, &_internals->receiver);
		_internals->driver = _internals->device->getVideoDriver();
		_internals->smgr = _internals->device->getSceneManager();
		_internals->cam = _internals->smgr->addCameraSceneNodeFPS();
		_internals->device->getCursorControl()->setVisible(false);
		_internals->lastFPS = -1;
		_internals->plane_mesh =  _internals->smgr->getGeometryCreator()->createPlaneMesh(irr::core::dimension2d<irr::f32>(1000,1000));
		//smgr->addLightSceneNode(0, core::vector3df(-15,5,-105), video::SColorf(1.0f, 1.0f, 1.0f));
		_internals->smgr->setAmbientLight(irr::video::SColor(0,60,60,60));
		_internals->plane_node = _internals->smgr->addMeshSceneNode(_internals->plane_mesh);
		_internals->cam->setPosition(irr::core::vector3df(0,20,0));
		_internals->plane_node->setPosition(irr::core::vector3df(0,0,80));
	}
	void Engine::closeup(){
		_internals->device->drop();
	}
	void Engine::render(){
		if(!_internals->device->run()) return;
		if (_internals->device->isWindowActive())
		{
			_internals->driver->beginScene(true, true, irr::video::SColor(255,200,200,200));
			_internals->smgr->drawAll();
			_internals->driver->endScene();

			int fps = _internals->driver->getFPS();

			if (_internals->lastFPS != fps)
			{
				irr::core::stringw str = L"Physics rendering at [";
				str += _internals->driver->getName();
				str += "] FPS:";
				str += fps;

				_internals->device->setWindowCaption(str.c_str());
				_internals->lastFPS = fps;
			}
		}
		else
			_internals->device->yield();
	}
	bool Engine::exitRequested(){
		return _internals->receiver.IsKeyDown(irr::KEY_ESCAPE);
	}
	Engine::~Engine(){
		delete _internals;
	}
};