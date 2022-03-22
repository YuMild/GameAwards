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

	bool GetRockOnJudge() const
	{
		return m_isRockOn;
	}

private:
	/// <summary>
	/// ���b�N�I�����邩�ۂ��̔��������B
	/// </summary>
	void Judge();

	/// <summary>
	/// �摜�̕`�揈�����Ǘ��B
	/// </summary>
	void Sprite();

	//�摜
	SpriteRender m_rockOn_1;
	SpriteRender m_rockOn_2;
	SpriteRender m_rockOn_3;
	SpriteRender m_rockOn_4;
	SpriteRender m_rockOn_5;
	SpriteRender m_rockOn_6;
	SpriteRender m_rockOn_7;
	SpriteRender m_rockOn_8;

	//�t�H���g
	FontRender m_fontRender;

	Vector3 m_difference;

	Bumper* m_bumper;
	Player* m_player;

	bool m_isReady = false;
	bool m_isRockOn = false;
};