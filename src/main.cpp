#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CCScene.hpp>

CCSprite* BigMan = nullptr;

int opacity = 0;

class $modify(PlayerObject) {
	void jumpscare() {
		if (opacity <= 0) {
			opacity = 255;
		}
	BigMan->setOpacity(opacity);
	BigMan->runAction((CCFadeOut::create(1.0)));
	}


	void pushButton(PlayerButton p0) {
		const auto runningScene = CCDirector::get()->getRunningScene();
		PlayerObject::pushButton(p0);

		if (Mod::get()->getSettingValue<bool>("jumpscare")) {
			if (!runningScene->getChildByID("big-man-jumpscare")) {
				BigMan = CCSprite::create("bigman.png"_spr);
				BigMan->setID("big-man-jumpscare");

				BigMan->setScaleX(CCDirector::get()->getWinSize().width / BigMan->getContentSize().width);
				BigMan->setScaleY(CCDirector::get()->getWinSize().height / BigMan->getContentSize().height);

				BigMan->setPosition({CCDirector::get()->getWinSize().width / 2, CCDirector::get()->getWinSize().height / 2});

				runningScene->addChild(BigMan, 100);
				}

				this->jumpscare();
		}
		
	}
};

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		if (Mod::get()->getSettingValue<bool>("menu")) {
			auto BigMan = CCSprite::create("bigman.png"_spr);
			auto menu = this->getChildByID("main-menu-bg");
			BigMan->setScaleX(CCDirector::get()->getWinSize().width / BigMan->getContentSize().width);
			BigMan->setScaleY(CCDirector::get()->getWinSize().height / BigMan->getContentSize().height);
			BigMan->setPosition({CCDirector::get()->getWinSize().width / 2, CCDirector::get()->getWinSize().height / 2});
			menu->addChild(BigMan);
			BigMan->setID("big-man-menu"_spr);
			menu->updateLayout();
		}

		return true;
	}
};

class $modify(CCScene) {
	bool init() {
		if (!CCScene::init()) {
			return false;
		}

		float bigManScale = Mod::get()->getSettingValue<double>("size") * 1.025;

		if (Mod::get()->getSettingValue<bool>("corner")) {
			auto BigMan = CCSprite::create("bigman.png"_spr);
			BigMan->setScaleX(CCDirector::get()->getWinSize().width / BigMan->getContentSize().width / 4 * bigManScale);
			BigMan->setScaleY(CCDirector::get()->getWinSize().height / BigMan->getContentSize().height / 4 * bigManScale);
			BigMan->setPosition({CCDirector::get()->getWinSize().width - 70 * bigManScale, 40 * bigManScale});
			this->addChild(BigMan);
			BigMan->setID("big-man-corner"_spr);
			BigMan->setZOrder(101);
			BigMan->setOpacity(Mod::get()->getSettingValue<double>("opacity"));

			if (Mod::get()->getSettingValue<bool>("corner-text")) {
				auto BigManText = CCLabelBMFont::create("big man", "bigFont.fnt");
				BigManText->setPosition({CCDirector::get()->getWinSize().width - 70 * bigManScale, 40 * bigManScale + (BigMan->getContentSize().height / 4 * bigManScale - BigMan->getContentSize().height / 24 * bigManScale)});
				BigManText->setScaleX(CCDirector::get()->getWinSize().width / BigMan->getContentSize().width / 4 * bigManScale);
				BigManText->setScaleY(CCDirector::get()->getWinSize().width / BigMan->getContentSize().width / 4 * bigManScale);
				BigManText->setExtraKerning(-3);
				this->addChild(BigManText);
				BigManText->setID("big-man-corner-text"_spr);
				BigManText->setZOrder(102);
				BigManText->setOpacity(Mod::get()->getSettingValue<double>("opacity"));
				BigManText->createFontChars();
				BigManText->updateLabel();
			}

			this->updateLayout();
		}

		int overlay = Mod::get()->getSettingValue<int64_t>("overlay");
		if (overlay != 0) {
			auto BigManOverlay = CCSprite::create("bigman.png"_spr);
			BigManOverlay->setScaleX(CCDirector::get()->getWinSize().width / BigManOverlay->getContentSize().width);
			BigManOverlay->setScaleY(CCDirector::get()->getWinSize().height / BigManOverlay->getContentSize().height);
			BigManOverlay->setPosition({CCDirector::get()->getWinSize().width / 2, CCDirector::get()->getWinSize().height / 2});
			this->addChild(BigManOverlay);
			BigManOverlay->setID("big-man-overlay"_spr);

			if (overlay == 1) {
				BigManOverlay->setBlendFunc({GL_SRC_ALPHA, GL_ONE}); // additive
			}
			else if (overlay == 2) {
				BigManOverlay->setBlendFunc({GL_DST_COLOR, GL_ZERO}); // multiplicative
			}
			else if (overlay == 3) {
				BigManOverlay->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR}); // subtractive
			}
			else if (overlay == 4) {
				BigManOverlay->setBlendFunc({GL_ONE, GL_ONE_MINUS_SRC_COLOR}); // screen
			}
			else if (overlay == 5) {
				BigManOverlay->setBlendFunc({GL_ONE, GL_ONE_MINUS_SRC_COLOR}); // darken
			}
			else if (overlay == 6) {
				BigManOverlay->setBlendFunc({GL_ONE, GL_ONE}); // lighten
			}
			else if (overlay == 7) {
				BigManOverlay->setBlendFunc({GL_ONE_MINUS_DST_COLOR, GL_ZERO}); // inverse
			}
			else if (overlay == 8) {
				BigManOverlay->setBlendFunc({GL_SRC_ALPHA, GL_ONE}); // overlay
			}

			BigManOverlay->setOpacity(Mod::get()->getSettingValue<double>("overlay-opacity"));

			this->updateLayout();
		}

		return true;
	}
};