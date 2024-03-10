#include "stdafx.h"
#include "GSPObject.h"

GSPObject::GSPObject()
{
	m_sizeX = 0.f;
	m_sizeY = 0.f;
	m_sizeZ = 0.f;

	m_posX = 0.f;
	m_posY = 0.f;
	m_posZ = 0.f;

	m_mass = 0.f;

	m_velX = 0.f;
	m_velY = 0.f;
	m_velZ = 0.f;

	m_accX = 0.f;
	m_accY = 0.f;
	m_accZ = 0.f;
	
	m_forceX = 0.f;
	m_forceY = 0.f;
	m_forceZ = 0.f;

	m_type = TYPE_DEFAULT;

	m_coolTime = 0.01f;
	m_remainCoolTime = m_coolTime;
	m_isCoolTimeExpired = false;

	m_moveCoolTime = 0.1f;
	m_remainMoveCoolTime = m_moveCoolTime;
	m_isMoveCoolTimeExpired = false;

	m_r = m_g = m_b = m_a = 1.f;
}
GSPObject::~GSPObject()
{

}

void GSPObject::SetSize(float x, float y, float z)
{
	m_sizeX = x;
	m_sizeY = y;
	m_sizeZ = z;
}

void GSPObject::SetPos(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}

void GSPObject::GetPos(float* x, float* y, float* z)
{
	*x = m_posX;
	*y = m_posY;
	*z = m_posZ;
}

void GSPObject::SetMass(float mass)
{
	m_mass = mass;
}
float GSPObject::GetMass()
{
	return m_mass;
}
void GSPObject::SetVel(float x, float y, float z)
{
	m_velX = x;
	m_velY = y;
	m_velZ = z;
}
void GSPObject::GetVel(float* x, float* y, float* z)
{
	*x = m_velX;
	*y = m_velY;
	*z = m_velZ;

}
float GSPObject::GetVelMag()
{
	float mag = sqrtf(m_velX * m_velX + m_velY * m_velY + m_velZ * m_velZ);
	return mag;
}
void GSPObject::SetAcc(float x, float y, float z)
{
	m_accX = x;
	m_accY = y;
	m_accZ = z;
}
void GSPObject::SetForce(float x, float y, float z)
{
	m_forceX = x;
	m_forceY = y;
	m_forceZ = z;
}
void GSPObject::SetType(int type)
{
	m_type = type;
}
int GSPObject::GetType()
{
	return m_type;
}

void GSPObject::SetColor(float r, float g, float b, float a)
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_a =a;
}

void GSPObject::GetBBMin(float* x, float* y, float* z)
{
	*x = m_posX - m_sizeX / 2.f;
	*y = m_posY - m_sizeY / 2.f;
	*z = m_posZ - m_sizeZ / 2.f;
}
void GSPObject::GetBBMax(float* x, float* y, float* z)
{
	*x = m_posX + m_sizeX / 2.f;
	*y = m_posY + m_sizeY / 2.f;
	*z = m_posZ + m_sizeZ / 2.f;
}

void GSPObject::SetID(int id)
{
	m_ID = id;
}

int GSPObject::GetID()
{
	return m_ID;
}

void GSPObject::SetParent(int id)
{
	m_parentID = id;
}

bool GSPObject::isAncestor(int id)
{
	if (m_parentID == id)
		return true;
	return false;
}

void GSPObject::SetCoolTime(float coolTime)
{
	m_coolTime = coolTime;
}
float GSPObject::GetCoolTime()
{
	return m_coolTime;
}
bool GSPObject::IsCoolTimeExpired()
{
	return m_isCoolTimeExpired;
}
void GSPObject::ResetCoolTime()
{
	m_remainCoolTime = m_coolTime;
}
void GSPObject::SetMoveCoolTime(float coolTime)
{
	m_moveCoolTime = coolTime;
}
float GSPObject::GetMoveCoolTime()
{
	return m_moveCoolTime;
}
bool GSPObject::IsMoveCoolTimeExpired()
{
	return m_isMoveCoolTimeExpired;
}
void GSPObject::ResetMoveCoolTime()
{
	m_remainMoveCoolTime = m_moveCoolTime;
}
void GSPObject::SetHP(float hp)
{
	m_HP = hp;
}
float GSPObject::GetHP()
{
	return m_HP;
}
void GSPObject::Draw(Renderer* renderer)
{
	renderer->DrawSolidRect(m_posX, m_posY, m_posZ, 
		m_sizeX, m_sizeY, m_sizeZ,
		m_r, m_g, m_b, m_a);

}

