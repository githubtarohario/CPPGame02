#pragma once

#include "./GameLib/game_lib.h"
#include "./GameLib/obj2d_data.h"

class OBJ2D
{
public:
    GameLib::SpriteData* sprData;
    VECTOR2 position;
    VECTOR2 scale;
    float rotation;
    VECTOR4 color;
    GameLib::Blender::BLEND_STATE blendState;
    
    //追加
    int state;       //状態
    VECTOR2 velocity;//速度
    //---------------------------------
    //コンストラクター
    OBJ2D() { 
        init(); 
    }

    void init()
    {
        sprData = nullptr;
        position = {};
        scale = { 1,1 };
        rotation = 0.0f;
        color = { 1,1,1,1 };
        blendState = GameLib::Blender::BLEND_STATE::BS_ALPHA;
        //状態と速度を初期設定(追加)
        state = 0;
        velocity = {};
        //--------------------------------------
    }

    void clear() { init(); }

    void draw();
};
