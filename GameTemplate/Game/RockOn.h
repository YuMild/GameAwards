#pragma once

class Player;
class Stage1;

class RockOn : public IGameObject
{
public:
	RockOn();
	~RockOn();
	bool Start();
	void Render(RenderContext& rc);
	void Update();

private:

	/// <summary>
	/// ���b�N�I�����邩�ۂ��̔��������B
	/// </summary>
	void Judge();

	Vector3 m_difference;

	Player* m_player;
	Stage1* m_stage1;
};