#ifndef MES_DEC_H
#define MES_DEC_H

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

typedef struct
{
    // The vehicle forward speed from dSPACE
    double speed;

    //The vehicle steer angle from dSPACE
    double steerAngle;

    // The vehicle forward right speed from dSPACE
    double wheel_speed_rightF;

    // The vehicle forward left speed from dSPACE
    double wheel_speed_leftF;

    // The vehicle rear right speed from dSPACE
    double wheel_speed_rightR;

    // The vehicle rear left speed from dSPACE
    double wheel_speed_leftR;

    // The data from dSPACE is available or not
    bool available;
}MBE_Struct;

class MES_DEC
{
private:
    void Message0x101(unsigned char data[8]);
    void Message0x122(unsigned char data[8]);
    void Message0x123(unsigned char data[8]);
public:
    MBE_Struct MBE_Data;
    MES_DEC();
    ~MES_DEC();
    MBE_Struct MBE_Data_Update(unsigned int ID, unsigned char data[8]);

};


#endif // MES_DEC_H
