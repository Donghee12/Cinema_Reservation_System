#include "DateSelector.h"

void DateSelector::Date()
{
    int date_ch;
    SYSTEMTIME st; // 시스템 시간을 가져오기 위한 구조체
    GetSystemTime(&st); // 시스템 시간 반환

    // 날짜 선택 옵션 출력
    cout << "==================================" << endl;
    cout << "            날짜 선택             " << endl;
    cout << "==================================" << endl;
    cout << "1. " << st.wYear << "년" << st.wMonth << "월" << st.wDay << "일" << endl;
    cout << "2. " << st.wYear << "년" << st.wMonth << "월" << st.wDay + 1 << "일" << endl;
    cout << "3. " << st.wYear << "년" << st.wMonth << "월" << st.wDay + 2 << "일" << endl;
    cout << "4. " << st.wYear << "년" << st.wMonth << "월" << st.wDay + 3 << "일" << endl;
    cout << "5. " << st.wYear << "년" << st.wMonth << "월" << st.wDay + 4 << "일" << endl;
    cout << "6. " << st.wYear << "년" << st.wMonth << "월" << st.wDay + 5 << "일" << endl;

    // 사용자로부터 날짜 선택 입력 받기
    cout << "보고싶은 날짜를 선택하세요 : ";
    cin >> date_ch;
    cout << endl;

    // 날짜에 따른 선택 결과 처리
    switch (date_ch)
    {
    case 1:
        s_date = to_string(st.wYear) + "년" + to_string(st.wMonth) + "월" + to_string(st.wDay) + "일"; 
        s_month = st.wMonth; s_day = st.wDay; break;
    case 2:
        s_date = to_string(st.wYear) + "년" + to_string(st.wMonth) + "월" + to_string(st.wDay + 1) + "일";
        s_month = st.wMonth; s_day = st.wDay+1; break;
    case 3:
        s_date = to_string(st.wYear) + "년" + to_string(st.wMonth) + "월" + to_string(st.wDay + 2) + "일";
        s_month = st.wMonth; s_day = st.wDay+2; break;
    case 4:
        s_date = to_string(st.wYear) + "년" + to_string(st.wMonth) + "월" + to_string(st.wDay + 3) + "일";
        s_month = st.wMonth; s_day = st.wDay+3; break;
    case 5:
        s_date = to_string(st.wYear) + "년" + to_string(st.wMonth) + "월" + to_string(st.wDay + 4) + "일";
        s_month = st.wMonth; s_day = st.wDay+4; break;
    case 6:
        s_date = to_string(st.wYear) + "년" + to_string(st.wMonth) + "월" + to_string(st.wDay + 5) + "일";
        s_month = st.wMonth; s_day = st.wDay+5; break;
    default:
        cout << "잘못된 날짜 선택이므로 다시 선택하세요." << endl;
        return Date(); // 잘못된 선택 시 재귀 호출로 다시 입력 받기
    }
    cout << "선택된 날짜는 " << s_date << "입니다." << endl << endl;
    system("cls"); // 화면 정리
}

// 선택된 날짜 반환
string DateSelector::g_Date()
{
    return s_date;
}

int DateSelector::g_Month()
{
    return s_month;
}

int DateSelector::g_Day()
{
    return s_day;
}