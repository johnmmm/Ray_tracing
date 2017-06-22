//
//  Beizer_Surface.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/21.
//  Copyright © 2017年 mac. All rights reserved.
//

#ifndef Beizer_Surface_hpp
#define Beizer_Surface_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include "Point.hpp"
#include "Objects.hpp"
#include "PhongModel.hpp"
using namespace std;


class Beizer_Surface : public Object
{
public:
    //Beizer_Surface(){init();}
    Beizer_Surface(int input_line=3, int input_row=3);//指定biezer_surface几行几列
    ~Beizer_Surface();
    
    void set_control_point(int x, int y, vector3<double> input);//设置第x行第y列
    void generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes);//产生曲面所对应的网格
    void output_obj();//输出obj文件
    vector3<double> get_point(double u, double v);//获得参数为u, v的曲面上的点
    vector3<double> getdpdu(double u, double v);
    vector3<double> getdpdv(double u, double v);
    bool NewtonIteration(Ray input_ray, double& t, double& u, double& v);//牛顿迭代法求交
    void init();
    
    bool intersect(Ray input_ray, vector3<double> &intersect_point);
    bool ball_intersect(Ray input_ray, vector3<double> &ball_vec);
    Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);   //in为法向量的引用
    vector3<double> get_normalvec(vector3<double> target_pos, vector3<double> view_direction);//法向量
    
    double du = 0.011f, dv = 0.011f;
    double solve_precision = 0.001;
    vector3<double> **controlled_points;
    int line, row;
    map<vector3<double>, vector2<double>> uvmap;
    double last_u, last_v;
    vector3<double> BallPoint = vector3<double>(8/9, 10/9, 13.35/9);
};

#endif /* Beizer_Surface_hpp */
