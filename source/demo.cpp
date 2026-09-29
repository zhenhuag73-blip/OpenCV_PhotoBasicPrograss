#include"quick.h"
#include<opencv2/opencv.hpp>
#include <opencv2/geometry.hpp>
#include<iostream>
#include<vector>

using namespace std;
using namespace cv;

Mat input = imread("/home/branc/桌面/C++OpenCV/Input/ugly.jpg",IMREAD_UNCHANGED);


/*
#################################################################
阈值与二值化
output = threshold(input,thresh,maxval,type);
thresh: 阈值
maxval: 当像素超过/小于 阈值，如何处理
type: THRESH_BINARY 二值化:(current > value ? max : 0) 
################################################################
*/
void QuickDemo::func2_3(Mat &image){
    Mat gray;
    cvtColor(image,gray,COLOR_BGR2GRAY);
    Mat output;
//  基础二值化
    threshold(gray,output,80,255,THRESH_BINARY);
    imshow("Basical",output);
//  自适应二值化 -- 仅适用于灰度
    adaptiveThreshold(gray,output,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,55,0);
    imshow("adaptive",output);

    adaptiveThreshold(gray,output,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,55,0);
    imshow("GaussAdptv",output);
}


/* 
滤波与降噪
滤波就是卷积，是一个小矩阵与原始图像的乘积
################################################################
define:
卷积核的大小  卷积核一般为奇数1x1，5x5  可以保证锚点在中间，防止位置偏移
            卷积核越大感受野(信息)越多，提取特征越好，计算量更大
锚点         锚点就是矩阵的中心
边界扩充：    当卷积核大于1且不进行边界扩充，输出尺寸相应缩小
            当卷积核以标准方式边界扩充，尺寸不变
N = (W - F + 2P) / S + 1
N输出大小 W源图大小 F卷积核大小 P扩充尺寸 S步长大小
步长  
#################################################################
低通滤波可以去除噪音，平滑图像
高通滤波可以帮助查找图像的边缘
#################################################################
图像卷积   图像   输出    位深   !卷积核  锚点         边界类型
fitlter2D(image,output,ddepth,kernel,anchor,delta,borderType)
*/
#define eleType float

int n;
int func_x;

Mat frame;

static void on_Track_gauss(int,void*){
    func_x = 2 * n + 1;
//  GaussBlur
    GaussianBlur(input,frame,Size(func_x,func_x),0);
    imshow("Gaussianblur",frame);
}
static void on_Track_medium(int, void*){
    func_x = 2 * n + 1;
//  medianBlur
    medianBlur(input,frame,func_x);
    imshow("medianblur",frame);
}    
void QuickDemo::func2_4(Mat &image){
//  平均滤波
    Mat kernel_ave = (Mat_<eleType>(3,3) << 
    4,8,4,
    8,16,8,
    4,8,4);

    kernel_ave = kernel_ave / 64;

    Mat dst;
    filter2D(image,dst,-1,kernel_ave,Point(-1,-1),0,BORDER_DEFAULT);
    namedWindow("dst",WINDOW_AUTOSIZE);
    imshow("dst",dst);

//  Blur
    blur(image,dst,Size(75,75),Point(-1,-1));
    namedWindow("blur",WINDOW_AUTOSIZE);
    imshow("blur",dst);

//  GaussBlur  平滑滤波
    namedWindow("Gaussianblur",WINDOW_AUTOSIZE);
    createTrackbar("Gaussianblur","Gaussianblur",&n,100,on_Track_gauss);
    on_Track_gauss(0,0);

//  medianBlur
    namedWindow("medianblur",WINDOW_AUTOSIZE);
    createTrackbar("medianBlur","medianblur",&n,100,on_Track_medium);
    on_Track_medium(0,0);

}


/*
#################################################################
形态学处理
腐蚀：常用于去除图像里的微小物体，分立两个较近的图像
     腐蚀会缩⼩⽩⾊区域，适合去掉⼩⽩点
  结构元素：getStructingElement(int shape,Size ksize,Point anchor = Point(-1,-1));

                        结构元素        腐蚀次数
  腐蚀：   erode(src,dst,Kernel,anchor,interations,borderType,borderValue);
                输入的待腐蚀图像，图像的通道数可以是任意的，但是图像的数据类型必须是CV 8U，CV_16U，CV_16S,CV_32F 或 CV_64F之一。
#################################################################
*/
int n2_5,
    value2_5;
Mat struct1,
    struct2,
    dst;

