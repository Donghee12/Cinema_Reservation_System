#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

void fadeTransition(const Mat& img1, const Mat& img2, int steps = 30, int delay = 30);

void poster();