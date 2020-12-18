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
import inet.node.inet.StandardHost;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.visualizer.integrated.IntegratedVisualizer;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;
import inet.physicallayer.ieee80211.packetlevel.*;
import inet.applications.pingapp.PingApp;
import inet.physicallayer.contract.packetlevel.IRadioMedium;
import inet.environment.common.PhysicalEnvironment;
import myuav.uavhost;
import myuav.AnyMacXmacLayer;

network uavnetwork
{
    parameters:
        int numHosts;
        @display("bgb=1000,1000");
    submodules:
        visualizer: IntegratedVisualizer {
            @display("p=60,48");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                config = xml("<config><interface hosts='*' address='192.168.1.x' netmask='255.255.255.0'/></config>");
                @display("p=60,325");
        }
        radioMedium: <default("UnitDiskRadioMedium")> like IRadioMedium {
            @display("p=60,190");
        }
        host[numHosts]: uavhost {
            @display("i=misc/node_vs");
        }
        physicalEnvironment: PhysicalEnvironment {
            @display("p=303.20798,429.71198");
        }
}
