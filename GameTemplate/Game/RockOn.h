#pragma once

class Player;
class Stage_0;

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

	//�t�H���g
	FontRender m_fontRender;

	Vector3 m_difference;

	Player* m_player;
	Stage_0* m_stage_0;
};