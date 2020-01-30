#pragma once
#include "Tool/ObjReader.h"
#include <stdlib.h>
#include <GL/glew.h>
#include <Tool/ObjReader.h>
#include <Tool/ImageReader.h>

/*ģ�ͻ��࣬���ڹ���ģ��*/
class BaseModel
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
	BaseModel(Float3 position, Float3 rotation, Float3 scale, int objectId, int imgId, bool enableBlend = false, bool enableTwoSide = false);

	~BaseModel();

	/*��SceneMangerÿ֡����*/
	void Update();
	/*
	�麯��ÿ֡���ã���Ⱦ����
	obj:ģ���ļ�
	image:ͼƬ�ļ�
	*/
	virtual void Render(ObjReader& obj, ImageReader& image);
	/*
	�麯����ÿ֡����
	*/
	virtual void Tick() {};

	/*ģ��λ��*/
	Float3 mPosition;
	/*ģ����ת*/
	Float3 mRotation;
	/*ģ������*/
	Float3 mScale;

	/*ģ��Id��*/
	int objId;
	/*ͼƬId��*/
	int imageId;
	/*�Ƕ�ת��*/
	float rotationTrans = 3.14 / 180.0;

protected:

	/*�Ƿ�����ɫ���*/
	bool isEnableBlend;
	/*�Ƿ���˫����Ⱦ*/
	bool isEnableTwoSide;
};

