#include "ModelQuad.h"

ModelQuad::ModelQuad(Float3 position, Float3 rotation, Float3 scale, int objectId, int imgId, bool enableBlend, bool enableTwoSide)
	:BaseModel(position, rotation, scale, objectId, imgId, enableBlend, enableTwoSide)
{

}

ModelQuad::~ModelQuad()
{
}

void ModelQuad::Render(ObjReader& obj, ImageReader& image)
{
    //���û��ָ��ģ�ͻ���ͼƬ��ֹͣ��Ⱦ
    if (!obj.IsLoad() || !image.IsLoad())
        return;

    //λ�þ���
    GLfloat T[][4] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {mPosition.x, mPosition.y, mPosition.z, 1} };
    //��Z����ת����
    GLfloat RZ[][4] = { {cos(mRotation.z * rotationTrans), sin(mRotation.z * rotationTrans), 0, 0}, {-sin(mRotation.z* rotationTrans), cos(mRotation.z * rotationTrans), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };
    //��X����ת����
    GLfloat RX[][4] = { {1, 0, 0, 0}, {0, cos(mRotation.x * rotationTrans), sin(mRotation.x * rotationTrans), 0}, {0, -sin(mRotation.x * rotationTrans), cos(mRotation.x * rotationTrans), 0}, {0, 0, 0, 1} };
    //��Y����ת����
    GLfloat RY[][4] = { {cos(mRotation.y * rotationTrans), 0, -sin(mRotation.y * rotationTrans), 0}, {0, 1, 0, 0}, {sin(mRotation.y * rotationTrans), 0, cos(mRotation.y * rotationTrans), 0}, {0, 0, 0, 1} };
    //���ž���
    GLfloat S[][4] = { {mScale.x, 0, 0, 0}, {0, mScale.y, 0, 0}, {0, 0, mScale.z, 0}, {0, 0, 0, 1} };

    // �ı�λ��
    glPushMatrix();
    glMultMatrixf(*T);
    glMultMatrixf(*RZ);
    glMultMatrixf(*RX);
    glMultMatrixf(*RY);
    glMultMatrixf(*S);

    //��ͼƬ
    glBindTexture(GL_TEXTURE_2D, image.texID);
    for (auto face : obj.faceArray)
    {
        //Ϊÿ�������÷��ߣ�����λ����Ϣ
        glBegin(GL_TRIANGLES);

        for (int i = 0; i < 3; i++)
        {
            GLfloat normal[3] = { obj.normalArray[face.normal[i] - 1].x, obj.normalArray[face.normal[i] - 1].y, obj.normalArray[face.normal[i] - 1].z };
            glNormal3fv(normal);

            //UV��չ10��
            GLfloat texCoord[3] = { obj.texcoordArray[face.Texcoord[i] - 1].x * 5, obj.texcoordArray[face.Texcoord[i] - 1].y * 5, obj.texcoordArray[face.Texcoord[i] - 1].z * 5};
            glTexCoord3fv(texCoord);

            GLfloat position[3] = { obj.vertexArray[face.position[i] - 1].x, obj.vertexArray[face.position[i] - 1].y, obj.vertexArray[face.position[i] - 1].z };
            glVertex3fv(position);
        }

        glEnd();
    }

    glPopMatrix();
}

void ModelQuad::Tick() 
{
}

