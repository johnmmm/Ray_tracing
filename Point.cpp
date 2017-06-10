//
//  Point.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/9.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "Point.hpp"
using namespace std;

std::ostream& operator<<(std::ostream& out, const vector3<double>& s)
{
    out << "[" << s.x << " ," << s.y << " ," << s.z << "]";
    return out;
}

std::ostream& operator<<(std::ostream& out, const vector3<int>& s)
{
    out << "[" << s.x << " ," << s.y << " ," << s.z << "]";
    return out;
}

vector3<double> reflect(vector3<double> in, vector3<double> normal_vector)
{
    if (normal_vector * in > 0)//判断夹角
    {
        normal_vector = normal_vector * -1;
    }
    return in - normal_vector * (2 * (in * normal_vector));
}

//判断是否会发生全反射
bool refract(vector3<double> in, vector3<double> normal_vector, double ni, double nt, vector3<double> &out)
{
    in = in * -1;
    double cos_i = in * normal_vector;//叉乘
    if (cos_i < 0)//判断法向量方向
    {
        cos_i *= -1;
        normal_vector = normal_vector * -1;
    }
    double ni_cp_nt = ni / nt;//n的比例
    double square_cos_t = 1 - ni_cp_nt * ni_cp_nt * (1 - cos_i * cos_i);
    if (square_cos_t <= 0 || std::abs(square_cos_t) < limit_zero)
    {
        return false;
    }
    double cos_t = sqrt(square_cos_t);
    out = (in * (-1 * (ni_cp_nt)) + normal_vector * (ni_cp_nt * cos_i - cos_t)).normallize();
    return true;
}

