//
// Created by torchwood on 18/01/31.
//

#ifndef BOMBERMAN_UTILS_H
#define BOMBERMAN_UTILS_H

#include <opencv2/opencv.hpp>

void resizeForView(cv::Mat&);
void resizeForWindow(cv::Mat&);
void paste(cv::Mat dst, cv::Mat src, int x, int y, int width, int height);
void overlay(cv::Mat dst,cv::Mat src,int _x,int _y);

#endif //BOMBERMAN_UTILS_H
