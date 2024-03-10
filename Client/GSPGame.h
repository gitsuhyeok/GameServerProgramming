#pragma once
#include "GSPGlobal.h"
#include "Renderer.h"
#include "GSPObjectMgr.h"
#include "GSPUserInterface.h"

class GSPGame
{
public:
	GSPGame(int windowSizeX, int windowSizeY);
	~GSPGame();

	void DrawAll(float elapsedTime);
	void KeyInput(GSPUserInterface* ui, float elapsedTime);


private:
	Renderer* m_Renderer;
	GSPObjectMgr* m_ObjectMgr;

	int m_HeroID = -1;

	float m_gameTime = 0.f;
};

