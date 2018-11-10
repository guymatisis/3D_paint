import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax1 = fig.add_subplot(121, projection='3d')
ax2 = fig.add_subplot(122, projection='3d')
ax1.set_xlabel('X')
ax1.set_ylabel('Z')
ax1.set_zlabel('Y')
ax2.set_xlabel('X')
ax2.set_ylabel('Z')
ax2.set_zlabel('Y')
def plot_cams():#plot cameras
    #cam1 cube
    ax1.plot([0,5,5,0,0,0,5,5,5,5,5,5,0,0,0,0],[0,0,5,5,0,0,0,0,0,5,5,5,5,5,5,0],[0,0,0,0,0,5,5,0,5,5,0,5,5,0,5,5])
    #cam2 cube
    ax1.plot([25,30,30,25,25,25,30,30,30,30,30,30,25,25,25,25],[0,0,5,5,0,0,0,0,0,5,5,5,5,5,5,0],[0,0,0,0,0,5,5,0,5,5,0,5,5,0,5,5])
    ax1.text(0, 0, 10, "cam1", color='red')
    ax1.text(25, 0, 10, "cam2", color='red')
    ax1.set_xlim(-200,800)
    ax1.set_ylim(300,1300)#REALLY Z
    ax1.set_zlim(-200,800)#REALLY Y
    ax1.view_init(elev=0, azim=90)

    #cam1 cube
    ax2.plot([0,5,5,0,0,0,5,5,5,5,5,5,0,0,0,0],[0,0,5,5,0,0,0,0,0,5,5,5,5,5,5,0],[0,0,0,0,0,5,5,0,5,5,0,5,5,0,5,5])
    #cam2 cube
    ax2.plot([25,30,30,25,25,25,30,30,30,30,30,30,25,25,25,25],[0,0,5,5,0,0,0,0,0,5,5,5,5,5,5,0],[0,0,0,0,0,5,5,0,5,5,0,5,5,0,5,5])
    ax2.text(0, 0, 10, "cam1", color='red')
    ax2.text(25, 0, 10, "cam2", color='red')
    ax2.set_xlim(-200,800)
    ax2.set_ylim(300,1300)#REALLY Z
    ax2.set_zlim(-200,800)#REALLY Y
    ax2.view_init(elev=0, azim=0)
def plot(x1,x2,y1,y2,z1,z2):
    ax1.plot([x1,x2],[y1,y2],[z1,z2])
    ax2.plot([x1,x2],[y1,y2],[z1,z2])
    #ax1.scatter(x1,y1,z1)
    plt.pause(.001)