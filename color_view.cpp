//
// Created by ubntu on 17/10/20.
//

#include "color_view.h"
#include "constants.h"

COLOR_VIEW::COLOR_VIEW() {
    view = cv::Mat::zeros(cv::Size(VIEW_WIDTH,VIEW_HEIGHT), CV_8UC3);

}

void COLOR_VIEW::synthesisView(cv::Mat& _photo,cv::Mat& _map) {
    //画素ごとに演算
    for(int y = 0; y < _photo.rows; ++y){
        cv::Vec3b *pphoto   = _photo.ptr<cv::Vec3b>(y);
        cv::Vec3b *pmap     = _map.ptr<cv::Vec3b>(y);
        cv::Vec3b *pview    = view.ptr<cv::Vec3b>(y);

        for(int x = 0; x < _photo.cols; ++x){

            //photoの情報でイニシャライズ
            pview[x][0] = pphoto[x][0];
            pview[x][1] = pphoto[x][1];
            pview[x][2] = pphoto[x][2];

            //カラーマップの情報で塗りつぶし
            if(pmap[x][1] == 255){
                //蛍光グリーン
                pview[x][0] = ((int)pview[x][0]+60)/2;
                pview[x][1] = ((int)pview[x][1]+255) /2;
                pview[x][2] = (int)pview[x][2]/2;
            }

            else if(pmap[x][2] == 255){
                //どピンク
                pview[x][0] = ((int)pview[x][0] + 255) /2;
                pview[x][1] = ((int)pview[x][1]) /2;
                pview[x][2] = ((int)pview[x][2] + 255) /2;
            }

        }
    }
}

cv::Mat& COLOR_VIEW::getView() {
    return view;
}