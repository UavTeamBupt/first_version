import json
import random
import os
import numpy as np
import math


def read_json_file(all_path):
    basic_node_position_dict=dict()
    router_node_position_dict=dict()
    for path in all_path:
        while not (os.path.exists(path)):#如果文件不存在就一直while
            continue
        with open(path) as f_obj:
            temp_dict=json.load(f_obj)
            for (title,all_values) in temp_dict.items():#进入一个json文件读取
                # print("title:",title)
                # print("all_values:",all_values)
                for node in all_values:
                    for (key2,value2) in node.items():
                        # print("key2:",key2)
                        # print("value2:",value2)
                        if "basic" in title:
                            if(key2 not in basic_node_position_dict.keys()):
                                basic_node_position_dict[key2]=value2
                        elif "router" in title:
                            if(key2 not in router_node_position_dict.keys()):
                                router_node_position_dict[key2]=value2
    return basic_node_position_dict,router_node_position_dict

#TODO 聚类模块 目前是简单的瞎搞


def get_distance(data1, data2):
    distance = np.sqrt(np.sum(np.square(data1-data2)))
    return distance


def get_cluster(basic_dict, router_dict):
    #注意这里是基础节点的输出
    print("--------------------basic_dict:")
    for(i, j) in basic_dict.items():
        print(i)
        print(j)
    #簇头节点的输出
    print("----------------------------------------router_dict:")
    for(i, j) in router_dict.items():
        print(i)
        print(j)
    basic_cluster_dict = dict()
    # pos=0
    router_name_list = list(router_dict.keys())
    router_name = np.array(router_name_list)
    basic_name_list = list(basic_dict.keys())
    basic_name = np.array(basic_name_list)
    router_position_list = list(router_dict.values())
    router_position = np.array(router_position_list)
    basic_position_list = list(basic_dict.values())
    basic_position = np.array(basic_position_list)

    for i in range(len(basic_dict)):
        min_dis = np.inf
        index = 0
        for j in range(len(router_dict)):
            distance = get_distance(router_position[j], basic_position[i])
            if distance < min_dis:
                min_dis = distance
                index = j
        basic_cluster_dict[str(basic_name[i])] = router_name[index]

    print("----------------------------------------random method result:")
    for(i, j) in basic_cluster_dict.items():
        print(i, j)
    return basic_cluster_dict


def write_to_json(res):
    filename = r"..\clusterResult.json"
    with open(filename, 'w') as f_obj:
        json.dump(res, f_obj,indent=2)


if __name__ == '__main__':
    basic_node_position_path=r"..\basicNodePosition.json"
    router_node_position_path=r"..\routerNodePosition.json"
    # while True:
    all_path=[basic_node_position_path,router_node_position_path]
    basic_dict,router_dict=read_json_file(all_path)
    basic_cluster_dict=get_cluster(basic_dict, router_dict)
    write_to_json(basic_cluster_dict)