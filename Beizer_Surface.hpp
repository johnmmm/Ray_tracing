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
#include "Point.hpp"
using namespace std;


class Beizer_Surface
{
public:
    Beizer_Surface(int input_line, int input_row);//指定biezer_surface几行几列
    ~Beizer_Surface();
    
    void set_control_point(int x, int y, vector3<double> input);//设置第x行第y列
    void generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes);//产生曲面所对应的网格
    void output_obj();//输出obj文件
    vector3<double> get_point(double u, double v);//获得参数为u, v的曲面上的点
    
    double du = 0.011f, dv = 0.011f;
    vector3<double> **controlled_points;
    int line, row;
};

#endif /* Beizer_Surface_hpp */
