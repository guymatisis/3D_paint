#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "camera.h"
#include "point_3d.h"
#include "point_2d.h"
#include <stdio.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <cfenv>
using namespace cv;
using namespace std;


template<typename T> void pop_front(std::vector<T>& vec)
{
    assert(!vec.empty());
    vec.front() = std::move(vec.back());
    vec.pop_back();
}

point_2d obj_detect(Mat img)
{
int scale=3;

    //-----------------------------------



    //  resize(imgTmp, imgTmp, Size(imgTmp.cols/scale, imgTmp.rows/scale));

//    namedWindow("Control", WINDOW_AUTOSIZE); //create a window called "Control"
//
    int iLowH = 170;
    int iHighH = 179;

    int iLowS = 150;
    int iHighS = 255;

    int iLowV = 60;
    int iHighV = 255;
//
//    //Create trackbars in "Control" window
//    createTrackbar("LowH", "Control", &iLowH, 255); //Hue (0 - 179)
//    createTrackbar("HighH", "Control", &iHighH, 255);
//
//    createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
//    createTrackbar("HighS", "Control", &iHighS, 255);
//
//    createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
//    createTrackbar("HighV", "Control", &iHighV, 255);


    //Create a black image with the size as the camera output
    Mat imgLines = Mat::zeros( img.size(), CV_8UC3 );
    Mat imgOriginal;
    Mat imgUndistorted;
    imgOriginal=img;




      //  resize(imgOriginal,imgOriginal, Size(imgOriginal.cols/scale, imgOriginal.rows/scale));
  //      undistort(imgOriginal, imgUndistorted, cam->intrinsic,cam->distCoeffs);

        Mat imgHSV;
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

        Mat imgThresholded,thresh_resize;

        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

        //morphological opening (removes small objects from the foreground)
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3) ));
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );

        //morphological closing (removes small holes from the foreground)
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
        resize(imgThresholded, thresh_resize, Size(imgThresholded.cols/scale, imgThresholded.rows/scale));
        imshow("",thresh_resize); //show the thresholded image
        int key = waitKey(0);
        //Calculate the moments of the thresholded image
        Moments oMoments = moments(imgThresholded);

        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double dArea = oMoments.m00;

        // if the area <= 5000, I consider that the there are no object in the image and it's because of the noise, the area is not zero
        if (dArea > 5000)
        {
            //calculate the position of the ball
            int posX = dM10 / dArea;
            int posY = dM01 / dArea;
            point_2d return_point(posX,posY);
          return(return_point);
        }else
        {

            point_2d return_point(-1,-1);
            return(return_point);
        }

        imgUndistorted = imgUndistorted + imgLines;
        imgOriginal= imgOriginal + imgLines;
        imshow("Original", imgOriginal); //show the original image
        waitKey(30) ; //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop





}