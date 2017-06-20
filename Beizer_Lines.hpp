//
//  Beizer_Lines.hpp
//  myfirstopencvpro
//
//  Created by mac on 17/6/20.
//  Copyright © 2017年 mac. All rights reserved.
//

#ifndef Beizer_Lines_hpp
#define Beizer_Lines_hpp

#include <stdio.h>
#include <vector>
#include <assert.h>
#include "Point.hpp"
using namespace std;


class Beizer_Lines
{
public:
    Beizer_Lines();
    ~Beizer_Lines();
    
    vector3<double> get_point(double t);                    //用de Casteljau算法算点
    void add_control_point(vector3 <double> input_point);     //增加控制点
    
private:
    vector<vector3<double> > controlled_point;               //beizer的控制点
};



#endif /* Beizer_Lines_hpp */
