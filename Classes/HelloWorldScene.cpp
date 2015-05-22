#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Server.h"


using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
    
    Server* _server = new Server();

    const std::vector<Vec2>& _path = _server->startMove(Vec2(1,1), Vec2(10,10));
    
    for(auto & child : _path)
    {
        log("%f,%f", child.x, child.y);
    }
    log("   ");
    const std::vector<Vec2>& _path2 = _server->startMove(Vec2(1,1), Vec2(20,20));
    
    for(auto & child : _path2)
    {
        log("%f,%f", child.x, child.y);
    }
    log("   ");
    const std::vector<Vec2>& _path3 = _server->startMove(Vec2(1,1), Vec2(50,50));
    
    for(auto & child : _path3)
    {
        log("%f,%f", child.x, child.y);
    }
    
    
    
    return true;
}
void HelloWorld::recivePath(std::vector<Vec2> data)
{
    
}