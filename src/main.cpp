#include <irrlicht/irrlicht.h>
#include <iostream>
#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFString.h>
#include <OpenGL/OpenGL.h>

using namespace irr;
class MyEventReceiver : public IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return false;
    }
    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }
private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};
#define driverType video::EDT_OPENGL
int main(int argc, char* argv[]){

	MyEventReceiver receiver;

    IrrlichtDevice* device = createDevice(driverType,
            core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    auto cam = smgr->addCameraSceneNodeFPS();
    device->getCursorControl()->setVisible(false);
    int lastFPS = -1;
    auto mesh = smgr->getGeometryCreator()->createPlaneMesh(core::dimension2d<f32>(100,100));
    //smgr->addLightSceneNode(0, core::vector3df(-15,5,-105), video::SColorf(1.0f, 1.0f, 1.0f));
    smgr->setAmbientLight(video::SColor(0,60,60,60));
    auto planenode = smgr->addMeshSceneNode(mesh);
    cam->setPosition(irr::core::vector3df(0,20,0));
    planenode->setPosition(irr::core::vector3df(0,0,80));
    
    while(device->run())
    {
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, video::SColor(255,200,200,200));
            smgr->drawAll();
            driver->endScene();

            int fps = driver->getFPS();

            if (lastFPS != fps)
            {
                core::stringw str = L"Physics rendering at [";
                str += driver->getName();
                str += "] FPS:";
                str += fps;

                device->setWindowCaption(str.c_str());
                lastFPS = fps;
            }
        }
        else
            device->yield();
        if(receiver.IsKeyDown(irr::KEY_ESCAPE)) break;
    }
    device->drop();
	return 0;
}

// function provides some Mac OS X specific source code to load files from the resources of the application bundle.
char * resPath(char **argv, char* name, char* type ) 
{
   static char resource[1024];
   
   CFURLRef cfBundleURL = CFBundleCopyResourceURL( CFBundleGetMainBundle(),    
                                       CFStringCreateWithCString(kCFAllocatorDefault,
                                                          name, 
                                                          kCFStringEncodingISOLatin1), 
                                       CFStringCreateWithCString(kCFAllocatorDefault, 
                                                          type, 
                                                          kCFStringEncodingISOLatin1), 
                                       NULL );
   
   
   CFStringGetCString( CFURLCopyPath(cfBundleURL),
                  resource,
                  1023,
                  kCFStringEncodingISOLatin1);
   
   return resource;
}
#pragma comment(lib, "libMacOSX.a")