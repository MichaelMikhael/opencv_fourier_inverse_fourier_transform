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


using namespace std;
using namespace cv;

class DFtrans
{
	public:	
	Mat Trans(Mat img)
	{
		Mat img_gry,cmplx,dft_im,mgn;
		cvtColor(img,img_gry,CV_BGR2GRAY);
		
		Mat pad[] = {Mat_<float>(img_gry),Mat::zeros(img_gry.size(),CV_32F)};
		merge(pad,2,cmplx);
		dft(cmplx,dft_im,DFT_SCALE|DFT_COMPLEX_OUTPUT);
		split(dft_im,pad);
		magnitude(pad[0],pad[1],pad[0]);
		mgn = pad[0];
		mgn += Scalar::all(1);
		log(mgn,mgn);
		mgn = mgn(Rect(0,0,mgn.rows & -2 , mgn.cols & -2));
		
		int cx0 = mgn.rows/2;
		int cy0 = mgn.cols/2;
		
		Mat q00(mgn,Rect(0,0,cx0,cy0));
		Mat q01(mgn,Rect(cx0,0,cx0,cy0));
		Mat q02(mgn,Rect(0,cy0,cx0,cy0));
		Mat q03(mgn,Rect(cx0,cy0,cx0,cy0));
	
	
		Mat tmp1;
	
		q00.copyTo(tmp1);
		q03.copyTo(q00);
		tmp1.copyTo(q03);

		q01.copyTo(tmp1);
		q02.copyTo(q01);
		tmp1.copyTo(q02);
		
		
		return mgn;
	}
	
	
};
