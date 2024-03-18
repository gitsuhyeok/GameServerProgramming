#pragma once
#include "GSPGlobal.h"
#include "GSPObject.h"
#include "Renderer.h"

class GSPObjectMgr
{
public:
	GSPObjectMgr();
	~GSPObjectMgr();

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
	
	void SetObjectVel(int id, float vx, float vy, float vz);
	void GetObjectVel(int id, float* vx, float* vy, float* vz);
	void SetObjectPos(int id, float x, float y, float z);
	void GetObjectPos(int id, float* x, float* y, float* z);

	void SetCoolTime(int id, float coolTime);
	float GetCoolTime(int id);
	bool IsCoolTimeExpired(int id);
	void ResetCoolTime(int id);

	void SetMoveCoolTime(int id, float coolTime);
	float GetMoveCoolTime(int id);
	bool IsMoveCoolTimeExpired(int id);
	void ResetMoveCoolTime(int id);

	void AddObjectForce(int id, float x, float y, float z, float elapsedTime);
	void BoardMove(int id, float x, float y, float z, float elapsedTime);
	
	float m_sizeX, m_sizeY, m_sizeZ = 0.f;
	float m_posX, m_posY, m_posZ = 0.f;
	float m_mass = 0.f;
	float m_velX, m_velY, m_velZ = 0.f;
	float m_accX, m_accY, m_accZ = 0.f;
	float m_forceX, m_forceY, m_forceZ = 0.f;

	bool DeleteObject(int id);
	void DrawAllObjects(Renderer* renderer, float elapsedTime);
	void UpdateAllObjects(float elapsedTime);
	void DoGarbageCollect();
	void DoAllObjectsOverlapTest();

private:
	bool BBOverlap(int srcID, int dstID);
	void CollisionProcessing(int srcID, int dstID);

	GSPObject* m_Objects[MAX_NUM_OBJECT];

	bool m_ObjectsOverlap[MAX_NUM_OBJECT];
};

