#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    ROS_INFO_STREAM("Moving the robot towards the ball");
    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    
    if (!client.call(srv))
    ROS_ERROR("Failed to call service comman_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    
    //SOLUTION:
    //We set an upper and lower bound so as to scan only the middle section of the image
    //because the ball is placed on the same level as the camera
    int lower_bound = img.data.size()/3;
    int upper_bound = (img.data.size()*2)/3;
    bool ball_status=false;
    for(int i=lower_bound;i+2<upper_bound;i+=3)
    {
        if(img.data[i]==255 && img.data[i+1]==255 && img.data[i+2]==255)
        {
            int x_pose = i % img.step;
            if (x_pose<img.step/3)
                drive_robot(0.5,1);
            else if (x_pose>img.step/3 * 2)
                drive_robot(0.5,-1);
            else
                drive_robot(0.5,0);
            ball_status = true;
            break;
        }
    }
    if (ball_status==false)
        drive_robot(0.0,0.0);
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
