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
    SEARCH_PATH_NORMAL,//正常的搜寻路径点集合
    SEARCH_PATH_PRECISE,//优化过的SEARCH_PATH_NORMAL
};
class PathSearchLogic
{
public:
	PathSearchLogic(Size size,
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
	Size m_mapSize;
	std::vector< std::vector<PathSprite*>> m_roadInspectArray;//路列表径
    std::vector< std::vector<PathSprite*>> m_obstaclesInspectArray;//障碍物列表
    std::vector<PathSprite*> m_haveInspectRoadList;//检测过的列表
    std::vector<PathSprite*> m_haveInspectObstaclesList;//检测过的列表
	std::vector<PathSprite*> m_openList;//开放列表(里面存放相邻节点)

    
    std::vector<Vec2> getSearchPath(Vec2 startPoint, Vec2 endPoint);//得到路径
	std::vector<Vec2> calculatePath(int startX, int startY, int endX, int endY);//计算路径
    Vec2 calculatePath(int startX, int startY);//计算点
	PathSprite* getMinPathFormOpenList();//从开放列表中得到最短路径点
	PathSprite* getAdjacentFromInspectArray( std::vector< std::vector<PathSprite*>>& InspectArray, int x, int y );//获得相邻点
	void inspectTheAdjacentNodes( PathSprite* node, PathSprite* adjacent, PathSprite* endNode );//把相邻点放入开放列表
    void inspectTheAdjacentNodes( PathSprite* node, PathSprite* adjacent);//把相邻点放入开放列表
	float calculateTwoObjDistance( PathSprite* obj1, PathSprite* obj2 );//计算两个路径点的距离
	bool removeAdjacentFromOpenList( PathSprite* sprite );//从开放列表中删除相邻点
	void clearPath(  );//清除数据
	void resetInspectArray();//还原列表数据
	bool detectWhetherCanPassBetweenTwoPoints( Vec2 p1, Vec2 p2 );//检测两点中是否有障碍物
    Vec2 resetObjPosition(Vec2 Vec2 );//保证位置正确
    
    
    SEARCH_PATH_ALGORITHM m_algorithm;
    SEARCH_PATH_PERCISION m_percision;
};

