#include "PathSearchLogic.h"
#include "StaticValue.h"
#include "MathLogic.h"

std::vector<Vec2> PathSearchLogic::getSearchPath(Vec2 startPoint, Vec2 endPoint)
{
    startPoint = resetObjPosition(startPoint);
    
    std::vector<Vec2> _path;
    if (endPoint.x<m_mapSize.width  && endPoint.y<m_mapSize.height)
    {
        PathSprite*_sp  =  NULL;
        if ((_sp = m_roadInspectArray[(int)endPoint.x][(int)(endPoint.y)]))
        {
            _path = calculatePath(startPoint.x, startPoint.y, _sp->m_x, _sp->m_y);
        }
        else
        {
            if ((_sp = m_obstaclesInspectArray[(int)endPoint.x][(int)(endPoint.y)]))
            {
                Vec2 _point =calculatePath(_sp->m_x, _sp->m_y);
                if (_point.x !=-1 && _point.y !=-1)
                {
                    _path = calculatePath(startPoint.x, startPoint.y, _point.x, _point.y);
                }
            }
        }

    }
    
    return _path;
}
std::vector<Vec2> PathSearchLogic::calculatePath( int startX, int startY, int endX, int endY )
{
	clearPath();
    
    std::vector<Vec2> _pathList;
    if(m_percision == SEARCH_PATH_NORMAL)
    {
        //得到开始点的节点
        PathSprite*   _startNode = m_roadInspectArray[startX][startY];
        //得到结束点的节点
        PathSprite*  _endNode = m_roadInspectArray[endX][endY];
        
        //因为是开始点 把到起始点的距离设为0, F值也为0
        _startNode->m_costToSource = 0;
        _startNode->m_FValue = 0;
        
        //把已经检测过的点从检测列表中删除
        m_roadInspectArray[startX][startY] = NULL;
        //把该点放入已经检测过点的列表中
        m_haveInspectRoadList.push_back(_startNode);
        //然后加入开放列表
        m_openList.push_back(_startNode);
        
        PathSprite* _node = NULL;
        while (true)
        {
            //得到离起始点最近的点(如果是第一次执行, 得到的是起点)
            _node = getMinPathFormOpenList();
            if (!_node)
            {
                break;
            }
            //把计算过的点从开放列表中删除
            removeObjFromOpenList( _node);
            int _x = _node->m_x;
            int _y = _node->m_y;
            
            //
            if (_x ==endX && _y == endY)
            {
                break;
            }
            
            //检测8个方向的相邻节点是否可以放入开放列表中
            PathSprite* _adjacent = NULL;
            
            _adjacent = getObjFromInspectArray(  m_roadInspectArray, _x +1, _y);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(  m_roadInspectArray, _x , _y -1);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(  m_roadInspectArray, _x -1, _y);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(  m_roadInspectArray, _x , _y+1);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(  m_roadInspectArray,_x + 1, _y + 1);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(  m_roadInspectArray, _x +1, _y-1);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(  m_roadInspectArray, _x -1, _y - 1);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(  m_roadInspectArray, _x -1, _y+1);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            
        }
        
        while (_node)
        {
            //把路径点加入到路径列表中
            _pathList.insert(_pathList.begin(),Vec2(_node->m_x, _node->m_y) );
            _node = _node->m_parent;
        }
        
        
        
    }
    else if(m_percision == SEARCH_PATH_PRECISE)
    {
        //得到开始点的节点
        PathSprite*    _endNode= m_roadInspectArray[startX][startY];
        //得到结束点的节点
        PathSprite*   _startNode = m_roadInspectArray[endX][endY];
        
        //因为是开始点 把到起始点的距离设为0, F值也为0
        _startNode->m_costToSource = 0;
        _startNode->m_FValue = 0;
        
        //把已经检测过的点从检测列表中删除
        m_roadInspectArray[endX][endY] = NULL;
        //把该点放入已经检测过点的列表中
        m_haveInspectRoadList.push_back(_startNode);
        //然后加入开放列表
        m_openList.push_back(_startNode);
        
        PathSprite* _node = NULL;
        while (true)
        {
            //得到离起始点最近的点(如果是第一次执行, 得到的是起点)
            _node = getMinPathFormOpenList();
            if (!_node)
            {
                //不到路径
                break;
            }
            //把计算过的点从开放列表中删除
            removeObjFromOpenList( _node);
            int _x = _node->m_x;
            int _y = _node->m_y;
            
            //
            if (_x ==startX && _y == startY)
            {
                break;
            }
            
            //检测8个方向的相邻节点是否可以放入开放列表中
            
            PathSprite* _adjacent = NULL;
            
            _adjacent = getObjFromInspectArray( m_roadInspectArray, _x +1, _y);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(  m_roadInspectArray, _x , _y -1);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(  m_roadInspectArray, _x -1, _y);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(   m_roadInspectArray, _x , _y+1);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(  m_roadInspectArray, _x + 1, _y + 1);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(   m_roadInspectArray, _x +1, _y-1);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(   m_roadInspectArray, _x -1, _y - 1);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            _adjacent = getObjFromInspectArray(   m_roadInspectArray, _x -1, _y+1);
            inspectTheAdjacentNodes(_node, _adjacent, _endNode);
            
            
        }
        
        while (_node)
        {
            //把路径点加入到路径列表中
            _pathList.push_back(Vec2(_node->m_x, _node->m_y) );
            _node = _node->m_parent;
        }
        
        
        
        
        clearPath();
        std::vector<Vec2> _pathListTemp;//路径列表
        _pathListTemp.push_back(_pathList[0]);
        for (int j = 0; j < _pathList.size(); j++)
        {
            for (int i = _pathList.size()-1; i > j; i--)
            {
                if(detectWhetherCanPassBetweenTwoPoints(_pathList[j], _pathList[i]))
                {
                    _pathListTemp.push_back( _pathList[i]);
                    
                    
                    j = i;
                }
            }
        }
        
        _pathList = _pathListTemp;
    }
    
	clearPath();
    return _pathList;
}
Vec2 PathSearchLogic::calculatePath(int startX, int startY)//计算点
{
    clearPath();
    
    //得到开始点的节点
    PathSprite*   _startNode = m_obstaclesInspectArray[startX][startY];
    //得到结束点的节点
    //PathSprite*  _endNode = m_obstaclesInspectArray[endX][endY];
    
    //因为是开始点 把到起始点的距离设为0, F值也为0
    _startNode->m_costToSource = 0;
    _startNode->m_FValue = 0;
    
    //把已经检测过的点从检测列表中删除
    m_obstaclesInspectArray[startX][startY] = NULL;
    //把该点放入已经检测过点的列表中
    m_haveInspectObstaclesList.push_back(_startNode);
    //然后加入开放列表
    m_openList.push_back(_startNode);
    
    PathSprite* _node = NULL;
    Vec2 _endPoint(-1,-1);
    while (true)
    {
        //得到离起始点最近的点(如果是第一次执行, 得到的是起点)
        _node = getMinPathFormOpenList();
        if (!_node)
        {
            break;
        }
        //把计算过的点从开放列表中删除
        removeObjFromOpenList( _node);
        int _x = _node->m_x;
        int _y = _node->m_y;
        
        //
        Vec2 _point[4] = {Vec2(_x, _y+1),Vec2(_x, _y-1),Vec2(_x+1, _y),Vec2(_x -1, _y)};
        for (int i = 0 ; i < 4; i++)
        {
            //路径列表中有该点
            if (!((int)_point[i].x <0 || (int)_point[i].y <0 || (int)_point[i].x >= m_roadInspectArray.size() ||(int)_point[i].y >= m_roadInspectArray[0].size() ))
            {
                if(m_roadInspectArray[(int)_point[i].x][(int)_point[i].y])
                {
                    _endPoint = _point[i];
                    goto B;
                }
            }
        }
        
        //检测8个方向的相邻节点是否可以放入开放列表中
        PathSprite* _adjacent = NULL;
        
        _adjacent = getObjFromInspectArray(m_obstaclesInspectArray,  _x +1, _y);
        inspectTheAdjacentNodes(_node, _adjacent);
        
        _adjacent = getObjFromInspectArray( m_obstaclesInspectArray, _x , _y -1);
        inspectTheAdjacentNodes(_node, _adjacent);
        
        _adjacent = getObjFromInspectArray( m_obstaclesInspectArray, _x -1, _y);
        inspectTheAdjacentNodes(_node, _adjacent);
        
        _adjacent = getObjFromInspectArray( m_obstaclesInspectArray, _x , _y+1);
        inspectTheAdjacentNodes(_node, _adjacent);
        
        _adjacent = getObjFromInspectArray( m_obstaclesInspectArray, _x + 1, _y + 1);
        inspectTheAdjacentNodes(_node, _adjacent);
        
        _adjacent = getObjFromInspectArray( m_obstaclesInspectArray, _x +1, _y-1);
        inspectTheAdjacentNodes(_node, _adjacent);
        
        _adjacent = getObjFromInspectArray( m_obstaclesInspectArray, _x -1, _y - 1);
        inspectTheAdjacentNodes(_node, _adjacent);
        
        _adjacent = getObjFromInspectArray( m_obstaclesInspectArray, _x -1, _y+1);
        inspectTheAdjacentNodes(_node, _adjacent);
    }
B:
    clearPath();
    return _endPoint;
}

