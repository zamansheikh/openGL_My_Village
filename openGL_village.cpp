#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <time.h>

/*
About the project:
This project is a simple 2D animation of a village scene. The scene includes a river, trees, houses, a boat, a well, and a tubewell. The scene also includes a day/night mode that can be toggled using the 'd' key. During the night, the scene also includes a moon and rain. The boat moves from left to right, and the fish move from right to left. The clouds also move from left to right. The scene is drawn using basic shapes such as rectangles, polygons, and circles. The scene is animated using the OpenGL library in C++.
This project is created by:
- Zaman Sheikh(github.com/zamansheikh) | Md. Shamsuzzaman | 211-15-4031 | Team Leader
- Nafiz | Mohaiminul Islam Nafiz | 211-15-4041

*/

// ------------------------------------CONTROL-------------------------------------------------
int i;
double dxr = 15, dyr = 15;
float cloud1Position = 150, cloud1Speed = 0.11;
float cloud2Position = 20, cloud2Speed = 0.11;

float boatPosition = -110, boatSpeed = 0.2;
float treeLeafSizeXr = 22, treeLeafSizeYr = 15;
float tree2LeafSizeXr = 17, tree2LeafSizeYr = 15;
float tree3LeafSizeXr = 90, tree3LeafSizeYr = 60;
float tree4LeafSizeXr = 38, tree4LeafSizeYr = 103;
float fishPosition = 100, fishSpeed = 0.2;
// Day/Night mode control
bool isDay = true;
bool isRaining = false;

// Position of the bird
float birdX = 200.0f;
float birdY = 700.0f;
float birdSpeed = 0.5f;
// Flag to toggle between two wing positions
bool wingUp = true;

float frenceDoor = 0;

// ------------------------------------CIRCLE-------------------------------------------------

void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

// ------------------------------------Fence-------------------------------------------------
void fence(int x)
{
    glBegin(GL_POLYGON);
    glColor3ub(184, 134, 11);

    glVertex2i(1000 - x, 350);
    glVertex2i(1000 - x, 290);
    glVertex2i(997 - x, 290);
    glVertex2i(997 - x, 350);
    glVertex2i(1000 - x, 350);

    glEnd();
}

void fenceAll()
{
    int x = 0;
    for (int i = 0; i < 45; i++)
    {
        fence(x);
        x += 10;
    }
    x = 500;
    for (int i = 50; i < 100; i++)
    {
        fence(x);
        x += 10;
    }
    glColor3ub(184, 134, 11); // left side
    glRecti(0, 340, 500, 335);
    glRecti(0, 320, 500, 315);
    glRecti(0, 305, 500, 300);

    glColor3ub(184, 134, 11); // right side
    glRecti(550, 340, 1000, 335);
    glRecti(550, 320, 1000, 315);
    glRecti(550, 305, 1000, 300);

    glPushMatrix();
    glTranslatef(frenceDoor, 0, 0);
    glColor3ub(184, 134, 11); // door
    glRecti(500, 345, 550, 340);
    glRecti(500, 325, 550, 320);
    glRecti(500, 310, 550, 305);
    glPopMatrix();
    fence(450 - frenceDoor);
    fence(460 - frenceDoor);
    fence(470 - frenceDoor);
    fence(480 - frenceDoor);
    fence(490 - frenceDoor);
}

// ------------------------------------RAIN-------------------------------------------------
// Structure to represent a rain drop
struct RainDrop
{
    float x;
    float y;
    float speed;
};

const int MAX_RAINDROPS = 500; // Maximum number of raindrops
RainDrop rain[MAX_RAINDROPS];

// Initialize rain drops with random positions and speeds
void initRain()
{
    srand(time(0)); // Seed the random number generator
    for (int i = 0; i < MAX_RAINDROPS; i++)
    {
        rain[i].x = rand() % 1000;                // Random x position within the window width
        rain[i].y = rand() % 800 + 800;           // Random y position starting above the window height
        rain[i].speed = (rand() % 5 + 2) / 10.0f; // Random speed between 0.2 and 0.7
    }
}

// Update rain drop positions for animation
void updateRain()
{
    for (int i = 0; i < MAX_RAINDROPS; i++)
    {
        rain[i].y -= rain[i].speed;

        // If the drop reaches the bottom, reset its position
        if (rain[i].y < 0)
        {
            rain[i].x = rand() % 1000;
            rain[i].y = 800;
        }
    }
}

