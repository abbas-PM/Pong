# Pong
Created simple pong along with another game mode using C++ and SDL2. 

# Screenshots
![image](https://github.com/abbas-PM/Pong/assets/116516812/49292361-4782-4b62-b0fc-a38f6a4aac45) ![image](https://github.com/abbas-PM/Pong/assets/116516812/679a7edf-c069-489e-87c3-04dc9e79dff7) ![image](https://github.com/abbas-PM/Pong/assets/116516812/8f92a66b-a38a-4579-b046-954f4b9c7c42)


# Background
Simple pong in which the player who scores ten points wins, along with another game mode where both players have to work together to make sure the ball does not hit any side of the 
wall ten times in one minute. Player one controls with Q and Z, player two controls with UP and DOWN.

# Compiling
To compile on windows, install Mingw64, SDL2, and SDL2_TTF. Place all the C header files from SDL2 and SDL2_TTF into the include folder, and create a new folder called lib and place all the library files, cmake files and pkgconfig files there. Finally create a bin folder and place the dll files there, thats also where the .exe file will be created. Run the line in the Makefile in the root directory to compile, then run the .exe file.


