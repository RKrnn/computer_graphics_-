#include "SceneManager.h"
#include "BaseModel.h"
#include "Model/waveplantsmodel.h"

extern Float3 cameraPos;

/*###################################################
##  ������SceneManager
##  ����������SceneManager��Ĺ��캯�����ÿ�
##  ������������
#####################################################*/
SceneManager::SceneManager()
{
}

/*###################################################
##  ������~SceneManager
##  ����������SceneManager�������������ɾ��ģ���ͷ���Ⱥ��
##          ɾ����͸�����塣
##  ������������
#####################################################*/
SceneManager::~SceneManager()
{
	for (auto cur : modelList)
	{
		delete cur;
	}

	//�����ͷţ�Ϊ�����ȴ�translucentModel�Ƴ�����
	delete fishEmitter1;
	delete fishEmitter2;
	delete fishEmitter3;

	for (auto cur : translucentModel)
	{
		delete cur.second;
	}

	modelList.clear();
	translucentModel.clear();
}

/*###################################################
##  ������Init
##  ����������SceneManager��ĳ�ʼ����������ʼ��ģ�͡���պ�
##          ���ա���Ȼ�������ʼ����Ⱥ��������
##  ������������
#####################################################*/
void SceneManager::Init()
{
	InitModel();

	InitSky();
	InitLight();
	InitFog();

	//��ʼ����Ⱥ������
	fishEmitter1 = new FishEmitter(10, 100, Float3(-10, 100, 50), Float3(0, 25, 0), 12, 12, 40);
	fishEmitter2 = new FishEmitter(10, 100, Float3(-10, 100, -100), Float3(0, 0, 0), 12, 13, -30);
	fishEmitter3 = new FishEmitter(10, 100, Float3(-10, 100, -100), Float3(0, 0, 0), 12, 14, -60);
}

/*###################################################
##  ������Update
##  �������������º�����ÿ��������ա�����ģ�ͺͰ�͸�����壬
##          ��������Ⱥλ�ú���Ⱦģ�ͺͰ�͸�����塣
##  ������������
#####################################################*/
void SceneManager::Update()
{
	SetSky();

	for (auto cur : modelList)
	{
		cur->Update();
	}

	map<int, BaseModel*> temp = translucentModel; //��ֹupdate()�ڶ��б�ĸ���
	for (auto cur : temp)
	{
		cur.second->Update();
	}

	//��Ⱥ����λ��
	fishEmitter1->Tick();
	fishEmitter2->Tick();
	fishEmitter3->Tick();

	//����Ⱦʵ��
	for (auto cur : modelList)
	{
		cur->Render(objList[cur->objId], imageList[cur->imageId]);
	}

	//����Ⱦ͸�����壬����Map��Ԫ���Զ������ܣ�����ȴ�С����͸������
	for (map<int, BaseModel*>::reverse_iterator cur = translucentModel.rbegin(); cur != translucentModel.rend(); cur++)
	{
		(*cur).second->Render(objList[(*cur).second->objId], imageList[(*cur).second->imageId]);
	}
}

