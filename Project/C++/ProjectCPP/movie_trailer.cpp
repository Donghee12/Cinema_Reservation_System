#include "movie_trailer.h"
#include "slide_img.h"
#include "reservation.h"

vector<string> video = {
	"1.mp4",
	"2.mp4",
	"3.mp4",
	"4.mp4",
	"5.mp4"
};

void movie_trailer(int num) {
	Mat img_frame;
	VideoCapture cap(video[num]);
	if (!cap.isOpened())
	{
		cout << "�������� �� �� �����ϴ�." << endl;
		return;
	}
	while (1)
	{
		bool ret = cap.read(img_frame);
		if (!ret)
		{
			cout << "������ ���� �б� �Ϸ�" << endl;
			break;
		}
		imshow("Movie Trailer", img_frame);
		int key = waitKey(25);
		if (key == 27)
			break;
	}
	cap.release();
	destroyAllWindows();
}

void movie_trailer_menu() {
	int main_ch;
	int movie;
	while (1)
	{
		std::cout << "[1] : ������ ����     " << endl;
		std::cout << "[2] : ������ ����     " << endl;
		std::cout << "[3] : �ڷΰ���     " << endl;
		std::cin >> main_ch;
		system("cls");
		switch (main_ch)
		{
		case 1:
			Movie m1;
			movie = m1.ShowMovies() - 1;
			system("cls");
			movie_trailer(movie);
			break;
		case 2:
			poster();
			break;
		case 3:
			std::cout << "�ڷΰ��ϴ�." << endl;
			return;
		default:
			std::cout << "��ȣ�� �߸� �����ϼ̽��ϴ�. �ٽ� �������ּ���." << endl;
			break;
		}
	}
}