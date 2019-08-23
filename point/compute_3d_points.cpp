//
// Created by guy on 10/7/18.
//

#include "compute_3d_points.h"
#include "point_2d.h"

point_3d compute_3d_points(point_2d p1,point_2d p2,point_2d image1_size,point_2d image2_size,Mat intrinsic1,Mat intrinsic2)
{
    //---------------------compute 3D points-----------------------
    vector<point_3d*> points;
    float radian =180/3.1415;
    float angle_cam1,angle_cam2;
    int b=250;                          //250 mm
    float x_center1 = image1_size.x/2;
    float y_center1 = image1_size.y/2;
    float x_center2 = image2_size.x/2;
    float z;
    float x1,x2;
    float x,y,y1;

    float focal_length_x_cam1= intrinsic1.at<double>(0,0);
    float focal_length_x_cam2= intrinsic2.at<double>(0,0);
    float focal_length_y_cam1= intrinsic1.at<double>(1,1);
    float focal_length_y_cam2= intrinsic2.at<double>(1,1);

    x1=(float)p1.x-x_center1;
    y1 =(float)p1.y-y_center1;
    x2=-((float)p2.x-x_center2);
    angle_cam1 = 1.57 - atan(x1/ focal_length_x_cam1);// in radians
    angle_cam2 = 1.57 - atan(x2 / focal_length_x_cam2);// in radians

    //-----------X,Y,Z EQUATIONS------------
    z= b/((1/(tan(angle_cam1))) + (1/(tan(angle_cam2))));
    x = (z*x1)/focal_length_x_cam1;
    y = -(z*y1)/focal_length_y_cam1; //negative to flip it right side up.

    point_3d new_point(x,y,z);
    return new_point;
}