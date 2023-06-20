# OpenGLDemo
Simple rendering and audio with OpenGL, C++, GLFW and GLEW

How to run:
Update the m_appFilePath in the Scene.h file.

If GLEW and GLFW can't be found, go to Project -> OpenGLDemo properties
In the properties, make sure that the library directories are correct in the following places:
VC++ Directiories -> Library Directiories
C/C++ -> General -> Additional Include Directiories
Linker -> Input -> Additional Dependencies
Also make sure that you are setting these properties for the right configuration (Debug or Release, Platform x64).

!!! Also the audio is quite loud in the application, so I recommend reducing your device's volume drastically.
