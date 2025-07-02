#include "seat.h"
#include <fstream>


vector<vector<bool>> seats(COLS, vector<bool>(ROWS, false)); // 좌석 상태 (false: 빈 좌석, true: 예약됨)
vector<string> reserved_seats; // 예약된 좌석 정보를 저장할 벡터
vector<string>paid_reserved_seats;
// 결제 완료 후 예약된 좌석을 추적하는 벡터 추가
// 결제 완료된 좌석 정보를 저장

#define screenclear() system("cls")  // Windows 환경에서 화면 초기화 함수

int balance = 100000;  // 초기 잔액 10만원
const int seat_price = 10000;  // 기본 좌석 가격 1만원
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

// 영화 상영 시간대 표시 함수
void showMovieInfo(const string& movieName, int time) {
    string timePeriod;

    // 상영 시간대 구분
    if (time >= 6 && time <= 10) {
        timePeriod = "모닝 (6:00~10:00)";
    }
    else if (time >= 10 && time <= 13) {
        timePeriod = "브런치 (10:01~13:00)";
    }
    else {
        timePeriod = "일반 (13:01~)";
    }

    // 영화 정보 출력
    cout << "영화: " << movieName << "\n";
    cout << "상영 시간대: " << timePeriod << endl;
}

// 시간대에 따른 가격 함수
int getSeatPrice(int time) {
    if (time >= 6 && time <= 10) {
        return 10000;  // 모닝
    }
    else if (time >= 10 && time <= 13) {
        return 13000;  // 브런치
    }
    else {
        return 14000;  // 일반
    }
}

// 좌석 상태 출력 함수
void seatPrint() {
    cout << "  1 2 3 4 5 6 7 8 9\n"; // 열 번호 표시
    for (int i = 0; i < COLS; i++) {
        cout << char('A' + i) << " ";  // 행 이름 (A~J)
        for (int j = 0; j < ROWS; j++) {
            cout << (seats[i][j] ? "■ " : "□ ");  // 예약된 좌석은 ■, 빈 좌석은 □
        }
        cout << endl;
    }
}

// 엔터키를 기다리는 함수
void pressEnter() {
    cout << "\n엔터키를 눌러 계속 진행하십시오...";
    cin.ignore();  // 이전 입력 버퍼를 비워줍니다.
    cin.get();  // 사용자가 엔터키를 누를 때까지 대기합니다.
}

// 좌석 선택 함수 (예약)
void seatSelect(int& people_count, int time, const string& movieName) {
    int col;
    char row;

    if (people_count <= 0) {
        cout << "예매 가능한 인원이 없습니다.\n";
        return;
    }

    while (people_count > 0) {
        screenclear();
        seatPrint();

        cout << "예약할 좌석을 입력하세요 (예: A3): ";
        cin >> row >> col;

        if (cin.fail()) {
            cin.clear();  // 오류 플래그 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 잘못된 입력 무시
            cout << "잘못된 입력입니다. 다시 입력하세요.\n";
            pressEnter();
            continue;
        }

        if (row < 'A' || row > 'J' || col < 1 || col > 9) {
            cout << "잘못된 좌석입니다. 다시 입력하세요.\n";
            pressEnter();
            continue;
        }

        int rowIndex = row - 'A';
        int colIndex = col - 1;

        if (seats[rowIndex][colIndex]) {
            cout << "이미 예약된 좌석입니다. 다른 좌석을 선택하세요.\n";
            pressEnter();
        }
        else {
            char confirm;
            cout << "좌석 " << row << col << " 예약하시겠습니까? (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y') {
                seats[rowIndex][colIndex] = true;
                reserved_seats.push_back(string(1, row) + to_string(col));
                people_count--;

                cout << "좌석 " << row << col << " 예약 완료! 남은 예약 인원: " << people_count << endl;
                pressEnter();
                break;  // 예약 후 다시 메뉴로 돌아가기
            }
            else {
                cout << "좌석 예약을 취소하셨습니다.\n";
            }
        }
    }
}

