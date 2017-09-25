# RRT-Pathfinding
A Rapidly-exploring Random Tree (RRT) algorithm visualized in C++ and OpenGL using FreeGLUT. This program visually 
shows how pathfinding using randomly generated coordinates can solve different mazes quickly but not in the most optimal way.<br><br><br>



--Windows | MSVC--<br>
This program comes with glut.h already, so including it into your MSVC include path won't be necessary, however, you will need
to make sure the working directory has glut32.dll in it otherwise you will receive a run-time error. In your program's properties
page make sure under "Linker >> Input >> Additional Dependancies" You have "opengl32.lib;glu32.lib;glut32.lib;%(AdditionalDependencies)"
as the set value. This will require you to make sure your MSVS library directory contains opengl32.lib, glu32.lib, and glut32.lib,
which if I remember correctly are found at the freeglut homepage, glut32.lib is included with the program, for some reason..<br><br>

--Windows | MinGW--<br>
Same as the MSVC build, only thing to note is to make sure your PATH variable contains your MinGW 'bin' directory (for access
to gcc/g++/etc..), then compiling just requires the following command string<br>
"g++ -o RRT *.cpp -lopengl32 -lglu32 -lglut32"<br><br>

--Linux--<br>
For Linux OS's, make sure you have FreeGLUT and gcc/g++ installed and compile using the following line<br>
"g++ -o RRT *.cpp -lopengl32 -lglu32 -lglut32"<br><br><br><br>
