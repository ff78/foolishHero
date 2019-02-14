//
//  Hero.cpp
//  foolishHero-mobile
//
//  Created by ff on 2018/12/10.
//

#include "Hero.hpp"
#include "GameDefine.h"
#include "GameUtils.h"
#include "MathAide.h"

USING_NS_CC;
using namespace cocostudio;
using namespace timeline;
using namespace ui;
using namespace spine;

Hero::Hero():
originArmAngle(0),
originHeadAngle(0)
{
    currState = MAX;
    originState = MAX;
    lastState = MAX;
    headRect = Rect::ZERO;
}

Hero::~Hero()
{
    currState = MAX;
    originState = MAX;
    lastState = MAX;
}

bool Hero::init()
{
    if (!Node::init()) {
        return false;
    }
    
    curveId = 0;

    return true;
}

void Hero::onEnter()
{
    Node::onEnter();
}

void Hero::updateState()
{
    
}

void Hero::update(float dt)
{
    getHeadBB();
}

void Hero::changeState(HERO_STATES nextState)
{
    if(currState == nextState)
        return;
    log("change hero state from %d to %d", currState, nextState);
    exitState(currState);
    lastState    = currState;
    currState    = nextState;
    enterState(nextState);
}

void Hero::enterState(HERO_STATES nextState)
{
    switch (nextState) {
        case STAND:
        {
            skeletonNode->setEmptyAnimation(0, 0.4);
            skeletonNode->setMix("hoverboard", "walk", 0.4);
            skeletonNode->setMix("walk", "idle", 0.4);
            skeletonNode->setAnimation(0, "hoverboard", true);
            skeletonNode->addAnimation(0, "walk", false, 1);
            skeletonNode->addAnimation(0, "idle", true);
//            playerAction->play("stand", true);
        }
            break;
            
        case DRAW:
        {
//            playerAction->play("walk", false);
//            skeletonNode->setMix("idle", "aim", 0.4);
            originHeadAngle = skeletonNode->findBone("head")->data->rotation;
            originArmAngle = skeletonNode->findBone("rear-upper-arm")->data->rotation;
//            skeletonNode->setEmptyAnimation(0, 0.4);
            skeletonNode->setAnimation(0, "idle", true);
        }
            break;
            
        case LOOSE:
        {
            originHeadAngle = skeletonNode->findBone("head")->data->rotation;
            originArmAngle = skeletonNode->findBone("rear-upper-arm")->data->rotation;
//            skeletonNode->setEmptyAnimation(0, 0);
//            skeletonNode->setMix("idle", "shoot", 0.1);
            spTrackEntry *shootTrack = skeletonNode->setAnimation(1, "shoot", false);
            skeletonNode->setTrackCompleteListener(shootTrack, CC_CALLBACK_1(Hero::endLoose, this));
            //            playerAction->play("walk_fire", false);
            //            playerAction->setAnimationEndCallFunc("walk_fire", CC_CALLBACK_0(Hero::back2Stand, this));
        }
            break;
            
        default:
            break;
    }
}

void Hero::exitState(HERO_STATES currState)
{
    switch (currState) {
        case DRAW:
        {
            auto torso = skeletonNode->findBone("rear-upper-arm");
            torso->data->rotation = originArmAngle;
            auto head = skeletonNode->findBone("head");
            head->data->rotation = originHeadAngle;
            
        }
            break;
        case LOOSE:
        {
            auto torso = skeletonNode->findBone("rear-upper-arm");
            torso->data->rotation = originArmAngle;
            auto head = skeletonNode->findBone("head");
            head->data->rotation = originHeadAngle;
        }
            break;
            
        default:
            break;
    }
}

void Hero::changeActionWithName(int nextAction)
{
    
}

void Hero::doFlag(int nextFlag)
{
    
}


void Hero::drawBow(float emitAngle, float velocity)
{
    changeState(DRAW);
}

void Hero::adjustBow(float emitAngle, float velocity)
{
//    skeletonNode->updateWorldTransform();
    auto torso = skeletonNode->findBone("rear-upper-arm");
//    torso->rotation = 180+emitAngle;
    torso->data->rotation = 180+emitAngle;
    auto head = skeletonNode->findBone("head");
//    head->rotation = emitAngle;
    head->data->rotation = emitAngle;
//    ->rotation = emitAngle;
//    skeletonNode->findBone("rear-upper-arm")->rotation = emitAngle;
//    skeletonNode->updateWorldTransform();
}

