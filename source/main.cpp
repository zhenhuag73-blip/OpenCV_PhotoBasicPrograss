#include"quick.h"


//################################################################
int num;
int value;
void onTrack(int,void*){
    value = 2*num + 1;
}
//################################################################

int main(int argc,char **argv){
    Mat image = imread("/home/branc/Desktop/C++OpenCV/Input/4.jpg",IMREAD_UNCHANGED);
    if(image.empty()){
        cout << "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR " << endl;
        return -1;
    }
    cout<<"----------BASIC INFORMATION----------" << endl;
    cout<<"image: " << "type: " << image.type() << endl;
    cout<<"       " << "长cols: " << image.cols << endl;
    cout<<"       " << "宽rows: " << image.rows << endl;
    cout<<"       " << "channels: " << image.channels() << endl;
    cout<<"       " << "eleSize: " << image.elemSize() << " 字节  (每个像素占的字节数)" << endl;
    cout<<"       " << "eleSize1: " << image.elemSize1() << "字节  (每个通道占的字节数)" << endl;
    cout<<"       " << "是否连续: " << (image.isContinuous() ? "Yes" : "No" ) << endl;

    QuickDemo qd;
//  qd.func2_8_roi(image);
    qd.func2_8_mask(image);

    
    waitKey(0);
    destroyAllWindows();
}