// Draw the rain drops
void drawRain()
{
    glColor3f(1.0f, 1.0f, 1.0f); // White color for rain
    glBegin(GL_LINES);
    for (int i = 0; i < MAX_RAINDROPS; i++)
    {
        glVertex2f(rain[i].x, rain[i].y);
        glVertex2f(rain[i].x, rain[i].y + 5); // Draw a short line for each drop
    }
    glEnd();
}

void house1(GLfloat red, GLfloat green, GLfloat blue)
{
    // --------------------------------------- HOUSE one----------------------------
    glBegin(GL_POLYGON);         // first Part
    glColor3f(red, green, blue); // gray
    glVertex2i(152, 335);
    glVertex2i(135, 365);
    glVertex2i(95, 370); // point
    glVertex2i(120, 320);
    glVertex2i(160, 320);
    glVertex2i(152, 335);
    glEnd();

    glBegin(GL_POLYGON);         // second Part
    glColor3f(red, green, blue); // maroon
    glVertex2i(95, 370);
    glVertex2i(80, 320);
    glVertex2i(90, 320);  // point
    glVertex2i(102, 357); // point
    glVertex2i(95, 370);
    glEnd();

    glBegin(GL_POLYGON);     // wall
    glColor3ub(46, 139, 87); //
    glVertex2i(102, 357);
    glVertex2i(90, 320);
    glVertex2i(90, 265);
    glVertex2i(120, 260); // point
    glVertex2i(120, 320);
    glVertex2i(102, 357);
    glEnd();

    glBegin(GL_POLYGON);       // wall
    glColor3ub(143, 188, 143); //
    glVertex2i(120, 260);
    glVertex2i(154, 265);
    glVertex2i(154, 320);
    glVertex2i(120, 320);
    glEnd();

    glColor3f(red, green, blue); // maroon // Door One
    glRecti(135, 300, 145, 260);
    glColor3f(red, green, blue); // maroon // Window
    glRecti(100, 310, 110, 290);

    glBegin(GL_POLYGON); // third Part (lower part 1)
    glColor3ub(0, 0, 0); //
    glVertex2i(120, 260);
    glVertex2i(87, 265);
    glVertex2i(87, 255);
    glVertex2i(120, 250);
    glVertex2i(120, 260);
    glEnd();

    glBegin(GL_POLYGON); // third Part (lower part 2)
    glColor3ub(0, 0, 0); //
    glVertex2i(120, 260);
    glVertex2i(155, 265);
    glVertex2i(155, 255);
    glVertex2i(120, 250);
    glVertex2i(120, 260);
    glEnd();
}

//-------------------------------------------  HOUSE  two  -------------------------------------------------
void house2(GLfloat red, GLfloat green, GLfloat blue)
{
    //-------------------------------------------  HOUSE  two  -------------------------------------------------
    glBegin(GL_POLYGON); // First part

    glColor3f(red, green, blue); // midnight blue
    glVertex2i(160, 360);
    glVertex2i(210, 369);
    glVertex2i(198, 308);
    glVertex2i(145, 309);
    glVertex2i(160, 360);
    glEnd();

    glBegin(GL_POLYGON);      // wall
    glColor3ub(70, 130, 180); // midnight blue
    glVertex2i(150, 310);
    glVertex2i(150, 250);
    glVertex2i(200, 245);
    glVertex2i(200, 315);
    glEnd();

    //--------------------------------------------------------------------------
    glBegin(GL_POLYGON);      // wall
    glColor3ub(95, 158, 160); // midnight blue
    glVertex2i(200, 245);
    glVertex2i(228, 255);
    glVertex2i(228, 320);
    glVertex2i(210, 368);
    glVertex2i(200, 320);
    glVertex2i(200, 245);

    //---------------------------------------Door------------------------------------------
    glColor3f(red, green, blue); // midnight blue
    glRecti(165, 290, 180, 247);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(red, green, blue); // midnight blue
    glVertex2i(209, 370);
    glVertex2i(230, 320);
    glVertex2i(227, 310);
    glVertex2i(206, 360);
    glVertex2i(209, 370);

    glEnd();

    glBegin(GL_POLYGON);         // door
    glColor3f(red, green, blue); // midnight blue
    glVertex2i(210, 290);
    glVertex2i(220, 293);
    glVertex2i(220, 252);
    glVertex2i(210, 249);
    glVertex2i(210, 290);

    glEnd();
    glBegin(GL_POLYGON); // (lower part 1)
    glColor3ub(0, 0, 0); //
    glVertex2i(200, 245);
    glVertex2i(200, 235);
    glVertex2i(230, 247);
    glVertex2i(230, 257);
    glVertex2i(200, 245);

    glEnd();
    glBegin(GL_POLYGON); // (lower part 2)
    glColor3ub(0, 0, 0); //
    glVertex2i(200, 245);
    glVertex2i(148, 250);
    glVertex2i(148, 240);
    glVertex2i(200, 235);
    glVertex2i(200, 245);

    glEnd();
}

