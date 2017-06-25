//
//  PhotonModel.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/22.
//  Copyright © 2017年 mac. All rights reserved.
//

#ifndef PhotonModel_hpp
#define PhotonModel_hpp

#include <stdio.h>
#include "Ray.hpp"
#include "Drawing.hpp"


struct photon
{
    photon(vector3<double> input_start, vector3<double> input_direction, Color input_color) : photon_ray(input_start, input_direction), color(input_color){}
    
    Ray photon_ray;//光子的起始点和方向
    Color color;//光子的颜色
    photon() = default;
};

struct object_feature//物体的特性
{
    double specular_reflect = 0;//镜面反射，漫反射，折射，吸收所占的权重
    double diffuse_reflect = 0;
    double refract = 0;
    double absorb = 0;
    double reflect_red = 1, reflect_green = 1, reflect_blue = 1;
    double refract_red = 1, refract_green = 1, refract_blue = 1;
    double pd = 0, ps = 0;//phong模型中漫反射光和镜面反射光的反射率
};


class PhotonModel
{
public:
    PhotonModel();
    ~PhotonModel();
};

#endif /* PhotonModel_hpp */
