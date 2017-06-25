//
//  Objects.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/15.
//  Copyright © 2017年 mac. All rights reserved.
//

#ifndef Objects_hpp
#define Objects_hpp

#include <stdio.h>
#pragma once
#include "Point.hpp"
#include "Ray.hpp"
#include "Drawing.hpp"
#include "PhotonModel.hpp"


class Object
{
public:
    enum Object_type//总共有4种object
    {
        _Plane = 0, _Sphere = 1,_Beizer_Surface = 2, _Beizer_Rotate = 3
    };
    Object_type object_type;
    
    virtual bool intersect(Ray input_ray, vector3<double> &intersect_point) = 0;             //求交
    virtual Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in) = 0;//根据光照模型获取target_pos上的颜色，view_direction是视点方向,同时获得法向量，最后一个参数引用法向量
    virtual vector3<double> get_normalvec(vector3<double> target_pos, vector3<double> view_direction) = 0;
    
    Object();
    ~Object();
    
    Material_feature color_feature;//光线追踪的feature
    object_feature feature;//对于一个光子来说object的feature
    double opacity = 0.5; //透明度
    bool reflective, refractive; //是否可反射，是否可折射
    double reflect_coefficient, refract_coefficient;//反射和折射的系数，光强衰减的大概
    double n;//折射率
    
protected:
    virtual void init() = 0;
};

#endif /* Objects_hpp */
