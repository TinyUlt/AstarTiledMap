#pragma once
#include <vector>
#include <iostream>
//#include "cocos2d.h"
#include "PathSprite.h"
//USING_NS_CC;

//搜寻算法
enum SEARCH_PATH_ALGORITHM
{
    SEARCH_PATH_DIJKSTRA,
    SEARCH_PATH_PRIORITY,
    SEARCH_PATH_ASTAR
};

//路径精确度
enum SEARCH_PATH_PERCISION
{
    SEARCH_PATH_POINT,//返回一个距离最近的边缘上的点
    SEARCH_PATH_NORMAL,//正常的搜寻路径点集合
    SEARCH_PATH_PRECISE,//优化过的SEARCH_PATH_NORMAL
};
class PathSearchLogic
{
public:
	PathSearchLogic(CCSize size,
                    std::vector< std::vector<PathSprite*>> inspectArray,
                    std::vector< std::vector<PathSprite*>> obstaclesInspect,
                    SEARCH_PATH_ALGORITHM algorithm, SEARCH_PATH_PERCISION percision):
    m_mapSize(size),
    m_roadInspectArray(inspectArray),
    m_obstaclesInspectArray(obstaclesInspect),
    m_algorithm(algorithm),
    m_percision(percision)
    {};
	~PathSearchLogic(){};
	CCSize m_mapSize;
	std::vector< std::vector<PathSprite*>> m_roadInspectArray;
    std::vector< std::vector<PathSprite*>> m_obstaclesInspectArray;
    std::vector<PathSprite*> m_haveInspectRoadList;//检测过的列表
    std::vector<PathSprite*> m_haveInspectObstaclesList;//检测过的列表
//	std::vector<Vec2> m_pathList;//路径列表
	std::vector<PathSprite*> m_openList;//开放列表(里面存放相邻节点)

    
    std::vector<Vec2> getSearchPath(Vec2 startPoint, Vec2 endPoint);
	std::vector<Vec2> calculatePath(int startX, int startY, int endX, int endY);//计算路径
    Vec2 calculatePath(int startX, int startY);//计算点
	PathSprite* getMinPathFormOpenList();
	PathSprite* getObjFromInspectArray( std::vector< std::vector<PathSprite*>>& InspectArray, int x, int y );

    
	void inspectTheAdjacentNodes( PathSprite* node, PathSprite* adjacent, PathSprite* endNode );
    void inspectTheAdjacentNodes( PathSprite* node, PathSprite* adjacent);
	float calculateTwoObjDistance( PathSprite* obj1, PathSprite* obj2 );
	bool removeObjFromOpenList( PathSprite* sprite );
	void clearPath(  );
	void resetInspectArray();
	bool detectWhetherCanPassBetweenTwoPoints( Vec2 p1, Vec2 p2 );
    Vec2 resetObjPosition(Vec2 Vec2 );//保证位置正确
    
    
    SEARCH_PATH_ALGORITHM m_algorithm;
    SEARCH_PATH_PERCISION m_percision;
};

