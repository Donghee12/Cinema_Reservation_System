#include "booking_info.h"
#include "CarNumberInput.h"
#include "CarNumberOutput.h"
#include "DateSelector.h"
#include "PeopleSelector.h"
#include "reservation.h"
#include "seat.h"
#include "TimeSelector.h"
#include "D_T_P.h"
#include "slide_img.h"
#include "viewBookingInfo.h"
#include "cancelBooking.h"
#include "movie_trailer.h"

int main()
{
    SetConsoleCP(949);  // 입력 코드 페이지를 CP949로 설정
    SetConsoleOutputCP(949);  // 출력 코드 페이지를 CP949로 설정

    booking_info b[100];
    int main_ch;
    int movie;
    string name;
    while (1)
    {
        std::cout << "==================================" << endl;
        std::cout << "         영화 예매 프로그램       " << endl;
        std::cout << "==================================" << endl;
        std::cout << "[1] : 예매     " << endl;
        std::cout << "[2] : 예매 내역 확인" << endl;
        std::cout << "[3] : 예매 취소" << endl;
        std::cout << "[4] : 주차권 발급" << endl;
        std::cout << "[5] : 주차차량 목록" << endl;
        std::cout << "[6] : 영화 목록" << endl;
        std::cout << "[7] : 종료" << endl;
        std::cout << "메뉴 번호를 입력하세요 : ";
        std::cin >> main_ch;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        system("cls");

       int people;
        // 메뉴 선택에 따른 처리
        switch (main_ch)
        {
        case 1:
            name = getname();
            Movie m1;
            movie = m1.ShowMovies() - 1;
            system("cls");
            D_T_P_mix();
            people = selectedPeople;
            startBookingProcess(name, selectedPeople, selectedMonth, selectedDay, selectedTime, movies[movie]);
            break;
        case 2:
            chooseBookingFile();
            break;
        case 3:
            cancelBooking();
            break;
        case 4:
            CarNumberInput();
            break;
        case 5:
            CarNumberOutput();
            break;
        case 6:
            movie_trailer_menu();
            break;
        case 7:
            std::cout << "종료되었습니다." << endl;
            return 0; // 종료

        default:
            std::cout << "번호를 잘못 선택하셨습니다. 다시 선택해주세요." << endl;
            break;
        }

        std::cout << "메뉴로 돌아가기위해서 엔터 또는 아무 키를 입력 해주세요." << endl;
        std::cin.ignore(); // 버퍼 비우기
        std::cin.get();
        system("cls"); // 화면 정리
    }
}
