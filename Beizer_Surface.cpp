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
    srand((unsigned)time(NULL));
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
    
//    set_control_point(0, 0, vector3<double>(0, 0, -5));
//    set_control_point(0, 1, vector3<double>(0, 1.5, -4));
//    set_control_point(0, 2, vector3<double>(0, 2, -4.5));
//    set_control_point(0, 3, vector3<double>(0, 2.5, -4));
//    set_control_point(1, 0, vector3<double>(1, 0, -4.7));
//    set_control_point(1, 1, vector3<double>(1, 1, 5));
//    set_control_point(1, 2, vector3<double>(1, 2, -4.1));
//    set_control_point(1, 3, vector3<double>(1, 3, 4.4));
//    set_control_point(2, 0, vector3<double>(2, 0, -5.2));
//    set_control_point(2, 1, vector3<double>(2, 1.3, -4.95));
//    set_control_point(2, 2, vector3<double>(1, 2.2, -4.2));
//    set_control_point(2, 3, vector3<double>(1, 3.2, -3.8));
//    set_control_point(3, 0, vector3<double>(3, 0, -4.7));
//    set_control_point(3, 1, vector3<double>(3, 1, 5));
//    set_control_point(3, 2, vector3<double>(2, 2, -4.1));
//    set_control_point(3, 3, vector3<double>(3, 3, 4.4));
    
//    set_control_point(0, 0, vector3<double>(0.6, 0.8, 0));
//    set_control_point(0, 1, vector3<double>(-0.8, 0.6, 0));
//    set_control_point(0, 2, vector3<double>(0.8, -0.6, 0));
//    set_control_point(0, 3, vector3<double>(-0.6, -0.8, 0));
//    set_control_point(1, 0, vector3<double>(0.9, 1.2, -1));
//    set_control_point(1, 1, vector3<double>(-1.2, 0.6, -1));
//    set_control_point(1, 2, vector3<double>(1.2, -0.6, -1));
//    set_control_point(1, 3, vector3<double>(-0.9, -1.2, -1));
//    set_control_point(2, 0, vector3<double>(1.4, 1.4, -2.2));
//    set_control_point(2, 1, vector3<double>(-1.4, 1.4, -2.3));
//    set_control_point(2, 2, vector3<double>(1.4, -1.4, -2.2));
//    set_control_point(2, 3, vector3<double>(-1.4, -1.4, -2.3));
//    set_control_point(3, 0, vector3<double>(1.5, 1.5, -3.5));
//    set_control_point(3, 1, vector3<double>(-1.5, 1.5, -3.5));
//    set_control_point(3, 2, vector3<double>(1.5, -1.5, -3.6));
//    set_control_point(3, 3, vector3<double>(-1.5, -1.5, -3.5));
    
    //正着的曲面
//    set_control_point(0, 0, vector3<double>(7, 9.2, -9));
//    set_control_point(0, 1, vector3<double>(7.5, 6.8, -6.99));
//    set_control_point(0, 2, vector3<double>(8, 7.8, -5.60));
//    set_control_point(0, 3, vector3<double>(7, 9, -4));
//    set_control_point(1, 0, vector3<double>(5, 7.4, -9));
//    set_control_point(1, 1, vector3<double>(5, 6.2, -7.20));
//    set_control_point(1, 2, vector3<double>(5, 7, -5.80));
//    set_control_point(1, 3, vector3<double>(5, 8.2, -4));
//    set_control_point(2, 0, vector3<double>(3.5, 8.2, -9));
//    set_control_point(2, 1, vector3<double>(3.5, 8.6, -6.9));
//    set_control_point(2, 2, vector3<double>(3.5, 9.8, -5.55));
//    set_control_point(2, 3, vector3<double>(3.5, 8.5, -4));
//    set_control_point(3, 0, vector3<double>(2, 9, -9));
//    set_control_point(3, 1, vector3<double>(2.5, 8.6, -7.36));
//    set_control_point(3, 2, vector3<double>(2.5, 9.2, -5.67));
//    set_control_point(3, 3, vector3<double>(2, 9, -4));
    
    //倒过来的曲面
//    set_control_point(0, 0, vector3<double>(1, 7, -8));
//    set_control_point(0, 1, vector3<double>(0.5, 9, -6.8));
//    set_control_point(0, 2, vector3<double>(0, 8, -5.40));
//    set_control_point(0, 3, vector3<double>(1, 7, -4));
//    set_control_point(1, 0, vector3<double>(3, 6.5, -9));
//    set_control_point(1, 1, vector3<double>(3, 8, -7.40));
//    set_control_point(1, 2, vector3<double>(3, 9, -5.40));
//    set_control_point(1, 3, vector3<double>(3, 8.5, -4));
//    set_control_point(2, 0, vector3<double>(4.5, 9, -8));
//    set_control_point(2, 1, vector3<double>(4.5, 9.5, -6.4));
//    set_control_point(2, 2, vector3<double>(4.5, 8.5, -5.25));
//    set_control_point(2, 3, vector3<double>(4.5, 7.5, -4));
//    set_control_point(3, 0, vector3<double>(6, 7, -8));
//    set_control_point(3, 1, vector3<double>(5.5, 8, -6.66));
//    set_control_point(3, 2, vector3<double>(5.5, 7.5, -5.33));
//    set_control_point(3, 3, vector3<double>(6, 7, -4));
    
