#include "pcie_rec.h"

int PCIE_REC::CAN2_Connect(void)
{

    s2 = socket(PF_CAN, SOCK_RAW, CAN_RAW); //创建套接字

    strcpy(ifr2.ifr_name, "can3" );


    ioctl(s2, SIOCGIFINDEX, &ifr2); //指定 can0 设备

    addr2.can_family = AF_CAN;

    addr2.can_ifindex = ifr2.ifr_ifindex;

    bind(s2, (struct sockaddr *)&addr2, sizeof(addr2));
}


unsigned int PCIE_REC::CAN2_Receive(unsigned int& ID2, unsigned char Data2buff[8])
{
     int j;
     struct can_frame frame2;
     int nbytes2;
      nbytes2 = read(s2, &frame2, sizeof(frame2));
   if(nbytes2>0){
       ID2=frame2.can_id;
       for(j=0;j<8;j++){
         Data2buff[j]=frame2.data[j];
       }
 return 1;
   }
 return 0;
}

PCIE_REC::PCIE_REC()
{
    CAN2_Connect();
}

PCIE_REC::~PCIE_REC()
{
    close(s2);
}
