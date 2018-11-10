from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np
from numpy import array

a=[]
b=[]
c=[]


real_x_0_20=[0,10,20]
real_x_10_10=[-10,0,10]
real_y_8_12=[8,-2,-12]
real_z_75=[75,75,75,75,75,75,75,75,75]
real_z_85=[85,85,85,85,85,85,85,85,85]
real_z_95=[95,95,95,95,95,95,95,95,95]

measured_x_75=[1,10,20,1,10,20,2,10,20]
measured_x_85=[-5,3,12,-5,3,12,-6,3,12]
measured_x_95=[-8,1,11,-8,2,10,-8,1,10]

measured_y_75=[8,5,5,-5,-5,-5,-13,-14,-15]
measured_y_85=[3,3,3,-6,-5,-5,-15,-15,-16]
measured_y_95=[2,2,2,-7,-7,-7,-16,-16,-16]

measured_z_75=[62,63,63,63,63,64,64,63,63]
measured_z_85=[75,75,75,73,73,73,71,73,73]
measured_z_95=[90,83,85,84,81,82,83,81,81]



real_x=[0,10,20,0,10,20,0,10,20,-10,0,10,-10,0,10,-10,0,10,-10,0,10,-10,0,10,-10,0,10]
real_y=[8,8,8,-2,-2,-2,-12,-12,-12,8,8,8,-2,-2,-2,-12,-12,-12,8,8,8,-2,-2,-2,-12,-12,-12]
real_z=[75,75,75,75,75,75,75,75,75,85,85,85,85,85,85,85,85,85,95,95,95,95,95,95,95,95,95]


def add_x(x):
	a.append(x)
def add_y(y):
	b.append(y)
def add_row():
	c.append([])
def add_z(row,z):
	c[row].append(z)
def error_plot(dim1,dim2):
	fig = plt.figure()
	ax = fig.gca(projection='3d')
	ax.set_xlabel('Focal Length')
	ax.set_ylabel('BaseLine')
	ax.set_zlabel('Z Uncertainty')
	s,t= np.meshgrid(b,a)
	nc =np.array(c)
	nc = nc.reshape(dim1,dim2)
	 #Plot the surface.
	surf = ax.plot_surface(s,t,nc, cmap=cm.coolwarm,linewidth=0, antialiased=False)
	plt.show()

def measured_plot():
	fig = plt.figure()
	ax1 = fig.add_subplot(131,projection='3d')
	ax2 = fig.add_subplot(132, projection='3d')
	ax3 = fig.add_subplot(133, projection='3d')
	
	
	#-------ACTUAL LOCATIONS----------
	s,t= np.meshgrid(real_x_0_20,real_y_8_12)
	q,r=np.meshgrid(real_x_10_10,real_y_8_12)
	z_75 =np.array(real_z_75)
	z_75= z_75.reshape(3,3)
	z_85 =np.array(real_z_85)
	z_85= z_85.reshape(3,3)
	z_95 =np.array(real_z_95)
	z_95= z_95.reshape(3,3)
	
	#--------MEASURED LOCATIONS---------
		#--------75 cm----------
	m_x_75 =np.array(measured_x_75)
	m_x_75= m_x_75.reshape(3,3)
	m_y_75 =np.array(measured_y_75)
	m_y_75= m_y_75.reshape(3,3)
	m_z_75 =np.array(measured_z_75)
	m_z_75= m_z_75.reshape(3,3)
	#--------85 cm----------
	m_x_85 =np.array(measured_x_85)
	m_x_85= m_x_85.reshape(3,3)
	m_y_85 =np.array(measured_y_85)
	m_y_85= m_y_85.reshape(3,3)
	m_z_85 =np.array(measured_z_85)
	m_z_85= m_z_85.reshape(3,3)		
	#--------95 cm----------
	m_x_95 =np.array(measured_x_95)
	m_x_95= m_x_95.reshape(3,3)
	m_y_95 =np.array(measured_y_95)
	m_y_95= m_y_95.reshape(3,3)
	m_z_95 =np.array(measured_z_95)
	m_z_95= m_z_95.reshape(3,3)
	#Plot the surface.
	surf = ax1.plot_surface(s,t,z_75, cmap=cm.coolwarm,linewidth=0, antialiased=False)
	surf = ax1.plot_surface(m_x_75,m_y_75,m_z_75, cmap=cm.coolwarm,linewidth=0, antialiased=False)
	
	
	surf = ax2.plot_surface(q,r,z_85, cmap=cm.coolwarm,linewidth=0, antialiased=False)
	surf = ax2.plot_surface(m_x_85,m_y_85,m_z_85, cmap=cm.coolwarm,linewidth=0, antialiased=False)

	surf = ax3.plot_surface(q,r,z_95, cmap=cm.coolwarm,linewidth=0, antialiased=False)
	surf = ax3.plot_surface(m_x_95,m_y_95,m_z_95, cmap=cm.coolwarm,linewidth=0, antialiased=False)
	plt.show()

