#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"

USING_NS_CC;

class GameOver : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameOver);

public:
	//·µ»Ø²Ëµ¥
	void menu_play(Ref * ref);

};
#endif //__GAME_OVER_H__