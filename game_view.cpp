//
// Created by ubntu on 17/10/25.
//

#include "game_view.h"
#include "constants.h"
using namespace std;

GAME_VIEW::GAME_VIEW() {
    //適当に初期化
    view = cv::Mat::zeros(cv::Size(WINDOW_WIDTH,WINDOW_HEIGHT), CV_8UC3);

}

void GAME_VIEW::synthesisView(cv::Mat& _color_view, STATE _state, double _left_time, int _red_score, int _green_score) {
    //ビューの合成処理
    view = cv::Mat::zeros(cv::Size(WINDOW_WIDTH, WINDOW_HEIGHT), CV_8UC3);
    drawBG(_state, _red_score, _green_score);
    drawColorView(_color_view);
    drawTime(_state, _left_time);
    drawScore(_state, _red_score, _green_score);
}

cv::Mat& GAME_VIEW::getView() {
    return view;
}

void GAME_VIEW::drawBG(STATE _state, int _red_score, int _green_score) {
    //resize(img, img, cv::Size(), 500.0 / img.cols, 500.0 / img.rows);
    //cv::Mat red_img(cv::Size(WINDOW_WIDTH,WINDOW_HEIGHT), CV_8UC3, cv::Scalar(0,0,255));
    view = cv::Mat::zeros(cv::Size(WINDOW_WIDTH,WINDOW_HEIGHT), CV_8UC3);
    if (_state == wait) {
        cv:: Mat temp;
        temp = AAA.clone();
        resize(temp, temp, cv::Size(), 800.0 / AAA.cols, 600.0 / AAA.rows);
        view = temp;
    }
    else if (_state == game) {
        cv:: Mat temp;
        temp = DDD.clone();
        resize(temp, temp, cv::Size(), 800.0 / DDD.cols, 600.0 / DDD.rows);
        view = temp;
    }
    else if (_state == result) {
        cv:: Mat temp;
        temp = EEE.clone();
        resize(temp, temp, cv::Size(), 800.0 / EEE.cols, 600.0 / EEE.rows);
        view = temp;
    }
    else if (_red_score >= 70) {
        cv:: Mat temp;
        temp = GGG.clone();
        resize(temp, temp, cv::Size(), 800.0 / GGG.cols, 600.0 / GGG.rows);
        view = temp;
    }
    else if (_green_score >= 70) {
        cv:: Mat temp;
        temp = HHH.clone();
        resize(temp, temp, cv::Size(), 800.0 / HHH.cols, 600.0 / HHH.rows);
        view = temp;
    }
    else {
        cv:: Mat temp;
        temp = FFF.clone();
        resize(temp, temp, cv::Size(), 800.0 / FFF.cols, 600.0 / FFF.rows);
        view = temp;
    }
    //cout << "Mat width: " << view.rows << endl;
    //cout << "Mat height: " << view.cols << endl;
    //背景をviewに描画してください
    //_state及び、現在のスコアに応じて背景が変わると尚良い
    //背景に用いる画像はフィールドとしてクラスに追加し、コンストラクタで読み込んでください
}

void GAME_VIEW::drawColorView(cv::Mat& _color_view) {
    cv::Mat temp;
    temp = _color_view.clone();
    paste(view, temp, 1, 1,VIEW_WIDTH, VIEW_HEIGHT);

    //カラービューをviewに描画してください
    //合成用の関数はopenCVになかったはずなので適当に用意してください(Time,Scoreも同様)
    //描画を行う座標定数はconstants.h等に定義してください(Time,Scoreも同様)
}

void GAME_VIEW::drawTime(STATE _state, double _left_time) {
    //残り時間をviewに描画してください
    //単位はsで小数点以下切上げにしてください
    //イカフォントなどを使うと尚良い
    int face[] = { cv::FONT_HERSHEY_SIMPLEX, cv::FONT_HERSHEY_PLAIN, cv::FONT_HERSHEY_DUPLEX, cv::FONT_HERSHEY_COMPLEX,
                   cv::FONT_HERSHEY_TRIPLEX, cv::FONT_HERSHEY_COMPLEX_SMALL, cv::FONT_HERSHEY_SCRIPT_SIMPLEX,
                   cv::FONT_HERSHEY_SCRIPT_COMPLEX, cv::FONT_ITALIC };
    double Lefttime = _left_time;
    int b = (int)Lefttime;//キャスト演算子
    char OnTime[256];
    sprintf(OnTime, "%d sec left", b);
    cv::putText(view, OnTime, cv::Point(500, 150), face[0], 1.2, cv::Scalar(200, 200, 200), 2, CV_AA);

}

void GAME_VIEW::drawScore(STATE _state, int _red_score, int _green_score) {
    //スコアをviewに描画してください
    //イカフォントなどを使うと尚良い
    int redscore = _red_score;
    int greenscore = _green_score;
    int face[] = { cv::FONT_HERSHEY_SIMPLEX, cv::FONT_HERSHEY_PLAIN, cv::FONT_HERSHEY_DUPLEX, cv::FONT_HERSHEY_COMPLEX,
                   cv::FONT_HERSHEY_TRIPLEX, cv::FONT_HERSHEY_COMPLEX_SMALL, cv::FONT_HERSHEY_SCRIPT_SIMPLEX,
                   cv::FONT_HERSHEY_SCRIPT_COMPLEX, cv::FONT_ITALIC };
    char value_RedScore[256];
    char value_GreenScore[256];//次の行で使う一時的な変数
    sprintf(value_RedScore, "%d", redscore);
    sprintf(value_GreenScore, "%d", greenscore); //変数の値も含めた表示したい文字列をchar型変数に格納
    cv::putText(view, value_RedScore, cv::Point(500, 250), face[0], 1.2, cv::Scalar(0, 0, 200), 2, CV_AA);
    cv::putText(view, value_GreenScore, cv::Point(600, 50), face[0] | face[8], 1.2, cv::Scalar(100, 200, 100), 2, CV_AA);
}

void GAME_VIEW::paste(cv::Mat dst, cv::Mat src, int x, int y, int width, int height) {
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

//お腹空いたので帰ります