#include "Server.h"
#include "PathData.h"
#include "MapXMLCreater.h"
#define CREATE_DATA_XML 0
Server::Server(void)
{
    init();
}

Server::~Server(void)
{
}

void Server::init()
{
#if CREATE_DATA_XML
    TMXTiledMap* _tiledMap = TMXTiledMap::create("mapData/baseMap.tmx");
    MapXMLCreater::createXML(_tiledMap);
#endif
	PathData::createPathData("mapData.xml");
	m_pathSearchLogic = new PathSearchLogic(PathData::m_roadPathXml.m_size,
                                            PathData::m_roadInspectArray,
                                            PathData::m_obstaclesInspectArray,
                                            SEARCH_PATH_ASTAR,
                                            SEARCH_PATH_PRECISE);
}

std::vector<Vec2> Server::startMove( Vec2 startPoint, Vec2 endPoint )
{
    const std::vector<Vec2>& _path = m_pathSearchLogic->getSearchPath( startPoint, endPoint);
    
    return _path;
}
