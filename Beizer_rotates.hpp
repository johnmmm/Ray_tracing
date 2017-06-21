//
//  Beizer_rotates.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/20.
//  Copyright © 2017年 mac. All rights reserved.
//

#ifndef Beizer_rotates_hpp
#define Beizer_rotates_hpp

#include <stdio.h>
#include <vector>
#include "Beizer_Lines.hpp"
#include "Point.hpp"
#include "Objects.hpp"
#include "PhongModel.hpp"
using namespace std;

const double pi = 3.1415926;


class Rotate
{
public:
    Matrix3<double> rotate_matrix;         //生成旋转矩阵
    Rotate(double input_angle, vector3<double> input_axis)
    {
        axis = input_axis.normallize();
        angle = input_angle;
        double cos_a = cos((angle / 180) * pi);
        double sin_a = sin((angle / 180) * pi);
        rotate_matrix.Array[0][0] = cos_a + (1 - cos_a) * axis.x * axis.x;
        rotate_matrix.Array[0][1] = (1 - cos_a) * axis.x * axis.y - axis.z * sin_a;
        rotate_matrix.Array[0][2] = (1 - cos_a) * axis.x * axis.z + axis.y * sin_a;
        rotate_matrix.Array[1][0] = (1 - cos_a) * axis.y * axis.x + axis.z * sin_a;
        rotate_matrix.Array[1][1] = cos_a + (1 - cos_a) * axis.y * axis.y;
        rotate_matrix.Array[1][2] = (1 - cos_a) * axis.y * axis.z - axis.x * sin_a;
        rotate_matrix.Array[2][0] = (1 - cos_a) * axis.z * axis.x - axis.y * sin_a;
        rotate_matrix.Array[2][1] = (1 - cos_a) * axis.z * axis.y + axis.x * sin_a;
        rotate_matrix.Array[2][2] = cos_a + (1 - cos_a) * axis.z * axis.z;
    }

private:
    double angle;//旋转角度
    vector3<double> axis;//旋转轴
};



class Beizer_rotates : public Object
{
public:
    void init();
    
    Beizer_rotates();                          //默认是按0, 0, 1旋转的
    Beizer_rotates(vector3<double> input_axis);
    ~Beizer_rotates();
    
    vector3<double> rotate_axis;             //Beizer曲线所绕着旋转的轴,是单位化了的
    double rotate_angle, beizer_step = 0.1;             //每次旋转所转的角度与Beizer曲线上t的步长（控制图像的精细程度）
    
    void add_control_point(vector3<double> input_point);
    void generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes);          //产生曲线所对应的网格
    void output_obj();//输出为obj文件
    
    bool intersect(Ray input_ray, vector3<double> &intersect_point);
    Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);   //in为法向量的引用
    bool NewtonIteration(Ray input_ray, double& t, double& tl, double& theta);
    
    double last_t = 0, last_tl = 0, last_theta = 0;

    Beizer_Lines beizer_line;
    Rotate rotate;
};

#endif /* Beizer_rotates_hpp */
