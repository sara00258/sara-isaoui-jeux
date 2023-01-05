#include "MainMenu.h"
#include "GameOverScene.h"

USING_NS_CC;
using namespace ui;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Ajouter un background
    auto background = Sprite::create("GameOver.jpg");

    //Positionnement du Background au centre
    background->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(background);

    //calcule de factor pour mettre le background selon la taille de l'ecran
    float rX = visibleSize.width / background->getContentSize().width;
    float rY = visibleSize.height / background->getContentSize().height;

    background->setScaleX(rX);
    background->setScaleY(rY);

    // add a "restart" button to go back to the main menu
    auto restartItem = MenuItemFont::create("Restart", CC_CALLBACK_1(GameOverScene::menuRestartCallback, this));
    restartItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2 - 50));
    auto menu = Menu::create(restartItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void GameOverScene::menuRestartCallback(Ref* pSender)
{
    // replace the game over scene with the main menu scene
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}
