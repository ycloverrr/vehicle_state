#include"vehicle_status.h"
PCIE_REC mes_rec;
MES_DEC mes_dec;

using namespace vehicle_status;
using namespace std;
VEHICLE_STATUS::VEHICLE_STATUS(ros::NodeHandle& nh, ros::NodeHandle& nh_local) : nh_(nh), nh_local_(nh_local){
    params_srv_ = nh_local_.advertiseService("params", &VEHICLE_STATUS::updateParams, this);

    initialize();
}
VEHICLE_STATUS::~VEHICLE_STATUS(){
    nh_local_.deleteParam("frame_id");
    mes_rec.~PCIE_REC();
}

bool VEHICLE_STATUS::updateParams(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res) {

    nh_local_.param<string>("frame_id", p_frame_id_, "vehicle");

    vehicle_status_pub_ = nh_.advertise<local_messages::VehicleState>("vehicle_state", 1);
    unsigned int ID;
    unsigned char Data[8];
    MBE_Struct mes_dec_data;


    while(ros::ok()){
        mes_rec.CAN2_Receive(ID,Data);
//        if(ID==0x101 || ID==0x122 || ID==0x123)
        cout<<hex<<ID<<endl;
        mes_dec_data = mes_dec.MBE_Data_Update(ID,Data);
        if(mes_dec_data.available)
        {
            publishmessage(mes_dec_data);
        }
        else
        {
            cout<<"vehicle_state not available."<<endl;
        }
    }
}
void VEHICLE_STATUS::publishmessage(MBE_Struct MBE_Data){
    local_messages::VehicleState vehicle_state;

    vehicle_state.speed = MBE_Data.speed;
    vehicle_state.steerAngle = MBE_Data.steerAngle;
    vehicle_state.wheel_speed_rightF = MBE_Data.wheel_speed_rightF;
    vehicle_state.wheel_speed_leftF = MBE_Data.wheel_speed_leftF;
    vehicle_state.wheel_speed_rightR = MBE_Data.wheel_speed_rightR;
    vehicle_state.wheel_speed_leftR = MBE_Data.wheel_speed_leftR;

    vehicle_status_pub_.publish(vehicle_state);
}
