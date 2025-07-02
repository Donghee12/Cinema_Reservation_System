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
//파일 쓰기
void write(const string& str);
//파일 비우기
void clearFile();
//예매 정보 저장
void booking_save_txt(const string& name, const string& movie, int month, int day,
    int time, int people_num, char col, int row, int price);
//예매 정보 저장2
void booking_save_txt(booking_info b);

//예매 파일 booking_info 클래스 배열로
void booking_arr(booking_info b[]);
//예매 확인
void search_booking(booking_info b[]);

int search_booking(booking_info b[], int a);

//현재 시간
time_t now_time();
//예매 시간
time_t movie_time(int month, int day, int hour);
//예매취소 가능여부
bool cancel_able(booking_info b);
//클래스 배열에서 취소한 예매 지우기
void booking_cancel_arr(booking_info b[], int index);

//예매취소
void booking_cancel(booking_info b[]);
