#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include <unistd.h>


using namespace std;

const int STATE_IDLE = 1;
const int STATE_SAVE = 2;
int currentState = STATE_IDLE;
int cnt = 0;

string root_dir;


string path_join(string src_path, string add_path) {
    if (src_path.at(src_path.length() - 1) == '/') {
        return src_path + add_path;
    } else {
        // std::cout << "[INFO] src_path: " << src_path << std::endl;
        return src_path.append("/") + add_path;
    }
}

string get_filename()
{
    time_t nowtime;
    struct tm* p;;
    time(&nowtime);
    p = localtime(&nowtime);

    ostringstream ostr;
    ostr<<"saved_images/";
    ostr << 1900+p->tm_year<<"-"<<p->tm_mon<<"-"<<p->tm_mday<<"-"<<p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec;
    ostr<<".jpg";
    return path_join(root_dir, ostr.str());
}
void save_image_func(const sensor_msgs::ImageConstPtr& msg)
{

    cout<<"rua===============\n";
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    // if(currentState == STATE_SAVE)
    {
        imwrite(get_filename().c_str(),cv_ptr->image);
        currentState = STATE_IDLE;
        cout<<"saved\n";
    }

}
int main(int argc, char** argv)
{
    // Added by qushuo
    int opt;
    const char *optstring;
    while ((opt = getopt(argc, argv, optstring)) != -1) {
        root_dir = std::string(optarg);
    }


    int sleepTime;
    if(argc > 1)
        sscanf(argv[1],"%d",&sleepTime);
    else
        sleepTime = 10;
    cout<<"sleepTime = "<<sleepTime<<endl;
    ros::init(argc, argv, "my_save_image");
    ros::NodeHandle n;
    cnt = 0;
    int currentState = STATE_IDLE;
    ros::Subscriber rgb_sub = n.subscribe("/kinect2/hd/image_color_rect", 1 , save_image_func);
    ros::Rate r(1);

    int cmd = 10;
    cout<<"init complete\n";


    while(ros::ok()){

        ros::spinOnce();
        r.sleep();
        for(int i=1;i<sleepTime;i++)
        {
            r.sleep();
        }
    }

}
