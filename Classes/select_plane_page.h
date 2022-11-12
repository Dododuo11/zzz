#ifndef __SELECT_PLANE_PAGE_
#define __SELECT_PLANE_PAGE_
#include "cocos2d.h"

USING_NS_CC;

class SelectPlanePage :public cocos2d::Node
{
public:
	//初始化飞机选择页面
	bool initLevelPage(int page);

	static SelectPlanePage* create(int page);
	void menuStartCallback(Ref* pSender);
	CREATE_FUNC(SelectPlanePage);

private:
	int page_;
};
#endif //__SELECT_PLANE_PAGE_
