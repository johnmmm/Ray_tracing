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
    init();
    
//    opacity = 0.0;
//    reflective = true;
//    opacity = 0.83;
//    color_feature.Kab = 0;
//    color_feature.Kdb = 0;
//    color_feature.Ksb = 0;
//    refract_coefficient = 0.933;
//    reflect_coefficient = 0.99;
//    n = 1.5;
    
    controlled_points = new vector3<double>*[line];
    for (int i = 0; i < line; i++)
    {
        controlled_points[i] = new vector3<double>[row];
    }
    
    set_control_point(0, 0, vector3<double>(0, 0, 0));
    set_control_point(0, 1, vector3<double>(0, 1.5, 1));
    set_control_point(0, 2, vector3<double>(0, 2, 0.5));
    set_control_point(1, 0, vector3<double>(1, 0, 0.3));
    set_control_point(1, 1, vector3<double>(1, 1, 10));
    set_control_point(1, 2, vector3<double>(1, 2, 0.9));
    set_control_point(2, 0, vector3<double>(2, 0, -0.2));
    set_control_point(2, 1, vector3<double>(2, 1.3, 0.05));
    set_control_point(2, 2, vector3<double>(1, 2.2, 0.8));
    output_obj();
}

Beizer_Surface::~Beizer_Surface()//删除占用空间
{
    for (int i = 0; i < line; i++)
    {
        delete[] controlled_points[i];
    }
    delete[] controlled_points;
}

