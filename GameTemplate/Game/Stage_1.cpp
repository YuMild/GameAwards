#include "stdafx.h"
#include "Stage_1.h"

#include "BreakBox.h"
#include "Bumper.h"
#include "CheckPoint.h"
#include "Door.h"
#include "Drone.h"
#include "Energy.h"
#include "Goal.h"
#include "HoneyCombBlock.h"
#include "JumpBoard.h"
#include "Nut.h"
#include "Player.h"
#include "SignBoard.h"
#include "SpeedUpRail.h"
#include "Stage_1_Stage.h"
#include "Turret.h"
#include "Volt.h"

Stage_1::Stage_1()
{

}

Stage_1::~Stage_1()
{
    const auto& breakBoxs = FindGOs<BreakBox>("breakBox");
    int breakBoxSize = breakBoxs.size();
    for (int i = 0; i < breakBoxSize; i++)
    {
        DeleteGO(breakBoxs[i]);
    }
    const auto& bumpers = FindGOs<Bumper>("bumper");
    int bumperSize = bumpers.size();
    for (int i = 0; i < bumperSize; i++)
    {
        DeleteGO(bumpers[i]);
    }
    const auto& checkPoints = FindGOs<CheckPoint>("checkPoint");
    int checkPointSize = checkPoints.size();
    for (int i = 0; i < checkPointSize; i++)
    {
        DeleteGO(checkPoints[i]);
    }
    const auto& doors = FindGOs<Door>("door");
    int doorSize = doors.size();
    for (int i = 0; i < doorSize; i++)
    {
        DeleteGO(doors[i]);
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
    const auto& speedUpRails = FindGOs<SpeedUpRail>("speedUpRail");
    int speedUpRailSize = speedUpRails.size();
    for (int i = 0; i < speedUpRailSize; i++)
    {
        DeleteGO(speedUpRails[i]);
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

bool Stage_1::Start()
{
    m_levelRender.Init("Assets/modelData/Stage_0/Stage_0.tkl",
        [&](LevelObjectData& objData)
        {
            if (objData.EqualObjectName(L"Stage_1") == true)
            {
                m_stage_1_Stage = NewGO<Stage_1_Stage>(0, "stage_1_Stage");         //��������B
                m_stage_1_Stage->SetPosition(objData.position);                     //���W��ݒ肷��B
                m_stage_1_Stage->SetScale(objData.scale);                           //�T�C�Y��ݒ肷��B
                m_stage_1_Stage->SetRotation(objData.rotation);                     //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"box") == true)
            {
                m_levelRender.InitBoxCollider(objData);
                return true;
            }
            else if (objData.ForwardMatchName(L"BreakBox") == true)
            {
                auto breakBox = NewGO<BreakBox>(0, "breakBox");                     //��������B
                breakBox->SetPosition(objData.position);                            //���W��ݒ肷��B
                breakBox->SetScale(objData.scale);                                  //�T�C�Y��ݒ肷��B
                breakBox->SetRotation(objData.rotation);                            //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Bumper") == true)
            {
                auto bumper = NewGO<Bumper>(0, "bumper");                           //��������B
                bumper->SetPosition(objData.position);                              //���W��ݒ肷��B
                bumper->SetScale(objData.scale);                                    //�T�C�Y��ݒ肷��B
                bumper->SetRotation(objData.rotation);                              //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"RespawnPoint") == true)
            {
                auto checkPoint = NewGO<CheckPoint>(0, "checkPoint");               //��������B
                checkPoint->SetPosition(objData.position);                          //���W��ݒ肷��B
                checkPoint->SetScale(objData.scale);                                //�T�C�Y��ݒ肷��B
                checkPoint->SetRotation(objData.rotation);                          //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Door") == true)
            {
                auto door = NewGO<Door>(0, "door");                              //��������B
                door->SetPosition(objData.position);                               //���W��ݒ肷��B
                door->SetScale(objData.scale);                                     //�T�C�Y��ݒ肷��B
                door->SetRotation(objData.rotation);                               //��]��ݒ肷��B
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
            else if (objData.ForwardMatchName(L"Energy") == true)
            {
                auto energy = NewGO<Energy>(0, "energy");                           //��������B
                energy->SetPosition(objData.position);                              //���W��ݒ肷��B
                energy->SetScale(objData.scale);                                    //�T�C�Y��ݒ肷��B
                energy->SetRotation(objData.rotation);                              //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Goal") == true)
            {
                auto goal = NewGO<Goal>(0, "goal");                                 //��������B
                goal->SetPosition(objData.position);                                //���W��ݒ肷��B
                goal->SetScale(objData.scale);                                      //�T�C�Y��ݒ肷��B
                goal->SetRotation(objData.rotation);                                //��]��ݒ肷��B
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
            else if (objData.ForwardMatchName(L"JumpBoard") == true)
            {
                auto jumpBoard = NewGO<JumpBoard>(0, "jumpBoard");                  //��������B
                jumpBoard->SetPosition(objData.position);                           //���W��ݒ肷��B
                jumpBoard->SetScale(objData.scale);                                 //�T�C�Y��ݒ肷��B
                jumpBoard->SetRotation(objData.rotation);                           //��]��ݒ肷��B
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
            else if (objData.ForwardMatchName(L"Signboard") == true)
            {
                auto signBoard = NewGO<SignBoard>(0, "signBoard");                  //��������B
                signBoard->SetPosition(objData.position);                           //���W��ݒ肷��B
                signBoard->SetScale(objData.scale);                                 //�T�C�Y��ݒ肷��B
                signBoard->SetRotation(objData.rotation);                           //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"SpeedUpRail") == true)
            {
                auto speedUpRail = NewGO<SpeedUpRail>(0, "speedUpRail");            //��������B
                speedUpRail->SetPosition(objData.position);                         //���W��ݒ肷��B
                speedUpRail->SetScale(objData.scale);                               //�T�C�Y��ݒ肷��B
                speedUpRail->SetRotation(objData.rotation);                         //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Turret") == true)
            {
                auto turret = NewGO<Turret>(0, "turret");                           //��������B
                turret->SetPosition(objData.position);                              //���W��ݒ肷��B
                turret->SetScale(objData.scale);                                    //�T�C�Y��ݒ肷��B
                turret->SetRotation(objData.rotation);                              //��]��ݒ肷��B
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

void Stage_1::Update()
{
    m_levelRender.Update();
}