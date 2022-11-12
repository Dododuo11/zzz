#include "HelloWorldScene.h"
#include "main_game.h"
#include "enemy_base.h"
#include "manager_base.h"
#include "bullet.h"

USING_NS_CC;
using namespace std;

bool Bullet::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

void Bullet::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();
	scheduleUpdate();

}
void Bullet::onExit()
{
	unscheduleUpdate();
	Sprite::onExit();
}

void Bullet::initBullet(char* bullet_name)
{
	//初始化子弹
	auto spr_name = String::createWithFormat("%s",bullet_name);
	this->initWithFile(spr_name->getCString());


}
void Bullet::update(float delta)
{
	//子弹运动
	this->setPositionY(this->getPositionY() + 5);

	//判断子弹是否移除屏幕
	if (this->getPositionY() > Director::getInstance()->getWinSize().height)
	{
		this->removeFromParentAndCleanup(true);
		ManagerBase::getInstance()->remove_bullet_list(this);
	}
}


