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
  //!File descriptor for the port
  int fd;
public:
  //! port path name (e.g. "/dev/ttyUSB0")
  std::string port;
  //! message to send or received (e.g. "CONF:GAIN 1")
  std::string message;
//! \todo [high] v add \c fd as member (so, read and write without)
//! \todo [high] _ add open() with \c port_path

//! \todo [low] move open, write and read to .cpp (i.e. need Makefile changes)

  //! Open serial port
  /** 
   *
   * @param[in] port 
   *
   * @return 
   */
  bool opens()
  {
    fd=open((const char*)port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
      perror(std::string("open_port: Unable to open "+port+" port.").c_str());//e.g. /dev/ttyUSB0
      return false;
    }
    fcntl(fd, F_SETFL, 0);
    std::cerr << "port is open"<<std::endl;
    return true;
  }//opens
  
  //! write on serial port
  /** 
   *
   * @param[in] message= string to send to serial port  
   *
   * @return 
   */
  bool writes()
  {
    int  tries=0;        /* Number of tries so far */
    message.append("\r");
    //cout << message << endl;
    //cout << message.size()<< endl;
    while(write(fd,(const char*)message.c_str(),message.size()) <message.size())
      {
	tries++;
	//    {
	//    if (write(fd,(const char*)message.c_str(),message.size()) <message.size())
	// 	  break;
	if (tries > 3)
	  {
	    std::cerr << "write KO :(" << std::endl;
	    return false;
	  }
	std::cerr << "rs232 not ready, retry" << std::endl;
      }//try loop
    std::cerr << "write OK" << std::endl;
    return true;
  }//writes

  //! read on serial port
  /** 
   *
   * @param[out] value= value returned by serial port
   *
   * @return 
   */
  bool reads(std::string& value)
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
//! \bug please do not close fd here !, \see closes
    //std::cout << buffer << endl;
    value=buffer;
    return true;
  }//reads

  //! Close serial port
  /** 
   *
   * @return 
   */
  bool closes()
  {
    close(fd);
    return true;
  }//closes

};//serialCOM class

#endif //SERIAL_COMMUNICATION