/*###################################################
##  ������InitModel
##  ��������������ģ�ͺ�ͼƬ���ڴ棬����ʵ������Ͱ�͸������ӵ�
##          ģ���б��С�
##  ������������
#####################################################*/
void SceneManager::InitModel()
{
	//����ģ�ͽ��ڴ�
    objList.push_back(ObjReader("objMesh/SM_URockB.obj")); //0
    objList.push_back(ObjReader("objMesh/SM_URockC.obj")); //1
    objList.push_back(ObjReader("objMesh/SM_URockD.obj")); //2
    objList.push_back(ObjReader("objMesh/SM_RedAlgaeB.obj"));	//3
    objList.push_back(ObjReader("objMesh/SM_RedAlgaeC.obj"));	//4
    objList.push_back(ObjReader("objMesh/SM_SeaweedA.obj"));	//5
    objList.push_back(ObjReader("objMesh/SM_SeaweedC.obj"));	//6
    objList.push_back(ObjReader("objMesh/SM_SeaweedD.obj"));	//7
    objList.push_back(ObjReader("objMesh/SM_SpongeB.obj"));	//8
    objList.push_back(ObjReader("objMesh/SM_SpongeC.obj"));	//9
    objList.push_back(ObjReader("objMesh/SM_AlgaeA.obj"));	//10
    objList.push_back(ObjReader("objMesh/SM_CorallineB.obj"));	//11
    objList.push_back(ObjReader("objMesh/SM_land.obj")); //12

    //����ͼƬ���ڴ�
    imageList.push_back(ImageReader("Textures/T_URockB_BC.png"));	//0
    imageList.push_back(ImageReader("Textures/T_URockC_BC.png"));	//1
    imageList.push_back(ImageReader("Textures/T_URockD_BC.png"));	//2
    imageList.push_back(ImageReader("Textures/T_FishA_BC.png"));	//3
    imageList.push_back(ImageReader("Textures/T_FishB_BC.png"));	//4
    imageList.push_back(ImageReader("Textures/T_FishC_BC.png"));	//5
    imageList.push_back(ImageReader("Textures/T_RedAlgae_BC.png"));	//6
    imageList.push_back(ImageReader("Textures/T_Seaweed_BC.png"));		//7
    imageList.push_back(ImageReader("Textures/T_Sponge_BC.png"));		//8
    imageList.push_back(ImageReader("Textures/T_SandDunes_BC.png"));		//9
    imageList.push_back(ImageReader("Textures/T_Algae_BC.png"));		//10
    imageList.push_back(ImageReader("Textures/T_Coralline_BC.png"));		//11
    imageList.push_back(ImageReader("Textures/T_FishA_BC.png"));		//12
    imageList.push_back(ImageReader("Textures/T_FishB_BC.png"));		//13
    imageList.push_back(ImageReader("Textures/T_FishC_BC.png"));		//14


	//ʵ������, ����Ҫ����
	modelList.push_back(new BaseModel(Float3(340, 0, -240), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 0, 0));
	modelList.push_back(new BaseModel(Float3(420, 0, -110), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 1, 1));
	modelList.push_back(new BaseModel(Float3(570, 100, -230), Float3(0, 0, 60), Float3(1.0, 1.0, 1.0), 2, 2));
	modelList.push_back(new BaseModel(Float3(1340, 170, 1190), Float3(0, 0, 0), Float3(3.0, 3.0, 3.0), 2, 2));
	modelList.push_back(new BaseModel(Float3(380, 0, 190), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 8, 8));
	modelList.push_back(new BaseModel(Float3(960, 0, -40), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 9, 8));
	modelList.push_back(new BaseModel(Float3(850, 0, 440), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 9, 8));
	modelList.push_back(new BaseModel(Float3(460, 0, 20), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 10, 10));
	modelList.push_back(new BaseModel(Float3(900, 0, -710), Float3(0, 270, 0), Float3(2.0, 2.0, 2.0), 11, 11));
    modelList.push_back(new ModelQuad(Float3(0, 0, 0), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 12, 9));

	//͸������
    translucentModel.insert(pair<int, BaseModel*>((Float3(420, cameraPos.y, 380) - cameraPos).Length(), new WavePlantMode(Float3(420, -30, 380), Float3(0, 30, 0), Float3(1.0, 1.0, 1.0), 7, 7, 100)));
    translucentModel.insert(pair<int, BaseModel*>((Float3(480, cameraPos.y, 330) - cameraPos).Length(), new WavePlantMode(Float3(480, -30, 330), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 7, 7, 100)));
    translucentModel.insert(pair<int, BaseModel*>((Float3(590, cameraPos.y, -200) - cameraPos).Length(), new WavePlantMode(Float3(590, 230, -200), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 3, 6, 10)));
    translucentModel.insert(pair<int, BaseModel*>((Float3(670, cameraPos.y, -60) - cameraPos).Length(), new WavePlantMode(Float3(670, 10, -60), Float3(0, 60, 0), Float3(1.0, 1.0, 1.0), 6, 7, 30)));
    translucentModel.insert(pair<int, BaseModel*>((Float3(670, cameraPos.y, 260) - cameraPos).Length(), new WavePlantMode(Float3(670, 30, 260), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 5, 7, 30)));
    translucentModel.insert(pair<int, BaseModel*>((Float3(770, cameraPos.y, -620) - cameraPos).Length(), new WavePlantMode(Float3(770, -30, -620), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 5, 7, 30)));
    translucentModel.insert(pair<int, BaseModel*>((Float3(960, cameraPos.y, 740) - cameraPos).Length(), new WavePlantMode(Float3(960, -10, 740), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 3, 6, 10)));
    translucentModel.insert(pair<int, BaseModel*>((Float3(800, cameraPos.y, 90) - cameraPos).Length(), new WavePlantMode(Float3(800, 0, 200), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 4, 6, 10)));
    translucentModel.insert(pair<int, BaseModel*>((Float3(1100, cameraPos.y, 400) - cameraPos).Length(), new WavePlantMode(Float3(1100, -30, 350), Float3(0, 0, 0), Float3(1.0, 1.0, 1.0), 6, 7, 30)));
}

/*###################################################
##  ������InitSky
##  ��������������ͼƬ������Ƭ�����������
##  ������������
#####################################################*/
void SceneManager::InitSky()
{
	//�������
	sky = ImageReader("Textures\\sky.png");
}

/*###################################################
##  ������SetSky
##  ������������ͼƬͨ����ת�ȱ任��Ϊ��ʵ�ȸе����
##  ������������
#####################################################*/
void SceneManager::SetSky()
{
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	
	GLUquadricObj *quadratic = gluNewQuadric();
	gluQuadricTexture(quadratic, GL_TRUE);
	gluQuadricOrientation(quadratic, GLU_INSIDE);
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	glBindTexture(GL_TEXTURE_2D, sky.texID);
	gluSphere(quadratic, 10000, 30, 30);
	
	glPopMatrix();
}


/*###################################################
##  ������InitLight
##  ������������ʼ�����գ�ȫ�ֹ���
##  ������������
#####################################################*/
void SceneManager::InitLight()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat LightAmbient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat LightDiffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat LightPosition[] = { 0.0f, 200.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
}

/*###################################################
##  ������InitFog
##  ������������ʼ����ʵ��Զ���Ա�Ч��
##  ������������
#####################################################*/
void SceneManager::InitFog()
{
	glEnable(GL_FOG);

    GLfloat fogColor[] = { 0.2f, 0.45f, 0.7f, 1.0f};

	glFogi(GL_FOG_MODE, GL_LINEAR); //����������
	glFogfv(GL_FOG_COLOR, fogColor); //������ɫ
	glFogf(GL_FOG_START, 0.0);		//��ʼλ�þ������������
    glFogf(GL_FOG_END, 1500);		//�����λ�þ������������
}
