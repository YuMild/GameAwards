#include "stdafx.h"
#include "Stage_0.h"

#include "Bumper.h"
#include "Drone.h"
#include "Energy.h"
#include "Goal.h"
#include "HoneyCombBlock.h"
#include "JumpBoard.h"
#include "Nut.h"
#include "Player.h"
#include "SignBoard.h"
#include "Stage_0_Ground.h"
#include "Stage_0_Wall.h"
#include "Turret.h"
#include "Volt.h"

Stage_0::Stage_0()
{

}

Stage_0::~Stage_0()
{
    DeleteGO(m_stage_0_Ground);
    DeleteGO(m_stage_0_Wall);
    const auto& bumpers = FindGOs<Bumper>("bumper");
    int bumperSize = bumpers.size();
    for (int i = 0; i < bumperSize; i++)
    {
        DeleteGO(bumpers[i]);
    }
    const auto& drones = FindGOs<Drone>("drone");
    int droneSize = drones.size();
    for (int i = 0; i < droneSize; i++)
    {
        DeleteGO(drones[i]);
    }
    const auto& energys = FindGOs<Energy>("energy");
    int energySize = energys.size();
    for (int i = 0; i < energySize; i++)
    {
        DeleteGO(energys[i]);
    }
    const auto& goals = FindGOs<Goal>("goal");
    int goalize = goals.size();
    for (int i = 0; i < goalize; i++)
    {
        DeleteGO(goals[i]);
    }
    const auto& honeyCombBlocks = FindGOs<HoneyCombBlock>("honeyCombBlock");
    int honeyCombBlockSize = honeyCombBlocks.size();
    for (int i = 0; i < honeyCombBlockSize; i++)
    {
        DeleteGO(honeyCombBlocks[i]);
    }
    const auto& jumpBoards = FindGOs<JumpBoard>("jumpBoard");
    int jumpBoardSize = jumpBoards.size();
    for (int i = 0; i < jumpBoardSize; i++)
    {
        DeleteGO(jumpBoards[i]);
    }
    const auto& nuts = FindGOs<Nut>("nut");
    int nutSize = nuts.size();
    for (int i = 0; i < nutSize; i++)
    {
        DeleteGO(nuts[i]);
    }
    const auto& signBoards = FindGOs<SignBoard>("signBoard");
    int signBoardSize = signBoards.size();
    for (int i = 0; i < signBoardSize; i++)
    {
        DeleteGO(signBoards[i]);
    }
    const auto& turrets = FindGOs<Turret>("turret");
    int turretSize = turrets.size();
    for (int i = 0; i < turretSize; i++)
    {
        DeleteGO(turrets[i]);
    }
    const auto& volts = FindGOs<Volt>("volt");
    int voltSize = volts.size();
    for (int i = 0; i < voltSize; i++)
    {
        DeleteGO(volts[i]);
    }
}