void Hero::loose(float emitAngle, float velocity)
{
    changeState(LOOSE);
    
    auto torso = skeletonNode->findBone("rear-upper-arm");
    torso->data->rotation = 180+emitAngle;
    auto head = skeletonNode->findBone("head");
    head->data->rotation = emitAngle;
}

void Hero::setupView(std::string res)
{
//    player = CSLoader::createNode(res.c_str());
//    playerAction = CSLoader::createTimeline(res.c_str());
//    addChild(player);
//    player->setScale(0.2);
//    player->runAction(playerAction);
//
//    auto body = player->getChildByName("Layer15");
//    auto head = body->getChildByName("Layer14");
//    auto arrow = Sprite::create("baobingjianbody.png");
//    arrow->setLocalZOrder(-1);
//    arrow->setScale(10);
//    head->addChild(arrow);
//    auto sum = body->getRotation();
//    sum += head->getRotation();
//    float arrowAngle = 20;
//    arrow->setRotation(-sum-arrowAngle);
//
//    player->setScaleX(flipX?0.2:-0.2);
    

    
//    //获得数据
//    spAtlas* _atlas = spAtlas_createFromFile("spineboy.atlas", 0);
//    spSkeletonJson* _json = spSkeletonJson_create(_atlas);
//    auto spData = spSkeletonJson_readSkeletonDataFile(_json , "spineboy-pro.json");
//    //创建
//    skeletonNode = SkeletonAnimation::createWithData(spData);
    skeletonNode = SkeletonAnimation::createWithJsonFile("spineboy-pro.json", "spineboy.atlas", 0.2);
    
    skeletonNode->setStartListener( [] (spTrackEntry* entry) {
        log("%d start: %s", entry->trackIndex, entry->animation->name);
    });
    skeletonNode->setInterruptListener( [] (spTrackEntry* entry) {
        log("%d interrupt", entry->trackIndex);
    });
    skeletonNode->setEndListener( [] (spTrackEntry* entry) {
        log("%d end", entry->trackIndex);
    });
    skeletonNode->setCompleteListener( [] (spTrackEntry* entry) {
        log("%d complete", entry->trackIndex);
    });
    skeletonNode->setDisposeListener( [] (spTrackEntry* entry) {
        log("%d dispose", entry->trackIndex);
    });
    skeletonNode->setEventListener( [] (spTrackEntry* entry, spEvent* event) {
        log("%d event: %s, %d, %f, %s", entry->trackIndex, event->data->name, event->intValue, event->floatValue, event->stringValue);
    });
    
//    skeletonNode->setMix("idle", "walk", 0.4);
//    skeletonNode->setMix("walk", "hoverboard", 0.4);
//    skeletonNode->setAnimation(0, "idle", true);
//    spTrackEntry* walkEntry = skeletonNode->addAnimation(0, "walk", false, 1);
//    skeletonNode->addAnimation(0, "hoverboard", true);
//
//    skeletonNode->setTrackStartListener(walkEntry, [] (spTrackEntry* entry) {
//        log("walked!");
//    });
    
    skeletonNode->setPosition(Vec2(_contentSize.width / 2, 20));
    skeletonNode->setScaleX(flipX?-1:1);
    addChild(skeletonNode);
    
    changeState(HERO_STATES::STAND);
    
    headCollide = DrawNode::create();
    headCollide->clear();
    addChild(headCollide);
    
    scheduleUpdate();
}

void Hero::back2Stand()
{
    changeState(STAND);
}

void Hero::getHeadBB()
{
    headRect = skeletonNode->getBoundingBoxForBone("head-bb", "head");
//    log("head bound:{xMin = %.2f, yMin = %.2f, width = %.2f, height = %.2f}", rect.getMinX(), rect.getMinY(),
//        rect.getMaxX()-rect.getMinX(), rect.getMaxY()-rect.getMinY());
    headCollide->clear();
    headCollide->drawRect(headRect.origin, headRect.origin+headRect.size, Color4F::GREEN);
}

void Hero::endLoose(spTrackEntry *entry)
{
    back2Stand();
}

int Hero::hitCheck(Vec2 arrowCenter, float angle, Size arrowSize)
{
    if(MathAide::rectHitTest(arrowCenter, arrowSize, angle, getPosition() + headRect.origin+headRect.size/2, headRect.size, 0))
    {
        return 1;
    }
    return 0;
}
