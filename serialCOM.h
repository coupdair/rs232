#ifndef SERIAL_COMMUNICATION
#define SERIAL_COMMUNICATION

#include <iostream>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

class serialCOM
{ 
 public:
  std::string port;
  std::string message;
//! \todo [high] add \c fd as member (so, read and write without)
//! \todo [] add open() with \c port_path

//! \todo [low] move open, write and read to .cpp (i.e. need Makefile changes)

  //! Open serial port
  /** 
   *
   * @param[in] port 
   *
   * @return 
   */
  int opens()
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
	std::cerr << "port is open"<<std::endl;
      }  
    return(fd);
  }
  
  //! write on serial port
  /** 
   *
   * @param[in] fd= File descriptor for the port 
   * @param[in] message= string to send to serial port  
   *
   * @return 
   */
  int writes(int fd)
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
	    std::cerr << "write KO :(" << std::endl;
	    return 1;
	  }
	std::cerr << "rs232 not ready, retry" << std::endl;
      }
    std::cerr << "write OK" << std::endl;
    return 0;
  }//writes

  //! read on serial port
  /** 
   *
   * @param[in] fd= File descriptor for the port 
   * @param[out] value= value returned by serial port
   *
   * @return 
   */
  int reads(int fd,std::string& value)
  {
    char buffer[255];  /* Input buffer */
    char *bufptr;      /* Current char in buffer */
    int  nbytes;       /* Number of bytes read */
    //std::string value;

    bufptr = buffer;
    while ((nbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1)) > 0)
      {
	std::cerr << "reading buffer" << std::endl;
	//std::cout<<"nbytes="<<nbytes<<"\n";
	bufptr += nbytes;
	if (bufptr[-1] == '\n' || bufptr[-1] == '\r')
	  break;
      }
    std::cerr << "read OK" << std::endl;
    buffer[bufptr-buffer-1]='\0';
    //std::cout << buffer << endl;
    close(fd);
    value=buffer;
    return (0);
  }//reads

};//serialCOM class

#endif //SERIAL_COMMUNICATION

