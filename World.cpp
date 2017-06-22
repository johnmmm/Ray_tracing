//
//  World.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/16.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "World.hpp"


World::World() : light()
{
    //light = Light(vector3<double>(0, 0, 0), vector3<double>(0.5, 0, 0), vector3<double>(0, 0.5, 0), vector3<double>(0, 0, -1), 5, 5, 0.9);
    //尝试面光源失败。。。
    
    camera = Camera(vector3<double>(-5, 0, 0), vector3<double>(1, 0, 0), vector3<double>(0, 0, 1));
    Drawer_instance = Drawer::get_instance();
    Drawer_instance->set_size(camera.size_x, camera.size_y);
}

bool World::intersect_point(Ray current_ray, int &object_index, vector3<double> &point)       //求交点！
{
    double distance = 10000000000;
    object_index = -1;
    
    ///枚举world中每一个物体求交点，选取一个最近的交点
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        vector3<double> intersect_Point;
        if (objects[i]->intersect(current_ray, intersect_Point))
        {
            double length = (intersect_Point - camera.position).length;
            if (length < distance)
            {
                distance = length;
                object_index = i;
                point = intersect_Point;
            }
        }
    }
    
    if (object_index < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool World::intersect_other_objects(vector3<double> point)
{
    for (int k = 0; k < light.each_light.size(); k++)
    {
        vector3<double> intersect_to_light(light.each_light[k].start_point - point);
        double distance = intersect_to_light.length;
        intersect_to_light = intersect_to_light.normallize();
        Ray to_light_ray(point, intersect_to_light);           //交点到光源的射线
        for (unsigned int i = 0; i < objects.size(); i++)
        {
            vector3<double> intersect_point;
            if (objects[i]->intersect(to_light_ray, intersect_point))
            {
                vector3<double> to_object = light.each_light[k].start_point - intersect_point;       //to object表示与intersect_to_light同向的由灯到物体的向量
                if (to_object.length < distance && intersect_to_light * to_object > limit_zero)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

Color World::determine_color_normalvec(int object_index, vector3<double> point, vector3<double> in_direction, vector3<double> &normal_vector)     //对于每一个灯，都求出一个颜色
{
    Color return_color(0, 0, 0, 255);//将这些相加并得出最终的结果
    
    for (int k = 0; k < light.each_light.size(); k++)
    {
        Color temp_color = objects[object_index]->get_color_normalvec(point, in_direction, light.each_light[k], normal_vector);
        //在当前点光源下得到的颜色
        
        //cout << (int)temp_color.r << " " << (int)temp_color.g << " " << (int)temp_color.g << endl;
        
        vector3<double> intersect_to_light(light.each_light[k].start_point - point);
        double distance = intersect_to_light.length;
        intersect_to_light = intersect_to_light.normallize();
        Ray to_light_ray(point, intersect_to_light);            //交点到光源的射线
        
        for (unsigned int i = 0; i < objects.size(); i++)//继续与物体求交
        {
            if (i == object_index)
                continue;
            vector3<double> intersect_point;
            if (objects[i]->intersect(to_light_ray, intersect_point))
            {
                vector3<double> to_object = light.each_light[k].start_point - intersect_point;
                //to object表示与intersect_to_light同向的由灯到物体的向量
                
                if (to_object.length < distance && intersect_to_light * to_object > limit_zero)
                {
                    temp_color.r *= objects[i]->opacity;
                    temp_color.g *= objects[i]->opacity;
                    temp_color.b *= objects[i]->opacity;
                }
                else
                {
                    continue;
                }
            }
        }
        
        //cout << (int)temp_color.r << " " << (int)temp_color.g << " " << (int)temp_color.g << endl;
        return_color = return_color + temp_color;
    }
    
    return return_color;
}

Color World::intersect_color(int n, Ray current_ray, stack<int> &refract_stack)           //在refract_stack中，-1表示没有在任何物体内，折射率为1
{
    if (n >= recursive_depth)
    {
        return Color();
    }
    vector3<double> _intersect_point;
    int object_index;
    if (intersect_point(current_ray, object_index, _intersect_point))
    {
        Color return_color;
        vector3<double> normal_vector;
        normal_vector = objects[object_index]->get_normalvec(_intersect_point, current_ray.direction);
        if (objects[object_index]->feature.specular_reflect > limit_zero)
        {
            vector3<double> reflect_direction = reflect(current_ray.direction, normal_vector);
            Ray reflect_ray(_intersect_point, reflect_direction);
            return_color = return_color + intersect_color(n + 1, reflect_ray, refract_stack) * objects[object_index]->feature.specular_reflect;
        }
        if (objects[object_index]->feature.refract > limit_zero)
        {
            double last_n = current_n;            //入射光线折射率
            //return_color = determine_color_normalvec(object_index, _intersect_point, current_ray.direction, normal_vector) *
            //	(1 - objects[object_index]->refract_coefficient);
            if (object_index == refract_stack.top())            //将要射出该物体
            {
                int top = refract_stack.top();
                refract_stack.pop();
                if (refract_stack.top() >= 0)
                {
                    current_n = objects[refract_stack.top()]->n;              //出射光线折射率
                }
                else
                {
                    current_n = 1;                    //在真空中折射率为1
                }
                vector3<double> refract_direction;
                if (refract(current_ray.direction, normal_vector, last_n, current_n, refract_direction))                    //能够折射
                {
                    Ray refract_ray(_intersect_point, refract_direction);
                    return_color = return_color + intersect_color(n + 1, refract_ray, refract_stack) * objects[object_index]->feature.refract;
                }
                else                                       //发生全反射
                {
                    refract_stack.push(top);
                    current_n = last_n;
                    vector3<double> reflect_direction = reflect(current_ray.direction, normal_vector);
                    Ray reflect_ray(_intersect_point, reflect_direction);
                    return_color = return_color + intersect_color(n + 1, reflect_ray, refract_stack) * objects[object_index]->feature.specular_reflect;
                }
            }
            else                                              //将要射入该物体
            {
                refract_stack.push(object_index);
                current_n = objects[object_index]->n;         //出射光线折射率
                vector3<double> refract_direction;
                if (refract(current_ray.direction, normal_vector, last_n, current_n, refract_direction))                    //能够折射
                {
                    Ray refract_ray(_intersect_point, refract_direction);
                    return_color = return_color + intersect_color(n + 1, refract_ray, refract_stack) * objects[object_index]->feature.refract;
                }
                else                                       //发生全反射
                {
                    refract_stack.pop();
                    current_n = last_n;
                    vector3<double> reflect_direction = reflect(current_ray.direction, normal_vector);
                    Ray reflect_ray(_intersect_point, reflect_direction);
                    return_color = return_color + intersect_color(n + 1, reflect_ray, refract_stack) * objects[object_index]->feature.specular_reflect;
                }
            }
        }
        if(objects[object_index]->feature.diffuse_reflect > limit_zero)
        {                //phong模型的颜色加上光子图的颜色以降低高频噪声
            if (intersect_other_objects(_intersect_point))
            {
                return_color = ((Photon_map::get_instance())->get_color(_intersect_point, normal_vector, current_ray.direction,
                                                                        objects[object_index]->feature.diffuse_reflect, objects[object_index]->feature.specular_reflect)) + return_color;
            }
            else
            {
                Color phong_color(0, 0, 0, 255);            //得到Phong模型返回的颜色
                for (int k = 0; k < light.each_light.size(); k++)
                {
                    vector3<double> useless;        //这一变量无用，为了填充参数
                    phong_color = objects[object_index]->get_color_normalvec(_intersect_point, current_ray.direction, light.each_light[k], useless) + phong_color;
                }
                return_color = ((Photon_map::get_instance())->get_color(_intersect_point, normal_vector, current_ray.direction,
                                                                        objects[object_index]->feature.diffuse_reflect, objects[object_index]->feature.specular_reflect)) * photon_weight +
                phong_color * (1 - photon_weight) + return_color;
            }
        }
        return return_color;
    }
    else
    {
        //cout << "no intersect" << endl;
        return Color();
    }
}

Color World::ray_trace(int i, int j)
{
    Ray current_ray = camera.generate_ray(i, j);             //产生i, j像素上的光线
    //cout << "generate " << current_ray.start_point << " " << current_ray.direction << endl;
    
    stack<int> refract_stack;
    refract_stack.push(-1);
    current_n = 1;
    //cout << i << " " << j << endl;
    //Color a = intersect_color(0, current_ray, refract_stack);
    //cout << (int)a.r << " " << (int)a.g << " " << (int)a.b << endl;
    
    return intersect_color(0, current_ray, refract_stack);
}

void World::add_object(Object* obj)
{
    objects.push_back(obj);
}

void World::ray_trace()
{
    cout << camera.size_x << " " << camera.size_y << endl;
    for (int i = 0; i < camera.size_x; i++)
        for (int j = 0; j < camera.size_y; j++)
        {
            Drawer_instance->set_pixel(i, j, ray_trace(i - (camera.size_x / 2), j - (camera.size_y / 2)));
        }
}

void World::photon_cast()
{
    (Photon_map::get_instance())->init_photon_map(objects, light.each_light[0].start_point, Color(255, 255, 255, 255));
    (Photon_map::get_instance())->generate_photon(3000000);
}

