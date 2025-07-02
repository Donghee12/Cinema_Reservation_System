#include "CarNumberInput.h"
using namespace cv;
using namespace std;

string input_number = "";
string nickname = "";

void onMouse(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        int clicked_number = -1;
        bool backspace_clicked = false;
        bool clear_file_clicked = false;

        for (int i = 0; i < 10; ++i)
        {
            int row = i / 3;
            int col = i % 3;
            int startX = col * 60;
            int startY = row * 60;

            if (x >= startX && x < startX + 60 && y >= startY && y < startY + 60)
            {
                clicked_number = i + 1;
                if (clicked_number == 10) clicked_number = 0;
                break;
            }
        }

        // 뒤로가기 버튼 위치 (8 아래로)
        if (x >= 120 && x < 180 && y >= 180 && y < 240)
        {
            backspace_clicked = true;
        }

        // A 버튼 클릭 (전체 지우기)
        if (x >= 60 && x < 120 && y >= 180 && y < 240)
        {
            clear_file_clicked = true;
        }

        if (clicked_number != -1)
        {
            input_number += to_string(clicked_number);
        }
        else if (backspace_clicked && !input_number.empty())
        {
            input_number.pop_back();
        }
        else if (clear_file_clicked)
        {
            // 파일 내용 지우기 (파일을 새로 열면 덮어쓰여짐)
            ofstream outFile("car_numbers.txt");
            if (outFile.is_open())
            {
                outFile.close(); // 파일을 열고 바로 닫으면 내용이 비워짐
                cout << "차량번호 파일 내용이 지워졌습니다." << endl;
            }
            else
            {
                cout << "파일 열기 실패" << endl;
            }
            input_number = ""; // 입력된 번호도 초기화
        }

        cout << "현재 입력된 차량번호 : " << input_number << endl;

        if (input_number.length() == 4)
        {
            cout << "4자리 차량번호 입력 완료: " << input_number << endl;

            ofstream outFile("car_numbers.txt", ios::app);
            if (outFile.is_open())
            {
                outFile << nickname << " " << input_number << endl;
                outFile.close();
                cout << "차량번호 저장 완료" << endl;
            }
            else
            {
                cout << "파일 열기 실패" << endl;
            }

            destroyAllWindows();
        }
    }
}

void CarNumberInput()
{
    // 닉네임 입력 받기
    cout << "사용자 아이디를 입력하세요: ";
    getline(cin, nickname);

    input_number = "";
    Mat img = Mat::zeros(310, 240, CV_8UC3); // 높이를 늘려줌

    for (int i = 0; i < 10; ++i)
    {
        int row = i / 3;
        int col = i % 3;
        int startX = col * 60;
        int startY = row * 60;
        rectangle(img, Point(startX, startY), Point(startX + 60, startY + 60), Scalar(255, 255, 255), 1);
        string number_text = to_string(i + 1);
        if (i == 9) number_text = "0";
        putText(img, number_text, Point(startX + 20, startY + 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
    }

    // 뒤로가기 버튼 추가 (8 아래로)
    int startX = 120; int startY = 180;
    rectangle(img, Point(startX, startY), Point(startX + 60, startY + 60), Scalar(255, 255, 255), 1);
    putText(img, "D", Point(startX + 20, startY + 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);

    // 전체 지우기 버튼 추가 (A)
    int startX1 = 60; int startY1 = 180;
    rectangle(img, Point(startX1, startY1), Point(startX1 + 60, startY1 + 60), Scalar(255, 255, 255), 1);
    putText(img, "A", Point(startX1 + 20, startY1 + 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);

    imshow("Num", img);
    setMouseCallback("Num", onMouse, NULL);
    waitKey(0);
}
