# Software-Rasterizer

personal project, tightlyish following [sebstian lague's software rasterizer](https://www.youtube.com/watch?v=yyJ-hdISgnw)


content warning: a few swears and varying levels of coding skills


why is this the only personal project i published? (just on github i have 35 private repos + this one, and that's a small portion of all my projects)

i made a poll for fun on discord to see if i publish this project

yes:7 votes (including mine)

no: 2 votes

# how to build/run
## linux

you need ```build-essentials``` and ```libx11-dev``` for x11 or the wayland dev kit for wayland

for wayland you also need to go to src/openGL/src/internal.h to comment out line 34 and uncomment line 35, note that i don't test wayland

do
```make```
to build

do
```make run```
to run

## windows
you need to have msvc installed, aka visual studio with the c++ development kit, then open the make.bat file and change the vcvarsall path to your vcvarsall
### powershell
do
```.\make```
to build

then
```.\build\out\software_rasterizer.exe```
to run
### cmd
do
```make```
to build

then reopen your terminal, because i forgot i used ```exit``` for function shenanigans, i'll fix it later

then do
```build\out\software_rasterizer.exe```
to run

## apple
no f*ing clue if that's gonna work

get your c/c++ dev environement that works with make

go to src/main.cpp and change the start_timer and print_timer functions accordingly

uncomment lines 40 44 77 78 79 in the makefile

follow(ish) build and run linux instructions

if that doesn't work, you're on your own, if that still doesn't work, you can shove it * * *.


# TODO
continue following the video

fix the thing to fix later

fixe a memory leak, seems fine for now, but it seems to crash if the model is too big
