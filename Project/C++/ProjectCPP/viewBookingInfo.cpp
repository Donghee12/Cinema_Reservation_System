#include "viewBookingInfo.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <cwctype>
#include <algorithm>    // remove_if

// 예약자 이름에 해당하는 파일을 검색하는 함수 정의

std::vector<std::string> loadBookingFiles(const std::string& name) {
    std::vector<std::string> files;
    std::wstring wname(name.begin(), name.end());
    wname.erase(std::remove_if(wname.begin(), wname.end(), ::iswspace), wname.end());

    // 올바른 방식으로 현재 경로를 얻기
    wchar_t currentDir[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, currentDir);
    std::wstring currentPath(currentDir);
    std::wstring searchPattern = currentPath + L"\\*";

    std::wcout << L"[DEBUG] searchPattern: " << searchPattern << std::endl;

    WIN32_FIND_DATAW findFileData;
    HANDLE hFind = FindFirstFileW(searchPattern.c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cout << "디렉토리 검색 실패\n";
        return files;
    }

    do {
        std::wstring wFilename = findFileData.cFileName;
        std::wstring wFilenameLower = wFilename;
        std::transform(wFilenameLower.begin(), wFilenameLower.end(), wFilenameLower.begin(), ::towlower);

        std::wstring wnameLower = wname;
        std::transform(wnameLower.begin(), wnameLower.end(), wnameLower.begin(), ::towlower);

        if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
            if (wFilenameLower.find(wnameLower) != std::wstring::npos &&
                wFilenameLower.substr(wFilenameLower.find_last_of(L'.') + 1) == L"txt") {

                std::wstring fullPath = currentPath + L"\\" + wFilename;

                int size_needed = WideCharToMultiByte(CP_UTF8, 0, fullPath.c_str(), -1, nullptr, 0, nullptr, nullptr);
                std::vector<char> strTo(size_needed);
                WideCharToMultiByte(CP_UTF8, 0, fullPath.c_str(), -1, strTo.data(), size_needed, nullptr, nullptr);

                files.push_back(std::string(strTo.data()));
            }
        }

    } while (FindNextFileW(hFind, &findFileData) != 0);

    FindClose(hFind);
    return files;
}

void chooseBookingFile() {
    SetConsoleCP(949);  // 입력 코드 페이지를 CP949로 설정
    SetConsoleOutputCP(949);  // 출력 코드 페이지를 CP949로 설정

    std::string name;
    std::cout << "예약 아이디를 입력하세요: ";

    // 기존 std::cin >> name을 std::getline(std::cin, name)로 변경하여 공백 포함 입력 받기
    std::getline(std::cin, name);

    // 추가적으로 cin.ignore()를 사용하여 남아있는 개행 문자 처리 (필요한 경우)
    // std::cin.ignore(); // 만약 std::cin >>를 사용한 후 이 함수가 호출될 경우에만 필요합니다.

    std::vector<std::string> files = loadBookingFiles(name);

    if (files.empty()) {
        std::cout << "해당 아이디로 예약된 정보가 없습니다.\n";
        return;
    }

    std::cout << "예약 정보 파일 목록:\n";
    for (int i = 0; i < files.size(); ++i) {
        std::string fileName = files[i];

        // 파일 이름에서 .txt 확장자를 제거
        size_t pos = fileName.find(".txt");
        if (pos != std::string::npos) {
            fileName = fileName.substr(0, pos);  // .txt를 제거한 부분만 남기기
        }

        std::cout << i + 1 << ". " << fileName << std::endl;
    }

    int choice;
    std::cout << "선택할 파일 번호를 입력하세요: ";
    std::cin >> choice;

    if (choice < 1 || choice > files.size()) {
        std::cout << "잘못된 선택입니다.\n";
        return;
    }

    std::string selectedFile = files[choice - 1];
    std::ifstream inFile(selectedFile);

    if (!inFile) {
        std::cout << "파일을 열 수 없습니다.\n";
        return;
    }

    std::string line;
    while (getline(inFile, line)) {
        std::cout << line << std::endl;  // 예약 정보 출력
    }

    inFile.close();
}
