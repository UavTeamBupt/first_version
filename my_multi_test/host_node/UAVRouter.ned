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

package myuav.host_node;
import inet.node.inet.*;//WirelessHost AdHocHost
import inet.node.aodv.*; //AODVRouter

//实际就是AODVRouter改了个图标!
module UAVRouter extends AodvRouter
{
        parameters:
        @display("i=device/quadcopter");
}