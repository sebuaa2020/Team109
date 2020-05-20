#include <ros/ros.h> 
#include <sensor_msgs/JointState.h> 
#define WPBH_TEST_MANI_ZERO 0 
#define WPBH_TEST_MANI_DOWN 1 
#define WPBH_TEST_MANI_UP 2 
#define WPBH_TEST_MANI_FOLD 3 
#define CMD_WAIT_SEC 10 

static int nState = WPBH_TEST_MANI_ZERO; 
int main(int argc, char** argv) { 
	ros::init(argc, argv, "wpb_home_mani_ctrl"); 
	ros::NodeHandle n; 
	ros::Publisher mani_ctrl_pub = n.advertise<sensor_msgs::JointState>("/wpb_home/mani_ctrl", 30); 
	sleep(2); 
	sensor_msgs::JointState ctrl_msg; 
	ctrl_msg.name.resize(2); 
	ctrl_msg.position.resize(2); 
	ctrl_msg.velocity.resize(2); 
	ctrl_msg.name[0] = "lift"; 
	ctrl_msg.name[1] = "gripper"; 
	ctrl_msg.position[0] = 0; 
	ctrl_msg.position[1] = 0; 
	int nCount = 0; 
	ros::Rate r(0.1); 
	while(ros::ok()) { 
		switch(nState) { 
			case WPBH_TEST_MANI_ZERO: //����״̬,�ȱ�ɳ�ʼ״̬ 
			ROS_INFO("[wpb_home_mani_ctrl] ZERO -> DOWN"); 
			ctrl_msg.position[0] = 0.5; //�����߶�(��λ:��) 
			ctrl_msg.velocity[0] = 0.5; //�����ٶ�(��λ:��/��) 
			ctrl_msg.position[1] = 0.1; //��צָ���(��λ:��) 
			ctrl_msg.velocity[1] = 5; //��צ���Ͻ��ٶ�(��λ:��/��) 
			nState = WPBH_TEST_MANI_DOWN; 
			break; 
			case WPBH_TEST_MANI_DOWN: 
			ROS_INFO("[wpb_home_mani_ctrl] DOWN -> UP "); 
			ctrl_msg.position[0] = 1.0; //�����߶�(��λ:��) 
			ctrl_msg.velocity[0] = 0.5; //�����ٶ�(��λ:��/��) 
			ctrl_msg.position[1] = 0; //��צָ���(��λ:��) 
			ctrl_msg.velocity[1] = 5; //��צ���Ͻ��ٶ�(��λ:��/��) 
			nState = WPBH_TEST_MANI_UP; 
			break; 
			case WPBH_TEST_MANI_UP: 
			ROS_INFO("[wpb_home_mani_ctrl] UP -> DOWN "); 
			ctrl_msg.position[0] = 0.5; //�����߶�(��λ:��) 
			ctrl_msg.velocity[0] = 0.5; //�����ٶ�(��λ:��/��) 
			ctrl_msg.position[1] = 0.1; //��צָ���(��λ:��) 
			ctrl_msg.velocity[1] = 5; //��צ���Ͻ��ٶ�(��λ:��/��) 
			nState = WPBH_TEST_MANI_FOLD; 
			break; 
			case WPBH_TEST_MANI_FOLD: 
			ROS_INFO("[wpb_home_mani_ctrl] DOWN -> ZERO "); 
			ctrl_msg.position[0] = 0; //�����߶�(��λ:��) 
			ctrl_msg.velocity[0] = 0.5; //�����ٶ�(��λ:��/��) 
			ctrl_msg.position[1] = 0.1; //��צָ���(��λ:��) 
			ctrl_msg.velocity[1] = 5; //��צ���Ͻ��ٶ�(��λ:��/��) 
			nState = WPBH_TEST_MANI_ZERO; 
			break; 
		} 
		mani_ctrl_pub.publish(ctrl_msg); //����ָ�� 
		ros::spinOnce(); 
		r.sleep(); 
	} 
	return 0; 
} 

