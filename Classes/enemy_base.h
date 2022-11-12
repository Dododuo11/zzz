#ifndef __ENEMY_BASE_H__
#define __ENEMY_BASE_H__
#include "cocos2d.h"


USING_NS_CC;
using namespace std;

class EnemyBase : public cocos2d::Sprite
{	
public:
   // void hero_death();

	EnemyBase();
	~EnemyBase();

	CREATE_FUNC(EnemyBase);


	virtual void update(float delta);

	static cocos2d::Scene* createScene();
public:
	//初始化敌机
	void initEnemy(int index = 1);

	//爆炸动画
	void enemy_death();

	//删除自己
	void remove_enemy();

	//敌机类型
	int enemy_index;

	//敌机血量
	void set_hp(int hp);
	int get_hp() { return enemy_hp; }
	//敌机血量参数
	int enemy_hp;

	//是否爆炸
	bool isdeath;

	virtual bool init();
};
#endif //__ENEMY_BASE_H__
