//
// Created by ubntu on 17/10/20.
//

#include "color_map.h"
#include "constants.h"

static bool green_evaluate(int,int,int);
static bool red_evaluate(int,int,int);


COLOR_MAP::COLOR_MAP(){
    //適当に初期化
    init();
}

void COLOR_MAP::init() {
    map = cv::Mat::zeros(cv::Size(VIEW_WIDTH,VIEW_HEIGHT), CV_8UC3);
    red_total   =0 ;
    green_total =0 ;
}

void COLOR_MAP::synthesisMap( cv::Mat& _cvtphoto) {
   cv:: Mat _photo;
    _photo=_cvtphoto.clone();
    cv::cvtColor(_cvtphoto, _photo, CV_BGR2HSV);
    red_total   = 0;
    green_total = 0;
    //auto lower = cv::Scalar(0, 0, 254);
    //auto upper = cv::Scalar(0, 0, 255);

    //cv::inRange(colorImg, lower, upper, redOnlyImg);

    //１画素ずつ読み込み、マップを生成
    for(int y = 0; y < _photo.rows; ++y){
        //cv::Vec3b *pphoto = _photo.ptr<cv::Vec3b>(y);
        cv::Vec3b *pmap = map.ptr<cv::Vec3b>(y);

        for(int x = 0; x < _photo.cols; ++x){
            int hue = _photo.at<cv::Vec3b>(y, x)[0];
            int sat = _photo.at<cv::Vec3b>(y, x)[1];
            int val = _photo.at<cv::Vec3b>(y, x)[2];

            //if(!(pphoto[x][1] > THRESHOLD_GREEN && pphoto[x][2] > THRESHOLD_RED)) {

            if (green_evaluate(hue,sat,val) ) {
                pmap[x][1] = 255;
                pmap[x][2] = 0;
            } else if (red_evaluate(hue,sat,val)) {
                pmap[x][2] = 255;
                pmap[x][1] = 0;
            }

            //カウント処理
            if(pmap[x][2] == 255){
                red_total++;
            }
            else if(pmap[x][1] == 255){
                green_total++;
            }
        }
    }
}

const int COLOR_MAP::getRedRate() {
    if(red_total == 0) return 0;
    return 100 * red_total / (red_total + green_total);
}

const int COLOR_MAP::getGreenRate() {
    if(green_total == 0) return 0;
    return 100 - getRedRate();
}

cv::Mat& COLOR_MAP::getMap() {
    return map;
}

static bool green_evaluate(int hue,int sat,int val){
    return (hue > 70 && hue<105) && (sat <=255 && sat>120) && (val>60 && val<=255);
}

static bool red_evaluate(int hue,int sat,int val){
    return (hue > 155 && hue<180) && (sat >120 && sat<=255) && (val>60 && val<255);
}