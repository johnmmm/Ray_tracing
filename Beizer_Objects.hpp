//
//  Beizer_Objects.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/21.
//  Copyright © 2017年 mac. All rights reserved.
//

#ifndef Beizer_Objects_hpp
#define Beizer_Objects_hpp

#include <stdio.h>
#include <map>
#include "Beizer_Surface.hpp"
#include "Beizer_Lines.hpp"
#include "Objects.hpp"
#include "PhongModel.hpp"

struct section       //区间（左闭右开区间）
{
    double Min;
    double Max;
    section(double in_min, double in_max): Min(in_min), Max(in_max)
    {
        
    }
    section() :Min(0), Max(0)
    {
        
    }
};

class Beizer_Objects : public Object
{
public:
    Beizer_Objects(int line, int row, vector3<double> point_array[]);
    ~Beizer_Objects();
    
    bool intersect(Ray input_ray, vector3<double> &intersect_point);
    Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);   //in为法向量的引用
    bool NewtonIteration(Ray input_ray, double& t, double& u, double& v);             //t是直线的参数，u,v是曲面的参数
    
    void init();
    
    Beizer_Surface beizer_surface;
    Beizer_Lines beizer_line;
    //BoundingBox* box;           //当前Beizer曲面的包围盒
    int last_index;
    map<vector3<double>, int> point_index_map;             //存储点对应的三角面片的索引
    
    
    bool intersect1(Ray input_ray, vector3<double>& input_point);
    section* x_sections;            //缓存沿Beizer曲线x方向不同参数的最大值与最小值
    section* z_sections;            //缓存沿Beizer曲线z方向不同参数的最大值与最小值
    const double solve_precision = 0.001;       //beizer曲线求交时的精度
    const int divide = 512;           //根据参数将beizer曲线（以及旋转）划分为多少块
    const int iteration_times = 5;   //牛顿迭代的迭代次数
    const double min_distance = 0.1;        //上一个交点与下一个交点的最短距离
    
    
    
    double beizer_xa, beizer_xb, beizer_xc;         //Beizer曲线对应的x方向上的导函数的参数（ax^2 + bx + c）
    double beizer_za, beizer_zb, beizer_zc;         //Beizer曲线对应的z方向上的导函数的参数（az^2 + bz + c）
    double extreme_x1, extreme_x2;                  //Beizer曲线对应的x方向上极值点的参数（二次方程有两个解）
    double extreme_z1, extreme_z2;                  //Beizer曲线对应的z方向上极值点的参数
    section get_section_x(int t);            //获取[t,t + 1)的最大值与最小值
    section get_section_z(int t);
    
    double last_linet, last_surfacet, last_theta;
};


#endif /* Beizer_Objects_hpp */
