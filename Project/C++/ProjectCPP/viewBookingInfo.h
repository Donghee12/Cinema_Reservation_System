#pragma once
#ifndef VIEW_BOOKING_INFO_H
#define VIEW_BOOKING_INFO_H

#include <string>
#include <vector>

// ���� ������ �ҷ����� �Լ� ����
std::vector<std::string> loadBookingFiles(const std::string& name);

// ���� ������ �����ϰ� �����ִ� �Լ� ����
void chooseBookingFile();

#endif // VIEW_BOOKING_INFO_H
