#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/video/video.hpp>
#include <opencv4/opencv2/video/tracking.hpp>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/imgproc/imgproc_c.h>
#include <opencv4/opencv2/highgui/highgui_c.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "ft.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat im,f;
	VideoCapture v(0);
	DFtrans df;
	
	while(1)
	{
		v>>im;
		resize(im,im,Size(500,500));
		im = Scalar::all(0);
		ellipse(im,Point(250,250),Size(25,35),45,0,360,Scalar(255,255,255),2,8);
		
		f = df.Trans(im);
		
		imshow("im",im);
		imshow("f",f);
		waitKey(30);
	}
	waitKey(0);
}
