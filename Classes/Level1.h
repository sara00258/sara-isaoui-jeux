#ifndef __LEVEL1_H__
#define __LEVEL1_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <chrono>

#define PTM_RATIO 32.0
using namespace cocos2d;

class Level1 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Level1);

    void setViewPointCenter(cocos2d::Point position);
    void update(float delta );
    ////////////////////////////KeyBoard/////////////////////////////
     void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
     void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    //////////////////////////////////////////////////////////////////

    std::map<EventKeyboard::KeyCode, std::chrono::system_clock::time_point> keys;

    float X, Y;

    Point tileCoordForPosition(Vec2 position);
    void setPlayerPosition(Vec2 position);
    void changeIsJumping();
    void changeGravity();
    //////////////////////////////////////////////////////////////////////////////

     void updatePhysics(float delta);

private:

    cocos2d::TMXTiledMap* map_level1;
    cocos2d::TMXLayer *_background1;
    cocos2d::TMXLayer* _blockage;
    cocos2d::Sprite* _player;
    cocos2d::PhysicsWorld* sceneWorld;

    Rect winRect;

    bool onContactBegin(PhysicsContact& contact);
    bool onContactPreSolve(PhysicsContact& contact,
        PhysicsContactPreSolve& solve);
    void onContactPostSolve(PhysicsContact& contact,
        const PhysicsContactPostSolve& solve);
    void onContactSeperate(PhysicsContact& contact);
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
};

#endif // __MAIN_MENU_H__