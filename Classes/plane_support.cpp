#include "plane_support.h"

USING_NS_CC;
using namespace std;


bool PlaneSupport::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void PlaneSupport::init_support(int index)
{
	//加载图片
	this->initWithFile(String::createWithFormat("plane/support%d.png", index)->getCString());

	//获取游戏屏幕大小
	auto size = Director::getInstance()->getWinSize();

	//获取自身大小
	auto content_size = this->getContentSize();

	//随机x,y坐标
	auto posx = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	auto posy = CCRANDOM_0_1()*(size.height - content_size.height) + content_size.height / 2;

	auto point = Point(posx, size.height);
	//初始化坐标
	this->setPosition(point);

	//创建贝塞尔曲线
	ccBezierConfig bezier;
	//随机x,y坐标(p1)
	posx = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	posy = CCRANDOM_0_1()*(size.height - content_size.height) + content_size.height / 2;
	bezier.controlPoint_1 = ccp(posx, posy);

	//随机x,y坐标(p2)
	posx = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	posy = CCRANDOM_0_1()*(size.height - content_size.height) + content_size.height / 2;
	bezier.controlPoint_2 = ccp(posx, posy);

	//p3坐标
	posx = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	bezier.endPosition = ccp(posx, -content_size.height);

	//贝塞尔曲线的动作
	auto bezieraction = BezierTo::create(2.0, bezier);
	//移除自己
	auto remover_action = RemoveSelf::create();

	auto ac = Sequence::create(bezieraction, remover_action, NULL);
	this->runAction(ac);
}

PlaneSupport::PlaneSupport()
{
}

PlaneSupport::~PlaneSupport()
{
}
