#pragma once
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <assert.h>
#include <cstdlib>
#include <bitset>
#include <unordered_map>
#include <random>

#include <WS2tcpip.h>
#pragma comment (lib, "WS2_32.LIB")

using namespace std;

const short SERVER_PORT = 4000;
const int BUFSIZE = 256;

//random_device rd;
//mt19937 gen(rd());
//float min_val = 0.0f;
//float max_val = 255.0f;
//uniform_real_distribution<float> distribution(min_val, max_val);

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