//
// Created by guy on 10/28/18.
//
#include <vector>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <pybind11/embed.h>
namespace py = pybind11;

using namespace std;
using namespace cv;
void estimate_error()
{
    double z=.85; //estimate error for 85 cm
    double b= .25; //baseline of 25 cm
    double f1 =1440;//measured focal length of camera 1
    py::scoped_interpreter guard{};
    py::module error_plot = py::module::import("error_plot");
    double d= f1*b/z; //disparity
    double sb = .01; //uncertainty for baseline= 1cm
    double sf = 10;   //uncertainty for focal length =100 pixel
    int nb=20,nf=12;
   double bvals[nb];
   double fvals[nf];

    for (int k = 0; k <=nb; ++k) { //15-35 including
        bvals[k] = (.15 + (double)k*(.01));
    }
    for (int k = 0; k <= nf; ++k) {//800-2000
        fvals[k] = (800 + (100*k));
    }

    double zs[nb+1][nf+1];
    double j[3];
    double Cx[3][3];
    double Cz;
    double j_cx[2];
    double f;

    for (int i = 0; i <=nb; ++i) {
         b= bvals[i];
        for (int k = 0; k <= nf; ++k) {
             f=fvals[k];
             d=f*b/z;
            j[0]= (double)b/d;
            j[1]= (double)f/d;
            j[2]=(double) -((f*b)/(d*d));
            Cx[1][1]=sb*sb;
            Cx[2][2]=sf*sf;

            j_cx[0]=j[1]*Cx[1][1];
            j_cx[1]=j[2]*Cx[2][2];
            Cz= j_cx[0]*j[1] +j_cx[1]*j[2];

            zs[i][k] =sqrt(Cz);
        }

    }
    for (int l = 0; l <=nb ; ++l) {
        error_plot.attr("add_x")(bvals[l]);
    }
    for (int l = 0; l <=nf ; ++l) {
        error_plot.attr("add_y")(fvals[l]);
    }

    for (int l = 0; l <=nb ; ++l) {
        error_plot.attr("add_row")();
        for (int k = 0; k <=nf ; ++k) {
            error_plot.attr("add_z")(l,zs[l][k]);
            cout<<zs[l][k]<<" ";
        }
        cout<<endl;
    }
    error_plot.attr("error_plot")(nb+1,nf+1);
    error_plot.attr("average_variance")();
    error_plot.attr("measured_plot")();
}