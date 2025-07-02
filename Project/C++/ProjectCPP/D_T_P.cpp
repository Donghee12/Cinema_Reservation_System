#include "D_T_P.h"

string selectedDate = " ";   // ���õ� ��¥
int selectedTime = 0;   // ���õ� �ð�
int selectedPeople = 0;      // ���õ� �ο� ��
int selectedMonth = 0;
int selectedDay = 0;


// ��¥, �ð�, �ο� ���� �����Ͽ� ���õ� ������ ���
void D_T_P_mix()
{
    DateSelector dateS;
    dateS.Date();
    TimeSelector timeS;
    timeS.Time();
    Peopleselector peopleS;
    peopleS.People();

    // ���� ������ ���� �Ҵ�
    selectedDate = dateS.g_Date();
    selectedMonth = dateS.g_Month();
    selectedDay = dateS.g_Day();
    selectedTime = timeS.g_Time();
    selectedPeople = peopleS.G_C_people();

    // ���õ� ��¥, �ð�, �ο� �� ���
    cout << "���� ���õ� ��¥�� " << selectedDate << "�Դϴ�." << endl;
    cout << "���� ���õ� �ð��� " << selectedTime << "���Դϴ�." << endl;
    cout << "���� ���õ� �ο� ���� " << selectedPeople << "�� �Դϴ�." << endl;
    cout << endl;
}