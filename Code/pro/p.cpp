//*
// *  Animation of the Solor System 
// *  Project2.cpp
// * 
// * -------------------------------------------------------------
// * -------------------------------------------------------------
// */
#include "C:\Users\student\Desktop\GLUT 3.7 for .NET/glut.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Bitmap.h"


//#include "Bitmap.h"

#define M_PI    3.1415926
#define M_2PI   2 * M_PI
#define M_PI_2  M_PI / 2

#define SOLAR_YEAR	     200	// Rotation Period of the solar system
#define MERCURY_YEAR     360	// Rotation Period of the Moon
#define EARTH_YEAR 	     4320   // Rotation Period of the Earth
#define VENUS_YEAR 	     2880   // Rotation Period of the Venus
#define MARS_YEAR 	     8640   // Rotation Period of the Mars
#define MOON_YEAR 	     360	// Rotation Period of the Moon
#define JUPITER_YEAR     40000	// Rotation Period of the Jupiter
#define SATURN_YEAR      120000 // Rotation Period of the Saturn
#define URANUS_YEAR      360000 // Rotation Period of the Uranus
#define NEPTUNE_YEAR     720000 // Rotation Period of the Neptune
#define PLUTO_YEAR 	     360	// Rotation Period of the Pluto

#define MERCURY_DAY      66		// Self-rotation Period of the Mercury
#define EARTH_DAY 	     11		// Self-rotation Period of the Earth	
#define VENUS_DAY 	     66		// Self-rotation Period of the Venus	
#define MARS_DAY 	     11 	// Self-rotation Period of the Mars	
#define JUPITER_DAY      4		// Self-rotation Period of the Jupiter
#define SATURN_DAY 	     5	    // Self-rotation Period of the Saturn	
#define URANUS_DAY 	     8	    // Self-rotation Period of the Uranus
#define NEPTUNE_DAY      8		// Self-rotation Period of the Neptune
#define PLUTO_DAY 	     66	    // Self-rotation Period of the Pluto

#define	SUN_RADIUS		 0.10	// Radius of the Sun
#define	MERCURY_RADIUS   0.06	// Radius of the Mecury
#define	VENUS_RADIUS	 0.25	// Radius of the Venus
#define	EARTH_RADIUS	 0.25	// Radius of the Earth
#define	MOON_RADIUS		 0.08	// Radius of the Moon
#define	MARS_RADIUS		 0.15	// Radius of the Mars
#define	JUPITER_RADIUS	 0.75	// Radius of the Jupiter
#define	SATURN_RADIUS	 0.65	// Radius of the Saturn
#define	URANUS_RADIUS	 0.40	// Radius of the Uranus
#define	NEPTUNE_RADIUS	 0.30	// Radius of the Neptune
#define	PLUTO_RADIUS	 0.04	// Radius of the Pluto

#define	MERCURY_ORBIT	 0.25	// Orbit Radius of the Venus
#define	VENUS_ORBIT		 0.75	// Orbit Radius of the Venus
#define	EARTH_ORBIT		 1.75	// Orbit Radius of the Earth
#define	MOON_ORBIT		 0.35	// Orbit Radius of the Moon
#define	MARS_ORBIT		 2.5	// Orbit Radius of the Mars
#define	JUPITER_ORBIT	 3.8	// Orbit Radius of the Jupiter
#define	SATURN_ORBIT	 6.5	// Orbit Radius of the Saturn
#define	URANUS_ORBIT	 8.5	// Orbit Radius of the Uranus
#define	NEPTUNE_ORBIT	 10.5	// Orbit Radius of the Neptune
#define	PLUTO_ORBIT		 12.0	// Orbit Radius of the Pluto

#define PRECESSION_YEAR  20 	// Self-rotation Period of the Earth Precession
#define PRECESSION_ANGLE 30
#define MAX_STAR 1000

#define TRUE  1
#define FALSE 0


int ro1 = 0,
    ro2 = 0,
    ro3 = 0,
    ro = 0;
double re=0;

