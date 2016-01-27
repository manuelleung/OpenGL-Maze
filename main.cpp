#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include "Maze.h"
#include <stdio.h>
#include <cmath>

/* Maze constructor */
static Maze m;
/* Generate the maze */
static int** myMaze = m.generateMaze();

/* Get the height and width of maze */
static int height = m.getHeight();
static int width = m.getWidth();

/* Vertices for cube */
static float v[8][3] =
{
    /* X, Y, Z */
    {1.0f, 1.0f, -1.0f},   // V0
    {-1.0f, 1.0f, -1.0f},  // V1
    {-1.0f, 1.0f, 1.0f},   // V2
    {1.0f, 1.0f, 1.0f},    // V3
    {1.0f, -1.0f, 1.0f},   // V4
    {-1.0f, -1.0f, 1.0f},  // V5
    {-1.0f, -1.0f, -1.0f}, // V6
    {1.0f, -1.0f, -1.0f}   // V7
};

/* Start and end points */
static float startH = 1.0f;
static float startW = 8.0f;
static float endH = 8.0f;
static float endW = 1.0f;

/* Camera values (eye, lookAt, angle) */
static float angle = 0.0;
static float lookX = 0.0f;
static float lookZ = -1.0f;
static float eyeX = startH*2;
static float eyeZ = startW*2;

/* Bird's eye flag */
static BOOLEAN birdsEye = false;

/* Resize callback */
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(45.0f, ar, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

/* Cube made of quads */
static void drawCube()
{
    glBegin(GL_QUADS);
        // Color
        glColor3f(0.0f, 0.0f, 0.0f);    // Black
        // Top square
        glVertex3fv(v[0]);  // Top: right
        glVertex3fv(v[1]);  // Top: left
        glVertex3fv(v[2]);  // Bottom: left
        glVertex3fv(v[3]);  // Bottom: right
        // Bottom square
        glVertex3fv(v[4]);  // Top: right
        glVertex3fv(v[5]);  // Top: left
        glVertex3fv(v[6]);  // Bottom: left
        glVertex3fv(v[7]);  // Bottom: right
        // Front square
        glVertex3fv(v[3]);  // Top: right
        glVertex3fv(v[2]);  // Top: left
        glVertex3fv(v[5]);  // Bottom: left
        glVertex3fv(v[4]);  // Bottom: right
        // Back square
        glVertex3fv(v[7]);  // Top: right
        glVertex3fv(v[6]);  // Top: left
        glVertex3fv(v[1]);  // Bottom: left
        glVertex3fv(v[0]);  // Bottom: right
        // Left square
        glVertex3fv(v[2]);  // Top: right
        glVertex3fv(v[1]);  // Top: left
        glVertex3fv(v[6]);  // Bottom: left
        glVertex3fv(v[5]);  // Bottom: right
        // Right square
        glVertex3fv(v[0]);  // Top: right
        glVertex3fv(v[3]);  // Top: left
        glVertex3fv(v[4]);  // Bottom: left
        glVertex3fv(v[7]);  // Bottom: right
    glEnd();
}

/* Ball to represent the camera */
static void drawBall()
{
    // Draw at position of eyeX and eyeZ
    glPushMatrix();
        glTranslatef(eyeX, 1.0f, eyeZ);
        glColor3f(1.0f, 0.0f, 0.0f);
        glutSolidSphere(0.75f, 20, 20);
    glPopMatrix();
}

/* Construct the maze */
static void drawMaze()
{
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            // End point
            if(endH==h && endW==w) {
                // Draw green square at end
                glPushMatrix();
                    glTranslatef(h*2.0f, 1.0f, w*2.0f);
                    glColor3f(0.0f, 1.0f, 0.0f);
                    glutSolidCube(1);
                glPopMatrix();
            }
            // Start point
            else if(startH==h && startW==w) {
                // Draw blue square at beginning
                glPushMatrix();
                    glTranslatef(h*2.0f, 1.0f, w*2.0f);
                    glColor3f(0.0f, 0.0f, 1.0f);
                    glutSolidCube(1);
                glPopMatrix();
            }
            // Walls
            else if(myMaze[h][w] == 1) {
                glPushMatrix();
                    glTranslatef(h*2.0f, 1.0f, w*2.0f);
                    drawCube();
                glPopMatrix();
            }
            // Path
            else if(myMaze[h][w] == 0) {
                 // Do nothing
                 continue;
            }
        }
    }
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
    glLoadIdentity();

    // Exit the program when camera has entered the end square (16-15, 1-2)
    if( ( eyeX < (endH*2) && eyeX>(endH*2)-1 ) || ( eyeZ>(endW*2)-1 && eyeZ<(endW) ) )
        exit(0);

    // Set camera to look at perspective with Y as up OR top down for bird's eye
    if(birdsEye == false)
        gluLookAt( eyeX, 1.0f, eyeZ, (eyeX+lookX), 1.0f, (eyeZ+lookZ), 0.0f, 1.0f, 0.0f);
    else
        gluLookAt( 8.0f, 70.0f, 8.0f, 8.0f, 1.0f, 7.0f, 0.0f, 1.0f, 0.0f);

    // Draw Camera ball
    drawBall();

    // Make maze
    drawMaze();

    glutSwapBuffers();
}

/* Normal ascii keyboard input handler */
static void normalKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
        // Exit key
        case 27 :
        case 'q':
            exit(0);
            break;

        // Space - bird's eye switch
        case ' ':
            if(birdsEye == false)
                birdsEye = true;
            else
                birdsEye = false;
            break;
    }
    glutPostRedisplay();
}

/* Special non ascii keyboard input handler */
static void specialKeys(int key, int xx, int yy)
{
    float moveFraction = 0.2f;
    float rotateFraction = 0.02f;

    switch (key)
    {
        // Left arrow - rotate counter-clockwise
		case GLUT_KEY_LEFT:
		angle -= rotateFraction;
		lookX = sin(angle);
		lookZ = -cos(angle);
		break;

        // Right arrow - rotate clockwise
		case GLUT_KEY_RIGHT:
		angle += rotateFraction;
		lookX = sin(angle);
		lookZ = -cos(angle);
		break;

        // Up arrow - move forward
		case GLUT_KEY_UP:
		eyeX += lookX * moveFraction;
		eyeZ += lookZ * moveFraction;
		break;

        // Down arrow - move downward
		case GLUT_KEY_DOWN:
		eyeX -= lookX * moveFraction;
		eyeZ -= lookZ * moveFraction;
		break;
    }

    glutPostRedisplay();
}

/* Program entry point */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("GLUT Maze");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutIdleFunc(display);
    glutKeyboardFunc(normalKeys);
    glutSpecialFunc(specialKeys);
    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glutMainLoop();
    return EXIT_SUCCESS;
}
