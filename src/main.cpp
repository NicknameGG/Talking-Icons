#include <Geode/Geode.hpp>
#include <Geode/modify/MenuGameLayer.hpp>
#include <Geode/modify/MoreOptionsLayer.hpp>

#include "IconDialogLabel.hpp"
#include "IconDialogPopup.hpp"

using namespace geode::prelude;


class $modify(MenuGameLayer) {
	struct Fields {
		IconDialogLabel* m_iconLabel;
	};

	bool init() {
		if (!MenuGameLayer::init())
			return false;
		
		m_fields->m_iconLabel = IconDialogLabel::create("I hate my job", "bigFont.fnt", this->m_playerObject);
		m_fields->m_iconLabel->setScale(0.4);
		this->addChild(m_fields->m_iconLabel);

		m_fields->m_iconLabel->iconRespawned();

		return true;
	} 

	void resetPlayer() {
		MenuGameLayer::resetPlayer();
		if (m_fields->m_iconLabel)
			m_fields->m_iconLabel->iconRespawned();
	}

	void destroyPlayer() {
		if (m_fields->m_iconLabel) {
			auto popup = IconDialogPopup::create(this->m_playerObject);
			popup->setScale(0.5);
			// Center
			popup->setPosition(CCDirector::get()->getWinSize() / 2);
			// Set Y position to * 1.5
			popup->setPositionY(popup->getPositionY() - popup->getPositionY() * .42);
			popup->show();
        }

		MenuGameLayer::destroyPlayer();
	}
};

$on_mod(Loaded) {
	PhrasesLoader::loadPhrases();
}