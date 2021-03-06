# ROS Engineering Theory and Practice: Robot Description -- ROS理论与实践: Robot Description

This is the solution of Assignment 04 of ROS Engineering Theory and Practice [深蓝学院](https://www.shenlanxueyuan.com/course/246).

深蓝学院ROS理论与实践第04讲Robot Description作业解答. 版权归深蓝学院所有. 请勿抄袭.

---

## Solutions

---

### 1. Create a robot model for differential drive mobile robot

#### Up & Running

The solution is available at [here](src/robot_description). Follow the instructions below to reproduce the results

```bash
# build release:
catkin config --install && catkin build robot_description
# set up session:
source install/setup.bash
# visualize target differential drive mobile robot:
roslaunch robot_description visualize_diff_drive_mobile_robot.launch
```

---

#### Move Base URDF

The move base of differential drive mobile robot is defined as follows. To verify its correctness, use the following command:

```bash
# check URDF correctness:
check_urdf diff_drive_mobile_robot.urdf
# reference output:
robot name is: diff_drive_mobile_robot
---------- Successfully Parsed XML ---------------
root Link: base_footprint has 1 child(ren)
    child(1):  base_link
        child(1):  caster_back_link
        child(2):  caster_front_link
        child(3):  left_wheel_link
        child(4):  right_wheel_link
```

```xml
<?xml version="1.0"?>
<robot name="diff_drive_mobile_robot">
    <link name="base_footprint">
        <visual name="">
            <origin xyz="0.0 0.0 0.0" rpy="0.0 0.0 0.0"/>
            <geometry>
                <sphere radius="0.001"/>
            </geometry>
        </visual>
    </link>

    <joint name="base_link_joint" type="fixed">
        <parent link="base_footprint"/>
        <child link="base_link"/>
        <origin xyz="0.0 0.0 0.04" rpy="0.0 0.0 0.0"/>
    </joint>

    <link name="base_link">
        <visual name="move_base">
            <origin xyz="0.0 0.0 0.0" rpy="0.0 0.0 0.0"/>
            <geometry>
                <cylinder radius="0.20" length="0.02"/>
            </geometry>
            <material name="white">
                <color rgba="1.0 1.0 1.0 1.0"/>
            </material>
        </visual>
    </link>

    <joint name="left_wheel_joint" type="continuous">
        <parent link="base_link"/>
        <child link="left_wheel_link"/>
        <origin xyz="0.0 0.20 0.0" rpy="-1.57079632679 0.0 0.0"/>
        <axis xyz="0.0 0.0 1.0"/>
    </joint>

    <link name="left_wheel_link">
        <visual name="left_wheel">
            <origin xyz="0.0 0.0 0.02" rpy="0.0 0.0 0.0"/>
            <geometry>
                <cylinder radius="0.04" length="0.04"/>
            </geometry>
            <material name="black">
                <color rgba="0.0 0.0 0.0 1.0"/>
            </material>
        </visual>
    </link>

    <joint name="right_wheel_joint" type="continuous">
        <parent link="base_link"/>
        <child link="right_wheel_link"/>
        <origin xyz="0.0 -0.20 0.0" rpy="1.57079632679 0.0 0.0"/>
        <axis xyz="0.0 0.0 1.0"/>
    </joint>

    <link name="right_wheel_link">
        <visual name="right_wheel">
            <origin xyz="0.0 0.0 0.02" rpy="0.0 0.0 0.0"/>
            <geometry>
                <cylinder radius="0.04" length="0.04"/>
            </geometry>
            <material name="black">
                <color rgba="0.0 0.0 0.0 1.0"/>
            </material>
        </visual>
    </link>

    <joint name="caster_front_joint" type="fixed">
        <parent link="base_link"/>
        <child link="caster_front_link"/>
        <origin xyz="0.15 0.0 -0.01" rpy="0.0 3.14159265359 0.0"/>
    </joint>

    <link name="caster_front_link">
        <visual name="caster_front">
            <origin xyz="0.0 0.0 0.0" rpy="0.0 0.0 0.0"/>
            <geometry>
                <sphere radius="0.02"/>
            </geometry>
            <material name="black">
                <color rgba="0.0 0.0 0.0 1.0"/>
            </material>
        </visual>
    </link>

    <joint name="caster_back_joint" type="fixed">
        <parent link="base_link"/>
        <child link="caster_back_link"/>
        <origin xyz="-0.15 0.0 -0.01" rpy="3.14159265359 0.0 0.0"/>
    </joint>

    <link name="caster_back_link">
        <visual name="caster_back">
            <origin xyz="0.0 0.0 0.0" rpy="0.0 0.0 0.0"/>
            <geometry>
                <sphere radius="0.02"/>
            </geometry>
            <material name="black">
                <color rgba="0.0 0.0 0.0 1.0"/>
            </material>
        </visual>
    </link>
</robot>
```

---

#### TF Tree

The `TF Tree` defined by the URDF can be exported with the following command. The exported TF tree in PDF is available at [here](src/robot_description/urdf/diff_drive_mobile_robot.pdf).

```bash
# export model tf tree to PDF:
urdf_to_graphiz diff_drive_mobile_robot.urdf
```

The TF tree is visualized below for easy reference:

<img src="doc/tf-tree.png" alt="Move Base TF Tree" width="%100">

---

#### Model Visualization

The model can be visualized using the launch file through RViz.

<img src="doc/visualization.png" alt="Move Base Visualization" width="%100">