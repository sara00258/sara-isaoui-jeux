#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "LevelObject.h"
#include "Box2D/Box2D.h"
using namespace cocos2d;

class Player : public LevelObject
{
public:
	void addBodyToWorld(b2World* world);
	void addFixturesToBody();
};

void Player::addBodyToWorld(b2World* world)
{
    // let superclass to the work, we just need to set the player to be
    // a bullet so it doesn't fall through the world on huge updates
    LevelObject::addBodyToWorld(world);
    body->SetBullet(true);
}

void Player::addFixturesToBody()
{
    this->addCircularFixtureToBody(0.7f);
}

#endif // __MAIN_MENU_H__