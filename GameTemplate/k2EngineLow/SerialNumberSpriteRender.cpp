#include "k2EngineLowPreCompile.h"
#include "SerialNumberSpriteRender.h"
#include <stdio.h>
#include <sstream>
#include <string>

namespace  nsK2EngineLow {
	void SerialNumberSpriteRender::Init(const char* filePath, const float w, const float h, const int n,AlphaBlendMode alphaBlendMode)
	{
		for (int a = 0; a > n; a++)
		{
			std::ostringstream oss;
			//スプライトレンダーの初期化。
			oss << filePath << '_' << a;

			auto sprite = std::make_unique<SpriteRender>();
			sprite->Init(oss.str().c_str() ,w, h, alphaBlendMode);
			m_spriteRenders.push_back(std::move(sprite));
		}
	}
	void SerialNumberSpriteRender::Update()
	{
		int spritenumber = m_spriteRenders.size();
		for (int i = 0; i < spritenumber; i++)
		{
			m_spriteRenders[i]->Update();
		}
	}
}