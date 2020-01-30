#pragma once
#include "BaseModel.h"


/*
�̳�ģ���࣬��һ���ķ���Ƭ������ģ����
*/
class FishModel :
	public BaseModel
{
public:
	/*
	position:ģ�ͳ�ʼ��λ��
	rotation:ģ�ͳ�ʼ����ת
	scale:ģ������
	objdectId:ģ��ID��
	imgId:ͼƬID��
	enableBlend���Ƿ�����ɫ��ϣ�����͸����Ⱦ
	enableTwoSide���Ƿ���˫����Ⱦ������Ƭ״����
	*/
	FishModel(Float3 position, Float3 rotation, Float3 scale, int objectId, int imgId, bool enableBlend = false, bool enableTwoSide = false);
	~FishModel();

	/*
	��д������Ⱦ������������Ⱦ��Ƭ
	*/
	virtual void Render(ObjReader& obj, ImageReader& image);

	/*ÿ֡���º���*/
	virtual void Tick();

	/*������Ⱥ�ζ�����*/
	void Init(float waveRange);

protected:
	/*��ת�Ƕȣ����ڱ任*/
	float angle;

	/*�ζ��ٶ�*/
	float speed;
	/*ʱ���ʱ��*/
	int time;
	/*�ζ����ȷ�Χ*/
	float waveRange;
	/*��XZƽ����������ľ���*/
	int disFromCamera;
};