void onTrackErodeJuxing(int,void*){
    value2_5 = (2 * n2_5) + 1;
    struct1 = getStructuringElement(0,Size(value2_5,value2_5));// 矩形 3x3
    erode(input,dst,struct1);
    imshow("矩形_erode",dst);
}
void onTrackErodeShizi(int,void*){
    value2_5 = (2 * n2_5) + 1;
    struct2 = getStructuringElement(1,Size(value2_5,value2_5));// 十字 3x3
    erode(input,dst,struct2);
    imshow("十字_erode",dst);
}
void onTrackVideo(int,void*){
    value2_5 = 2* n2_5 + 1;
}
void QuickDemo::func2_5_erode(){

    namedWindow("矩形_erode",WINDOW_FREERATIO);
    namedWindow("十字_erode",WINDOW_FREERATIO);

    createTrackbar("control_1","矩形_erode",&n2_5,100,onTrackErodeJuxing);
    onTrackErodeJuxing(0,0);

    createTrackbar("control_2","十字_erode",&n2_5,100,onTrackErodeShizi);
    onTrackErodeShizi(0,0);

//#################################################################
//视频处理
    VideoCapture vd = VideoCapture(0);
    Mat frame,temp;
    
    namedWindow("Frame_erode",WINDOW_FREERATIO);
    createTrackbar("VideoControl","Frame_erode",&n2_5,100,onTrackVideo);
       onTrackVideo(0,0);

    while(1){
        vd >> temp;

        Mat structVD = getStructuringElement(0,Size(value2_5,value2_5));
        erode(temp,frame,structVD);

        imshow("Frame_erode",frame);
        waitKey(27);
    }

    destroyAllWindows();

}
/*
#################################################################
形态学处理
膨胀：膨胀会扩⼤⽩⾊区域，适合填补缺⼝。

                        结构元素        膨胀次数
    膨胀：dilate(src,dst,Kernel,anchor,interations,borderType,borderValue)
                输入的待腐蚀图像，图像的通道数可以是任意的，但是图像的数据类型必须是CV 8U，CV_16U，CV_16S,CV_32F 或 CV_64F之一。
#################################################################
*/
Mat struct3,struct4;
    void onTrackDilateJuxing(int,void*){
    value2_5 = (2 * n2_5) + 1;
    struct3 = getStructuringElement(0,Size(value2_5,value2_5));// 矩形 3x3
    dilate(input,dst,struct3);
    imshow("矩形_dilate",dst);
}
void onTrackDilateShizi(int,void*){
    value2_5 = (2 * n2_5) + 1;
    struct4 = getStructuringElement(1,Size(value2_5,value2_5));// 十字 3x3
    dilate(input,dst,struct4);
    imshow("十字_dilate",dst);
}
void QuickDemo::func2_5_dilate(){

    namedWindow("矩形_dilate",WINDOW_FREERATIO);
    namedWindow("十字_dilate",WINDOW_FREERATIO);

    createTrackbar("control_3","矩形_dilate",&n2_5,100,onTrackDilateJuxing);
    onTrackDilateJuxing(0,0);

    createTrackbar("control_4","十字_dilate",&n2_5,100,onTrackDilateShizi);
    onTrackDilateShizi(0,0);
    

//#################################################################
//视频处理
    VideoCapture vd = VideoCapture();
    Mat frame,temp;
    
    namedWindow("Frame_dilate",WINDOW_FREERATIO);
    createTrackbar("VideoControl","Frame_dilate",&n2_5,100,onTrackVideo);
       onTrackVideo(0,0);

    while(1){
        vd >> temp;

        Mat structVD = getStructuringElement(2,Size(value2_5,value2_5));
        dilate(temp,frame,structVD);

        imshow("Frame_dilate",frame);
        waitKey(27);
    }
    destroyAllWindows();
}   
/*
#################################################################
形态学处理：

                                   操作                 处理次数
void morphologyEx(input,output,int option,kernel,Point,interations,borderType,borderValue)
                               腐蚀0 膨胀1
MORPH_TYPE                               
>>>>>>>>>>>>>>>>>>>>>>     开运算(2)     <<<<<<<<<<<<<<<<<<<<<<<<<<<<
————MORPH_OPEN
去除图像的噪声，消除较小的连通域，保留较大的连通域
先对图像进行腐蚀，再对图像进行膨胀

>>>>>>>>>>>>>>>>>>>>>>     闭运算(3)     <<<<<<<<<<<<<<<<<<<<<<<<<<<<
————MORPH_CLOSE
去除图像内的小型空洞，平滑物体轮廓，连接两个邻近的连通域
先对图像进行膨胀，再对图像进行腐蚀

>>>>>>>>>>>>>>>>>>>>>>     梯度运算(4)     <<<<<<<<<<<<<<<<<<<<<<<<<<<<
————MORPH_GRADIENT
对原图膨胀，对原图腐蚀，得到轮廓
膨胀 - 腐蚀 = 形态学基本梯度

>>>>>>>>>>>>>>>>>>>>>>     顶帽运算(5)     <<<<<<<<<<<<<<<<<<<<<<<<<<<<
————MORPH_TOPHAT
分离比邻近点亮一些的斑块
对原图像开运算，原图像 - 开运算

>>>>>>>>>>>>>>>>>>>>>>     黑帽运算(6)     <<<<<<<<<<<<<<<<<<<<<<<<<<<<
————MORPH_BLACKHAT
分离比邻近点暗一些的斑块
对原图像进行闭运算，原图像 - 闭运算

>>>>>>>>>>>>>>>>>>>>>>    击中击不中运算(7)     <<<<<<<<<<<<<<<<<<<<<<<<<<<<
————MORPH_HITMISS
与图像腐蚀类似，但是要能比图像腐蚀要求更苛刻的运算

#################################################################
*/
int n2_5_ProPicture,
    n2_5_ProVideo,
    value2_5_Option,
    value2_5_ProPicture,
    value2_5_ProVideo,
    option;

