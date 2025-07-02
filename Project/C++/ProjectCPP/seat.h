#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int ROWS = 9;  // 열 개수 (1~9)
const int COLS = 10; // 행 개수 (A~J)
extern vector<vector<bool>> seats; // 좌석 상태 (false: 빈 좌석, true: 예약됨)
extern vector<string> reserved_seats; // 예약된 좌석 정보를 저장할 벡터
// 결제 완료 후 예약된 좌석을 추적하는 벡터 추가
extern vector<string> paid_reserved_seats;  // 결제 완료된 좌석 정보를 저장

extern int balance;
extern const int seat_price;
extern int totalCost;
extern int previousReservedCount;
extern char col[10];
extern int row[10];
extern int Cost;

void showMovieInfo(const string& movieName, int time);
int getSeatPrice(int time);
void seatPrint();
void pressEnter();
void seatSelect(int& people_count, int time, const string& movieName);
void cancelSeat(int& people_count, bool bookingComplete);
void manageBooking(int& people_count, int time, const string& movieName, bool& bookingComplete);
void processPayment(const string& name,int month, int day,int time, const string& movieName, int people_count);
void startBookingProcess(string name ,int& people_count, int month, int day, int time, const string& movieName);
//void askForRestart(int& people_count, bool& bookingComplete, int time, const string& movieName);

#define screenclear() system("cls")  // Windows 환경에서 화면 초기화 함수

void saveBookingDetailsToFile(const string& name, const string& movieName, int month, int day, int time, int people_count);
void savePaidSeatsToFile(const string& movieName, int month, int day,int time);
void loadPaidSeatsFromFile(const string& movieName, int month, int day, int time);
void resetAllSeats();