//-------------------------------------TREE 1------------------------
void tree1()
{
    glBegin(GL_POLYGON); // Main Tree // first part
    glColor3ub(139, 69, 19);
    glVertex2i(55, 380);
    glVertex2i(57, 340);
    glColor3ub(139, 69, 19);
    glVertex2i(47, 260);
    glVertex2i(80, 260);
    glColor3ub(139, 69, 19);
    glVertex2i(72, 340);
    glVertex2i(75, 380);
    glVertex2i(55, 380);
    glEnd();

    glBegin(GL_POLYGON); // Main Tree // second part
    glColor3ub(139, 69, 19);
    glVertex2i(72, 320);
    glVertex2i(125, 420);
    glVertex2i(130, 420);
    glVertex2i(72, 300);
    glVertex2i(72, 320);
    glEnd();

    glBegin(GL_POLYGON); // Main Tree // third part
    glColor3ub(139, 69, 19);
    glVertex2i(55, 380);
    glVertex2i(40, 430);
    glVertex2i(35, 430);
    glVertex2i(57, 310);
    glVertex2i(55, 380);
    glEnd();

    glBegin(GL_POLYGON);     // Main Tree // fourth part
    glColor3ub(139, 69, 19); //
    glVertex2i(65, 380);
    glVertex2i(75, 430);
    glVertex2i(85, 430);
    glVertex2i(75, 380);
    glVertex2i(65, 380);
    glEnd();

    glColor3ub(0, 128, 0); // leaf
    circle(treeLeafSizeXr, treeLeafSizeYr, 130, 420);
    circle(treeLeafSizeXr, treeLeafSizeYr, 145, 400);
    circle(treeLeafSizeXr, treeLeafSizeYr, 115, 400);
    circle(treeLeafSizeXr, treeLeafSizeYr, 105, 420);

    circle(treeLeafSizeXr, treeLeafSizeYr, 75, 420);
    circle(treeLeafSizeXr, treeLeafSizeYr, 95, 400);
    circle(treeLeafSizeXr, treeLeafSizeYr, 100, 440);
    circle(treeLeafSizeXr, treeLeafSizeYr, 85, 450);

    circle(treeLeafSizeXr, treeLeafSizeYr, 35, 430);
    circle(treeLeafSizeXr, treeLeafSizeYr, 45, 420);
    circle(treeLeafSizeXr, treeLeafSizeYr, 50, 445);
    circle(treeLeafSizeXr, treeLeafSizeYr, 30, 410);
}

//-------------------------------------TREE 2------------------------
void tree2()
{
    //-------------------------------------Secondary TREE------------------------
    glColor3ub(139, 69, 19); //
    glRecti(205, 420, 212, 360);
    glColor3ub(0, 100, 0);
    circle(tree2LeafSizeXr, tree2LeafSizeYr, 195, 410);
    circle(tree2LeafSizeXr, tree2LeafSizeYr, 225, 410);
    circle(tree2LeafSizeXr, tree2LeafSizeYr, 215, 430);
    circle(tree2LeafSizeXr, tree2LeafSizeYr, 195, 395);
    circle(tree2LeafSizeXr, tree2LeafSizeYr, 225, 390);
}

void tree3()
{
    //-------------------------------------Secondary TREE------------------------
    glColor3ub(139, 69, 19); // Tree trunk color
    glRecti(860, 360, 905, -120);

    glColor3ub(0, 100, 0); // Dark green leaves
    circle(tree3LeafSizeXr, tree3LeafSizeYr, 845, 330);

    glColor3ub(0, 104, 0); // Slightly lighter green leaves
    circle(tree3LeafSizeXr, tree3LeafSizeYr, 935, 330);

    glColor3ub(0, 105, 0); // Even lighter green leaves
    circle(tree3LeafSizeXr, tree3LeafSizeYr, 905, 390);

    glColor3ub(0, 100, 0); // Dark green leaves
    circle(tree3LeafSizeXr, tree3LeafSizeYr, 845, 285);

    glColor3ub(0, 101, 0); // Medium green leaves
    circle(tree3LeafSizeXr, tree3LeafSizeYr, 935, 270);
}


