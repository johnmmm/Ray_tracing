#include <iostream>
#include <cmath>
#include <time.h>
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Point.hpp"
#include "World.hpp"
#include "Beizer_rotates.hpp"
#include "Beizer_Surface.hpp"
using namespace std;

int main()
{
    clock_t start,finish;
    double totaltime;
    start=clock();
    
//    World world;
//    
//    Object* leftwall = new Plane(vector3<double>(0, 0, -10), vector3<double>(0, 0, 1));
//    leftwall->reflective = true;
//    leftwall->reflect_coefficient = 0.2;
//    leftwall->color_feature.Kab = 0.3, leftwall->color_feature.Kdb = 0.4; leftwall->color_feature.Ksb = 0.3;
//    leftwall->color_feature.Kar = 0.3, leftwall->color_feature.Kdr = 0.4; leftwall->color_feature.Ksr = 0.3;
//    world.add_object(leftwall);
//    
//    Object* rightwall = new Plane(vector3<double>(0, 0, 10), vector3<double>(0, 0, -1));//两边自带反光
//    rightwall->reflective = true;
//    rightwall->reflect_coefficient = 0.2;
//    rightwall->color_feature.Kab = 0.3, rightwall->color_feature.Kdb = 0.4; rightwall->color_feature.Ksb = 0.3;
//    rightwall->color_feature.Kar = 0.3, rightwall->color_feature.Kdr = 0.4; rightwall->color_feature.Ksr = 0.3;
//    world.add_object(rightwall);
//    
//    Object* forwardwall = new Plane(vector3<double>(10, 0, 0), vector3<double>(-1, 0, 0));
//    forwardwall->color_feature.Kar = 0.3;
//    forwardwall->color_feature.Kdr = 0.4;
//    forwardwall->color_feature.Ksr = 0.3;
//    world.add_object(forwardwall);
//    
////    Object* backwall = new Plane(vector3<double>(-10, 0, 0), vector3<double>(1, 0, 0));
////    world.add_object(backwall);
//    Object* ceiling = new Plane(vector3<double>(0, -10, 0), vector3<double>(0, 1, 0));
//    world.add_object(ceiling);
//    Object* floor = new Plane(vector3<double>(0, 10, 0), vector3<double>(0, -1, 0));
//    world.add_object(floor);
//    
//    //Object* ball = new Sphere(vector3<double>(8/9, 10/9, 13.35/9), 2.5);
//    Object* ball = new Sphere(vector3<double>(5, 6.5, -2), 1.5);
////    ball->opacity = 1.0;
////    ball->reflective = true;
////    ball->reflect_coefficient = 0.5;
////    ball->color_feature.Ksr = 0.5;
////    ball->color_feature.Ksg = 0.5;
////    ball->color_feature.Ksb = 0.5;
////    ball->refractive = true;
////    ball->refract_coefficient = 1.0;
//    //ball->n = 1.62;
//    world.add_object(ball);
//    
//    //Beizer_Surface a;
////    a.set_control_point(0, 0, vector3<double>(0, 0, 0));
////    a.set_control_point(0, 1, vector3<double>(0, 1.5, 1));
////    a.set_control_point(0, 2, vector3<double>(0, 2, 0.5));
////    a.set_control_point(1, 0, vector3<double>(1, 0, 0.3));
////    a.set_control_point(1, 1, vector3<double>(1, 1, 10));
////    a.set_control_point(1, 2, vector3<double>(1, 2, 0.9));
////    a.set_control_point(2, 0, vector3<double>(2, 0, -0.2));
////    a.set_control_point(2, 1, vector3<double>(2, 1.3, 0.05));
////    a.set_control_point(2, 2, vector3<double>(1, 2.2, 0.8));
////    a.output_obj();
//    
//    Object* mian = new Beizer_Surface();
//    world.add_object(mian);
//    
////    Object* xian = new Beizer_rotates();
////    world.add_object(xian);
    
    World world;
    Object* floor = new Plane(vector3<double>(0, 10, 0), vector3<double>(0, -1, 0));
    floor->feature.absorb = 0.5; floor->feature.diffuse_reflect = 0.5;
    //floor->feature.reflect_green = 0.5;
    world.add_object(floor);
    
    Object* ceiling = new Plane(vector3<double>(0, -10, 0), vector3<double>(0, 1, 0));
    ceiling->feature.absorb = 0.5; ceiling->feature.diffuse_reflect = 0.5;
    //ceiling->feature.reflect_red = 0.5;
    world.add_object(ceiling);
    
    Object* forwardwall = new Plane(vector3<double>(10, 0, 0), vector3<double>(-1, 0, 0));
    forwardwall->feature.absorb = 0.5; forwardwall->feature.diffuse_reflect = 0.5;
    forwardwall->feature.reflect_blue = 0.5;
//    forwardwall->color_feature.Kar = 0.3;
//    forwardwall->color_feature.Kdr = 0.4;
//    forwardwall->color_feature.Ksr = 0.3;
    world.add_object(forwardwall);
    
    Object* backwall = new Plane(vector3<double>(-10, 0, 0), vector3<double>(1, 0, 0));
    backwall->feature.absorb = 0.5; backwall->feature.diffuse_reflect = 0.5;
    backwall->feature.reflect_blue = 0.5;
    world.add_object(backwall);
    
    Object* leftwall = new Plane(vector3<double>(0, 0, -10), vector3<double>(0, 0, 1));
    leftwall->feature.absorb = 0.4; leftwall->feature.diffuse_reflect = 0.4; leftwall->feature.specular_reflect = 0.2;
    leftwall->feature.reflect_green = 0.5;
//    leftwall->reflective = true;
//    leftwall->reflect_coefficient = 0.2;
//    leftwall->color_feature.Kab = 0.3, leftwall->color_feature.Kdb = 0.4; leftwall->color_feature.Ksb = 0.3;
//    leftwall->color_feature.Kar = 0.3, leftwall->color_feature.Kdr = 0.4; leftwall->color_feature.Ksr = 0.3;
    world.add_object(leftwall);
    
    Object* rightwall = new Plane(vector3<double>(0, 0, 10), vector3<double>(0, 0, -1));
    rightwall->feature.absorb = 0.4; rightwall->feature.diffuse_reflect = 0.4; rightwall->feature.specular_reflect = 0.2;
    rightwall->feature.reflect_red = 0.5;
//    rightwall->reflective = true;
//    rightwall->reflect_coefficient = 0.2;
//    rightwall->color_feature.Kab = 0.3, rightwall->color_feature.Kdb = 0.4; rightwall->color_feature.Ksb = 0.3;
//    rightwall->color_feature.Kar = 0.3, rightwall->color_feature.Kdr = 0.4; rightwall->color_feature.Ksr = 0.3;
    world.add_object(rightwall);
    
    Object* ball = new Sphere(vector3<double>(5, 6.5, -2), 1.5);
    ball->feature.absorb = 0.05; ball->feature.diffuse_reflect = 0; ball->feature.specular_reflect = 0; ball->feature.refract = 0.95;
    world.add_object(ball);
    
    Object* mian = new Beizer_Surface();
    mian->feature.absorb = 0.2; mian->feature.diffuse_reflect = 0.3; mian->feature.specular_reflect = 0.5;
    mian->feature.reflect_red = 0.7; mian->feature.reflect_green = 0.4; mian->feature.reflect_blue = 0.7;
//    mian->reflective = true;
//    mian->reflect_coefficient = 0.3;
    world.add_object(mian);

    world.photon_cast();
    world.ray_trace();
    Drawer *p = Drawer::get_instance();
    p->output_image();
    
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"此程序的运行时间为"<<totaltime<<"秒！"<<endl;
    
    return 0;
}