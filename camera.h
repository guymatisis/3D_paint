//
// Created by guy on 10/4/18.
//

#ifndef INC_3D_PAINT_CAMERA_H
#define INC_3D_PAINT_CAMERA_H

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <cfenv>
using namespace cv;
using namespace std;
class camera {
public:
    int cam_num;
    char *stream_location;
    int usb_location;
    camera()
    {

    }
};


#endif //INC_3D_PAINT_CAMERA_H