bool Stage_0::Start()
{
    m_levelRender.Init("Assets/modelData/Stage_0/Stage_0.tkl",
        [&](LevelObjectData& objData)
        {
            if (objData.EqualObjectName(L"Stage_0_Ground") == true)
            {
                m_stage_0_Ground = NewGO<Stage_0_Ground>(0, "stage_0_Ground");      //生成する。
                m_stage_0_Ground->SetPosition(objData.position);                    //座標を設定する。
                m_stage_0_Ground->SetScale(objData.scale);                          //サイズを設定する。
                m_stage_0_Ground->SetRotation(objData.rotation);                    //回転を設定する。
                return true;
            }
            else if (objData.EqualObjectName(L"Stage_0_Wall") == true)
            {
                m_stage_0_Wall = NewGO<Stage_0_Wall>(0, "stage_0_Wall");            //生成する。
                m_stage_0_Wall->SetPosition(objData.position);                      //座標を設定する。
                m_stage_0_Wall->SetScale(objData.scale);                            //サイズを設定する。
                m_stage_0_Wall->SetRotation(objData.rotation);                      //回転を設定する。
                return true;
            }
            else if (objData.ForwardMatchName(L"Signboard") == true)
            {
                auto signBoard = NewGO<SignBoard>(0, "signBoard");                  //生成する。
                signBoard->SetPosition(objData.position);                           //座標を設定する。
                signBoard->SetScale(objData.scale);                                 //サイズを設定する。
                signBoard->SetRotation(objData.rotation);                           //回転を設定する。
                return true;
            }
            else if (objData.ForwardMatchName(L"JumpBoard") == true)
            {
                auto jumpBoard = NewGO<JumpBoard>(0, "jumpBoard");                  //生成する。
                jumpBoard->SetPosition(objData.position);                           //座標を設定する。
                jumpBoard->SetScale(objData.scale);                                 //サイズを設定する。
                jumpBoard->SetRotation(objData.rotation);                           //回転を設定する。
                return true;
            }
            else if (objData.ForwardMatchName(L"Bumper") == true)
            {
                auto bumper = NewGO<Bumper>(0, "bumper");                           //生成する。
                bumper->SetPosition(objData.position);                              //座標を設定する。
                bumper->SetScale(objData.scale);                                    //サイズを設定する。
                bumper->SetRotation(objData.rotation);                              //回転を設定する。
                return true;
            }
            else if (objData.ForwardMatchName(L"Drone") == true)
            {
                auto drone = NewGO<Drone>(0, "drone");                              //生成する。
                drone->SetPosition(objData.position);                               //座標を設定する。
                drone->SetScale(objData.scale);                                     //サイズを設定する。
                drone->SetRotation(objData.rotation);                               //回転を設定する。
                return true;
            }
            else if (objData.ForwardMatchName(L"Energy") == true)
            {
                auto energy = NewGO<Energy>(0, "energy");                           //生成する。
                energy->SetPosition(objData.position);                              //座標を設定する。
                energy->SetScale(objData.scale);                                    //サイズを設定する。
                energy->SetRotation(objData.rotation);                              //回転を設定する。
                return true;
            }
            else if (objData.ForwardMatchName(L"Goal") == true)
            {
                auto goal = NewGO<Goal>(0, "goal");                                 //生成する。
                goal->SetPosition(objData.position);                                //座標を設定する。
                goal->SetScale(objData.scale);                                      //サイズを設定する。
                goal->SetRotation(objData.rotation);                                //回転を設定する。
                return true;
            }
            else if (objData.ForwardMatchName(L"HoneyComb") == true)
            {
                auto honeyCombBlock = NewGO<HoneyCombBlock>(0, "honeyCombBlock");   //生成する。
                honeyCombBlock->SetPosition(objData.position);                      //座標を設定する。
                honeyCombBlock->SetScale(objData.scale);                            //サイズを設定する。
                honeyCombBlock->SetRotation(objData.rotation);                      //回転を設定する。
                return true;
            }
            else if (objData.ForwardMatchName(L"Nut") == true)
            {
                auto nut = NewGO<Nut>(0, "nut");                                    //生成する。
                nut->SetPosition(objData.position);                                 //座標を設定する。
                nut->SetScale(objData.scale);                                       //サイズを設定する。
                nut->SetRotation(objData.rotation);                                 //回転を設定する。
                return true;
            }
            else if (objData.ForwardMatchName(L"Turret") == true)
            {
                auto turret = NewGO<Turret>(0, "turret");                           //生成する。
                turret->SetPosition(objData.position);                              //座標を設定する。
                turret->SetScale(objData.scale);                                    //サイズを設定する。
                turret->SetRotation(objData.rotation);                              //回転を設定する。
                return true;
            }
            else if (objData.ForwardMatchName(L"Volt") == true)
            {
                auto volt = NewGO<Volt>(0, "volt");                                 //生成する。
                volt->SetPosition(objData.position);                                //座標を設定する。
                volt->SetScale(objData.scale);                                      //サイズを設定する。
                volt->SetRotation(objData.rotation);                                //回転を設定する。
                return true;
            }
        });
    return true;
}

void Stage_0::Update()
{
    m_levelRender.Update();
}