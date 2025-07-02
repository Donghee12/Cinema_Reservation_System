#include "booking_info.h"
#include "seat.h"

void booking_info::set_booking_info(string name, string movie, int month, int day,
    int time, int people_num, char col, int row, int price)
{
    this->name = name;
    this->movie = movie;        
    this->month = month;
    this->day = day;
    this->time = time;
    this->people_num = people_num;
    this->col = col;
    this->row = row;
    this->price = price;       
}
void booking_info::print_booking() {
    cout << "������:" << name << " ��ȭ:" << movie << ", " << month << "�� " 
        << day << "��, " << time << "��, " << people_num << "�� �¼�:"
        << col << row << " ���ұݾ�:" << price << "��" << endl;
}
string booking_info::getname() {
    return name;
}
string booking_info::getmovie() {
    return movie;
}
int booking_info::getmonth() {
    return month;
}
void booking_info::setmonth(int month) {
    this->month = month;
}
int booking_info::getday() {
    return day;
}
int booking_info::gettime() {
    return time;
}
int booking_info::getpeople_num() {
    return people_num;
}
char booking_info::getcol() {
    return col;
}
int booking_info::getrow() {
    return row;
}
int booking_info::getprice() {
    return price;
}

//���� ����
void write(const string& str) {
    ofstream out("booking.txt", ios::app);
    if (out.is_open()) {
        out << str;
    }
}
//���� ����
void clearFile() {
    ofstream out("booking.txt", ios::trunc);
    out.close();
}
//���� ���� ����
void booking_save_txt(const string& name, const string& movie, int month, int day,
    int time, int people_num, char col, int row, int price) {
    char str[20];
    write(name);
    write("\n");
    write(movie);
    write("\n");
    write(to_string(month));
    write("\n");
    write(to_string(day));
    write("\n");
    write(to_string(time));
    write("\n");
    write(to_string(people_num));
    write("\n");
    write(string(1,col));
    write("\n");
    write(to_string(row));
    write("\n");
    write(to_string(price));
    write("\n");
}
//���� ���� ����2
void booking_save_txt(booking_info b) {
    char str[20];
    write(b.getname());
    write("\n");
    write(b.getmovie());
    write("\n");
    write(to_string(b.getmonth()));
    write("\n");
    write(to_string(b.getday()));
    write("\n");
    write(to_string(b.gettime()));
    write("\n");
    write(to_string(b.getpeople_num()));
    write("\n");
    write(string(1, b.getcol()));
    write("\n");
    write(to_string(b.getrow()));
    write("\n");
    write(to_string(b.getprice()));
    write("\n");
}

//���� ���� booking_info Ŭ���� �迭��
void booking_arr(booking_info b[]) {
    string line;
    string name;
    string movie;
    int month = -1;
    int day = -1;
    int time = -1;
    int people_num = -1;
    char col;
    char row = -1;
    int price = -1;

    ifstream in("booking.txt");
    if (!in.is_open()) {
        cout << "������ �� �� �����ϴ�!" << endl;
        return;
    }
    int c = 0;
    int i = 0;
    while (getline(in, line)) {
        if (c == 0)
            name = line;
        else if (c == 1)
            movie = line;
        else if (c == 2)
            month = stoi(line);
        else if (c == 3)
            day = stoi(line);
        else if (c == 4)
            time = stoi(line);
        else if (c == 5)
            people_num = stoi(line);
        else if (c == 6)
            col = line[0];
        else if (c == 7)
            row = stoi(line);
        else if (c == 8)
            price = stoi(line);
        c++;
        if (c == 9) {
            b[i].set_booking_info(name, movie, month, day, time, people_num, col, row, price);
            i++;
            c = 0;
        }
    }
    in.close();
}
//���� Ȯ��
void search_booking(booking_info b[])
{
    string name;
    int index = -1;
    char str[50];
    while (1) {
        cout << "�������� ������ �˷��ּ���(
            =q):";
        cin >> name;
        if (name.c_str()[0] == 'q' && name.c_str()[1] == '\0') {
            cout << "��ҵǾ����ϴ�." << endl;
            break;
        }
        for (int i = 0;i < 100;i++) {
            if (b[i].getname().compare(name) == 0) {
                index = i;
                break;
            }
        }
        if (index == -1)
            cout << "�������� �ʾҽ��ϴ�. �ٽ��Է����ּ���." << endl;
        else {
            b[index].print_booking();
            break;
        }
    }
}

int search_booking(booking_info b[],int a)
{
    string name;
    int index = -1;
    char str[50];
    while (1) {
        cout << "�������� ������ �˷��ּ���(���=q):";
        cin >> name;
        if (name.c_str()[0] == 'q' && name.c_str()[1] == '\0') {
            cout << "��ҵǾ����ϴ�." << endl;
            break;
        }
        for (int i = 0;i < 100;i++) {
            if (b[i].getname().compare(name) == 0) {
                index = i;
                break;
            }
        }
        if (index == -1)
            cout << "�������� �ʾҽ��ϴ�. �ٽ��Է����ּ���." << endl;
        else {
            b[index].print_booking();
            break;
        }
    }
    return index;
}

//���� �ð�
time_t now_time(){
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    return now_c;
}
//���� �ð�
time_t movie_time(int month, int day, int hour) {
    struct tm t = {};
    t.tm_year = 2025 - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = 0;
    t.tm_sec = 0;
    return mktime(&t);
}
//������� ���ɿ���
bool cancel_able(booking_info b) {
    time_t x = movie_time(b.getmonth(), b.getday(), b.gettime());
    time_t y = now_time();
    if (x > y)
        return true;
    else
        return false;
}
//Ŭ���� �迭���� ����� ���� �����
void booking_cancel_arr(booking_info b[], int index) {
    int pn = b[index].getpeople_num();
    for (index;b[index+pn].getmonth() != -1;index++) {
        b[index] = b[index + pn];
    }
    for (int i = 0;i < pn;i++)
        b[index + i].setmonth(-1);
}

//�������
void booking_cancel(booking_info b[]) {
    int index = search_booking(b, 1);
    char ans;
    if (index == -1)
        return;
    if (cancel_able(b[index]) == true) {
        while (1) {
            cout << "���Ÿ� ����Ͻðڽ��ϱ�?(y or n):";
            cin >> ans;
            if (ans == 'y') {
                booking_cancel_arr(b, index);
                clearFile();
                for (int i = 0;b[i].getmonth() != -1;i++)
                    booking_save_txt(b[i]);
                balance = balance + b[index].getprice();
                cout << "���� ��ҵǾ����ϴ�" << endl;
                break;
            }
            else if (ans == 'n') {
                cout << "���� ��Ұ� ����Ǿ����ϴ�" << endl;
                break;
            }
            else {
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
            }
        }
    }
    else
        cout << "�̹� �󿵵� ��ȭ�Դϴ�. ������Ұ� �Ұ����մϴ�." << endl;
}

//int main(void) {
//    booking_info b[100];
//    //booking_save_txt("�Ž���", "��Ű17", 2, 18, 14, 2, 'G', 6, 28000);
//    booking_arr(b);
//    //search_booking(b);
//    //booking_cancel(b);
//    booking_cancel(b);
//    return 0;
//}