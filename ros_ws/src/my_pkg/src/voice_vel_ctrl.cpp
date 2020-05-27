#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <geometry_msgs/Twist.h>

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
ros::Publisher vel_pub;
using namespace std;

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    // ROS_INFO("I heard: [%s]", msg->data.c_str());
    cout<<"========="<<endl;
    std::cout<<"收到了消息: "<<msg->data<<std::endl;
    geometry_msgs::Twist vel_cmd;
    vel_cmd.linear.x = 0;
    vel_cmd.linear.y = 0;
    vel_cmd.linear.z = 0;
    vel_cmd.angular.x = 0;
    vel_cmd.angular.y = 0;
    vel_cmd.angular.z = 0;
    if(msg->data.find("前进")!=string::npos)
    {
        cout<<"识别到了前进"<<endl;
        vel_cmd.linear.x = 1;
    }
    if(msg->data.find("后退")!=string::npos)
    {
        cout<<"识别到了后退"<<endl;
        vel_cmd.linear.x = -1;
    }
    if(msg->data.find("停止")!=string::npos)
    {

        cout<<"识别到了停止"<<endl;
        vel_cmd.linear.x = 0;
        vel_cmd.linear.y = 0;
        vel_cmd.linear.z = 0;
        vel_cmd.angular.x = 0;
        vel_cmd.angular.y = 0;
        vel_cmd.angular.z = 0;

    }
    if (msg->data.find("左转")!=string::npos)
    {

        cout<<"识别到了左转"<<endl;
        vel_cmd.angular.z = 0.3;
    }
    if(msg->data.find("右转")!=string::npos)
    {

        cout<<"识别到了右转"<<endl;
        vel_cmd.angular.z = -0.3;
    }

    vel_pub.publish(vel_cmd);
    sleep(1);
    vel_cmd.linear.x = 0;
    vel_cmd.linear.y = 0;
    vel_cmd.linear.z = 0;
    vel_cmd.angular.x = 0;
    vel_cmd.angular.y = 0;
    vel_cmd.angular.z = 0;
    vel_pub.publish(vel_cmd);
}

int main(int argc, char *argv[])
{
    /**
     * The ros::init() function needs to see argc and argv so that it can perform
     * any ROS arguments and name remapping that were provided at the command line.
     * For programmatic remappings you can use a different version of init() which takes
     * remappings directly, but for most command-line programs, passing argc and argv is
     * the easiest way to do it.  The third argument to init() is the name of the node.
     *
     * You must call one of the versions of ros::init() before using any other
     * part of the ROS system.
     */
    ros::init(argc, argv, "my_pkg");

    /**
     * NodeHandle is the main access point to communications with the ROS system.
     * The first NodeHandle constructed will fully initialize this node, and the last
     * NodeHandle destructed will close down the node.
     */
    ros::NodeHandle n;

    /**
     * The subscribe() call is how you tell ROS that you want to receive messages
     * on a given topic.  This invokes a call to the ROS
     * master node, which keeps a registry of who is publishing and who
     * is subscribing.  Messages are passed to a callback function, here
     * called chatterCallback.  subscribe() returns a Subscriber object that you
     * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
     * object go out of scope, this callback will automatically be unsubscribed from
     * this topic.
     *
     * The second parameter to the subscribe() function is the size of the message
     * queue.  If messages are arriving faster than they are being processed, this
     * is the number of messages that will be buffered up before beginning to throw
     * away the oldest ones.
     */
    ros::Subscriber sub = n.subscribe("/xfyun/iat", 1000, chatterCallback);
    vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel",10);
    /**
     * ros::spin() will enter a loop, pumping callbacks.  With this version, all
     * callbacks will be called from within this thread (the main one).  ros::spin()
     * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
     */
    ros::spin();

    return 0;
}