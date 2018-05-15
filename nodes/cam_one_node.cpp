#include <ros/ros.h>
#include <usb_cam/usb_cam.h>
#include <image_transport/image_transport.h>
#include <camera_info_manager/camera_info_manager.h>
#include <std_srvs/Empty.h>
#include <std_msgs/String.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

#include "UsbCamNode.cpp"

using namespace std;
using namespace cv;

int CamPicRequest;

void callback(const std_msgs::String::ConstPtr& msg) {
    CamPicRequest = std::stoi(msg->data.c_str());
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "usb_cam");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("pix_publisher", 1000, callback);

    usb_cam::UsbCamNode a;
    a.spin();
    return EXIT_SUCCESS;
}


