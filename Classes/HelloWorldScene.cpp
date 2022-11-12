/****************************************************************************
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "main_game.h"
#include "enemy_base.h"
#include "select_plane_layer.h"
#include "select_plane_scene.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);

	return scene;
}


bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//游戏窗口大小
	auto size = Director::getInstance()->getWinSize();

	//游戏背景
	auto spr_bg = Sprite::create("ui/bg.png");
	spr_bg->setPosition(ccp(size.width / 2, size.height / 2));
	this->addChild(spr_bg);

	//读取xml
	auto dic = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto str = (String*)(dic->objectForKey("title"));

	//游戏标题
	auto title = Label::create();
	title->setString(str->getCString());
	title->setPosition(ccp(size.width / 2, size.height *0.5+150));
	title->setSystemFontSize(50);
	title->setColor(ccc3(174, 111, 23));
	this->addChild(title);

	//创建帧动画
	auto animation = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		auto spr_name = String::createWithFormat("ui/start%d.png", i);
		animation->addSpriteFrameWithFile(spr_name->getCString());
	}
	animation->setDelayPerUnit(0.3f);
	animation->setLoops(-1);

	//创建精灵
	auto sprite = Sprite::create("ui/start1.png");
	sprite->setPosition(ccp(size.width / 2, size.height / 2));
	this->addChild(sprite);
	sprite->runAction(Animate::create(animation));

	//添加开始游戏按钮
	str = (String*)(dic->objectForKey("play"));
	auto btn_label = Label::create();
	btn_label->setString(str->getCString());
	btn_label->setSystemFontSize(40);

	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(HelloWorld::Hello_play, this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(size.width / 2, size.height *0.3));
	this->addChild(menu);

	return true;
}


void HelloWorld::Hello_play(Ref* ref)
{
	//切换场景
	Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5, SelectPlaneScene::createScene()));
}
