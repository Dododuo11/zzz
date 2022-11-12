#include "select_plane_page.h"
#include "select_plane_scene.h"
#include "main_game.h"

USING_NS_CC;
using namespace std;

SelectPlanePage* SelectPlanePage::create(int page)
{
	SelectPlanePage* pRet = new SelectPlanePage();
	if (pRet&&pRet->initLevelPage(page))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

//初始化飞机
bool SelectPlanePage::initLevelPage(int page)   
{
	if (!Node::init())
	{
		return false;
	}
	page_ = page;
	auto size = Director::getInstance()->getWinSize();

	log("join select page!");
	//背景
	auto sprite = Sprite::create("ui/bg_select.png");
	sprite->setPosition(Point(size.width / 2, size.height / 2));
	addChild(sprite);
	sprite->setVisible(false);

	//添加帧动画
	auto animation = Animation::create();
	for (int i = 1; i <=2; ++i)
	{
		auto spr_name = String::createWithFormat("plane/heros%d_%d.png", page, i);
		animation->addSpriteFrameWithFile(spr_name->getCString());
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);

	auto spr_name = String::createWithFormat("plane/heros%d_%d.png", page, 1);
	auto plane_sprite = Sprite::create(spr_name->getCString());
	plane_sprite->setPosition(size.width / 2, size.height/2);
	plane_sprite->setScale(2);
	this->addChild(plane_sprite);

	//动作
	auto animate = Animate::create(animation);
	plane_sprite->runAction(animate);

	//添加menu
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto btn_label = Label::create();
	btn_label->setString(((String*)(dictionary->objectForKey("select")))->getCString());
	btn_label->setSystemFontSize(40);
	btn_label->setColor(ccc3(36, 106, 32));
	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(SelectPlanePage::menuStartCallback,this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(size.width / 2, size.height*0.3));
	this->addChild(menu);

	return true;
}

void SelectPlanePage::menuStartCallback(Ref* pSender)
{
	//进入游戏界面
	auto scene = Scene::create();
	auto main_layer = MainGame::create();
	//初始化玩家飞机
	main_layer->init_hero_plane(this->getTag());
	scene->addChild(main_layer);
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0, scene));
}


