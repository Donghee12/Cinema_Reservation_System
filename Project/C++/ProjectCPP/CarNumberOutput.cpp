#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

// ������� �̸����� �����ϴ� ������ �����ϴ��� Ȯ���ϴ� �Լ�
bool checkUserFileExists(const string& name) {
    string searchPattern = name + "_*"; // ��: "rla_*"
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(searchPattern.c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        FindClose(hFind);
        return true; // ���� ����
    }
    return false; // ���� ����
}

void CarNumberOutput()
{
    string name;
    cout << "����� ���̵� �Է��ϼ���: ";
    cin >> name;

    if (!checkUserFileExists(name)) {
        cout << "����� " << name << "�� ���� ������ �����ϴ�.\n";
        cout << "���� ����ڰ� �ƴϹǷ� 30�� ���� �����Դϴ�." << endl;
        return;
    }

    ifstream inFile("car_numbers.txt"); // ���� ����
    if (inFile.is_open()) // ������ ���������� ���ȴٸ�
    {
        string line;
        bool found = false;

        while (getline(inFile, line)) // ���Ͽ��� �� �پ� �б�
        {
            // �̸��� ������ȣ�� �����Ͽ� ����ϱ� ���� ������ �������� �и�
            size_t spacePos = line.find(" "); // ù ��° ���� ��ġ ã��
            if (spacePos != string::npos) {
                string userName = line.substr(0, spacePos); // ���� �� �κ��� �̸�
                string carNumber = line.substr(spacePos + 1); // ���� ���� �κ��� ���� ��ȣ

                // �̸��� ��ġ�ϸ� �ش� ���� ��ȣ�� ���
                if (userName == name) {
                    cout << name << "���� ���� ��ȣ: " << carNumber << endl;
                    cout << "3�ð� ���� �����մϴ�." << endl;
                    found = true;
                    break; // �ش� �̸��� ã���� �� �̻� ������ ���� �ʿ� ����
                }
            }
        }

        if (!found) {
            cout << name << "���� ���� ��ȣ�� ������� �ʾҽ��ϴ�.\n";
        }

        inFile.close(); // ���� �ݱ�
    }
    else {
        cout << "������ �� �� �����ϴ�!" << endl; // ���� ���� ����
    }
}
