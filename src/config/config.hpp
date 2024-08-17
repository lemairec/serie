#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#define PILOT_LANGAGE_ARDUINO 0
#define PILOT_LANGAGE_HADRIEN 1

enum LissageGpsMode{
    LissageGpsMode_None = 0,
    LissageGpsMode_Ekf = 1
};

enum CapMode{
    CapMode_Custom = 0,
    CapMode_Ekf = 1,
    CapMode_Rmc = 2
};

enum LissageImuMode{
    LissageImuMode_None = 0,
    LissageImuMode_Ekf = 1
};

class Config  {
public:
    std::string m_serial;
    int m_baudrate = 115200;
    bool m_fullscreen = true;
    
    bool m_all_tty = false;

    Config();
    
    void save();
    void load();
};

//-500 =>

#endif // CONFIG_H
