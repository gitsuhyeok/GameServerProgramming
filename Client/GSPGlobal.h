#pragma once
#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "WS2_32.LIB")

constexpr short PORT = 4000;
constexpr int BUFSIZE = 256;

#define MAX_NUM_OBJECT 1000
#define GRAVITY 9.8f
#define BLOCK_MOVE 62.5f

//Type definitions
#define TYPE_DEFAULT -1
#define TYPE_HERO 0
#define TYPE_HERO_2 1
#define TYPE_BUILDING 2
#define TYPE_BULLET 3
//tbd


//void CALLBACK send_callback(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
//void CALLBACK recv_callback(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
//void send_to_server();
//
//void CALLBACK send_callback(DWORD err_res, DWORD r_size, LPWSAOVERLAPPED p_wsaover, DWORD rec_flag)
//{
//	cout << "send_callback 실행" << endl;
//
//	wsabuf[0].len = BUFSIZE;
//	DWORD recv_flag = 0;
//	ZeroMemory(&wsaover, sizeof(wsaover));
//	WSARecv(server_s, wsabuf, 1, nullptr, &recv_flag, &wsaover, recv_callback);
//
//	cout << "send_callback 실행 완료" << endl;
//}
//void CALLBACK recv_callback(DWORD err_res, DWORD r_size, LPWSAOVERLAPPED p_wsaover, DWORD rec_flag)
//{
//	if (err_res != 0)
//	{
//		print_error("WSASend prev send_callback", WSAGetLastError());
//
//	}
//	cout << "recv_callback 실행" << endl;
//
//	cout << buf << endl;
//
//
//	if (r_size == 0) {
//		b_logout = true;
//		return;
//	}
//	int p_size = 0;
//	while (p_size < r_size) {
//		char m_size = buf[0 + p_size];
//		int c_id = buf[1 + p_size];
//		std::cout << "데이터 크기 : " << m_size << " Clien[" << c_id << "] sent : ";
//		for (char i = 0; i < m_size; ++i)
//			std::cout << buf[i + 2 + p_size];
//		std::cout << std::endl;
//		p_size += m_size;
//	}
//	SendObjectData sod;
//	memcpy(&sod, buf + 2, p_size - 2);
//
//	g_game->SetObjectPos(sod.ID, sod.x, sod.y, sod.z);
//	cout << "ID : " << sod.ID << "x : " << sod.x << "y : " << sod.y << "z : " << sod.z << endl;
//	cout << r_size << endl;
//
//	cout << "recv_callback 실행 완료" << endl;
//}

//void send_to_server()
//{
//	// //서버로 보낼 데이터 처리
//	unsigned char bit = { 0b00000000 };
//	g_game->GetBit(&bit);
//
//	if (bit & 0b11111111)
//	{
//		cout << "send_to_server 실행" << endl;
//
//		memcpy(buf, &bit, sizeof(bit));
//
//		wsabuf[0].buf = buf;
//		wsabuf[0].len = static_cast<int>(strlen(buf));
//
//		cout << bit << ":" << sizeof(bit) << endl;
//		cout << buf << ":" << sizeof(buf) << endl;
//
//		DWORD sent_size;
//		ZeroMemory(&wsaover, sizeof(wsaover));
//		int res = WSASend(server_s, wsabuf, 1, &sent_size, 0, &wsaover, send_callback);
//		if (0 != res) {
//			print_error("WSASend prev send_callback", WSAGetLastError());
//		}
//		cout << "send_to_server 실행 완료" << endl;
//	}
//
//}
//
//void do_recv()
//{
//	ZeroMemory(&wsaover, sizeof(wsaover));
//	DWORD recv_flag = 0;
//	int res = WSARecv(server_s, wsabuf, 1, nullptr, &recv_flag, &wsaover, recv_callback);
//	if (0 != res) {
//		auto err_no = WSAGetLastError();
//		if (WSA_IO_PENDING != err_no)
//			print_error("WSARecv Error : ", WSAGetLastError());
//	}
//}
//
