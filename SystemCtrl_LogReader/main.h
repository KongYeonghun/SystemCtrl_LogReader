
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <WinSock2.h>
#include <windows.h>
#include <list>
#include <algorithm>
#include <thread>
#include <mutex>
#include <time.h>

#include "struct.h"

using namespace std;

ofstream AlgLoggingFile;

time_t timer;
struct tm* t;