void tubewell()
{
    //-----------------------------------------------TUBEWELL-----------------------------------------

    glBegin(GL_POLYGON); // First part

    glColor3ub(0, 100, 0); //
    glVertex2i(325, 285);
    glVertex2i(305, 225);
    glVertex2i(355, 225);
    glVertex2i(375, 285);
    glVertex2i(325, 285);

    glEnd();
    glBegin(GL_POLYGON); // second part

    glColor3ub(143, 188, 143); //
    glVertex2i(330, 278);
    glVertex2i(314, 233);
    glVertex2i(350, 232);
    glVertex2i(365, 278);
    glVertex2i(330, 278);

    glEnd();
    glColor3ub(0, 0, 0); // third part
    glRecti(305, 225, 355, 214);

    glBegin(GL_POLYGON); // fourth  part
    glColor3ub(0, 0, 0); //
    glVertex2i(375, 285);
    glVertex2i(376, 275);
    glVertex2i(355, 214);
    glVertex2i(355, 225);
    glVertex2i(375, 285);
    glEnd();
    glBegin(GL_POLYGON); // tubewell 1st part
    glColor3ub(184, 134, 11);
    glVertex2i(330, 305);
    glVertex2i(330, 250);
    glVertex2i(335, 248);
    glVertex2i(340, 250);
    glVertex2i(340, 305);
    glVertex2i(335, 307);
    glVertex2i(330, 305);
    glEnd();
    glBegin(GL_POLYGON);     // tubewell second part
    glColor3ub(255, 215, 0); // golden rod
    glVertex2i(330, 305);
    glVertex2i(335, 300);
    glVertex2i(340, 305);
    glVertex2i(335, 307);
    glVertex2i(330, 305);

    glEnd();
    glColor3ub(205, 133, 63); // golden rod // tubewell third part
    glRecti(333, 320, 336, 305);

    glBegin(GL_POLYGON);     // tubewell fourth part
    glColor3ub(139, 69, 19); // saddle brown
    glVertex2i(336, 320);
    glVertex2i(338, 322);
    glVertex2i(338, 330);
    glVertex2i(336, 333);
    glVertex2i(334, 331);
    glVertex2i(310, 300);
    glVertex2i(300, 290);
    glVertex2i(300, 285);
    glVertex2i(310, 293);
    glVertex2i(336, 320);
    glEnd();
    glBegin(GL_POLYGON);      // tubewell 5th part
    glColor3ub(210, 105, 30); // golden rod
    glVertex2i(340, 290);
    glVertex2i(350, 290);
    glVertex2i(350, 270);
    glVertex2i(346, 270);
    glVertex2i(346, 280);
    glVertex2i(340, 280);
    glVertex2i(340, 290);

    glEnd();
    glColor3ub(210, 105, 30); // golden rod //tubewell last part
    glRecti(333, 249, 337, 240);
    glColor3ub(139, 69, 19); // saddle brown
    glRecti(328, 242, 342, 234);
}

void cloud1day()
{
    //-------------------------------------------CLOUD-------------------------------------------------
    glPushMatrix();
    glColor3ub(220, 220, 220);
    glTranslatef(cloud1Position, 0, 0);
    circle(40, 30, 210, 700);
    circle(40, 30, 235, 720);
    circle(40, 30, 260, 700);
    circle(20, 15, 195, 680);
    circle(20, 15, 220, 695);
    circle(20, 15, 250, 690);
    circle(20, 15, 275, 710);
    glPopMatrix();
}

void cloud2day()
{
    //-------------------------------------------CLOUD-------------------------------------------------
    glPushMatrix();
    glColor3ub(220, 220, 220);
    glTranslatef(cloud2Position, 0, 0);
    circle(30, 20, 500, 720);
    circle(30, 20, 525, 740);
    circle(30, 20, 540, 720);
    circle(30, 20, 550, 710);
    glPopMatrix();
}

