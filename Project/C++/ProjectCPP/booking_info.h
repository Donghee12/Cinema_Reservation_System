#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <chrono>
#include <ctime>

using namespace std;

class booking_info {
private:
    string name;
    string movie;
    int month = -1;
    int day;
    int time;
    int people_num;
    char col;
    int row;
    int price;

public:
    void set_booking_info(string name, string movie, int month, int day,
        int time, int people_num, char col, int row, int price);
    void print_booking();
    string getname();
    string getmovie();
    int getmonth();
    void setmonth(int month);
    int getday();
    int gettime();
    int getpeople_num();
    char getcol();
    int getrow();
    int getprice();
};
//���� ����
void write(const string& str);
//���� ����
void clearFile();
//���� ���� ����
void booking_save_txt(const string& name, const string& movie, int month, int day,
    int time, int people_num, char col, int row, int price);
//���� ���� ����2
void booking_save_txt(booking_info b);

//���� ���� booking_info Ŭ���� �迭��
void booking_arr(booking_info b[]);
//���� Ȯ��
void search_booking(booking_info b[]);

int search_booking(booking_info b[], int a);

//���� �ð�
time_t now_time();
//���� �ð�
time_t movie_time(int month, int day, int hour);
//������� ���ɿ���
bool cancel_able(booking_info b);
//Ŭ���� �迭���� ����� ���� �����
void booking_cancel_arr(booking_info b[], int index);

//�������
void booking_cancel(booking_info b[]);
