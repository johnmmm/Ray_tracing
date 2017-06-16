//
//  Sphere.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/9.
//  Copyright © 2017年 mac. All rights reserved.
//
//画球的
#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>
#pragma once
#include "Objects.hpp"
#include "Point.hpp"
class Sphere:public Object
{
public:
    vector3<double> sphere_center;         //球心
    double radius;                        //半径
    Sphere();
    ~Sphere();
    
    Sphere(vector3<double> input_center, double input_radius);
    bool intersect(Ray input_ray, vector3<double> &intersect_point);
    Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);

private:
    void init();
    double square_radius;                  //半径平方
};

#endif /* Sphere_hpp */
