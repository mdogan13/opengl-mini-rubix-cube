//
//  cube.h
//  COMP410_HW2
//
//  Created by Murat Doğan on 26.03.2019.
//  Copyright © 2019 Murat Doğan. All rights reserved.
//

#ifndef cube_h
#define cube_h


#include "Angel.h"
#include "util.h"
#include <iostream>


using namespace std;
typedef vec4  color4;
typedef vec4  point4;

class cube {
public:
    mat4 cube_model_view;
    const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)
    int Index = 0;
    point4 points[36];
    color4 colors[36];
   // Vertices of a unit cube centered at origin, sides aligned with axes
    point4 vertices[8] = {
        point4( -0.5, -0.5,  0.5, 1.0 ),
        point4( -0.5,  0.5,  0.5, 1.0 ),
        point4(  0.5,  0.5,  0.5, 1.0 ),
        point4(  0.5, -0.5,  0.5, 1.0 ),
        point4( -0.5, -0.5, -0.5, 1.0 ),
        point4( -0.5,  0.5, -0.5, 1.0 ),
        point4(  0.5,  0.5, -0.5, 1.0 ),
        point4(  0.5, -0.5, -0.5, 1.0 )
    };
    
    //euler angles
    float alpha=0;
    float beta=0;
    float angle=0;
    
    GLfloat rotateXangle=25;
    GLfloat rotateYangle=-45;
    GLfloat rotateZangle=0;
    int colorIndex;

    
    //constructor
    cube(int colorIndex){
        this->colorIndex=colorIndex;
        colorcube(colorIndex);
        cubeCoordinates[colorIndex]=cubeCoordinates[colorIndex]*0.55;
        cube_model_view = ( Scale(0.2, 0.2, 0.2)  * RotateX( rotateXangle ) * RotateY( rotateYangle ) * RotateZ( rotateZangle ) *rotationMatrix(calc3Dvec(alpha, beta), angle)* Translate( cubeCoordinates[colorIndex] ) );
       
    }
   
    //setters
    
    void setAlpha(GLfloat alpha){
        this->alpha=alpha;
        updateModelView();
    }
    void setBeta(GLfloat beta){
        this->beta=beta;
        updateModelView();
    }
  
    void incrementAngle(GLfloat angle){
        this->angle+=angle;
        this->updateModelView();
    }
    void incrementrotateXangle(GLfloat angle){
        this->rotateXangle+=angle;
        updateModelView();
    }
    void incrementrotateYangle(GLfloat angle){
        this->rotateYangle+=angle;
        updateModelView();
    }
    void incrementrotateZangle(GLfloat angle){
        this->rotateZangle+=angle;
        updateModelView();
    }
   
    
    void updateModelView(){
         this->cube_model_view = ( Scale(0.2, 0.2, 0.2)  * RotateX( rotateXangle) * RotateY( rotateYangle ) * RotateZ( rotateZangle ) *rotationMatrix(calc3Dvec(alpha, beta), angle)* Translate( cubeCoordinates[this->colorIndex] ) );
    }
    // quad generates two triangles for each face and assigns colors to the vertices
    
    void quad( int a, int b, int c, int d ,int colorSelection)
    {
        colors[Index] = vertex_colors[colorSelection]; points[Index] = vertices[a]; Index++;
        colors[Index] = vertex_colors[colorSelection]; points[Index] = vertices[b]; Index++;
        colors[Index] = vertex_colors[colorSelection]; points[Index] = vertices[c]; Index++;
        colors[Index] = vertex_colors[colorSelection]; points[Index] = vertices[a]; Index++;
        colors[Index] = vertex_colors[colorSelection]; points[Index] = vertices[c]; Index++;
        colors[Index] = vertex_colors[colorSelection]; points[Index] = vertices[d]; Index++;
    }
    
    // generate 12 triangles: 36 vertices and 36 colors
    void colorcube(int cubeIndex){
        
        quad( 1, 0, 3, 2 ,cubeColors[cubeIndex][0]); // red 1     front
        quad( 2, 3, 7, 6 ,cubeColors[cubeIndex][1]); // yellow 2  right
        quad( 3, 0, 4, 7 ,cubeColors[cubeIndex][2]); // green 3   bottom
        quad( 6, 5, 1, 2 ,cubeColors[cubeIndex][3]); // blue 4    top
        quad( 4, 5, 6, 7 ,cubeColors[cubeIndex][4]); // magenta 5 back
        quad( 5, 4, 0, 1 ,cubeColors[cubeIndex][5]); // white 6   left
       
    }
    
    //calculates the rotation axis(a vector) for euler angles alpha and beta
    vec3 calc3Dvec(GLfloat alpha,GLfloat beta){
        //alpha: angle between x and z axis
        //beta: angle between y and z axis
        GLfloat angleA = DegreesToRadians * alpha;
        GLfloat angleB = DegreesToRadians * beta;
        return vec3(cos(angleB)*sin(angleA),cos(angleB)*cos(angleA),sin(angleB));
    }
    
    //calculates rotation matrix for rotation around arbitrary axis by "angle" degrees
    mat4 rotationMatrix(vec3 axis, float angle){
        GLfloat ang =DegreesToRadians*angle;
        axis = normalize(axis);
        float s = sin(ang);
        float c = cos(ang);
        float oc = 1.0 - c;
        
        return mat4(oc * axis.x * axis.x + c,oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                    oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,  oc * axis.y * axis.z - axis.x * s,  0.0,
                    oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,   0.0,
                    0.0,     0.0,      0.0,     1.0);
    }
    
};

#endif /* cube_h */
