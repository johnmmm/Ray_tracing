
//
//  Camera.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/22.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "Camera.hpp"


Camera::Camera()
{
    
}


Camera::~Camera()
{
    
}

Ray Camera::generate_ray(int x, int y)
{
    vector3<double> target_direction = (horizental * x + upward * y + direction * distance).normallize();          //朝向x, y的方向
    //cout << x << " " << y<<endl;
    //cout <<"generate "<< target_direction.x << " " << target_direction.y << " " << target_direction.z << endl;
    return Ray(position, target_direction);
}