void GSPObject::Update(float elapsedTime)
{
	float t = elapsedTime;
	float tt = t * t;

	//accel
	//m_accX = m_forceX / m_mass;
	//m_accY = m_forceY / m_mass;
	//m_accZ = m_forceZ / m_mass;

	//vel
	//m_velX = m_velX + m_accX * t;
	//m_velY = m_velY + m_accY * t;
	//m_velZ = m_velZ + m_accZ * t;

	//pos
	//m_posX = m_posX + m_velX * t + 0.5f * m_accX * tt;
	//m_posY = m_posY + m_velY * t + 0.5f * m_accY * tt;
	//m_posZ = m_posZ + m_velZ * t + 0.5f * m_accZ * tt;

	//m_velX... apply friction
	//cal normal force
	float normalForce = m_mass * GRAVITY;

	float frictionCoef = 100.f;

	float friction = frictionCoef * normalForce;

	float frictionDirX = -m_velX;
	float frictionDirY = -m_velY;

	float mag = sqrtf(frictionDirX * frictionDirX + frictionDirY * frictionDirY);
	
	if (mag > FLT_EPSILON)
	{
		frictionDirX = frictionDirX / mag;
		frictionDirY = frictionDirY / mag;

		float frictionForceX = frictionDirX * friction;
		float frictionForceY = frictionDirY * friction;

		float frictionAccX = frictionForceX / m_mass;
		float frictionAccY = frictionForceY / m_mass;

		float resultVelX = m_velX + frictionAccX * elapsedTime;
		float resultVelY = m_velY + frictionAccY * elapsedTime;
		float resultVelZ = m_velZ;


		if (resultVelX * m_velX < 0.f)
		{
			m_velX = 0.f;
		}
		else 
		{
			m_velX = resultVelX;
		}
		if (resultVelY * m_velY < 0.f)
		{
			m_velY = 0.f;
		}
		else
		{
			m_velY = resultVelY;
		}
		if (resultVelZ * m_velZ < 0.f)
		{
			m_velZ = 0.f;
		}
		else
		{
			m_velZ = resultVelZ;
		}
	}

	m_posX = m_posX + m_velX * t;
	m_posY = m_posY + m_velY * t;
	m_posZ = m_posZ + m_velZ * t;

	m_remainCoolTime -= elapsedTime;
	if (m_remainCoolTime < FLT_EPSILON)
	{
		m_isCoolTimeExpired = true;
	}
	else
	{
		m_isCoolTimeExpired = false;
	}

	m_remainMoveCoolTime -= elapsedTime;
	if (m_remainMoveCoolTime < FLT_EPSILON)
	{
		m_isMoveCoolTimeExpired = true;
	}
	else
	{
		m_isMoveCoolTimeExpired = false;
	}
}

void GSPObject::AddForce(float x, float y, float z, float elapsedTime)
{
	//calc acc
	float accX = x / m_mass;
	float accY = y / m_mass;
	float accZ = z / m_mass;

	m_velX = m_velX + accX*elapsedTime;
	m_velY = m_velY + accY*elapsedTime;
	m_velZ = m_velZ + accZ*elapsedTime;
}

void GSPObject::BoardMove(float x, float y, float z, float elapsedTime)
{
	float newX = m_posX + x;
	float newY = m_posY + y;
	float newZ = m_posZ + z;
	if (-250 < newX && newX < 250 && -250 < newY && newY < 250)
	{ 
		m_posX = newX;
		m_posY = newY;
		m_posZ = newZ;
	}
}
