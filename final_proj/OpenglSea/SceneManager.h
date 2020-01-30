#pragma once
#include <map>
#include <vector>
#include <Tool/ObjReader.h>
#include <Tool/ImageReader.h>
#include <BaseModel.h>
#include <Model/ModelQuad.h>
#include <FishEmitter.h>

#define WINDOW_WIDTH 1280	
#define WINDOW_HEIGHT 720

/*
*������������ͳ�ܳ�����Ⱦ
*/
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	/*��ʼ����������*/
	void Init();

	/*ÿ֡���ã��ȸ��³��������λ�ã��ٽ�����Ⱦ*/
	void Update();
	
	/*�洢͸����Ⱦ����*/
	map<int, BaseModel*> translucentModel;

private:
	/*��ʼ�����*/
	void InitSky();
	/*��ʼ���ƹ�*/
	void InitLight();
	/*��ʼ����*/
	void InitFog();

	/*��Ⱦ���*/
	void SetSky();
	
	/*��ʼ������ģ��*/
	void InitModel();

	ImageReader sky;

	/*��Ⱥ������*/
	FishEmitter* fishEmitter1;
	FishEmitter* fishEmitter2;
	FishEmitter* fishEmitter3;

	/*�洢ģ���ļ�*/
	vector<ObjReader> objList;
	/*�洢ͼƬ�ļ�*/
	vector<ImageReader> imageList;

	/*�洢ʵ��ģ��*/
	vector<BaseModel*> modelList;
};

