#include "select_plane_scene.h"
#include "select_plane_layer.h"
#include "select_plane_page.h"

USING_NS_CC;
using namespace std;

Scene* instance_;
Scene* SelectPlaneScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectPlaneScene::create();
	scene->addChild(layer);
	return scene;
}

bool SelectPlaneScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	instance_ = this;

	Size size = Director::getInstance()->getWinSize();
	
	//添加可滑动界面
	SelectPlaneLayer* scrollView = SelectPlaneLayer::create();

	for (int i = 1; i <= 3; ++i)
	{
		//添加飞机界面
		auto page = SelectPlanePage::create(i);
		page->setTag(i);
		scrollView->addNode(page);
	}

	//背景
	Sprite* spritebg = Sprite::create("ui/bg_select.png");
	spritebg->setPosition(Point(size.width / 2 ,size.height / 2));
	addChild(spritebg);
	this->addChild(scrollView);

	return true;
}



