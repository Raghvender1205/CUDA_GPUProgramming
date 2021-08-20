import sys
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

def display():
	# Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	
	# render stuff in here
	# If will go to an off-screen frame buffer
	
	# Copy offscreen buffer to the screen
	glutSwapBuffers()

glutInit(sys.argv)

# Create a double-buffer RGBA window.   (Single-buffering is possible.
# So is creating an index-mode window.)
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)

# Create a window, setting its title
glutCreateWindow('interactive')

# Set the display callback.  You can set other callbacks for keyboard and
# mouse events.
glutDisplayFunc(display)

# Run the GLUT main loop until the user closes the window.
glutMainLoop()
