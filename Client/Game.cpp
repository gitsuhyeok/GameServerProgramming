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

GSPGame * g_game = NULL;
GSPUserInterface* g_userInterface = NULL;
DWORD g_startTime = 0;
DWORD g_prevTime = 0;
SOCKET server_s;

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
	g_game->KeyInput(g_userInterface, elapsedTimeInSec,server_s);

	// Renderer Test
	g_game->DrawAll(elapsedTimeInSec);

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
	int id =- 1;
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

int main(int argc, char **argv)
{
	string SERVER_ADDR;
	cout << "서버 주소 입력 : ";
	cin >> SERVER_ADDR;
	if (!isValidIpAddress(SERVER_ADDR))
	{
		cout<<"잘못된 서버 주소 형식. 127.0.0.1 접속 시도합니다."<<endl;
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
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	server_s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, 0);
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

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyDownInput);
	glutSpecialUpFunc(SpecialKeyUpInput);

	g_startTime = timeGetTime();
	glutMainLoop();

	closesocket(server_s);
	WSACleanup();
	delete g_game;

    return 0;
}

