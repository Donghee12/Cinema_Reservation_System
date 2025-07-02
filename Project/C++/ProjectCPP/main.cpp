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
    SetConsoleCP(949);  // �Է� �ڵ� �������� CP949�� ����
    SetConsoleOutputCP(949);  // ��� �ڵ� �������� CP949�� ����

    booking_info b[100];
    int main_ch;
    int movie;
    string name;
    while (1)
    {
        std::cout << "==================================" << endl;
        std::cout << "         ��ȭ ���� ���α׷�       " << endl;
        std::cout << "==================================" << endl;
        std::cout << "[1] : ����     " << endl;
        std::cout << "[2] : ���� ���� Ȯ��" << endl;
        std::cout << "[3] : ���� ���" << endl;
        std::cout << "[4] : ������ �߱�" << endl;
        std::cout << "[5] : �������� ���" << endl;
        std::cout << "[6] : ��ȭ ���" << endl;
        std::cout << "[7] : ����" << endl;
        std::cout << "�޴� ��ȣ�� �Է��ϼ��� : ";
        std::cin >> main_ch;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        system("cls");

       int people;
        // �޴� ���ÿ� ���� ó��
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
            std::cout << "����Ǿ����ϴ�." << endl;
            return 0; // ����

        default:
            std::cout << "��ȣ�� �߸� �����ϼ̽��ϴ�. �ٽ� �������ּ���." << endl;
            break;
        }

        std::cout << "�޴��� ���ư������ؼ� ���� �Ǵ� �ƹ� Ű�� �Է� ���ּ���." << endl;
        std::cin.ignore(); // ���� ����
        std::cin.get();
        system("cls"); // ȭ�� ����
    }
}
