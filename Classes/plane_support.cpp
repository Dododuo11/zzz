#include "plane_support.h"

USING_NS_CC;
using namespace std;


bool PlaneSupport::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void PlaneSupport::init_support(int index)
{
	//����ͼƬ
	this->initWithFile(String::createWithFormat("plane/support%d.png", index)->getCString());

	//��ȡ��Ϸ��Ļ��С
	auto size = Director::getInstance()->getWinSize();

	//��ȡ�����С
	auto content_size = this->getContentSize();

	//���x,y����
	auto posx = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	auto posy = CCRANDOM_0_1()*(size.height - content_size.height) + content_size.height / 2;

	auto point = Point(posx, size.height);
	//��ʼ������
	this->setPosition(point);

	//��������������
	ccBezierConfig bezier;
	//���x,y����(p1)
	posx = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	posy = CCRANDOM_0_1()*(size.height - content_size.height) + content_size.height / 2;
	bezier.controlPoint_1 = ccp(posx, posy);

	//���x,y����(p2)
	posx = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	posy = CCRANDOM_0_1()*(size.height - content_size.height) + content_size.height / 2;
	bezier.controlPoint_2 = ccp(posx, posy);

	//p3����
	posx = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	bezier.endPosition = ccp(posx, -content_size.height);

	//���������ߵĶ���
	auto bezieraction = BezierTo::create(2.0, bezier);
	//�Ƴ��Լ�
	auto remover_action = RemoveSelf::create();

	auto ac = Sequence::create(bezieraction, remover_action, NULL);
	this->runAction(ac);
}

PlaneSupport::PlaneSupport()
{
}

PlaneSupport::~PlaneSupport()
{
}
