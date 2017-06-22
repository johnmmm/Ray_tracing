//
//  Beizer_rotates.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/20.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "Beizer_rotates.hpp"
#include <cstdio>


void Beizer_rotates::init()
{
    object_type = Object_type::_Beizer_Rotate;
}

Beizer_rotates::Beizer_rotates() : rotate_axis(0, 0, 1), rotate_angle(1), rotate(rotate_angle, rotate_axis)
{
    init();
    add_control_point(vector3<double>(0, 1, 0));
    add_control_point(vector3<double>(0, 2, 1.6));
    add_control_point(vector3<double>(0, 3, 1.3));
    output_obj();
    
    opacity = 0.0;
    reflective = true;
    opacity = 0.83;
    //    color_feature.Kab = 0;
    //    color_feature.Kdb = 0;
    //    color_feature.Ksb = 0;
    refract_coefficient = 0.933;
    reflect_coefficient = 0.99;
}

Beizer_rotates::Beizer_rotates(vector3<double> input_axis) : rotate_axis(input_axis), rotate(rotate_angle, rotate_axis)
{
    init();
}

Beizer_rotates::~Beizer_rotates()
{
    
}

void Beizer_rotates::add_control_point(vector3<double> input_point)
{
    beizer_line.add_control_point(input_point);
}

void Beizer_rotates::generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes)
{
    int num = 1 / beizer_step + 1;           //beizer曲线方向上点的数量
    int counter = 0;
    
    for (double t = 0; t <= (1.0f + limit_zero); t += beizer_step)
    {
        points.push_back(beizer_line.get_point(t));
        counter++;
    }
    
    for (double angle = rotate_angle; angle < 360; angle += rotate_angle)//逐个生成点
    {
        for (int i = 0; i < num; i++)
        {
            vector3<double> temp = rotate.rotate_matrix * points[counter - num];
            points.push_back(temp);
            if (i == 0)
            {
                meshes.push_back(vector3<int>(counter - num + 1, counter - num + 2, counter + 1));
            }
            else if (i == num - 1)
            {
                meshes.push_back(vector3<int>(counter - num + 1, counter + 1, counter));
            }
            else
            {
                meshes.push_back(vector3<int>(counter - num + 1, counter - num + 2, counter + 1));
                meshes.push_back(vector3<int>(counter - num + 1, counter + 1, counter));
            }
            counter++; //counter计算生成了多少个点
        }
    }
    counter -= num;
    
    for (int i = 0; i < num; i++)
    {
        if (i == 0)
        {
            meshes.push_back(vector3<int>(counter + 1, counter + 2, i + 1));
        }
        else if (i == num - 1)
        {
            meshes.push_back(vector3<int>(counter + 1, i + 1, i));
        }
        else
        {
            meshes.push_back(vector3<int>(counter + 1, counter + 2, i + 1));
            meshes.push_back(vector3<int>(counter + 1, i + 1, i));
        }
        counter++;
    }
}

void Beizer_rotates::output_obj()
{
    FILE* stream = fopen("/Users/mac/Desktop/programme/program/4st_term/Ray_Tracing/beizer_lines.obj", "w");
    vector<vector3<double> > points;
    vector<vector3<int> > meshes;
    generate_meshes(points, meshes);
    
    for (int i = 0; i < points.size(); i++)
    {
        fprintf(stream, "v %lf %lf %lf\n", points[i].x, points[i].y, points[i].z);
    }
    for (int i = 0; i < meshes.size(); i++)
    {
        fprintf(stream, "f %d %d %d\n", meshes[i].x, meshes[i].y, meshes[i].z);
    }
    fclose(stream);
}

bool Beizer_rotates::intersect(Ray input_ray, vector3<double> &intersect_point)
{
    double t = 0.1, tl = 0.2, theta = 20;
    //cout << "an?" << endl;
    if(NewtonIteration(input_ray, t, tl, theta))
    {
        last_t = t;
        last_tl = tl;
        last_theta = theta;
        cout << t << " " << tl << " " << theta << endl;
        intersect_point = input_ray.start_point + input_ray.direction * t;
        return true;
    }
    return false;
}

Color Beizer_rotates::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)//in为法向量的引用
{
    light.direction = (target_pos - light.start_point).normallize();
    
    vector3<double> p_partial_t = beizer_line.Beizer_Derivative(last_tl);
    vector3<double> beizer_point = beizer_line.get_point(last_tl);
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
    return PhongModel::reflect_color(light, in, view_direction, feature);
}

bool Beizer_rotates::NewtonIteration(Ray input_ray, double& t, double& tl, double& theta)
{
    double delta_t = 0, delta_surfacet = 0, delta_theta = 0;
    for (int i = 0; i < 5; i++)
    {
        vector3<double> beizer_point = beizer_line.get_point(tl);
        vector3<double> beizer_partial_surfacet = beizer_line.Beizer_Derivative(tl);
        vector3<double> surface_partial_surfacet = vector3<double>(cos(theta) * beizer_partial_surfacet.x, sin(theta) * beizer_partial_surfacet.x, beizer_partial_surfacet.z);
        vector3<double> surface_partial_theta = vector3<double>(-1 * sin(theta) * beizer_point.x, cos(theta) * beizer_point.x, 0);
        vector3<double> f_value = input_ray.start_point + input_ray.direction * t - vector3<double>(beizer_point.x * cos(theta), beizer_point.x * sin(theta), beizer_point.z);
        
        vector3<double> tmp = surface_partial_surfacet.cross_product(surface_partial_theta);
        double D = input_ray.direction * tmp;
        
        
        if (abs(D) < limit_zero)
            return false;
        
        tmp = surface_partial_theta.cross_product(f_value);
        delta_t = surface_partial_surfacet * tmp / D;
        
        tmp =surface_partial_theta.cross_product(f_value);
        delta_surfacet = input_ray.direction * tmp / D;
        
        tmp = surface_partial_surfacet.cross_product(f_value);
        delta_theta = input_ray.direction * tmp / D;
        
        t -= delta_t;
        tl -= delta_surfacet;
        theta += delta_theta;
        cout << t << " " << tl << " " << theta << endl;
    }
    cout << "~~~~~~~" << endl;
    if (max(abs(delta_t), max(abs(delta_surfacet), abs(delta_theta))) > 0.001)          //认为迭代时迭飞了，没有交点
    {
        return false;
    }
    else
    {
        if (tl < -1 * limit_zero || tl > 1 + limit_zero)
        {
            return false;
        }
        return true;
    }
}

