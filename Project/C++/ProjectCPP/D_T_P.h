#pragma once
#include "DateSelector.h"
#include "TimeSelector.h"
#include "PeopleSelector.h"

extern string selectedDate;   // 선택된 날짜
extern int selectedTime;   // 선택된 시간
extern int selectedPeople;      // 선택된 인원 수
extern int selectedMonth;
extern int selectedDay;

// 날짜, 시간, 인원 수를 결합하여 선택된 내용을 출력
void D_T_P_mix();