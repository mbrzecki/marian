import pandas as pd
import math as m

import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv(r'.\convergenceExample1.csv',';')
df.set_index('NS',inplace=True)

fig, axes = plt.subplots(1,2,figsize=(12,5))
for t in [col for col in df.columns if not col == 'Analytic' ]:
    axes[0].plot(df[t],label=t)

axes[0].plot(df['Analytic'],'k--')
axes[0].legend()
axes[0].set_xlabel('spatial steps')
axes[0].set_ylabel('price')

for t in [col for col in df.columns if not col == 'Analytic' ]:
    df[t + '_diff'] = abs(df[t] - df['Analytic'])

for t in [col for col in df.columns if col.endswith('diff') ]:
    axes[1].plot(df[t],label=t)
axes[1].set_xlabel('spatial steps')
axes[1].set_ylabel('diff price')
plt.savefig('convergence_spatial.png',format='png')

df = pd.read_csv(r'.\build\convergenceExample2.csv',';')
df.set_index('NT',inplace=True)


fig, axes = plt.subplots(1,2,figsize=(12,5))
for t in [col for col in df.columns if not col == 'Analytic' ]:
    axes[0].plot(df[t],label=t)

axes[0].set_xlabel('time steps')
axes[0].set_ylabel('price')
axes[0].plot(df['Analytic'],'k--')
axes[0].legend()

for t in [col for col in df.columns if not col == 'Analytic' ]:
    df[t + '_diff'] = abs(df[t] - df['Analytic'])
    
for t in [col for col in df.columns if col.endswith('diff') ]:
    axes[1].plot(df[t],label=t)

axes[1].set_xlabel('time steps')
axes[1].set_ylabel('diff price')
plt.savefig('convergence_time.png',format='png')