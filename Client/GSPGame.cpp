#include "stdafx.h"
#include "GSPGame.h"
#include "math.h"

GSPGame::GSPGame(int windowSizeX, int windowSizeY)
{
	m_Renderer = new Renderer(windowSizeX, windowSizeY);

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


	//for (int i = 0; i < 10; i++)
	//{
	//	float x = (500.f * (float)rand() / (float)RAND_MAX) - 250.f;
	//	float y = (500.f * (float)rand() / (float)RAND_MAX) - 250.f;
	//	float z = 0;

	//	float sX = 50.f * (float)rand() / (float)RAND_MAX;
	//	float sY = 50.f * (float)rand() / (float)RAND_MAX;
	//	float sZ = 1.f;

	//	float mass = 10.f;

	//	float velX = (10.f * (float)rand() / (float)RAND_MAX) - 5.f;
	//	float velY = (10.f * (float)rand() / (float)RAND_MAX) - 5.f;
	//	float velZ = 0.f;

	//	float accX = 0.f;
	//	float accY = 0.f;
	//	float accZ = 0.f;

	//	float forceX = 0.f;
	//	float forceY = 0.f;
	//	float forceZ = 0.f;

	//	int id = m_ObjectMgr->AddObject(x, y, z,
	//		sX, sY, sZ,
	//		mass,
	//		velX, velY, velZ,
	//		accX, accY, accZ,
	//		forceX, forceY, forceZ,
	//		TYPE_DEFAULT,
	//		100,
	//		-1);
	//}

	//float x1 = 0;
	//float y1 = -250;
	//float x2 = 0;
	//float y2 = 62.5;

	//float sx1 = 500;
	//float sy1 = 10;
	//float sx2 = 10;
	//float sy2 = 500;
	//int id = m_ObjectMgr->AddObject(x1, y1, 0,
	//	10, 500, 1.f,
	//	1,
	//	0, 0, 0,
	//	0, 0, 0,
	//	0, 0, 0,
	//	TYPE_DEFAULT,
	//	2000,
	//	-1
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
	delete m_Renderer;
	m_Renderer = NULL;

	delete m_ObjectMgr;
	m_ObjectMgr = NULL;
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

void GSPGame::KeyInput(GSPUserInterface* ui, float elapsedTime,SOCKET socket)
{
	//character movement(hero)
	
	unsigned char bit = { 0b00000000 };
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
	if (bit & 0b11111111)
	{
		WSABUF wsabuf;
		wsabuf.buf = (char*)&bit;
		wsabuf.len = sizeof(bit);

		DWORD sent_size;
		WSASend(socket, &wsabuf, 1, &sent_size, 0, nullptr, nullptr);

		SendObjectData sod;
		wsabuf.buf = (char*)&sod;
		wsabuf.len = sizeof(sod);
		DWORD recv_size;
		DWORD recv_flag = 0;
		WSARecv(socket, &wsabuf, 1, &recv_size, &recv_flag, nullptr, nullptr);

		m_ObjectMgr->SetObjectPos(sod.ID, sod.x, sod.y, sod.z);
		cout << "ID : " << sod.ID << "x : " << sod.x << "y : " << sod.y << "z : " << sod.z << endl;
		cout << wsabuf.len << endl;

	}

	//m_ObjectMgr->BoardMove(m_HeroID, x, y, z, elapsedTime);


	//float forceAmount = 2000.f;
	//if (ui->Is_SP_Arrow_Up_Down())
	//{
	//	y += forceAmount;
	//}
	//if (ui->Is_SP_Arrow_Down_Down())
	//{
	//	y -= forceAmount;
	//}
	//if (ui->Is_SP_Arrow_Left_Down())
	//{
	//	x -= forceAmount;
	//}
	//if (ui->Is_SP_Arrow_Right_Down())
	//{
	//	x += forceAmount;
	//}

	//m_ObjectMgr->AddObjectForce(m_HeroID, x, y, z, elapsedTime);

	////총
	//if (ui->Is_Spacebar_Down())
	//{
	//	//bullet
	//	// 0. can hero shoot bullet(is cooltime expired?)
	//	bool canShoot = m_ObjectMgr->IsCoolTimeExpired(m_HeroID);
	//	if (canShoot)
	//	{
	//		//1 get hero position
	//		float  vx, vy, vz;
	//		float  x, y, z;
	//		m_ObjectMgr->GetObjectPos(m_HeroID, &x, &y, &z);
	//		m_ObjectMgr->GetObjectVel(m_HeroID, &vx, &vy, &vz);

	//		//2 calc bullet velocity
	//		float mag = sqrtf(vx * vx + vy * vy);
	//		float bulletVX = 1.f;
	//		float bulletVY = 0.f;
	//		float bulletSpeed = 1000.f;
	//		float theta = m_gameTime * 10.f;

	//		float newBX = cos(theta) * bulletVX - sin(theta) * bulletVY;
	//		float newBY = sin(theta) * bulletVX + cos(theta) * bulletVY;

	//		newBX *= bulletSpeed;
	//		newBY *= bulletSpeed;

	//		m_ObjectMgr->AddObject(x, y, z,
	//			5, 5, 5,
	//			1,
	//			newBX, newBY, 0,
	//			0, 0, 0,
	//			0, 0, 0,
	//			TYPE_BULLET,
	//			10,
	//			m_HeroID,
	//			0, 0, 0, 1);

	//		//if (mag > FLT_EPSILON)
	//		//{
	//		//	vx = vx / mag;
	//		//	vy = vy / mag;
	//		//	bulletVX = bulletSpeed * vx;
	//		//	bulletVY = bulletSpeed * vy;

	//		//	//3 add object(vel, pos)
	//		//	m_ObjectMgr->AddObject(x, y, z,
	//		//		20, 20, 10,
	//		//		1,
	//		//		bulletVX, bulletVY, 0,
	//		//		0, 0, 0,
	//		//		0, 0, 0,
	//		//		TYPE_BULLET);
	//		//}

	//		m_ObjectMgr->ResetCoolTime(m_HeroID);
	//	}
	//}
}
