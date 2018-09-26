import pandas as pd
import numpy as np

import matplotlib.pyplot as plt
import imageio

#
# Importing data
#
df = pd.DataFrame.from_csv("./build/EuroOptExample_sample.csv",sep=';',index_col=None)

#
# Taking market and data ids
#
opt_ids = list(df['Option'].unique())
opt_ids = list(df['Market'].unique())

#
# Plottig
#
fig, axes = plt.subplots(1,3,figsize=(15,6))
for i,(opt1,opt2) in enumerate(zip(opt_ids[:-1:2],opt_ids[1::2])):
    temp = df[df['Option'] == opt1].set_index('Market')
    axes[i].plot(temp['FDM'],'ro',label='Analytic ' + opt1)
    axes[i].plot(temp['FDM'],'kx',markersize=10,label='FDM ' + opt1)

    temp = df[df['Option'] == opt2].set_index('Market')   
    axes[i].plot(temp['FDM'],'bo',label='Analytic ' + opt2)
    axes[i].plot(temp['FDM'],'kx',markersize=10,label='FDM ' + opt2)
    
    axes[i].legend()
    axes[i].set_xlabel('Market')
    axes[i].set_ylabel('Price')    
plt.savefig('EuroOptExample.png',format='png')

df = pd.DataFrame.from_csv("./build/EuroOptExample_solution.csv",sep=';',index_col=None)
df['S'] =[np.exp(S) for S in df['S']]
df = df[(df['S'] < 2.0) & (df['S'] > 0.5)]
time = sorted(list(set(df['T'].tolist())))


def plot_for_offset(data,t):
    temp = data[data['T']==t]
    x = temp['S'].tolist()
    f = temp['f'].tolist()
    
    temp = data[data['T']==time[0]]
    xend = temp['S'].tolist()
    fend = temp['f'].tolist()
    
    temp = data[data['T']==time[-1]]
    xst = temp['S'].tolist()
    fst = temp['f'].tolist()
    
    fig, ax = plt.subplots(figsize=(6,4))
    ax.plot(x, f, 'r-',label='Solution')
    ax.plot(xend, fend, 'k--',label='Value (t=0)')
    ax.plot(xst, fst, 'k-',label='Payoff (t=T)')
    
    ax.grid()
    
    plt.legend()
    plt.xlabel('Spot')
    plt.ylabel('Value of option')
    ax.set(title='time =' + str(round(t,2)))
    fig.canvas.draw()
    image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
    image = image.reshape(fig.canvas.get_width_height()[::-1] + (3,))

    return image

imageio.mimsave('EuroOptExample_solution.gif', [plot_for_offset(df,t) for t in reversed(time)], fps=20)