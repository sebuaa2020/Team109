/*********************************************************************
* Software License Agreement (BSD License)
* 
*  Copyright (c) 2017-2020, Waterplus http://www.6-robot.com
*  All rights reserved.
* 
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
* 
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the WaterPlus nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  FOOTPRINTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/
/* @author Zhang Wanjie                                             */

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include <waterplus_map_tools/Waypoint.h>
#include <waterplus_map_tools/GetNumOfWaypoints.h>
#include <waterplus_map_tools/GetWaypointByIndex.h>
#include <waterplus_map_tools/GetWaypointByName.h>
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
waterplus_map_tools::GetWaypointByIndex srvI;
waterplus_map_tools::GetNumOfWaypoints srvNum;
int nNumOfWaypoints = 0;
ros::ServiceClient cliGetNum;
ros::ServiceClient cliGetWPIndex;
ros::ServiceClient cliGetWPName;
void show_all_wp()
{

    
    if (cliGetNum.call(srvNum))
    {
        ROS_INFO("Num_wp = %d", (int)srvNum.response.num);
    }
    else
    {
        ROS_ERROR("Failed to call service get_num_waypoints");
    }
    for(int i=0;i<srvNum.response.num;i++)
    {
        srvI.request.index = i;
        if (cliGetWPIndex.call(srvI))
        {
            std::string name = srvI.response.name;
            float x = srvI.response.pose.position.x;
            float y = srvI.response.pose.position.y;
            // ROS_INFO("Get_wp_index: name = %s (%.2f,%.2f)", name.c_str(),x,y);
            printf("找到了%d号导航点:%s\t坐标为(%.2f,%.2f)\n",i, name.c_str(),x,y);
        }
        else
        {
            ROS_ERROR("Failed to call service get_wp_index");
        }
    }
     if (cliGetNum.call(srvNum))
    {
        // ROS_INFO("Num_wp = %ld", (long int)srvNum.response.num);
        nNumOfWaypoints = (int)srvNum.response.num;

        printf("共发现了%d个导航点\n",nNumOfWaypoints);
    }
    else
    {
        ROS_ERROR("Failed to call service get_num_waypoint");
        exit;
    }
}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "wp_nav_test");

    ros::NodeHandle nh;
    cliGetNum = nh.serviceClient<waterplus_map_tools::GetNumOfWaypoints>("/waterplus/get_num_waypoint");
    cliGetWPIndex = nh.serviceClient<waterplus_map_tools::GetWaypointByIndex>("/waterplus/get_waypoint_index");
    cliGetWPName = nh.serviceClient<waterplus_map_tools::GetWaypointByName>("/waterplus/get_waypoint_name");

    ///////////////////////////////////////////////////////////////////////////////////
    
    waterplus_map_tools::GetWaypointByIndex srvI;


    MoveBaseClient ac("move_base", true);

    while(!ac.waitForServer(ros::Duration(5.0)))
    {
        if(!ros::ok())
            break;
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    int nWPIndex = 0;
    move_base_msgs::MoveBaseGoal goal;
    
    while(ros::ok())
    {
        waterplus_map_tools::GetNumOfWaypoints srvNum;
        show_all_wp();
        nWPIndex = -1;
        while(nWPIndex<0 || nWPIndex>=nNumOfWaypoints){
            cout<<"请输入想要去的导航点:\n";
            cin>>nWPIndex;
            
        }


        waterplus_map_tools::GetWaypointByIndex srvI;
        srvI.request.index = nWPIndex;

        if (cliGetWPIndex.call(srvI))
        {
            std::string name = srvI.response.name;
            float x = srvI.response.pose.position.x;
            float y = srvI.response.pose.position.y;
            printf("正在前往%d号导航点，其坐标为(%.2f,%.2f)\n",nWPIndex,x,y);
        }
        else
        {
            ROS_ERROR("Failed to call service get_wp_index");
        }

        ROS_INFO("Go to the WayPoint[%d]",nWPIndex);
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        goal.target_pose.pose = srvI.response.pose;
        ac.sendGoal(goal);
        ac.waitForResult();

        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        {
            ROS_INFO("Arrived at WayPoint[%d] !",nWPIndex);
            nWPIndex ++;
        }
        else
            ROS_INFO("Failed to get to WayPoint[%d] ...",nWPIndex );
    }

    return 0;
}