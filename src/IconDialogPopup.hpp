#pragma once

#include <Geode/Geode.hpp>
#include "PhrasesLoader.hpp"

using namespace geode::prelude;

class IconDialogPopup : public cocos2d::CCLayer { 
public:
  PlayerObject* m_pPlayerObject;
  CCScale9Sprite* m_pBackground;
  std::string m_sPhrase;

  static IconDialogPopup *create(PlayerObject* playerObject) {
    IconDialogPopup *pRet = new IconDialogPopup();
    if (pRet && pRet->init(playerObject)) {
      pRet->autorelease();
      return pRet;
    } else {
      delete pRet;
      pRet = 0;
      return 0;
    }
  };

  CCSprite *clonePlayerSprite() {
        auto middle = CCDirector::get()->getWinSize() / 2;
        PlayerObject* frameContainer = this->m_pPlayerObject;
        CCRenderTexture* frame = CCRenderTexture::create(500, 300);
        CCDirector::get()->getRunningScene()->addChild(frame);

        float oldScale = frameContainer->getScale();
        CCPoint oldpos = frameContainer->getPosition();
        
        // Setup the frame container to be rendered
        frameContainer->setScale(5.0f);
        frameContainer->setPosition(middle);
        frame->setPosition(frameContainer->getPosition());

        // Render the frame to the frameContainer
        frame->begin();
        frameContainer->visit();
        frame->end();

        // return the frameContainer to its original state
        frameContainer->setScale(oldScale);
        frameContainer->setPosition(oldpos);

        CCSprite* clone = CCSprite::createWithTexture(frame->getSprite()->getTexture());
        frame->removeMeAndCleanup(); 
        return clone;
  }

    bool init(PlayerObject* playerObject) {
        if (!CCLayer::init()) return false;
        std::string phrase = PhrasesLoader::getRandomDeathPhrase();
        this->m_sPhrase = phrase.c_str();

        this->m_pPlayerObject = playerObject;
        // Create a background
        m_pBackground = CCScale9Sprite::create("transparentSquare.png"_spr);
        m_pBackground->setContentSize({ 380.0f, 95.0f });
        
        // Position 50 px from bottom, and centered
        m_pBackground->setPosition({ CCDirector::get()->getWinSize().width / 2.0f, 60.0f });

        CCSprite* frameSprite = this->clonePlayerSprite();

        frameSprite->setFlipX(true);
        frameSprite->setRotation(180);
        frameSprite->setScale(0.3f);
        frameSprite->setPosition(ccp(40, 43));
        m_pBackground->addChild(frameSprite);

        // Create the label
        auto label = TextArea::create(phrase, "bigFont.fnt", 1, 350, ccp(0, 0), 22.5, true);
        label->setScale(0.6);
        label->setContentSize({300, label->getContentSize().height});
        label->setPosition(m_pBackground->getContentSize() / 2.0f - 10.0f);
        m_pBackground->addChild(label);


        this->addChild(m_pBackground);

        return true;
    }

    CCSequence* createShowSequence() {
        auto fadeIn = CCFadeIn::create(0.25f);
        auto delay = CCDelayTime::create(0.5f);
        auto fadeOut = CCFadeOut::create(1.0f + m_sPhrase.length() * 0.02f);
        auto remove = CCRemoveSelf::create();

        return CCSequence::create(fadeIn, delay, fadeOut, remove, nullptr);
    }

    void show() {
        auto scene = CCDirector::sharedDirector()->getRunningScene();
        // Apply to all children
        scene->addChild(this, 100);

        // Action animations
        this->runAction(createShowSequence());
        m_pBackground->runAction(createShowSequence());

        for (auto child : CCArrayExt<CCNode *>(m_pBackground->getChildren())) {
            child->runAction(createShowSequence());
        }
    }
};