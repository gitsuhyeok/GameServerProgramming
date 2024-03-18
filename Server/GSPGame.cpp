#include "stdafx.h"
#include "GSPGame.h"
#include "math.h"

GSPGame::GSPGame(int windowSizeX, int windowSizeY)
{
	m_ObjectMgr = new GSPObjectMgr();

	//create hero object
	m_HeroID = m_ObjectMgr->AddObject(-BLOCK_MOVE/2, -15+ BLOCK_MOVE/2, 0,
		30, 30, 1.f,
		1,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		TYPE_HERO,
		2000,
		-1,
		1, 0, 0, 1
	);

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

void GSPGame::BoardMove(int id, float x, float y, float z, float elapsedTime)
{
	if (m_ObjectMgr != NULL)
	{
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

