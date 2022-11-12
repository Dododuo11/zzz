#ifndef __SUSPAND_LAYER_H__
#define __SUSPAND_LAYER_H__
#include "cocos2d.h"

using namespace std;

class SuspendLayer : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//»Ø¸´ÓÎÏ·Âß¼­
    void back_game(Ref * ref);

	CREATE_FUNC(SuspendLayer);
	
};
#endif //__SUSPAND_LAYER_H__