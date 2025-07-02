#pragma once

#include <iostream>
#include<string.h>
#include<vector>
using namespace std;

class Movie {

private:
    char name[30];  //영화제목
    bool reservation;   //예매 유무

public:

    void Movie_Reservation();  //영화를 예매합니다
    int ShowReservation();   //예매 메뉴를 보여주고 선택된 번호를 반환
    int ShowMovies(); //영화 목록을 보여주고 선택된 번호를 반환
};

extern vector<string> movies;   //영화 목록
extern vector<string> reservation_menu; //예매 메뉴
string getname();