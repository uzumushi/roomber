//
// Created by ubntu on 17/10/25.
//

#ifndef BOMBERMAN_TIMER_H
#define BOMBERMAN_TIMER_H

#include <chrono>

//時間計測クラス(未テスト)
class TIMER {
public:
    TIMER();
    int startTimer();//開始時刻の設定
    int getLeftTime();//残り時間を返す(ms)

private:
    int max_time;//最大時間
    std::chrono::system_clock::time_point start_time;//開始時刻
};


#endif //BOMBERMAN_TIMER_H
