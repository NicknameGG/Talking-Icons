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
	if (!Loader::get()->isModLoaded("iristraa.mainmenuwallpaper")) {
		bool init() {
			if (!MenuGameLayer::init())
				return false;
			
			iconLabel = IconDialogLabel::create("I hate my job", "bigFont.fnt", this->m_playerObject);
			iconLabel->setScale(0.4);
			this->addChild(iconLabel);
	
			iconLabel->iconRespawned();
	
			return true;
		} 
		
		if (m_playerObject->isVisible()) {
			void resetPlayer() {
				MenuGameLayer::resetPlayer();
				if (iconLabel)
					iconLabel->iconRespawned();
			}
		
			void destroyPlayer() {
				if (iconLabel) {
					IconDialogPopup::create(this->m_playerObject)->show();
		        }
		
				MenuGameLayer::destroyPlayer();
			}
		}
	}
};

$on_mod(Loaded) {
	PhrasesLoader::loadPhrases();
}