//    set_control_point(0, 0, vector3<double>(1, 9, -8));
//    set_control_point(0, 1, vector3<double>(0.5, 7.5, -6.8));
//    set_control_point(0, 2, vector3<double>(0, 6.8, -5.40));
//    set_control_point(0, 3, vector3<double>(1, 5.6, -4));
//    set_control_point(1, 0, vector3<double>(3, 8.6, -9));
//    set_control_point(1, 1, vector3<double>(3, 7.7, -7.40));
//    set_control_point(1, 2, vector3<double>(3, 6.95, -5.40));
//    set_control_point(1, 3, vector3<double>(3, 6.8, -4));
//    set_control_point(2, 0, vector3<double>(4.5, 9, -8));
//    set_control_point(2, 1, vector3<double>(4.5, 7.8, -6.4));
//    set_control_point(2, 2, vector3<double>(4.5, 7.3, -5.25));
//    set_control_point(2, 3, vector3<double>(4.5, 7.5, -4));
//    set_control_point(3, 0, vector3<double>(6, 9.2, -8));
//    set_control_point(3, 1, vector3<double>(5.5, 9, -6.66));
//    set_control_point(3, 2, vector3<double>(5.5, 8.6, -5.33));
//    set_control_point(3, 3, vector3<double>(6, 9, -4));
    
    //matlab的曲面
    set_control_point(0, 0, vector3<double>(6, 9, -8));
    set_control_point(0, 1, vector3<double>(5.5, 0, -6.8));
    set_control_point(0, 2, vector3<double>(5.5, 7.2, -5.40));
    set_control_point(0, 3, vector3<double>(6, 8.8, -4));
    set_control_point(1, 0, vector3<double>(4.5, 8.7, -9));
    set_control_point(1, 1, vector3<double>(4.5, 5.05, -7.40));
    set_control_point(1, 2, vector3<double>(4.5, 8.9, -5.40));
    set_control_point(1, 3, vector3<double>(4.5, 5.5, -4));
    set_control_point(2, 0, vector3<double>(3, 8.8, -8));
    set_control_point(2, 1, vector3<double>(3, 8.0, -6.4));
    set_control_point(2, 2, vector3<double>(3, 9.5, -5.25));
    set_control_point(2, 3, vector3<double>(3, 8.95, -4));
    set_control_point(3, 0, vector3<double>(1, 9, -8));
    set_control_point(3, 1, vector3<double>(1, 9.15, -6.66));
    set_control_point(3, 2, vector3<double>(1, 9.1, -5.33));
    set_control_point(3, 3, vector3<double>(1, 9, -4));
    
    double xs = 0, ys = 0, zs = 0;
    for(int i = 0; i < line; i++)
        for(int j = 0; j < row; j++)
        {
            xs += controlled_points[i][j].x;
            ys += controlled_points[i][j].y;
            zs += controlled_points[i][j].z;
        }
    BallPoint = vector3<double>(xs/16,ys/16,zs/16);
    
