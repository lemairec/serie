#include "hexa_parser.hpp"
#include "../util/util.hpp"
#include "../util/include.hpp"
#include "../framework.hpp"
//#include "gps_module.hpp"

HexaParser::HexaParser(){
}
void HexaParser::parseBuffer(){
    if(m_bufferIndLast > 0){
        std::stringstream ss;
        std::string s2 = "parse => " + ss.str();
        for(size_t i =0; i < m_bufferIndLast; ++i){
            ss << " " << std::setw(2) << std::setfill('0') << std::hex << (int)((uchar)m_buffer[i]);
        }
        
        Framework & f = Framework::Instance();
        f.addSerialMessage(s2);
        this->resetBuffer();
    }
}

bool HexaParser::checkBuffer(){
    int checksum = 0;
    for(size_t i =0; i < m_bufferIndLast; ++i){
        const char c = m_buffer[i];
        if (c == '*'){
            if(i < m_bufferIndLast+2){
                char c1 = m_buffer[i+1];
                char c2 = m_buffer[i+2];
                
                int i = getHexIntWithChar(c1)*16+getHexIntWithChar(c2);
                if(i == checksum){
                    return true;
                }
            }
            break;
        }
        checksum = checksum ^ c;
    }
    m_error_read++;
    return false;
}

int m_parser_i = 0;
void HexaParser::handle100ms(){
    m_parser_i++;
    if(m_parser_i>9){
        m_parser_i = 0;
        Framework & f = Framework::Instance();
        if(f.m_hexa){
            std::vector<unsigned char> l = {0x01, 0x03, 0x00, 0x00, 0x00, 0x07, 0x04, 0x08};
            f.sendMessagesHexa(l);
        }
    }
    parseBuffer();
}
