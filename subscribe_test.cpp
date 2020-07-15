//
// Created by torchwood on 17/11/29.
//

#include <opencv2/opencv.hpp>

#include "ros/ros.h"
#include "cv_bridge/cv_bridge.h"
#include "bomberman/game_status.h"

#include <iostream>
using namespace std;


void windowDrawer(const bomberman::game_status msg){
    cout    << "running"    << (int)msg.running      << endl
            << "left_time"  << msg.left_time    << endl
            << "red_score"  << msg.red_score    << endl
            << "green_score"<< msg.green_score  << endl;

    cv_bridge::CvImagePtr image = cv_bridge::toCvCopy(msg.color_map,sensor_msgs::image_encodings::BGR8);

    cv::imshow("Subscribe_test", image->image);
    cv::waitKey(1);
}

int main(int argc,char** argv){

    cvNamedWindow("Subscribe_test", CV_WINDOW_AUTOSIZE);

    ros::init(argc,argv,"sub_tester");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("game_status",1,windowDrawer);

    ros::spin();

    return 0;
}