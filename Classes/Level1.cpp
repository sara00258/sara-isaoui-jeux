#include "Level1.h"
#include "Definition.h"
#include "MainMenu.h"
#include "CCEventKeyboard.h"
#include <map>
#include <iostream>

USING_NS_CC;
using namespace std;

#define __FLT_EPSILON__ 1.19209290e-07F
float _filteredUpdateDelta;

float sale = -1;
int isJumping = 0;
int mapsize = 0;


Scene* Level1::createScene()
{
    return Level1::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Level1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    initWithPhysics();
    auto sceneWorld = getPhysicsWorld();
    sceneWorld->setGravity(Vec2(0,-98));
    sceneWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);




//Ajouter un background 

//ajouter Tile Map 
    map_level1 = TMXTiledMap::create("mytile.tmx");

    float XX = map_level1->getPosition().x;
    float YY = map_level1->getPosition().y;

    _background1 = map_level1->getLayer("Level1");
    _blockage = map_level1->getLayer("Blockage01");

    addChild(map_level1 ,-1);

//importer le point de Spawn de joueur de tile map au cocos2d avec la fonction getObjectGroup 
    TMXObjectGroup* objects = map_level1->getObjectGroup("Object-player");
    auto playerShowUpPoint = objects->getObject("PlayerShowUpPoint");
    float x = playerShowUpPoint["x"].asFloat();
    float y = playerShowUpPoint["y"].asFloat();

   
//ajouter le joueur au Tile Map et le positionné sur l'objet "PlayerShowUpPoint"
     _player = Sprite::create("Picopark player.png");
    _player->setScale(0.75);
    auto player_body = PhysicsBody::createBox(_player->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    player_body->setDynamic(true);
    player_body->setRotationEnable(false);
    player_body->setContactTestBitmask(1);
    player_body->setContactTestBitmask(true);

    _player->setPosition(x , y );
    setViewPointCenter(_player->getPosition());
    _player->setPhysicsBody(player_body);
    this->addChild(_player);



    auto test = objects->getObject("test");
   
    std::vector<Vec2>vectors;
    vectors.push_back(Vec2(0, 0));
    vectors.push_back(Vec2(2098.5, -2));
    vectors.push_back(Vec2(2099.5, 277));
    vectors.push_back(Vec2(-0.5, 277.5));

    for (int x = 0; x < 70; x++)       //width of map
    {
        for (int y = 0; y < 32; y++)   //height of map
        {
            auto spriteTile = _background1->getTileAt(Vec2(x, y));
            if (spriteTile != NULL)
            {
                PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(20, 20), PhysicsMaterial(0.0f , 0.0f , 0.0f));
                tilePhysics->setDynamic(false); //static is good enough for wall
                tilePhysics->setGravityEnable(false);
                tilePhysics->setCollisionBitmask(2);
                tilePhysics->setContactTestBitmask(true);
                spriteTile->setPhysicsBody(tilePhysics);
            }
        }
    }

    /////////////////////////////////////////keyBoard///////////////////////////////////
    Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
    auto eventListener = EventListenerKeyboard::create();
    EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

    eventListener->onKeyPressed = CC_CALLBACK_2(Level1::onKeyPressed, this);
    eventListener->onKeyReleased = CC_CALLBACK_2(Level1::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    this->scheduleUpdate();

    /////////////////////////////////////////////////////////////////////////////////////////


    return true;
}

bool Level1::onContactPreSolve(PhysicsContact& contact , PhysicsContactPreSolve& solve)
{
    solve.setRestitution(0);
    
    return true;
}

void Level1::onKeyPressed(EventKeyboard::KeyCode keyCode , Event *event)
{

        if (keys.find(keyCode) == keys.end())
        {
            keys[keyCode] = std::chrono::system_clock::now();
        }

}

void Level1::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

    keys.erase(keyCode);

}

void Level1::update(float delta)
{
    X = _player->getPosition().x;
    Y = _player->getPosition().y;
    float translate = 100.0 * delta;

    if (keys.find(EventKeyboard::KeyCode::KEY_LEFT_ARROW) != keys.end() ||
        keys.find(EventKeyboard::KeyCode::KEY_A) != keys.end())
    {
        X = X - translate;
        _player->setPosition(X, Y);
    }

    else 
    if(keys.find(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) != keys.end() ||
    keys.find(EventKeyboard::KeyCode::KEY_D) != keys.end())
    {
        X = X + translate;
        _player->setPosition(X, Y);
        
    }

    else if(keys.find(EventKeyboard::KeyCode::KEY_UP_ARROW) != keys.end() ||
        keys.find(EventKeyboard::KeyCode::KEY_W) != keys.end())
    {
        Y = Y + translate;
        _player->getPhysicsBody()->applyImpulse(Vec2(_player->getPosition().x, 100));
    }

    else if(keys.find(EventKeyboard::KeyCode::KEY_DOWN_ARROW) != keys.end() ||
        keys.find(EventKeyboard::KeyCode::KEY_S) != keys.end())
    {
        if (isJumping == 0)
        {
            _player->getPhysicsBody()->setVelocityLimit(70);
            _player->getPhysicsBody()->applyImpulse(Vec2(0, 3500));

            auto delayAction = DelayTime::create(0.5);
            auto funcCallback1 = CallFunc::create([&]() {Level1::changeGravity(); });
            this->runAction(Sequence::create(delayAction, funcCallback1, NULL));

        }
    }
    Rect mapsize = map_level1->getBoundingBox();
    auto followplayer = Follow::create(_player, mapsize);
    this->runAction(followplayer);

}


void Level1::changeIsJumping()
{
    isJumping = 0;
    getPhysicsWorld()->setGravity(Vec2(0, -98));

}

void Level1::changeGravity()
{
    getPhysicsWorld()->setGravity(Vec2(0, -20000));
}
void Level1::setViewPointCenter(Point position) {
    auto winSize = Director::getInstance()->getWinSize();

    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);
    x = MIN(x, (map_level1->getMapSize().width * this->map_level1->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (map_level1->getMapSize().height * map_level1->getTileSize().height) - winSize.height / 2);
    auto actualPosition = Point(x, y);

    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
    auto viewPoint = centerOfView - actualPosition;
    this->setPosition(viewPoint);
}

Point Level1::tileCoordForPosition(Point position)
{
    int x = position.x / map_level1->getTileSize().width;
    int y = ((map_level1->getMapSize().height * map_level1->getTileSize().height) - position.y) / map_level1->getTileSize().height;
    return Point(x, y);
}

void Level1::setPlayerPosition(Point position )
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = map_level1->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            string collision = properties["Blockage"].asString();
                if ("true" == collision) {
                    return;
                    
                }
        }
    }
    _player->setPosition(position);
}

void Level1::updatePhysics(float delta)
{
    const int phyiscsSubSteps = 3;
    float dt = delta / static_cast<float>(phyiscsSubSteps);
    _filteredUpdateDelta = dt > __FLT_EPSILON__ ? 0.15 * dt + 0.85 * _filteredUpdateDelta : 0.0;
    for (int i = phyiscsSubSteps; i > 0; i--)
    {
        sceneWorld->step(_filteredUpdateDelta);
    }
}
