//
//  PhongModel.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/15.
//  Copyright © 2017年 mac. All rights reserved.
//

#ifndef PhongModel_hpp
#define PhongModel_hpp

#include <stdio.h>
#include "Drawing.hpp"
#include "Point.hpp"
#include "Ray.hpp"


class PhongModel
{
public:
    PhongModel();
    ~PhongModel();
    
    static int reflect_parameter;
    static Color reflect_color(Single_Light light, vector3<double> normal_vector, vector3<double> view_direction, Material_feature feature);
};



#endif /* PhongModel_hpp */
