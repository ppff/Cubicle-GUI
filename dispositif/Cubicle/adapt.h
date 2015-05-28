#ifndef ADAPT
#define ADAPT
#ifdef CUBICLE_ON_LINUX
#include <GL/glut.h>

#endif

#ifdef CUBICLE_ON_MAC



#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#endif

#ifdef CUBICLE_ON_WINDOWS


#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>

#endif
#endif // ADAPT

