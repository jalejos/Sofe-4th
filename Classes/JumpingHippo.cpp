#include "JumpingHippo.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* JumpingHippo::createScene()
{
    return JumpingHippo::create();
}

bool JumpingHippo::init()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    getPhysicsWorld()->setGravity(Vec2::ZERO);
    
    initHippoSprite();
    initSpawner();
    initClickListener();
    
    return true;
}

void JumpingHippo::initHippoSprite()
{
    hippoSprite = Sprite::create("Hippo.png");
    
    hippoSprite->setPosition(Director::getInstance()->getVisibleSize()/2);
    hippoSprite->setScale(0.1f);
    
    addChild(hippoSprite, 1);
    
}

void JumpingHippo::initSpawner()
{
    auto size = Director::getInstance()->getVisibleSize();
    schedule([=](float dt){
        
        Sprite* spikesSprite = Sprite::create("SpikeBall.png");
        context->addChild(spikesSprite);
        
        spikesSprite->setScale(0.25f);
        spikesSprite->setPosition(Vec2(size.width, size.height/2));
        
        auto moveToLeft = MoveTo::create(2.f, Vec2(0, size.height/2));
        spikesSprite->runAction(moveToLeft);
        
    }, 1.f, CC_REPEAT_FOREVER, 1.f, "spawnerCallBack");
}

void JumpingHippo::initClickListener()
{
    auto mouseListener = EventListenerTouchOneByOne::create();
    
    mouseListener->onTouchBegan = [=](Touch* touch, Event* event){
        //reinicia la rotacion del hippo en cada click
        hippoSprite ->setRotation(0.0f);

        auto jump = JumpBy::create(0.8, Vec2::ZERO, 150, 1);
        //rotar 360 grados
        auto rotateBy = RotateBy::create(0.8f, 360.0f);

        // running the above Actions with Spawn.
        auto mySpawn = Spawn::createWithTwoActions(jump, rotateBy);
        hippoSprite->runAction(mySpawn);
        return true;
    };
    mouseListener->onTouchMoved = [=](Touch* touch, Event* event){};
    
    mouseListener->onTouchEnded = [=](Touch* touch, Event* event){};
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

