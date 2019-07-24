Written by
Guy Matisis

This project creates a stereo-vision system with a laptop and two webcams. The stereo-vision system was then used to track a red ball in three dimensions and plot its path in real time in attempt to 'paint' in 3d with the ball. The PDF file explains the project in depth.
The project was predominantly written in c/c++, but there is also a small section written in python in order to utilize some plotting libraries.

The important files included:
1. main - controls the overall flow of the project.
2.calibration  - used to calibrate the two webcameras. was done in real time.
3.compute_3d_points - the mathematical equations of stereovision are used to compute X,Y,Z.
4.error -estimation -  perceived location is compared to actual location.
5.object detection -  the ball is detected and its X,Y coordinates are found.




