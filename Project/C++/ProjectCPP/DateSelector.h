#pragma once

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class DateSelector
{
private:
    string s_date; // ���õ� ��¥ ����
    int s_month;
    int s_day;
public:
    // ��¥ ���� �Լ�
    void Date();
    // ���õ� ��¥ ��ȯ
    string g_Date();
    int g_Month();
    int g_Day();
};
