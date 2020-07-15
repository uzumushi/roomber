//
// Created by torchwood on 18/01/31.
//

#include <vector>
#include <iostream>
#include "utils.h"
#include "constants.h"
using namespace std;

void resizeForView(cv::Mat& photo){
    resize(photo, photo, cv::Size(), (double)VIEW_WIDTH / photo.cols, (double)VIEW_HEIGHT / photo.rows);
}

void resizeForWindow(cv::Mat& photo){
    resize(photo, photo, cv::Size(), (double)WINDOW_WIDTH / photo.cols, (double)WINDOW_HEIGHT / photo.rows);
}

void paste(cv::Mat dst, cv::Mat src, int x, int y, int width, int height) {
    cv::Mat resized_img;
    cv::resize(src, resized_img, cv::Size(width, height));

    if (x >= dst.cols || y >= dst.rows) return;
    int w = (x >= 0) ? std::min(dst.cols - x, resized_img.cols) : std::min(std::max(resized_img.cols + x, 0), dst.cols);
    int h = (y >= 0) ? std::min(dst.rows - y, resized_img.rows) : std::min(std::max(resized_img.rows + y, 0), dst.rows);
    int u = (x >= 0) ? 0 : std::min(-x, resized_img.cols - 1);
    int v = (y >= 0) ? 0 : std::min(-y, resized_img.rows - 1);
    int px = std::max(x, 0);
    int py = std::max(y, 0);

    cv::Mat roi_dst = dst(cv::Rect(px, py, w, h));
    cv::Mat roi_resized = resized_img(cv::Rect(u, v, w, h));
    roi_resized.copyTo(roi_dst);
}

void overlay(cv::Mat dst,cv::Mat src,int _x,int _y){


    for(int y = 0; y < src.rows; ++y){
        cv::Vec3b *pdst    = dst.ptr<cv::Vec3b>(y + _y);
        cv::Vec4b *psrc    = src.ptr<cv::Vec4b>(y);

        for(int x = 0; x < src.cols; ++x){



             //カラーマップの情報で塗りつぶし
            if(psrc[x][3] != 0){

                //蛍光グリーン
                pdst[x + _x][0] = psrc[x][0];
                pdst[x + _x][1] = psrc[x][1];
                pdst[x + _x][2] = psrc[x][2];
            }
        }
    }
}