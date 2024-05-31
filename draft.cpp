#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <time.h>

/*
About the project:
This project is a simple 2D animation of a village scene. The scene includes a river, trees, houses, a boat, a well, and a tubewell. The scene also includes a day/night mode that can be toggled using the 'd' key. During the night, the scene also includes a moon and rain. The boat moves from left to right, and the fish move from right to left. The clouds also move from left to right. The scene is drawn using basic shapes such as rectangles, polygons, and circles. The scene is animated using the OpenGL library in C++.
This project is created by:
- Zaman Sheikh(github.com/zamansheikh) | Md. Shamsuzzaman | 211-15-4031
- Nafiz | Mohaiminul Islam Nafiz | 211-15-4041

*/

// ------------------------------------CONTROL-------------------------------------------------
int i;
double dxr = 15, dyr = 15;
float cloud1Position = 150, cloud1Size = 15, cloud1Speed = 0.01;
float cloud2Position = 20, cloud2Size = 15, cloud2Speed = 0.01;
float boatPosition = -110, boatSpeed = 0.2;
float treeLeafSizeXr = 22, treeLeafSizeYr = 15;
float tree2LeafSizeXr = 17, tree2LeafSizeYr = 15;
float fishPosition = 100, fishSpeed = 0.2;
// Day/Night mode control
bool isDay = true;

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

    glVertex2i(400 - x, 350);
    glVertex2i(400 - x, 290);
    glVertex2i(397 - x, 290);
    glVertex2i(397 - x, 350);
    glVertex2i(400 - x, 350);

    glEnd();
}

void fenceAll()
{
    int x = 0;
    for (int i = 0; i < 39; i++)
    {
        fence(x);
        x += 10;
    }
}

// ------------------------------------RAIN-------------------------------------------------
// Structure to represent a rain drop
struct RainDrop
{
    float x;
    float y;
    float speed;
};

const int MAX_RAINDROPS = 200; // Maximum number of raindrops
RainDrop rain[MAX_RAINDROPS];

