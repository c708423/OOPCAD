// Testing.cpp: 定义控制台应用程序的入口点。
//
#include "../CAD/include/definitions.h"
#include "../CAD/include/Stroke.h"
#include <iostream>

using namespace std;
using namespace ACCAD;

int main()
{
    vector<pair<Vec2i, Color>> origin
    {
        {{1,1},{1,1,1,1}},
        {{2,2},{2,2,2,2}}
    };
    Stroke(origin, { 0,0,0,0 });
    return 0;
}

