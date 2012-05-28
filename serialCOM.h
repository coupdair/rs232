#ifndef SERIAL_COMMUNICATION
#define SERIAL_COMMUNICATION

#include <iostream>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#define SERIAL_OPEN_ERROR  -1
#define SERIAL_CLOSED      -2

class serialCOM
{
public:
  //! class name for debug only
#if cimg_debug>1
  std::string class_name;
#endif
private:
  //!File descriptor for the port
  int fd;
public:
  //! port path name (e.g. "/dev/ttyUSB0")
  std::string port;
//! \todo [high] _ \c port_name for information only (remove \c port).
//! \todo [next] _ replace \c fd by \c port.
  //! message to send or received (e.g. "CONF:GAIN 1") for information only.
  std::string message;
//! \todo [high] v add opens() with \c port_path and writes with message.
//! \todo [high] _ \c last_message_written, \c last_message_readed (remove \c message).

//! \todo [medium] _ error handling: init fd to SERIAL_CLOSED (i.e. constructor), return code error in all functions but opens() (i.e. if(fd!=SERIAL_CLOSED) closes(); ).
//! \todo [next]   _ call closes in destructor (e.g. add also if(fd!=SERIAL_CLOSED) in closes).
//! \todo [low] move opens, writes, reads and closes to .cpp (i.e. need Makefile changes)
  serialCOM()
  {
#if cimg_debug>1
    class_name="serialCOM";
#endif
  }//constructor

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
    if (fd == SERIAL_OPEN_ERROR)
    {
      std::cerr<<"open_port: Unable to open "<<port<<" port.\n";//e.g. /dev/ttyUSB0
      return false;
    }
    fcntl(fd, F_SETFL, 0);
    std::cerr << "port is open"<<std::endl;
    return true;
  }//opens

  //! Open serial port
  /** 
   *
   * @param[in] port 
   *
   * @return 
   */
  bool opens(const std::string& port_path)
  {
    port=port_path;
    return opens();
  }//opens
  
  //! write on serial port
  /** 
   *
   * @param[in] message= string to send to serial port  
   *
   * @return 
   */
  bool writes(std::string value,const int number_of_try=3,const int try_wait_time=10)
  {
#if cimg_debug>1
std::cerr<<class_name<<"::"<<__func__<<"(\""<<value<<"\""<<","<<number_of_try<<" tries,"<<try_wait_time<<" ms)\n"<<std::flush;
#endif
    message=value;
    value.append("\r\n");
    int  tries=0;        /* Number of tries so far */
    while(write(fd,(const char*)value.c_str(),value.size()) <value.size())
      {
	tries++;
	if (tries > number_of_try)
	  {
	    std::cerr<<"error: write KO :( (with "<<--tries<<" tries)\n"<<std::flush;
	    return false;
	  }
	std::cerr<<"warning: rs232 not ready, retry\n"<<std::flush;
        cimg_library::cimg::wait(try_wait_time);
      }//try loop
    std::cerr << "write OK\n" << std::flush;
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
#if cimg_debug>1
    std::cerr<<class_name<<"::"<<__func__<<"(get \""<<value<<"\")\n"<<std::flush;
#endif
    char buffer[255];  /* Input buffer */
    char *bufptr;      /* Current char in buffer */
    int  nbytes;       /* Number of bytes read */
    //std::string value;
//std::cerr<<__func__<<"/sizeof(buffer)="<<sizeof(buffer)<<"\n"<<std::flush;
    //initialisation
//    std::memset(buffer,0,255);
    //read loop
    bufptr = buffer;
    while ((nbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1)) > 0)
      {
	std::cerr << "reading buffer" << std::endl;
//std::cerr<<"nbytes="<<nbytes<<"\n"<<std::flush;
	bufptr += nbytes;
	if (bufptr[-1] == '\n' || bufptr[-1] == '\r')
	  break;
      }
    std::cerr << "read OK\n" << std::flush;
    buffer[bufptr-buffer-1]='\0';
//std::cerr<<__func__<<"/lenght(buffer)="<<strlen(buffer)<<"\n"<<std::flush;
    value=buffer;
    message=value;//for information
#if cimg_debug>1
std::cerr<<class_name<<"::"<<__func__<<"(set \""<<value<<"\")\n"<<std::flush;
#endif
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
    fd=SERIAL_CLOSED;
    return true;
  }//closes

};//serialCOM class

#endif //SERIAL_COMMUNICATION

