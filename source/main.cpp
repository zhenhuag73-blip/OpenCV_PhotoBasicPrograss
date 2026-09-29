#include"quick.h"


//################################################################
int num;
int value;
void onTrack(int,void*){
    value = 2*num + 1;
}
//################################################################

int main(int argc,char **argv){
    Mat image = imread("/home/branc/Desktop/C++OpenCV/Input/object.jpg",IMREAD_UNCHANGED);
//    namedWindow("original",WINDOW_FREERATIO);
//    imshow("original",image);

    QuickDemo qd;
 //   qd.func2_6(image);
    qd.func2_5_Pro();
    
    waitKey(0);
    destroyAllWindows();
}