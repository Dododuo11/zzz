#ifndef __MANAGER_BASE_H__
#define __MANAGER_BASE_H__

#include "cocos2d.h"
#include "bullet.h"
#include "enemy_base.h"

USING_NS_CC;

class ManagerBase
{
	ManagerBase();
	~ManagerBase();

public:
	//创建
	static ManagerBase* getInstance();
	//删除
	static void deleteInstance();

	//管理子弹和敌机
	Vector<EnemyBase*> &getEnemyList() { return enemy_list; }
	Vector<Bullet*>&getBulletList() { return bullet_list; }
	//添加敌机
	void set_enemy_list(EnemyBase* enemy);
	//添加子弹
	void set_bullet_list(Bullet* bullet);
	//删除敌机
	void remove_enemy_list(EnemyBase* enemy);
	//删除子弹
	void remove_bullet_list(Bullet*bullet);

	Vector<EnemyBase*> enemy_list;
	Vector<Bullet*> bullet_list;

private:
	static ManagerBase* manager;
};

#endif //__MANAGER_BASE_H__