#ifndef serial
#define serial

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

int main(void) 
{ 
  // OPEN 
  string port="/dev/ttyUSB0";
  int fd=serial_open(port);
  // WRITE 
  string message="INST:CNUM?";
  serial_write(fd,message);
  // READ
  string value;
  serial_read(fd,value);
  cout << value << endl;
   return (0);
}

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
      cerr << "port is open"<<endl;
    }  
  return(fd);
}

//! write on serial port
/** 
 *
 * @param[in] fd= state of port 
 * @param[in] message= string to send to serial port  
 *
 * @return 
 */
int serial_write(int fd,string message)
{
  int  tries=0;        /* Number of tries so far */
  message.append("\r");
  //cout << message << endl;
  //cout << message.size()<< endl;
  while (write(fd,(const char*)message.c_str(),message.size()) <message.size())
    {
      tries++;
  //    {
  //    if (write(fd,(const char*)message.c_str(),message.size()) <message.size())
  // 	  break;
      if (tries > 3)
	{
	  cerr << "write KO :(" << endl;
	  return 1;
	}
      cerr << "rs232 not ready, retry" << endl;
    }
    cerr << "write OK" << endl;
    return 0;
}

//! write on serial port
/** 
 *
 * @param[in] fd= state of port 
 * @param[out] value= value returned by serial port
 *
 * @return 
 */
int serial_read(int fd,string &value)
{
  char buffer[255];  /* Input buffer */
  char *bufptr;      /* Current char in buffer */
  int  nbytes;       /* Number of bytes read */

	bufptr = buffer;
	while ((nbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1)) > 0)
	  {
	    //cout<<"nbytes="<<nbytes<<"\n";
	    bufptr += nbytes;
	    if (bufptr[-1] == '\n' || bufptr[-1] == '\r')
	      break;
	  }
	buffer[bufptr-buffer-1]='\0';
	//cout << buffer << endl;
	close(fd);
	value=buffer;
   return (0);
}















