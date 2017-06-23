//
//  Drawing.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/9.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "Drawing.hpp"
#include <assert.h>
#include <algorithm>
using namespace std;

Drawer* Drawer::instance = new Drawer(960,1280);  //对静态成员实例化

Drawer::Drawer(int w, int h)
{
    cv::Mat imaging(w,h,CV_8UC3);//做一张图？
    imaging.copyTo(images);
}

Drawer::~Drawer()
{
    
}

void Drawer::set_size(unsigned input_width, unsigned input_height)
{
    height = input_height;
    width = input_width;
    cv::Mat tmp(width,height,CV_8UC3);
    tmp.copyTo(images);
}

void Drawer::set_pixel(unsigned x, unsigned y, Color color)//???改成那个的
{
    assert(x < width && y < height);
    
    images.at<cv::Vec3b>(x,y)[2] = std::min(color.r, (unsigned char)255);
    images.at<cv::Vec3b>(x,y)[1] = std::min(color.g, (unsigned char)255);
    images.at<cv::Vec3b>(x,y)[0] = std::min(color.b, (unsigned char)255);
}

void Drawer::set_pixel(Point point, Color color)
{
    set_pixel(point.x, point.y, color);
}

Color Drawer::get_pixel(unsigned x, unsigned y)
{
    assert(x < width && y < height);

    Color target_color;
    target_color.r = images.at<cv::Vec3b>(x,y)[2];
    target_color.g = images.at<cv::Vec3b>(x,y)[1];
    target_color.b = images.at<cv::Vec3b>(x,y)[0];

    return target_color;
}

Color Drawer::get_pixel(Point point)
{
    return get_pixel(point.x, point.y);
}

bool Drawer::output_image()
{
    cv::imwrite("/Users/mac/Desktop/programme/program/4st_term/Ray_Tracing/test_1.bmp", images);
    
    
    cv::Mat small_images(images.rows/2,images.cols/2,CV_8UC3);//缩小，抗锯齿
    for(int i = 0; i < small_images.rows; i++)
        for(int j = 0; j < small_images.cols; j++)
        {
            small_images.at<cv::Vec3b>(i,j)[0] = (images.at<cv::Vec3b>(i*2,j*2)[0]+images.at<cv::Vec3b>(i*2+1,j*2)[0]+images.at<cv::Vec3b>(i*2,j*2+1)[0]+images.at<cv::Vec3b>(i*2+1,j*2+1)[0])/4;
            small_images.at<cv::Vec3b>(i,j)[1] = (images.at<cv::Vec3b>(i*2,j*2)[1]+images.at<cv::Vec3b>(i*2+1,j*2)[1]+images.at<cv::Vec3b>(i*2,j*2+1)[1]+images.at<cv::Vec3b>(i*2+1,j*2+1)[1])/4;
            small_images.at<cv::Vec3b>(i,j)[2] = (images.at<cv::Vec3b>(i*2,j*2)[2]+images.at<cv::Vec3b>(i*2+1,j*2)[2]+images.at<cv::Vec3b>(i*2,j*2+1)[2]+images.at<cv::Vec3b>(i*2+1,j*2+1)[2])/4;
        }
    cv::imwrite("/Users/mac/Desktop/programme/program/4st_term/Ray_Tracing/small_one.bmp", small_images);
    
    return true;
}

bool Drawer::point_illegal(int x, int y)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
    {
        return true;
    }
    else
    {
        return false;                
    }
    return true;
}

Color Color::mix_back(Color background_color)
{
    Color mixed_color;
    double ratio = (double)a / 255;
    mixed_color.r = (unsigned char)(ratio * (double)r + (1 - ratio) * (double)background_color.r);            //根据灰度来算合成的r
    mixed_color.g = (unsigned char)(ratio * (double)g + (1 - ratio) * (double)background_color.g);            //根据灰度来算合成的g
    mixed_color.b = (unsigned char)(ratio * (double)b + (1 - ratio) * (double)background_color.b);            //根据灰度来算合成的b
    mixed_color.a = 255;
    return mixed_color;
}





