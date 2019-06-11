// COMP 410 Assignment 2
//
// Murat Doğan
// 27624

#include "Angel.h"
#include <iostream>
#include "cube.h"
#include "util.h"
#include <vector>
using std::vector;
using namespace std;
typedef vec4  color4;
typedef vec4  point4;

vector<cube> cubes;
GLuint abuffer[8];


mat2 faces[6] = {
    mat2(0, 1, 2, 3), // Front
    mat2(5, 4, 7, 6), // Back
    mat2(1, 5, 3, 7), // Right
    mat2(4, 0, 6, 2), // Left
    mat2(4, 5, 0, 1), // Top
    mat2(2, 3, 6, 7)  // Bottom
};

int modifyIndexes[4];
int faceToRotate;
float angle = 0;
int rotDirection = 1;
bool animate = false;


//enum for rotations 1:ccw  2:cw
int rotationType;
enum { top1 = 0, top2 = 1, bottom1 = 2, bottom2 = 3, left1 = 4, left2 = 5,
    right1 = 6, right2 = 7, front1 = 8, front2 = 9, back1 = 10, back2 = 11 };

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection;




void updateIndexes(int rotType){
    
    //picks the cubes that'll rotate
    for(int j=0; j<4; j++){
        modifyIndexes[j]=faces[faceToRotate][0][j];
    }
    
    //modify alpha beta
    GLfloat updatedAlpha;
    GLfloat updatedBeta;
    if(rotType==top1||rotType==top2||rotType==bottom1||rotType==bottom2){
        //roty
        updatedAlpha=0;
        updatedBeta=0;
    }else if(rotType==front1||rotType==front2||rotType==back1||rotType==back2){
        //rot z
        updatedAlpha=90;
        updatedBeta=90;
    }else{
        //rotx
        //rotType==left1||rotType==left2||rotType==right1||rotType==right2
        updatedAlpha=90;
        updatedBeta=0;
    }
    
    for(int i=0; i<4; i++){
        cubes[modifyIndexes[i]].setAlpha(updatedAlpha);
        cubes[modifyIndexes[i]].setBeta(updatedBeta);
    }
    
    
}


// OpenGL initialization
void init()
{
    
    //init cubes
    for(int i=0; i<8; i++){
        cubes.push_back(cube(i));
    }
    
    
    glGenVertexArrays( 8, abuffer );
    
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    
    
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(0) );
    
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(sizeof( cubes[0].points)) );
    
    GLuint buffers[8];
    
    for(int i =0; i<8; i++){
        glBindVertexArray( abuffer[i] );
        glGenBuffers( 1, &buffers[i] );
        glBindBuffer( GL_ARRAY_BUFFER, buffers[i] );
        glBufferData(GL_ARRAY_BUFFER,  sizeof(cubes[i].points) + sizeof(cubes[i].colors), cubes[i].points, GL_STATIC_DRAW);
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( cubes[i].points), cubes[i].points );
        glBufferSubData( GL_ARRAY_BUFFER, sizeof( cubes[i].points), sizeof(cubes[i].colors),  cubes[i].colors );
        
        glEnableVertexAttribArray( vPosition );
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(0) );
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(sizeof( cubes[i].points)) );
        
    }
    
    // Retrieve transformation uniform variable locations
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );
    
    // Set projection matrix
    mat4  projection;
    projection = Ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Ortho(): user-defined function in mat.h
    //projection = Perspective( 45.0, 1.0, 0.5, 3.0 );
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    
    glEnable( GL_DEPTH_TEST );
    
    glClearColor( 0,0,0,1 ); //0001: black, 1110:white
    
    glUseProgram( program );
}





//CALLBACK-FUNCTIONS-START-------------------------------------------------------------------------

void display( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for(int i =0; i<8; i++){
        
        glBindVertexArray( abuffer[i] );
        mat4 instance = cubes[i].cube_model_view;
        glUniformMatrix4fv( ModelView, 1, GL_TRUE,  instance );
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glFlush();
        
    }
    
    glutSwapBuffers();
    
}