void init_plants();
void fordo();
void draw_venus();
void draw_earth();
void draw_mars();
void init_plants();
void init_texture();
void doTexture();


typedef struct tmp_star {
   float x;
   float y;
   float z;
} Star;

Star star[MAX_STAR];
int stop_g = 1;
int stop_t = 1;


GLUquadricObj *sun, *mercury, *venus, *earth, *moon, *mars;
GLUquadricObj *jupiter, *saturn, *uranus, *neptune, *pluto;

GLubyte *sun_image,  *venus_image, *earth_image, *moon_image, *mars_image;
static GLuint tex_sun, tex_venus, tex_earth, tex_moon, tex_mars;
static int sun_teximageWidth, sun_teximageHeight, venus_teximageWidth, venus_teximageHeight, earth_teximageWidth, earth_teximageHeight,
			moon_teximageWidth, moon_teximageHeight, mars_teximageWidth, mars_teximageHeight;

float angle_global = 0;
float year_mercury, year_earth = 0, year_venus = 0, year_mars = 0, year_moon = 0;
float year_jupiter = 0, year_saturn = 0, year_uranus = 0, year_neptune = 0, year_pluto = 0;
float day_mercury = 0, day_earth = 0, day_venus = 0, day_mars = 0;
float day_jupiter = 0, day_saturn = 0, day_uranus = 0, day_neptune = 0, day_pluto = 0;

float precession = 0;

GLfloat Rotate_x = 0, Rotate_y = 60;
GLfloat Translate_x = 0.0, Translate_y = 0.0;
GLfloat Zoom = 0.0, Scale = 1.0;
GLfloat dx, dy, old_x = 0.0, old_y = 0.0;
GLfloat old_dx = 0, old_dy = 0;
GLfloat dr, theta = 0;
GLfloat new_x, new_y;
int G_mousedown_L = FALSE, G_mousedown_R = FALSE;

float winwidth, winheight;
int _ScreenMode = 3;



void TransformXY(int ix, int iy, float *x, float *y)
{
   *x = 2.0 * (float) ix / (float) winwidth - 1.0;
   *y = -2.0 * (float) iy / (float) winheight + 1.0;
}

 //Capture the BMP file
GLubyte* TextureLoadBitmap(char *filename, int *w, int *h) // I - Bitmap file to load
{
   BITMAPINFO *info; // Bitmap information
   void		  *bits; // Bitmap pixel bits
   GLubyte	  *rgb;	 // Bitmap RGB pixels
   GLubyte    err = '0';

   // Try to load the bitmap and converting it to RGB...
   bits = LoadDIBitmap(filename, &info);
   if (bits == NULL) 
	  return (NULL);
   
   rgb = ConvertRGB(info, bits);
   
   if (rgb == NULL) {
      free(info);
      free(bits);
   };

   printf("%s: %d %d\n", filename, info->bmiHeader.biWidth, info->bmiHeader.biHeight);
   printf("read %s successfully\n", filename);
   *w = info->bmiHeader.biWidth;
   *h = info->bmiHeader.biHeight;

   // Free the bitmap and RGB images, then return 0 (no errors).
   free(info);
   free(bits);
   
   return (rgb);
}

 //Mouse callback for handling mouse click
void Mouse(int button, int state, int ix, int iy)
{
   float x, y;

   // Transform mouse position from screen coordinate to world 2D coordinate
   TransformXY(ix, iy, &x, &y);

   // Save old cursor location when mouse is clicked
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
	  G_mousedown_L = TRUE;
	  old_x = x;
	  old_y = y;
   }
   else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
	  G_mousedown_L = FALSE;
	  old_dx = dx;
	  old_dy = dy;
	  dx = 0;
	  dy = 0;
   }
   if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
	  G_mousedown_R = TRUE;
	  old_x = x;
	  old_y = y;
   }
   else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
	  G_mousedown_R = FALSE;
   }
   glutPostRedisplay();
}

