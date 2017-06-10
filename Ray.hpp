//
//  Ray.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/9.
//  Copyright © 2017年 mac. All rights reserved.
//

//进行光线的标记，还有光源
#ifndef Ray_hpp
#define Ray_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Drawing.hpp"
#include <vector>
#include <iostream>
using namespace std;

class Ray
{
public:
    vector3<double> start_point;   //开始点和方向
    vector3<double> direction;
    Ray(vector3<double> input_point, vector3<double> input_direction);
    virtual ~Ray();
};

class Single_Light : public Ray   //点光源
{
public:
    double intensity; // 强度
    Color color;
    //起点，方向，强度，颜色（前两个继承前面的）
    Single_Light(vector3<double> input_point, vector3<double> input_direction, double input_intensity, Color in_color) : Ray(input_point, input_direction)
    {
        intensity = input_intensity;
        color = in_color;
    }
    ~Single_Light()
    {
        
    }
};

class Light
{
public:
    vector<Single_Light> each_light;//记录光点们
    double intensity; //强度
    
    Light()
    {
        intensity = 0.9;
        Single_Light single_light(vector3<double>(0, 0, 8), vector3<double>(0, 0, -1), 1, Color(255, 255, 255, 255));
        each_light.push_back(single_light);
        //自己默认自己的光源位置
    }
    
    Light(vector3<double> light_point, vector3<double> direction, double input_intensity)
    {
        intensity = input_intensity;
        Single_Light single_light(light_point, direction, input_intensity, Color(255, 255, 255, 255));
        each_light.push_back(single_light);
        //单个白光源
    }
    
    Light(vector3<double> start_point, vector3<double> end_point, vector3<double> direction, int light_num, double input_intensity)
    {
        intensity = input_intensity;
        double each_intensity = intensity / light_num;
        vector3<double> diff((end_point.x - start_point.x) / light_num, (end_point.y - start_point.y) / light_num, (end_point.z - start_point.z) / light_num);
        for (int i = 0; i < light_num; i++)
        {
            //cout << start_point << endl;
            Single_Light single_light(start_point, direction, each_intensity, Color(255, 255, 255, 255));
            each_light.push_back(single_light);
            start_point = start_point + diff;
        }
        //多个白点光源
    }
    
    //面光源？？？
};

struct Material_feature //物体的各种反射系数
{
    double Kdr = 0, Kdg = 0, Kdb = 0;//漫反射
    double Ksr = 0, Ksg = 0, Ksb = 0;//
    double Kar = 0, Kag = 0, Kab = 0;//
};


#endif /* Ray_hpp */
