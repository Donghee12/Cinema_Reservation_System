#pragma once
#include <Windows.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;
extern string input_number;
// ���콺 �̺�Ʈ ó�� �Լ�: ���� ��ȣ �Է��� ���� Ŭ�� �̺�Ʈ ó��
void onMouse(int event, int x, int y, int flags, void* userdata);
void CarNumberInput();
