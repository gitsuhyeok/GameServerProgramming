#include "stdafx.h"

#include "GSPGlobal.h"
#include "GSPGame.h"
#include "GSPObjectMgr.h"

GSPGame* g_game = NULL;
SOCKET server_s;

char g_session_id = 0;

bool b_shutdown = false;

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
	cout << msg;
	wcout << L" : 에러 : " << msg_buf;
	while (true);
	LocalFree(msg_buf);
}
void CALLBACK recv_callback(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
void CALLBACK send_callback(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
class SESSION;
unordered_map<LPWSAOVERLAPPED, SESSION> players;

class EXP_OVER {
public:
	WSAOVERLAPPED wsaover;
	WSABUF wsabuf[1];
	char	buf[BUFSIZE];
public:
	EXP_OVER(char s_id, char* mess, int m_size)
	{
		int size = m_size + sizeof(char) + sizeof(int);


		ZeroMemory(&wsaover, sizeof(wsaover));
		wsabuf[0].buf = buf;
		wsabuf[0].len = size;

		memcpy(buf, &size, sizeof(int));
		memcpy(buf + sizeof(int), &s_id, sizeof(char));
		memcpy(buf + sizeof(int) + sizeof(char), mess, m_size);
	}
};

//=====================================
//				SESSION
//=====================================
class SESSION {
public:
	char	s_id_;

	SOCKET client_s_;
	char buf[BUFSIZE];
	WSABUF wsabuf[1];
	WSAOVERLAPPED* wsaover;

	int object_id;

public:
	SESSION()
	{
		std::cout << "ERROR\n";
		exit(-1);
	}

	SESSION(SOCKET s, WSAOVERLAPPED* over) : client_s_(s), wsaover(over)
	{
		s_id_ = g_session_id++;
		wsabuf[0].buf = buf;
		wsabuf[0].len = BUFSIZE;
	}
	~SESSION()
	{
		closesocket(client_s_);
		delete wsaover;
	}

	void do_recv()
	{
		cout << "do_recv" << endl;
		ZeroMemory(wsaover, sizeof(*wsaover));
		DWORD recv_flag = 0;
		int res = WSARecv(client_s_, wsabuf, 1, nullptr, &recv_flag, wsaover, recv_callback);
		if (0 != res) {
			auto err_no = WSAGetLastError();
			if (WSA_IO_PENDING != err_no)
				print_error("WSARecv Error : ", WSAGetLastError());
		}
	}

	void do_send(char s_id, char* buf, int m_size)
	{
		cout << "do_send" << endl;
		auto b = new EXP_OVER(s_id, buf, m_size);
		//cout << b->buf << ":" << sizeof(b->buf) << endl;
		int res = WSASend(client_s_, b->wsabuf, 1, nullptr, 0, &b->wsaover, send_callback);
	}

	void do_recv_callback(DWORD transfer_size)
	{
		cout << "do_recv_callback" << endl;
		//클라로부터 받은 bit값 처리
		unsigned char bit;

		if (0 == transfer_size) {
			cout << "[" << s_id_ << "]와의 연결이 끊겼습니다." << endl;
			for (auto& ss : players)
			{
				SendObjectData temp_sod;
				temp_sod.id = object_id; temp_sod.type = 2;
				g_game->GetObjectPos(temp_sod.id, &temp_sod.x, &temp_sod.y, &temp_sod.z);
				g_game->GetObjectColor(temp_sod.id, &temp_sod.r, &temp_sod.g, &temp_sod.b, &temp_sod.a);
				char temp_buf[BUFSIZE];

				memcpy(temp_buf, &temp_sod, sizeof(temp_sod));
				ss.second.do_send(6000, temp_buf, sizeof(temp_sod));
			}
			object_id = -1;
			return;
		}

	/*	std::cout << "Message from Client : ";
		for (DWORD i = 0; i < transfer_size; ++i)
			std::cout << buf[i];
		std::cout << std::endl;*/

		//g_game->BoardMove(0, *buf, g_game->GetGameTime());

		memcpy(&bit, buf, sizeof(unsigned char));

		cout << bit << ":" << sizeof(bit) << endl;
		g_game->BoardMove(object_id, bit, g_game->GetGameTime());
		//-----------------------

		//클라로 objectpos 값 전송
		SendObjectData sod;
		sod.id = object_id; sod.type = 0;
		g_game->GetObjectPos(sod.id, &sod.x, &sod.y, &sod.z);
		g_game->GetObjectColor(sod.id, &sod.r, &sod.g, &sod.b, &sod.a);
		cout << sod.x << ":" << sod.y << ":" << sod.z << endl;

		memcpy(buf, &sod, sizeof(sod));
		//-----------------------

		for (auto& ss : players)
		{
			ss.second.do_send(s_id_, buf, sizeof(sod));
		}

		do_recv();
	}
};
//-------------------------------------


//=====================================
//				callback
//=====================================
void CALLBACK send_callback(DWORD err_res,
	DWORD transfer_size,
	LPWSAOVERLAPPED p_wsaover,
	DWORD rec_flag)
{
	cout << "send_callback" << endl;
	auto b = reinterpret_cast<EXP_OVER*>(p_wsaover);
	delete b;
}

void CALLBACK recv_callback(DWORD err_res,
	DWORD transfer_size,
	LPWSAOVERLAPPED p_wsaover,
	DWORD rec_flag)
{
	cout << "recv_callback" << endl;
	players[p_wsaover].do_recv_callback(transfer_size);
}
//----------------------------------------

int main()
{
	std::wcout.imbue(std::locale("korean"));

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);

	server_s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(server_s, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
	listen(server_s, SOMAXCONN);

	sockaddr client_addr;
	int addr_size = sizeof(client_addr);

	//GameObject Generate
	g_game = new GSPGame(500, 500);

	while (b_shutdown == false) {
		SOCKET client_s = WSAAccept(server_s, &client_addr, &addr_size, nullptr, 0);
		LPWSAOVERLAPPED p_over = new WSAOVERLAPPED;

		players.try_emplace(p_over, client_s, p_over);

		players[p_over].object_id = g_game->AddObject(-BLOCK_MOVE / 2, -15 + BLOCK_MOVE / 2, 0,
			30, 30, 1.f,
			1,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			TYPE_HERO,
			2000,
			-1,
			1, 0, 0, 1);
		//클라로 objectpos 값 전송
		SendObjectData sod;
		sod.id = players[p_over].object_id; sod.type = 1;
		g_game->GetObjectPos(sod.id, &sod.x, &sod.y, &sod.z);
		g_game->GetObjectColor(sod.id, &sod.r, &sod.g, &sod.b, &sod.a);
		cout << sod.x << ":" << sod.y << ":" << sod.z << endl;
		
		char m_buf[BUFSIZE];

		memcpy(m_buf, &sod, sizeof(sod));
		//-----------------------

		for (auto& ss : players)
		{
			if (ss.second.object_id != players[p_over].object_id && ss.second.object_id != -1)
			{
				SendObjectData temp_sod;
				temp_sod.id = ss.second.object_id; temp_sod.type = 1;
				g_game->GetObjectPos(temp_sod.id, &temp_sod.x, &temp_sod.y, &temp_sod.z);
				g_game->GetObjectColor(temp_sod.id, &temp_sod.r, &temp_sod.g, &temp_sod.b, &temp_sod.a);
				char temp_buf[BUFSIZE];

				memcpy(temp_buf, &temp_sod, sizeof(temp_sod));
				players[p_over].do_send(5000, temp_buf, sizeof(temp_sod));
			}
				
			Sleep(100);
			ss.second.do_send(5000, m_buf, sizeof(sod));
		}


		players[p_over].do_recv();
	}
	players.clear();
	closesocket(server_s);
	WSACleanup();
}