#include "stdafx.h"
#include "GSPObjectMgr.h"
#include <iostream>

GSPObjectMgr::GSPObjectMgr()
{
	for (int i = 0; i < MAX_NUM_OBJECT; i++)
	{
		m_Objects[i] = NULL;
		m_ObjectsOverlap[i] = false;
	}
	// memset 사용이 더 좋음 현재는 가독성 중시
}

GSPObjectMgr::~GSPObjectMgr()
{
	for (int i = 0; i < MAX_NUM_OBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			delete m_Objects[i];
			m_Objects[i] = NULL;
		}

	}
}
int GSPObjectMgr::AddObject(int id, float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ,
	float mass,
	float velX, float velY, float velZ,
	float accX, float accY, float accZ,
	float forceX, float forceY, float forceZ,
	int type,
	float HP,
	int ancestor,
	float r, float g, float b, float a)
{
	//Find empty slot
	int index = id;

	if (index >= 0)
	{
		m_Objects[index] = new GSPObject();
		m_Objects[index]->SetPos(posX, posY, posZ);
		m_Objects[index]->SetSize(sizeX, sizeY, sizeZ);
		m_Objects[index]->SetMass(mass);
		m_Objects[index]->SetVel(velX, velY, velZ);
		m_Objects[index]->SetAcc(accX, accY, accZ);
		m_Objects[index]->SetForce(forceX, forceY, forceZ);
		m_Objects[index]->SetType(type);
		m_Objects[index]->SetID(index);
		m_Objects[index]->SetHP(HP);
		m_Objects[index]->SetParent(ancestor);
		m_Objects[index]->SetColor(r, g, b, a);
		return index;
	}

	std::cout << "No more empty object slot!" << std::endl;
	return index;

}
int GSPObjectMgr::AddObject(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ,
	float mass,
	float velX, float velY, float velZ,
	float accX, float accY, float accZ,
	float forceX, float forceY, float forceZ,
	int type,
	float HP,
	int ancestor,
	float r, float g, float b, float a)
{
	//Find empty slot
	int index = -1;
	for (int i = 0; i < MAX_NUM_OBJECT; i++)
	{
		if (m_Objects[i] == NULL)
		{
			index = i;
			break;
		}
	}

	if (index >= 0)
	{
		m_Objects[index] = new GSPObject();
		m_Objects[index]->SetPos(posX, posY, posZ);
		m_Objects[index]->SetSize(sizeX, sizeY, sizeZ);
		m_Objects[index]->SetMass(mass);
		m_Objects[index]->SetVel(velX, velY, velZ);
		m_Objects[index]->SetAcc(accX, accY, accZ);
		m_Objects[index]->SetForce(forceX, forceY, forceZ);
		m_Objects[index]->SetType(type);
		m_Objects[index]->SetID(index);
		m_Objects[index]->SetHP(HP);
		m_Objects[index]->SetParent(ancestor);
		m_Objects[index]->SetColor(r, g, b, a);
		return index;
	}

	std::cout << "No more empty object slot!" << std::endl;
	return index;

}

void GSPObjectMgr::SetObjectVel(int id, float vx, float vy, float vz)
{
	if (m_Objects[id] != NULL)
	{
		m_Objects[id]->SetVel(vx, vy, vz);
	}
	else
	{
		//log...
	}
}

void GSPObjectMgr::GetObjectVel(int id, float* vx, float* vy, float* vz)
{
	if (m_Objects[id] != NULL)
	{
		m_Objects[id]->GetVel(vx, vy, vz);
	}
	else
	{
		//log...
	}
}

void GSPObjectMgr::SetObjectPos(int id, float x, float y, float z)
{
	if (m_Objects[id] != NULL)
	{
		m_Objects[id]->SetPos(x, y, z);
	}
	else
	{
		//log...
	}
}

void GSPObjectMgr::GetObjectPos(int id, float* x, float* y, float* z)
{
	if (m_Objects[id] != NULL)
	{
		m_Objects[id]->GetPos(x, y, z);
	}
	else
	{
		//log...
	}
}

