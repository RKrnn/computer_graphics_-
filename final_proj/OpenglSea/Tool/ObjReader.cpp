#include <iostream>
#include <sstream>
#include <fstream>
#include "Tool/ObjReader.h"
#include <QtCore/qdir.h>

using namespace std;

ObjReader::ObjReader(const char* filename)
{
	isLoad = false;

	ObjLoadModel(filename);
}

ObjReader::~ObjReader()
{

}

bool ObjReader::ObjLoadModel(const char* filename)
{
    // ת���ɾ���·��
    string dir = QDir::currentPath().toStdString() + "/" + filename;
    const char* s = dir.c_str();

    ifstream file;
	// ���ļ�,��������
    file.open(s, ios_base::in);
	if (!file.is_open())
	{
		cout << "open file failed." << endl;
		return false;
	}

	string temp; // �����޹���Ϣ
	char szoneLine[256]; // ��ȡһ�е�����

	// ѭ����ȡ
	while (file)
	{
		file.getline(szoneLine, 256);

		if (strlen(szoneLine) > 0) // ���в�Ϊ��
		{
			if (szoneLine[0] == 'v') // ��ȡv��ͷ������
			{
				stringstream ssOneLine(szoneLine); // ���ݴ洢��stringstream��
				if (szoneLine[1] == 't') // ������Ϣ
				{
					ssOneLine >> temp; //���ձ�ʶ��vt

					Float3 tempTexcoord; // ������������
					ssOneLine >> tempTexcoord.x >> tempTexcoord.y >> tempTexcoord.z; // �洢��������
					tempTexcoord.y = 1 - tempTexcoord.y;	//����������·�ת����
					texcoordArray.push_back(tempTexcoord); // �����������������
				}
				else if (szoneLine[1] == 'n') // ��¼�ķ�����Ϣ
				{
					ssOneLine >> temp; //���ձ�ʶ��vn

					Float3 tempNormal;  //������������
					ssOneLine >> tempNormal.x >> tempNormal.y >> tempNormal.z; // �洢��������
					normalArray.push_back(tempNormal);//��������Ϣ��������
				}
				else if (szoneLine[1] == ' ') // ���λ����Ϣ
				{
					ssOneLine >> temp; //���ձ�ʶ��v

					Float3 tempLocation; //λ������
					ssOneLine >> tempLocation.x >> tempLocation.y >> tempLocation.z; //�洢λ������
					vertexArray.push_back(tempLocation); // ��λ�������������
				}
			}
			else if (szoneLine[0] == 'f') //��¼����Ϣ
			{
				stringstream ssOneLine(szoneLine); //��ȡһ������
				ssOneLine >> temp; //���ձ�ʶ��f

				// һ�е���������:f 1/1/1 2/2/2 3/3/3 
				// �ֱ��ʾ:λ������/��������/��������   �����㹹��һ����
				// ����������1/1/1��һ������
				string vertexStr;
				Face tempFace; // �����
				for (int i = 0; i < 3; ++i) // ÿ����3����
				{
					ssOneLine >> vertexStr; // �����ж�ȡ���������Ϣ
					size_t pos = vertexStr.find_first_of('/'); // �ҵ���һ��'/'��λ��,���ҵ����λ����Ϣ
					string locIndexStr = vertexStr.substr(0, pos); // ����λ����Ϣ
					size_t pos2 = vertexStr.find_first_of('/', pos + 1); // �ҵ��ڶ���'/',���ҵ��������������Ϣ

					tempFace.position[i] = atoi(locIndexStr.c_str()); // ��������Ϣ�� srtingת��Ϊint,����λ��������Ϣ��ֵ

					if (pos2 - pos == 1) // �����˫б�ߵ������'//',���� 1//1
					{
						string norIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - pos2 - 1); // ��ȡ������Ϣ

						tempFace.normal[i] = atoi(norIndexStr.c_str());
						tempFace.Texcoord[i] = 0; // ��־Ϊ0���ں�������ʱ�����0�ţ�0,0��0��
					}
					else // ��б�ߵ���������� 1/1/1
					{
						string texIndexSrt = vertexStr.substr(pos + 1, pos2 - 1 - pos); // ���������Ϣ
						string norIndexSrt = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2); // ��ķ�����Ϣ

						tempFace.normal[i] = atoi(norIndexSrt.c_str()); //�洢����������Ϣ
						tempFace.Texcoord[i] = atoi(texIndexSrt.c_str()); //�洢����������Ϣ
					}
				}
				faceArray.push_back(tempFace);
			}
		}

	}

	//��ֹû������������������������Ĭ��ֵ
	if (texcoordArray.size() == 0)
		texcoordArray.push_back(Float3(0, 0, 0)); 

	cout << "load model: " << filename << endl;

	file.close();
	isLoad = true;
	return true;
}


bool ObjReader::IsLoad()
{
	return isLoad;
}
