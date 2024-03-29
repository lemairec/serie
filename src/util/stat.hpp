#ifndef STAT_H
#define STAT_H

#include <chrono>
#include <list>
#include <time.h>
#include <math.h>

class TimeObserver{
    std::list<double> m_values;
    std::chrono::system_clock::time_point m_last_time_received;
public:
    double m_moy;
    double m_et;
    
    double m_sec_connected = 2.0;
    
    void setNewTime(){
        auto begin = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = begin - m_last_time_received;

        double millis = diff.count()*1000;
        addNewValue(millis);
        m_last_time_received = begin;
    }
    
    bool isConnected(){
        auto begin = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = begin - m_last_time_received;

        if(diff.count() < m_sec_connected){
            return true;
        } else {
            return false;
        }
    }
    
    
    void addNewValue(double value){
        if(value > 10000){
            return;
        }
        m_values.push_front(value);
        while(m_values.size()>10){
            m_values.pop_back();
        }
        
        double sum = 0;
        for(auto c : m_values){
            sum += c;
        }
        double moy = sum/((double)m_values.size());
        //INFO(moy);
        
        
        double sum2 = 0;
        for(auto c : m_values){
            sum2 += (moy-c)*(moy-c);
        }
        m_et = sqrt(sum2/m_values.size());
        m_moy = moy;
    }
};


class ValueStat{
public:
    std::list<double> m_values;
    size_t m_size_max;

    double m_moy;
    double m_moy_carre;
    double m_et;
    
    ValueStat();
    void addNewValue(double value);
    void addNewValueDeg(double value);
    void clear(){m_values.clear();};
};

#endif //STAT_H