void GSPObjectMgr::SetObjectColor(int id, float r, float g, float b, float a)
{
	if (m_Objects[id] != NULL)
	{
		m_Objects[id]->SetColor(r, g, b, a);
	}
	else
	{
		//log...
	}
}

void GSPObjectMgr::SetCoolTime(int id, float coolTime)
{
	if (m_Objects[id] != NULL)
	{
		m_Objects[id]->SetCoolTime(coolTime);
	}
	else
	{
		//log...
	}
}

float GSPObjectMgr::GetCoolTime(int id)
{
	if (m_Objects[id] != NULL)
	{
		return m_Objects[id]->GetCoolTime();
	}
	else
	{
		return 0.f;
	}
}

bool GSPObjectMgr::IsCoolTimeExpired(int id)
{
	if (m_Objects[id] != NULL)
	{
		return m_Objects[id]->IsCoolTimeExpired();
	}
	else
	{
		return false;
	}
}

void GSPObjectMgr::ResetCoolTime(int id)
{
	if (m_Objects[id] != NULL)
	{
		return m_Objects[id]->ResetCoolTime();
	}
	else
	{

	}
}

void GSPObjectMgr::SetMoveCoolTime(int id, float coolTime)
{
	if (m_Objects[id] != NULL)
	{
		m_Objects[id]->SetMoveCoolTime(coolTime);
	}
	else
	{
		//log...
	}
}

float GSPObjectMgr::GetMoveCoolTime(int id)
{
	if (m_Objects[id] != NULL)
	{
		return m_Objects[id]->GetMoveCoolTime();
	}
	else
	{
		return 0.f;
	}
}

bool GSPObjectMgr::IsMoveCoolTimeExpired(int id)
{
	if (m_Objects[id] != NULL)
	{
		return m_Objects[id]->IsMoveCoolTimeExpired();
	}
	else
	{
		return false;
	}
}

void GSPObjectMgr::ResetMoveCoolTime(int id)
{
	if (m_Objects[id] != NULL)
	{
		return m_Objects[id]->ResetMoveCoolTime();
	}
	else
	{

	}

}

void GSPObjectMgr::AddObjectForce(int id, float x, float y, float z, float elapsedTime)
{
	if (m_Objects[id] != NULL)
	{
		m_Objects[id]->AddForce(x, y, z, elapsedTime);
	}
	else
	{
		//log..
	}
}

void GSPObjectMgr::BoardMove(int id, float x, float y, float z, float elapsedTime)
{
	if (m_Objects[id] != NULL)
	{
		m_Objects[id]->BoardMove(x, y, z, elapsedTime);
	}
	else
	{
		//log..
	}
}

bool GSPObjectMgr::DeleteObject(int id)
{
	if (m_Objects[id] != NULL)
	{
		delete m_Objects[id];
		m_Objects[id] = NULL;
		return true;
	}

	std::cout << "Index " << id << " already deleted." << std::endl;
	return false;
}

void GSPObjectMgr::DoGarbageCollect()
{
	//find garbage & delete it
	for (int i = 0; i < MAX_NUM_OBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			//Bullet garbage
			int type = m_Objects[i]->GetType();
			if (type == TYPE_BULLET)
			{
				float mag = m_Objects[i]->GetVelMag();
				if (mag < FLT_EPSILON)
				{
					DeleteObject(i);
					continue;
				}
			}

			float hp = m_Objects[i]->GetHP();
			if (hp < FLT_EPSILON)
			{
				DeleteObject(i);
				continue;
			}
		}
	}
}

void GSPObjectMgr::DoAllObjectsOverlapTest()
{
	memset(m_ObjectsOverlap, 0, sizeof(bool) * MAX_NUM_OBJECT);

	//for...
	for (int i = 0; i < MAX_NUM_OBJECT; i++)
	{
		for (int j = i + 1; j < MAX_NUM_OBJECT; j++)
		{
			bool isOverlap = BBOverlap(i, j);

			if (isOverlap)
			{
				bool ancestorA = m_Objects[i]->isAncestor(j);
				bool ancestorB = m_Objects[j]->isAncestor(i);
				if (ancestorA == false && ancestorB == false)
				{
					m_ObjectsOverlap[i] = true;
					m_ObjectsOverlap[j] = true;

					//Collision Processing
					CollisionProcessing(i, j);

					float iHP = m_Objects[i]->GetHP();
					float jHP = m_Objects[j]->GetHP();
					float fiHP = iHP - jHP;
					float fjHP = jHP - iHP;
					m_Objects[i]->SetHP(fiHP);
					m_Objects[j]->SetHP(fjHP);
				}
			}
		}
	}

	//overlaps
	for (int i = 0; i < MAX_NUM_OBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_ObjectsOverlap[i])
			{
				m_Objects[i]->SetColor(1, 0, 0, 1);
			}
			else
			{
				m_Objects[i]->SetColor(1, 1, 1, 1);
			}
		}
	}
}

