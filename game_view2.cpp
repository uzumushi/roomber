//
// Created by torchwood on 18/01/31.
//

#include <iostream>
#include "game_view2.h"
#include "utils.h"
#include "constants.h"

//コンストラクタ適当に初期化
GAME_VIEW2::GAME_VIEW2() {
    //適当に初期化
    view = cv::Mat::zeros(cv::Size(WINDOW_WIDTH,WINDOW_HEIGHT), CV_8UC3);

    //各背景
    wait_image = cv::imread("image/wait_image.png");

    game_image_re = cv::imread("image/game_image_red.png");
    game_image_gr = cv::imread("image/game_image_green.png");
    game_image    = cv::imread("image/game_image.png");

    result_image_re = cv::imread("image/result_image_red.png");
    result_image_gr = cv::imread("image/result_image_green.png");
    result_image    = cv::imread("image/result_image.png");

    //対戦情報表示用画像

    /*雑、関数化すれば省略可能*/

    //black numbers
    std::string black_path=("image/numbers/");
    for(int i=0;i<10;i++){
        std::string tmp=black_path;
        tmp += (char)('0' + i);
        tmp += ".png";
        numbers_image[i] = cv::imread(tmp,cv::IMREAD_UNCHANGED);
    }

    //lime numbers
    std::string lime_path("image/lime_numbers/");
    for(int i=0;i<10;i++){
        std::string tmp=lime_path;
        tmp += (char)('0' + i);
        tmp += ".png";
        numbers_image_lime[i] = cv::imread(tmp,cv::IMREAD_UNCHANGED);

    }

    //magenta numbers
    std::string magenta_path("image/magenta_numbers/");
    for(int i=0;i<10;i++){
        std::string tmp=magenta_path;
        tmp += (char)('0' + i);
        tmp += ".png";
        numbers_image_magenta[i] = cv::imread(tmp,cv::IMREAD_UNCHANGED);

    }

    VS_image = cv::imread("image/VS.png",cv::IMREAD_UNCHANGED);
    time_left_image = cv::imread("image/sec_left.png",cv::IMREAD_UNCHANGED);
    red_win_image = cv::imread("image/red_win.png",cv::IMREAD_UNCHANGED);
    green_win_image = cv::imread("image/green_win.png",cv::IMREAD_UNCHANGED);
    draw_image =cv::imread("image/draw.png",cv::IMREAD_UNCHANGED);
    logo_image = cv::imread("image/roomber.png",cv::IMREAD_UNCHANGED);
}

//画面の合成
void GAME_VIEW2::synthesisView(cv::Mat& _color_view, STATE _state, double _left_time, int _red_score, int _green_score) {
    //ビューの合成処理
    view = cv::Mat::zeros(cv::Size(WINDOW_WIDTH, WINDOW_HEIGHT), CV_8UC3);
    drawBG(_state, _red_score, _green_score);
    drawColorView(_color_view);
    drawLogo(_state);
    drawTime(_state, _left_time);
    drawScore(_state, _red_score, _green_score);
}

//ビューのゲッタ
cv::Mat& GAME_VIEW2::getView() {
    return view;
}

//背景の描画
void GAME_VIEW2::drawBG(STATE _state, int _red_score, int _green_score) {
    //resize(img, img, cv::Size(), 500.0 / img.cols, 500.0 / img.rows);
    //cv::Mat red_img(cv::Size(WINDOW_WIDTH,WINDOW_HEIGHT), CV_8UC3, cv::Scalar(0,0,255));

    cv:: Mat temp;

    switch(_state){
        //ステートがwait状態の時
        case wait:
            temp = wait_image.clone();break;

        //ステートがgame状態の時
        case game:
            if(_red_score == _green_score)
                temp = game_image.clone();
            else if(_red_score > _green_score)
                temp = game_image_re.clone();
            else
                temp = game_image_gr.clone();
            break;

        //ステートがresult状態の時
        case result:
            if(_red_score == _green_score)
                temp = result_image.clone();
            else if(_red_score > _green_score)
                temp = result_image_re.clone();
            else
                temp = result_image_gr.clone();
            break;
    }

    //リサイズして設定
    resizeForWindow(temp);
    view = temp;

    //cout << "Mat width: " << view.rows << endl;
    //cout << "Mat height: " << view.cols << endl;
    //背景をviewに描画してください
    //_state及び、現在のスコアに応じて背景が変わると尚良い
    //背景に用いる画像はフィールドとしてクラスに追加し、コンストラクタで読み込んでください
}

//カラービューの描画
void GAME_VIEW2::drawColorView(cv::Mat& _color_view) {
    cv::Mat temp;
    temp = _color_view.clone();
    paste(view, temp, 20 , (WINDOW_HEIGHT - VIEW_HEIGHT )/ 2,VIEW_WIDTH, VIEW_HEIGHT);

    //カラービューをviewに描画してください
    //合成用の関数はopenCVになかったはずなので適当に用意してください(Time,Scoreも同様)
    //描画を行う座標定数はconstants.h等に定義してください(Time,Scoreも同様)
}

//ロゴの描画
void GAME_VIEW2::drawLogo(STATE _state) {

    if(_state == wait){
        overlay(view,logo_image,(WINDOW_WIDTH - logo_image.cols)/2,30);
    }
}

void GAME_VIEW2::drawTime(STATE _state, double _left_time) {
    //残り時間をviewに描画してください
    //単位はsで小数点以下切上げにしてください
    //イカフォントなどを使うと尚良い

    int left_time = _left_time;

    if(_state ==game) {
        if(_left_time >= 100)
            overlay(view,numbers_image[ left_time / 100],320,0);

        if(_left_time >= 10)
            overlay(view,numbers_image[ (left_time /10) % 10],360,0);

        overlay(view,numbers_image[ left_time % 10],400,0);

        overlay(view, time_left_image, 450, 25);
    }
}

void GAME_VIEW2::drawScore(STATE _state, int _red_score, int _green_score) {
    //スコアをviewに描画してください
    //イカフォントなどを使うと尚良い

    if(_state == result){
        if(_red_score == _green_score)
            overlay(view,draw_image,370,10);

        else if(_red_score > _green_score)
            overlay(view,red_win_image,300,10);

        else
            overlay(view,green_win_image,230,10);

    }

    std::cout << "magenta:" <<_red_score << " lime:" << _green_score <<std::endl;
    drawRedScore(_red_score);
    drawGreenScore(_green_score);
    overlay(view,VS_image,440,205);
}

void GAME_VIEW2::drawRedScore(int _score) {

    if(_score == 100){
        overlay(view,numbers_image_magenta[_score/100],350,130);
        overlay(view,numbers_image_magenta[(_score/10)%10],390,130);
        overlay(view,numbers_image_magenta[_score%10],430,130);
    }else if(_score >= 10){
        overlay(view,numbers_image_magenta[_score/10],390,130);
        overlay(view,numbers_image_magenta[_score%10],430,130);
    }else{
        overlay(view,numbers_image_magenta[_score%10],400,130);
    }
}

void GAME_VIEW2::drawGreenScore(int _score) {

    if(_score == 100){
        overlay(view,numbers_image_lime[_score/100],480,280);
        overlay(view,numbers_image_lime[(_score/10)%10],520,280);
        overlay(view,numbers_image_lime[_score%10],560,280);
    }
    else if(_score >= 10){
        overlay(view,numbers_image_lime[_score/10],520,280);
        overlay(view,numbers_image_lime[_score%10],560,280);
    }else{
        overlay(view,numbers_image_lime[_score%10],550,280);
    }

}

//お腹空いたので帰ります
