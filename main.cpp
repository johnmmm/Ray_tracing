#include <iostream>
#include <cmath>
#include <time.h>
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Point.hpp"
#include "World.hpp"
#include "Beizer_Surface.hpp"
using namespace std;

int main()
{
    clock_t start,finish;
    double totaltime;
    start=clock();
    
    World world;
    Object* floor = new Plane(vector3<double>(0, 10, 0), vector3<double>(0, -1, 0));
    floor->feature.absorb = 0.5; floor->feature.diffuse_reflect = 0.5;
    floor->feature.reflect_red = 0.8; floor->feature.reflect_green = 0.8; floor->feature.reflect_blue = 0.8;
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
    
//    Object* backwall = new Plane(vector3<double>(-10, 0, 0), vector3<double>(1, 0, 0));
//    backwall->feature.absorb = 0.5; backwall->feature.diffuse_reflect = 0.5;
//    backwall->feature.reflect_blue = 0.5;
//    world.add_object(backwall);
    
    Object* leftwall = new Plane(vector3<double>(0, 0, -10), vector3<double>(0, 0, 1));
    leftwall->feature.absorb = 0.4; leftwall->feature.diffuse_reflect = 0.4; leftwall->feature.specular_reflect = 0.2;
    leftwall->feature.reflect_green = 0.5;
//    leftwall->reflective = true;
//    leftwall->reflect_coefficient = 0.2;
//    leftwall->color_feature.Kab = 0.3, leftwall->color_feature.Kdb = 0.4; leftwall->color_feature.Ksb = 0.3;
//    leftwall->color_feature.Kar = 0.3, leftwall->color_feature.Kdr = 0.4; leftwall->color_feature.Ksr = 0.3;
    world.add_object(leftwall);
    
    Object* rightwall = new Plane(vector3<double>(0, 0, 10), vector3<double>(0, 0, -1));
    rightwall->feature.absorb = 0.5; rightwall->feature.diffuse_reflect = 0.5; rightwall->feature.specular_reflect = 0.0;
    rightwall->feature.reflect_red = 0.678; rightwall->feature.reflect_green = 0.361; rightwall->feature.reflect_blue = 0.047;
//    rightwall->reflective = true;
//    rightwall->reflect_coefficient = 0.2;
//    rightwall->color_feature.Kab = 0.3, rightwall->color_feature.Kdb = 0.4; rightwall->color_feature.Ksb = 0.3;
//    rightwall->color_feature.Kar = 0.3, rightwall->color_feature.Kdr = 0.4; rightwall->color_feature.Ksr = 0.3;
    world.add_object(rightwall);
    
    Object* ball1 = new Sphere(vector3<double>(5, 7, 0), 1.5);
    ball1->feature.absorb = 0.05; ball1->feature.diffuse_reflect = 0; ball1->feature.specular_reflect = 0; ball1->feature.refract = 0.95;
    world.add_object(ball1);
//
    Object* ball2 = new Sphere(vector3<double>(5,8,5),2.0);
    ball2->feature.absorb = 0.05; ball2->feature.diffuse_reflect = 0; ball2->feature.specular_reflect = 0.95; ball2->feature.refract = 0;
    ball2->feature.reflect_blue = 1; ball2->feature.reflect_green = 1; ball2->feature.reflect_red = 1;
    world.add_object(ball2);
    
    Object* mian = new Beizer_Surface();
    mian->feature.absorb = 0.5; mian->feature.diffuse_reflect = 0.5; mian->feature.specular_reflect = 0.0;
    world.add_object(mian);

    //    Object* ball2 = new Sphere(vector3<double>(3.5625,7.79063,-6.1025),3.8);//验证包围球用
    //    ball2->feature.absorb = 0.05; ball2->feature.diffuse_reflect = 0; ball2->feature.specular_reflect = 0; ball2->feature.refract = 0.95;
    //    //ball2->feature.reflect_blue = 1; ball2->feature.reflect_green = 1; ball2->feature.reflect_red = 1;
    //    world.add_object(ball2);
    
    world.photon_cast();
    world.ray_trace();
    Drawer *p = Drawer::get_instance();
    p->output_image();
    
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"此程序的运行时间为"<<totaltime<<"秒！"<<endl;
    
    return 0;
}