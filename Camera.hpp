//
//  Camera.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/15.
//  Copyright © 2017年 mac. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#pragma once
#include "Point.hpp"
#include "Ray.hpp"
#include <cmath>
#include <iostream>
using namespace std;
#define PI 3.14159265


class Camera
{
public:
    Camera();
    ~Camera();
    
    vector3<double> position;       //所处的位置
    vector3<double> upward;         //相机向上的方向
    vector3<double> direction;      //相机看的方向
    unsigned int size_x, size_y;              //图的大小
    double view_angle_h, view_angle_w;        //视角
    double distance;                //距离
    
    Camera(vector3<double> eye_place, vector3<double> forward_direction, vector3<double> upward_direction, unsigned int picture_size_x = 300, unsigned int picture_size_y = 400, double input_angle_h =95)
    {
        position = eye_place;
        upward = upward_direction.normallize();
        direction = forward_direction.normallize();
        size_x = picture_size_x, size_y = picture_size_y;
        view_angle_h = input_angle_h;
        view_angle_w = (view_angle_h / (double)size_y) * (double)size_x;
        distance = (double) size_y / (2 * tan(view_angle_h * PI / 360));                          // 计算距离
        horizental = (upward.cross_product(direction)).normallize();
    }
    
    Ray generate_ray(int x, int y);
    
private:
    vector3<double> horizental;     //所处的平面
};

#endif /* Camera_hpp */
