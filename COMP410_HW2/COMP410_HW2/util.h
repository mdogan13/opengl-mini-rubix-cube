//
//  util.h
//  COMP410_HW2
//
//  Created by Murat Doğan on 26.03.2019.
//  Copyright © 2019 Murat Doğan. All rights reserved.
//

#ifndef util_h
#define util_h

#include "Angel.h"
#include "util.h"
#include <iostream>


using namespace std;
typedef vec4  color4;
typedef vec4  point4;



// RGBA olors
color4 vertex_colors[8] = {
    color4( 0.0, 0.0, 0.0, 1.0 ),  // black    0
    color4( 1.0, 0.0, 0.0, 1.0 ),  // red      1
    color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow    2
    color4( 0.0, 1.0, 0.0, 1.0 ),  // green     3
    color4( 0.0, 0.0, 1.0, 1.0 ),  // blue      4
    color4( 1.0, 0.5, 0.0, 0.0 ),  // orange   5
    color4( 1.0, 1.0, 1.0, 1.0 ),  // white     6
    color4( 0.0, 1.0, 1.0, 1.0 )   // cyan      7
};

vec3 cubeCoordinates[8]{
    vec3(-1.0,1.0,1.0), //cube 0
    vec3(1.0,1.0,1.0), //cube 1
    vec3(-1.0,-1.0,1.0), //cube 2
    vec3(1.0,-1.0,1.0) , //cube 3
    vec3(-1.0,1.0,-1.0), //cube 4
   vec3(1.0,1.0,-1.0), //cube 5
    vec3(-1.0,-1.0,-1.0), //cube 6
   vec3(1.0,-1.0,-1.0)  //cube 7
    
};


int cubeColors[8][6] = {
    //front right bottom top back left
    {3, 0, 0, 4, 0, 1} , //cube 0
    {3, 2, 0, 4, 0, 0} , //cube 1
    {3, 0, 6, 0, 0, 1} , //cube 2
    {3, 2, 6, 0, 0, 0} , //cube 3
    {0, 0, 0, 4, 5, 1} , //cube 4
    {0, 2, 0, 4, 5, 0} , //cube 5
    {0, 0, 6, 0, 5, 1} , //cube 6
    {0, 2, 6, 0, 5, 0} , //cube 7
    
};

#endif /* util_h */
