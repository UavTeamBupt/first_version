# -*- coding: utf-8 -*-
"""
Created on Thu Dec 24 13:25:45 2020

@author: 17115
"""

import numpy as np
import json
import os

CLUSTER_NUM=3#聚类数量

def get_json_data(path):
    while not (os.path.exists(path)):  # 如果文件不存在就一直while
        continue
    with open(path) as f_obj:
        strF = f_obj.read()  # TODO new add
        if len(strF) <= 0:
            return -1,-1,-1,-1,-1#不处理
        temp = json.loads(strF)
        json_data=temp['basicNodePosition']
        json_length=len(json_data)
        values = {}
        keys = {}
        x = np.linspace(0, json_length, json_length)  # 开头，结尾，元素个数
        y = np.linspace(0, json_length, json_length)
        z = np.linspace(0, json_length, json_length)
        for i in range(json_length):
            d=json_data[i]
            for(key,value) in d.items():
                keys[i] = key
                values[i] = value
        for i in range(json_length):
            x[i]=values[i][0]
            y[i]=values[i][1]
            z[i]=values[i][2]
        return x,y,z,keys,json_length

def get_cluster(x,y,z,keys,json_length,result_path):
    belongs_to_value={}
    xmin,ymin,zmin=min(x),min(y),min(z)
    xmax,ymax,zmax=max(x),max(y),max(z)
    a1=np.linspace(xmin,xmax, CLUSTER_NUM)#从xmin到xmax分CLUSTER_NUM个段
    a2=np.linspace(ymin,ymax, CLUSTER_NUM)
    a3=np.linspace(zmin,zmax, CLUSTER_NUM)
    fake_center_1 = np.array([a1[0], a2[0],a3[0]])#第0段中心
    fake_center_2 = np.array([a1[1], a2[1],a3[1]])#第1段中心
    fake_center_3 = np.array([a1[2], a2[2],a3[2]])#第2段中心
    dis = np.zeros([json_length, CLUSTER_NUM+2])
    node2FakeCenterDis = np.zeros([json_length+1, CLUSTER_NUM])

    for i in range(json_length):#每个点分别到各center的距离
        node2FakeCenterDis[i, 0] = np.sqrt((x[i] - fake_center_1[0])**2 + (y[i] - fake_center_1[1])**2+(z[i] - fake_center_1[2])**2)
        node2FakeCenterDis[i, 1] = np.sqrt((x[i] - fake_center_2[0])**2 + (y[i] - fake_center_2[1])**2+(z[i] - fake_center_2[2])**2)
        node2FakeCenterDis[i, 2] = np.sqrt((x[i] - fake_center_3[0])**2 + (y[i] - fake_center_3[1])**2+(z[i] - fake_center_3[2])**2)
    for j in range(CLUSTER_NUM):
        #在第json_length最后这个位置上，放上每类的中心点
        #node2FakeCenterDis[:json_length,i]是对第j个伪聚类中心，各点到其的距离，argmin取自变量，即离伪聚类中心最短的点下标。
        node2FakeCenterDis[json_length, j] = np.argmin(node2FakeCenterDis[:json_length,j])
    center_node_index_1=int(node2FakeCenterDis[json_length][0])#到第0个伪聚类中心最短的点的下标
    center_node_index_2=int(node2FakeCenterDis[json_length][1])#到第1个伪聚类中心最短的点的下标
    center_node_index_3=int(node2FakeCenterDis[json_length][2])#到第2个伪聚类中心最短的点的下标

    # 1.选择初始聚类中心
    center1 = np.array([x[center_node_index_1], y[center_node_index_1],z[center_node_index_1]])
    center2 = np.array([x[center_node_index_2], y[center_node_index_2],z[center_node_index_2]])
    center3 = np.array([x[center_node_index_3], y[center_node_index_3],z[center_node_index_3]])
    print("=======================ALL CENTERS：=======================")
    print("center1:",keys[center_node_index_1])
    print("center2:",keys[center_node_index_2])
    print("center3:",keys[center_node_index_3])
    for i in range(json_length):#各个点到真正3个中心的距离
        dis[i, 0] = np.sqrt((x[i] - center1[0])**2 + (y[i] - center1[1])**2+(z[i] - center1[2])**2)
        dis[i, 1] = np.sqrt((x[i] - center2[0])**2 + (y[i] - center2[1])**2+(z[i] - center2[2])**2)
        dis[i, 2] = np.sqrt((x[i] - center3[0])**2 + (y[i] - center3[1])**2+(z[i] - center3[2])**2)
        # print("node_index:{},dis1:{},dis2:{},dis3:{}".format(i,int(dis[i, 0]),int(dis[i, 1]),int(dis[i, 2])))
        # 3.归类,该点属于哪个聚类簇头
        dis[i, 3] = np.argmin(dis[i,:3])
    for i in range(json_length):
        temp=dis[i][3]
        if temp == 0:
            belongs_to_value[i]=keys[center_node_index_1]
        elif temp == 1:
            belongs_to_value[i]=keys[center_node_index_2]
        elif temp == 2:
            belongs_to_value[i]=keys[center_node_index_3]
    res_dict=dict()
    for i in range(json_length):
        # if keys[i] not in res_dict.keys():
        res_dict[keys[i]]=belongs_to_value[i]
    with open(result_path,'w',encoding='utf-8') as f_obj:
        json.dump(res_dict, f_obj,indent=2)

if __name__ == '__main__':
    basic_node_position_path=r"..\basicNodePosition.json"
    result_path=r"..\clusterResult.json"
    while True:
        x,y,z,keys,json_length=get_json_data(basic_node_position_path)
        if json_length==-1: #while的时候用
            continue
        get_cluster(x,y,z,keys,json_length,result_path)



        


