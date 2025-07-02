#include "TimeSelector.h"
#include "DateSelector.h"
// 시간 선택 함수
void TimeSelector::Time()
{
    int time_ch;
    cout << "==================================" << endl;
    cout << "            시간 선택             " << endl;
    cout << "==================================" << endl;
    cout << "1. 10 : 00 " << endl;
    cout << "2. 12 : 00 " << endl;
    cout << "3. 14 : 00 " << endl;
    cout << "4. 16 : 00 " << endl;
    cout << "5. 18 : 00 " << endl;
    cout << "보고싶은 시간을 선택하세요 : ";
    cout << "뒤로가기를 하고싶으면 숫자 '9' 입력 " << endl;
    cin >> time_ch;
    cout << endl;

    // 시간에 따른 선택 결과 처리
    switch (time_ch)
    {
    case 1:
        s_time = 10; break;
    case 2:
        s_time = 12; break;
    case 3:
        s_time = 14; break;
    case 4:
        s_time = 16; break;
    case 5:
        s_time = 18; break;
    case 9:
    {
        system("cls");
        DateSelector dateSelector;
        dateSelector.Date();
        Time();
        return;
    }
    default:
        cout << "잘못된 시간 선택이므로 다시 선택하세요." << endl;
        return Time(); // 잘못된 선택 시 재귀 호출로 다시 입력 받기
    }
    cout << "선택된 시간은 " << s_time << "시입니다." << endl << endl;
    system("cls"); // 화면 정리
}

// 선택된 시간 반환
int TimeSelector::g_Time()
{
    return s_time;
}
