#pragma once

#include <iostream>
#include<string.h>
#include<vector>
using namespace std;

class Movie {

private:
    char name[30];  //��ȭ����
    bool reservation;   //���� ����

public:

    void Movie_Reservation();  //��ȭ�� �����մϴ�
    int ShowReservation();   //���� �޴��� �����ְ� ���õ� ��ȣ�� ��ȯ
    int ShowMovies(); //��ȭ ����� �����ְ� ���õ� ��ȣ�� ��ȯ
};

extern vector<string> movies;   //��ȭ ���
extern vector<string> reservation_menu; //���� �޴�
string getname();