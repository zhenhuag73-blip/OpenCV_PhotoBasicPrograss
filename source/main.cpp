#include"quick.h"


//################################################################
int num;
int value;
void onTrack(int,void*){
    value = 2*num + 1;
}
//################################################################

int main(int argc,char **argv){
    Mat image = imread("/home/branc/桌面/C++OpenCV/Input/5.jpg",IMREAD_UNCHANGED);
//    namedWindow("original",WINDOW_FREERATIO);
//    imshow("original",image);

    QuickDemo qd;
 //   qd.func2_6(image);
    qd.func2_6_toClose(image);
    
//################################################################
/*
    namedWindow("Frame",WINDOW_FREERATIO);
    createTrackbar("Value","Frame",&num,100,onTrack);
    onTrack(0,0);
    VideoCapture vd = VideoCapture(0);
    Mat temp;
    Mat frame;
    while(1){
        vd>>temp;
//>>>>>>" algorithm "<<<<<<<<
//      threshold(temp,frame,value,155,THRESH_BINARY);
        GaussianBlur(temp,frame,Size(value,value),0);
//>>>>>>" algorithm "<<<<<<<<
        imshow("Frame",frame);
        waitKey(27);
    }
*/
//################################################################
    waitKey(0);
    destroyAllWindows();
}