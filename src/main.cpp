#include "Config.h"
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <string>
#include <pcl_ros/transforms.h>
#include <pcl/filters/passthrough.h>

int main (int argc, char** argv){
  Config config;

  ros::init (argc, argv, "my_pcl_tutorial");
  ros::NodeHandle nh;

  pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud;
  temp_cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
  sensor_msgs::PointCloud2 publish_cloud;

  ros::Publisher pub = nh.advertise<sensor_msgs::PointCloud2> ("publish_cloud", 1);

  pcl::PointXYZ point;
  std::string str_buf;
  float f_buf;
  std::fstream fs;
  fs.open(config.path, std::ios::in);
  int i=0;
  while (!fs.eof()){
    getline(fs, str_buf, ',');
    if(str_buf.size() > 2){
      f_buf = stof(str_buf);
      if (i%3 == 0){
        point.x = f_buf;
      }
      else if(i%3 == 1){
        point.y = f_buf;
      }
      else{
        point.z = f_buf;
      }
      if(i%3 == 2)
      {
        temp_cloud->push_back(point);
      }
      i++;
    }
  }

  Eigen::Affine3f transform_plToBody =
  pcl::getTransformation(config.delX, config.delY, config.delZ, config.delRoll, config.delPitch, config.delYaw);
  pcl::transformPointCloud(*temp_cloud, *temp_cloud, transform_plToBody);

  pcl::PassThrough<pcl::PointXYZ> pass;
  pass.setInputCloud(temp_cloud);
  pass.setFilterFieldName("x");
  pass.setFilterLimits(config.minX, config.maxX);
  pass.filter(*temp_cloud);

  pcl::toROSMsg(*temp_cloud, publish_cloud);
  publish_cloud.header.frame_id = "world";
  publish_cloud.header.stamp = ros::Time::now();

  ros::Rate rate(10);
  bool written = false;
  while (ros::ok()) {
    pub.publish(publish_cloud);
    ros::spinOnce();
  }
}