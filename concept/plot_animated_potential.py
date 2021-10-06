import numpy as np
import matplotlib.pyplot as pl
import matplotlib.animation as an
import scipy.special as sp

def s(t,mode,p):
	t0 = (p.Tmax-p.Tmin)/2+p.Tmin
	t1 = p.sr*(t-t0)
	if mode=="tanh":
		res = 0.5*np.tanh(t1)+0.5
		return res
	elif mode=="erf":
		res = 0.5*sp.erf(t1)+0.5
		return res
	elif mode=="arctan":
		res = 0.5*np.arctan(t1)/(np.pi/2)+0.5
		return res
	else:
		return 0

def b(x,mode,p):
	if mode=="gauss":
		res = p.b0/(p.sb*np.sqrt(2*np.pi))
		res*= np.exp(-x**2/(2*p.sb**2))
		return res
	elif mode=="lorentz":
		res = p.b0/np.pi*p.sb/(x**2+p.sb**2)
		return res
	else:
		return 0
		



class par:
	def __init__(self, m, w, sb, b0, sr, Tmin, Tmax):
		self.m = m
		self.w = w
		self.w2 = w*w
		self.sb = sb
		self.b0 = b0
		self.sr = sr
		self.Tmin = Tmin
		self.Tmax = Tmax


step_mode = "tanh"
barrier_mode = "gauss"

Tsec = 2
Tfps = 10
Tpts = Tsec*Tfps
Tmin = 0
Tmax = 8*np.pi

T = np.linspace(Tmin, Tmax, num=Tpts, endpoint=False)


Xpts = 10
Xlen = 8
Xmin = -Xlen
Xmax = Xlen

X = np.linspace(Xmin, Xmax, num=Xpts)



P = np.zeros((Tpts,Xpts))
S = np.zeros(Tpts)


p = par(1,1,0.5,20,10,Tmin,Tmax)


for i1 in range(Tpts):
	for i2 in range(Xpts):
		P[i1,i2]=p.m*p.w2/2*X[i2]**2
		P[i1,i2]+=b(X[i2],barrier_mode,p)*s(T[i1],step_mode,p)
	S[i1]=s(T[i1],step_mode,p)

fig, axs = pl.subplots(1,2)



line0, = axs[0].plot(T,S)
scat0, = axs[0].plot(T[0],S[0],'o')

line1, = axs[1].plot(X, P[0]) 


axs[0].set_xlabel(r'$t$')
axs[0].set_ylabel(r'$s$')
title0 = axs[0].text(
	0.0,
	0.9,
	r'$t=$'+str(np.around(T[0], decimals=2))
)


axs[1].set_xlabel(r'$x$')
axs[1].set_ylabel(r'$V$')

objects = [line0,scat0,title0,line1]


def init(): 
	objects[3].set_data(X, P[0])
	axs[1].set_ylim([np.amin(P),np.amax(P)])
	return objects


def animate(i):
	objects[1].set_xdata([T[i]])
	objects[1].set_ydata([S[i]])
	objects[3].set_ydata(P[i])
	objects[2].set_text(r'$t=$'+str(np.around(T[i], decimals=2)))
	return objects
   
anim = an.FuncAnimation(
	fig,
	animate,
	init_func = init,
	frames = Tpts,
	interval = 20,
	blit = True
)

pl.show()

'''   
anim.save(
	'continuousSineWave.mp4', 
	writer = 'ffmpeg',
	fps = 30
)
'''