//    cout << xs/16 << " " << ys/16 << " " << zs/16 << endl;
//    cout << sqrt((xs/16-1)*(xs/16-1) + (ys/16-7)*(ys/16-7) + (zs/16+8)*(zs/16+8)) << endl;
//    cout << sqrt((xs/16-1)*(xs/16-1) + (ys/16-7)*(ys/16-7) + (zs/16+4)*(zs/16+4)) << endl;
//    cout << sqrt((xs/16-6)*(xs/16-6) + (ys/16-7)*(ys/16-7) + (zs/16+8)*(zs/16+8)) << endl;
//    cout << sqrt((xs/16-6)*(xs/16-6) + (ys/16-7)*(ys/16-7) + (zs/16+4)*(zs/16+4)) << endl;
    
    
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
    for (int i = 0; i < 60; i++)
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
        
        t -= delta_t*0.45;
        u -= delta_u*0.45;
        v += delta_v*0.45;
        
        if (u < 0 || u > 1 || v < 0 || v > 1)
            return false;
        
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
    int num_v = 1 / dv + 1;        //将要生成的u, v的数量
    //num_u = 1 / du + 1,
    int counter = 0;
    for (double u = 0.0f, i = 0; u <= (1.0f + limit_zero); u += du, i++)
    {
        for (double v = 0.0f, j = 0; v <= (1.0f + limit_zero); v += dv, j++)
        {
            vector3<double> vecuv = get_point(u, v);
            vector3<double> vecn(0,0,0);
            vecn = vecuv - BallPoint;
            vecn = vecn.normallize();
            
//            int tmmp = vecn.x * 10;
//            vecn.x = double(tmmp) / 10;
//            tmmp = vecn.y * 10;
//            vecn.y = double(tmmp) / 10;
//            tmmp = vecn.z * 10;
//            vecn.z = double(tmmp) / 10;
//            
//            uvmap[vecn] = vector2<double>(u, v);
//            //cout << "uv" << u << " " << v << endl;
            
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
    double t = 0.01, u = 0.5, v = 0.5;
    u = (double)(rand() % 999+0.1) / 1000;
    v = (double)(rand() % 999+0.1) / 1000;
    vector3<double> ballvecs(0,0,0);

    if(ball_intersect(input_ray, intersect_point))
    {
        u = (double)(rand() % 999+0.1) / 1000;
        v = (double)(rand() % 999+0.1) / 1000;
        u = 0.6; v = 0.6;
        if(NewtonIteration(input_ray, t, u, v))
        {
            intersect_point = get_point(u, v);
            //uvmap[intersect_point] = vector2<double>(u, v);
            
            last_u = u;
            last_v = v;
            
            //cout << "uv" << u << " " << v << endl;
            //cout << "Points:" << intersect_point.x << " " << intersect_point.y << " " << intersect_point.z << endl;
            return true;
        }
        
        u = (double)(rand() % 999+0.1) / 1000;//第二次
        v = (double)(rand() % 999+0.1) / 1000;
        if(NewtonIteration(input_ray, t, u, v))
        {
            intersect_point = get_point(u, v);
            
            last_u = u;
            last_v = v;

            return true;
        }
        
        u = (double)(rand() % 999+0.1) / 1000;//第三次
        v = (double)(rand() % 999+0.1) / 1000;
        if(NewtonIteration(input_ray, t, u, v))
        {
            intersect_point = get_point(u, v);
            
            last_u = u;
            last_v = v;

            return true;
        }
    }
    return false;
}

bool Beizer_Surface::ball_intersect(Ray input_ray, vector3<double> &intersect_point)
{
    intersect_point = input_ray.start_point;
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
    else if(abs(l.length - radius) < limit_zero)//可以根据光线的方向与到圆心的点积判断(锐角，则靠近，钝角，则远离)
    {
        if(direction_radius_dot > 0)          //光线与球心的距离变远
        {
            double square_distance = l.length * l.length - direction_radius_dot * direction_radius_dot;
            double square_t1 = square_radius - square_distance;
            double t1 = sqrt(square_t1);
            double t = direction_radius_dot + t1;
            intersect_point = input_ray.start_point + input_ray.direction * t;
            return true;
        }
        else
        {
            return false;
        }
    }
    else                                              
    {
        return true;
    }
    return true;
}

Color Beizer_Surface::get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in)   //in为法向量的引用
{
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
    
    double xx = (target_pos.x+10)/20, yy = (target_pos.y+10)/20;
    int xp = xx*55, yp = yy*55;
    
    vector3<double> qie_x, qie_y;
    qie_x = du.normallize();
    qie_y = dv.normallize();
    double r_gradiant, g_gradiant, b_gradiant;
    r_gradiant = ((double)image5.at<cv::Vec3b>(xp,yp)[2] / (double)255 - 0.5) * 2;
    g_gradiant = ((double)image5.at<cv::Vec3b>(xp,yp)[1] / (double)255 - 0.5) * 2;
    b_gradiant = ((double)image5.at<cv::Vec3b>(xp,yp)[0]-128) / (double)128;
    
    in = vector3<double>(qie_x.x*r_gradiant+qie_y.x*g_gradiant+in.x*b_gradiant, qie_x.y*r_gradiant+qie_y.y*g_gradiant+in.y*b_gradiant, qie_x.z*r_gradiant+qie_y.z*g_gradiant+in.z*b_gradiant);

    if (in * light.direction > 0)
    {
        in = in * -1;
    }
    in = in.normallize();
    
//    object_feature feature1;
//    feature1.absorb = 0.5;
//    feature1.diffuse_reflect = 0.5;
//    
//    int yy = last_u*200, zz = last_v*200;
//    
//    feature1.reflect_blue = (double)image2.at<cv::Vec3b>(yy,zz)[0] / (double)255;
//    feature1.reflect_green = (double)image2.at<cv::Vec3b>(yy,zz)[1] / (double)255;
//    feature1.reflect_red = (double)image2.at<cv::Vec3b>(yy,zz)[2] / (double)255;
//    
//    return PhongModel::reflect_color(light, in, view_direction, feature1);
    
    return PhongModel::reflect_color(light, in, view_direction, feature);
    
}

vector3<double> Beizer_Surface::get_normalvec(vector3<double> target_pos, vector3<double> view_direction)
{
    vector3<double> du = getdpdu(last_u,last_v);
    vector3<double> dv = getdpdv(last_u,last_v);
    
    return du.cross_product(dv);
}

