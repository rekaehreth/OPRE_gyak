//make a copy of file given in argv[1] to file given in argv[2]
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>	   //open,creat
#include <sys/types.h> //open
#include <sys/stat.h>
#include <errno.h> //perror, errno

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		// error channel is the same as the standard output by default 
		perror("You have to use program with two arguments, the file names copy_from copy_to");
		exit(1);
	}
	int f, g;

	f = open(argv[1], O_RDONLY);
	// there is an access function with which we can see whether the file exists or not
	// access(filename, F_OK);
	// 1. parameter - file name
	// 2. parameter - what we want to use the file for
	// O_RDONLY - only for reading,
	// O_WRONLY - only for writing
	// return value - integer, -1 if an error occured
	// errno variable contains the error number

	// We could use fopen, but open has a similar syntax to the later functions

	if (f < 0)
	{
		perror("Error at opening the file\n");
		exit(1);
	}
	// There is errno variable in which there is the number of error --
	// if (errno!=0) there is an error

	g = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	// the three parameter long version of open - it can create the file if it doesnt exist
	// there is a creat function as well - creat(filename, permissions);
		// O_TRUNC - if the file exists, clear its contents
		// O_CREAT - create if file doesn't exist
	// 3. parameter 
		// permission(s), if the file has to be created
		// S_IRUSR - permission for reading by the owner (user)
		// S_IWUSR - permission for writing by the owner (user)
	
	if (g < 0)
	{
		perror("Error at opening the file\n");
		// e.g. no space for creating the file, no acces for the user
		exit(1);
	}

	char c; // sizeof(char) == 1 byte
	while (read(f, &c, sizeof(c)))
	{
		// read gives back the number of bytes
			// if read was unsuccesfull, it returns 0, so the loop stops
		// 1. parameter - file descriptor
		// 2. parameter - address of variable, we read into
		// 3. parameter - number of bytes we want to read in
		printf("%c", c); // we prints out the content of the file on the screen
		if (write(g, &c, sizeof(c)) != sizeof(c))
		{
			// write returns the number of written bytes
			// 1. parameter - file descriptor
			// 2. parameter - address of variable we want to write out
			// 3. parameter - number of bytes we want to write out
			perror("There is a mistake in writing\n");
			exit(1);
		}
	}
	close(f);
	close(g);
	return 0;
	// **TODO** Define a primitive struct (e.g. name + birth year), fill it with data, save it to a file, then read it back
	// **TODO** Last excercise but with the name as a dynamic array (what'll be written in the file?)
}