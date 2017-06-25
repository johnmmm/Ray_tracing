//
//  Plane.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/15.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "Plane.hpp"
#include "PhongModel.hpp"
#include "Drawing.hpp"
#include <iostream>
using namespace std;


Plane::Plane()
{
    init();
    A = 0, B = 0, C = 0, D = 0;
}

Plane::~Plane()
{
    
}

Plane::Plane(vector3<double> in_point, vector3<double> input_normal_vector)
{
    init();
    passed_point = in_point;
    normal_vector = input_normal_vector.normallize();
    A = normal_vector.x;
    B = normal_vector.y;
    C = normal_vector.z;
    D = -1 * (A * passed_point.x + B * passed_point.y + C * passed_point.z);

    n = 0;
}

void Plane::init()
{
    object_type = Object_type::_Plane;
}

bool Plane::intersect(Ray input_ray, vector3<double> &intersect_point)
{
    double denominator = input_ray.direction * normal_vector;
    double numerator = input_ray.start_point * normal_vector + D;
    
    if (abs(denominator) <= limit_zero)//直线与平面平行
    {
        return false;
    }
    else
    {
        double t = (-1 * numerator) / denominator;
        
        if (t < limit_zero)
            return false;

        else
        {
            intersect_point = input_ray.start_point + input_ray.direction * t;
            return true;
        }
    }
}

double Plane::signed_distance(Ray input_ray)
{
    double denominator = input_ray.direction * normal_vector;
    
    if (abs(denominator) < limit_zero)
        return std::numeric_limits<double>::infinity();

    else
    {
        double numerator = input_ray.start_point * normal_vector + D;
        double t = (-1 * numerator) / denominator;
        return t; //标准化的直线参数方程中,t即为距离
    }
}

Color Plane::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)
{
    light.direction = (target_pos - light.start_point).normallize();
    
    in = normal_vector.normallize();
    
    if(A == -1 && target_pos.y > -4.2 && target_pos.y < 4.2 && target_pos.z > -7.5 && target_pos.z < 7.5)//贴滑稽
    {
        object_feature feature1;
        feature1.absorb = 0.5;
        feature1.diffuse_reflect = 0.5;
        
        int yy = target_pos.y*100, zz = target_pos.z*100;
        yy /= 5;
        zz /= 5;

        feature1.reflect_blue = (double)image1.at<cv::Vec3b>(yy+84,zz+150)[0] / (double)255;
        feature1.reflect_green = (double)image1.at<cv::Vec3b>(yy+84,zz+150)[1] / (double)255;
        feature1.reflect_red = (double)image1.at<cv::Vec3b>(yy+84,zz+150)[2] / (double)255;
        
        return PhongModel::reflect_color(light, normal_vector, view_direction, feature1);
    }
    
    if(B == -1 && target_pos.x > -10.0 && target_pos.x < 10.0 && target_pos.z > -10.0 && target_pos.z < 10.0)//贴地板
    {
        double xx = (target_pos.x+10)/20, zz = (target_pos.z+10)/20;
        int xp = xx*599, zp = zz*599;
        
        object_feature feature1;
        feature1.absorb = 0.5;
        feature1.diffuse_reflect = 0.5;
        
        feature1.reflect_blue = (double)image3.at<cv::Vec3b>(xp,zp)[0] * 0.7 / (double)255;
        feature1.reflect_green = (double)image3.at<cv::Vec3b>(xp,zp)[1] * 0.7 / (double)255;
        feature1.reflect_red = (double)image3.at<cv::Vec3b>(xp,zp)[2] * 0.7 / (double)255;

        return PhongModel::reflect_color(light, in, view_direction, feature1);
    }
    
    if(C == -1 && target_pos.x > -10.0 && target_pos.x < 10.0 && target_pos.y > -10.0 && target_pos.y < 10.0)//贴右墙
    {
        double xx = (target_pos.x+10)/20, yy = (target_pos.y+10)/20;
        int xp = xx*299, yp = yy*299;
        
        vector3<double> qie_x, qie_y;
        qie_y = vector3<double>(1,0,0);
        qie_x = vector3<double>(0,1,0);
        double r_gradiant, g_gradiant, b_gradiant;
        r_gradiant = ((double)image4.at<cv::Vec3b>(yp,xp)[2] / (double)255 - 0.5) * 2;
        g_gradiant = ((double)image4.at<cv::Vec3b>(yp,xp)[1] / (double)255 - 0.5) * 2;
        b_gradiant = ((double)image4.at<cv::Vec3b>(yp,xp)[0]-128) / (double)128;
        
        in = vector3<double>(qie_x.x*r_gradiant+qie_y.x*g_gradiant+normal_vector.x*b_gradiant, qie_x.y*r_gradiant+qie_y.y*g_gradiant+normal_vector.y*b_gradiant, qie_x.z*r_gradiant+qie_y.z*g_gradiant+normal_vector.z*b_gradiant);
        in = in.normallize();
        
        return PhongModel::reflect_color(light, in, view_direction, feature);
    }
    
    if(B == 1 && target_pos.x > -10.0 && target_pos.x < 10.0 && target_pos.z > -10.0 && target_pos.z < 10.0)//贴天花板
    {
        double xx = (target_pos.x+10)/20, zz = (target_pos.z+10)/20;
        int xp = xx*500, zp = zz*500;
        
        vector3<double> qie_x, qie_y;
        qie_y = vector3<double>(1,0,0);
        qie_x = vector3<double>(0,0,1);
        double r_gradiant, g_gradiant, b_gradiant;
        r_gradiant = ((double)image6.at<cv::Vec3b>(zp,xp)[2] / (double)255 - 0.5) * 2;
        g_gradiant = ((double)image6.at<cv::Vec3b>(zp,xp)[1] / (double)255 - 0.5) * 2;
        b_gradiant = ((double)image6.at<cv::Vec3b>(zp,xp)[0]-128) / (double)128;
        
        in = vector3<double>(qie_x.x*r_gradiant+qie_y.x*g_gradiant+normal_vector.x*b_gradiant, qie_x.y*r_gradiant+qie_y.y*g_gradiant+normal_vector.y*b_gradiant, qie_x.z*r_gradiant+qie_y.z*g_gradiant+normal_vector.z*b_gradiant);
        in = in.normallize();
        
        return PhongModel::reflect_color(light, in, view_direction, feature);
    }
    
    return PhongModel::reflect_color(light, normal_vector, view_direction, feature);
}


vector3<double> Plane::get_normalvec(vector3<double> target_pos, vector3<double> view_direction)//法向量
{
    return normal_vector.normallize();
}

