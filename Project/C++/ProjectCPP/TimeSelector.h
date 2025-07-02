#pragma once

#include <iostream>
#include <string>

using namespace std;

class TimeSelector
{
private:
    int s_time; // 선택된 시간 저장

public:
    // 시간 선택 함수
    void Time();
    // 선택된 시간 반환
    int g_Time();
};
