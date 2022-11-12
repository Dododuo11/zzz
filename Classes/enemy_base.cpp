#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "main_game.h"
#include "enemy_base.h"
#include "manager_base.h"


USING_NS_CC;


bool EnemyBase::init()
{
	isdeath = false;
	if (!Sprite::init())
	{
		return false;
	}
	//游戏窗口大小
	auto size = Director::getInstance()->getWinSize();
	return true;
}

void EnemyBase::initEnemy(int name_index)
{
	//敌机血量
	enemy_hp = name_index;
	//初始化敌机
	string name_str = String::createWithFormat("plane/enemy%d.png", name_index)->getCString();
	//添加敌机图片
	this->initWithFile(name_str);
	//获取屏幕大小
	Size size = Director::getInstance()->getWinSize();
	//s随机敌机坐标
	Point pos = ccp(CCRANDOM_0_1()*(size.width - this->getContentSize().width) + this->getContentSize().width / 2, size.height - this->getContentSize().height / 2);
	this->setPosition(pos);
	this->scheduleUpdate();
}
void EnemyBase::enemy_death()
{
	isdeath = true;
	//爆炸动画
	auto animation = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		auto enemy_name = String::createWithFormat("plane/b%d.png", i);
		animation->addSpriteFrameWithFile(enemy_name->getCString());
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(1);
	this->runAction(Sequence::create(Animate::create(animation), RemoveSelf::create(),CallFunc::create(CC_CALLBACK_0(EnemyBase::remove_enemy,this)), NULL));
}

void EnemyBase::update(float delta)
{
	//如果爆炸不移动
	if (isdeath)
		return;
	//实现敌机运动
	auto point = this->getPositionY() - 5;
	this->setPositionY(point);
	//如果移动出了屏幕则从父节点中移除
	if (point < -this->getContentSize().height)
	{
		this->removeFromParentAndCleanup(true);
		remove_enemy();
	}
}

void EnemyBase::remove_enemy()
{
	ManagerBase::getInstance()->remove_enemy_list(this);
}

void EnemyBase::set_hp(int hp)
{
	enemy_hp = hp;
}

EnemyBase::EnemyBase()
{
}
EnemyBase::~EnemyBase()
{
}