#include "PathData.h"

std::vector< std::vector<PathSprite*>> PathData::m_opcityInspectArray;

std::vector< std::vector<PathSprite*>> PathData::m_obstaclesInspectArray;

std::vector< std::vector<PathSprite*>> PathData::m_roadInspectArray;

MapPathXML PathData::m_opcityPathXml;

MapPathXML PathData::m_obstaclesPathXml;

MapPathXML PathData::m_roadPathXml;


PathData::PathData(void)
{
}


PathData::~PathData(void)
{
}

void PathData::createPathData( std::string mapXMLPath )
{
	getPathdataFromXML(mapXMLPath);

	{
		std::string & _str = m_roadPathXml.m_data;
		int  _width = m_roadPathXml.m_size.width;
		int  _height = m_roadPathXml.m_size.height;
		int index = 0;

		for (int j = 0;  j < _width; j++) {
			std::vector<PathSprite*> _pathSprite;
			m_roadInspectArray.push_back(_pathSprite);
			for (int i = 0;  i < _height; i++) {
				index = j * _height + i;
				if (_str[index]=='1') {

					PathSprite* _pathSprite = new PathSprite();
					_pathSprite->m_x = j;
					_pathSprite->m_y =i;

					m_roadInspectArray[j].push_back(_pathSprite); //把地图中所有的点一一对应放入检测列表中
				}
				else
				{
					m_roadInspectArray[j].push_back(NULL);
				}
			}
		}	
	}
	{
		std::string & _str = m_obstaclesPathXml.m_data;
		int  _width = m_obstaclesPathXml.m_size.width;
		int  _height = m_obstaclesPathXml.m_size.height;
		int index = 0;

		for (int j = 0;  j < _width; j++) {
			std::vector<PathSprite*> _pathSprite;
			m_obstaclesInspectArray.push_back(_pathSprite);
			for (int i = 0;  i < _height; i++) {
				index = j * _height + i;
				if (_str[index]=='1') {

					PathSprite* _pathSprite = new PathSprite();
					_pathSprite->m_x = j;
					_pathSprite->m_y =i;

					m_obstaclesInspectArray[j].push_back(_pathSprite); //把地图中所有的点一一对应放入检测列表中
				}
				else
				{
					m_obstaclesInspectArray[j].push_back(NULL);
				}
			}
		}	
	}
	{
		std::string & _str = m_opcityPathXml.m_data;
		int  _width = m_opcityPathXml.m_size.width;
		int  _height = m_opcityPathXml.m_size.height;
		int index = 0;

		for (int j = 0;  j < _width; j++) {
			std::vector<PathSprite*> _pathSprite;
			m_opcityInspectArray.push_back(_pathSprite);
			for (int i = 0;  i < _height; i++) {
				index = j * _height + i;
				if (_str[index]=='1') {

					PathSprite* _pathSprite = new PathSprite();
					_pathSprite->m_x = j;
					_pathSprite->m_y =i;

					m_opcityInspectArray[j].push_back(_pathSprite); //把地图中所有的点一一对应放入检测列表中
				}
				else
				{
					m_opcityInspectArray[j].push_back(NULL);
				}
			}
		}	
	}
}

void PathData::getPathdataFromXML( std::string mapPath )
{
	//std::string wirtePath      = CCFileUtils::sharedFileUtils()->getWritablePath()+mapPath;//"mapData.xml";
	std::string wirtePath      = CCFileUtils::sharedFileUtils()->fullPathForFilename(mapPath.c_str());
    TiXmlDocument* myDocument = new TiXmlDocument(wirtePath.c_str());
	myDocument->LoadFile();

	TiXmlElement* MapDataElement = myDocument->RootElement();  // MapData
	std::string _strwidth = MapDataElement->Attribute("width");  //获得student的name属性
	std::string _strheight = MapDataElement->Attribute("height");  //获得student的name属性

	m_roadPathXml.m_size.width =std::atoi( _strwidth.c_str() );
	m_roadPathXml.m_size.height =std::atoi( _strheight.c_str() );
	m_obstaclesPathXml.m_size.width =std::atoi( _strwidth.c_str() );
	m_obstaclesPathXml.m_size.height =std::atoi( _strheight.c_str() );
	m_opcityPathXml.m_size.width =std::atoi( _strwidth.c_str() );
	m_opcityPathXml.m_size.height =std::atoi( _strheight.c_str() );
	TiXmlElement* roadDataElement = MapDataElement->FirstChildElement();
	m_roadPathXml.m_data = roadDataElement->GetText();

	TiXmlElement* obstaclesElement = roadDataElement->NextSiblingElement();
	m_obstaclesPathXml.m_data = obstaclesElement->GetText();

	TiXmlElement* opcityElement = obstaclesElement->NextSiblingElement();
	m_opcityPathXml.m_data = opcityElement->GetText();

	delete myDocument;
}

