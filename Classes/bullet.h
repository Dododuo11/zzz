#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Bullet : public cocos2d::Sprite
{

public:

	virtual bool init();
	CREATE_FUNC(Bullet);

	void onEnterTransitionDidFinish();//进入层而且过渡动画结束时调用
	void onExit();//退出层时调用

	void update(float delta);

	//初始化子弹
	void initBullet(char* bullet_name);
	
};

#endif //__BULLET_H__
