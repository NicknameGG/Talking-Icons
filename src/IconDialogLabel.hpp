#pragma once

#include <Geode/Geode.hpp>
#include "PhrasesLoader.hpp"

using namespace geode::prelude;

class IconDialogLabel : public cocos2d::CCLabelBMFont {
public:
	PlayerObject* m_pFollowObject;
	constexpr static float m_fDistance = 2.4525f - 2.0f;
	std::string phrase = PhrasesLoader::getRandomPhrase();
	bool m_bIsShowing = false;

	static IconDialogLabel* create(const char* text, const char* fontFile, PlayerObject* followNode) {
		IconDialogLabel* label = new IconDialogLabel();
		if (label && label->initWithString(text, fontFile, followNode)) {
			label->autorelease();
			return label;
		}
		CC_SAFE_DELETE(label);
		return nullptr;
	}

	void changePhrase() {
		// Choose a random phrase
		this->phrase = PhrasesLoader::getRandomPhrase();

		// Set the text
		this->setString(this->phrase.c_str());
	}

	bool initWithString(const char* text, const char* fontFile, PlayerObject* followNode) {
		if (!CCLabelBMFont::initWithString(text, fontFile))
			return false;

		this->m_pFollowObject = followNode;
		this->m_pFollowObject->retain();
		this->scheduleUpdate();
		return true;
	}

	void update(float dt) {
		CCPoint pos = this->m_pFollowObject->getPosition();
		// Set this node position to be 5 pixels up the followers
		// content size
		this->setPosition(pos.x, pos.y + this->getContentSize().height);

		if (pos.x > -10.0f && !m_bIsShowing) {
			this->showText();
			m_bIsShowing = true;
		} else if (pos.x > CCDirector::sharedDirector()->getWinSize().width + 50.0f 
					|| pos.x < -10.0f) {
			this->setOpacity(0);
			changePhrase();
		}
	}

    void showText() {
		float playerSpeed = this->m_pFollowObject->m_playerSpeed;
		float time = 0;
		/*
				Speeds:
				0.7
				0.9
				1.3
				1.5

				Formula for fade in depending on speed

		*/
		float seconds = m_fDistance / playerSpeed;
		seconds /= phrase.length();

		for (auto child : CCArrayExt<CCSprite *>(this->getChildren())) {
				child->stopAllActions();
				child->setOpacity(0);
				child->runAction(CCSequence::create(CCDelayTime::create(time),
					CCFadeIn::create(0.05), nullptr));
				time += seconds;
		}
    }

	void iconRespawned() {
		m_bIsShowing = false;
	}
};