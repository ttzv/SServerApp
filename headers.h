#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <sstream>
#include <string.h>
#include <iomanip>
#include <time.h>
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>
/////////////zmienne do obliczen
const double M_PI = 3.14159265358979323846;
double ALT_old=0, AZ_old=0;
double RAp, RA;
double DECp, DEC;
double LAT = 0;
double LON = 0;
/////////////Bazowanie
bool CHECK_LEFT=FALSE;
bool CHECK_RIGHT=FALSE;
bool CHECK_UP=FALSE;
bool CHECK_DOWN=FALSE;
/////////////BUFOR TCP
int bytesRecv = SOCKET_ERROR;
char recvbuf[ 20 ];

