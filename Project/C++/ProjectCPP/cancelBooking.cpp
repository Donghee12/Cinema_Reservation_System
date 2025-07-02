#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <sstream>

// 예약자 이름에 해당하는 파일을 검색하는 함수
std::vector<std::string> findBookingFiles(const std::string& name) {
    std::vector<std::string> files;

    // 입력된 이름을 소문자 wstring으로 변환
    std::wstring wname(name.begin(), name.end());
    std::transform(wname.begin(), wname.end(), wname.begin(), ::towlower);

    wchar_t currentDir[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, currentDir);
    std::wstring currentPath(currentDir);
    std::wstring searchPattern = currentPath + L"\\*";

    WIN32_FIND_DATAW findFileData;
    HANDLE hFind = FindFirstFileW(searchPattern.c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) return files;

    do {
        std::wstring wFilename = findFileData.cFileName;

        if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
            std::wstring wFilenameLower = wFilename;
            std::transform(wFilenameLower.begin(), wFilenameLower.end(), wFilenameLower.begin(), ::towlower);

            if (wFilenameLower.find(wname) != std::wstring::npos &&
                wFilenameLower.substr(wFilenameLower.find_last_of(L'.') + 1) == L"txt") {

                int size_needed = WideCharToMultiByte(CP_ACP, 0, wFilename.c_str(), -1, nullptr, 0, nullptr, nullptr);
                std::vector<char> strTo(size_needed);
                WideCharToMultiByte(CP_ACP, 0, wFilename.c_str(), -1, strTo.data(), size_needed, nullptr, nullptr);

                files.push_back(std::string(strTo.data()));
            }
        }
    } while (FindNextFileW(hFind, &findFileData) != 0);

    FindClose(hFind);
    return files;
}


// 파일에서 예약된 좌석을 읽어오는 함수
std::vector<std::string> readSeatsFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    std::vector<std::string> seats;
    std::string line;

    while (std::getline(inFile, line)) {
        if (line.find("예약된 좌석:") != std::string::npos) {
            size_t pos = line.find(":") + 2;
            std::string seatStr = line.substr(pos);
            std::istringstream ss(seatStr);
            std::string seat;
            while (ss >> seat) seats.push_back(seat);
        }
    }

    return seats;
}

// 좌석 파일에서 특정 좌석을 삭제하는 함수
void removeSeatsFromFile(const std::string& seatFilename, const std::vector<std::string>& seatsToRemove) {
    std::ifstream inFile(seatFilename);
    if (!inFile) return;

    std::vector<std::string> seats;
    std::string seat;
    while (inFile >> seat) {
        if (std::find(seatsToRemove.begin(), seatsToRemove.end(), seat) == seatsToRemove.end()) {
            seats.push_back(seat);
        }
    }
    inFile.close();

    std::ofstream outFile(seatFilename, std::ios::trunc);
    for (const auto& s : seats) {
        outFile << s << std::endl;
    }
}

// 예매 취소 함수
void cancelBooking() {
    std::string name;
    std::cout << "예약 아이디를 입력하세요: ";
    std::cin >> name;

    std::vector<std::string> files = findBookingFiles(name);
    if (files.empty()) {
        std::cout << "해당 아이디로 된 예약이 없습니다.\n";
        return;
    }

    std::cout << "예약 목록:\n";
    for (size_t i = 0; i < files.size(); ++i) {
        std::cout << i + 1 << ". " << files[i] << std::endl;
    }

    int choice;
    std::cout << "취소할 예약 번호를 입력하세요: ";
    std::cin >> choice;
    if (choice < 1 || choice > files.size()) {
        std::cout << "잘못된 선택입니다.\n";
        return;
    }

    std::string bookingFile = files[choice - 1];

    // 📌 새로운 파일명 형식에 맞춰 좌석 파일 이름을 추출
    size_t firstUnderscore = bookingFile.find("_");
    if (firstUnderscore == std::string::npos) {
        std::cout << "파일 이름 분석 오류.\n";
        return;
    }

    // `name_` 이후 부분 추출 (영화 정보)
    std::string movieInfo = bookingFile.substr(firstUnderscore + 1);

    // `_peoplecount명.txt` 제거하기
    size_t peoplePos = movieInfo.find_last_of("_");
    if (peoplePos == std::string::npos) {
        std::cout << "파일 이름 분석 오류.\n";
        return;
    }
    movieInfo = movieInfo.substr(0, peoplePos); // 마지막 `_peoplecount명` 부분 제거

    // 좌석 파일 이름 구성
    std::string seatFile = movieInfo + "_seats.txt";

    // 예약된 좌석 읽기
    std::vector<std::string> reservedSeats = readSeatsFromFile(bookingFile);

    // 좌석 파일에서 해당 좌석 삭제
    removeSeatsFromFile(seatFile, reservedSeats);

    // 예매 정보 파일 삭제
    if (remove(bookingFile.c_str()) == 0) {
        std::cout << "예약이 취소되었습니다.\n";
    }
    else {
        std::cout << "파일 삭제 실패.\n";
    }
}

