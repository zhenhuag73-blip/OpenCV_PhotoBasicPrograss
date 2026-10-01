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
//腐蚀&膨胀
    void func2_5_erode();
    void func2_5_dilate();
//形态学处理
    void func2_5_Pro();
//轮廓、连通域&⽬标筛选
    void func2_6(Mat &image);
    void func2_6_toClose(Mat &image);
//边缘 直线，圆与矩形检测
    void func2_7(Mat &image);
    void func2_7_Pro(Mat &image);
//ROI与掩膜
    void func2_8_roi(Mat &image);
    void func2_8_mask(Mat &image);
};