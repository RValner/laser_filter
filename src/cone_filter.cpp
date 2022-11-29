#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <iostream>
#include <chrono>
#include <assert.h>
#include <boost/program_options.hpp>

ros::Publisher laser_frame_pub;
double FILTER_ANGLE_START;
double FILTER_ANGLE_END;

void laserFrameCb(const sensor_msgs::LaserScan& msg)
{
	sensor_msgs::LaserScan filtered_frame = msg;
	unsigned int start_index = (FILTER_ANGLE_START - msg.angle_min) / msg.angle_increment;
	unsigned int end_index = (FILTER_ANGLE_END - msg.angle_min) / msg.angle_increment;

	for (unsigned int i=start_index; i<=end_index; i++)
	{
		filtered_frame.ranges.at(i) = msg.range_max + 10; // Push the point out of the range
	}

	laser_frame_pub.publish(filtered_frame);
}

int main(int argc, char** argv)
{
	namespace po = boost::program_options;
	po::variables_map vm;
	po::options_description desc("Allowed options");
	desc.add_options()
		("start-angle", po::value<double>(), "Starting angle of the filter.")
		("end-angle", po::value<double>(), "End angle of the filter");

	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	FILTER_ANGLE_START = vm["start-angle"].as<double>();
	FILTER_ANGLE_END = vm["end-angle"].as<double>();

	ros::init(argc, argv, "frame_box_filtering");
	ros::NodeHandle nh;

	laser_frame_pub = nh.advertise<sensor_msgs::LaserScan>("scan_filtered", 1);
	ros::Subscriber laser_frame_sub = nh.subscribe("scan", 1, laserFrameCb);

	ros::spin();
	return 0;
}
