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
	//��ʼ���л�
	void initEnemy(int index = 1);

	//��ը����
	void enemy_death();

	//ɾ���Լ�
	void remove_enemy();

	//�л�����
	int enemy_index;

	//�л�Ѫ��
	void set_hp(int hp);
	int get_hp() { return enemy_hp; }
	//�л�Ѫ������
	int enemy_hp;

	//�Ƿ�ը
	bool isdeath;

	virtual bool init();
};
#endif //__ENEMY_BASE_H__
