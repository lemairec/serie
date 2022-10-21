#include "util.hpp"
#include "directory_manager.hpp"
#include <math.h>

std::string execute2(std::string cmd){
    std::string file = DirectoryManager::Instance().getDataDirectory() + "/tmp_cmd";
    std::string cmd2 = cmd + " > " + file;
    system(cmd2.c_str());
    std::ifstream infile(file);
    std::stringstream strStream;
    strStream << infile.rdbuf();//read the file
    std::string res = strStream.str();
    return res;
};


#include <stdlib.h>
#include <stdio.h>

#if WIN32
    #include <windows.h>

    void mySleep(int durationMilliSecond){
        Sleep(durationMilliSecond);
    }
#else
   #include <unistd.h>

    void mySleep(int durationMilliSecond){
        usleep(durationMilliSecond * 1000);
    }
#endif

int myRound(double value){
   return (int) value;
}

#ifdef WIN32
#include <WinBase.h>
void callDebugger()
{
   DebugBreak();
}
#else
void callDebugger()
{
}
#endif

double my_map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


double my_angle(double x1, double y1, double x2, double y2){
    if(x1 == 0 && y1 ==0){
        return 0;
    }
    double angle1 = atan2(y1,x1);
    double angle2 = atan2(y2,x2);
    
    
    return angle2-angle1;
}

double angleBetweenPI2(double a){
    double angle = a;
    if(a>3.14/2){
        angle = angle-3.14;
    }
    if(angle>3.14/2){
        angle = angle-3.14;
    }
    if(angle < -3.14/2){
        angle = angle+3.14;
    }
    if(angle < -3.14/2){
        angle = angle+3.14;
    }
    return angle;
}

#include <codecvt>
#include <string>
#include <locale>

// convert UTF-8 string to wstring
std::wstring string_to_w (const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.from_bytes(str);
}

// convert wstring to UTF-8 string
std::string w_to_string (const std::wstring& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.to_bytes(str);
}


int getHexIntWithChar(char c){
    if(c == '0'){
        return 0x0;
    } else if(c == '1'){
        return 0x1;
    } else if(c == '2'){
        return 0x2;
    } else if(c == '3'){
        return 0x3;
    } else if(c == '4'){
        return 0x4;
    } else if(c == '5'){
        return 0x5;
    } else if(c == '6'){
        return 0x6;
    } else if(c == '7'){
        return 0x7;
    } else if(c == '8'){
        return 0x8;
    } else if(c == '9'){
        return 0x9;
    } else if(c == 'a'){
        return 0xA;
    } else if(c == 'A'){
        return 0xA;
    } else if(c == 'b'){
        return 0xB;
    } else if(c == 'B'){
        return 0xB;
    } else if(c == 'c'){
        return 0xC;
    } else if(c == 'C'){
        return 0xC;
    } else if(c == 'd'){
        return 0xD;
    } else if(c == 'D'){
        return 0xD;
    } else if(c == 'e'){
        return 0xE;
    } else if(c == 'E'){
        return 0xE;
    } else if(c == 'f'){
        return 0xF;
    } else if(c == 'F'){
        return 0xF;
    }
    return 0;
}
