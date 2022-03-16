#include "stdafx.h"
#include "Stage_0.h"

#include "Bumper.h"
#include "JumpBoard.h"
#include "Player.h"
#include "Stage_0_Ground.h"
#include "Stage_0_Wall.h"

Stage_0::Stage_0()
{

}

Stage_0::~Stage_0()
{

}

bool Stage_0::Start()
{
    m_levelRender.Init("Assets/modelData/Stage_0/Stage_0.tkl",
        [&](LevelObjectData& objData)
        {
            if (objData.EqualObjectName(L"Stage_0_Wall") == true)
            {
                m_stage_0_Wall = NewGO<Stage_0_Wall>(0, "stage_0_Wall");            //生成する。
                m_stage_0_Wall->SetPosition(objData.position);                      //座標を設定する。
                m_stage_0_Wall->SetScale(objData.scale);                            //サイズを設定する。
                m_stage_0_Wall->SetRotation(objData.rotation);                      //回転を設定する。
                return true;
            }
            else if (objData.EqualObjectName(L"Stage_0_Ground") == true)
            {
                m_stage_0_Ground = NewGO<Stage_0_Ground>(0, "stage_0_Ground");      //生成する。
                m_stage_0_Ground->SetPosition(objData.position);                    //座標を設定する。
                m_stage_0_Ground->SetScale(objData.scale);                          //サイズを設定する。
                m_stage_0_Ground->SetRotation(objData.rotation);                    //回転を設定する。
                return true;
            }
            else if (objData.ForwardMatchName(L"Stage_0_JumpBoard") == true)
            {
                auto jumpBoard = NewGO<JumpBoard>(0, "jumpBoard");                  //生成する。
                jumpBoard->SetPosition(objData.position);                           //座標を設定する。
                jumpBoard->SetScale(objData.scale);                                 //サイズを設定する。
                jumpBoard->SetRotation(objData.rotation);                           //回転を設定する。
                return true;
            }
            else if (objData.ForwardMatchName(L"Stage_0_Bumper") == true)
            {
                auto bumper = NewGO<Bumper>(0, "bumper");                           //生成する。
                bumper->SetPosition(objData.position);                              //座標を設定する。
                bumper->SetScale(objData.scale);                                    //サイズを設定する。
                bumper->SetRotation(objData.rotation);                              //回転を設定する。
                return true;
            }
        });
    return true;
}

void Stage_0::Update()
{
    m_levelRender.Update();
}

void Stage_0::Render(RenderContext(&rc))
{

}