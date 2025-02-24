#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Window (C++)");

    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    gluOrtho2D(-1, 1, -1, 1); // Setting coordinate system

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
