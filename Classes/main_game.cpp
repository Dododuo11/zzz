#include "main_game.h" 
#include "enemy_base.h"
#include "bullet.h"
#include "manager_base.h"
#include "plane_support.h"
#include "suspend_layer.h"		
#include "game_over.h"
#include "select_plane_scene.h"
#include "select_plane_layer.h"


Scene* MainGame::createScene()
{
	auto scene = Scene::create();
	auto layer = MainGame::create();
	scene->addChild(layer);

	return scene;
}

bool MainGame::init()
{
	int plane_type = NULL;//��ʼ���ɻ�����
	plane_support = NULL; //��ʼ����Դ����
	score = 0;

	if (!Scene::init())
		return false;

	Size size = Director::getInstance()->getWinSize();
	//����һ
	bg1 = Sprite::create("ui/bgs.png");
	bg1->setAnchorPoint(ccp(0, 0));
	bg1->setPosition(ccp(0, 0));
	this->addChild(bg1);
	//������
	bg2 = Sprite::create("ui/bgs.png");
	bg2->setAnchorPoint(ccp(0, 0));
	bg2->setPosition(ccp(0, bg2->getContentSize().height - 2));
	this->addChild(bg2);

	//��ʼ���ɻ�
	//init_hero_plane(1);


	//�����ͣ����
	//���menu
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto btn_label = Label::create();
	btn_label->setString(((String*)(dictionary->objectForKey("suspend")))->getCString());
	btn_label->setSystemFontSize(30);
	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(MainGame::suspend, this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(size.width - btn_label->getContentSize().width / 2 - 5, size.height - btn_label->getContentSize().height / 2 - 5));
	this->addChild(menu);
	

	//���÷���
	//��������
	auto label_score = Label::create();
	label_score->setString(((String*)(dictionary->objectForKey("score")))->getCString());
	label_score->setSystemFontSize(30);
	label_score->setAnchorPoint(ccp(0.5, 0.5));
	label_score->setPosition(ccp(label_score->getContentSize().width / 2 + 5, size.height - label_score->getContentSize().height / 2 - 5));
	this->addChild(label_score);

	//��ǰ����
	label_score_num = Label::create();
	label_score_num->setSystemFontSize(30);
	label_score_num->setAnchorPoint(ccp(0, 0.5));
	label_score_num->setPosition(ccp(label_score->getContentSize().width + 5, label_score->getPositionY()));
	this->addChild(label_score_num);
	//��߷�
	auto label_best_score = Label::create();
	label_best_score->setString(((String*)(dictionary->objectForKey("best_score")))->getCString());
	label_best_score->setSystemFontSize(30);
	label_best_score->setAnchorPoint(ccp(0.5, 0.5));
	label_best_score->setPosition(ccp(label_best_score->getContentSize().width / 2 + 5, label_score->getPositionY() - label_best_score->getContentSize().height - 5));
	this->addChild(label_best_score);

	label_best_score_num = Label::create();
	label_best_score_num->setSystemFontSize(30);
	label_best_score_num->setAnchorPoint(ccp(0, 0.5));
	label_best_score_num->setPosition(ccp(label_best_score->getContentSize().width + 5, label_best_score->getPositionY()));
	this->addChild(label_best_score_num);

	//��߷�
	int score_win = UserDefault::getInstance()->getIntegerForKey("best_score");
	label_best_score_num->setString(String::createWithFormat("%d", score_win)->getCString());
	//��ǰ��
	label_score_num->setString(String::createWithFormat("%d", score)->getCString());


	//���㴥���ļ�����
	EventListenerTouchOneByOne* m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(MainGame::onTouchMoved, this);
	//�������ɴ���
	m_touchListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);
	
	return true;
}


void MainGame::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	scheduleUpdate();

	//�л�
	this->schedule(SEL_SCHEDULE(&MainGame::add_enemy), 0.3f);
	//�ӵ�
	this->schedule(SEL_SCHEDULE(&MainGame::add_bullet), 0.08f);
	//��ײ���
	this->schedule(SEL_SCHEDULE(&MainGame::is_crash));
	//����
	this->schedule(SEL_SCHEDULE(&MainGame::add_support), 5.0f);
}

void MainGame::onExit()
{
	unscheduleUpdate();
	ManagerBase::getInstance()->deleteInstance();
	Scene::onExit();
}

void MainGame::update(float delta)
{
	//ʵ�ֱ�������
	float y1 = bg1->getPositionY() - 3;
	float y2 = bg2->getPositionY() - 3;

	bg1->setPositionY(y1);
	bg2->setPositionY(y2);

	//�жϱ���ͼƬ�Ƿ񳬳��߽�
	if (y1 < -bg1->getContentSize().height)
	{
		bg1->setPositionY(bg2->getPositionY() + bg2->getContentSize().height - 2);

	}
	else if (y2 < -bg2->getContentSize().height)
	{
		bg2->setPositionY(bg1->getPositionY() + bg1->getContentSize().height - 2);

	}
}

