//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package myuav;
import myuav.host_node.*;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;

import inet.physicallayer.contract.packetlevel.IRadioMedium;
import inet.visualizer.integrated.IntegratedVisualizer;

import inet.environment.common.PhysicalEnvironment;




//import inet.networklayer.ipv4.RoutingTableRecorder;
//import inet.visualizer.contract.IIntegratedVisualizer;
//import inet.common.scenario.ScenarioManager;
//import inet.common.lifecycle.LifecycleController;


network UAVNetwork_Multi
{
    parameters:
        //每簇的UAV数目
        int numHosts = default(30);
        string mediumType = default("Ieee80211ScalarRadioMedium");
        @display("bgb=2000,2000");//1610.5125,874.96497
    submodules:
        visualizer: IntegratedVisualizer {
            @display("p=96.19199,412.82397");
        }
        configurator: Ipv4NetworkConfigurator {//配置器,分配IP地址并为IPv4网络设置静态路由
            parameters:
                @display("p=98.8575,183.5925");
        }
        radioMedium: <mediumType> like IRadioMedium {
            @display("p=96.84,48.42");
        }
        physicalEnvironment: PhysicalEnvironment {
            @display("p=108.215996,677.352");
        }
        basicHosts[numHosts]: UAVHost {
            parameters:
                @display("p=500,500");
        }
        hostRouters[5]: UAVRouter {
            parameters:
                @display("p=800,200");
        }
    //        BackBoneRouter: BackBoneRouter{
    //            parameters:
    //                @display("p=1000,500");
    //        }
    //        routingTableRecorder: RoutingTableRecorder {
    //            parameters:
    //                @display("p=100,150");
    //        }
    //        lifecycleController: LifecycleController {
    //            parameters:
    //                @display("p=100,200");
    //        }//管理诸如节点的关闭/重启，挂起/恢复，崩溃/恢复等操作，以及节点（路由器，主机等），接口和协议的类似操作。
    //        scenarioManager: ScenarioManager {
    //            parameters:
    //                script = default(xml("<scenario/>"));
    //                @display("p=100,250");
    //        }//用于设置和控制仿真实验。安排某些事件在指定时间进行，就像更改参数值，更改连接，删除或在路由表等中添加路由，以便观察瞬态行为。
    //由于是无线网络 因此不需要connetion
    connections allowunconnected:
}
