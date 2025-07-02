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
		cout << "동영상을 열 수 없습니다." << endl;
		return;
	}
	while (1)
	{
		bool ret = cap.read(img_frame);
		if (!ret)
		{
			cout << "동영상 파일 읽기 완료" << endl;
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
		std::cout << "[1] : 예고편 보기     " << endl;
		std::cout << "[2] : 포스터 보기     " << endl;
		std::cout << "[3] : 뒤로가기     " << endl;
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
			std::cout << "뒤로갑니다." << endl;
			return;
		default:
			std::cout << "번호를 잘못 선택하셨습니다. 다시 선택해주세요." << endl;
			break;
		}
	}
}