void Drag(int ix, int iy)
{  
   // Transform mouse position from screen coordinate to world 2D coordinate
   TransformXY(ix, iy, &new_x, &new_y);

   // Increment rotation angle for right mouse dragging
   if (G_mousedown_L) {
	  Rotate_y += (new_y - old_y) * 30;
	  old_x = new_x;
	  old_y = new_y;
   }

   // Increment scale for left mouse dragging
   if (G_mousedown_R) {
	  Scale += new_y - old_y;
	  if (Scale < 0.2) Scale = (float) 0.2;
	  if (Scale > 3.0) Scale = (float) 3.0;
	  old_x = new_x;
	  old_y = new_y;
   }
   glutPostRedisplay();
}

// Keyboard callback for handling keyboard event
void Keyboard(unsigned char key, int x, int y)
{

	switch(key){
	case 'r':
	case 'R':
		day_venus=0;
		day_earth=0;
		day_mars=0;
		year_venus=0;
		year_earth=0;
		year_moon=0;
		year_mars=0;
		break;
	case 'g':
	case 'G':
		stop_g++;
		stop_g = stop_g%2;
		break;
	case 't':
	case 'T':
		stop_t++;
		stop_t = stop_t%2;
		break;
	case 27:
	case 'q':
	case 'Q':
		exit(0);
	}
   // Add code here to control the animation interactively
}

// Special key-stroke callback function
void Special(int key, int x, int y)
{
   if (key == GLUT_KEY_F1) {
	  _ScreenMode ++;
	  if (_ScreenMode > 3) _ScreenMode = 0;
	  if (_ScreenMode == 0)
		 glutReshapeWindow(350, 200);
	  else if(_ScreenMode == 1)
		 glutReshapeWindow(700, 400);
	  else if(_ScreenMode == 2)
	 	 glutReshapeWindow(900, 600);
	  else if(_ScreenMode == 3)
	 	 glutReshapeWindow(150, 75);
   }
}

// Reshape callback
void Reshape(int w, int h)
{
   winwidth  = w;
   winheight = h;
   glViewport(0, 0, w, h);      // Viewport transformation
   glMatrixMode(GL_PROJECTION);	// Projection transformation
   glLoadIdentity(); 
   gluPerspective(50, (GLfloat) w / (GLfloat) h, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
   glutPostRedisplay();
}

// Display callback
void Display(void)
{
   // Clear the window color before drawing is performed
   glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

   // Add code here to
   // 1. Transform the planets and draw them, 
   // 2. Draw the star-sphere by points, 
   // 3. Set correctly material properties of the Sun & planets.
   // You may use glTranslate*(), glRotate*(), glLoadIdentity(), glPushMatrix(), 
   // glPopMatrix(), glMaterial*(), glBegin(), gluSphere(), etc.
   //
   // 4. Provide texture mapping for each planets except the Sun
   // Learn to use glTexImage2D().
  
    glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glLoadIdentity();
    gluLookAt(0.0,0.0,5,     0,0,0,      0,1,0);
    glColor3f(1.0, 1.0, 1.0);
 
	glPushMatrix();
    glRotatef(year_mars*2,0.0,1,0.0);
	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    int i=0;
    glVertex3f(0.11,0,-10);
        for(i=0;i<MAX_STAR/2;i++){
			
				glVertex3f(star[i].x+re,star[i].y+re,star[i].z);
			
				glVertex3f(star[i].x-re,star[i].y-re,star[i].z);
//            glVertex3f(star[i].x-0.2,star[i].y,star[i].z-0.1);
//            glVertex3f(star[i].x,star[i].y,star[i].z-0.2);
//            glVertex3f(star[i].x,star[i].y+0.3,star[i].z+0.1);
//            glVertex3f(star[i].x+0.2,star[i].y,star[i].z+0.2);
            //printf("venus is %f and earth is %f  zheshi di%d ci\n",star[i].x,star[i].y,i)
    }
    glEnd();
    glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tex_sun);
    gluSphere(sun, SUN_RADIUS, 50, 50);
    glPopMatrix();

    //for venus
    draw_venus();
    
    //for earth
    draw_earth();
    
    //for mars
    draw_mars();   	
  
	fordo();
   glutSwapBuffers();
}

