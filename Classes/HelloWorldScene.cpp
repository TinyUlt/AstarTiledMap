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
    TMXTiledMap* _tiledMap = TMXTiledMap::create("mapData/baseMap.tmx");
    rootNode->addChild(_tiledMap);
    m_sprite = MoveSprite::create();
    rootNode->addChild(m_sprite);
    addChild(rootNode);
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    
    m_server = new Server();

    const std::vector<Vec2>& _path3 = m_server->startMove(Vec2(200,200), Vec2(8,8));
    
    for(auto & child : _path3)
    {
        log("%f,%f", child.x, child.y);
    }
    
    return true;
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    auto _touchPosition = touch->getLocation();
    
    m_sprite->startMove(m_server->startMove(m_sprite->getPosition(), _touchPosition));
    return true;
}
void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    
}
void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    
}