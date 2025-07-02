#include "seat.h"
#include <fstream>


vector<vector<bool>> seats(COLS, vector<bool>(ROWS, false)); // �¼� ���� (false: �� �¼�, true: �����)
vector<string> reserved_seats; // ����� �¼� ������ ������ ����
vector<string>paid_reserved_seats;
// ���� �Ϸ� �� ����� �¼��� �����ϴ� ���� �߰�
// ���� �Ϸ�� �¼� ������ ����

#define screenclear() system("cls")  // Windows ȯ�濡�� ȭ�� �ʱ�ȭ �Լ�

int balance = 100000;  // �ʱ� �ܾ� 10����
const int seat_price = 10000;  // �⺻ �¼� ���� 1����
int totalCost = 0;
int previousReservedCount = 0;
int Cost = 0;

char col[10];
int row[10];

void resetcolrow(char a[], int b[]) {
    for (int i = 0;i < 10; i++) {
        a[i] = 0;
        b[i] = 0;
    }
}

void makecolrow(char a[], int b[], vector<string> c)
{
    for (int i = 0;i < c.size();i++) {
        a[i] = c[i][0];
        b[i] = c[i][1]- '0';
    }
}

// ��ȭ �� �ð��� ǥ�� �Լ�
void showMovieInfo(const string& movieName, int time) {
    string timePeriod;

    // �� �ð��� ����
    if (time >= 6 && time <= 10) {
        timePeriod = "��� (6:00~10:00)";
    }
    else if (time >= 10 && time <= 13) {
        timePeriod = "�귱ġ (10:01~13:00)";
    }
    else {
        timePeriod = "�Ϲ� (13:01~)";
    }

    // ��ȭ ���� ���
    cout << "��ȭ: " << movieName << "\n";
    cout << "�� �ð���: " << timePeriod << endl;
}

// �ð��뿡 ���� ���� �Լ�
int getSeatPrice(int time) {
    if (time >= 6 && time <= 10) {
        return 10000;  // ���
    }
    else if (time >= 10 && time <= 13) {
        return 13000;  // �귱ġ
    }
    else {
        return 14000;  // �Ϲ�
    }
}

// �¼� ���� ��� �Լ�
void seatPrint() {
    cout << "  1 2 3 4 5 6 7 8 9\n"; // �� ��ȣ ǥ��
    for (int i = 0; i < COLS; i++) {
        cout << char('A' + i) << " ";  // �� �̸� (A~J)
        for (int j = 0; j < ROWS; j++) {
            cout << (seats[i][j] ? "�� " : "�� ");  // ����� �¼��� ��, �� �¼��� ��
        }
        cout << endl;
    }
}

// ����Ű�� ��ٸ��� �Լ�
void pressEnter() {
    cout << "\n����Ű�� ���� ��� �����Ͻʽÿ�...";
    cin.ignore();  // ���� �Է� ���۸� ����ݴϴ�.
    cin.get();  // ����ڰ� ����Ű�� ���� ������ ����մϴ�.
}

// �¼� ���� �Լ� (����)
void seatSelect(int& people_count, int time, const string& movieName) {
    int col;
    char row;

    if (people_count <= 0) {
        cout << "���� ������ �ο��� �����ϴ�.\n";
        return;
    }

    while (people_count > 0) {
        screenclear();
        seatPrint();

        cout << "������ �¼��� �Է��ϼ��� (��: A3): ";
        cin >> row >> col;

        if (cin.fail()) {
            cin.clear();  // ���� �÷��� �ʱ�ȭ
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �߸��� �Է� ����
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n";
            pressEnter();
            continue;
        }

        if (row < 'A' || row > 'J' || col < 1 || col > 9) {
            cout << "�߸��� �¼��Դϴ�. �ٽ� �Է��ϼ���.\n";
            pressEnter();
            continue;
        }

        int rowIndex = row - 'A';
        int colIndex = col - 1;

        if (seats[rowIndex][colIndex]) {
            cout << "�̹� ����� �¼��Դϴ�. �ٸ� �¼��� �����ϼ���.\n";
            pressEnter();
        }
        else {
            char confirm;
            cout << "�¼� " << row << col << " �����Ͻðڽ��ϱ�? (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y') {
                seats[rowIndex][colIndex] = true;
                reserved_seats.push_back(string(1, row) + to_string(col));
                people_count--;

                cout << "�¼� " << row << col << " ���� �Ϸ�! ���� ���� �ο�: " << people_count << endl;
                pressEnter();
                break;  // ���� �� �ٽ� �޴��� ���ư���
            }
            else {
                cout << "�¼� ������ ����ϼ̽��ϴ�.\n";
            }
        }
    }
}

