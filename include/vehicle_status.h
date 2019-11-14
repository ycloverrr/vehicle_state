#ifndef VEHICLE_STATUS_H
#define VEHICLE_STATUS_H

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <geometry_msgs/Pose2D.h>
#include <tf/transform_listener.h>
#include "local_messages/VehicleState.h"
#include <geometry_msgs/Point32.h>
#include "pcie_rec.h"
#include "mes_dec.h"


namespace vehicle_status{
class VEHICLE_STATUS{
public:
    VEHICLE_STATUS(ros::NodeHandle& nh, ros::NodeHandle& nh_local);
    ~VEHICLE_STATUS();
private:
    bool updateParams(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res);


    void initialize() { std_srvs::Empty empt; updateParams(empt.request, empt.response); }


    void publishmessage(MBE_Struct mes_dec_data);

    ros::NodeHandle nh_;
    ros::NodeHandle nh_local_;

    ros::ServiceServer params_srv_;

    ros::Publisher vehicle_status_pub_;

    ros::Time stamp_;

    std::string p_frame_id_;


};

}



#endif // VEHICLE_STATUS_H
