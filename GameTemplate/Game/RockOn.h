#pragma once

class Bumper;
class Player;

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

	Bumper* m_bumper;
	Player* m_player;

	bool m_isReady = false;
	bool m_isRockOn = false;
};