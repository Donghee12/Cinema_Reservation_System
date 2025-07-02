#pragma once
#include <iostream>

using namespace std;

class Peopleselector
{
private:
    int C_people; // 선택된 인원 수 저장

public:
    // 인원 수 선택 함수
    void People();

    // 선택된 인원 수 반환
    int G_C_people();
};