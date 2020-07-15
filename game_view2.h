//
// Created by torchwood on 18/01/31.
//

#ifndef BOMBERMAN_GAME_VIEW2_H
#define BOMBERMAN_GAME_VIEW2_H
#include <opencv2/opencv.hpp>
#include "state.h"

class GAME_VIEW2 {
public:
    GAME_VIEW2();

    void synthesisView(cv::Mat &, STATE, double, int, int);//ゲームビューの合成
    cv::Mat &getView();//ビューのゲッター

private:
    void drawBG(STATE, int, int);//背景描画
    void drawColorView(cv::Mat &);//カラービューの描画
    void drawLogo(STATE);
    void drawTime(STATE, double);//残り時間の描画
    void drawScore(STATE,int, int);//スコアの描画

    void drawRedScore(int);
    void drawGreenScore(int);

    cv::Mat view;//// ビュー

    /*背景画像群*/

    //待機時の背景画像
    cv::Mat wait_image;

    //ゲーム中の背景画像(red有利、green有利,タイ)
    cv::Mat game_image_re;
    cv::Mat game_image_gr;
    cv::Mat game_image;

    //リザルト画面の背景画像(red勝利、green勝利、タイ)
    cv::Mat result_image_re;
    cv::Mat result_image_gr;
    cv::Mat result_image;

    //情報出力用画像
    cv::Mat numbers_image[10];
    cv::Mat numbers_image_lime[10];
    cv::Mat numbers_image_magenta[10];
    cv::Mat VS_image;
    cv::Mat time_left_image;
    cv::Mat red_win_image;
    cv::Mat green_win_image;
    cv::Mat draw_image;
    cv::Mat logo_image;

};
#endif //BOMBERMAN_GAME_VIEW_H