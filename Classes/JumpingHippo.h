#ifndef __JumpingHippo_SCENE_H__
#define __JumpingHippo_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class JumpingHippo : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    Sprite* hippoSprite;
    
    void initHippoSprite();
    
    void initSpawner();
    
    void initClickListener();
    
    JumpingHippo* context = this;

    void inicializarFisica(cocos2d::Sprite* sprite);
    
    void initScore();
    
    int score = 0;
    
    Label *scoreLabel = Label::create();

    
    CREATE_FUNC(JumpingHippo);
    
private:
    bool isJumping = false;
    
};

#endif // JumpingHippo
