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
	//����
	static ManagerBase* getInstance();
	//ɾ��
	static void deleteInstance();

	//�����ӵ��͵л�
	Vector<EnemyBase*> &getEnemyList() { return enemy_list; }
	Vector<Bullet*>&getBulletList() { return bullet_list; }
	//��ӵл�
	void set_enemy_list(EnemyBase* enemy);
	//����ӵ�
	void set_bullet_list(Bullet* bullet);
	//ɾ���л�
	void remove_enemy_list(EnemyBase* enemy);
	//ɾ���ӵ�
	void remove_bullet_list(Bullet*bullet);

	Vector<EnemyBase*> enemy_list;
	Vector<Bullet*> bullet_list;

private:
	static ManagerBase* manager;
};

#endif //__MANAGER_BASE_H__