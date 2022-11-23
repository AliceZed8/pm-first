#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <cmath>
#include <iostream>

float vert[] = {1,1,0 ,  1,-1,0,  -1,-1,0, -1, 1,0};
float xAlfa = 20;
float zAlfa = 20;
float x_pos = 0, y_pos = 0;
float speed = 0;
float temp_angle = 0;
const float pi = 3.14159265358979;


void specKey(int key, int x, int y) {

}


void pressKey(unsigned char key, int x, int y){
    temp_angle = (-zAlfa * pi) / 180;
    std::cout << key << std::endl;
    switch (key) {
        case 'w':
            if (xAlfa < 178) {
                xAlfa+= 2;
            }
            break;
        case 's':
            if (xAlfa > 2) {
                xAlfa-=2;
            }
            break;
        case 'a':
            zAlfa+=3;
            break;
        case 'd':
            zAlfa-=3;
            break;
        case 't':
            speed = 0.3;
            break;
        case 'g':
            speed = -0.3;
            break;

        case 'f':
            speed = 0.3;
            temp_angle -= pi/2;
            break;

        case 'h':
            speed = 0.3;
            temp_angle += pi/2;
            break;

    }

}
void ShowWorld() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0 , &vert);
    for (int i = -10; i < 10; i++) {
        for (int j = -10; j < 10; j++) {
            glPushMatrix();
            if ((i+j)%2 == 0) glColor3f(0,0.5,0);
            else glColor3f(1,1,1);
            glTranslatef(i*2, j*2, 0);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glPopMatrix();
        }
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}


void MoveCamera() {
    glRotatef(-xAlfa, 1, 0,0);
    glRotatef(-zAlfa, 0, 0,1);

    if (speed != 0) {
        x_pos += std::sin(temp_angle) * speed;
        y_pos += std::cos(temp_angle) * speed;
    }
    speed = 0;


    glTranslatef(-x_pos,-y_pos,-3);
}


void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    MoveCamera();
    ShowWorld();
    glPopMatrix();

    glutSwapBuffers();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello");

    glFrustum(-1,1,  -1, 1,  2, 80);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutKeyboardFunc(pressKey);

    glutMainLoop();

}