void Beizer_Surface::init()
{
    object_type = Object_type::_Beizer_Surface;
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

double Bij_dao(double a, double b, double uv)
{
    double ans = 0;
    ans = (double)Combination(b,a) * (a * pow(uv, a-1) * pow(1-uv, b-a) + (a-b) * pow(uv, a) * pow(1-uv, b-a-1));
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

vector3<double> Beizer_Surface::getdpdu(double u, double v)
{
    vector3<double> vecuv(0,0,0);
    for (int i = 0; i < row; i++)
    {
        for(int j = 0; j < line; j++)
        {
            vecuv = vecuv + controlled_points[i][j] * Bij(i,row-1,v) * Bij_dao(j,line-1,u);
        }
    }
    return vecuv;
}

vector3<double> Beizer_Surface::getdpdv(double u, double v)
{
    vector3<double> vecuv(0,0,0);
    for (int i = 0; i < row; i++)
    {
        for(int j = 0; j < line; j++)
        {
            vecuv = vecuv + controlled_points[i][j] * Bij_dao(i,row-1,v) * Bij(j,line-1,u);
        }
    }
    return vecuv;
}

bool Beizer_Surface::NewtonIteration(Ray input_ray, double& t, double& u, double& v)
{
    double delta_t = 0, delta_u = 0, delta_v = 0;
    for (int i = 0; i < 10; i++)
    {
        //vector3<double> beizer_point = get_point(u,v);
        
        vector3<double> surface_partial_du = getdpdu(u,v);
        vector3<double> surface_partial_dv = getdpdv(u,v);
        
        vector3<double> f_value = input_ray.start_point + input_ray.direction * t - get_point(u, v);
        
        vector3<double> tmp = surface_partial_du.cross_product(surface_partial_dv);
        double D = input_ray.direction * tmp;
        
        if (abs(D) < limit_zero)
            return false;
        
        tmp = surface_partial_dv.cross_product(f_value);
        delta_t = surface_partial_du * tmp / D;
        
        tmp = surface_partial_dv.cross_product(f_value);
        delta_u = input_ray.direction * tmp / D;
        
        tmp = surface_partial_du.cross_product(f_value);
        delta_v = input_ray.direction * tmp / D;
        
        t -= delta_t*(1+0.001);
        u -= delta_u*(1+0.001);
        v += delta_v*(1+0.001);
        
        //cout << t << " " << u << " " << v << endl;
    }
    //cout << "~~~~~~~~~~" << endl;
    if (abs(delta_t) > solve_precision)          //认为迭代时迭飞了，没有交点
    {
        return false;
    }
    else
    {
        if (u < limit_zero || u > 1 - limit_zero || v < limit_zero || v > 1 - limit_zero || t < limit_zero)
        {
            return false;
        }
        //cout << "uv: " << u << " " << v << endl;
        return true;
    }
}

void Beizer_Surface::generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes)
{
    int num_u = 1 / du + 1, num_v = 1 / dv + 1;        //将要生成的u, v的数量
    int counter = 0;
    for (double u = 0.0f, i = 0; u <= (1.0f + limit_zero); u += du, i++)
    {
        for (double v = 0.0f, j = 0; v <= (1.0f + limit_zero); v += dv, j++)
        {
            vector3<double> vecuv = get_point(u, v);
            vector3<double> vecn(0,0,0);
            vecn = vecuv - BallPoint;
            vecn = vecn.normallize();
            
            int tmmp = vecn.x * 10;
            vecn.x = double(tmmp) / 10;
            tmmp = vecn.y * 10;
            vecn.y = double(tmmp) / 10;
            tmmp = vecn.z * 10;
            vecn.z = double(tmmp) / 10;
            
            uvmap[vecn] = vector2<double>(u, v);
            //cout << "uv" << u << " " << v << endl;
            
            points.push_back(vecuv);
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

bool Beizer_Surface::intersect(Ray input_ray, vector3<double> &intersect_point)
{
    double t = 0.1, u = 0.2, v = 0.2;
//    u = (double)(rand() % 8 + 1) / 10;
//    v = (double)(rand() % 8 + 1) / 10;
    vector3<double> ballvecs(0,0,0);
    if(ball_intersect(input_ray, intersect_point))
    {
//        vector3<double> vecn(0,0,0);
//        vecn = intersect_point - BallPoint;
//        vecn = vecn.normallize();
//        
//        int tmmp = vecn.x * 10;
//        vecn.x = double(tmmp) / 10;
//        tmmp = vecn.y * 10;
//        vecn.y = double(tmmp) / 10;
//        tmmp = vecn.z * 10;
//        vecn.z = double(tmmp) / 10;
//        cout << vecn.x << " " << vecn.y << " " << vecn.z << endl;
//        
//        u = uvmap[vecn].x + 0.001;
//        v = uvmap[vecn].y + 0.001;
//        cout << "uv" << u << " " << v << endl;
        if(NewtonIteration(input_ray, t, u, v))
        {
            //cout << "uv" << u << " " << v << endl;
            //        int tmmp = u * 1000;
            //        u = double(tmmp) / 1000;
            //        tmmp = v * 1000;
            //        v = double(tmmp) / 1000;
            
            intersect_point = get_point(u, v);
            //uvmap[intersect_point] = vector2<double>(u, v);
            
            last_u = u;
            last_v = v;
            
            //cout << "uv" << u << " " << v << endl;
            //cout << "Points:" << intersect_point.x << " " << intersect_point.y << " " << intersect_point.z << endl;
            return true;
        }
    }
    return false;
}

bool Beizer_Surface::ball_intersect(Ray input_ray, vector3<double> &intersect_point)
{
    intersect_point = input_ray.start_point;
    double radius = 2.7;
    double square_radius = radius * radius;

    vector3<double> l = BallPoint - input_ray.start_point;
    double direction_radius_dot = l * input_ray.direction;
    if (l.length > radius && fabs(l.length - radius) >= limit_zero)//光源必须在球外面
    {
        if (direction_radius_dot > 0)
        {
            double square_distance = l.length * l.length - direction_radius_dot * direction_radius_dot;
            if (square_distance > square_radius || fabs(square_distance - square_radius) < limit_zero) //相切为不相交
            {
                return false;
            }
            else
            {
                double square_t1 = square_radius - square_distance;
                double t1 = sqrt(square_t1);
                double t = direction_radius_dot - t1;
                intersect_point = input_ray.start_point + input_ray.direction * t;
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    
    //光源在球面上（需要进行判断，如果光线的前进方向与圆心距离变近，那么求交，如果前进方向与圆心距离变远，那么不相交）
    else if(abs(l.length - radius) < limit_zero)
    {                                            //可以根据光线的方向与到圆心的点积判断(锐角，则靠近，钝角，则远离)
        if(direction_radius_dot > 0)          //光线与球心的距离变远
        {
            double square_distance = l.length * l.length - direction_radius_dot * direction_radius_dot;
            double square_t1 = square_radius - square_distance;
            double t1 = sqrt(square_t1);
            double t = direction_radius_dot + t1;
            intersect_point = input_ray.start_point + input_ray.direction * t;
            return true;
        }
        else                                 //变近？
        {
            return false;
        }
    }
    else                                               //光源在球面内
    {
        return true;
    }
    return true;
}

Color Beizer_Surface::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)   //in为法向量的引用
{
    //cout << "fuck YOU" << endl;
    light.direction = (target_pos - light.start_point).normallize();
    
//    vector2<double> uv = uvmap[target_pos];
//    double u1 = uv.x;
//    double v1 = uv.y;
    //cout << u1 << " " << v1 << endl;
    
    vector3<double> du = getdpdu(last_u,last_v);
    vector3<double> dv = getdpdv(last_u,last_v);
    
    in = du.cross_product(dv);
    in = in.normallize();

    if (in * light.direction > 0)
    {
        in = in * -1;
    }
    return PhongModel::reflect_color(light, in, view_direction, feature);
    
}

vector3<double> Beizer_Surface::get_normalvec(vector3<double> target_pos, vector3<double> view_direction)
{
    vector3<double> du = getdpdu(last_u,last_v);
    vector3<double> dv = getdpdv(last_u,last_v);
    
    return du.cross_product(dv);
}

