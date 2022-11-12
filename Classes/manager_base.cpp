#include "manager_base.h"

USING_NS_CC;
using namespace std;

ManagerBase* ManagerBase::manager = NULL;

ManagerBase::ManagerBase()
{

}

ManagerBase::~ManagerBase()
{

}

ManagerBase* ManagerBase::getInstance()
{
	if (manager == NULL)
	{
		manager = new ManagerBase();

	}
	return manager;
}

void ManagerBase::deleteInstance()
{
	if (manager)
	{
		delete manager;
		manager = NULL;
	}
}

//添加敌机管理器
void ManagerBase::set_enemy_list(EnemyBase* enemy)
{
	enemy_list.pushBack(enemy);
}

//添加子弹管理器
void ManagerBase::set_bullet_list(Bullet* bullet)
{
	bullet_list.pushBack(bullet);
}

//删除敌机管理器
void ManagerBase::remove_enemy_list(EnemyBase* enemy)
{
	enemy_list.eraseObject(enemy);
}

//删除子弹管理器
void ManagerBase::remove_bullet_list(Bullet*bullet)
{
	bullet_list.eraseObject(bullet);
}


