#include "ros/ros.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseAction.h>
#include "std_msgs/String.h"
#include "std_msgs/UInt16.h"

class MakeGoal {

public:
	MakeGoal();
private:
    double x;
    double w;
    move_base_msgs::MoveBaseGoal goal;
	ros::Subscriber sub = n.subscribe("txt", 1000, readIn);
    ros::Publisher output_pub = n.advertise<move_base_msgs::MoveBaseGoal>("simple_goal", 1000);
	void makeAGoal(const double &x, const double &w, move_base_msgs::MoveBaseGoal goal);
    void readIn(istream &txt, double &x, double &w);
};

void MakeGoal::makeAGoal(const double &x, const double &w, move_base_msgs::MoveBaseGoal goal){
    goal.target_pose.header.frame_id = "base_link";
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = x;
    goal.target_pose.pose.orientation.w = w;
    output_pub.publish(goal);
}

void MakeGoal::readIn(istream &txt, double &x, double &w){
    while(txt >> x >> w){
        this.makeAGoal(x, w, goal);
    }
}


int main(int argc, char **argv) {
	ros::init(argc, argv, "output");
	MakeGoal make_goal;
	ros::NodeHandle n;
	ros::spin();
	return 0;
}
