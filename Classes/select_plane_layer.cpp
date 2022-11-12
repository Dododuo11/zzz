#include "select_plane_layer.h"

USING_NS_CC;
using namespace std;

Scene* SelectPlaneLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectPlaneLayer::create();
	scene->addChild(layer);
	return scene;
}

bool SelectPlaneLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//添加触摸绑定事件
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SelectPlaneLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SelectPlaneLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SelectPlaneLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	size_x = Director::getInstance()->getWinSize().width;
	size_y = Director::getInstance()->getWinSize().height;

	return true;
}

void SelectPlaneLayer::goToCurrNode()
{
	//滑动效果
	this->runAction(MoveTo::create(0.4f, Point(-cur_page_node*size_x, 0)));
}

void SelectPlaneLayer::addNode(Node* level)
{
	if (level)
	{
		level->setContentSize(Size(size_x, size_y));
		level->setPosition(Point(size_x*page_node, 0));
		this->addChild(level);
		//记录添加几个飞机界面
		page_node++;
	}
}


bool SelectPlaneLayer::onTouchBegan(Touch *touch, Event *event)
{
	touch_down_point = touch->getLocation();
	touch_cur_point = touch_down_point;
	return true;
}

void SelectPlaneLayer::onTouchMoved(Touch *touch, Event* event)
{
	Point touchPoint = touch->getLocation();
	auto currX = this->getPositionX() + touchPoint.x - touch_up_point.x;
	Point pos_point = Point(currX, getPositionY());

	touch_cur_point = touchPoint;
}

void  SelectPlaneLayer::onTouchEnded(Touch* touch, Event *event)
{
	touch_up_point = touch->getLocation();

	//坐标差
	auto dis = touch_up_point.getDistance(touch_down_point);

	if (dis >= SHORTEST_SLIDE_LENGTH)
	{
		if (touch_down_point.x > touch_up_point.x)
		{
			//记录当前页
			++cur_page_node;
			if (page_node - 1 < cur_page_node)
				cur_page_node = page_node - 1;
		}
		else if (touch_down_point.x < touch_up_point.x)
		{
			//记录当前页
			--cur_page_node;
			if (cur_page_node < 0)
				cur_page_node = 0;
		}
		//播放滚动界面
		goToCurrNode();
	}
}