Mat kernel2_5_ProPicture,
    kernel2_5_ProVideo;
void onTrackOption(int, void*){
    option = value2_5_Option;
}
void Kernel2_5_ProPicture(int,void*){
    value2_5_ProPicture = 2 * n2_5_ProPicture + 1;
}
void Kernel2_5_ProVideo(int,void*){
    value2_5_ProVideo = 2 * n2_5_ProVideo + 1;
}

void QuickDemo::func2_5_Pro(){

    namedWindow("Picture",WINDOW_NORMAL);
    namedWindow("Video",WINDOW_NORMAL);
    namedWindow("Public",WINDOW_NORMAL);

    namedWindow("Original_Picture",WINDOW_NORMAL);
    imshow("Original_Picture",input);

    createTrackbar("Option","Public",&value2_5_Option,6,onTrackOption);
    createTrackbar("Value_ON_Picture","Picture",&n2_5_ProPicture,112,Kernel2_5_ProPicture);
    createTrackbar("Value_ON_Video","Video",&n2_5_ProVideo,112,Kernel2_5_ProVideo);
    
    onTrackOption(0,0);
    Kernel2_5_ProPicture(0,0);
    Kernel2_5_ProVideo(0,0);

    namedWindow("Original_Video",WINDOW_NORMAL);
    VideoCapture vd = VideoCapture(0);
    Mat temp,
        frame;
    while(1){
        kernel2_5_ProPicture = getStructuringElement(2,Size(value2_5_ProPicture,value2_5_ProPicture));
    //alogorithm
        morphologyEx(input,dst,option,kernel2_5_ProPicture);
        imshow("Picture",dst);
        waitKey(27);

        vd >> temp;
        imshow("Original_Video",temp);
        kernel2_5_ProVideo = getStructuringElement(0,Size(value2_5_ProVideo,value2_5_ProVideo));
    //alogorithm
        morphologyEx(temp,frame,option,kernel2_5_ProVideo);
        imshow("Video",frame);
        waitKey(27);
    }
}


