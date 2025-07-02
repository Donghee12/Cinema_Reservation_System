#include "reservation.h"


vector<string> movies = {   //영화 목록
         "캡틴 아메리카_브레이브 뉴 월드",
         "말할 수 없는 비밀",
         "히트맨2",
         "검은 수녀들",
         "브로큰"
};
//vector<string> reservation_menu = { //예매 메뉴
//         "예매하기",
//         "예매내역확인하기",
//         "예매중단"
//};


void Movie::Movie_Reservation() {  //영화를 예매합니다
    reservation = true;
}

//int Movie::ShowReservation()   //예매 메뉴를 보여주고 선택된 번호를 반환
//{
//    int input;
//    cout << "======영화 예매======" << endl;
//    for (int i = 0; i < reservation_menu.size();i++)
//    {
//        cout << i + 1 << ". " << reservation_menu[i] << endl;
//    }
//    cout << "=====================" << endl;
//    cin >> input;
//    return input;
//}

int Movie::ShowMovies() //영화 목록을 보여주고 선택된 번호를 반환
{
    int input;
    cout << "======영화 목록======" << endl;
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
    cout << "예매자의 아이디를 입력하세요:";
    cin >> name;
    return name;
}
