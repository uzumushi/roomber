//
// Created by ubntu on 17/10/20.
//

#ifndef BOMBERMAN_COLOR_VIEW_H
#define BOMBERMAN_COLOR_VIEW_H

#include <opencv2/opencv.hpp>

//カラービュークラス
class COLOR_VIEW {
public:
    COLOR_VIEW();
    void synthesisView(cv::Mat&,cv::Mat&);//カラービューの合成
    cv::Mat& getView();//ゲッター

private:
    cv::Mat view;//ビュー
};


#endif //BOMBERMAN_COLOR_VIEW_H
