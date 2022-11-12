#ifndef __MAIN_GAME_H__
#define __MAIN_GAME_H__

#include "cocos2d.h"

USING_NS_CC;

class PlaneSupport;//引用支援物资类

class MainGame : public cocos2d::Scene
{
public:

	CREATE_FUNC(MainGame);

	void onEnterTransitionDidFinish();//进入层而且过渡动画结束时调用
	void onExit();//退出层时调用

	void update(float delta);

	//单点触摸方法
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);

public:
	Sprite* bg1;
	Sprite* bg2;

	//玩家飞机
	Sprite* hero_player;

	//初始化玩家飞机
	void init_hero_plane(int index);

    //添加子弹
	void add_bullet(float tm);

	//添加敌机
	void add_enemy(float delta);

	//碰撞检测
	void is_crash(float tm);

    //玩家飞机死亡
	void hero_death();

    //添加物资
	void add_support(float tm);
	//添加玩家飞机获得物资后的子弹效果
	void add_support_bullet(float tm);
	//支援物资的类型
	int support_index;   
	PlaneSupport* plane_support; //资源物资
	
	void suspend(Ref * ref);//暂停
	
    int score;//玩家飞机的分数
	Label* label_score_num; //当前分
	Label* label_best_score_num; // 最高分

	void game_over(); //结束场景

	static cocos2d::Scene* createScene();

	virtual bool init();
};

#endif // __HELLOWORLD_SCENE_H__