#include <ros/ros.h>
#include <usb_cam/usb_cam.h>
#include <image_transport/image_transport.h>
#include <camera_info_manager/camera_info_manager.h>
#include <std_srvs/Empty.h>
#include <std_msgs/String.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>

#include "UsbCamNode.cpp"

using namespace std;
using namespace cv;

int CamPicRequest;

sensor_msgs::Image img_;
int counter = 1;

void callback(const std_msgs::String::ConstPtr &msg) {

    CamPicRequest = std::stoi(msg->data.c_str());


    if (CamPicRequest == 1) {
        cv_bridge::CvImagePtr cv_ptr;
        cv_ptr = cv_bridge::toCvCopy(img_, sensor_msgs::image_encodings::BGR8);

        std::string location = "/home/frankenbox/Pictures/CamTesting/Requested/";
        std::string camName = "CamOne";
        std::string saveLocation = location + camName + std::to_string(counter) + ".jpg";

        cout << "Requesting picture from camera 1..." << endl;
        imwrite(saveLocation, cv_ptr->image);

        cout << saveLocation << endl;

        counter++;
    }

    //Cameras will be recording at all times.
    //To grab a pic, we will steal the most recent frame captured by that camera
    //To do this, we first need to make sure that the cameras are working.
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "usb_cam");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("pix_publisher", 1000, callback);

    usb_cam::UsbCamNode a;

    cout << "Beginning recording." << endl;
    a.take_and_save_image(img_);
    a.spin(img_);

    return EXIT_SUCCESS;
}


