//
//  Beizer_Surface.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/21.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "Beizer_Surface.hpp"


Beizer_Surface::Beizer_Surface(int input_line, int input_row): line(input_line), row(input_row)
{
    controlled_points = new vector3<double>*[line];
    for (int i = 0; i < line; i++)
    {
        controlled_points[i] = new vector3<double>[row];
    }
}

Beizer_Surface::~Beizer_Surface()//删除占用空间
{
    for (int i = 0; i < line; i++)
    {
        delete[] controlled_points[i];
    }
    delete[] controlled_points;
}


void Beizer_Surface::set_control_point(int x, int y, vector3<double> input)
{
    controlled_points[x][y] = input;
}

int Combination(int n, int m)
{
    const int M = 10007;
    int ans = 1;
    for(int i=n; i>=(n-m+1); --i)
        ans *= i;
    while(m)
        ans /= m--;
    return ans % M;
}

double Bij(double a, double b, double uv)
{
    double ans = 0;
    ans = (double)Combination(b,a) * pow(uv,a) * pow(1-uv,b-a);
    return ans;
}

vector3<double> Beizer_Surface::get_point(double u, double v)
{
    vector3<double> vecuv(0,0,0);
    for (int i = 0; i < row; i++)
    {
        for(int j = 0; j < line; j++)
        {
            vecuv = vecuv + controlled_points[i][j] * Bij(i,row-1,v) * Bij(j,line-1,u);
        }
    }
    return vecuv;
}

void Beizer_Surface::generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes)
{
    int num_u = 1 / du + 1, num_v = 1 / dv + 1;        //将要生成的u, v的数量
    int counter = 0;
    for (double u = 0.0f, i = 0; u <= (1.0f + limit_zero); u += du, i++)
    {
        for (double v = 0.0f, j = 0; v <= (1.0f + limit_zero); v += dv, j++)
        {
            points.push_back(get_point(u, v));
            counter++;
            if (i != 0 && j != 0)
            {
                meshes.push_back(vector3<int>(counter - num_v - 1, counter - num_v, counter - 1));
                meshes.push_back(vector3<int>(counter - num_v, counter, counter - 1));
            }
        }
    }
}

void Beizer_Surface::output_obj()
{
    FILE* stream = fopen("/Users/mac/Desktop/programme/program/4st_term/Ray_Tracing/beizer_surface.obj", "w");
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