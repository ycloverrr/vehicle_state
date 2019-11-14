#include "vehicle_status.h"
using namespace vehicle_status;
int main(int argc, char **argv)
{
    ros::init(argc, argv, "vehicle_status_node",ros::init_options::NoRosout);
    ros::NodeHandle nh("");
    ros::NodeHandle nh_local("~");
    try {
      ROS_INFO("[vehicle_status]: Initializing node");
      VEHICLE_STATUS ml(nh, nh_local);
      ros::spin();
    }
    catch (const char* s) {
      ROS_FATAL_STREAM("[vehicle_status Decode]: "  << s);
    }
    catch (...) {
      ROS_FATAL_STREAM("[vehicle_status Decode]: Unexpected error");
    }

    return 0;
}

