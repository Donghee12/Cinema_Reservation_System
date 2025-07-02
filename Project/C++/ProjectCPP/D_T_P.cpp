#include "D_T_P.h"

string selectedDate = " ";   // 선택된 날짜
int selectedTime = 0;   // 선택된 시간
int selectedPeople = 0;      // 선택된 인원 수
int selectedMonth = 0;
int selectedDay = 0;


// 날짜, 시간, 인원 수를 결합하여 선택된 내용을 출력
void D_T_P_mix()
{
    DateSelector dateS;
    dateS.Date();
    TimeSelector timeS;
    timeS.Time();
    Peopleselector peopleS;
    peopleS.People();

    // 전역 변수에 값을 할당
    selectedDate = dateS.g_Date();
    selectedMonth = dateS.g_Month();
    selectedDay = dateS.g_Day();
    selectedTime = timeS.g_Time();
    selectedPeople = peopleS.G_C_people();

    // 선택된 날짜, 시간, 인원 수 출력
    cout << "현재 선택된 날짜는 " << selectedDate << "입니다." << endl;
    cout << "현재 선택된 시간은 " << selectedTime << "시입니다." << endl;
    cout << "현재 선택된 인원 수는 " << selectedPeople << "명 입니다." << endl;
    cout << endl;
}