void draw_venus(){
    glPushMatrix();
    glRotatef(year_venus,0.0,1,0.0);
    glTranslatef(VENUS_ORBIT, 0, 0);
    glRotatef(day_venus,0.0,1,0.0);
	glBindTexture(GL_TEXTURE_2D, tex_venus);
	glRotatef(90,1.0,0,0.0);
    gluSphere(venus, VENUS_RADIUS, 50, 50);
    glPopMatrix();
}

void draw_earth(){
    
    glPushMatrix();
    //for earth's axis
    glRotatef(year_earth,0.0,1,0.0);
    
    glPushMatrix();
    glTranslatef(EARTH_ORBIT, 0, 0);
    
    //moon
    glRotatef(-day_earth,0.0,1,0.0);
    glRotatef(PRECESSION_ANGLE, 0.0,0,1.0);
    glPushMatrix();
    glRotatef(year_moon,0.0,1,0.0);
    glTranslatef(MOON_ORBIT, 0, 0);
	glBindTexture(GL_TEXTURE_2D, tex_moon);
	glRotatef(90,1.0,0,0.0);
    gluSphere(moon, MOON_RADIUS, 50, 50);
    glPopMatrix();
    
    glBegin(GL_LINES);
    glVertex3f(0,-0.5,0);
    glVertex3f(0,0.5,0);
    glEnd();
	glBindTexture(GL_TEXTURE_2D, tex_earth);
	glRotatef(90,1.0,0,0.0);
    gluSphere(earth, EARTH_RADIUS, 50, 50);
    glPopMatrix();

    glPopMatrix();

}

void draw_mars(){

    glPushMatrix();
    glRotatef(year_mars,0.0,1,0.0);
    glTranslatef(MARS_ORBIT, 0, 0);
    glRotatef(day_mars,0.0,1,0.0);
	glBindTexture(GL_TEXTURE_2D, tex_mars);
	glRotatef(90,1.0,0,0.0);
    gluSphere(mars, MARS_RADIUS, 50, 50);

    glPopMatrix();
}


void fordo(){
	if(stop_t){
		day_venus += 360.0/VENUS_DAY/120.0;	if(day_venus>=360.0)   day_venus = 360 % (int)day_venus;
		day_earth += 360.0/EARTH_DAY/120.0;	if(day_earth>=360.0)   {day_earth = 360 % (int)day_earth; ro=ro+1; re =rand()%100; re=re/100;}
		day_mars +=360.0/MARS_DAY/120.0;		if(day_mars>=360.0)   day_mars = 360 % (int)day_mars;
		year_moon += 360.0/MOON_YEAR/6;			if(year_moon>=360.0)    year_moon = 360 % (int)year_moon;
	
    
	}
   if(stop_g){
		
    year_earth += 360.0/EARTH_YEAR/6;			if(year_earth>=360.0)  year_earth = 360 % (int)year_earth;
   	
    
    year_mars += 360.0/MARS_YEAR/6;			 if(year_mars>=360.0)  year_mars = 360 % (int)year_mars;
    year_venus+= 360.0/VENUS_YEAR/6;	if(year_venus>=360.0)  year_venus = 360 % (int)year_venus;

   }

    glutPostRedisplay();
}

void init_start(){
    float p;
    int i;
    for(i=0;i<MAX_STAR/2;i++){
        //srand((unsigned)time(NULL));
        p= rand()%24-12+rand()/float(RAND_MAX);
        star[i].x = p;

        p= rand()%12-6+rand()/float(RAND_MAX);
        star[i].y = p;
        
        p= rand()%40-20+rand()/float(RAND_MAX);
        star[i].z = p;
    }
}