PathSprite* PathSearchLogic::getMinPathFormOpenList()
{
	if (m_openList.size()>0) {
		PathSprite* _sp =* m_openList.begin();
		for ( std::vector<PathSprite*>::iterator iter = m_openList.begin(); iter !=  m_openList.end(); iter++)
		{
			if ((*iter)->m_FValue < _sp->m_FValue)
			{
				_sp = *iter;
			}
		}
		return _sp;
	}
	else
	{
		return NULL;
	}

}

PathSprite* PathSearchLogic::getObjFromInspectArray( std::vector< std::vector<PathSprite*>>& InspectArray, int x, int y )
{
	if (x >=0 && y >=0 && x < m_mapSize.width && y < m_mapSize.height) {
		return InspectArray[x][y];
	}
	return  NULL;
}

void PathSearchLogic::inspectTheAdjacentNodes( PathSprite* node, PathSprite* adjacent, PathSprite* endNode )
{
	if (adjacent)
	{
		float _x = abs(endNode->m_x - adjacent->m_x);
		float _y = abs(endNode->m_y - adjacent->m_y);

		float F , G, H1, H2, H3;
		G = adjacent->m_costToSource = node->m_costToSource + calculateTwoObjDistance(node, adjacent);//获得累计的路程

		//三种算法, 感觉H2不错
		H1 = _x + _y;
		H2 = hypot(_x, _y);
		H3 = fmax(_x, _y);

        switch (m_algorithm)
        {
            case SEARCH_PATH_ASTAR:
                F = G + H1;
                break;
            case SEARCH_PATH_DIJKSTRA:
                F = G;
                break;
            case SEARCH_PATH_PRIORITY:
                F = H2;
                break;
                
            default:
                break;
        }
		adjacent->m_FValue = F;

		adjacent->m_parent = node;//设置父节点


		m_haveInspectRoadList.push_back(adjacent);
		node->m_child = adjacent;//设置子节点

		m_roadInspectArray[adjacent->m_x][adjacent->m_y] = NULL;//把检测过的点从检测列表中删除
		m_openList.push_back(adjacent);//加入开放列表
	}
}
void PathSearchLogic::inspectTheAdjacentNodes( PathSprite* node, PathSprite* adjacent )
{
    if (adjacent)
    {
        
        float F , G;
        G = adjacent->m_costToSource = node->m_costToSource + calculateTwoObjDistance(node, adjacent);//获得累计的路程
        
        
        //Dijkstra算法
        F = G;

        adjacent->m_FValue = F;
        
        adjacent->m_parent = node;//设置父节点
        
        
        m_haveInspectObstaclesList.push_back(adjacent);
        node->m_child = adjacent;//设置子节点
        
        m_obstaclesInspectArray[adjacent->m_x][adjacent->m_y] = NULL;//把检测过的点从检测列表中删除
        m_openList.push_back(adjacent);//加入开放列表
    }
}