void cloud1night()
{
    //-------------------------------------------CLOUD-------------------------------------------------
    glPushMatrix();
    glColor3f(0.529, 0.529, 0.506);
    glTranslatef(cloud1Position, 0, 0);
    circle(40, 30, 210, 700);
    circle(40, 30, 235, 720);
    circle(40, 30, 260, 700);
    circle(20, 15, 195, 680);
    circle(20, 15, 220, 695);
    circle(20, 15, 250, 690);
    circle(20, 15, 275, 710);
    glPopMatrix();
}

void cloud2night()
{
    //-------------------------------------------CLOUD-------------------------------------------------
    glPushMatrix();
    glColor3f(0.529, 0.529, 0.506);
    glTranslatef(cloud2Position, 0, 0);
    circle(30, 20, 500, 720);
    circle(30, 20, 525, 740);
    circle(30, 20, 540, 720);
    circle(30, 20, 550, 710);
    glPopMatrix();
}

void boat()
{
    //-------------------------------------------BOAT-------------------------------------------------
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glTranslatef(boatPosition, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(30, 450); // 150 + 300
    glVertex2i(45, 420); // 120 + 300
    glVertex2i(60, 400); // 100 + 300
    glVertex2i(60, 420); // 120 + 300
    glVertex2i(30, 450); // 150 + 300
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(60, 420);  // 120 + 300
    glVertex2i(60, 400);  // 100 + 300
    glVertex2i(90, 395);  // 95 + 300
    glVertex2i(120, 400); // 100 + 300
    glVertex2i(125, 420); // 120 + 300
    glVertex2i(60, 420);  // 120 + 300
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(125, 420); // 120 + 300
    glVertex2i(120, 400); // 100 + 300
    glVertex2i(135, 415); // 115 + 300
    glVertex2i(150, 450); // 150 + 300
    glVertex2i(125, 420); // 120 + 300
    glEnd();
    //--------------------------BOAT FLAG----------------------------
    glBegin(GL_POLYGON);
    glColor3ub(173, 216, 230);
    glVertex2i(153, 480); // 180 + 300
    glVertex2i(160, 510); // 210 + 300
    glVertex2i(161, 530); // 230 + 300
    glVertex2i(160, 550); // 250 + 300
    glVertex2i(155, 565); // 265 + 300
    glVertex2i(147, 577); // 277 + 300
    glVertex2i(137, 588); // 288 + 300 // end
    glVertex2i(105, 565); // 265 + 300
    glVertex2i(160, 510); // 210 + 300

    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(173, 216, 230);

    glVertex2i(142, 450); // 150 + 300
    glVertex2i(153, 480); // 180 + 300
    glVertex2i(125, 530); // 230 + 300
    glVertex2i(142, 450); // 150 + 300
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(173, 216, 230);
    glVertex2i(125, 420); // 120 + 300
    glVertex2i(142, 450); // 150 + 300
    glVertex2i(130, 510); // 210 + 300
    glVertex2i(125, 420); // 120 + 300
    glEnd();

    glColor3ub(139, 69, 19);
    glRecti(122, 600, 124, 420); // Boat stand, 300 added to each y value
    glBegin(GL_POLYGON);
    glColor3f(0.55, 0.27, 0.0745); // wood color
    glVertex2i(125, 420);          // 120 + 300
    glVertex2i(123, 440);          // 140 + 300
    glVertex2i(117, 458);          // 158 + 300
    glVertex2i(113, 465);          // 165 + 300
    glVertex2i(105, 470);          // 170 + 300
    glVertex2i(90, 472);           // 172 + 300
    glVertex2i(90, 420);           // 120 + 300
    glVertex2i(125, 420);          // 120 + 300
    glEnd();

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.55, 0.27, 0.0745); // wood color
    glVertex2i(60, 420);           // 120 + 300
    glVertex2i(62, 440);           // 140 + 300
    glVertex2i(68, 458);           // 158 + 300
    glVertex2i(72, 465);           // 165 + 300
    glVertex2i(80, 470);           // 170 + 300
    glVertex2i(95, 472);           // 172 + 300
    glVertex2i(95, 420);           // 120 + 300
    glVertex2i(60, 420);           // 120 + 300

    glEnd();

    //--------------------------BOAT LINE----------------------------
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex2i(68, 458);         // 158 + 300
    glVertex2i(137, 588);        // 288 + 300
    glVertex2i(137, 583);        // 283 + 300

    glVertex2i(68, 458);  // 158 + 300
    glVertex2i(105, 565); // 265 + 300
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex2i(62, 440);         // 140 + 300
    glVertex2i(123, 440);        // 140 + 300
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex2i(68, 458);         // 158 + 300
    glVertex2i(117, 458);        // 158 + 300
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex2i(95, 472);         // 172 + 300
    glVertex2i(95, 420);         // 120 + 300
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex2i(80, 470);         // 170 + 300
    glVertex2i(80, 420);         // 120 + 300
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex2i(110, 468);        // 168 + 300
    glVertex2i(110, 420);        // 120 + 300
    glEnd();

    glPopMatrix();
}

