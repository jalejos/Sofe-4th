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
    initScore();
    return true;
}

auto scoreLabel = Label::create();

void JumpingHippo::initScore(){
    Size size = Director::getInstance()->getVisibleSize();
//    scoreLabel = Label::create();
    scoreLabel->setScale(1.f/0.85, 2.f);
    scoreLabel->setString("Score: " + std::to_string(score));
    scoreLabel->setPosition(Vec2(size.width - scoreLabel->getContentSize().width, size.height - scoreLabel->getContentSize().height));
    this->addChild(scoreLabel);
}

void JumpingHippo::initHippoSprite()
{
    hippoSprite = Sprite::create("Hippo.png");
    
    hippoSprite->setPosition(Director::getInstance()->getVisibleSize()/2);
    hippoSprite->setScale(0.1f);
    inicializarFisica(hippoSprite);
    addChild(hippoSprite, 1);
    
}

void JumpingHippo::initSpawner()
{
    auto size = Director::getInstance()->getVisibleSize();
    schedule([=](float dt){
        
        Sprite* spikesSprite = Sprite::create("SpikeBall.png");
        inicializarFisica(spikesSprite);
        context->addChild(spikesSprite);
        
        spikesSprite->setScale(0.25f);
        spikesSprite->setPosition(Vec2(size.width, size.height/2));
        
//        CCJumpTo* jumpTo = CCJumpTo::create(1,ccp(x/6,y/8),y/1.2f,1);
//        auto jump = JumpBy::create(0.8, Vec2(size.width/3.0 , 0), 150, 1);
        auto callbackMoveToLeft = CallFunc::create([=](){
            score += score;
            scoreLabel->setString("Score: " + std::to_string(score));
            this->removeChild(spikesSprite);

        });
        auto moveToLeft = MoveTo::create(2.f, Vec2(-spikesSprite->getContentSize().width , size.height/2));
//        auto seq = Sequence::create(jump, jump, jump, callbackMoveToLeft, nullptr);
        auto seq = Sequence::create(moveToLeft, callbackMoveToLeft, nullptr);
//        auto seq2 = Sequence::create(jump, jump, jump, nullptr);
//        spikesSprite->runAction(moveToLeft);
        spikesSprite->runAction(seq);
//        spikesSprite->runAction(seq2);

        
    }, 1.f, CC_REPEAT_FOREVER, 1.f, "spawnerCallBack");
}

void JumpingHippo::initClickListener()
{
    auto mouseListener = EventListenerTouchOneByOne::create();
    
    mouseListener->onTouchBegan = [=](Touch* touch, Event* event){
        
        if(!isJumping){
            
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
            audio->playEffect("sound/jump.mp3");
            isJumping = true;
            //reinicia la rotacion del hippo en cada click
            hippoSprite ->setRotation(0.0f);
            
            auto jump = JumpBy::create(0.8, Vec2::ZERO, 150, 1);
            //rotar 360 grados
            auto rotateBy = RotateBy::create(0.8f, 360.0f);
            
            auto callbackJump = CallFunc::create([=](){
                isJumping = false;
            });
            
            auto mySpawn = Spawn::createWithTwoActions(jump, rotateBy);
            auto seq = Sequence::create(mySpawn, callbackJump, nullptr);
            
            hippoSprite->runAction(seq);
            //            return true;
            
        }
        return true;
    };
    mouseListener->onTouchMoved = [=](Touch* touch, Event* event){};
    
    mouseListener->onTouchEnded = [=](Touch* touch, Event* event){};
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void JumpingHippo::inicializarFisica(cocos2d::Sprite* sprite){
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
    body -> setContactTestBitmask(true);
    body -> setDynamic(true);
    sprite -> setPhysicsBody(body);
}


