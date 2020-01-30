#include "FishModel.h"
#include "SceneManager.h"

extern SceneManager scene;
extern Float3 cameraPos;

FishModel::FishModel(Float3 position, Float3 rotation, Float3 scale, int objectId, int imgId, bool enableBlend, bool enableTwoSide)
	: BaseModel(position, rotation, scale, objectId, imgId, enableBlend, enableTwoSide)
{
	//�������ʼ����
	mPosition.y = mPosition.y + rand() % 300;
	mPosition.z = mPosition.z + rand() % 300;

	//������ٶ�
	speed = rand()% 5 / 10.0 + 2;

	//��ʼ������
	time = 0;
	angle = 0;
	this->waveRange = 60;

	//�������С
	float s = (float)(rand() % 5) / 5 + 1.0;
	mScale = Float3(s, s, s);

    //������XZƽ������������ľ���
	Float3 p1 = mPosition;
	p1.y = cameraPos.y;
	disFromCamera = (p1 - cameraPos).Length();

	//������������ľ�����뵽͸����Ⱦ���У�����������Ѿ�����ͬ�����������ڣ��򽫾���+1
	while (scene.translucentModel.count(disFromCamera))
	{
		disFromCamera++;
	}
	scene.translucentModel.insert(pair<int, BaseModel*>(disFromCamera, this));

}


FishModel::~FishModel()
{
	//�ͷų����ڵ��Լ�
	scene.translucentModel.erase(disFromCamera);
}

void FishModel::Init(float waveRange)
{
	//�����ζ�ƫ��
	this->waveRange = waveRange;
}

void FishModel::Render(ObjReader& obj, ImageReader& image)
{
	//��Ⱦ�����ͼƬû�м��ؾ�ֹͣ
	if (!image.IsLoad())
		return;

	// �ı�λ��
	glPushMatrix();
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glRotatef(mRotation.y + angle, 0.0, 1.0, 0.0);
	glScalef(mScale.x, mScale.y, mScale.z);

	//һ����Ķ���
	GLfloat vertices[][3] =
	{
		{-10.0f, 10.0f, 0.0f}, {-10.0f, -10.0f, 0.0f},
		{ 10.0f, 10.0f, 0.0f}, { 10.0f, -10.0f, 0.0f}
	};

	//������ϣ��趨��ɫ���ģʽ
	glEnable(GL_BLEND);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glDepthMask(false);	//������Ȼ�����ֻ��

	//��ͼƬ
	glBindTexture(GL_TEXTURE_2D, image.texID);

	//������
	GLfloat n[] = { 0, 0, 1 };
	glNormal3fv(n);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3fv(vertices[0]);

	glTexCoord2f(0, 1);
	glVertex3fv(vertices[1]);

	glTexCoord2f(1, 1);
	glVertex3fv(vertices[3]);

	glTexCoord2f(1, 0);
	glVertex3fv(vertices[2]);
	glEnd();

	glPopMatrix();
}

void FishModel::Tick()
{
	//��ʱ��+1
	time += 1;

	//ˢ����Ⱦ�б�
	scene.translucentModel.erase(disFromCamera);	//�Ƴ�֮ǰ��

	Float3 p1 = mPosition;
	p1.y = cameraPos.y;
	disFromCamera = (p1 - cameraPos).Length(); //�������ֵ
	while (scene.translucentModel.count(disFromCamera)) //�ж��Ƿ������ͬ���
	{
		disFromCamera++;
	}
	scene.translucentModel.insert(pair<int, BaseModel*>(disFromCamera, this));


	//���㵱ǰ��Ⱥ�Ƕ�ת��
	angle = sin(time/120.0f) * waveRange;
	float angle2 = (angle + mRotation.y) * 3.14 / 180.0;
	
	//�ζ�����
	Float3 dir(cos(angle2), 0, -sin(angle2));

	//����λ��
	mPosition = Float3(mPosition.x + dir.x * speed, mPosition.y + dir.y * speed, mPosition.z + dir.z * speed);
}