void fish(float x, float y, float size)
{
    glPushMatrix();
    glTranslatef(x, y, 0); // translate fish position

    // Fish body
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.65f, 0.0f); // orange color
    glVertex2f(0, 0);
    glVertex2f(20 * size, 10 * size);
    glVertex2f(30 * size, 5 * size);
    glVertex2f(20 * size, -5 * size);
    glVertex2f(0, 0);
    glEnd();

    // Fish tail
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.55f, 0.0f); // darker orange
    glVertex2f(30 * size, 5 * size);
    glVertex2f(40 * size, 15 * size);
    glVertex2f(40 * size, -5 * size);
    glEnd();

    // Fish eye
    glColor3f(1.0f, 1.0f, 1.0f); // white
    circle(1.5 * size, 1.5 * size, 10 * size, 5 * size);

    glColor3f(0.0f, 0.0f, 0.0f); // black
    circle(0.5 * size, 0.5 * size, 10 * size, 5 * size);

    glPopMatrix();
}

void drawFishGroup()
{
    glPushMatrix();
    glTranslatef(fishPosition, 0, 0);
    fish(120, 340, 0.5);
    fish(110, 350, 0.4);
    fish(100, 340, 0.3);
    fish(90, 350, 0.6);
    glPopMatrix();
}

// -------------------------------------SUN------------------------
void sun()
{
    glColor3ub(255, 215, 0);
    circle(34, 34, 700, 700);
}

void moon()
{
    glColor3ub(255, 255, 255);
    circle(34, 34, 700, 700);
    glColor3f(0.11f, 0.11f, 0.11f);
    circle(34, 34, 720, 710);
}

void daySky()
{
    glColor3f(0.529, 0.808, 0.980); // light blue
    glRecti(0, 800, 1000, 400);
}

void nightSky()
{
    glColor3f(0.11f, 0.11f, 0.11f); // black
    glRecti(0, 800, 1000, 400);
}

void drawBirdWingsUp()
{
    glPushMatrix();
    glTranslatef(birdX, birdY, 0);

    // Draw the bird body
    glColor3ub(0, 0, 0); // Black color for the bird
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(5, 10);
    glVertex2f(10, 10);
    glVertex2f(15, 0);
    glVertex2f(10, -10);
    glVertex2f(5, -10);
    glEnd();

    // Draw left wing up
    glBegin(GL_POLYGON);
    glVertex2f(5, 10);
    glVertex2f(-5, 20);
    glVertex2f(-15, 15);
    glVertex2f(0, 5);
    glEnd();

    // Draw right wing up
    glBegin(GL_POLYGON);
    glVertex2f(10, 10);
    glVertex2f(20, 20);
    glVertex2f(30, 15);
    glVertex2f(15, 5);
    glEnd();

    glPopMatrix();
}

// Function to draw a bird with wings down
void drawBirdWingsDown()
{
    glPushMatrix();
    glTranslatef(birdX, birdY, 0);

    // Draw the bird body
    glColor3ub(0, 0, 0); // Black color for the bird
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(5, 10);
    glVertex2f(10, 10);
    glVertex2f(15, 0);
    glVertex2f(10, -10);
    glVertex2f(5, -10);
    glEnd();

    // Draw left wing down
    glBegin(GL_POLYGON);
    glVertex2f(5, -10);
    glVertex2f(-5, -20);
    glVertex2f(-15, -15);
    glVertex2f(0, -5);
    glEnd();

    // Draw right wing down
    glBegin(GL_POLYGON);
    glVertex2f(10, -10);
    glVertex2f(20, -20);
    glVertex2f(30, -15);
    glVertex2f(15, -5);
    glEnd();

    glPopMatrix();
}

void timer(int value)
{
    wingUp = !wingUp; // Toggle the wing position
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0); // Call this function again after 1 second
}

