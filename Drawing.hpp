//
//  Drawing.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/9.
//  Copyright © 2017年 mac. All rights reserved.
//

#ifndef Drawing_hpp
#define Drawing_hpp

#include <stdio.h>
#include "opencv/highgui.h"
#include "opencv/cv.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
//#include <cv.h>

using namespace std;

struct Color //rgb
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
    Color mix_back(Color background_color);
    Color(unsigned char x, unsigned char y, unsigned char z, unsigned char w=255)
    {
        r = x, g = y, b = z, a = w;
    }
    Color()
    {
        r = 0, g = 0, b = 0, a = 0;
    }
    Color operator*(const double &a)
    {
        Color temp;
        temp.r = (unsigned char)(min(a * (double)r, 255.0));
        temp.g = (unsigned char)(min(a * (double)g, 255.0));
        temp.b = (unsigned char)(min(a * (double)b, 255.0));
        temp.a = 255;
        return temp;
    }
    Color operator+(const Color &a)
    {
        Color temp;
        temp.r = (unsigned char)min((short)a.r + (short)r, 255);
        temp.g = (unsigned char)min((short)a.g + (short)g, 255);
        temp.b = (unsigned char)min((short)a.b + (short)b, 255);
        temp.a = 255;
        return temp;
    }
};

struct Point
{
    int x;
    int y;
};

class Drawer
{
public:
    Drawer(int h, int w);
    ~Drawer();
    static Drawer* get_instance()
    {
        if (instance == nullptr)
        {
            instance = new Drawer(800,600);
        }
        return instance;
    }
    void set_size(unsigned input_width, unsigned input_height);//设置图片大小
    void set_pixel(unsigned x, unsigned y, Color color);//
    void set_pixel(Point point, Color color);//画图
    Color get_pixel(unsigned x, unsigned y);//
    Color get_pixel(Point point);
    bool output_image();//保存图片
    bool point_illegal(int x, int y);
    const char* filename = "test.bmp";

    vector<unsigned char> image;
    unsigned width;
    unsigned height;
    cv::Mat images;
    static Drawer* instance;
};

#endif /* Drawing_hpp */
