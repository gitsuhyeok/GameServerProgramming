#include "stdafx.h"
#include "GSPUserInterface.h"
#include <iostream>

GSPUserInterface::GSPUserInterface()
{
	m_SP_Arrow_Up = false;
	m_SP_Arrow_Down = false;
	m_SP_Arrow_Left = false;
	m_SP_Arrow_Right = false;

	m_Spacebar = false;
}

GSPUserInterface::~GSPUserInterface()
{

}

void GSPUserInterface::KeyDown(char key, int id)
{
	switch (key)
	{
	case ' ':
		m_Spacebar = true;
	default:
		break;
	}

	switch (id)
	{
	case 100: //SP_KEY_LEFT
		m_SP_Arrow_Left = true;
		break;
	case 101: //SP_KEY_UP
		m_SP_Arrow_Up = true;
		break;
	case 102: //SP_KEY_RIGHT
		m_SP_Arrow_Right = true;
		break;
	case 103: //SP_KEY_DOWN
		m_SP_Arrow_Down = true;
		break;
	default:
		break;
	}

	std::cout << m_SP_Arrow_Left << m_SP_Arrow_Up << m_SP_Arrow_Right << m_SP_Arrow_Down << std::endl;
	std::cout << m_Spacebar << std::endl;
}

void GSPUserInterface::KeyUp(char key, int id)
{
	switch (key)
	{
	case ' ':
		m_Spacebar = false;
	default:
		break;
	}

	switch (id)
	{
	case 100: //SP_KEY_LEFT
		m_SP_Arrow_Left = false;
		break;
	case 101: //SP_KEY_UP
		m_SP_Arrow_Up = false;
		break;
	case 102: //SP_KEY_RIGHT
		m_SP_Arrow_Right = false;
		break;
	case 103: //SP_KEY_DOWN
		m_SP_Arrow_Down = false;
		break;
	default:
		break;
	}
}

bool GSPUserInterface::Is_SP_Arrow_Up_Down()
{
	return m_SP_Arrow_Up;
}

bool GSPUserInterface::Is_SP_Arrow_Down_Down()
{
	return m_SP_Arrow_Down;
}

bool GSPUserInterface::Is_SP_Arrow_Left_Down()
{
	return m_SP_Arrow_Left;
}

bool GSPUserInterface::Is_SP_Arrow_Right_Down()
{
	return m_SP_Arrow_Right;
}

bool GSPUserInterface::Is_Spacebar_Down()
{
	return m_Spacebar;
}
