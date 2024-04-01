#include "stdafx.h"
#include "GSPGame.h"
#include "math.h"

GSPGame::GSPGame(int windowSizeX, int windowSizeY)
{
	m_Renderer = new Renderer(windowSizeX, windowSizeY);

	m_ObjectMgr = new GSPObjectMgr();

	m_HeroID = m_ObjectMgr->AddObject(-BLOCK_MOVE / 2, -15 + BLOCK_MOVE / 2, 0,
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
	delete m_Renderer;
	m_Renderer = NULL;

	delete m_ObjectMgr;
	m_ObjectMgr = NULL;
}

int GSPGame::AddObject(int id, float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, float mass, float velX, float velY, float velZ, float accX, float accY, float accZ, float forceX, float forceY, float forceZ, int type, float HP, int ancestor, float r, float g, float b, float a)
{
	if (m_ObjectMgr != NULL)
	{
		return m_ObjectMgr->AddObject(id, posX, posY, posZ,
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

void GSPGame::DrawAll(float elapsedTime)
{
	//draw objects (Null! draw)
	//m_Renderer->DrawSolidRect(250, 0, 0, 50, 1, 1, 1, 1);

	//objmgr

	if (m_Renderer != NULL)
	{
		m_ObjectMgr->UpdateAllObjects(elapsedTime);
		//m_ObjectMgr->DoGarbageCollect();
		//m_ObjectMgr->DoAllObjectsOverlapTest();
		m_ObjectMgr->DrawAllObjects(m_Renderer, elapsedTime);
	}
	m_gameTime += elapsedTime;
}

void GSPGame::KeyInput(GSPUserInterface* ui, float elapsedTime)
{
	//character movement(hero)

	bit = { 0b00000000 };

	//player1 0
	if (m_ObjectMgr->IsMoveCoolTimeExpired(m_HeroID))
	{
		if (ui->Is_SP_Arrow_Up_Down())
		{
			bit |= 0b100;
		}
		if (ui->Is_SP_Arrow_Down_Down())
		{
			bit |= 0b10;
		}
		if (ui->Is_SP_Arrow_Left_Down())
		{
			bit |= 0b1000;
		}
		if (ui->Is_SP_Arrow_Right_Down())
		{
			bit |= 0b1;
		}

		m_ObjectMgr->ResetMoveCoolTime(m_HeroID);
	}
}

void GSPGame::SetObjectPos(int id, float x, float y, float z)
{
	if (m_ObjectMgr != NULL)
	{
		m_ObjectMgr->SetObjectPos(id, x, y, z);
	}
	else
	{
		//log...
	}
}

void GSPGame::SetObjectColor(int id, float r, float g, float b, float a)
{
	if (m_ObjectMgr != NULL)
	{
		m_ObjectMgr->SetObjectColor(id, r, g, b, a);
	}
	else
	{
		//log...
	}
}

void GSPGame::GetBit(unsigned char* ibit)
{
	*ibit = bit;

}
