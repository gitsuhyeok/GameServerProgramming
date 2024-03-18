#include "stdafx.h"

#include "GSPGlobal.h"
#include "GSPGame.h"
#include "GSPObjectMgr.h"
#include <bitset>
GSPGame* g_game = NULL;
SOCKET server_s;

struct SendObjectData {
	int ID;
	float x, y, z;
};

void print_error(const char* msg, int err_no)
{
	WCHAR* msg_buf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPWSTR>(&msg_buf), 0, NULL);
	cout << msg;
	wcout << L" : ¿¡·¯ : " << msg_buf;
	while (true);
	LocalFree(msg_buf);
}

int main()
{
	std::wcout.imbue(std::locale("korean"));
	
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	server_s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(server_s, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
	listen(server_s, SOMAXCONN);

	INT addr_size = sizeof(server_addr);
	SOCKET client_s = WSAAccept(server_s, reinterpret_cast<sockaddr*>(&server_addr), &addr_size, 0, 0);

	//GameObject Generate
	g_game = new GSPGame(500, 500);

	while (true) {
		unsigned char bit;

		WSABUF wsabuf;
		wsabuf.buf = (char*)&bit;
		wsabuf.len = sizeof(bit);
		DWORD recv_size;
		DWORD recv_flag = 0;
		int res = WSARecv(client_s, &wsabuf, 1, &recv_size, &recv_flag, nullptr, nullptr);
		if (0 != res) {
			print_error("WSARecv", WSAGetLastError());
		}

		cout << bitset<8>(bit) << endl;
		cout << wsabuf.len << endl;
		int ID = (bit >> 4 ) & 0b1;
		float x, y, z;
		x = y = z = 0.f;

		if (bit & 0b100)
		{
			y += BLOCK_MOVE;
		}
		if (bit & 0b10)
		{
			y -= BLOCK_MOVE;
		}
		if (bit & 0b1000)
		{
			x -= BLOCK_MOVE;
		}
		if (bit & 0b1)
		{
			x += BLOCK_MOVE;
		}
		g_game->BoardMove(ID, x, y, z, g_game->GetGameTime());
		
		SendObjectData sod;
		sod.ID = ID;
		wsabuf;
		g_game->GetObjectPos(sod.ID, &sod.x, &sod.y, &sod.z);
		wsabuf.buf = (char*)&sod;
		wsabuf.len = sizeof(sod);

		DWORD sent_size=0;
		res = WSASend(client_s, &wsabuf, 1, &sent_size, 0, nullptr, nullptr);
	}
	closesocket(server_s);
	closesocket(client_s);
	WSACleanup();
}