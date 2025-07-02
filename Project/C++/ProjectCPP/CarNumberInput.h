#pragma once
#include <Windows.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;
extern string input_number;
// 마우스 이벤트 처리 함수: 차량 번호 입력을 위한 클릭 이벤트 처리
void onMouse(int event, int x, int y, int flags, void* userdata);
void CarNumberInput();
