#include "SceneGame.h"
#include "./GameLib/game_lib.h"
#include "WinMain.h"
#include "SpriteData.h"
#include "Obj2d.h"

// 定数宣言
static constexpr int BACK_MAX = 2;
static constexpr int ENRMY_MAX = 10;//(1)add
// 変数宣言
OBJ2D player;
OBJ2D backs[BACK_MAX];
OBJ2D enemies[ENRMY_MAX];//(2)敵の配列　add



// プロトタイプ宣言(更新に関する)
void backUpdate(OBJ2D* obj);  //背景更新処理
void playerUpdate(OBJ2D* obj);//プレイヤー更新処理
void enemySample(OBJ2D* obj); //敵の更新処理
//C 
void enemyKadai1(OBJ2D* obj);
void enemyKadai2(OBJ2D* obj);


void SceneGame::init()
{
    // テクスチャのロード
    GameLib::texture::load(loadTexture);

    // 背景初期設定
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

    // プレイヤー初期設定
    player.sprData = &sprPlayer;
    player.position = { 640, 360 };

    // 敵キャラ初期設定
    enemies[0].init();//追加

}

void SceneGame::deinit()
{
    GameLib::texture::release(loadTexture);
}
/*--------------------------------
    SceneGame::update
    更新処理

----------------------------------*/
void SceneGame::update()
{
    //(1)背景更新
    for (auto& back : backs)
    {
        backUpdate(&back);
    }

    // (2)プレイヤー更新
    playerUpdate(&player);

    // (3)敵キャラ更新(追加) 位置を更新する
    enemySample(&enemies[0]);

    // シーン切り替えチェック
    if (GameLib::input::TRG(0) & GameLib::input::PAD_START) { setScene(SCENE::TITLE); }
}

void backUpdate(OBJ2D* obj)
{
    obj->position.x -= 4;

    // スクロール処理
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
// 関数名　void enemySample
// 引数　　OBJ2D* obj
// 戻り値　なし
// 　　　　敵サンプル
//------------------------------------------------------------------
void enemySample(OBJ2D* obj)
{

    //obj->stateを4ンパターン
    switch (obj->state) {
    case 0:
        obj->sprData = &sprEnemy;//画像をロードする
        obj->position = { 1280 + 64,160 };
        obj->state++;
        break;
    case 1:
        obj->position.x -= 8;        //左へ移動
        if (obj->position.x < 128) {//128より小さくなったら
            obj->state++;           //次の状態へ行く(state2)
        }
        break;
    case 2:
        obj->position.x += 8;        //右下がりの処理
        obj->position.y += 8;        //（比例）
        if (obj->position.y > 480)
            obj->state++;
        break;
    case 3:
        obj->position.x += 8;//右へ移動
        break;

    }

}


//----------------------------------------------------------------
// 敵移動処理①
// 関数　enemyKadai1
/*
状態
処理内容
0 画像：sprEnemy、初期位置：(1280+200, 160)初期設定を行ったら次の状態へ
1 X方向：-8  X座標 < 960 になったら次の状態へ
2 X方向：+8、Y方向：+8 Y座標 > 320 になったら次の状態へ
3 X方向：-8 X座標 < 180 になったら次の状態へ
4 X方向：+8、Y方向：+8 Y座標 > 480 になったら次の状態へ
5 X方向：+8
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
// 敵移動処理②
void enemyKadai2(OBJ2D* obj) {





}

void SceneGame::draw()
{
    // 画面をクリア
    GameLib::clear(0, 0, 0);

    // 背景描画
    for (auto& back : backs)
    {
        back.draw();
    }

    // プレイヤー描画
    player.draw();

    // 敵キャラ描画(追加)
#define ENMY_NUM 3
    for(int i=0;i< ENMY_NUM ;i++)
       enemies[i].draw();
    
    
    
    // 文字列描画
    GameLib::font::textOut(4, "SAMPLE",  enemies[0].position + VECTOR2(0, -48), { 1, 1 }, { 1,1,1,1 }, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::font::textOut(4, "KADAI_1", enemies[1].position + VECTOR2(0, -48), { 1, 1 }, { 0,1,1,1 }, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::font::textOut(4, "KADAI_2", enemies[2].position + VECTOR2(0, -48), { 1, 1 }, { 0,1,1,1 }, GameLib::TEXT_ALIGN::MIDDLE);

    GameLib::font::textOut(4, "PRESS [SPACE] TO TITLE", { 0, 700 }, { 2, 2 },
        { 1, 1, 0, 1 }, GameLib::TEXT_ALIGN::MIDDLE_LEFT);
}
