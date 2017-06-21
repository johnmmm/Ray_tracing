//
//  Beizer_Objects.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/21.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "Beizer_Objects.hpp"
#include "Point.hpp"

#include <cmath>
#include <algorithm>
#include <iostream>

Beizer_Objects::Beizer_Objects(int line, int row, vector3<double> point_array[]) : beizer_surface(line, row)

{
    
}


Beizer_Objects::~Beizer_Objects()
{
    
}

bool Beizer_Objects::intersect(Ray input_ray, vector3<double> &intersect_point)
{
    
    return false;
}

Color Beizer_Objects::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)   //in为法向量的引用
{
    light.direction = (target_pos - light.start_point).normallize();
    vector3<double> p_partial_t = beizer_line.Beizer_Derivative(last_surfacet);
    vector3<double> beizer_point = beizer_line.get_point(last_surfacet);
    double x_partial_t = p_partial_t.x * cos(last_theta);
    double x_partial_theta = beizer_point.x * sin(last_theta) * -1;
    double y_partial_t = p_partial_t.x * sin(last_theta);
    double y_partial_theta = beizer_point.x * cos(last_theta);
    double z_partial_t = p_partial_t.z;
    double z_partial_theta = 0;
    double A = y_partial_t * z_partial_theta - y_partial_theta * z_partial_t;
    double B = z_partial_t * x_partial_theta - z_partial_theta * x_partial_t;
    double C = x_partial_t * y_partial_theta - x_partial_theta * y_partial_t;
    in = vector3<double>(A, B, C).normallize();
    if (in * light.direction > 0)
    {
        in = in * -1;
    }
    return PhongModel::reflect_color(light, in, view_direction, color_feature);

}

bool Beizer_Objects::NewtonIteration(Ray input_ray, double& line_t, double& surface_t, double& theta)         //t是直线的参数，u,v是曲面的参数
{
    double delta_t, delta_surfacet, delta_theta;
    for (int i = 0; i < 5; i++)
    {
        vector3<double> beizer_point = beizer_line.get_point(surface_t);
        vector3<double> beizer_partial_surfacet = beizer_line.Beizer_Derivative(surface_t);
        vector3<double> surface_partial_surfacet = vector3<double>(cos(theta) * beizer_partial_surfacet.x, sin(theta) * beizer_partial_surfacet.x, beizer_partial_surfacet.z);
        vector3<double> surface_partial_theta = vector3<double>(-1 * sin(theta) * beizer_point.x, cos(theta) * beizer_point.x, 0);
        vector3<double> f_value = input_ray.start_point + input_ray.direction * line_t - vector3<double>(beizer_point.x * cos(theta), beizer_point.x * sin(theta), beizer_point.z);
        
        double D = input_ray.direction * surface_partial_surfacet.cross_product(surface_partial_theta);
        if (abs(D) < limit_zero)
            return false;
        delta_t = surface_partial_surfacet * (surface_partial_theta.cross_product(f_value)) / D;
        delta_surfacet = input_ray.direction * (surface_partial_theta.cross_product(f_value)) / D;
        delta_theta = input_ray.direction * (surface_partial_surfacet.cross_product(f_value)) / D;
        line_t -= delta_t;
        surface_t -= delta_surfacet;
        theta += delta_theta;
    }
    
    if (max(abs(delta_t), max(abs(delta_surfacet), abs(delta_theta))) > 0.001)          //认为迭代时迭飞了，没有交点
    {
        return false;
    }
    else
    {
        if (surface_t < -1 * limit_zero || surface_t > 1 + limit_zero)
        {
            return false;
        }
        return true;
    }
}

void Beizer_Objects::init()
{
    object_type = Object_type::_Beizer_Surface;
}