#ifndef UTIL_H
#define UTIL_H

#include "environnement.hpp"
#include <fstream>
#include <memory>
#include <list>
#include <string>
#include <vector>
#include <time.h>
#include <unistd.h>

#include "log.hpp"

#ifndef PI
#define PI 3.14159265
#endif
#ifndef DEMI_PI
#define DEMI_PI 1.570796325
#endif

#if WIN32
#define mysprintf sprintf_s
#else
#define mysprintf snprintf
#endif


void mySleep(int durationMilliSecond);
int myRound(double value);
void callDebugger();
double my_map(double x, double in_min, double in_max, double out_min, double out_max);

std::string execute2(std::string cmd);

double my_angle(double x1, double y1, double x2, double y2);
double angleBetweenPI2(double a);

std::wstring string_to_w (const std::string& str);
std::string w_to_string (const std::wstring& str);

int getHexIntWithChar(char c);

#endif
