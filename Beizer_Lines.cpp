//
//  Beizer_Lines.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/20.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "Beizer_Lines.hpp"
#include <algorithm>
using namespace std;


Beizer_Lines::Beizer_Lines()
{
    
}

Beizer_Lines::~Beizer_Lines()
{
    
}

vector3<double> Beizer_Lines::get_point(double t)
{
    vector3<double>* temp_vec1 = new vector3<double>[controlled_point.size()];
    vector3<double>* temp_vec2 = new vector3<double>[controlled_point.size()];
    copy(controlled_point.begin(), controlled_point.end(), temp_vec1);
    for (int i = 0; i < controlled_point.size() - 1; i++)//递推公式
    {
        if ((i & 1) == 0)
        {
            for (int j = 0; j < controlled_point.size() - i - 1; j++)
            {
                temp_vec2[j] = temp_vec1[j] * (1 - t) + temp_vec1[j + 1] * t;
            }
        }
        else
        {
            for (int j = 0; j < controlled_point.size() - i - 1; j++)
            {
                temp_vec1[j] = temp_vec2[j] * (1 - t) + temp_vec2[j + 1] * t;
            }
        }
    }
    
    if ((controlled_point.size() & 1) == 0)
    {
        vector3<double> return_vector = temp_vec2[0];
        delete[] temp_vec1;
        delete[] temp_vec2;
        return return_vector;
    }
    else
    {
        vector3<double> return_vector = temp_vec1[0];
        delete[] temp_vec1;
        delete[] temp_vec2;
        return return_vector;
    }
}

void Beizer_Lines::add_control_point(vector3<double> input_point)
{
    controlled_point.push_back(input_point);
}