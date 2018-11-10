//
// Created by guy on 10/4/18.
//


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using namespace cv;
#include "camera.h"

//pop front of vector
template<typename T> void pop_front(std::vector<T>& vec)
{
    assert(!vec.empty());
    vec.front() = std::move(vec.back());
    vec.pop_back();
}

//calibration method
void calibrate(camera *cam) {
    int scale =4;               //resize image by factor of .5
    int numBoards = 30;         //num of images
    int numCornersHor = 7;      //horizontal checkerboard
    int numCornersVer = 5;      //vertical checkerboard
    int numSquares = numCornersHor * numCornersVer;
    Size board_sz = Size(numCornersHor, numCornersVer);
    int successes = 0;

//--- for video/image control---
    VideoCapture capture;
    vector <vector<Point3f>> object_points;
    vector <vector<Point2f>> image_points;
    vector <Point3f> obj;
    vector <Point2f> corners;
    Mat image,image_resize;
    Mat imageUndistorted,stam;
    Mat gray_image;

//---for calibration---
    vector<Mat> rvecs;
    vector<Mat> tvecs;
    Mat intrinsic = Mat(3, 3, CV_32FC1);  //intrinsic params
    intrinsic.ptr<float>(0)[0] = 1;
    intrinsic.ptr<float>(1)[1] = 1;
    Mat distCoeffs = Mat::zeros(8, 1, CV_64F);


    if(cam->cam_num==1)    //get stream depending on which camera
    {
        capture = VideoCapture(cam->stream_location);   //taken from web
        capture.set(CAP_PROP_BUFFERSIZE, 1);
    }else
    {
        capture = VideoCapture(cam->usb_location);      //taken from usb
    }
        capture >> image;
        for (int j = 0; j < numSquares; j++) {
            obj.push_back(Point3f(j / numCornersHor, j % numCornersHor, 0.0f));
        }



    //------------------MAIN LOOP------------------------------

    while (1) {
        cvtColor(image, gray_image, COLOR_BGR2GRAY);
        bool found = findChessboardCorners(image, board_sz, corners,
                                           CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FILTER_QUADS);
        if (found) {  //gray image/draw lines
            cornerSubPix(gray_image, corners, Size(11, 11), Size(-1, -1),
                         TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
            drawChessboardCorners(gray_image, board_sz, corners, found);
            resize(gray_image, image_resize, Size(image.cols / scale, image.rows / scale));
            imshow("win3", image_resize);
        } else {
            printf("not found.\n");
        }

            for (int i = 0; i < 59; ++i) {  //30fps: .5 per second
            capture >> stam;
            }
            capture >> image;
            if (image.empty()) {
                break;
            }
            resize(image, image_resize, Size(image.cols / scale, image.rows / scale));
            imshow("win1", image_resize);
            int key = waitKey(1)& 0xFF;
            if ((key == 13)) { break; }  //enter breaks loop.

            if (found) {        //found chessboard
                image_points.push_back(corners);
                object_points.push_back(obj);
                successes++;
                cout<<"SUCCESS: "<<successes<<endl;
                //----------undistort and show-----------------
                if (successes >= numBoards+1) {
                    pop_front(image_points);
                    pop_front(object_points);
                    double rms = calibrateCamera(object_points, image_points, image.size(), intrinsic,
                                                 distCoeffs, rvecs,
                                                 tvecs);
                    cout << "rms: " << rms << endl;  //display rms value should be between .2 -.5
                    undistort(image, imageUndistorted, intrinsic, distCoeffs);
                    resize(image, image_resize, Size(image.cols / scale, image.rows / scale));
                    imshow("win2", image_resize);
                    int key = waitKey(1);
                }


            }
        }
 capture.release();


    //store results
if(cam->cam_num==1)
{
    FileStorage fs1("/home/guy/CLionProjects/3d_paint/cam1_calib.xml", FileStorage::WRITE);
    fs1<<"intrinsic"<<intrinsic;
    fs1<<"disCoeffs"<<distCoeffs;
    fs1.release();
}else
{
    FileStorage fs1("/home/guy/CLionProjects/3d_paint/cam2_calib.xml", FileStorage::WRITE);
    fs1<<"intrinsic"<<intrinsic;
    fs1<<"disCoeffs"<<distCoeffs;
    fs1.release();
}




}