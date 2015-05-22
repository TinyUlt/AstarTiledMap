#pragma once
#include "tinyxml.h"
#include <string>
#include <vector>
#include <iostream>
//#include "cocos2d.h"
#include "PathSprite.h"
USING_NS_CC;

class PathData
{
public:
	PathData(void);
	~PathData(void);

	static MapPathXML m_roadPathXml;
	static MapPathXML m_obstaclesPathXml;
	static MapPathXML m_opcityPathXml;
    static Size m_mapSize;
    static Size m_tileSize;

	static std::vector< std::vector<PathSprite*>> m_roadInspectArray;
	static std::vector< std::vector<PathSprite*>> m_obstaclesInspectArray;
	static std::vector< std::vector<PathSprite*>> m_opcityInspectArray;

    static void createPathData(std::string mapXMLPath);
    static void getPathdataFromXML( std::string mapPath );
};

