#ifndef __LEVEL2_H__
#define __LEVEL2_H__

#include "cocos2d.h"
#include<chrono>

using namespace cocos2d;
class Level2 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    float X, Y;
    // implement the "static create()" method manually
    CREATE_FUNC(Level2);

};

#endif // __LEVEL2_H__
