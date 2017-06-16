//
//  Objects.cpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/15.
//  Copyright © 2017年 mac. All rights reserved.
//

#include "Objects.hpp"



Object::Object()//初始就认为没有了
{
    reflective = false;
    refractive = false;
    reflect_coefficient = 0;
    refract_coefficient = 0;
}


Object::~Object()
{
}