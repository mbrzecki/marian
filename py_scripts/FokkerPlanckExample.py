import pandas as pd
import numpy as np

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter

df = pd.DataFrame.from_csv(r"C:\Unix\home\OEM\fdm\build\fokker_planck_equation.csv",sep=';',index_col=None)
ylim = max(df['f'])
time = sorted(list(set(df['T'].tolist())))


temp1 = df[df['T']==time[0]]
temp2 = df[df['T']==time[-1]]
plt.plot(temp1['S'],temp1['f'])

plt.savefig('FokkerPlackExampleInit.png',format='png')

import imageio

def plot_for_offset(data,t):
    temp = data[data['T']==t]
    x = temp['S'].tolist()
    f = temp['f'].tolist()
    temp = data[data['T']==0.8]
    xend = temp['S'].tolist()
    fend = temp['f'].tolist()
    temp = data[data['T']==0.0]
    xst = temp['S'].tolist()
    fst = temp['f'].tolist()
    fig, ax = plt.subplots(figsize=(6,4))
    ax.plot(temp1['S'],temp1['f'],'--',c='lightgray')
    ax.plot(x, f, 'k-')

    ax.grid()

    ax.set_ylim(0, ylim)
    ax.set(title='time =' + str(round(t,2)))
    fig.canvas.draw()
    image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
    image = image.reshape(fig.canvas.get_width_height()[::-1] + (3,))

    return image

imageio.mimsave(r'C:\Unix\home\OEM\fdm\build\fokkerPlackExample.gif', [plot_for_offset(df,t) for t in time], fps=20)