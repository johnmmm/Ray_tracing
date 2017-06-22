
//
//  Ray.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/22.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "Ray.hpp"


Ray::Ray(vector3<double> input_point, vector3<double> input_direction)
{
    start_point = input_point;
    direction = input_direction.normallize();
}


Ray::~Ray()
{
    
}
