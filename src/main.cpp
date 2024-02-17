#include <Geode/Geode.hpp>
#include <Geode/modify/MenuGameLayer.hpp>
#include <Geode/modify/MoreOptionsLayer.hpp>
#include <Geode/loader/Loader.hpp>

#include "IconDialogLabel.hpp"
#include "IconDialogPopup.hpp"

#include <chrono>

using namespace geode::prelude;

IconDialogLabel* iconLabel = nullptr;

class $modify(MenuGameLayer) {
		bool init() {
			if (!MenuGameLayer::init())
				return false;

			if (this->m_playerObject->isVisible())
			{
				iconLabel = IconDialogLabel::create("", "bigFont.fnt", this->m_playerObject);
				iconLabel->setScale(0.4);
				this->addChild(iconLabel);
		
				iconLabel->iconRespawned();
			} else if (!this->m_playerObject->isVisible()) {
				iconLabel->setVisible(false);
			}

			return true;
		} 

		void resetPlayer() {
			MenuGameLayer::resetPlayer();
			if (iconLabel && this->isVisible() && m_playerObject->isVisible()) {
				iconLabel->iconRespawned();
			}
		}
				
		
		void destroyPlayer() {
			if (iconLabel && this->isVisible() && m_playerObject->isVisible()) {
				IconDialogPopup::create(this->m_playerObject)->show();
		    }
		
			MenuGameLayer::destroyPlayer();
		}
	};

$on_mod(Loaded) {
	PhrasesLoader::loadPhrases();
}
