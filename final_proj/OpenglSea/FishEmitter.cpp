#include "FishEmitter.h"
#include "SceneManager.h"

/*###################################################
##  ����: FishEmitter
##  ���������� FishEmitter��Ĺ��캯����ʹ�ô���Ĳ�����ʼ��
            ��Ա������fishes����Ⱥ���У��Զ���ʼ��Ϊ�ն���
##  ����������
## freTime:ÿ�����ʱ������һ����
## fishNum:�������������������������������������
## pos:������λ�ã����ʼ�ο�����
## rot:��������ת�ȣ����ʼ�ο���ת��
## objectID:���ģ��ID�ţ�ʵ�����㲻��Ҫ�õ���ֻ�Ǽ̳��˻��������
## imgID:��ģ�͵�ͼƬ��
## waveRange:���ζ���·��ƫ�ƽǶ�
#####################################################*/
FishEmitter::FishEmitter(int freTime, int fishNum, Float3 pos, Float3 rot, int objectId, int imgId, float waveRange)
{
	//��ʼ����Ϣ
	time = freTime;
	num = fishNum;
	mPosition = pos;
	mRotation = rot;
	freTimeCount = 0;

	this->objectId = objectId;
	this->imgId = imgId;
	this->waveRange = waveRange;
}

/*###################################################
##  ����: ~FishEmitter
##  ���������� FishEmitter��������������ͷŶ����е���Ⱥ
##  ������������
#####################################################*/
FishEmitter::~FishEmitter()
{	
	//�ͷ���
	for (auto cur : fishes)
	{
		delete cur;
	}

	fishes.clear();
}

/*###################################################
##  ����: Tick
##  ���������� ÿ֡����ʱ��������������Ե�����Ⱥ������µ��㣬�������
            �����ﵽ����ɾ�����ȼ������
##  ������������
#####################################################*/
void FishEmitter::Tick()
{
	//ˢ��ʱ�������
	freTimeCount += 1;
	if (freTimeCount > time)
	{
		freTimeCount = 0;

		//����һ������
		FishModel* cur = new FishModel(mPosition, mRotation, Float3(1, 1, 1), objectId, imgId);
		cur->Init(waveRange);
		fishes.push_back(cur);
		//�����������������ͷŶ�����ǰ������
		if (fishes.size() > num)
		{
			delete fishes.front();
			fishes.pop_front();
		}
	}

}