float PathSearchLogic::calculateTwoObjDistance( PathSprite* obj1, PathSprite* obj2 )
{

	float _x = abs(obj2->m_x - obj1->m_x);
	float _y = abs(obj2->m_y - obj1->m_y);

	return _x + _y;
}

void PathSearchLogic::clearPath()
{
	resetInspectArray();

	//把移除了障碍物的地图放入检测列表中
	m_openList.clear();
//	m_pathList.clear();
	m_haveInspectRoadList.clear();
    m_haveInspectObstaclesList.clear();

}

void PathSearchLogic::resetInspectArray()
{
	for (std::vector<PathSprite*>::iterator iter = m_haveInspectRoadList.begin(); iter != m_haveInspectRoadList.end(); iter++)
	{
		(*iter)->m_costToSource = 0;
		(*iter)->m_FValue = 0;
		(*iter)->m_parent = NULL;
		(*iter)->m_child = NULL;

		m_roadInspectArray[(*iter)->m_x][(*iter)->m_y] = (*iter);
	}
    for (std::vector<PathSprite*>::iterator iter = m_haveInspectObstaclesList.begin(); iter != m_haveInspectObstaclesList.end(); iter++)
    {
        (*iter)->m_costToSource = 0;
        (*iter)->m_FValue = 0;
        (*iter)->m_parent = NULL;
        (*iter)->m_child = NULL;
        
        m_obstaclesInspectArray[(*iter)->m_x][(*iter)->m_y] = (*iter);
    }
}

