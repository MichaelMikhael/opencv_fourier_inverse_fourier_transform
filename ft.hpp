#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/video/tracking.hpp>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <opencv2/contrib/contrib.hpp>
#include <opencv/cv.h>
#include <opencv/cv.hpp>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>
#include <opencv/cv.h>
#include <opencv/cv.hpp>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace cv;
using namespace std;

Mat blnk = imread("/home/mmwm/old_mint/blnk.jpg");
Mat mask0,mask1,mask2,mask3,mult,rst,rslt_b;

Mat mcm = imread("/home/mmwm/old_mint/mg.jpg");
Mat sky = imread("/home/mmwm/old_mint/sky.jpg");
Mat checker = imread("/home/mmwm/old_mint/grid0.jpg");
Mat crp = imread("/home/mmwm/old_mint/crp.jpg");
Mat blk = imread("/home/mmwm/old_mint/blk.jpg");
Mat mask;
Mat rslt,rslt0,rslt_gry,sky_gry;
Mat dftt;

Mat checker_not,checker_gry; 

Mat v_rslt,sky_check,sc_gry;

Mat cmplx,cmplx0,s,s_u,mg,i_dft,i_dft0,cropped,i_im,i_im0,mgc;

Mat crp_not;
//bitwise_not(crp,crp,crp_not);
Mat inv;
Mat r,crp_8,mm,mcm0,mg0,r_gry,blk_gry;

Vec3b in_col;
Vec2b in_val;
uchar val0;
float val;

Mat im;

Mat s0,s00;

VideoCapture v(0);

int pp,ppp,pp0,pp1;

void on_trackbar(int pos)
{
	int pp=pos;
}
void on_trackbar0(int pos)
{
	int ppp=pos;
}
void on_trackbar1(int pos)
{
	int pp0=pos;
}
void on_trackbar2(int pos)
{
	int pp1=pos;
}







class Ftrans
{
public:
Ftrans(const char* imPath, int Length, int Width, bool Filter){  

Mat img =imread(imPath);
Mat ft;

int l = Length;
int w = Width; 

Mat final_img;

while(1){

v>>im;
resize(im,im,Size(l,w));
resize(blnk,blnk,Size(l,w));
resize(checker,checker,Size(l,w));

add(im,blnk,rst,mask0,0);

bitwise_not(rst,rst,rslt_b);
add(rst,sky,v_rslt,mask1,0);

final_img = v_rslt;

if(l != w)
{
cout<<"Square images only"<<endl;
break;
}

if(Filter==1)
{
	add(v_rslt,checker,final_img,mask2,0);
}

	cvNamedWindow("mov",1);
	cvCreateTrackbar("P1","mov",&pp,500,on_trackbar);
	
	cvCreateTrackbar("P2","mov",&pp0,500,on_trackbar1);

	cvtColor(final_img,sc_gry,CV_BGR2GRAY);
	
	Mat pad[] = {Mat_<float>(sc_gry),Mat::zeros(sc_gry.size(),CV_32F)};
	merge(pad,2,cmplx);
	
	dft(cmplx,s,DFT_SCALE|DFT_COMPLEX_OUTPUT);
	
	s0 = s.clone();
	s00 = s0.clone();
	split(s,pad);
	magnitude(pad[0],pad[1],pad[0]);
	
	mg = pad[0];
	mg +=Scalar::all(1);
	log(mg,mg);
	
	
	mg = mg(Rect(0,0,mg.rows & -2 , mg.cols & -2));
	
	int cx = mg.rows/2;
	int cy = mg.cols/2;

	Mat q0(mg,Rect(0,0,cx,cy));
	Mat q1(mg,Rect(cx,0,cx,cy));
	Mat q2(mg,Rect(0,cy,cx,cy));
	Mat q3(mg,Rect(cx,cy,cx,cy));

	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	
	Mat tmp0;
	
	int sx = s0.rows/2;
	int sy = s0.cols/2;
	
	Mat q00(s0,Rect(0,0,sx,sy));
	Mat q01(s0,Rect(sx,0,sx,sy));
	Mat q02(s0,Rect(0,sy,sx,sy));
	Mat q03(s0,Rect(sx,sy,sx,sy));
	
	
	q00.copyTo(tmp0);
	q03.copyTo(q00);
	tmp0.copyTo(q03);

	q01.copyTo(tmp0);
	q02.copyTo(q01);
	tmp0.copyTo(q02);
	
	s00=Scalar::all(0);

   for(int i=0;i<=s0.rows;i++)
    {
		for(int j=0;j<=s0.cols;j++)
		{
			if(i<500-pp && j<500-pp){
			if(i>pp0 && j>pp0){
			 s00.at<double>(i,j) = s0.at<double>(i,j);
			}
			}
		}
	}
	rectangle(mg,Point(pp0,pp0),Point(500-pp,500-pp),Scalar(255,0,0),1,8,0);

	idft(s00,i_dft0,DFT_INVERSE|DFT_REAL_OUTPUT);
	normalize(i_dft0,i_dft0,0,1,CV_MINMAX);
	i_dft0.convertTo(i_im0,CV_8U,255);

imshow("im",mg);
imshow("inverse_dft",i_dft0);
waitKey(30);
}
waitKey(0);
}

