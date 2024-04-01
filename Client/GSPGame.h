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

	int AddObject(int id, float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ,
		float mass,
		float velX, float velY, float velZ,
		float accX, float accY, float accZ,
		float forceX, float forceY, float forceZ,
		int type,
		float HP,
		int ancestor,
		float r, float g, float b, float a);

	void DrawAll(float elapsedTime);
	void KeyInput(GSPUserInterface* ui, float elapsedTime);
	void SetObjectPos(int id, float x, float y, float z);
	void SetObjectColor(int id, float r, float g, float b, float a);

	void GetBit(unsigned char* ibit);

private:
	Renderer* m_Renderer;
	GSPObjectMgr* m_ObjectMgr;

	int m_HeroID = -1;

	float m_gameTime = 0.f;
	unsigned char bit = { 0b00000000 };
};

