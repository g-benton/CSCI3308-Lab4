#include <stdio.h>
#include <random>
#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// globals //
double yRotate=0;  //  Rotation angle
double xRotate=0;
// parameters for the lorenz attractor
double s, b, p;

double* lorenz(double current_coords[], double params[]);

/*
 * This function is called by GLUT to display the scene
 */
void display()
{	
	//set up stuff for lorenz attractor
	double init_coords[3] = {1,1,1};
	double *current_coords;
	int iteration_count = 50000;
	double params[3] = {s, b, p};
	
	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	// glClear(GL_COLOR_BUFFER_BIT);
	//  Reset transformations
	glLoadIdentity();
	glOrtho( -100, 100, -100, 100, -100, 100);
	//  Rotate around Y axis
	glRotatef(xRotate, 1, 0, 0);
	glRotatef(yRotate, 0, 1, 0);

	// axes are white
	glColor3f(1,1,1);
	// plot the axes
	glBegin(GL_LINE_STRIP);
	glVertex3f(0,0,0);
	glVertex3f(50,0,0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(0,0,0);
	glVertex3f(0,50,0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(0,0,0);
	glVertex3f(0,0,50);
	glEnd();


	// set up the first round of coordinates
	current_coords = lorenz(init_coords, params);
	glColor3f(0,0,1);
	glColor3f(((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)));
	glBegin(GL_LINE_STRIP);
	glVertex3f(current_coords[0],current_coords[1], current_coords[2]);
	for (int i = 0; i < iteration_count; ++i)
	{	
		current_coords = lorenz(current_coords, params);
		glVertex3f(current_coords[0],current_coords[1], current_coords[2]);
		// if (i % 100 == 0){
		// 	glColor3f(((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)));
		// }
		glColor3f((double) (i % 10000)/10000,(double)i/10000, 1 - (double)i/10000);

	}
	glEnd();


    // glBegin(GL_LINE_STRIP);
    // glVertex2f(-4.00, 0.00);
    // glVertex2f(-3.00, 2.00);
    // glVertex2f(-2.00, 0.00);
    // glVertex2f(-1.00, 2.00);
    // glVertex2f(0.0, 0.00);
    // glVertex2f(1.00, 2.00);
    // glVertex2f(2.00, 0.00);
    // glVertex2f(3.00, 2.00);
    // glVertex2f(4.00, 0.00);
    // glEnd();


   glFlush();
   glutSwapBuffers();
}

void special(int key,int x,int y)
{

   	if (key == GLUT_KEY_RIGHT)
      yRotate += 5;
   	else if (key == GLUT_KEY_LEFT)
      yRotate -= 5;
  	else if (key == GLUT_KEY_UP)
      xRotate += 5;
   	else if (key == GLUT_KEY_DOWN)
      xRotate -= 5;
 
   //  Request display update
   glutPostRedisplay();
}

void param_change(unsigned char key, int x, int y){
	// read in o and p keypresses
	if (key == 'q'){
		s -= 0.5;
	} else if (key == 'w'){
		s += 0.5;
	}
	if (key == 'a'){
		b -= 0.5;
	} else if (key == 's'){
		b += 0.5;
	}
	if (key == 'z'){
		p -= 0.5;
	} else if (key == 'x'){
		p += 0.5;
	}
	
   glutPostRedisplay();
}


int main(int argc,char* argv[])
{
	s = 10;
	b = 2.666;
	p = 28;
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered true color window with Z-buffer
   // glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(900,900);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   //  Create window
   glutCreateWindow("Greg Benton: Lorenz Attractor");
   //  Register display and key callbacks
   glutKeyboardFunc(param_change); // Tell GLUT to use the method "keyPressed" for key presses  
   glutDisplayFunc(display);
   glutSpecialFunc(special);
   //  Enable Z-buffer depth test
   glEnable(GL_DEPTH_TEST);
   //  Pass control to GLUT for events
   glutMainLoop();
   //  Return to OS
   return 0;
}


// The lorenz attractor equation

double* lorenz(double current_coords[], double params[]){
	// takes in the previous coordinates and the parameters
	double x, y, z;
	double s, b, r;
	double dt = 0.001;

	//set coords
	x = current_coords[0];
	y = current_coords[1];
	z = current_coords[2];

	// set parameters
	s = params[0];
	b = params[1];
	r = params[2];



	double dx = s*(y-x);
	double dy = x*(r-z)-y;
	double dz = x*y - b*z;
	x += dt*dx;
	y += dt*dy;
	z += dt*dz; 

	double* next_coords = new double[3];
	// double next_coords[3] = {x,y,z}
	next_coords[0] = x;
	next_coords[1] = y;
	next_coords[2] = z;
	// printf("%f\n", next_coords[1]);
	return next_coords;
}




// Done using Euler's method with a small time-step
// (I don't think this is a stiff ODE, so even though 
// Euler's is generally not very good it should be fine)






