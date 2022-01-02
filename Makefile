#######################################################################
# Homework Assignment 5, for EECS 22, Winter 2020
#
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables
FLAGS = -ansi -std=c99 -Wall -g
DESIGN = MovieLab

# Default target
all: MovieLab

######################### Generate object files #######################
# Target for FileIO.o
FileIO.o: FileIO.h FileIO.c Image.h Constants.h
	gcc $(FLAGS) -c FileIO.c -o FileIO.o
# Target for DIPs.o
DIPs.o: DIPs.h DIPs.c Image.h FileIO.h Constants.h
	gcc $(FLAGS) -lm -c DIPs.c -o DIPs.o 
# Target for Image.o
Image.o: Image.h Image.c 
	gcc $(FLAGS) -c Image.c -o Image.o
	
# Target for other object files

# Target for Movie.o
Movie.o: Movie.h Movie.c ImageList.h Image.h
	gcc $(FLAGS) -c Movie.c -o Movie.o 

ImageList.o: ImageList.h ImageList.c Image.h
	gcc $(FLAGS) -c ImageList.c -o ImageList.o 

# Target for MovieIO.o
MovieIO.o: MovieIO.h MovieIO.c FileIO.h Image.h ImageList.h Movie.h Constants.h
	gcc $(FLAGS) -c MovieIO.c -o MovieIO.o 

# Target for IterativeFilter.o
IterativeFilter.o: IterativeFilter.h IterativeFilter.c Image.h Movie.h 
	gcc $(FLAGS) -c IterativeFilter.c -o IterativeFilter.o 

# Target for MovieLab.o
MovieLab.o: MovieLab.c FileIO.h DIPs.h Image.h Movie.h ImageList.h MovieIO.h IterativeFilter.h Constants.h
	gcc $(FLAGS) -c MovieLab.c -o MovieLab.o 

######################### Generate the executable #####################
# Target for MovieLab
MovieLab: MovieLab.o FileIO.o DIPs.o Image.o Movie.o ImageList.o MovieIO.o IterativeFilter.o
	gcc $(FLAGS) -lm MovieLab.o FileIO.o DIPs.o Image.o Movie.o ImageList.o MovieIO.o IterativeFilter.o -o MovieLab

###############################  others  ##############################
# Target for clean
clean: 
	rm -f *.o *.yuv $(DESIGN)
