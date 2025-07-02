#pragma once
#ifndef VIEW_BOOKING_INFO_H
#define VIEW_BOOKING_INFO_H

#include <string>
#include <vector>

// 예약 파일을 불러오는 함수 선언
std::vector<std::string> loadBookingFiles(const std::string& name);

// 예약 파일을 선택하고 보여주는 함수 선언
void chooseBookingFile();

#endif // VIEW_BOOKING_INFO_H
