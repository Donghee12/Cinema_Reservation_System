#include "PeopleSelector.h"
#include "TimeSelector.h"

// �ο� �� ���� �Լ�
void Peopleselector::People()
{
    cout << "==================================" << endl;
    cout << "             �ο� ����            " << endl;
    cout << "==================================" << endl;
    cout << "�ο� ���� �����ϼ��� ( 1 ~ 8 ) : ";
    cout << "�ڷΰ��⸦ �ϰ������ ���� '9' �Է�     " << endl;
    cin >> C_people;
    cout << endl;

    // �ο� ���� �߸� �ԷµǸ� ���Է� �ޱ�
    if (C_people == 9)
    {
        system("cls");
        TimeSelector timeSelector;
        timeSelector.Time();
        People();
        return;
    }
    else if (C_people < 1 && C_people > 9)
    {
        cout << "�ο� �� �Է��� �߸��Ǿ����ϴ�. �ٽ� �Է��ϼ���" << endl;
        return People();
    }

    cout << "���õ� �ο� ���� " << C_people << "�� �Դϴ�." << endl << endl;
    system("cls"); // ȭ�� ����
}

// ���õ� �ο� �� ��ȯ
int Peopleselector::G_C_people()
{
    return C_people;
}