bool PathSearchLogic::removeObjFromOpenList( PathSprite* sprite )
{
	if (!sprite) {
		return  false;
	}
	for ( std::vector<PathSprite*>::iterator iter = m_openList.begin(); iter !=  m_openList.end(); iter++)
	{
		if (*iter == sprite)
		{
			m_openList.erase(iter);
			return true;
		}
	}
	return false;

}  
bool PathSearchLogic::detectWhetherCanPassBetweenTwoPoints( Vec2 p1, Vec2 p2 )
{ 
	float _maxX = p1.x>p2.x?p1.x:p2.x;
	float _maxY = p1.y>p2.y?p1.y:p2.y;
	float _minX = p1.x<p2.x?p1.x:p2.x;
	float _minY = p1.y<p2.y?p1.y:p2.y;

	if (p1.x == p2.x)
	{
		if (_maxY - _minY >1)
		{
			return false;
		}
		float _x = p1.x;
		for (int _y = _minY; _y <=_maxY; _y++)
		{
			PathSprite*_sp = m_roadInspectArray[(int)_x][(int)(_y)];
			if (!_sp)
			{
				return false;
			} 
		}

	}
	else if (p1.y == p2.y)
	{
		if (_maxX - _minX > 1)
		{
			return false;
		}
		float _y = p1.y;
		for (int _x = _minX; _x <=_maxX; _x++ )
		{
			PathSprite*_sp = m_roadInspectArray[(int)_x][(int)(_y)];
			if (!_sp)
			{
				return false;
			} 
		}
	}
	else
	{
		for (int _y = _minY; _y <= _maxY; _y++)
		{
			for (int _x = _minX; _x <= _maxX; _x++)
			{
				float _length = MathLogic::linearEquationWithOneUnknown_solveShortLenghtRequiredPoint(p1, p2, Vec2(_x, _y));
				float _maxLength = MathLogic::calculateLengthRequiredTwoPoint(Vec2(0,0), Vec2(0.5,0.5));
				if (_length < _maxLength)
				{
					PathSprite*_sp = m_roadInspectArray[(int)_x][(int)(_y)];
					if (!_sp)
					{
						return false;
					} 
				}

			}
		}
	}

	return true;
}
Vec2 PathSearchLogic::resetObjPosition(Vec2 point )
{
    PathSprite* _sp = m_roadInspectArray[point.x][point.y];
    
    if (_sp)
    {
        return point;
    }
    else
    {
        Vec2 _PArray[4] = {point + Vec2(0, -1),point +  Vec2(0, 1), point + Vec2(-1, 0), point + Vec2(1, 0)};
        
        for (int i = 0 ; i < 4 ; i++)
        {
            PathSprite* _up = m_roadInspectArray[_PArray[i].x][_PArray[i].y];
            if (_up)
            {
                return _PArray[i];
            }
        }
    }
    return point;
}