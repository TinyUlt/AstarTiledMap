﻿#pragma once
#include "PathSearchLogic.h"
#include <functional>
#include <vector>
using namespace std;
class Server
{
public:
	Server(void);
	~Server(void);
	void init();
	
	std::vector<Vec2> startMove( Vec2 startVec2,  Vec2 endVec2 );//接收数据
    static Vec2 getWorldPositionByMapPosition( Vec2 point );
    static Vec2 getMapPositionByWorldPosition( Vec2 point );

	PathSearchLogic* m_pathSearchLogic;//路径数据
};