def average_variance():
	#------------AVERAGE ERROR-------------
	# ---Xs---
	x_sum=0.0
	for i in range(3):
		x_sum+=  0 - measured_x_75[0+(i*3)]
		x_sum+= 10 - measured_x_75[1+(i*3)]
		x_sum+= 20 - measured_x_75[2+(i*3)]
	for i in range(3):
		x_sum+=-10 - measured_x_85[0+(i*3)]
		x_sum+=  0 - measured_x_85[1+(i*3)]
		x_sum+= 10 - measured_x_85[2+(i*3)]
		x_sum+=-10 - measured_x_95[0+(i*3)]
		x_sum+=  0 - measured_x_95[1+(i*3)]
		x_sum+= 10 - measured_x_95[2+(i*3)]
	avg_x=x_sum/27
	print("X AVG ERROR: ",avg_x)

	y_sum=0.0	
	for i in range(3):
		y_sum+=  8 - measured_y_75[0+i]
		y_sum+= -2 - measured_y_75[3+i]
		y_sum+=-12 - measured_y_75[6+i]
		y_sum+=  8 - measured_y_85[0+i]
		y_sum+= -2 - measured_y_85[3+i]
		y_sum+=-12 - measured_y_85[6+i]
		y_sum+=  8 - measured_y_95[0+i]
		y_sum+= -2 - measured_y_95[3+i]
		y_sum+=-12 - measured_y_95[6+i]
	avg_y =y_sum/27
	print("Y AVG ERROR: ",avg_y)

	z_sum=0.0
	for i in range(9):
		z_sum+= 75 - measured_z_75[i]
		z_sum+= 85 - measured_z_85[i]
		z_sum+= 95 - measured_z_95[i]
	avg_z=z_sum/27
	print("Z AVG ERROR: ",avg_z)



#-------------VARIANCE---------------


	# ---Xs---
	x_var=0.0
	for i in range(3):
		x_var+=  ((0 - measured_x_75[0+(i*3)]) - avg_x)**2
		x_var+= ((10 - measured_x_75[1+(i*3)]) - avg_x)**2
		x_var+= ((20 - measured_x_75[2+(i*3)]) - avg_x)**2
	for i in range(3):
		x_var+=((-10 - measured_x_85[0+(i*3)]) - avg_x)**2
		x_var+= (( 0 - measured_x_85[1+(i*3)]) - avg_x)**2
		x_var+= ((10 - measured_x_85[2+(i*3)]) - avg_x)**2
		x_var+=((-10 - measured_x_95[0+(i*3)]) - avg_x)**2
		x_var+= (( 0 - measured_x_95[1+(i*3)]) - avg_x)**2
		x_var+= ((10 - measured_x_95[2+(i*3)]) - avg_x)**2
	print("X ERROR VARIANCE: ",x_var/27)

	y_var=0.0
	for i in range(3):
		y_var+=  ((8 - measured_y_75[0+i]) - avg_y)**2
		y_var+= ((-2 - measured_y_75[3+i]) - avg_y)**2
		y_var+=((-12 - measured_y_75[6+i]) - avg_y)**2
		y_var+=  ((8 - measured_y_85[0+i]) - avg_y)**2
		y_var+= ((-2 - measured_y_85[3+i]) - avg_y)**2
		y_var+=((-12 - measured_y_85[6+i]) - avg_y)**2
		y_var+=  ((8 - measured_y_95[0+i]) - avg_y)**2
		y_var+= ((-2 - measured_y_95[3+i]) - avg_y)**2
		y_var+=((-12 - measured_y_95[6+i]) - avg_y)**2

	print("Y ERROR VARIANCE: ",y_var/27)

	z_var=0.0
	for i in range(9):
		z_var+= ((75 - measured_z_75[i]) - avg_z)**2
		z_var+= ((85 - measured_z_85[i]) - avg_z)**2
		z_var+= ((95 - measured_z_95[i]) - avg_z)**2
	print("Z ERROR VARIANCE: ",z_var/27)

