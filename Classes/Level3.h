#ifndef __LEVEL3_H__
#define __LEVEL3_H__

#include "cocos2d.h"
#include<chrono>

using namespace cocos2d;

class Level3 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
  
    // implement the "static create()" method manually
    CREATE_FUNC(Level3);


};

#endif // __MAIN_MENU_H__
