//
//  Beizer_rotates.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/20.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "Beizer_rotates.hpp"
#include <cstdio>


Beizer_rotates::Beizer_rotates() : rotate_axis(0, 0, 1), rotate_angle(1), rotate(rotate_angle, rotate_axis)
{
    
}

Beizer_rotates::Beizer_rotates(vector3<double> input_axis) : rotate_axis(input_axis), rotate(rotate_angle, rotate_axis)
{
    
}

Beizer_rotates::~Beizer_rotates()
{
}

void Beizer_rotates::add_control_point(vector3<double> input_point)
{
    beizer_line.add_control_point(input_point);
}

void Beizer_rotates::generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes)
{
    int num = 1 / beizer_step + 1;           //beizer曲线方向上点的数量
    int counter = 0;
    
    for (double t = 0; t <= (1.0f + limit_zero); t += beizer_step)
    {
        points.push_back(beizer_line.get_point(t));
        counter++;
    }
    
    for (double angle = rotate_angle; angle < 360; angle += rotate_angle)//逐个生成点
    {
        for (int i = 0; i < num; i++)
        {
            vector3<double> temp = rotate.rotate_matrix * points[counter - num];
            points.push_back(temp);
            if (i == 0)
            {
                meshes.push_back(vector3<int>(counter - num + 1, counter - num + 2, counter + 1));
            }
            else if (i == num - 1)
            {
                meshes.push_back(vector3<int>(counter - num + 1, counter + 1, counter));
            }
            else
            {
                meshes.push_back(vector3<int>(counter - num + 1, counter - num + 2, counter + 1));
                meshes.push_back(vector3<int>(counter - num + 1, counter + 1, counter));
            }
            counter++; //counter计算生成了多少个点
        }
    }
    counter -= num;
    
    for (int i = 0; i < num; i++)
    {
        if (i == 0)
        {
            meshes.push_back(vector3<int>(counter + 1, counter + 2, i + 1));
        }
        else if (i == num - 1)
        {
            meshes.push_back(vector3<int>(counter + 1, i + 1, i));
        }
        else
        {
            meshes.push_back(vector3<int>(counter + 1, counter + 2, i + 1));
            meshes.push_back(vector3<int>(counter + 1, i + 1, i));
        }
        counter++;
    }
}

void Beizer_rotates::output_obj()
{
    FILE* stream = fopen("/Users/mac/Desktop/programme/program/4st_term/Ray_Tracing/beizer.obj", "w");
    vector<vector3<double> > points;
    vector<vector3<int> > meshes;
    generate_meshes(points, meshes);
    
    for (int i = 0; i < points.size(); i++)
    {
        fprintf(stream, "v %lf %lf %lf\n", points[i].x, points[i].y, points[i].z);
    }
    for (int i = 0; i < meshes.size(); i++)
    {
        fprintf(stream, "f %d %d %d\n", meshes[i].x, meshes[i].y, meshes[i].z);
    }
    fclose(stream);
}