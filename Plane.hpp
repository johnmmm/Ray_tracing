//
//  Plane.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/15.
//  Copyright © 2017年 mac. All rights reserved.
//

#ifndef Plane_hpp
#define Plane_hpp

#include <stdio.h>
#include "Objects.hpp"
#include "Point.hpp"


class Plane : public Object
{
public:
    Plane();
    ~Plane();
    
    double A, B, C, D;                 //平面方程的四个参数
    vector3<double> normal_vector;             //平面的法向量
    vector3<double> passed_point;              //经过的点
    
    Plane(vector3<double> input_point, vector3<double> input_normal_vector);
    bool intersect(Ray input_ray, vector3<double> &intersect_point);
    
    double signed_distance(Ray input_ray);
    Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);

private:
    void init();
};

#endif /* Plane_hpp */