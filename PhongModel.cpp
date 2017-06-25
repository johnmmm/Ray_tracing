//
//  PhongModel.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/15.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "PhongModel.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

int PhongModel::reflect_parameter = 10;
double PhongModel::amplify_parameter = 2.5;

PhongModel::PhongModel()
{
    
}


PhongModel::~PhongModel()
{
    
}

Color PhongModel::reflect_color(Single_Light light, vector3<double> normal_vector, vector3<double> view_direction, object_feature feature)
{
    double r = 0;
    double g = 0;
    double b = 0;
    vector3<double> reverse_light = light.direction * -1;
    vector3<double> reverse_view = view_direction * -1;
    double L_N_dot = reverse_light * normal_vector;
    
    if (L_N_dot < 0)
        L_N_dot = 0;
    
    vector3<double> angle_bisector = (reverse_light + reverse_view).normallize();          
    double R_V_dot = angle_bisector * normal_vector;
    
    if (R_V_dot < 0)
        R_V_dot = 0;
    
    r += light.intensity * light.color.r * feature.diffuse_reflect * feature.reflect_red * L_N_dot;
    g += light.intensity * light.color.g * feature.diffuse_reflect * feature.reflect_green * L_N_dot;
    b += light.intensity * light.color.b * feature.diffuse_reflect * feature.reflect_blue * L_N_dot;
    r += light.intensity * light.color.r * feature.specular_reflect * feature.reflect_red * pow(R_V_dot, reflect_parameter);
    g += light.intensity * light.color.g * feature.specular_reflect * feature.reflect_green * pow(R_V_dot, reflect_parameter);
    b += light.intensity * light.color.b * feature.specular_reflect * feature.reflect_blue * pow(R_V_dot, reflect_parameter);
//    r += light.intensity * light.color.r * feature.Kdr * L_N_dot;
//    g += light.intensity * light.color.g * feature.Kdg * L_N_dot;
//    b += light.intensity * light.color.b * feature.Kdb * L_N_dot;
//    r += light.intensity * light.color.r * feature.Ksr * pow(R_V_dot, reflect_parameter);
//    g += light.intensity * light.color.g * feature.Ksg * pow(R_V_dot, reflect_parameter);
//    b += light.intensity * light.color.b * feature.Ksb * pow(R_V_dot, reflect_parameter);
//    r += light.intensity * light.color.r * feature.Kar;
//    g += light.intensity * light.color.g * feature.Kag;
//    b += light.intensity * light.color.b * feature.Kab;
    r *= amplify_parameter;
    g *= amplify_parameter;
    b *= amplify_parameter;
    
    r = min(r, 255.0);
    g = min(g, 255.0);
    b = min(b, 255.0);
    
    return Color((unsigned char)r, (unsigned char)g, (unsigned char)b, 255);
}

double PhongModel::PhongBRDF(vector3<double> normal_vector, vector3<double> in_direction, vector3<double> view_direction, double pd, double ps)
{
    vector3<double> reverse_view = view_direction * -1;
    vector3<double> reverse_direction = in_direction * -1;
    double L_N_dot = reverse_direction * normal_vector;
    
    if (L_N_dot < limit_zero)
        return 0;
    
    vector3<double> angle_bisector = (reverse_direction + reverse_view).normallize();             //求角平分线
    double R_V_dot = angle_bisector * normal_vector;
    
    if (R_V_dot < 0)
        R_V_dot = 0;
    
    return (pd + ps * pow(R_V_dot, reflect_parameter) / L_N_dot) * amplify_parameter;
}