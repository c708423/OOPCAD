// Testing.cpp: 定义控制台应用程序的入口点。
//
#include "../CAD/include/definitions.h"
#include "../CAD/include/Stroke.h"
#include <iostream>

using namespace std;
using namespace ACCAD;

int main()
{
    Image image(5, 3);
    Stroke stroke({ { { 1,0 },{ 255,255,255,255 } },{ { 2,1 },{ 255,255,255,255 } } }, { 0,0,0,0 });
    PrintImage(image);
    cout << endl;
    stroke.exec(image);
    PrintImage(image);
    cout << endl;
    stroke.undo(image);
    PrintImage(image);
    cout << endl;
    return 0;
}