bool MainGame::onTouchBegan(Touch *touch, Event *unused_event)
{
	//�жϵ���������Ƿ��ڷɻ���
	auto point = touch->getLocation(); //
	auto rect = hero_player->getBoundingBox();
	if (rect.containsPoint(point))
	{
		return true;
	}
	return false;
}

void MainGame::onTouchMoved(Touch *touch, Event *unused_event)
{
	//��ȡ�ɻ��ƶ��ľ���
	auto add_point = touch->getLocation() - touch->getPreviousLocation();
	hero_player->setPosition(hero_player->getPosition() + add_point);

	//�жϷɻ��ƶ��ķ�Χ����Ҫ�����߽�
	auto size = Director::getInstance()->getWinSize();
	auto hero_size = hero_player->getContentSize();

	//x����
	if (hero_player->getPositionX() < hero_size.width / 2)
	{
		hero_player->setPositionX(hero_size.width / 2);
	}
	else if (hero_player->getPositionX() > size.width - hero_size.width / 2)
	{
		hero_player->setPositionX(size.width - hero_size.width / 2);
	}

	//y����
	if (hero_player->getPositionY() < hero_size.height / 2)
	{
		hero_player->setPositionY(hero_size.height / 2);
	}
	else if (hero_player->getPositionY() > size.height - hero_size.height / 2)
	{
		hero_player->setPositionY(size.height - hero_size.height / 2);
	}

}

void MainGame::init_hero_plane(int index)
{
	//���֡����
	auto animation = Animation::create();
	for (int i = 0; i < 2; ++i)
	{
		auto str_name = String::createWithFormat("plane/heros%d_%d.png", index, i + 1);
		animation->addSpriteFrameWithFile(str_name->getCString());
	}
	animation->setDelayPerUnit(0.5);
	animation->setLoops(-1);

	//�����ɻ�����
	hero_player = Sprite::create(String::createWithFormat("plane/heros%d_1.png", index)->getCString());
	auto size = Director::getInstance()->getWinSize();
	hero_player->setPosition(ccp(size.width / 2, size.height * 0.2));
	this->addChild(hero_player);
	hero_player->runAction(Animate::create(animation));

}

void MainGame::add_enemy(float delta)
{
	//��ӵл�
	//���ݲ�ͬ������Ӳ�ͬ�ɻ�
	int enemy_x = CCRANDOM_0_1() * 9 + 1;

	if (enemy_x > 6)
	{
		enemy_x = 2;
	}
	else
	{
		enemy_x = 1;
	}

	auto enemy = EnemyBase::create();
	enemy->initEnemy(enemy_x);
	this->addChild(enemy);
	ManagerBase::getInstance()->set_enemy_list(enemy);
}

void MainGame::add_bullet(float tm)
{
	//����ӵ�
	auto bullet = Bullet::create();
	bullet->initBullet("plane/bullet1.png");

	auto point = ccp(hero_player->getPositionX(), hero_player->getPositionY() + hero_player->getContentSize().height / 2 + 10);
	bullet->setPosition(point);
	this->addChild(bullet);
	//���ӵ����������
	ManagerBase::getInstance()->set_bullet_list(bullet);

}

void MainGame::is_crash(float tm)
{
    //��ײ���
	auto & enemy_list = ManagerBase::getInstance()->getEnemyList();
	auto & bullet_list = ManagerBase::getInstance()->getBulletList();

	//���л���Vector���е������
	for (int i = enemy_list.size() - 1;i >= 0;--i)
	{
		//�л�
		auto enemy = enemy_list.at(i);
		if (enemy->get_hp() <= 0)
		{
			continue;
		}
		auto enemy_size = enemy->boundingBox();

		//���ӵ�Ҳ���е������
		for (int i = bullet_list.size() - 1;i >= 0;--i)
		{
			auto bullet = bullet_list.at(i);
			//�ж��ӵ��͵л��Ƿ���ײ
			if (enemy_size.containsPoint(bullet->getPosition()))
			{
				//��ײ��л�Ѫ��-1
				enemy->set_hp(enemy->get_hp() - 1);

				//�Ƴ��ӵ�
				bullet->removeFromParentAndCleanup(true);
				ManagerBase::getInstance()->remove_bullet_list(bullet);

				//����л�Ѫ��Ϊ0���򲥷ű�ը����
				if (enemy->get_hp() <= 0)
				{
					enemy->enemy_death();
					score += 10;//�л���ը�����+10
					label_score_num->setString(String::createWithFormat("%d", score)->getCString());
				}
			}

		}
	}

	//��ҷɻ��͵л�����ײ���
	for (auto i = enemy_list.size() - 1; i >= 0; --i)
	{
		auto enemy = enemy_list.at(i);

		if (enemy->get_hp() <= 0)
		{
			//����Ѿ�����Ͳ�������ײ���
			continue;
		}
		auto rect = this->hero_player->getBoundingBox();
		auto point = enemy->getPosition();
		//�жϵл���ɻ��Ƿ���ײ 
		//�����,��ִ����ҷɻ�����
		if (rect.containsPoint(point))
		{
			//��ҷɻ�����
			hero_death();
		}
	}

	//�����Ƿ�����ҷɻ���ײ
	if (plane_support != NULL)
	{
		//��ҷɻ���С
		auto rect = hero_player->getBoundingBox();
		//֧Ԯ��������
		auto point = plane_support->getPosition();
		//����ɻ���֧Ԯ���ʷ�����ײ
		if (rect.containsPoint(point))
		{
			//���֧Ԯ���ʵ��ӵ�
			this->schedule(SEL_SCHEDULE(&MainGame::add_support_bullet), 0.1f, 50, 0);// 50�����������������������ü���
			//ֹͣ�����ͨ�ӵ�																																			 //ֹͣ��ͨ�ӵ�
			this->unschedule(SEL_SCHEDULE(&MainGame::add_bullet));
			//�����ӳ�ִ�������ͨ�ӵ�ʱ�� 
			this->schedule(SEL_SCHEDULE(&MainGame::add_bullet), 0.1f, -1, 5.0f);//5.0f ���������������������ӳٶ�ú󱻵���

			plane_support->setVisible(false);
			plane_support = NULL;
		}
		//�Ƴ�����
		if (plane_support != NULL && point.y < -plane_support->getContentSize().height / 2)
		{
			plane_support->removeFromParent();
			plane_support = NULL;
		}
	}

}

