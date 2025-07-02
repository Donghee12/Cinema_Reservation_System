#include "viewBookingInfo.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <cwctype>
#include <algorithm>    // remove_if

// ������ �̸��� �ش��ϴ� ������ �˻��ϴ� �Լ� ����

std::vector<std::string> loadBookingFiles(const std::string& name) {
    std::vector<std::string> files;
    std::wstring wname(name.begin(), name.end());
    wname.erase(std::remove_if(wname.begin(), wname.end(), ::iswspace), wname.end());

    // �ùٸ� ������� ���� ��θ� ���
    wchar_t currentDir[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, currentDir);
    std::wstring currentPath(currentDir);
    std::wstring searchPattern = currentPath + L"\\*";

    std::wcout << L"[DEBUG] searchPattern: " << searchPattern << std::endl;

    WIN32_FIND_DATAW findFileData;
    HANDLE hFind = FindFirstFileW(searchPattern.c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cout << "���丮 �˻� ����\n";
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
    SetConsoleCP(949);  // �Է� �ڵ� �������� CP949�� ����
    SetConsoleOutputCP(949);  // ��� �ڵ� �������� CP949�� ����

    std::string name;
    std::cout << "���� ���̵� �Է��ϼ���: ";

    // ���� std::cin >> name�� std::getline(std::cin, name)�� �����Ͽ� ���� ���� �Է� �ޱ�
    std::getline(std::cin, name);

    // �߰������� cin.ignore()�� ����Ͽ� �����ִ� ���� ���� ó�� (�ʿ��� ���)
    // std::cin.ignore(); // ���� std::cin >>�� ����� �� �� �Լ��� ȣ��� ��쿡�� �ʿ��մϴ�.

    std::vector<std::string> files = loadBookingFiles(name);

    if (files.empty()) {
        std::cout << "�ش� ���̵�� ����� ������ �����ϴ�.\n";
        return;
    }

    std::cout << "���� ���� ���� ���:\n";
    for (int i = 0; i < files.size(); ++i) {
        std::string fileName = files[i];

        // ���� �̸����� .txt Ȯ���ڸ� ����
        size_t pos = fileName.find(".txt");
        if (pos != std::string::npos) {
            fileName = fileName.substr(0, pos);  // .txt�� ������ �κи� �����
        }

        std::cout << i + 1 << ". " << fileName << std::endl;
    }

    int choice;
    std::cout << "������ ���� ��ȣ�� �Է��ϼ���: ";
    std::cin >> choice;

    if (choice < 1 || choice > files.size()) {
        std::cout << "�߸��� �����Դϴ�.\n";
        return;
    }

    std::string selectedFile = files[choice - 1];
    std::ifstream inFile(selectedFile);

    if (!inFile) {
        std::cout << "������ �� �� �����ϴ�.\n";
        return;
    }

    std::string line;
    while (getline(inFile, line)) {
        std::cout << line << std::endl;  // ���� ���� ���
    }

    inFile.close();
}
