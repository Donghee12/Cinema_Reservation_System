#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

// 사용자의 이름으로 시작하는 파일이 존재하는지 확인하는 함수
bool checkUserFileExists(const string& name) {
    string searchPattern = name + "_*"; // 예: "rla_*"
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(searchPattern.c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        FindClose(hFind);
        return true; // 파일 존재
    }
    return false; // 파일 없음
}

void CarNumberOutput()
{
    string name;
    cout << "사용자 아이디를 입력하세요: ";
    cin >> name;

    if (!checkUserFileExists(name)) {
        cout << "사용자 " << name << "의 예약 파일이 없습니다.\n";
        cout << "예약 사용자가 아니므로 30분 무료 주차입니다." << endl;
        return;
    }

    ifstream inFile("car_numbers.txt"); // 파일 열기
    if (inFile.is_open()) // 파일이 정상적으로 열렸다면
    {
        string line;
        bool found = false;

        while (getline(inFile, line)) // 파일에서 한 줄씩 읽기
        {
            // 이름과 차량번호를 구분하여 출력하기 위해 공백을 기준으로 분리
            size_t spacePos = line.find(" "); // 첫 번째 공백 위치 찾기
            if (spacePos != string::npos) {
                string userName = line.substr(0, spacePos); // 공백 전 부분이 이름
                string carNumber = line.substr(spacePos + 1); // 공백 이후 부분이 차량 번호

                // 이름이 일치하면 해당 차량 번호를 출력
                if (userName == name) {
                    cout << name << "님의 차량 번호: " << carNumber << endl;
                    cout << "3시간 주차 가능합니다." << endl;
                    found = true;
                    break; // 해당 이름을 찾으면 더 이상 파일을 읽을 필요 없음
                }
            }
        }

        if (!found) {
            cout << name << "님의 차량 번호가 저장되지 않았습니다.\n";
        }

        inFile.close(); // 파일 닫기
    }
    else {
        cout << "파일을 열 수 없습니다!" << endl; // 파일 열기 실패
    }
}
