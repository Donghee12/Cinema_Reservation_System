#include "reservation.h"


vector<string> movies = {   //��ȭ ���
         "ĸƾ �Ƹ޸�ī_�극�̺� �� ����",
         "���� �� ���� ���",
         "��Ʈ��2",
         "���� �����",
         "���ū"
};
//vector<string> reservation_menu = { //���� �޴�
//         "�����ϱ�",
//         "���ų���Ȯ���ϱ�",
//         "�����ߴ�"
//};


void Movie::Movie_Reservation() {  //��ȭ�� �����մϴ�
    reservation = true;
}

//int Movie::ShowReservation()   //���� �޴��� �����ְ� ���õ� ��ȣ�� ��ȯ
//{
//    int input;
//    cout << "======��ȭ ����======" << endl;
//    for (int i = 0; i < reservation_menu.size();i++)
//    {
//        cout << i + 1 << ". " << reservation_menu[i] << endl;
//    }
//    cout << "=====================" << endl;
//    cin >> input;
//    return input;
//}

int Movie::ShowMovies() //��ȭ ����� �����ְ� ���õ� ��ȣ�� ��ȯ
{
    int input;
    cout << "======��ȭ ���======" << endl;
    for (int j = 0; j < movies.size(); j++)
    {
        cout << j + 1 << ". " << movies[j] << endl;
    }
    cout << "======================" << endl;
    cin >> input;
    return input;
}

string getname() {
    string name;
    cout << "�������� ���̵� �Է��ϼ���:";
    cin >> name;
    return name;
}
