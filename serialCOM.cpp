#include <iostream>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

    /*
     * 'open_port()' - Open serial port 1.
     *
     * Returns the file descriptor on success or -1 on error.
     */
using namespace std;

//! Open serial port
/** 
 *
 * @param[in] port 
 *
 * @return 
 */
int serial_open(string port)
{
  int fd; /* File descriptor for the port */  
  fd = open((const char*)port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
    {
      perror("open_port: Unable to open /dev/ttyUSB0 - ");
    }
  else	
    {
      fcntl(fd, F_SETFL, 0);
      printf("port is open.\n");
    }  
  return(fd);
}
int serial_write(int fd,string message)
{
  int  tries;        /* Number of tries so far */
  message.append("\r");
  //cout << message << endl;
  //cout << message.size()<< endl;
   for (tries = 0; tries < 3; tries ++)
      {
  	if (write(fd,(const char*)message.c_str(),message.size()) <message.size())
	  {
	  cout << "write ok" << endl;
	  break;
	  }
	  cout << "try again ..." << endl;
      }
   return 0;
}

int main(void) 
{ 
  string port="/dev/ttyUSB0";
  int fd=serial_open(port);
  // WRITE 
  string message="INST:CNUM?";
  serial_write(fd,message);
  //READ
  char buffer[255];  /* Input buffer */
  char *bufptr;      /* Current char in buffer */
  int  nbytes;       /* Number of bytes read */

  //if (write(fd, "INST:CNUM?\r",11) <11)
	  //  continue;
	//  int n = write(fd, "*IDN?\r", 6);
	//if (n < 0)
	//fputs("write() of 6 bytes failed!\n", stderr);
	//n =read(fd,"",10);
	bufptr = buffer;
	//	  fcntl(fd, F_SETFL, FNDELAY);
	while ((nbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1)) > 0)
	  {
cout<<"nbytes="<<nbytes<<"\n";
	    bufptr += nbytes;
	    if (bufptr[-1] == '\n' || bufptr[-1] == '\r')
	      break;
	  }
	buffer[bufptr-buffer-1]='\0';
	//CLOSE 

	cout << buffer << endl;
	close(fd);
	//        cout << "Hello World!\n";
	
       //main
   return (0);
}















