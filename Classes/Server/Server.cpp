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
	m_pathSearchLogic = new PathSearchLogic(PathData::m_mapSize,
                                            PathData::m_roadInspectArray,
                                            PathData::m_obstaclesInspectArray,
                                            SEARCH_PATH_ASTAR,
                                            SEARCH_PATH_PRECISE);
}

std::vector<Vec2> Server::startMove( Vec2 startPoint, Vec2 endPoint )
{
    startPoint = getMapPositionByWorldPosition(startPoint);
    endPoint = getMapPositionByWorldPosition(endPoint);

    std::vector<Vec2> _path = m_pathSearchLogic->getSearchPath( (startPoint), (endPoint));
    for(auto & child : _path)
    {
        child = getWorldPositionByMapPosition(child);
    }
    
    return _path;
}
Vec2 Server::getWorldPositionByMapPosition( Vec2 point )
{
    return Vec2(PathData::m_tileSize.width * point.x, (PathData::m_mapSize.height - point.y)*PathData::m_tileSize.height);
}

Vec2 Server::getMapPositionByWorldPosition( Vec2 point )
{
    return Vec2((int)(point.x/PathData::m_tileSize.width),(int)(PathData::m_mapSize.height - point.y/PathData::m_tileSize.height ) );
}