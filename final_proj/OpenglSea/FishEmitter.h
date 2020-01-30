#pragma once
#include <Tool/ObjReader.h>
#include <Tool/ImageReader.h>
#include <Model/FishModel.h>
#include <list>

/*
��Ⱥ������
*/
class FishEmitter
{
public:
	/*
	freTime:ÿ�����ʱ������һ����
	fishNum:�������������������������������������
	pos:������λ�ã����ʼ�ο�����
	rot:��������ת�ȣ����ʼ�ο���ת
	objectID:���ģ��ID��
	imgID:��ģ�͵�ͼƬ��
	waveRange:���ζ���·��ƫ�ƽǶ�
	*/
	FishEmitter(int freTime, int fishNum, Float3 pos, Float3 rot, int objectId, int imgId, float waveRange = 60);
	~FishEmitter();

	/*ÿ֡����*/
	void Tick();

	/*������λ��*/
	Float3 mPosition;
	/*��������ת��*/
	Float3 mRotation;

private:
	/*ʱ���ʱ��*/
	int time;
	/*������ʱ��*/
	int num;
	/*ÿ�����ʱ������һ����*/
	int freTimeCount;
	/*���ģ��ID��*/
	int objectId;
	/*��ģ�͵�ͼƬ��*/
	int imgId;
	/*���ζ���·��ƫ�ƽǶ�*/
	float waveRange;

	/*�����Ⱥ�б�*/
	list<FishModel*> fishes;
};

