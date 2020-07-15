//
// Created by ubntu on 17/10/20.
//

#ifndef BOMBERMAN_COLOR_MAP_H
#define BOMBERMAN_COLOR_MAP_H

#include <opencv2/opencv.hpp>

//カラーマップクラス
class COLOR_MAP {
public:
    COLOR_MAP();
    void synthesisMap(cv::Mat& );//カラーマップの生成
    const int getRedRate();//赤側の得点率を返す
    const int getGreenRate();//緑側の得点率を返す
    cv::Mat& getMap();//ゲッターofマップ画像
    void init();

private:
    cv::Mat map;//マップ画像
    int red_total;//赤画素総数
    int green_total;//緑画素総数

};


#endif //BOMBERMAN_COLOR_MAP_H
