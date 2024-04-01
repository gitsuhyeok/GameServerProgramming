#pragma once
#include "GSPGlobal.h"
#include "GSPObjectMgr.h"

class GSPGame
{
public:
	GSPGame(int windowSizeX, int windowSizeY);
	~GSPGame();

	int AddObject(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ,
		float mass,
		float velX, float velY, float velZ,
		float accX, float accY, float accZ,
		float forceX, float forceY, float forceZ,
		int type,
		float HP,
		int ancestor,
		float r, float g, float b, float a);

	void BoardMove(int id, unsigned char bit, float elapsedTime);

	float GetGameTime();

	void GetObjectPos(int id, float* x, float* y, float* z);
	void GetObjectColor(int id, float* r, float* g, float* b, float* a);

private:
	GSPObjectMgr* m_ObjectMgr;

	int m_HeroID = -1;

	float m_gameTime = 0.f;
};