void MainGame::hero_death()
{
	//�洢��������
	UserDefault::getInstance()->setIntegerForKey("score", score);
	//�洢��߷�
	int high_score = UserDefault::getInstance()->getIntegerForKey("best_score");
	if (score>high_score)
	{
		UserDefault::getInstance()->setIntegerForKey("best_score", score);
	}
	//��ҷɻ�׹��
	hero_player->stopAllActions();
	this->unschedule(SEL_SCHEDULE(&MainGame::add_bullet));//ֹͣ����ӵ� 
	this->unschedule(SEL_SCHEDULE(&MainGame::is_crash));//ֹͣ��ײ���

	//����׹��֡����												
	auto animation = Animation::create();

	for (int i = 1; i <= 4; ++i)
	{
		auto str_name = String::createWithFormat("plane/b%d.png", i);
		animation->addSpriteFrameWithFile(str_name->getCString());
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(1);

	hero_player->runAction(Sequence::create(Animate::create(animation),
	//���ý���ҳ��
	CallFunc::create(CC_CALLBACK_0(MainGame::game_over, this)), NULL));
}



void MainGame::add_support(float tm)
{
	//��ʼ������
	plane_support = PlaneSupport::create();
	//�����֧Ԯ���ʵ�����
	int index = CCRANDOM_0_1() * 2 + 1;
	support_index = index;
	plane_support->init_support(index);
	this->addChild(plane_support);
	plane_support->setTag(index);
}

void MainGame::add_support_bullet(float tm)
{
	//��ҷɻ��Ե����ʺ���ӵ�
	auto bullet = Bullet::create();

	if (support_index == 2)
		bullet->initBullet("plane/bullet_suspand2.png");
	else
		bullet->initBullet("plane/bullet_suspand1.png");

	auto point = Point(hero_player->getPositionX(),
		hero_player->getPositionY() + hero_player->getContentSize().height / 2 + 10);
	bullet->setPosition(point);

	this->addChild(bullet);

	//���ӵ���ӵ�ManagerBase��
	ManagerBase::getInstance()->set_bullet_list(bullet);
}

//��ͣ
void MainGame::suspend(Ref * ref)
{
	unscheduleUpdate();
	//�Ȱ�֮ǰ���õ�����ɾ��
	CCTextureCache::getInstance()->removeUnusedTextures();

	//����
	auto size = Director::getInstance()->getWinSize();
	auto texture = RenderTexture::create(size.width, size.height);
	texture->begin();//��ʼ����
	//��Ⱦ
	Director::getInstance()->getRunningScene()->visit();
	texture->end();//��������

	texture->saveToFile("suspand.png", Image::Format::PNG);


	//ʹ��schedule����һ֡�е���callback����
	//����ʱ�� ��һ֡
	auto back = [](float dt)
	{
		//�л�����ͣ����
		auto scene = Scene::create();
		auto layer = SuspendLayer::create();
		scene->addChild(layer);
		//�����õ�pushScene
		Director::getInstance()->pushScene(scene);
	};
	//���ﴴ��Layer ����Ϊ ��ֲandroid ʱ���ܵ������߳��н������һ֡ 
	auto layer = Layer::create();
	this->addChild(layer);
	auto schedules = layer->getScheduler();
	schedules->schedule(back, layer, 0.0f, 0, 0.0f, false, "screenshot");
}

//��������
void MainGame::game_over()
{
	//ֹͣ��ӷɻ�
	this->unschedule(SEL_SCHEDULE(&MainGame::add_enemy));
	//���ý���ҳ��
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1, GameOver::createScene()));
}


