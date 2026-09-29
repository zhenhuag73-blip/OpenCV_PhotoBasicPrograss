#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class QuickDemo{
    public:
    void test(Mat &image);
    void CrtBar();
//阈值&二值化
    void func2_3(Mat &image);
//滤波与降噪
    void func2_4(Mat &image); 
//腐蚀 膨胀 
    void func2_5_erode();
    void func2_5_dilate();
//形态学处理
    void func2_5_Pro();
//轮廓、连通域与⽬标筛选
    void func2_6(Mat &image);
    void func2_6_toClose(Mat &image);
};