// 좌석 취소 함수
void cancelSeat(int& people_count, bool bookingComplete) {
    if (reserved_seats.empty()) {
        cout << "취소할 예약된 좌석이 없습니다.\n";
        pressEnter();
        return;
    }
    if (bookingComplete) {
        cout << "결제 완료 후에는 이전 예약된 좌석을 취소할 수 없습니다.\n";
        pressEnter();
        return;
    }

    string cancelSeat;
    cout << "취소할 좌석을 입력하세요 (예: A3): ";
    cin >> cancelSeat;
    try {
        char row = cancelSeat[0];
        int col = stoi(cancelSeat.substr(1));

        if (find(paid_reserved_seats.begin(), paid_reserved_seats.end(), cancelSeat) != paid_reserved_seats.end()) {
            cout << "이미 결제된 좌석은 취소할 수 없습니다.\n";
            pressEnter();
            return;
        }
        auto it = find(reserved_seats.begin(), reserved_seats.end(), cancelSeat);
        if (it != reserved_seats.end()) {
            reserved_seats.erase(it);
            seats[row - 'A'][col - 1] = false;
            people_count++;
            cout << "좌석 " << cancelSeat << " 예약 취소 완료!\n";
            pressEnter();

        }
        else {
            cout << "해당 좌석이 예약되지 않았습니다.\n";
        }
    }
    catch (...) {
        cout << "잘못된 입력 형식입니다. 다시 입력하세요.\n";
    }
}

// 예약/취소를 선택하는 함수
void manageBooking(int& people_count, int time, const string& movieName, bool& bookingComplete) {
    while (people_count > 0) {
        screenclear();

        // 영화 정보 표시
        showMovieInfo(movieName, time);

        seatPrint();
        cout << "\n현재 잔액: " << balance << "원\n";

        char choice;
        cout << "\n현재 예매할 좌석 수: " << people_count << endl;
        cout << "[R] 좌석 예약  |  [C] 좌석 취소  |  [E] 종료\n";
        cout << "선택: ";
        cin >> choice;

        if (choice == 'R' || choice == 'r') {
            seatSelect(people_count, time, movieName);
        }
        else if (choice == 'C' || choice == 'c') {
            cancelSeat(people_count, bookingComplete);
        }
        else if (choice == 'E' || choice == 'e') {
            if (people_count == 0) {
                bookingComplete = true;  // 예약이 완료되었으면 true
                cout << "예약이 완료되었습니다. 영화 예매를 종료합니다.\n";
                break;  // 종료 선택 시 루프 종료
            }
            else {
                cout << "예매할 인원이 남아 있습니다. 예매를 완료한 후 종료할 수 있습니다.\n";
                pressEnter();
            }
        }
        else {
            cout << "잘못된 입력입니다. 다시 선택하세요.\n";
            pressEnter();
        }
    }

    // 예약된 좌석 수 갱신
    if (people_count == 0) {
        cout << "더 이상 예약할 수 있는 좌석이 없습니다.\n";
        bookingComplete = true;  // 예매 완료 후 종료
    }
}


// 결제 처리 함수 수정 (결제 후 다시 예매 진행)
void processPayment(const string& name,int month, int day,int time, const string& movieName, int people_count) {
    int additionalSeats = reserved_seats.size() - previousReservedCount;  // 새로 예약한 좌석 수

    totalCost = 0;

    // 예약된 좌석들에 대해 가격 계산
    for (int i = previousReservedCount; i < reserved_seats.size(); i++) {
        totalCost += getSeatPrice(time);  // 예시: 8시 영화 (모닝)
    }


    cout << "\n좌석 예약이 완료되었습니다! 결제를 진행하시겠습니까? (Y/N): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        cout << "총 결제 금액: " << totalCost << "원\n";

        if (balance >= totalCost) {
            balance -= totalCost;
            cout << "결제가 완료되었습니다! 잔액: " << balance << "원\n";
            Cost = totalCost;
            totalCost = 0;
        
            previousReservedCount = reserved_seats.size();  // 결제 후 예약된 좌석 수 갱신
            paid_reserved_seats.insert(paid_reserved_seats.end(), reserved_seats.begin(), reserved_seats.end());
            makecolrow(col, row, paid_reserved_seats);

            savePaidSeatsToFile(movieName,month, day ,time);  // 결제된 좌석을 파일에 저장
            people_count += reserved_seats.size();
            saveBookingDetailsToFile(name,movieName,month,day,time,people_count);
            resetAllSeats();
        }
        else {
            cout << "잔액이 부족하여 결제할 수 없습니다.\n";
        }
    }
    else {
        cout << "결제를 취소하셨습니다.\n";
        for (const string& seat : reserved_seats) {
            char row = seat[0];
            int col = stoi(seat.substr(1)) - 1;

            int rowIndex = row - 'A';
            int colIndex = col;

            seats[rowIndex][colIndex] = false;  // 좌석을 다시 빈 좌석으로 변경
        }

        reserved_seats.clear();  // 예약 리스트 초기화
    }
}

