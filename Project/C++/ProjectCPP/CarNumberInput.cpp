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

        // �ڷΰ��� ��ư ��ġ (8 �Ʒ���)
        if (x >= 120 && x < 180 && y >= 180 && y < 240)
        {
            backspace_clicked = true;
        }

        // A ��ư Ŭ�� (��ü �����)
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
            // ���� ���� ����� (������ ���� ���� �������)
            ofstream outFile("car_numbers.txt");
            if (outFile.is_open())
            {
                outFile.close(); // ������ ���� �ٷ� ������ ������ �����
                cout << "������ȣ ���� ������ ���������ϴ�." << endl;
            }
            else
            {
                cout << "���� ���� ����" << endl;
            }
            input_number = ""; // �Էµ� ��ȣ�� �ʱ�ȭ
        }

        cout << "���� �Էµ� ������ȣ : " << input_number << endl;

        if (input_number.length() == 4)
        {
            cout << "4�ڸ� ������ȣ �Է� �Ϸ�: " << input_number << endl;

            ofstream outFile("car_numbers.txt", ios::app);
            if (outFile.is_open())
            {
                outFile << nickname << " " << input_number << endl;
                outFile.close();
                cout << "������ȣ ���� �Ϸ�" << endl;
            }
            else
            {
                cout << "���� ���� ����" << endl;
            }

            destroyAllWindows();
        }
    }
}

void CarNumberInput()
{
    // �г��� �Է� �ޱ�
    cout << "����� ���̵� �Է��ϼ���: ";
    getline(cin, nickname);

    input_number = "";
    Mat img = Mat::zeros(310, 240, CV_8UC3); // ���̸� �÷���

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

    // �ڷΰ��� ��ư �߰� (8 �Ʒ���)
    int startX = 120; int startY = 180;
    rectangle(img, Point(startX, startY), Point(startX + 60, startY + 60), Scalar(255, 255, 255), 1);
    putText(img, "D", Point(startX + 20, startY + 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);

    // ��ü ����� ��ư �߰� (A)
    int startX1 = 60; int startY1 = 180;
    rectangle(img, Point(startX1, startY1), Point(startX1 + 60, startY1 + 60), Scalar(255, 255, 255), 1);
    putText(img, "A", Point(startX1 + 20, startY1 + 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);

    imshow("Num", img);
    setMouseCallback("Num", onMouse, NULL);
    waitKey(0);
}