// �¼� ��� �Լ�
void cancelSeat(int& people_count, bool bookingComplete) {
    if (reserved_seats.empty()) {
        cout << "����� ����� �¼��� �����ϴ�.\n";
        pressEnter();
        return;
    }
    if (bookingComplete) {
        cout << "���� �Ϸ� �Ŀ��� ���� ����� �¼��� ����� �� �����ϴ�.\n";
        pressEnter();
        return;
    }

    string cancelSeat;
    cout << "����� �¼��� �Է��ϼ��� (��: A3): ";
    cin >> cancelSeat;
    try {
        char row = cancelSeat[0];
        int col = stoi(cancelSeat.substr(1));

        if (find(paid_reserved_seats.begin(), paid_reserved_seats.end(), cancelSeat) != paid_reserved_seats.end()) {
            cout << "�̹� ������ �¼��� ����� �� �����ϴ�.\n";
            pressEnter();
            return;
        }
        auto it = find(reserved_seats.begin(), reserved_seats.end(), cancelSeat);
        if (it != reserved_seats.end()) {
            reserved_seats.erase(it);
            seats[row - 'A'][col - 1] = false;
            people_count++;
            cout << "�¼� " << cancelSeat << " ���� ��� �Ϸ�!\n";
            pressEnter();

        }
        else {
            cout << "�ش� �¼��� ������� �ʾҽ��ϴ�.\n";
        }
    }
    catch (...) {
        cout << "�߸��� �Է� �����Դϴ�. �ٽ� �Է��ϼ���.\n";
    }
}

// ����/��Ҹ� �����ϴ� �Լ�
void manageBooking(int& people_count, int time, const string& movieName, bool& bookingComplete) {
    while (people_count > 0) {
        screenclear();

        // ��ȭ ���� ǥ��
        showMovieInfo(movieName, time);

        seatPrint();
        cout << "\n���� �ܾ�: " << balance << "��\n";

        char choice;
        cout << "\n���� ������ �¼� ��: " << people_count << endl;
        cout << "[R] �¼� ����  |  [C] �¼� ���  |  [E] ����\n";
        cout << "����: ";
        cin >> choice;

        if (choice == 'R' || choice == 'r') {
            seatSelect(people_count, time, movieName);
        }
        else if (choice == 'C' || choice == 'c') {
            cancelSeat(people_count, bookingComplete);
        }
        else if (choice == 'E' || choice == 'e') {
            if (people_count == 0) {
                bookingComplete = true;  // ������ �Ϸ�Ǿ����� true
                cout << "������ �Ϸ�Ǿ����ϴ�. ��ȭ ���Ÿ� �����մϴ�.\n";
                break;  // ���� ���� �� ���� ����
            }
            else {
                cout << "������ �ο��� ���� �ֽ��ϴ�. ���Ÿ� �Ϸ��� �� ������ �� �ֽ��ϴ�.\n";
                pressEnter();
            }
        }
        else {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �����ϼ���.\n";
            pressEnter();
        }
    }

    // ����� �¼� �� ����
    if (people_count == 0) {
        cout << "�� �̻� ������ �� �ִ� �¼��� �����ϴ�.\n";
        bookingComplete = true;  // ���� �Ϸ� �� ����
    }
}


// ���� ó�� �Լ� ���� (���� �� �ٽ� ���� ����)
void processPayment(const string& name,int month, int day,int time, const string& movieName, int people_count) {
    int additionalSeats = reserved_seats.size() - previousReservedCount;  // ���� ������ �¼� ��

    totalCost = 0;

    // ����� �¼��鿡 ���� ���� ���
    for (int i = previousReservedCount; i < reserved_seats.size(); i++) {
        totalCost += getSeatPrice(time);  // ����: 8�� ��ȭ (���)
    }


    cout << "\n�¼� ������ �Ϸ�Ǿ����ϴ�! ������ �����Ͻðڽ��ϱ�? (Y/N): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        cout << "�� ���� �ݾ�: " << totalCost << "��\n";

        if (balance >= totalCost) {
            balance -= totalCost;
            cout << "������ �Ϸ�Ǿ����ϴ�! �ܾ�: " << balance << "��\n";
            Cost = totalCost;
            totalCost = 0;
        
            previousReservedCount = reserved_seats.size();  // ���� �� ����� �¼� �� ����
            paid_reserved_seats.insert(paid_reserved_seats.end(), reserved_seats.begin(), reserved_seats.end());
            makecolrow(col, row, paid_reserved_seats);

            savePaidSeatsToFile(movieName,month, day ,time);  // ������ �¼��� ���Ͽ� ����
            people_count += reserved_seats.size();
            saveBookingDetailsToFile(name,movieName,month,day,time,people_count);
            resetAllSeats();
        }
        else {
            cout << "�ܾ��� �����Ͽ� ������ �� �����ϴ�.\n";
        }
    }
    else {
        cout << "������ ����ϼ̽��ϴ�.\n";
        for (const string& seat : reserved_seats) {
            char row = seat[0];
            int col = stoi(seat.substr(1)) - 1;

            int rowIndex = row - 'A';
            int colIndex = col;

            seats[rowIndex][colIndex] = false;  // �¼��� �ٽ� �� �¼����� ����
        }

        reserved_seats.clear();  // ���� ����Ʈ �ʱ�ȭ
    }
}

