//
// Created by ubntu on 17/10/25.
//

#ifndef BOMBERMAN_GAME_VIEW_H
#define BOMBERMAN_GAME_VIEW_H
#include <opencv2/opencv.hpp>
#include "state.h"

class GAME_VIEW {
public:
    GAME_VIEW();

    void synthesisView(cv::Mat &, STATE, double, int, int);//ゲームビューの合成
    cv::Mat &getView();//ビューのゲッター

private:
    void drawBG(STATE, int, int);//背景描画
    void drawColorView(cv::Mat &);//カラービューの描画
    void drawTime(STATE, double);//残り時間の描画
    void drawScore(STATE,int, int);//スコアの描画
    void paste(cv::Mat dst, cv::Mat src, int x, int y, int width, int height);//画像の重ねあわせ

public:
    cv::Mat view;//ビュー
    cv::Mat AAA = cv::imread("/home/torchwood/ros_ws/devel/lib/bomberman/02.jpg",1);
    //cv::Mat BBB = cv::imread("03.jpg",1);
    //cv::Mat CCC = cv::imread("04.jpg",1);
    cv::Mat DDD = cv::imread("/home/torchwood/ros_ws/devel/lib/bomberman/05.JPG",1);
    cv::Mat EEE = cv::imread("/home/torchwood/ros_ws/devel/lib/bomberman/06.JPG",1);
    cv::Mat FFF = cv::imread("/home/torchwood/ros_ws/devel/lib/bomberman/07.png",1);
    cv::Mat GGG = cv::imread("/home/torchwood/ros_ws/devel/lib/bomberman/08.jpg",1);
    cv::Mat HHH = cv::imread("/home/torchwood/ros_ws/devel/lib/bomberman/09.jpeg",1);

};
#endif //BOMBERMAN_GAME_VIEW_H