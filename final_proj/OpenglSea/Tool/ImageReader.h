#pragma once

#include <QtGui/qimage.h>
#include <stdlib.h>
#include <GL/glew.h>

/*ͼƬ��ȡ����*/
class ImageReader
{
public:
	ImageReader();
	/*
	filename:ͼƬ���·��
	*/
    ImageReader(const char* filename);
	~ImageReader();

	/*�Ƿ��Ѿ����ص��ڴ�*/
	bool IsLoad();

	/*ͼƬ����*/
	QImage image;
	/*�󶨵�Opengl��ͼƬID*/
	GLuint texID;

private:
	/*
	����ͼƬ���ڴ�
	filename:ͼƬ���·��
	*/
    bool LoadTexture(const char* filename);

	/*�Ƿ��Ѿ����ص��ڴ�ı�־*/
	bool isLoad;
};

