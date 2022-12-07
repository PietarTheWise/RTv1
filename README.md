<h1 align="center">
  <br>
    RTv1
  <br>
</h1>

<h3 align="center">Simple raytracer engine, built in c with SDL2</h3>

<img src="screenshots/rtv1_cool.png"></img>

<p align="center">
  <a href="#what-it-does">What it does?</a> •
  <a href="#primitives">Primitives</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#disclaimer">Disclaimer</a>
</p>

## What it does?

* Renders pictures on the screen of a 3D scene.
* Renders simple primitives, cone, cylinder, sphere and plane.
* Takes in a parameter on the command line of a scene.
* Parses the data in the file and creates the scene accordingly.
* You can rotate the the camera and objects from the files.

## Primitives

<img src="screenshots/primitives.png"></img>

## How To Use

To clone and run this application, you'll need [Git](https://git-scm.com) and gcc compiler installed on your computer. Also you need miniLibX graphics library which on my knowledge doesn't work on windows. This has been tested only on MacOs. Run the following commands on the command line:

```bash
# Clone this repository
$ git clone https://github.com/PietarTheWise/RTv1.git
# Build the program by typing:
$ make
# in command line

#then run:
$ ./Rtv1 scenes/cool_scene

#Note: There are other scenes on the scenes folder that you can run with the program.

```

## DISCLAIMER

<p>
This is a project from 42 school, which is a school that utilizes peer to peer learning.
We're only given a document that gives us the details of the assignment, therefore each implementation
is unique. Each assignment is tested for crashes and other bugs thoroughly by other peers. Apart from some exceptions, existing
libraries are banned, these projects utilize our self made version of libc called libft.
</p>