void keyboard( unsigned char key, int x, int y )
{

    switch( key ) {
        case 033:  // Escape key
        case 'q': case 'Q':
            exit( EXIT_SUCCESS );
            break;
            
        case 'c':
            //rotate top ccw
            rotDirection=1;
            faceToRotate=4;
            updateIndexes(top1);
            animate=true;
            break;
        case 'f':
            //rotate top cw
            rotDirection=-1;
            faceToRotate=4;
            updateIndexes(top2);
            animate=true;
            break;
        case 'v':
            //rotate bottom ccw
            rotDirection=1;
            faceToRotate=5;
            updateIndexes(bottom1);
            animate=true;
            break;
        case 'g':
            //rotate bottom cw
            rotDirection=-1;
            faceToRotate=5;
            updateIndexes(bottom2);
            animate=true;
            break;
        case 'b':
            //rotate left ccw
            rotDirection=1;
            faceToRotate=3;
            updateIndexes(left1);
            animate=true;
            break;
        case 'h':
            //rotate left cw
            rotDirection=-1;
            faceToRotate=3;
            updateIndexes(left2);
            animate=true;
            break;
        case 'n':
            //rotate right ccw
            rotDirection=1;
            faceToRotate=2;
            updateIndexes(right1);
            animate=true;
            break;
        case 'j':
            //rotate right cw
            rotDirection=-1;
            faceToRotate=2;
            updateIndexes(right2);
            animate=true;
            break;
        case 'm':
            //rotate front ccw
            rotDirection=1;
            faceToRotate=0;
            updateIndexes(front1);
            animate=true;
            break;
        case 'k':
            //rotate front cw
            rotDirection=-1;
            faceToRotate=0;
            updateIndexes(front2);
            animate=true;
            break;
        case 'l':
            //rotate back ccw
            rotDirection=1;
            faceToRotate=1;
            updateIndexes(back1);
            animate=true;
            break;
        case 'p':
            //rotate back cw
            rotDirection=-1;
            faceToRotate=1;
            updateIndexes(back2);
            animate=true;
            break;
        case 'a':
            for(int i=0; i<8; i++){
                cubes[i].incrementrotateYangle(-3);
            }
            break;
        case 'd':
            for(int i=0; i<8; i++){
                cubes[i].incrementrotateYangle(3);
            }
            break;
        case 'w':
            for(int i=0; i<8; i++){
                cubes[i].incrementrotateXangle(-3);
            }
            break;
        case 's':
            for(int i=0; i<8; i++){
                cubes[i].incrementrotateXangle(3);
            }
            break;
        case 'i':case 'I':
            std::cout << "------------------------------" << std::endl;
            std::cout << "-----------CONTROLS-----------" << std::endl;
            std::cout << "------------------------------" << std::endl;
            
            std::cout << "F/C\t Rotate the top cw/ccw" << std::endl;
            std::cout << "G/V\t Rotate the bottom cw/ccw" << std::endl;
            std::cout << "H/B\t Rotate the left cw/ccw" << std::endl;
            std::cout << "J/N\t Rotate the right cw/ccw" << std::endl;
            std::cout << "K/M\t Rotate the front cw/ccw" << std::endl;
            std::cout << "P/L\t Rotate the back cw/ccw" << std::endl;
            std::cout << "W/A/S/D\t Rotate the cube as a whole" << std::endl;
            std::cout << "Q\tExit the program" << std::endl;
             std::cout << "\t " << std::endl;
            std::cout << "Important: While it is possible to rotate any face in any direction (in initial state)," << std::endl;
            std::cout << "there isn't any mechanism to track the faces after rotations." << std::endl;
            std::cout << "To avoid weird looking shapes, make sure you rotate the last rotated face in the " << std::endl;
            std::cout << "reverse direction before trying another face and do not interrupt the ongoing animation with another keyboard input." << std::endl;
            std::cout << "Example run: F,C,G,V,H,B,J,N,K,M,P,L" << std::endl;
            
            break;
            
            
    }
}

void reshape( int w, int h ){
    //Keeps the window square shaped.
    
    if (( w != 700 ) || ( h != 700 ))
    {
        glutReshapeWindow(w, w);
        w = 700;
        h = 700;
    }
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(0.0f, (GLfloat) w,(GLfloat) h, 0.0f,-10.0f,10.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
    
    
}
void Timer(int value) {
    if(animate){
        angle+=1;
        
        for(int j=0; j<4; j++){
            cubes[modifyIndexes[j]].incrementAngle(1*rotDirection);
            
        }
        
        if(angle==90 ){
            angle=0;
            animate=false;
            
        }
    }
    glutTimerFunc(5, Timer, 0);
    glutPostRedisplay();
}


void idle( void ){
    for(int i=0; i<8; i++){
        cubes[i].updateModelView();
    }
    glutPostRedisplay();
}


//CALLBACK-FUNCTIONS-END-------------------------------------------------------



int main( int argc, char **argv )
{
    
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE );
    glutInitWindowSize( 700, 700 );
    glutInitWindowPosition( 470, 100 );
    glutCreateWindow( "Assignment 2" );
    
    printf("Press 'I' for info. \n");
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    init();
    Timer(0);
    
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutReshapeFunc( reshape );
    // glutIdleFunc( idle );
    glutMainLoop();
    
    return 0;
}

