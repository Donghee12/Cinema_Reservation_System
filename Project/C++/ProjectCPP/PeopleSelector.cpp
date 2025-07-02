#include "PeopleSelector.h"
#include "TimeSelector.h"

// 인원 수 선택 함수
void Peopleselector::People()
{
    cout << "==================================" << endl;
    cout << "             인원 선택            " << endl;
    cout << "==================================" << endl;
    cout << "인원 수를 선택하세요 ( 1 ~ 8 ) : ";
    cout << "뒤로가기를 하고싶으면 숫자 '9' 입력     " << endl;
    cin >> C_people;
    cout << endl;

    // 인원 수가 잘못 입력되면 재입력 받기
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
        cout << "인원 수 입력이 잘못되었습니다. 다시 입력하세요" << endl;
        return People();
    }

    cout << "선택된 인원 수는 " << C_people << "명 입니다." << endl << endl;
    system("cls"); // 화면 정리
}

// 선택된 인원 수 반환
int Peopleselector::G_C_people()
{
    return C_people;
}