// Initialize rain drops with random positions and speeds
void initRain()
{
    srand(time(0)); // Seed the random number generator
    for (int i = 0; i < MAX_RAINDROPS; i++)
    {
        rain[i].x = rand() % 420;                 // Random x position within the window width
        rain[i].y = rand() % 530 + 530;           // Random y position starting above the window height
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
            rain[i].x = rand() % 420;
            rain[i].y = 530;
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

void house1()
{
    // --------------------------------------- HOUSE one----------------------------
    glBegin(GL_POLYGON);   // first Part
    glColor3ub(128, 0, 0); // gray
    glVertex2i(152, 335);
    glVertex2i(135, 365);
    glVertex2i(95, 370); // point
    glVertex2i(120, 320);
    glVertex2i(160, 320);
    glVertex2i(152, 335);
    glEnd();

    glBegin(GL_POLYGON);   // second Part
    glColor3ub(120, 0, 0); // maroon
    glVertex2i(95, 370);
    glVertex2i(80, 320);
    glVertex2i(90, 320);  // point
    glVertex2i(102, 357); // point
    glVertex2i(95, 370);
    glEnd();

    glBegin(GL_POLYGON);     // third Part
    glColor3ub(46, 139, 87); //
    glVertex2i(102, 357);
    glVertex2i(90, 320);
    glVertex2i(90, 265);
    glVertex2i(120, 260); // point
    glVertex2i(120, 320);
    glVertex2i(102, 357);
    glEnd();

    glBegin(GL_POLYGON);       // fourth Part
    glColor3ub(143, 188, 143); //
    glVertex2i(120, 260);
    glVertex2i(154, 265);
    glVertex2i(154, 320);
    glVertex2i(120, 320);
    glEnd();

    glColor3ub(120, 0, 0); // maroon // Door One
    glRecti(135, 300, 145, 260);
    glColor3ub(120, 0, 0); // maroon // Door One
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
void house2()
{
    //-------------------------------------------  HOUSE  two  -------------------------------------------------
    glBegin(GL_POLYGON); // First part

    glColor3ub(25, 25, 112); // midnight blue
    glVertex2i(160, 360);
    glVertex2i(210, 369);
    glVertex2i(198, 308);
    glVertex2i(145, 309);
    glVertex2i(160, 360);
    glEnd();

    glBegin(GL_POLYGON);      // Second Part
    glColor3ub(70, 130, 180); // midnight blue
    glVertex2i(150, 310);
    glVertex2i(150, 250);
    glVertex2i(200, 245);
    glVertex2i(200, 315);
    glEnd();

    //---------------------------------------Door------------------------------------------
    glColor3ub(25, 25, 112); // midnight blue
    glRecti(165, 290, 180, 247);

    //--------------------------------------------------------------------------
    glBegin(GL_POLYGON);      // Third part
    glColor3ub(95, 158, 160); // midnight blue
    glVertex2i(200, 245);
    glVertex2i(228, 255);
    glVertex2i(228, 320);
    glVertex2i(210, 368);
    glVertex2i(200, 320);
    glVertex2i(200, 245);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(25, 25, 112); // midnight blue
    glVertex2i(209, 370);
    glVertex2i(230, 320);
    glVertex2i(227, 310);
    glVertex2i(206, 360);
    glVertex2i(209, 370);

    glEnd();

    glBegin(GL_POLYGON);     // door
    glColor3ub(25, 25, 112); // midnight blue
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

//-----------------------------------field------------------------------
void field()
{
    //-----------------------------------field------------------------------
    glBegin(GL_POLYGON);

    // Set the color to green
    glColor3f(0, 0.3921, 0);

    // Update the coordinates with the offsets
    glVertex2i(10, 320);
    glVertex2i(110, 380);
    glVertex2i(210, 320);
    glVertex2i(260, 290);
    glVertex2i(310, 400);
    glVertex2i(410, 320);

    // Change color to gold
    glColor3ub(255, 215, 0);

    glVertex2i(410, 20);
    glVertex2i(10, 20);
    glVertex2i(10, 320);

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

void river()
{
    //------------------------------------------RIVER--------------------------------------------------
    glBegin(GL_POLYGON);
    glColor3ub(30, 144, 255);
    glVertex2i(10, 170);
    glVertex2i(410, 190);
    glColor3ub(0, 0, 128);
    glVertex2i(410, 20);
    glVertex2i(10, 20);
    glVertex2i(10, 170);
    glEnd();
    glBegin(GL_POLYGON); // border
    glColor3ub(128, 128, 0);
    glVertex2i(10, 175);
    glVertex2i(410, 195);
    glVertex2i(410, 190);
    glVertex2i(10, 170);
    glVertex2i(10, 175);
    glEnd();
}

void cloud1day()
{
    //-------------------------------------------CLOUD-------------------------------------------------
    glPushMatrix();
    glColor3ub(220, 220, 220);
    glTranslatef(cloud1Position, 0, 0);
    circle(15, 15, 210, 470);
    circle(15, 15, 225, 465);
    circle(15, 15, 220, 460);
    circle(15, 15, 208, 463);

    circle(15, 15, 130, 470);
    circle(15, 15, 115, 465);
    circle(15, 15, 120, 460);
    circle(15, 15, 120, 463);
    circle(15, 15, 135, 463);

    glPopMatrix();
}

void cloud2day()
{
    //-------------------------------------------CLOUD-------------------------------------------------
    glPushMatrix();
    glTranslatef(cloud1Position, 0, 0);
    glColor3ub(211, 211, 211);
    circle(15, 15, 45, 480);
    circle(15, 15, 25, 465);
    circle(15, 15, 30, 460);
    circle(15, 15, 58, 463);
    glPopMatrix();
}

void cloud1night()
{
    //-------------------------------------------CLOUD-------------------------------------------------
    glPushMatrix();
    glTranslatef(cloud1Position, 0, 0);
    glColor3f(0.529, 0.529, 0.506);
    circle(15, 15, 210, 470);
    circle(15, 15, 225, 465);
    circle(15, 15, 220, 460);
    circle(15, 15, 208, 463);
    circle(15, 15, 130, 470);
    circle(15, 15, 115, 465);
    circle(15, 15, 120, 460);
    circle(15, 15, 120, 463);
    circle(15, 15, 135, 463);
    glPopMatrix();
}

void cloud2night()
{
    //-------------------------------------------CLOUD-------------------------------------------------
    glPushMatrix();
    glTranslatef(cloud1Position, 0, 0);
    glColor3f(0.529, 0.529, 0.506);
    circle(15, 15, 45, 480);
    circle(15, 15, 25, 465);
    circle(15, 15, 30, 460);
    circle(15, 15, 58, 463);
    glPopMatrix();
}

//-------------------------------------Boat------------------------
void boat()
{
    //-------------------------------------------BOAT-------------------------------------------------
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glTranslatef(boatPosition, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(30, 150);
    glVertex2i(45, 120);
    glVertex2i(60, 100);
    glVertex2i(60, 120);
    glVertex2i(30, 150);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(60, 120);
    glVertex2i(60, 100);
    glVertex2i(90, 95);
    glVertex2i(120, 100);
    glVertex2i(125, 120);
    glVertex2i(60, 120);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(125, 120);
    glVertex2i(120, 100);
    glVertex2i(135, 115);
    glVertex2i(150, 150);
    glVertex2i(125, 120);
    glEnd();
    //--------------------------BOAT FLAG----------------------------
    glBegin(GL_POLYGON);
    glColor3ub(173, 216, 230);
    glVertex2i(153, 180);
    glVertex2i(160, 210);
    glVertex2i(161, 230);
    glVertex2i(160, 250);
    glVertex2i(155, 265);
    glVertex2i(147, 277);
    glVertex2i(137, 288); // end
    glVertex2i(105, 265);
    glVertex2i(160, 210);

    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(173, 216, 230);

    glVertex2i(142, 150);
    glVertex2i(153, 180);
    glVertex2i(125, 230);
    glVertex2i(142, 150);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(173, 216, 230);
    glVertex2i(125, 120);
    glVertex2i(142, 150);
    glVertex2i(130, 210);
    glVertex2i(125, 120);
    glEnd();

    glColor3ub(139, 69, 19);
    glRecti(122, 300, 124, 120); // Boat stand
    glBegin(GL_POLYGON);
    glColor3f(0.55, 0.27, 0.0745); // wood color
    glVertex2i(125, 120);
    glVertex2i(123, 140);
    glVertex2i(117, 158);
    glVertex2i(113, 165);
    glVertex2i(105, 170);
    glVertex2i(90, 172);
    glVertex2i(90, 120);
    glVertex2i(125, 120);
    glEnd();

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.55, 0.27, 0.0745); // wood color
    glVertex2i(60, 120);
    glVertex2i(62, 140);
    glVertex2i(68, 158);
    glVertex2i(72, 165);
    glVertex2i(80, 170);
    glVertex2i(95, 172);
    glVertex2i(95, 120);
    glVertex2i(60, 120);

    glEnd();

    //--------------------------BOAT LINE----------------------------
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex2i(68, 158);
    glVertex2i(137, 288);
    glVertex2i(137, 283);

    glVertex2i(68, 158);
    glVertex2i(105, 265);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex2i(62, 140);
    glVertex2i(123, 140);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex2i(68, 158);
    glVertex2i(117, 158);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex2i(95, 172);
    glVertex2i(95, 120);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex2i(80, 170);
    glVertex2i(80, 120);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex2i(110, 168);
    glVertex2i(110, 120);
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
    fish(120, 40, 0.5);
    fish(110, 50, 0.4);
    fish(100, 40, 0.3);
    fish(90, 50, 0.6);
    glPopMatrix();
}

// -------------------------------------SUN------------------------
void sun()
{
    glColor3ub(255, 215, 0);
    circle(17, 17, 300, 470);
}

void moon()
{
    glColor3ub(255, 255, 255);
    circle(17, 17, 300, 470);
    glColor3f(0.0f, 0.0f, 0.0f);
    circle(17, 17, 310, 475);
}

void daySky()
{
    glColor3f(0.529, 0.808, 0.980); // light blue
    glRecti(10, 520, 410, 320);
}

void nightSky()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glRecti(10, 520, 410, 320);
}

void canvas()
{
    glColor3ub(255, 255, 255); // border
    glRecti(0, 530, 10, 10);
    glRecti(410, 530, 420, 10);
}
void well()
{
    /// well
    glPushMatrix();
    glTranslatef(-60, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(178, 34, 34);
    glVertex2f(153, 240);
    glVertex2f(153, 206.5);
    glVertex2f(144.5, 202.5);
    glVertex2f(136, 199.5);
    glVertex2f(119, 199.5);
    glVertex2f(110.5, 202.5);
    glVertex2f(102, 206.5);
    glVertex2f(102, 240);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 154, 214);
    glVertex2f(153, 240);
    glVertex2f(144.5, 236.25);
    glVertex2f(136, 235.4);
    glVertex2f(119, 235.4);
    glVertex2f(110.5, 236.25);
    glVertex2f(102, 240);
    glVertex2f(110.5, 243.9);
    glVertex2f(119, 244.75);
    glVertex2f(136, 244.75);
    glVertex2f(144.5, 243.9);
    glEnd();

    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3ub(204, 51, 0);
    glVertex2f(153, 240);
    glVertex2f(144.5, 243.9);
    glVertex2f(144.5, 243.9);
    glVertex2f(136, 244.75);
    glVertex2f(136, 244.75);
    glVertex2f(119, 244.75);
    glVertex2f(119, 244.75);
    glVertex2f(110.5, 243.9);
    glVertex2f(110.5, 243.9);
    glVertex2f(102, 240);
    glEnd();

    /// bucket
    glBegin(GL_POLYGON);
    glColor3ub(194, 194, 163);
    glVertex2f(159.8, 213.3);
    glVertex2f(156.4, 201.4);
    glVertex2f(147.9, 201.4);
    glVertex2f(144.5, 213.3);
    glVertex2f(147.9, 215);
    glVertex2f(156.4, 215);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 154, 214);
    glVertex2f(158.95, 213.3);
    glVertex2f(156.06, 211.6);
    glVertex2f(149.26, 211.6);
    glVertex2f(145.35, 213.3);
    glVertex2f(149.26, 214.15);
    glVertex2f(156.4, 214.15);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(194, 194, 163);
    glVertex2f(159.80f, 213.30f);
    glVertex2f(156.40f, 220.10f);
    glVertex2f(156.40f, 220.10f);
    glVertex2f(153.00f, 220.10f);
    glVertex2f(153.00f, 220.10f);
    glVertex2f(147.90f, 220.10f);
    glVertex2f(147.90f, 220.10f);
    glVertex2f(144.50f, 213.30f);
    glEnd();

    /// rope
    glLineWidth(2.5);
    glBegin(GL_LINES);
    glColor3ub(230, 172, 0);
    glVertex2f(152.15f, 220.95f);
    glVertex2f(156.40f, 209.90f);
    glVertex2f(156.40f, 209.90f);
    glVertex2f(157.25f, 201.40f);
    glVertex2f(157.25f, 201.40f);
    glVertex2f(158.10f, 196.30f);
    glVertex2f(158.10f, 196.30f);
    glVertex2f(156.40f, 192.90f);
    glVertex2f(156.40f, 192.90f);
    glVertex2f(141.10f, 196.30f);
    glEnd();
    glPopMatrix();
}
// ------------------------------------DRAWALL-------------------------------------------------
void drawAll()
{
    // Update sky color based on day/night mode
    isDay ? daySky() : nightSky();
    isDay ? sun() : moon();

    field();
    fenceAll();
    glColor3ub(184, 134, 11);
    glRecti(10, 340, 410, 335);
    glRecti(10, 320, 410, 315);
    glRecti(10, 305, 410, 300);

    isDay ? cloud1day() : cloud1night();
    isDay ? cloud2day() : cloud2night();

    tree1();
    tree2();
    tubewell();
    house1();
    house2();
    river();
    well();
    boat();
    drawFishGroup();
    canvas();
}

// ------------------------------------DISPLAY-------------------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAll();
    if (!isDay) // Show rain only during night time
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
    if (cloud1Position > 410)
    {
        cloud1Position = 10;
    }

    cloud1Position += cloud1Speed;
    if (cloud1Position > 480)
    {
        cloud1Position = 30;
    }

    // Update boat position for animation
    boatPosition += boatSpeed;
    if (boatPosition > 480)
    {
        boatPosition = -100; // Reset position for looping
    }

    // Update fish position for animation
    fishPosition -= fishSpeed;
    if (fishPosition < -100)
    {
        fishPosition = 530; // Reset position for looping
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
    }
}

void key(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        // coditon here
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        // coditon here
        glutPostRedisplay();
        break;
    }
}

// ------------------------------------INIT-------------------------------------------------
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(0, 420, 0, 530);
}

// ------------------------------------MAIN-------------------------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1060, 840);
    glutCreateWindow("Village Scenery");
    init();
    initRain(); // Initialize rain
    glutDisplayFunc(display);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(key);
    glutTimerFunc(0, update, 0); // Start the animation loop
    glutMainLoop();
    return 0;
}
