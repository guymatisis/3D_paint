#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "camera.h"
#include "calibration.h"
#include "object_detection.h"
#include "compute_3d_points.h"
#include "point_2d.h"
#include "point_3d.h"
#include "error_estimation.h"
using namespace std;
using namespace cv;
#include <pybind11/embed.h>
namespace py = pybind11;
vector <point_3d> points_3d;
void get_points(camera *cam1,camera *cam2);
void calibrate(camera *cam1,camera *cam2);



//---------------------------------MAIN-------------------------------------------
int main()
{
    camera *cam1= new camera();
    camera *cam2= new camera();
    cam1->cam_num=1;            //xiaomi
    cam2->cam_num=2;            //webcam
    cam1->stream_location="http://192.168.42.129:5500/camera";
    cam2->usb_location=0;

    calibrate(cam1,cam2);       //calibration
    get_points(cam1,cam2);
    estimate_error();
return 0;

}


void calibrate(camera *cam1,camera *cam2)
{
    char user_input1,user_input2;
    cout<<"Do you want to calibrate camera 1. enter 1 for yes, anything else for no."<<endl;
    cin>>user_input1;
    if(user_input1=='1') {
        calibrate(cam1);
    }
    cout<<"Do you want to calibrate camera 2. enter 1 for yes, anything else for no."<<endl;
    cin>>user_input2;
    if(user_input2=='1') {
        calibrate(cam2);
    }
}


void get_points(camera *cam1,camera *cam2) {

    py::scoped_interpreter guard{};                 //starts python interpreter
    py::module plot = py::module::import("plot");  //imports python plotting module
    plot.attr("plot_cams")();                       //sets axis and plots cameras at (0,0,0) and (25,0,0)

    vector<point_3d> smoothed_points;
    int scale =3;
    Mat img1, img2,img1_resize, img2_resize,img1_undistort,img2_undistort;
    point_2d p1(0,0),p2(0,0);
    point_3d p(0,0,0);
    int sum_x,sum_y,sum_z;

    //-------------------retreive camera calibration -------------------
    Mat intrinsic1 =Mat::zeros(3, 3, CV_32FC1);
    Mat intrinsic2 =Mat::zeros(3, 3, CV_32FC1);
    Mat distCoeffs1 = Mat::zeros(8, 1, CV_64F);
    Mat distCoeffs2 = Mat::zeros(8, 1, CV_64F);
    FileStorage  fs1("/home/guy/CLionProjects/3d_paint/cam1_calib.xml", FileStorage::READ);
    FileStorage fs2("/home/guy/CLionProjects/3d_paint/cam2_calib.xml", FileStorage::READ);
    fs1["intrinsic"]>>intrinsic1;
    fs2["intrinsic"]>>intrinsic2;
    fs1["disCoeffs"]>>distCoeffs1;
    fs2["disCoeffs"]>>distCoeffs2;
    fs1.release();
    fs2.release();

    //-------------------video control-------------------
    VideoCapture cap1(cam1->stream_location);
    VideoCapture cap2(cam2->usb_location);
    if (!cap1.isOpened() || !cap2.isOpened())  // if not success, exit program
        {
            cout << "Cannot open the object video" << endl;
            return;
        }
    //------read images------
    cap1>>img1;
    cap2>>img2;
    if(img1.empty() || img2.empty()){
        cout<<"IMAGES EMPTY"<<endl;
        return;
    }

    //------record size of images------
    point_2d image1_size(0,0);
    point_2d image2_size(0,0);
    image1_size.x=img1.size().width;
    image1_size.y=img1.size().height;
    image2_size.x=img2.size().width;
    image2_size.y=img2.size().height;



    //-------------MAIN LOOP------------------
    while (1) {
        for (int i = 0; i < 11; ++i) { //burns images to account for delay in stream
        cap1>>img1;
        }
        cap2>>img2;
        //------------undistort images and resize for viewing ------------
        undistort(img1, img1_undistort, intrinsic1, distCoeffs1);
        undistort(img2, img2_undistort, intrinsic2, distCoeffs2);;
        resize(img1_undistort, img1_resize, Size(img1.cols/scale, img1.rows/scale));
        resize(img2_undistort, img2_resize, Size(img2.cols/scale, img2.rows/scale));
        imshow("xiaomi", img1_resize);
        int key = waitKey(1);
        imshow("webcam", img2_resize);
        int key2 = waitKey(1);

        p1 = obj_detect(img1);  //detect object in images.
        p2 = obj_detect(img2);
        if (p1.x != -1 and p2.x != -1) {  // '-1' denoes object not detected.
            p = compute_3d_points(p1, p2, image1_size, image2_size,intrinsic1,intrinsic2);//get 3d points
            points_3d.push_back(p);

            int num_pts=5;
            //  ------------plot 3d point------------
            if (points_3d.size() > num_pts) {
                //------------smoothing------------
                sum_x =sum_y=sum_z=0;
                for (int i = points_3d.size()-1; i >= points_3d.size()-num_pts; --i) {
                   sum_x = sum_x+points_3d[i].x_3d;
                    sum_y += points_3d[i].y_3d;
                    sum_z += points_3d[i].z_3d;
                }
                //----PRINT POINTS------
                cout<<"avg x: "<<sum_x/num_pts<<", avg y: "<<sum_y/num_pts<<", avg_z: "<<sum_z/num_pts<<endl; //display smoothed points
                smoothed_points.push_back(point_3d(sum_x/num_pts,sum_y/num_pts,sum_z/num_pts));
                if (smoothed_points.size() > 2) {
                                        //---------plot---------
                    int last_item=smoothed_points.size() - 1;
                    plot.attr("plot")(smoothed_points[last_item].x_3d,smoothed_points[last_item-1].x_3d,
                                      smoothed_points[last_item].z_3d,smoothed_points[last_item-1].z_3d,
                                      smoothed_points[last_item].y_3d,smoothed_points[last_item-1].y_3d);
                }
            }
        }
        if(waitKey(1)==13){     //breaks on enter.
            break;
        }
    }

}