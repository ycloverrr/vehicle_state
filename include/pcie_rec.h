#ifndef PCIE_REC_H
#define PCIE_REC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>


class PCIE_REC
{
private:
    int CAN2_Connect(void);

public:

    unsigned int CAN2_Receive(unsigned int& ID2, unsigned char Data2buff[8]);


    int s2;

    struct sockaddr_can addr2;

    struct ifreq ifr2;

    struct can_filter rfilter2[1];

    PCIE_REC();//构造函数
    ~PCIE_REC();//析构函数
};




#endif // PCIE_REC_H