// �¼� ���� �� ���� ���� �Լ� ���� (���� �� �翹�� ����)
void startBookingProcess(string name, int& people_count,int month, int day, int time, const string& movieName) {
    bool bookingComplete = false;  // ���� �Ϸ� ���� Ȯ��
    previousReservedCount = reserved_seats.size();  // ���� ����� �¼� �� �ʱ�ȭ
    Cost = 0;
    resetcolrow(col, row);

    loadPaidSeatsFromFile(movieName, month, day, time);  // ���� ���� �� �¼� ���� �ҷ�����


    // �¼� ���� �� ���� ����
    while (!bookingComplete) {
        manageBooking(people_count, time, movieName, bookingComplete);  // ���� ����
        // ������ �Ϸ�Ǹ�
        if (bookingComplete) {

            cout << "�¼� ���Ű� �Ϸ�Ǿ����ϴ�!\n";
            processPayment(name, month, day, time,movieName,people_count);  // ���� ó��

         
            break;
        }
    }
}

// �¼� ������ ���Ͽ��� �ҷ��ͼ� ���� �¼� �迭�� �ݿ��ϴ� �Լ�
void loadPaidSeatsFromFile(const string& movieName, int month, int day, int time) {
    ifstream inFile(movieName + "_" + to_string(month) + "��_" + to_string(day) + "��_" + to_string(time) + "��_seats.txt");

    if (!inFile) {
        cout << "������ �� �� �����ϴ�.\n";
        return;
    }

    string seat;
    while (getline(inFile, seat)) {
        // �¼� ������ "A3" ���·� ���� ���
        char row = seat[0];  // �� (A~J)
        int col = stoi(seat.substr(1)) - 1;  // �� (1~9)

        // �¼� ��ġ�� ���� �¼� �迭�� �ݿ�
        int rowIndex = row - 'A';  // �� �ε���
        seats[rowIndex][col] = true;  // �ش� �¼��� �����(true) ���·� ����


    }

    inFile.close();
}

// �¼� ������ ���Ͽ� �����ϴ� �Լ�
void savePaidSeatsToFile(const string& movieName, int month, int day,int time) {
    ofstream outFile(movieName + "_" + to_string(month) + "��_" + to_string(day) + "��_" + to_string(time) + "��_seats.txt", ios::app);

    if (!outFile) {
        cout << "������ �� �� �����ϴ�.\n";
        return;
    }

    // paid_reserved_seats�� ����� �¼� ������ ���Ͽ� ���
    for (const string& seat : paid_reserved_seats) {
        outFile << seat << endl;
    }

    outFile.close();
}

void resetAllSeats() {
    // ��� �¼� �迭 �ʱ�ȭ
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            seats[i][j] = false;  // ��� �¼��� �� ���·� ����
        }
    }

    // ����� �¼� ���� �ʱ�ȭ
    reserved_seats.clear();
    paid_reserved_seats.clear();  // ���� �Ϸ�� �¼� ������ �ʱ�ȭ
    cout << "��� �¼� ������ �ʱ�ȭ�Ǿ����ϴ�.\n";
}

void saveBookingDetailsToFile(const string& name, const string& movieName, int month, int day, int time, int people_count) {
    // ���� �̸� ���� (��: ��ȭ�̸�_2025-02-18_15��_4��.txt)
    string fileName = name+"_"+movieName + "_" + to_string(month) + "��_" + to_string(day) + "��_" + to_string(time) + "��_" + to_string(people_count)+"��" + ".txt";

    ofstream outFile(fileName);

    if (!outFile) {
        cout << "������ �� �� �����ϴ�.\n";
        return;
    }

    // ���Ͽ� ���� ���� ���
    outFile << "������: " << name << endl;
    outFile << "��ȭ: " << movieName << endl;
    outFile << "�� ��¥: " << month << "�� " << day << "��" << endl;
    outFile << "�� �ð�: " << time << "��" << endl;
    outFile << "���� �ο�: " << people_count << "��" << endl;

    // �¼� ���� ���
    outFile << "����� �¼�: ";
    for (const string& seat : reserved_seats) {
        outFile << seat << " ";  // ����� �¼� ���
    }
    outFile << endl;

    outFile.close();
    cout << "���� ������ " << fileName << " ���Ͽ� ����Ǿ����ϴ�.\n";
}