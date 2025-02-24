#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set text color to white
    glColor3f(1.0, 1.0, 1.0);

    // Position the text (slightly left and up from center)
    glRasterPos2f(-0.3, 0.0);

    // Draw "Hello World" character by character
    const char* text = "Hello World";
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Window (C)");

    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    gluOrtho2D(-1, 1, -1, 1); // Setting coordinate system

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
