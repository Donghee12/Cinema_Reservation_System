#pragma once
#include "DateSelector.h"
#include "TimeSelector.h"
#include "PeopleSelector.h"

extern string selectedDate;   // ���õ� ��¥
extern int selectedTime;   // ���õ� �ð�
extern int selectedPeople;      // ���õ� �ο� ��
extern int selectedMonth;
extern int selectedDay;

// ��¥, �ð�, �ο� ���� �����Ͽ� ���õ� ������ ���
void D_T_P_mix();