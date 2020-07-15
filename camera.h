//
// Created by torchwood on 17/10/26.
//

#ifndef BOMBERMAN_CAMERA_H
#define BOMBERMAN_CAMERA_H

#include <opencv2/opencv.hpp>

class CAMERA {
public:
    CAMERA(int=0);
    void capturePhoto();
    cv::Mat& getPhoto();

private:
    cv::VideoCapture cap;
    cv::Mat photo;
};


#endif //BOMBERMAN_CAMERA_H