// 좌석 예매 및 결제 시작 함수 수정 (결제 후 재예약 진행)
void startBookingProcess(string name, int& people_count,int month, int day, int time, const string& movieName) {
    bool bookingComplete = false;  // 예약 완료 여부 확인
    previousReservedCount = reserved_seats.size();  // 이전 예약된 좌석 수 초기화
    Cost = 0;
    resetcolrow(col, row);

    loadPaidSeatsFromFile(movieName, month, day, time);  // 예매 시작 시 좌석 정보 불러오기


    // 좌석 예매 및 결제 진행
    while (!bookingComplete) {
        manageBooking(people_count, time, movieName, bookingComplete);  // 예약 관리
        // 예약이 완료되면
        if (bookingComplete) {

            cout << "좌석 예매가 완료되었습니다!\n";
            processPayment(name, month, day, time,movieName,people_count);  // 결제 처리

         
            break;
        }
    }
}

// 좌석 정보를 파일에서 불러와서 실제 좌석 배열에 반영하는 함수
void loadPaidSeatsFromFile(const string& movieName, int month, int day, int time) {
    ifstream inFile(movieName + "_" + to_string(month) + "월_" + to_string(day) + "일_" + to_string(time) + "시_seats.txt");

    if (!inFile) {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    string seat;
    while (getline(inFile, seat)) {
        // 좌석 정보가 "A3" 형태로 들어올 경우
        char row = seat[0];  // 행 (A~J)
        int col = stoi(seat.substr(1)) - 1;  // 열 (1~9)

        // 좌석 위치를 실제 좌석 배열에 반영
        int rowIndex = row - 'A';  // 행 인덱스
        seats[rowIndex][col] = true;  // 해당 좌석을 예약됨(true) 상태로 설정


    }

    inFile.close();
}

// 좌석 정보를 파일에 저장하는 함수
void savePaidSeatsToFile(const string& movieName, int month, int day,int time) {
    ofstream outFile(movieName + "_" + to_string(month) + "월_" + to_string(day) + "일_" + to_string(time) + "시_seats.txt", ios::app);

    if (!outFile) {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    // paid_reserved_seats에 저장된 좌석 정보를 파일에 기록
    for (const string& seat : paid_reserved_seats) {
        outFile << seat << endl;
    }

    outFile.close();
}

void resetAllSeats() {
    // 모든 좌석 배열 초기화
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            seats[i][j] = false;  // 모든 좌석을 빈 상태로 설정
        }
    }

    // 예약된 좌석 정보 초기화
    reserved_seats.clear();
    paid_reserved_seats.clear();  // 결제 완료된 좌석 정보도 초기화
    cout << "모든 좌석 정보가 초기화되었습니다.\n";
}

void saveBookingDetailsToFile(const string& name, const string& movieName, int month, int day, int time, int people_count) {
    // 파일 이름 생성 (예: 영화이름_2025-02-18_15시_4명.txt)
    string fileName = name+"_"+movieName + "_" + to_string(month) + "월_" + to_string(day) + "일_" + to_string(time) + "시_" + to_string(people_count)+"명" + ".txt";

    ofstream outFile(fileName);

    if (!outFile) {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    // 파일에 예약 정보 기록
    outFile << "예약자: " << name << endl;
    outFile << "영화: " << movieName << endl;
    outFile << "상영 날짜: " << month << "월 " << day << "일" << endl;
    outFile << "상영 시간: " << time << "시" << endl;
    outFile << "예약 인원: " << people_count << "명" << endl;

    // 좌석 정보 기록
    outFile << "예약된 좌석: ";
    for (const string& seat : reserved_seats) {
        outFile << seat << " ";  // 예약된 좌석 목록
    }
    outFile << endl;

    outFile.close();
    cout << "예약 정보가 " << fileName << " 파일에 저장되었습니다.\n";
}