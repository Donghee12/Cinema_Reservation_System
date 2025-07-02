#pragma once

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class DateSelector
{
private:
    string s_date; // 선택된 날짜 저장
    int s_month;
    int s_day;
public:
    // 날짜 선택 함수
    void Date();
    // 선택된 날짜 반환
    string g_Date();
    int g_Month();
    int g_Day();
};
