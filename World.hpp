//
//  World.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/15.
//  Copyright © 2017年 mac. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <vector>
#include <stack>
#include <map>

//#include "Objects.hpp"
//#include "Plane.hpp"
//#include "Point.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Photon_map.hpp"
using namespace std;


class World
{
public:
    World();
    ~World(){}
    
    bool intersect_point(Ray input_ray, int &object_index, vector3<double> &point);//求取距离input_ray最近的交点
    bool intersect_other_objects(vector3<double> point); //判断当前光线是否先跟别的物体相交
    Color determine_color_normalvec(int object_index, vector3<double> point, vector3<double> in_direction, vector3<double> &normal_vector);     //获得颜色（已经添加了阴影）和法向量，传入的第三个参数为射入方向
    Color intersect_color(int n, Ray current_ray, stack<int> &refract_stack);//current_ray代表对其追踪的光线
    Color ray_trace(int i, int j);
    
    void add_object(Object* input_obj);//增加一个物品
    void ray_trace();                //光线追踪主函数
    void photon_cast();
    
    vector<Object*> objects;
    Drawer* Drawer_instance;
    double current_n;  //当前的折射率
    Light light;
    Camera camera;
    const int recursive_depth = 20; //递归深度
    const double photon_weight = 0.5;//当光源可以直接照射到一个点时，光子图的颜色与phong模型的颜色的比值
};



#endif /* World_hpp */
