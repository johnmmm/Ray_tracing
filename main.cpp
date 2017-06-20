#include <iostream>
#include <cmath>
#include <time.h>
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Point.hpp"
#include "World.hpp"
using namespace std;

int main()
{
    clock_t start,finish;
    double totaltime;
    start=clock();
    
    World world;
    
    Object* leftwall = new Plane(vector3<double>(0, 0, -10), vector3<double>(0, 0, 1));
    leftwall->reflective = true;
    leftwall->reflect_coefficient = 0.2;
    leftwall->color_feature.Kab = 0.3, leftwall->color_feature.Kdb = 0.4; leftwall->color_feature.Ksb = 0.3;
    leftwall->color_feature.Kar = 0.3, leftwall->color_feature.Kdr = 0.4; leftwall->color_feature.Ksr = 0.3;
    world.add_object(leftwall);
    
    Object* rightwall = new Plane(vector3<double>(0, 0, 10), vector3<double>(0, 0, -1));//两边自带反光
    rightwall->reflective = true;
    rightwall->reflect_coefficient = 0.2;
    rightwall->color_feature.Kab = 0.3, rightwall->color_feature.Kdb = 0.4; rightwall->color_feature.Ksb = 0.3;
    rightwall->color_feature.Kar = 0.3, rightwall->color_feature.Kdr = 0.4; rightwall->color_feature.Ksr = 0.3;
    world.add_object(rightwall);
    
    Object* forwardwall = new Plane(vector3<double>(10, 0, 0), vector3<double>(-1, 0, 0));
    forwardwall->color_feature.Kar = 0.3;
    forwardwall->color_feature.Kdr = 0.4;
    forwardwall->color_feature.Ksr = 0.3;
    world.add_object(forwardwall);
    
//    Object* backwall = new Plane(vector3<double>(-10, 0, 0), vector3<double>(1, 0, 0));
//    world.add_object(backwall);
    Object* ceiling = new Plane(vector3<double>(0, -10, 0), vector3<double>(0, 1, 0));
    world.add_object(ceiling);
    Object* floor = new Plane(vector3<double>(0, 10, 0), vector3<double>(0, -1, 0));
    world.add_object(floor);
    
    Object* ball = new Sphere(vector3<double>(5, 6.5, -2), 1.5);
//    ball->opacity = 1.0;
//    ball->reflective = true;
//    ball->reflect_coefficient = 0.5;
//    ball->color_feature.Ksr = 0.5;
//    ball->color_feature.Ksg = 0.5;
//    ball->color_feature.Ksb = 0.5;
//    ball->refractive = true;
//    ball->refract_coefficient = 1.0;
    //ball->n = 1.62;
    world.add_object(ball);
    
    world.ray_trace();
    Drawer *p = Drawer::get_instance();
    p->output_image();
    
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"此程序的运行时间为"<<totaltime<<"秒！"<<endl;
    
    return 0;
}