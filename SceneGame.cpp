#include "SceneGame.h"
#include "./GameLib/game_lib.h"
#include "WinMain.h"
#include "SpriteData.h"
#include "Obj2d.h"

// �萔�錾
static constexpr int BACK_MAX = 2;
static constexpr int ENRMY_MAX = 10;//(1)add
// �ϐ��錾
OBJ2D player;
OBJ2D backs[BACK_MAX];
OBJ2D enemies[ENRMY_MAX];//(2)�G�̔z��@add



// �v���g�^�C�v�錾(�X�V�Ɋւ���)
void backUpdate(OBJ2D* obj);  //�w�i�X�V����
void playerUpdate(OBJ2D* obj);//�v���C���[�X�V����
void enemySample(OBJ2D* obj); //�G�̍X�V����
//C 
void enemyKadai1(OBJ2D* obj);
void enemyKadai2(OBJ2D* obj);


void SceneGame::init()
{
    // �e�N�X�`���̃��[�h
    GameLib::texture::load(loadTexture);

    // �w�i�����ݒ�
    VECTOR2 backPosition[] = {
        { 0,0 }, 
        { 1280,0 }, 
    };
    int index = 0;
    for (auto& back : backs)
    {
        back.sprData = &sprBack;
        back.position = backPosition[index++];
    }

    // �v���C���[�����ݒ�
    player.sprData = &sprPlayer;
    player.position = { 640, 360 };

    // �G�L���������ݒ�
    enemies[0].init();//�ǉ�

}

void SceneGame::deinit()
{
    GameLib::texture::release(loadTexture);
}
/*--------------------------------
    SceneGame::update
    �X�V����

----------------------------------*/
void SceneGame::update()
{
    //(1)�w�i�X�V
    for (auto& back : backs)
    {
        backUpdate(&back);
    }

    // (2)�v���C���[�X�V
    playerUpdate(&player);

    // (3)�G�L�����X�V(�ǉ�) �ʒu���X�V����
    enemySample(&enemies[0]);

    // �V�[���؂�ւ��`�F�b�N
    if (GameLib::input::TRG(0) & GameLib::input::PAD_START) { setScene(SCENE::TITLE); }
}

void backUpdate(OBJ2D* obj)
{
    obj->position.x -= 4;

    // �X�N���[������
    if (obj->position.x < -1280)
    {
        obj->position.x += 1280 * 2;
    }
}

void playerUpdate(OBJ2D* obj)
{
    if (GameLib::input::STATE(0) & GameLib::input::PAD_UP)      obj->position.y -= 8;
    if (GameLib::input::STATE(0) & GameLib::input::PAD_DOWN)    obj->position.y += 8;
    if (GameLib::input::STATE(0) & GameLib::input::PAD_LEFT)    obj->position.x -= 8;
    if (GameLib::input::STATE(0) & GameLib::input::PAD_RIGHT)   obj->position.x += 8;
}


//----------------------------------------------------------------
// �֐����@void enemySample
// �����@�@OBJ2D* obj
// �߂�l�@�Ȃ�
// �@�@�@�@�G�T���v��
//------------------------------------------------------------------
void enemySample(OBJ2D* obj)
{

    //obj->state��4���p�^�[��
    switch (obj->state) {
    case 0:
        obj->sprData = &sprEnemy;//�摜�����[�h����
        obj->position = { 1280 + 64,160 };
        obj->state++;
        break;
    case 1:
        obj->position.x -= 8;        //���ֈړ�
        if (obj->position.x < 128) {//128��菬�����Ȃ�����
            obj->state++;           //���̏�Ԃ֍s��(state2)
        }
        break;
    case 2:
        obj->position.x += 8;        //�E������̏���
        obj->position.y += 8;        //�i���j
        if (obj->position.y > 480)
            obj->state++;
        break;
    case 3:
        obj->position.x += 8;//�E�ֈړ�
        break;

    }

}


//----------------------------------------------------------------
// �G�ړ������@
// �֐��@enemyKadai1
/*
���
�������e
0 �摜�FsprEnemy�A�����ʒu�F(1280+200, 160)�����ݒ���s�����玟�̏�Ԃ�
1 X�����F-8  X���W < 960 �ɂȂ����玟�̏�Ԃ�
2 X�����F+8�AY�����F+8 Y���W > 320 �ɂȂ����玟�̏�Ԃ�
3 X�����F-8 X���W < 180 �ɂȂ����玟�̏�Ԃ�
4 X�����F+8�AY�����F+8 Y���W > 480 �ɂȂ����玟�̏�Ԃ�
5 X�����F+8
*/
void enemyKadai1(OBJ2D* obj) {
    switch (obj->state) {
    case 0:

        break;
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;



    }





}

//----------------------------------------------------------------
// �G�ړ������A
void enemyKadai2(OBJ2D* obj) {





}

void SceneGame::draw()
{
    // ��ʂ��N���A
    GameLib::clear(0, 0, 0);

    // �w�i�`��
    for (auto& back : backs)
    {
        back.draw();
    }

    // �v���C���[�`��
    player.draw();

    // �G�L�����`��(�ǉ�)
#define ENMY_NUM 3
    for(int i=0;i< ENMY_NUM ;i++)
       enemies[i].draw();
    
    
    
    // ������`��
    GameLib::font::textOut(4, "SAMPLE",  enemies[0].position + VECTOR2(0, -48), { 1, 1 }, { 1,1,1,1 }, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::font::textOut(4, "KADAI_1", enemies[1].position + VECTOR2(0, -48), { 1, 1 }, { 0,1,1,1 }, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::font::textOut(4, "KADAI_2", enemies[2].position + VECTOR2(0, -48), { 1, 1 }, { 0,1,1,1 }, GameLib::TEXT_ALIGN::MIDDLE);

    GameLib::font::textOut(4, "PRESS [SPACE] TO TITLE", { 0, 700 }, { 2, 2 },
        { 1, 1, 0, 1 }, GameLib::TEXT_ALIGN::MIDDLE_LEFT);
}
