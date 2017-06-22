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
#include "PhotonModel.hpp"


class PhongModel
{
public:
    PhongModel();
    ~PhongModel();
    
    static int reflect_parameter;
    static double amplify_parameter;
    static Color reflect_color(Single_Light light, vector3<double> normal_vector, vector3<double> view_direction, object_feature feature);
    static double PhongBRDF(vector3<double> normal_vector, vector3<double> in_direction, vector3<double> view_direction, double pd, double ps);          //反射光和镜面反射光的反射率
};



#endif /* PhongModel_hpp */