bool GSPObjectMgr::BBOverlap(int srcID, int dstID)
{
	if (m_Objects[srcID] != NULL && m_Objects[dstID] != NULL)
	{
		GSPObject* src = m_Objects[srcID];
		GSPObject* dst = m_Objects[dstID];

		float srcMinX, srcMinY, srcMinZ;
		float srcMaxX, srcMaxY, srcMaxZ;
		float dstMinX, dstMinY, dstMinZ;
		float dstMaxX, dstMaxY, dstMaxZ;
		src->GetBBMin(&srcMinX, &srcMinY, &srcMinZ);
		src->GetBBMax(&srcMaxX, &srcMaxY, &srcMaxZ);
		dst->GetBBMin(&dstMinX, &dstMinY, &dstMinZ);
		dst->GetBBMax(&dstMaxX, &dstMaxY, &dstMaxZ);

		if (srcMinX > dstMaxX)
			return false;
		if (srcMaxX < dstMinX)
			return false;
		if (srcMinY > dstMaxY)
			return false;
		if (srcMaxY < dstMinY)
			return false;
		if (srcMinZ > dstMaxZ)
			return false;
		if (srcMaxZ < dstMinZ)
			return false;

		return true;
	}
	return false;
}

void GSPObjectMgr::CollisionProcessing(int srcID, int dstID)
{
	GSPObject* src = m_Objects[srcID];
	GSPObject* dst = m_Objects[dstID];
	float  srcMass = src->GetMass();
	float dstMass = dst->GetMass();
	float srcVx, srcVy, srcVz;
	src->GetVel(&srcVx, &srcVy, &srcVz);
	float dstVx, dstVy, dstVz;
	dst->GetVel(&dstVx, &dstVy, &dstVz);

	float srcFVx, srcFVy, srcFVz;
	srcFVx = (((srcMass - dstMass) / (srcMass + dstMass)) * srcVx) +
		(((2 * dstMass) / (srcMass + dstMass)) * dstVx);
	srcFVy = (((srcMass - dstMass) / (srcMass + dstMass)) * srcVy) +
		(((2 * dstMass) / (srcMass + dstMass)) * dstVy);
	srcFVz = (((srcMass - dstMass) / (srcMass + dstMass)) * srcVz) +
		(((2 * dstMass) / (srcMass + dstMass)) * dstVz);

	float dstFVx, dstFVy, dstFVz;
	dstFVx = (((2 * srcMass) / (srcMass + dstMass)) * srcVx) +
		(((dstMass - srcMass) / (srcMass + dstMass)) * dstVx);
	dstFVy = (((2 * srcMass) / (srcMass + dstMass)) * srcVy) +
		(((dstMass - srcMass) / (srcMass + dstMass)) * dstVy);
	dstFVz = (((2 * srcMass) / (srcMass + dstMass)) * srcVz) +
		(((dstMass - srcMass) / (srcMass + dstMass)) * dstVz);

	src->SetVel(srcFVx, srcFVy, srcFVz);
	dst->SetVel(dstFVx, dstFVy, dstFVz);
}

void GSPObjectMgr::DrawAllObjects(Renderer* renderer, float elapsedTime)
{
	//for...
	for (int i = 0; i < MAX_NUM_OBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			m_Objects[i]->Draw(renderer);
		}
	}
}

void GSPObjectMgr::UpdateAllObjects(float elapsedTime)
{
	for (int i = 0; i < MAX_NUM_OBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			m_Objects[i]->Update(elapsedTime);
		}
	}
}