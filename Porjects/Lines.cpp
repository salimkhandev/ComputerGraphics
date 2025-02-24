#include <windows.h>
#include <GL/glut.h>
#include <cmath>

float ballX = -3.0f;  // Ball's X position
float angle = 0.0f;   // Rotation angle
float speed = 0.05f;  // Movement speed

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set camera position (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
    gluLookAt(0.0, 1.5, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Draw ground
    glColor3f(0.2f, 0.5f, 0.2f); // Green ground
    glBegin(GL_QUADS);
    glVertex3f(-4.0f, -0.5f, -4.0f);
    glVertex3f(4.0f, -0.5f, -4.0f);
    glVertex3f(4.0f, -0.5f, 4.0f);
    glVertex3f(-4.0f, -0.5f, 4.0f);
    glEnd();

    // Draw the ball
    glPushMatrix();
    glTranslatef(ballX, -0.2f, 0.0f); // Move ball
    glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis
    glColor3f(1.0f, 0.0f, 0.0f); // Red ball
    glutSolidSphere(0.3, 30, 30); // Sphere with high resolution
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value) {
    ballX += speed;  // Move ball to the right
    angle -= 5.0f;   // Rotate for rolling effect

    // Reset position when it reaches the right edge
    if (ballX > 3.0f) {
        ballX = -3.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Call update every 16ms (~60 FPS)
}

void init() {
    glEnable(GL_DEPTH_TEST);  // Enable depth test
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Rolling Ball in 3D");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0); // Start animation

    glutMainLoop();
    return 0;
}
