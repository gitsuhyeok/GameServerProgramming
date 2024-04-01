#include "stdafx.h"
#include "GSPGame.h"
#include "math.h"

GSPGame::GSPGame(int windowSizeX, int windowSizeY)
{
	m_ObjectMgr = new GSPObjectMgr();

	//m_HeroID = m_ObjectMgr->AddObject(-BLOCK_MOVE / 2, -15 + BLOCK_MOVE / 2, 0,
	//	30, 30, 1.f,
	//	1,
	//	0, 0, 0,
	//	0, 0, 0,
	//	0, 0, 0,
	//	TYPE_HERO,
	//	2000,
	//	-1,
	//	1, 0, 0, 1
	//);

	//8*8 체스판
	for (int i = 0; i < 9; i++)
	{
		float x = -250 + 62.5 * (float)i;
		float y = -255 + 62.5 * (float)i;

		//가로선
		int id = m_ObjectMgr->AddObject(0, y, 0,
			500, 10, 1.f,
			1,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			TYPE_DEFAULT,
			2000,
			-1,
			0.737, 0.560, 0.560, 1
		);

		//세로선
		id = m_ObjectMgr->AddObject(x, -250, 0,
			10, 500, 1.f,
			1,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			TYPE_DEFAULT,
			2000,
			-1,
			0.737, 0.560, 0.560, 1
		);
	}

}

GSPGame::~GSPGame()
{
	delete m_ObjectMgr;
	m_ObjectMgr = NULL;
}

int GSPGame::AddObject(float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, float mass, float velX, float velY, float velZ, float accX, float accY, float accZ, float forceX, float forceY, float forceZ, int type, float HP, int ancestor, float r, float g, float b, float a)
{
	if (m_ObjectMgr != NULL)
	{
		return m_ObjectMgr->AddObject(posX, posY, posZ,
			sizeX, sizeY, sizeZ,
			mass,
			velX, velY, velZ,
			accX, accY, accZ,
			forceX, forceY, forceZ,
			type, HP, ancestor,
			r, g, b, a);
	}
	else
	{
		return -1;
	}
}

void GSPGame::BoardMove(int id, unsigned char bit, float elapsedTime)
{
	if (m_ObjectMgr != NULL)
	{
		float x, y, z;
		x = y = z = 0.f;

		if (bit & 0b100)
		{
			y += BLOCK_MOVE;
		}
		if (bit & 0b10)
		{
			y -= BLOCK_MOVE;
		}
		if (bit & 0b1000)
		{
			x -= BLOCK_MOVE;
		}
		if (bit & 0b1)
		{
			x += BLOCK_MOVE;
		}


		m_ObjectMgr->BoardMove(id, x, y, z, elapsedTime);
	}
	else
	{

	}

}

float GSPGame::GetGameTime()
{
	return m_gameTime;
}

void GSPGame::GetObjectPos(int id, float* x, float* y, float* z)
{
	if (m_ObjectMgr != NULL)
	{
		m_ObjectMgr->GetObjectPos(id, x, y, z);
	}
	else
	{

	}
}

void GSPGame::GetObjectColor(int id, float* r, float* g, float* b, float* a)
{
	if (m_ObjectMgr != NULL)
	{
		m_ObjectMgr->GetObjectColor(id, r, g, b, a);
	}
	else
	{

	}
}

