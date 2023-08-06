# MandelBrot-Set-Explorer
A simple project that will let you explore the mandelbrot set.

# Pictures:
The full MandelBrot:

![image](https://user-images.githubusercontent.com/62178977/160417535-c5a373f2-c9f4-43cd-8466-29fde3e1a13f.png)

Neat Shapes
![image](https://user-images.githubusercontent.com/62178977/160417958-90e22612-8921-417b-b978-32b63ae62e54.png)

Fun Spirals
![image](https://user-images.githubusercontent.com/62178977/160418187-53ab9526-6bb8-4d84-84f4-67eb1856308b.png)

Horizon of the MandelBrot
![image](https://user-images.githubusercontent.com/62178977/160418416-bb74ffb2-e581-45b4-8312-ebce5e437494.png)

# Controls:

> Mouse motion : Move around
 
> Scroll : Zoom

> TAB : Free mouse


# Compiling on Linux:

## dependencies:

> openGL 4.0
> glfw3 (libglfw3-dev on debian/ubuntu)
> make
> glad(included)

## running:

To Compile the program simply write the command specified below in your terminal

> make

It will launch the executable automatically.
you can pass one argument to the executable: the iteration count.
The higher it is the more precise the mandelbrot will be,
by default this value is set to 500.
you can change it to 1500 iterations by running:

> ./MandelBrotSetExplorer 1500
