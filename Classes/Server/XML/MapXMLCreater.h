#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include <string>

using namespace std;

class MapXMLCreater
{
public:
	static void createXML(CCTMXTiledMap* _tiledMap);
};