void init()
{
   int i;
   float theta, phi, r = 10;

   // Clear screen color
   glEnable(GL_COLOR_MATERIAL);
   glClearColor(0, 0, 0, 0);
   glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
    
   // Texture mapping setting for Microsoft's OpenGL implementation
   glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
   glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
   glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
   glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);

   // Texture mapping parameters for filter and repeatance
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   // Add code here to 
   // 1. Initialize light-source settings, 
   // 2. Read bitmap images, 
   // 3. Initialize different GLU spheres and the position of the stars.
   // Use glLight*(), TextureLoadBitmap(), gluNewQuadric(), etc.
    
    //initialize
	init_start();
    init_plants();
	init_texture();
	doTexture();

}

void doTexture(){
//venus
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &tex_venus);
	glBindTexture(GL_TEXTURE_2D, tex_venus);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	// Read the texture image and store the RGB byte to teximage
	venus_image = TextureLoadBitmap("venus.bmp", &venus_teximageWidth, &venus_teximageHeight);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, venus_teximageWidth, 
		venus_teximageHeight,  GL_RGB, GL_UNSIGNED_BYTE, venus_image);

//earth
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &tex_earth);
	glBindTexture(GL_TEXTURE_2D, tex_earth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	// Read the texture image and store the RGB byte to teximage
	earth_image = TextureLoadBitmap("earth.bmp", &earth_teximageWidth, &earth_teximageHeight);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, earth_teximageWidth, 
		earth_teximageHeight,  GL_RGB, GL_UNSIGNED_BYTE, earth_image);

//moon
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &tex_moon);
	glBindTexture(GL_TEXTURE_2D, tex_moon);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	// Read the texture image and store the RGB byte to teximage
	moon_image = TextureLoadBitmap("moon.bmp", &moon_teximageWidth, &moon_teximageHeight);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, moon_teximageWidth, 
		moon_teximageHeight,  GL_RGB, GL_UNSIGNED_BYTE, moon_image);


//mars
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &tex_mars);
	glBindTexture(GL_TEXTURE_2D, tex_mars);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	// Read the texture image and store the RGB byte to teximage
	mars_image = TextureLoadBitmap("mars.bmp", &mars_teximageWidth, &mars_teximageHeight);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, mars_teximageWidth, 
		mars_teximageHeight,  GL_RGB, GL_UNSIGNED_BYTE, mars_image);


}

void init_texture(){
	gluQuadricTexture(sun,GL_TRUE);
	gluQuadricTexture(venus,GL_TRUE);
	gluQuadricTexture(earth,GL_TRUE);
	gluQuadricTexture(moon,GL_TRUE);
	gluQuadricTexture(mars,GL_TRUE);
}

void init_plants(){
    sun = gluNewQuadric();
    gluQuadricDrawStyle(sun,GLU_FILL);
    
    venus = gluNewQuadric();
    gluQuadricDrawStyle(venus, GLU_FILL);
    
    earth = gluNewQuadric();
    gluQuadricDrawStyle(earth, GLU_FILL);
    
    moon = gluNewQuadric();
    gluQuadricDrawStyle(moon, GLU_FILL);
    
    mars = gluNewQuadric();
    gluQuadricDrawStyle(mars, GLU_FILL);

}

void Idle(void)
{
   // Add code here to 
   // 1. Update the rotation angles, 
   // 2. Force the system to display after the event
}

int main(int argc, char** argv)
{
   // Initialization of GLUT Library
   glutInitWindowSize(800, 450);
   glutInitWindowPosition(100, 100);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   // Create a window with title specified
   glutCreateWindow("Project2: Solor System Animation");

   // Register different callback functions for GLUT to response 
   // with different events, e.g. window sizing, mouse click or
   // keyboard stroke
   glutReshapeFunc(Reshape);
   glutDisplayFunc(Display);
   glutKeyboardFunc(Keyboard);
   glutSpecialFunc(Special);
   glutIdleFunc(Idle);
   glutMouseFunc(Mouse);
   glutMotionFunc(Drag);
   init();	// not GLUT call, initialize several parameters
	
   // Enter the GLUT event processing loop which never returns.
   // It will call different registered callback according to different events.
   glutMainLoop();
}



