//
//  MoveSprite.cpp
//  AstarTiledMap
//
//  Created by TinyUlt on 15/5/22.
//
//

#include "MoveSprite.h"
bool MoveSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    m_pathIndex = 0;
    this->initWithFile("r1.png");
    this->setPosition(Vec2(500,500));
    
    return true;
}

void MoveSprite::startMove(std::vector<Vec2> pathList)
{
    m_pathIndex = 1;
    m_pathList = pathList;

    stopAllActions();
    moving();
}

void MoveSprite::moving()
{
    if (m_pathList.size() > m_pathIndex)
    {
        auto _start = this->getPosition();
        float _lenth = (m_pathList[m_pathIndex] - _start).length();
        float _time = _lenth * 0.005f;
        this->runAction(Sequence::create(MoveTo::create(_time, m_pathList[m_pathIndex]), CallFunc::create(std::bind(&MoveSprite::moving, this)), NULL));
        m_pathIndex++;
    }
    else
    {
        //done
    }
   
}