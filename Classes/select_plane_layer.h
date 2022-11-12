#ifndef __SELECT_PLANE_LAYER
#define __SELECT_PLANE_LAYER
#include "cocos2d.h"

USING_NS_CC;

class SelectPlaneLayer :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	
	virtual bool init();
	void SelectPlaneLayer::goToCurrNode();
	bool SelectPlaneLayer::onTouchBegan(Touch *touch, Event *event);
	void SelectPlaneLayer::onTouchMoved(Touch *touch, Event* event);
	void SelectPlaneLayer::onTouchEnded(Touch* touch, Event *event);
	void SelectPlaneLayer::addNode(Node* level);
	CREATE_FUNC(SelectPlaneLayer);

private:
	float size_x;
	float size_y;

	int page_node;
	int cur_page_node;//当前页面
	int SHORTEST_SLIDE_LENGTH = 0;

	Point touch_down_point;//点击时停止
	Point touch_up_point;//抬起时停止
	Point touch_cur_point;
};
#endif //__SELECT_PLANE_LAYER