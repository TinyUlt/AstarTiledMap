#pragma once
#include "cocos2d.h"
USING_NS_CC;
struct MapPathXML
{
	std::string m_data;
	CCSize m_size;
};
class PathSprite 
{
public:
	PathSprite():m_parent(NULL),
		m_child(NULL),
		m_costToSource(0),
		m_FValue(0),
		m_startX(0),
		m_startY(0),
		m_endX(0),
		m_endY(0)
	{

	};
public:
	PathSprite* m_parent;//父节点
	PathSprite* m_child;//子节点
	float m_costToSource;//到起始点的距离
	int m_x;//地图坐标
	int m_y;
	float m_FValue;

	int m_startX;//开始点
	int m_startY;

	int m_endX;//结束点
	int m_endY;

};