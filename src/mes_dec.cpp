#include"mes_dec.h"
//=============================================Message===================================
void MES_DEC::Message0x101(unsigned char data[8])
{
    MBE_Data.steerAngle = (short int)((data[0] << 8) + data[1]) * 0.1 ;
    MBE_Data.speed = (unsigned short int)((data[2] << 8) + data[3]) * 0.05625;
    MBE_Data.available = true;
}

void MES_DEC::Message0x113(unsigned char data[8])
{
    unsigned char gear_info = (data[4] & 0x0F) >> 4 ;
    if(gear_info == 0x0){
        MBE_Data.gear = 2;
    }
    else if( gear_info == 0x1 || gear_info == 0x2 || gear_info == 0x3 || gear_info == 0x4 || gear_info == 0x4 || gear_info == 0x5 || gear_info == 0x6 || gear_info == 0x7){
        MBE_Data.gear = 1;
    }
    else if(gear_info == 0xA){
        MBE_Data.gear = 0;
    }
    else if(gear_info == 0xB){
        MBE_Data.gear = -1;
    }
    else{
        MBE_Data.gear = 100;
    }
    MBE_Data.available = true;
}

void MES_DEC::Message0x122(unsigned char data[8])
{
    unsigned char direction_leftF = (data[1] & 0x06)>>1; // 10-9: 0: standstill; 1: forward; 2: backward; 3: invalid
    double data_leftF = (unsigned short int)((data[1]>>3) + (data[0] <<5) )* 0.0563;//7-0, 15-11
    unsigned char direction_rightF = (data[3] & 0x06)>>1; // 26-25: 0: standstill; 1: forward; 2: backward; 3: invalid
    double data_rightF = (unsigned short int)((data[3]>>3) + (data[2]<<5) )* 0.0563;//23-16, 31-27
    if(direction_leftF==0x01)
    {
        MBE_Data.wheel_speed_leftF = data_leftF;
    }
    else if(direction_leftF==0x02)
    {
        MBE_Data.wheel_speed_leftF = -data_leftF;
    }
    else if(direction_leftF==0x00)
    {
        MBE_Data.wheel_speed_leftF = 0;
    }
    else if(direction_leftF==0x03)
    {
        MBE_Data.wheel_speed_leftF = 0;
    }

    if(direction_rightF==0x01)
    {
        MBE_Data.wheel_speed_rightF = data_rightF;
    }
    else if(direction_rightF==0x02)
    {
        MBE_Data.wheel_speed_rightF = -data_rightF;
    }
    else if(direction_rightF==0x00)
    {
        MBE_Data.wheel_speed_rightF = 0;
    }
    else if(direction_rightF==0x03)
    {
        MBE_Data.wheel_speed_rightF = 0;
    }
    MBE_Data.available = true;
}

void MES_DEC::Message0x123(unsigned char data[8])
{
    unsigned char direction_leftR = (data[1] & 0x06)>>1; // 10-9: 0: standstill; 1: forward; 2: backward; 3: invalid
    double data_leftR = (unsigned short int)((data[1]>>3) + (data[0]<<5) )* 0.0563;//7-0, 15-11
    unsigned char direction_rightR = (data[3] & 0x06)>>1; // 26-25: 0: standstill; 1: forward; 2: backward; 3: invalid
    double data_rightR = (unsigned short int)((data[3]>>3) + (data[2]<<5) )* 0.0563;//23-16, 31-27
    if(direction_leftR==0x01)
    {
        MBE_Data.wheel_speed_leftR = data_leftR;
    }
    else if(direction_leftR==0x02)
    {
        MBE_Data.wheel_speed_leftR = -data_leftR;
    }
    else if(direction_leftR==0x00)
    {
        MBE_Data.wheel_speed_leftR = 0;
    }
    else if(direction_leftR==0x03)
    {
        MBE_Data.wheel_speed_leftR = 0;
    }

    if(direction_rightR==0x01)
    {
        MBE_Data.wheel_speed_rightR = data_rightR;
    }
    else if(direction_rightR==0x02)
    {
        MBE_Data.wheel_speed_rightR = -data_rightR;
    }
    else if(direction_rightR==0x00)
    {
        MBE_Data.wheel_speed_rightR = 0;
    }
    else if(direction_rightR==0x03)
    {
        MBE_Data.wheel_speed_rightR = 0;
    }
    MBE_Data.available = true;
}

//=============================================MES_DEC===================================

MES_DEC::MES_DEC()
{
    MBE_Data.speed = 0;
    MBE_Data.gear = 0;
    MBE_Data.steerAngle = 0;
    MBE_Data.wheel_speed_rightF = 0;
    MBE_Data.wheel_speed_leftF = 0;
    MBE_Data.wheel_speed_rightR = 0;
    MBE_Data.wheel_speed_leftR = 0;
    MBE_Data.available = false;
}
MES_DEC::~MES_DEC(){

}

MBE_Struct MES_DEC::MBE_Data_Update(unsigned int ID, unsigned char data[8])
{
    switch (ID)
    {
        case 0x0101: Message0x101(data); break;
        case 0x0113: Message0x113(data); break;
        case 0x0122: Message0x122(data); break;
        case 0x0123: Message0x123(data); break;
        default:break;
    }
    return MBE_Data;
}
