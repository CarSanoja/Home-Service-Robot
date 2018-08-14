/*
 * Copyright (c) 2010, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// %Tag(FULLTEXT)%
// %Tag(INCLUDES)%
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/UInt8.h>
// %EndTag(INCLUDES)%

double pick[2] = {-6.00, -9.25};
double drop[2] = {-1.00, -0.00};

visualization_msgs::Marker marker;
uint8_t state = 2;

void robot_status(const std_msgs::UInt8::ConstPtr& msg){
   state = msg->data;
   return;
}

void add_marker(double xpos, double ypos, bool ToDo){

  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();

  marker.ns = "basic_shapes";
  marker.id = 0;
  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = visualization_msgs::Marker::CUBE;

  if(ToDo){
    marker.action = visualization_msgs::Marker::ADD;
  }
  else{
    marker.action = visualization_msgs::Marker::DELETE;
  }
  
  // Set the pose, scan and color of the marker. 
  marker.pose.position.x = xpos;
  marker.pose.position.y = ypos;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
  marker.scale.x = 1.0;
  marker.scale.y = 1.0;
  marker.scale.z = 1.0;
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
  marker.lifetime = ros::Duration();

}

// %Tag(INIT)%
int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle n;
  ros::Rate r(1);
  bool initialPosition = false;
  bool finalPosition = false;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber status_sub = n.subscribe("/robot_position", 1, robot_status);
// %EndTag(INIT)%
  
  // Set our initial shape type to be a cube
// %Tag(SHAPE_INIT)%
  uint32_t shape = visualization_msgs::Marker::CUBE;
// %EndTag(SHAPE_INIT)%

// %Tag(MARKER_INIT)%
  while (ros::ok())
  {
    if(!initialPosition){
      ROS_INFO_ONCE("Adding object for picking");
      add_marker(pick[0],pick[1], true);
      while (marker_pub.getNumSubscribers() < 1){
          if (!ros::ok()){
            return 0;
          }
          ROS_WARN_ONCE("Please create a subscriber to the marker");
          sleep(1);}
      marker_pub.publish(marker);
      
    }


    if( state==0 && !initialPosition){
      initialPosition = true;
      add_marker(pick[0], pick[0], false);
      marker_pub.publish(marker);
      ros::Duration(5.0).sleep();
    }

    if(initialPosition && !finalPosition){
      while (marker_pub.getNumSubscribers() < 1){
        if (!ros::ok()){
          return 0;
        }
        ROS_WARN_ONCE("Please create a subscriber to the marker");
        sleep(1);}
    }


    if( state==1 && !finalPosition){
      add_marker(drop[0], drop[1], true);
      marker_pub.publish(marker);
      ros::Duration(5.0).sleep();
      return 0;
    }

    ros::spinOnce();
    
// %EndTag(SLEEP_END)%
}
// %EndTag(FULLTEXT)%
}
