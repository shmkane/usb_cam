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

void callback(const std_msgs::String::ConstPtr& msg, usb_cam::UsbCamNode &node) {
    CamPicRequest = std::stoi(msg->data.c_str());
    int cam = node.cam_number;

    if(CamPicRequest == cam) {
        cout << "Taking picture on camera " << cam << endl;
        node.take_and_save_image(node.pic_location);
    } else if (CamPicRequest == 5) {
        //Save a pic on all cams if it == 5
        cout << "Pic on all cams: Cam " << cam << endl;
        node.take_and_save_image(node.pic_location);
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "usb_cam");
    ros::NodeHandle n;
    usb_cam::UsbCamNode camNode;

    ros::Subscriber sub = n.subscribe<std_msgs::String>("pix_publisher", 100, boost::bind(callback, _1, boost::ref(camNode)));

    camNode.spin();
    return EXIT_SUCCESS;
}


