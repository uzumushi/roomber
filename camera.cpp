//
// Created by torchwood on 17/10/26.
//

#include "camera.h"

CAMERA::CAMERA(int _camera_id) {
    cap.open(_camera_id);
}

void CAMERA::capturePhoto() {
    cap >> photo;
}

cv::Mat& CAMERA::getPhoto() {
    return photo;
}