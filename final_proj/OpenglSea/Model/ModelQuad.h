#pragma once
#include <BaseModel.h>

/*
�̳�ģ���࣬��һ���ķ���Ƭ������ģ�����
*/
class ModelQuad : public BaseModel
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
	ModelQuad(Float3 position, Float3 rotation, Float3 scale, int objectId, int imgId, bool enableBlend = false, bool enableTwoSide = false);
	~ModelQuad();

	/*
	��д������Ⱦ������������Ⱦ��Ƭ
	*/
	virtual void Render(ObjReader& obj, ImageReader& image);
	
protected:
	/*ÿ֡���º���*/
	virtual void Tick();
};