void river()
{
    //------------------------------------------RIVER--------------------------------------------------
    glBegin(GL_POLYGON);
    glColor3ub(20, 80, 128); // Dark blue
    glVertex2i(0, 450);
    glVertex2i(1000, 450);
    glColor3ub(30, 144, 255); // light blue
    glVertex2i(1000, 310);    // MarkedUP
    glVertex2i(0, 300);
    glVertex2i(0, 500);
    glEnd();
    glBegin(GL_POLYGON);     // border
    glColor3ub(128, 128, 0); // Brown
    glVertex2i(0, 300);
    glVertex2i(1000, 310); // MarkedUP
    glVertex2i(1000, 300); // MatchedUP
    glVertex2i(0, 290);
    glVertex2i(0, 300);
    glEnd();
}

void field()
{
    //-----------------------------------field------------------------------
    glBegin(GL_POLYGON);
    // Set the color to green
    glColor3f(0, 0.3921, 0);
    // Update the coordinates to cover the entire width of the screen
    glVertex2i(0, 290);
    glVertex2i(1000, 300);
    // Change color to gold
    glColor3ub(155, 215, 0);
    glVertex2i(1000, 0);
    glVertex2i(0, 0);
    glVertex2i(0, 280);
    glEnd();
}

void canvas()
{
    glColor3ub(255, 255, 255);  // border
    glRecti(0, 800, 10, 0);     // Left border
    glRecti(990, 800, 1000, 0); // Right border
    glRecti(0, 800, 1000, 790); // Top border
    glRecti(0, 0, 1000, 10);    // Bottom border
}

void well()
{
    /// well
    glPushMatrix();
    glTranslatef(-200, -250, 0);

    glBegin(GL_POLYGON);
    glColor3ub(178, 34, 34);
    glVertex2f(306, 480);
    glVertex2f(306, 413);
    glVertex2f(289, 405);
    glVertex2f(272, 399);
    glVertex2f(238, 399);
    glVertex2f(221, 405);
    glVertex2f(204, 413);
    glVertex2f(204, 480);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 154, 214);
    glVertex2f(306, 480);
    glVertex2f(289, 472);
    glVertex2f(272, 470);
    glVertex2f(238, 470);
    glVertex2f(221, 472);
    glVertex2f(204, 480);
    glVertex2f(221, 487);
    glVertex2f(238, 489);
    glVertex2f(272, 489);
    glVertex2f(289, 487);
    glEnd();

    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3ub(204, 51, 0);
    glVertex2f(306, 480);
    glVertex2f(289, 487);
    glVertex2f(289, 487);
    glVertex2f(272, 489);
    glVertex2f(272, 489);
    glVertex2f(238, 489);
    glVertex2f(238, 489);
    glVertex2f(221, 487);
    glVertex2f(221, 487);
    glVertex2f(204, 480);
    glEnd();

    /// bucket
    glBegin(GL_POLYGON);
    glColor3ub(194, 194, 163);
    glVertex2f(319.6, 426.6);
    glVertex2f(312.8, 402.8);
    glVertex2f(295.8, 402.8);
    glVertex2f(289, 426.6);
    glVertex2f(295.8, 430);
    glVertex2f(312.8, 430);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 154, 214);
    glVertex2f(317.9, 426.6);
    glVertex2f(312.1, 423.2);
    glVertex2f(298.5, 423.2);
    glVertex2f(290.7, 426.6);
    glVertex2f(298.5, 427.3);
    glVertex2f(312.8, 427.3);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(194, 194, 163);
    glVertex2f(319.6, 426.6);
    glVertex2f(312.8, 441.8);
    glVertex2f(312.8, 441.8);
    glVertex2f(306, 441.8);
    glVertex2f(306, 441.8);
    glVertex2f(295.8, 441.8);
    glVertex2f(295.8, 441.8);
    glVertex2f(289, 426.6);
    glEnd();

    /// rope
    glLineWidth(2.5);
    glBegin(GL_LINES);
    glColor3ub(230, 172, 0);
    glVertex2f(304.3, 441.9);
    glVertex2f(312.8, 419.8);
    glVertex2f(312.8, 419.8);
    glVertex2f(314.5, 402.8);
    glVertex2f(314.5, 402.8);
    glVertex2f(316.2, 392.6);
    glVertex2f(316.2, 392.6);
    glVertex2f(312.8, 385.8);
    glVertex2f(312.8, 385.8);
    glVertex2f(282.2, 392.6);
    glEnd();
    glPopMatrix();
}

