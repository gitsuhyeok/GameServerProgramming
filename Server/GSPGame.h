#pragma once
#include "GSPGlobal.h"
#include "GSPObjectMgr.h"

class GSPGame
{
public:
	GSPGame(int windowSizeX, int windowSizeY);
	~GSPGame();

	void BoardMove(int id, float x, float y, float z, float elapsedTime);

	float GetGameTime();

private:
	GSPObjectMgr* m_ObjectMgr;

	int m_HeroID = -1;

	float m_gameTime = 0.f;
};

