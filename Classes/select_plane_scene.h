#ifndef __SELECT_PLANE_SCENE
#define __SELECT_PLANE_SCENE_
#include "cocos2d.h"

USING_NS_CC;

class SelectPlaneScene :public cocos2d::Scene
{
public:
	virtual bool init();

	CREATE_FUNC(SelectPlaneScene);
	void menuCloseCallback(Ref* pSender);
	static cocos2d::Scene* createScene();
	static SelectPlaneScene* getInstance();
};

#endif//__SELECT_PLANE_SCENE_
