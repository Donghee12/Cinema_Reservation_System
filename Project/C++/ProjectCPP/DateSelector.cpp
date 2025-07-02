#include "DateSelector.h"

void DateSelector::Date()
{
    int date_ch;
    SYSTEMTIME st; // �ý��� �ð��� �������� ���� ����ü
    GetSystemTime(&st); // �ý��� �ð� ��ȯ

    // ��¥ ���� �ɼ� ���
    cout << "==================================" << endl;
    cout << "            ��¥ ����             " << endl;
    cout << "==================================" << endl;
    cout << "1. " << st.wYear << "��" << st.wMonth << "��" << st.wDay << "��" << endl;
    cout << "2. " << st.wYear << "��" << st.wMonth << "��" << st.wDay + 1 << "��" << endl;
    cout << "3. " << st.wYear << "��" << st.wMonth << "��" << st.wDay + 2 << "��" << endl;
    cout << "4. " << st.wYear << "��" << st.wMonth << "��" << st.wDay + 3 << "��" << endl;
    cout << "5. " << st.wYear << "��" << st.wMonth << "��" << st.wDay + 4 << "��" << endl;
    cout << "6. " << st.wYear << "��" << st.wMonth << "��" << st.wDay + 5 << "��" << endl;

    // ����ڷκ��� ��¥ ���� �Է� �ޱ�
    cout << "������� ��¥�� �����ϼ��� : ";
    cin >> date_ch;
    cout << endl;

    // ��¥�� ���� ���� ��� ó��
    switch (date_ch)
    {
    case 1:
        s_date = to_string(st.wYear) + "��" + to_string(st.wMonth) + "��" + to_string(st.wDay) + "��"; 
        s_month = st.wMonth; s_day = st.wDay; break;
    case 2:
        s_date = to_string(st.wYear) + "��" + to_string(st.wMonth) + "��" + to_string(st.wDay + 1) + "��";
        s_month = st.wMonth; s_day = st.wDay+1; break;
    case 3:
        s_date = to_string(st.wYear) + "��" + to_string(st.wMonth) + "��" + to_string(st.wDay + 2) + "��";
        s_month = st.wMonth; s_day = st.wDay+2; break;
    case 4:
        s_date = to_string(st.wYear) + "��" + to_string(st.wMonth) + "��" + to_string(st.wDay + 3) + "��";
        s_month = st.wMonth; s_day = st.wDay+3; break;
    case 5:
        s_date = to_string(st.wYear) + "��" + to_string(st.wMonth) + "��" + to_string(st.wDay + 4) + "��";
        s_month = st.wMonth; s_day = st.wDay+4; break;
    case 6:
        s_date = to_string(st.wYear) + "��" + to_string(st.wMonth) + "��" + to_string(st.wDay + 5) + "��";
        s_month = st.wMonth; s_day = st.wDay+5; break;
    default:
        cout << "�߸��� ��¥ �����̹Ƿ� �ٽ� �����ϼ���." << endl;
        return Date(); // �߸��� ���� �� ��� ȣ��� �ٽ� �Է� �ޱ�
    }
    cout << "���õ� ��¥�� " << s_date << "�Դϴ�." << endl << endl;
    system("cls"); // ȭ�� ����
}

// ���õ� ��¥ ��ȯ
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