void drawPalmTree(float x, float y)
{
    // Draw trunk
    glColor3ub(139, 69, 19); // Brown color for trunk
    glBegin(GL_POLYGON);
    glVertex2f(x - 10, y);
    glVertex2f(x + 10, y);
    glVertex2f(x + 10, y + 100);
    glVertex2f(x - 10, y + 100);
    glEnd();

    // Draw fronds
    glColor3ub(50, 205, 50); // Green color for fronds
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 30, y + 100);
    glVertex2f(x, y + 150);
    glVertex2f(x + 30, y + 100);
    glEnd();
}

// ------------------------------------DRAWALL-------------------------------------------------
void drawAll()
{
    // Update sky color based on day/night mode
    isDay ? daySky() : nightSky();
    if (!isRaining)
    {
        isDay ? sun() : moon();
    }
    river();
    field();
    drawFishGroup();
    boat();
    fenceAll();

    isDay ? cloud1day() : cloud1night();
    isDay ? cloud2day() : cloud2night();
    wingUp ? drawBirdWingsUp() : drawBirdWingsDown();
    tree1();
    tree2();
    drawPalmTree(650, 300);
    tubewell();
    house1(0.231, 0.059, 0.016);
    house2(0.478, 0.029, 0.114);
    glPushMatrix();
    glTranslatef(650, -300, 0);
    glScalef(1.7, 1.7, 0);
    tree1();
    glPopMatrix();

    glPushMatrix();
    glScalef(2, 2, 0);
    glTranslatef(200, -200, 0);
    house1(0.231, 0.059, 0.016);
    house2(0.231, 0.059, 0.016);
    glPopMatrix();
    glPushMatrix();
    glScalef(2, 2, 0);
    glTranslatef(350, -200, 0);
    house1(0.231, 0.059, 0.016);
    glPopMatrix();

    tree3();

    well();

    canvas();
}

// ------------------------------------DISPLAY-------------------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAll();
    if (isRaining) // Show rain only during night time
    {
        drawRain();
    }
    glFlush();
}

// ------------------------------------ANIMATION----------------------------------------------
void update(int value)
{
    // Update cloud positions for animation
    cloud1Position += cloud1Speed;
    if (cloud1Position > 1000)
    {
        cloud1Position = 10;
    }

    cloud2Position += cloud2Speed;
    if (cloud2Position > 1000)
    {
        cloud2Position = 30;
    }

    // Update bird position for animation
    birdX += birdSpeed;
    if (birdX > 1000)
    {
        birdX = -100;
    }
    // Update bird position for animation in y direction with sine wave
    birdY = 700 + (50 * sin(birdX / 50));

    // Update boat position for animation
    boatPosition += boatSpeed;
    if (boatPosition > 1000)
    {
        boatPosition = -100; // Reset position for looping
    }

    // Update fish position for animation
    fishPosition -= fishSpeed;
    if (fishPosition < -100)
    {
        fishPosition = 800; // Reset position for looping
    }
    updateRain(); // Update rain positions

    glutPostRedisplay();          // Redraw the scene
    glutTimerFunc(16, update, 0); // Call update function again after 16 ms
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // 27 is the Escape key
        exit(0);
        break;
    case 'd': // 'd' key to toggle day/night mode
        isDay = !isDay;
        glutPostRedisplay();
        break;
    case 'r': // 'r' key to toggle rain
        isRaining = !isRaining;
        glutPostRedisplay();
        break;
    }
}

void key(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if (frenceDoor > -50.0)
        {
            frenceDoor -= 1;
        }

        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        if (frenceDoor < 0.5)
        {
            frenceDoor += 1;
        }
        glutPostRedisplay();
        break;
    }
}

// ------------------------------------INIT-------------------------------------------------
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white
    gluOrtho2D(0, 1000, 0, 800);          // Set the orthographic projection to match the new coordinate system
}

// ------------------------------------MAIN-------------------------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(1900 - 1000, 1000 - 800);
    glutInitWindowSize(1000, 800); // Set the window size to 1000 x 800
    glutCreateWindow("Village Scenery");
    init();
    initRain(); // Initialize rain
    glutDisplayFunc(display);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(key);
    glutTimerFunc(0, update, 0); // Start the animation loop
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