/*
轮廓检测
#################################################################
>>>>>>>>>>>>>      --检测--      <<<<<<<<<<<<<<
                   检测的轮廓         检测模式      每个轮廓点移动的范围,一般默认
findContours(image,contours,hieratchy,mode,method,offset)
                                         轮廓逼近方式
OutPutArraryOfArrarys contours
hierarchy  检测到的轮廓，用于描绘其的矩阵或者一个向量
#################################################################
>>>>>>>>>>>>>      --绘制--      <<<<<<<<<<<<<<
                                             粗细int        线形         上一个向量  绘制轮廓的偏移量
drawContours(image,contours,contourIdx,color,int thickness,int lineType,hieratchy,InputArrart，max_level)
                                                                                               绘制轮廓的最大的程度
contourIdx: 绘制轮廓的参数，也就是要绘制第几个轮廓
            若要绘制所有轮廓，将其设置为 -1
color:  const Sccalar & colo
#################################################################
>>>>>>>>>>>>>      --面积--      <<<<<<<<<<<<<<

double contourArea(contour,bool oriented = false)
bool oriented 是否具有方向性
返回值：面积
#################################################################
>>>>>>>>>>>>>      --长度--      <<<<<<<<<<<<<<

double arcLength(curve,bool closed);
curve: 轮廓或者2D曲线的像素点
*/
void QuickDemo::func2_6(Mat &image){
    Mat gray,
        binary;
    cvtColor(image,gray,COLOR_BGR2GRAY);
//  平滑滤波
    GaussianBlur(gray,gray,Size(27,27),4,4);
    threshold(gray,binary,170,255,THRESH_BINARY | THRESH_OTSU);
    namedWindow("result",WINDOW_NORMAL);
//  轮廓
    vector<vector<Point>> contours;
//  存放轮廓的结构体变量
    vector<Vec4i> hieratchy;

    findContours(binary,
                contours,
                hieratchy,
                RETR_TREE,
                CHAIN_APPROX_SIMPLE,
                Point());
    drawContours(image,
                 contours,
                 -1,
                 Scalar(0,0,255),
                 2,8);

    imshow("result",image);
    
    for(int i = 0;i < contours.size();++i){
        double square = contourArea(contours[i]);
        cout << "Square[ " << i << " ]: " << square << endl;
    }
    for(int i = 0;i < contours.size();++i){
        double legth = arcLength(contours[i],true);
        cout << "Length[ " << i << " ]: " << legth << endl;
    }
//#################################################################
    VideoCapture vd = VideoCapture(0);
    Mat vd_gray,
        vd_binary,
        frame;
        namedWindow("Video",WINDOW_FREERATIO);
    while(1){
        vd >> frame;
        
        cvtColor(frame,vd_gray,COLOR_BGR2GRAY);
        GaussianBlur(vd_gray,vd_gray,Size(3,3),4,4);
        threshold(vd_gray,vd_binary,170,255,THRESH_BINARY | THRESH_OTSU);

        vector<vector<Point>> vd_contours;
        vector<Vec4i> vd_hieratchy;

        findContours(vd_binary,vd_contours,vd_hieratchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point());
        drawContours(frame,vd_contours,-1,Scalar(0,0,255),2,8);

        imshow("Video",frame);
        waitKey(27);
    }
    waitKey(0);
}


/*
轮廓矩形拟合
#################################################################
关键函数

矩形拟合
 |Rect boundingRect(InputArray array);
 |
 |RotatedRect minAreaRect(InputArray Points);
 |旋转的矩形
array输入的灰度图像与2D点集，输入的对象为向量vector<Point>或者Mat

多边形拟合
 |approxPolyDP(InputArray curve,        ————轮廓像素点
               OutputArray approxCurve, ————逼近结果，以多边形顶点坐标形式给出
               double epsillon          ————拟合精度
               bool closed);            ————whether closed?
*/
int n2_6,
    canny_threshold1_2_6;
void onCannyThrhod2_6(int,void*){
    canny_threshold1_2_6 = 4* (n2_6 + 1);
}
void QuickDemo::func2_6_toClose(Mat &image){
    namedWindow("result",WINDOW_FREERATIO);
//#################################################################
//  去噪声与二值化
    Mat canny;
    Canny(image,canny,canny_threshold1_2_6,160,3,false);
    imshow("canny",canny);
//  膨胀下
    Mat kernel = getStructuringElement(0,Size(3,3));
    dilate(canny,canny,kernel);

    vector<vector<Point>> contours;
    vector<Vec4i> hieratchy;
    findContours(canny,
                 contours,
                 hieratchy,
                 0,
                 2,
                 Point());
//  寻找外接矩形
    for(int i = 0;i < contours.size();++i){
            Rect rect = boundingRect(contours[i]);
            rectangle(image,rect,Scalar(0,255,0),3,8);
        }        
    imshow("result",image);
    
//#################################################################
    VideoCapture vd = VideoCapture(0);
    Mat frame, canny_video;
    namedWindow("VideoStream",WINDOW_FREERATIO);
    namedWindow("VideoStream1",WINDOW_FREERATIO);

    createTrackbar("threshold1","VideoStream",&n2_6,100,onCannyThrhod2_6);
    onCannyThrhod2_6(0,0);

    while(1){
//#################################################################

//#################################################################
        vd >> frame;
        Canny(frame, canny_video,canny_threshold1_2_6,160,3,false);

        imshow("VideoStream1",canny_video);

        dilate(canny_video, canny_video, kernel);
        findContours(canny_video, contours, hieratchy, 0, 2, Point());
        for(int i = 0;i < contours.size();++i){
            Rect rect = boundingRect(contours[i]);
            rectangle(frame, rect, Scalar(0,0,255),1,8);
        }
        imshow("VideoStream",frame);
        waitKey(27);
    }

}