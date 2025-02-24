#include <windows.h>
#include <GL/glut.h>

void display() {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Set background color to blue
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the screen
    glFlush();                             // Render the frame
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Hello OpenGL");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
