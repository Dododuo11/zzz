#ifndef __MAIN_GAME_H__
#define __MAIN_GAME_H__

#include "cocos2d.h"

USING_NS_CC;

class PlaneSupport;//����֧Ԯ������

class MainGame : public cocos2d::Scene
{
public:

	CREATE_FUNC(MainGame);

	void onEnterTransitionDidFinish();//�������ҹ��ɶ�������ʱ����
	void onExit();//�˳���ʱ����

	void update(float delta);

	//���㴥������
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);

public:
	Sprite* bg1;
	Sprite* bg2;

	//��ҷɻ�
	Sprite* hero_player;

	//��ʼ����ҷɻ�
	void init_hero_plane(int index);

    //����ӵ�
	void add_bullet(float tm);

	//��ӵл�
	void add_enemy(float delta);

	//��ײ���
	void is_crash(float tm);

    //��ҷɻ�����
	void hero_death();

    //�������
	void add_support(float tm);
	//�����ҷɻ�������ʺ���ӵ�Ч��
	void add_support_bullet(float tm);
	//֧Ԯ���ʵ�����
	int support_index;   
	PlaneSupport* plane_support; //��Դ����
	
	void suspend(Ref * ref);//��ͣ
	
    int score;//��ҷɻ��ķ���
	Label* label_score_num; //��ǰ��
	Label* label_best_score_num; // ��߷�

	void game_over(); //��������

	static cocos2d::Scene* createScene();

	virtual bool init();
};

#endif // __HELLOWORLD_SCENE_H__