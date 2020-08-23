#ifndef ROS_COMM_TURTLESIM_CONTROL_ACTIVITY_H
#define ROS_COMM_TURTLESIM_CONTROL_ACTIVITY_H

#include <string>
#include <unordered_map>

#include <ros/ros.h>

#include "turtlesim_control/SpawnTurtle.h"
#include "turtlesim_control/SetSpeed.h"

namespace ros_comm {

struct Config {
    struct {
        size_t N;
        double grid_size;
        size_t num_turtles;
        size_t max_turtles;
    } spawn;
};

struct State {
    std::string name;

    ros::Publisher pub;

    struct {
        double w;
        double v;
    } velocity;
};

class Activity {
public:
    Activity();
    ~Activity();

    void Init(void);
    bool SpawnTurtle(const std::string &name);
    void PublishCmdVels(void);

    size_t GetMaxNumTurtles(void) const { return config_.spawn.max_turtles; }
    size_t GetCurrNumTurtles(void) const { return config_.spawn.num_turtles; }
private:
    Config config_;

    void ResetWorld(void);

    bool SpawnTurtle(
        turtlesim_control::SpawnTurtle::Request &spawn_req,
        turtlesim_control::SpawnTurtle::Response &spawn_res
    );

    bool SetSpeed(
        turtlesim_control::SetSpeed::Request &set_speed_req,
        turtlesim_control::SetSpeed::Response &set_speed_res
    );

    ros::NodeHandle private_nh_;

    std::unordered_map<size_t, State> turtle_state;

    struct {
        ros::ServiceServer spawn_;
        ros::ServiceServer motion_control_;
    } service;

    ros::ServiceClient client_;
};

} // namespace ros_comm

#endif  // ROS_COMM_TURTLESIM_CONTROL_ACTIVITY_H