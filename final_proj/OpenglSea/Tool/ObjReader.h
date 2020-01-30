#pragma once
#include <stdlib.h>
#include <vector>

using namespace std;

/*
��ά���ݣ���������ʾλ�ã�����
*/
struct Float3 
{
	float x, y, z;

	Float3()
		: x(0), y(0), z(0)
	{
	}

	Float3(float x0, float y0, float z0)
		:x(x0), y(y0), z(z0)
	{
	}

	/*�õ���������*/
	float Length()
	{
		return sqrt(x*x + y * y + z * z);
	}

	/*���� - �����*/
	Float3& operator-(const Float3& right)
	{
		x = this->x - right.x;
		y = this->y - right.y;
		z = this->z - right.z;

		return *this;
	}
};

/*һ�����ڵ�����*/
struct Face 
{
	/*λ��*/
	int position[3];
	/*����*/
	int normal[3];
	/*��������*/
	int Texcoord[3];
};

/*ģ�Ͷ�ȡ��*/
class ObjReader
{
public:
	/*
	filename:ģ�ʹ��·��
	*/
    ObjReader(const char* filename);
	~ObjReader();

	/*�Ƿ��Ѿ����ص��ڴ�*/
	bool IsLoad();

	/*����λ������*/
	vector<Float3> vertexArray;
	/*��������*/
	vector<Float3> texcoordArray;
	/*��������*/
	vector<Float3> normalArray;
	/*�������*/
	vector<Face> faceArray;
	
private:
    bool ObjLoadModel(const char* filename);

	bool isLoad;
};

