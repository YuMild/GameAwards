#include "stdafx.h"
#include "Stage_0.h"

#include "Bumper.h"
#include "Drone.h"
#include "HoneyCombBlock.h"
#include "JumpBoard.h"
#include "Nut.h"
#include "Player.h"
#include "SignBoard.h"
#include "Stage_0_Ground.h"
#include "Stage_0_Wall.h"
#include "Volt.h"

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
            if (objData.EqualObjectName(L"Stage_0_Ground") == true)
            {
                m_stage_0_Ground = NewGO<Stage_0_Ground>(0, "stage_0_Ground");      //��������B
                m_stage_0_Ground->SetPosition(objData.position);                    //���W��ݒ肷��B
                m_stage_0_Ground->SetScale(objData.scale);                          //�T�C�Y��ݒ肷��B
                m_stage_0_Ground->SetRotation(objData.rotation);                    //��]��ݒ肷��B
                return true;
            }
            else if (objData.EqualObjectName(L"Stage_0_Wall") == true)
            {
                m_stage_0_Wall = NewGO<Stage_0_Wall>(0, "stage_0_Wall");            //��������B
                m_stage_0_Wall->SetPosition(objData.position);                      //���W��ݒ肷��B
                m_stage_0_Wall->SetScale(objData.scale);                            //�T�C�Y��ݒ肷��B
                m_stage_0_Wall->SetRotation(objData.rotation);                      //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Signboard") == true)
            {
                auto signBoard = NewGO<SignBoard>(0, "signBoard");                  //��������B
                signBoard->SetPosition(objData.position);                           //���W��ݒ肷��B
                signBoard->SetScale(objData.scale);                                 //�T�C�Y��ݒ肷��B
                signBoard->SetRotation(objData.rotation);                           //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Stage_0_JumpBoard") == true)
            {
                auto jumpBoard = NewGO<JumpBoard>(0, "jumpBoard");                  //��������B
                jumpBoard->SetPosition(objData.position);                           //���W��ݒ肷��B
                jumpBoard->SetScale(objData.scale);                                 //�T�C�Y��ݒ肷��B
                jumpBoard->SetRotation(objData.rotation);                           //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Stage_0_Bumper") == true)
            {
                auto bumper = NewGO<Bumper>(0, "bumper");                           //��������B
                bumper->SetPosition(objData.position);                              //���W��ݒ肷��B
                bumper->SetScale(objData.scale);                                    //�T�C�Y��ݒ肷��B
                bumper->SetRotation(objData.rotation);                              //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Drone") == true)
            {
                auto drone = NewGO<Drone>(0, "drone");                              //��������B
                drone->SetPosition(objData.position);                               //���W��ݒ肷��B
                drone->SetScale(objData.scale);                                     //�T�C�Y��ݒ肷��B
                drone->SetRotation(objData.rotation);                               //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"HoneyComb") == true)
            {
                auto honeyCombBlock = NewGO<HoneyCombBlock>(0, "honeyCombBlock");   //��������B
                honeyCombBlock->SetPosition(objData.position);                      //���W��ݒ肷��B
                honeyCombBlock->SetScale(objData.scale);                            //�T�C�Y��ݒ肷��B
                honeyCombBlock->SetRotation(objData.rotation);                      //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Nut") == true)
            {
                auto nut = NewGO<Nut>(0, "nut");                                    //��������B
                nut->SetPosition(objData.position);                                 //���W��ݒ肷��B
                nut->SetScale(objData.scale);                                       //�T�C�Y��ݒ肷��B
                nut->SetRotation(objData.rotation);                                 //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Volt") == true)
            {
                auto volt = NewGO<Volt>(0, "volt");                                 //��������B
                volt->SetPosition(objData.position);                                //���W��ݒ肷��B
                volt->SetScale(objData.scale);                                      //�T�C�Y��ݒ肷��B
                volt->SetRotation(objData.rotation);                                //��]��ݒ肷��B
                return true;
            }
        });
    return true;
}

void Stage_0::Update()
{
    m_levelRender.Update();
}