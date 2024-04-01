/*
Copyright 2022 Lee Taek Hee (Tech University of Korea)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "timeapi.h"

#include "GSPGlobal.h"
#include "GSPGame.h"
#include "GSPUserInterface.h"

#include <regex>

GSPGame* g_game = NULL;
GSPUserInterface* g_userInterface = NULL;
DWORD g_startTime = 0;
DWORD g_prevTime = 0;

SOCKET server_s;

char send_buf[BUFSIZE]; //size + id + message  -> 

char recv_buf[BUFSIZE]; //size + id + message  -> 
WSABUF recv_wsabuf[1];
WSAOVERLAPPED recv_wsaover;

bool b_logout = false;

struct SendObjectData {
	int id; int type;
	float x, y, z;
	float r, g, b, a;
};

void print_error(const char* msg, int err_no)
{
	WCHAR* msg_buf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPWSTR>(&msg_buf), 0, NULL);
	std::cout << msg;
	std::wcout << L" : 에러 : " << msg_buf;
	while (true);
	LocalFree(msg_buf);
}
bool isValidIpAddress(const std::string& address) {
	// IP 주소를 확인하기 위한 정규 표현식
	std::regex ipRegex("^\\b(?:\\d{1,3}\\.){3}\\d{1,3}\\b$");

	return std::regex_match(address, ipRegex);
}


void CALLBACK send_callback(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
void CALLBACK recv_callback(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
//void send_message_to_server();
void send_to_server();
void do_recv();
void do_send(char* buf, int m_size);

class EXP_OVER {
public:
	WSAOVERLAPPED wsaover;
	WSABUF wsabuf[1];
	char	buf[BUFSIZE];
public:
	EXP_OVER(char* mess, int m_size)
	{
		ZeroMemory(&wsaover, sizeof(wsaover));
		wsabuf[0].buf = buf;
		wsabuf[0].len = m_size;

		memcpy(buf, mess, m_size);
	}
};

void CALLBACK send_callback(DWORD err_res,
	DWORD transfer_size,
	LPWSAOVERLAPPED p_wsaover,
	DWORD rec_flag)
{
	cout << "send callback" << endl;
	auto b = reinterpret_cast<EXP_OVER*>(p_wsaover);
	delete b;
	if (err_res != 0)
		print_error("WSAsend send_CALLBACK", WSAGetLastError());
}

void CALLBACK recv_callback(DWORD err_res, DWORD r_size, LPWSAOVERLAPPED p_wsaover, DWORD rec_flag)
{
	cout << "recv_callback 실행" << endl;
	
	if (err_res != 0)
	{
		print_error("WSARECV RECV_CALLBACK", WSAGetLastError());

	}

	int m_size;
	char s_id;
	SendObjectData sod;
	memcpy(&m_size, recv_buf, sizeof(int));
	memcpy(&s_id, recv_buf + sizeof(int), sizeof(char));
	memcpy(&sod, recv_buf + sizeof(int) + sizeof(char), sizeof(SendObjectData));

	cout << "m_size : " << m_size << endl;
	cout << "s_id : " << s_id << endl;
	cout << "sod.id : " << sod.id << endl;
	cout << "sod.type : " << sod.type << endl;

	switch (sod.type)
	{
	case 0: //이동
		g_game->SetObjectPos(sod.id, sod.x, sod.y, sod.z);
		break;
	case 1: //추가
		if (g_game->GetHeroID() == -1)
			g_game->SetHeroID(sod.id);
		g_game->AddObject(sod.id, sod.x, sod.y, sod.z,
			30, 30, 1.f,
			1,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			TYPE_HERO,
			2000,
			-1,
			sod.r, sod.g, sod.b, sod.a);

		break;
	case 2: //삭제
		g_game->DeleteObject(sod.id);
		break;
	}

	//cout << "ID : " << sod.ID << "x : " << sod.x << "y : " << sod.y << "z : " << sod.z << endl;
	//cout << r_size << endl;

	//recv 재실행

	do_recv();


	cout << "recv_callback 실행 완료" << endl;
}

void send_to_server()
{
	// //서버로 보낼 데이터 처리
	unsigned char bit = { 0b00000000 };
	g_game->GetBit(&bit);

	if (bit & 0b11111111)
	{
		cout << "send_to_server 실행" << endl;

		memcpy(send_buf, &bit, sizeof(bit));

		cout << bit << ":" << sizeof(bit) << endl;
		cout << send_buf << ":" << sizeof(send_buf) << endl;

		//DWORD sent_size;
		//ZeroMemory(&send_wsaover, sizeof(send_wsaover));
		//int res = WSASend(server_s, send_wsabuf, 1, &sent_size, 0, &send_wsaover, send_callback);
		//if (0 != res) {
		//	print_error("WSASend prev send_callback", WSAGetLastError());
		//}

		do_send(send_buf, sizeof(bit));
	}

}

void do_recv()
{
	cout << "do_recv함수 실행" << endl;
	ZeroMemory(&recv_wsaover, sizeof(recv_wsaover));
	DWORD recv_flag = 0;

	recv_wsabuf[0].buf = recv_buf;
	recv_wsabuf[0].len = BUFSIZE;

	int res = WSARecv(server_s, recv_wsabuf, 1, nullptr, &recv_flag, &recv_wsaover, recv_callback);
	if (0 != res) {
		auto err_no = WSAGetLastError();
		if (WSA_IO_PENDING != err_no)
			print_error("WSARecv Error : ", WSAGetLastError());
	}
}

void do_send(char* buf, int m_size)
{
	cout << "do_send" << endl;
	auto b = new EXP_OVER(buf, m_size);
	//cout << b->buf << ":" << sizeof(b->buf) << endl;
	WSASend(server_s, b->wsabuf, 1, nullptr, 0, &b->wsaover, send_callback);
}

void RenderScene(void)
{
	DWORD elapsedTime = 0;
	DWORD currentTime = timeGetTime();
	if (g_prevTime == 0)
	{
		elapsedTime = currentTime - g_startTime;
	}
	else
	{
		elapsedTime = currentTime - g_prevTime;
	}
	g_prevTime = currentTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	//elapsed time( ms->s )
	float elapsedTimeInSec = (float)elapsedTime / 1000.f;

	//send key inputs
	g_game->KeyInput(g_userInterface, elapsedTimeInSec);
	send_to_server();

	// Renderer Test
	g_game->DrawAll(elapsedTimeInSec);

	SleepEx(0.001, true);

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}

void KeyDownInput(unsigned char key, int x, int y)
{
	int id = -1;
	g_userInterface->KeyDown(key, id);
}
void KeyUpInput(unsigned char key, int x, int y)
{
	int id = -1;
	g_userInterface->KeyUp(key, id);
}

void SpecialKeyDownInput(int id, int x, int y)
{
	unsigned char key = '~';
	g_userInterface->KeyDown(key, id);
}
void SpecialKeyUpInput(int id, int x, int y)
{
	unsigned char key = '~';
	g_userInterface->KeyUp(key, id);
}

int main(int argc, char** argv)
{
	string SERVER_ADDR;
	cout << "서버 주소 입력 : ";
	cin >> SERVER_ADDR;
	if (!isValidIpAddress(SERVER_ADDR))
	{
		cout << "잘못된 서버 주소 형식. 127.0.0.1 접속 시도합니다." << endl;
		SERVER_ADDR = "127.0.0.1";
	}

	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	//server
	std::wcout.imbue(std::locale("korean"));
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);

	server_s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	SOCKADDR_IN server_a;
	server_a.sin_family = AF_INET;
	server_a.sin_port = htons(PORT);
	inet_pton(AF_INET, SERVER_ADDR.c_str(), &server_a.sin_addr);
	int res = connect(server_s, reinterpret_cast<sockaddr*>(&server_a), sizeof(server_a));
	if (0 != res) {
		print_error("connect", WSAGetLastError());
	}


	// Initialize Renderer
	g_userInterface = new GSPUserInterface();
	g_game = new GSPGame(500, 500);

	do_recv();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyDownInput);
	glutSpecialUpFunc(SpecialKeyUpInput);

	g_startTime = timeGetTime();

	glutMainLoop();


	WSACleanup();
	delete g_game;
	closesocket(server_s);

	return 0;
}

