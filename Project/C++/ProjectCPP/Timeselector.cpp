#include "TimeSelector.h"
#include "DateSelector.h"
// �ð� ���� �Լ�
void TimeSelector::Time()
{
    int time_ch;
    cout << "==================================" << endl;
    cout << "            �ð� ����             " << endl;
    cout << "==================================" << endl;
    cout << "1. 10 : 00 " << endl;
    cout << "2. 12 : 00 " << endl;
    cout << "3. 14 : 00 " << endl;
    cout << "4. 16 : 00 " << endl;
    cout << "5. 18 : 00 " << endl;
    cout << "������� �ð��� �����ϼ��� : ";
    cout << "�ڷΰ��⸦ �ϰ������ ���� '9' �Է� " << endl;
    cin >> time_ch;
    cout << endl;

    // �ð��� ���� ���� ��� ó��
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
        cout << "�߸��� �ð� �����̹Ƿ� �ٽ� �����ϼ���." << endl;
        return Time(); // �߸��� ���� �� ��� ȣ��� �ٽ� �Է� �ޱ�
    }
    cout << "���õ� �ð��� " << s_time << "���Դϴ�." << endl << endl;
    system("cls"); // ȭ�� ����
}

// ���õ� �ð� ��ȯ
int TimeSelector::g_Time()
{
    return s_time;
}
