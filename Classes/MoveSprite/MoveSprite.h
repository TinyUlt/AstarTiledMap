//
//  MoveSprite.h
//  AstarTiledMap
//
//  Created by TinyUlt on 15/5/22.
//
//

#ifndef __AstarTiledMap__MoveSprite__
#define __AstarTiledMap__MoveSprite__

#include "cocos2d.h"
USING_NS_CC;
class MoveSprite:public Sprite
{
public:
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MoveSprite);
    
    void startMove(std::vector<Vec2> pathList);
    void moving();
    
    std::vector<Vec2> m_pathList;
    int m_pathIndex;
        
};
#endif /* defined(__AstarTiledMap__MoveSprite__) */
