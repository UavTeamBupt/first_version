# -*- coding: utf-8 -*-
"""
Created on Thu Dec 24 13:25:45 2020

@author: 17115
"""

import numpy as np
import json
t={}
#各个节点的xyz坐标
x = np.linspace(0, 30, 30)
y = np.linspace(0, 30, 30)
z = np.linspace(0, 30, 30)
path=r"..\basicNodePosition.json"
with open(path)as fp:
    json_data = json.load(fp)

    print (json_data['basicNodePosition'])
    a=json_data['basicNodePosition']
    i=0
    for item in a:
        for(key,value) in item.items():
            x[i]=value[0]
            y[i]=value[1]
            z[i]=value[2]
        i+=1

# for i in range(30):
#     d=a[i]
#     t[i]=d['position']
# for i in range(len(a)):
#     x[i]=t[i][0]
#     y[i]=t[i][1]
#     z[i]=t[i][2]

xmin=min(x)
ymin=min(y)
zmin=min(z)
xmax=max(x)
ymax=max(y)
zmax=max(z)
a1=np.linspace(xmin,xmax, 3)#x的最大最小值
a2=np.linspace(ymin,ymax, 3)#y的最大最小值
a3=np.linspace(zmin,zmax, 3)#z的最大最小值
center11 = np.array([a1[0], a2[0],a3[0]])
center22 = np.array([a1[1], a2[1],a3[1]])
center33 = np.array([a1[2], a2[2],a3[2]])



k = 3
n = len(x)
dis = np.zeros([n, k+1])
disa = np.zeros([n+1, k])
for i in range(n):
        #每个点到各center的距离
        disa[i, 0] = np.sqrt((x[i] - center11[0])**2 + (y[i] - center11[1])**2+(z[i] - center11[2])**2)
        disa[i, 1] = np.sqrt((x[i] - center22[0])**2 + (y[i] - center22[1])**2+(z[i] - center22[2])**2)
        disa[i, 2] = np.sqrt((x[i] - center33[0])**2 + (y[i] - center33[1])**2+(z[i] - center33[2])**2)
        # 3
for i in range(3):
        #选择这30个节点中距离哪个center最近
        disa[30, i] = np.argmin(disa[:30,i])  # 将值较小的下标值赋值给dis[i, 2]

a11=int(disa[30][0])
a22=int(disa[30][1])
a33=int(disa[30][2])

# 1.选择初始聚类中心
center1 = np.array([x[a11], y[a11],z[a11]])
center2 = np.array([x[a22], y[a22],z[a22]])
center3 = np.array([x[a33], y[a33],z[a33]])
for i in range(n):

        dis[i, 0] = np.sqrt((x[i] - center1[0])**2 + (y[i] - center1[1])**2+(z[i] - center1[2])**2)
        dis[i, 1] = np.sqrt((x[i] - center2[0])**2 + (y[i] - center2[1])**2+(z[i] - center2[2])**2)
        dis[i, 2] = np.sqrt((x[i] - center3[0])**2 + (y[i] - center3[1])**2+(z[i] - center3[2])**2)
        # 3.归类
        dis[i, 3] = np.argmin(dis[i,:3])  # 将值较小的下标值赋值给dis[i, 2]
    
print(dis)

a=dis.tolist()
v = a
f = open('xiaoma.json',mode='w',encoding='utf-8') #文件不存在就会生成
val = json.dump(v,f)
print(val)
f.close()




