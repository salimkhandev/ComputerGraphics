#include <GL/glut.h>
#include <cmath>

// Global variables for ball position and rotation
float ballX = 0.0f;
float ballY = 0.5f;  // Ball radius is 0.5, so this keeps it on the ground
float ballZ = 0.0f;
float rotationAngle = 0.0f;
float bounceHeight = 0.0f;
float time = 0.0f;
const float BALL_RADIUS = 0.5f;
const float GRAVITY = 9.81f;
const float BOUNCE_DAMPING = 0.8f;
float verticalVelocity = 0.0f;

void init() {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);  // Sky blue background
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    // Adjusted lighting for better edge visibility
    GLfloat light_position[] = { 3.0f, 6.0f, 5.0f, 0.0f };
    GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat light_diffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat light_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
}

void drawGround() {
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);  // Darker gray color for ground
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawBall() {
    // Bright red base color for the ball
    GLfloat red_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };      // Pure red
    GLfloat red_specular[] = { 1.0f, 0.2f, 0.2f, 1.0f };     // Light red specular
    GLfloat red_ambient[] = { 0.7f, 0.0f, 0.0f, 1.0f };      // Darker red ambient
    GLfloat shininess[] = { 50.0f };

    // Set material properties for red parts
    glMaterialfv(GL_FRONT, GL_AMBIENT, red_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, red_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
    glTranslatef(ballX, ballY, ballZ);
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);

    // Draw the base red sphere
    glutSolidSphere(BALL_RADIUS, 32, 32);

    // Draw edge pattern with darker red
    GLfloat edge_diffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f };     // Slightly darker red
    GLfloat edge_specular[] = { 0.6f, 0.1f, 0.1f, 1.0f };
    GLfloat edge_ambient[] = { 0.5f, 0.0f, 0.0f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, edge_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, edge_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, edge_specular);

    // Draw faceted pattern
    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glRotatef(i * 45.0f, 0.0f, 1.0f, 0.0f);

        for (int j = 0; j < 4; j++) {
            glPushMatrix();
            glRotatef(j * 90.0f, 1.0f, 0.0f, 0.0f);
            glTranslatef(0.0f, 0.0f, BALL_RADIUS * 0.99f);
            glScalef(0.25f, 0.25f, 0.02f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }

        // Add diagonal edges
        for (int j = 0; j < 4; j++) {
            glPushMatrix();
            glRotatef(45.0f + j * 90.0f, 1.0f, 0.0f, 0.0f);
            glTranslatef(0.0f, 0.0f, BALL_RADIUS * 0.99f);
            glScalef(0.25f, 0.25f, 0.02f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }

        glPopMatrix();
    }

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(3.0f, 4.0f, 5.0f,    // Camera position
        0.0f, 0.0f, 0.0f,    // Look at point
        0.0f, 1.0f, 0.0f);   // Up vector

    drawGround();
    drawBall();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void update(int value) {
    float deltaTime = 0.01f;  // 10ms in seconds
    float speed = 5.0f;      // Units per second

    // Update horizontal position
    float previousX = ballX;
    ballX += speed * deltaTime;

    // Calculate rotation based on distance traveled
    float distanceTraveled = ballX - previousX;
    float rotationPerUnit = 360.0f / (2.0f * M_PI * BALL_RADIUS);
    rotationAngle += distanceTraveled * rotationPerUnit;

    // Update vertical motion with realistic physics
    verticalVelocity -= GRAVITY * deltaTime;
    ballY += verticalVelocity * deltaTime;

    // Ground collision with bouncing
    if (ballY < BALL_RADIUS) {
        ballY = BALL_RADIUS;
        verticalVelocity = -verticalVelocity * BOUNCE_DAMPING;

        // Add small random bounce variation
        verticalVelocity += (rand() % 100) / 1000.0f;
    }

    // Reset ball position when it goes off screen
    if (ballX > 10.0f) {
        ballX = -10.0f;
        // Add a random initial bounce
        verticalVelocity = 3.0f + (rand() % 100) / 100.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rolling Ball");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
