#include <opencv2/opencv.hpp>
#include "constants.h"
#include "color_map.h"
#include "color_view.h"
#include "game_view.h"
#include "game_view2.h"
#include "camera.h"
#include "timer.h"
#include "utils.h"
#include "state.h"

//ROS関連include
#include "ros/ros.h"
#include "cv_bridge/cv_bridge.h"
#include "roomber/game_status.h"

#include <iostream>

void resizeForView(cv::Mat&);
void resizeForWindow(cv::Mat&);

void setMessage(roomber::game_status&,bool,int,int,int,cv::Mat&);

TIMER timer;
int left_time;

//画面をマウスでクリックした時、ステートを変化させる
void CallBackFunc(int eventType, int x, int y, int flags,void* _state)
{

    STATE* state = static_cast<STATE*>(_state);

    if(eventType == cv::EVENT_LBUTTONDOWN){

        switch(*state){
            case wait:
                *state = game;
                timer.startTimer();
                left_time = timer.getLeftTime();
                break;

            case game:  *state = wait;break;
            case result:*state = wait;break;
        }
    }

}



int main(int argc,char** argv) {

    COLOR_MAP  color_map;
    COLOR_VIEW color_view;
    GAME_VIEW2 game_view;
    CAMERA camera;

    STATE state = wait;

    //ros初期化
    ros::init(argc, argv, "Miach");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<roomber::game_status>("game_status",1);

    ros::Rate loop_rate(1);

    roomber::game_status status_message;


    //ウィンドウ生成
    cvNamedWindow("ROOMBER", CV_WINDOW_AUTOSIZE);

    cv::setMouseCallback("ROOMBER", CallBackFunc, &state);
    timer.startTimer();
    left_time = timer.getLeftTime();

    while(ros::ok()){

        //カメラのキャプチャ
        if(state != result) {
            camera.capturePhoto();
            resizeForView(camera.getPhoto());
        }

        //カラーマップの合成
        switch (state){
            case game:color_map.synthesisMap(camera.getPhoto());break;
            case wait:color_map.init();break;
        }

        //カラービューの合成
        color_view.synthesisView(camera.getPhoto(), color_map.getMap());

        //ゲームビューの合成
        game_view.synthesisView(color_view.getView(), state, state == game ? timer.getLeftTime() : 0,
                                color_map.getRedRate(), color_map.getGreenRate());//ゲームビューの合成

        //ウィンドウに描画
        cv::imshow("ROOMBER", game_view.getView());
        cv::waitKey(1);

        std::cout << "red:" << color_map.getRedRate() << " green:" << color_map.getGreenRate() << std::endl;


        //適当なレートでパブリッシュ
        if(left_time != timer.getLeftTime()) {
            setMessage(status_message, state == game ? true:false, color_map.getRedRate(), color_map.getGreenRate(), state == game ? timer.getLeftTime():0, color_map.getMap());
            pub.publish(status_message);
            left_time = timer.getLeftTime();

            if(left_time == 0 && state == game){
                state = result;
            }

        }
    }

    /*
    //カメラ機能テスト
    for(int i=0; i<10000; i++) {
        camera.capturePhoto();

        resizeForView(camera.getPhoto());
        color_map.synthesisMap(camera.getPhoto());

        color_view.synthesisView(camera.getPhoto(),color_map.getMap());

        cv::imshow("ROOMBER", color_view.getView());

        std::cout << "red:" << color_map.getRedRate() << " green:" << color_map.getGreenRate() << std::endl;

        setMessage(status_message,true,color_map.getRedRate(),color_map.getGreenRate(),10,color_view.getView());
        pub.publish(status_message);
        cv::waitKey(100);
    }


    cv::imwrite("photo1.jpg",camera.getPhoto());

    */


    //カラービュー作成テスト
    /*
    cv::Mat image1 = cv::imread("photo.jpg",1);
    resizeForView(image1);
    color_map.synthesisMap(image1);
    cv::imshow("Bomber man",color_map.getMap());
    cv::waitKey(0);

    color_view.synthesisView(image1,color_map.getMap());
    cv::imshow("Bomber man",color_view.getView());
    cv::waitKey(0);

    cv::imwrite("image1.jpg",image1);
    cv::imwrite("color_map.jpg",color_map.getMap());
    cv::imwrite("color_view.jpg",color_view.getView());
    */

    //カラー・マップ作成テスト
    /*
    cv::Mat image1 = cv::imread("restless.jpeg",1);
    resizeForView(image1);
    color_map.synthesisMap(image1);
    cv::imshow("Bomber man",color_map.getMap());
    cv::waitKey(0);

    cv::Mat image2 = cv::imread("BvS.jpg",1);
    resizeForView(image2);
    color_map.synthesisMap(image2);
    cv::imshow("Bomber man",color_map.getMap());
    cv::waitKey(0);
    */


    return 0;
}


void setMessage(roomber::game_status& status_message,bool _running,int _red_score,int _green_score,int _left_time,cv::Mat& _color_map){
    status_message.running = _running;
    status_message.red_score = _red_score;
    status_message.green_score = _green_score;
    status_message.left_time = _left_time;
    status_message.color_map = *cv_bridge::CvImage(std_msgs::Header(),"bgr8",_color_map).toImageMsg();

}
