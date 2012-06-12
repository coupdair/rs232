#ifndef SERIAL_COMMUNICATION
#define SERIAL_COMMUNICATION

#include <iostream>
#include <fstream>
#include <string>

class Cserial
{
public:
  //! class name for debug only
#if cimg_debug>1
  std::string class_name;
#endif
  //! class (or library) version for information only
  std::string class_version;
  //! port path name (e.g. "/dev/ttyUSB0")
  std::string port_path;
  std::string last_message_written;
  std::string last_message_readed;

  //! constructor
  /**
   *
  **/
  Cserial()
  {
#if cimg_debug>1
    class_name="Cserial_virtual";
#endif
    class_version=RS232_VERSION;
  }//constructor

  //! Open serial port from \c port_path
  /** 
   *
   * @return true on success (false otherwize)
   */
  virtual bool opens()=0;

  //! Open serial port from new value of \c port_path
  /** 
   *
   * @param[in] port_path_name: path
   *
   * @return 
   */
  virtual bool opens(const std::string& port_path_name)
  {
    port_path=port_path_name;
    return opens();
  }//opens
  
  //! write on serial port
  /** 
   *
   * @param[in] message= string to send to serial port  
   *
   * @return 
   */
  virtual bool writes(std::string value,const int number_of_try=3,const int try_wait_time=20)=0;

  //! read on serial port
  /** 
   *
   * @param[out] value= value returned by serial port
   *
   * @return 
   */
  virtual bool reads(std::string& value)=0;

  //! get a value from device on serial port (i.e. write then read; e.g. ask for a value)
  /** 
   *
   * @param[in]  ask=ask for a variable value (writes: string to send to serial port) 
   * @param[out] value=returned value (reads: value returned by serial port)
   *
   * @return 
   */
  virtual bool gets(std::string ask,std::string value,const int number_of_try=3,const int try_wait_time=20)=0;

  //! Close serial port
  /** 
   *
   * @return 
   */
  virtual bool closes()=0;

};//Cserial class

class Cserial_system: public Cserial
{
public:
  //! constructor
  /**
   *
  **/
  Cserial_system()
  {
#if cimg_debug>1
    class_name="Cserial_system";
#endif
  }//constructor

  //! Open serial port (actually, check if exists)
  /** 
   *
   * @param[in] port port name
   *
   * @return 
   */
  bool opens()
  {
#if cimg_debug>1
std::cerr<<class_name<<"::"<<__func__<<": use system command execution (i.e. std::system() )\n"<<std::flush;
#endif
    ///check \c port_name validity
    if(port_path.empty()) return false;
    ///check port validity
    int error=std::system(std::string("ls "+port_path).c_str());
    if(error!=0)
    {
      std::cerr<<"error: Unable to list "<<port_path<<" port (i.e. std::system error code="<<error<<").\n";//e.g. /dev/ttyUSB0
      return false;
    }
    ///print availability
    std::cerr<<"port is available"<<std::endl;
    return true;
  }//opens

  //! Open serial port from new value of \c port_path
  /** 
   *
   * @param[in] port_path_name: path
   *
   * @return 
   */
  bool opens(const std::string& port_path_name)
  {
    return Cserial::opens(port_path_name);
  }//opens

  //! write on serial port
  /** 
   *
   * @param[in] message= string to send to serial port  
   *
   * @return 
   */
  bool writes(std::string value,const int number_of_try=3,const int try_wait_time=20)
  {
#if cimg_debug>1
//std::cerr<<class_name<<"::"<<__func__<<"(\""<<value<<"\","<<number_of_try<<" tries,"<<try_wait_time<<" ms)\n"<<std::flush;
//std::cerr<<class_name<<"::"<<__func__<<"(\""<<value<<"\", no try nor wait time implemented, yet! )\n"<<std::flush;
std::cerr<<class_name<<"::"<<__func__<<"(\""<<value<<"\", no try yet, wait_time="<<try_wait_time<<")\n"<<std::flush;
#endif
    last_message_written=value;
//    value.append("\r\n");
    ///send message to port
    char character[2];character[1]='\0';
    std::string message_echo;message_echo.reserve(255);
    for(int i=0;i<value.size();++i)
    {
      character[0]=value[i];
      message_echo="/bin/echo -e -n '"+std::string(character)+"' > "+port_path;
      int error=std::system(message_echo.c_str());
      if(error!=0)
      {
        std::cerr<<"error: message send fail (i.e. std::system error code="<<error<<"); message=\""<<value<<"\" @["<<i<<"]="<<value[i]<<".\n";//e.g. /dev/ttyUSB0
        return false;
      }
//std::cerr<<message_echo<<"\n"<<std::flush;
      cimg_library::cimg::wait(try_wait_time/*wait_time*/);
    }
    ///print ok
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
    std::cerr<<class_name<<"::"<<__func__<<" empty function.\n"<<std::flush;
#endif
/*
#if cimg_debug>1
    std::cerr<<class_name<<"::"<<__func__<<"(get \""<<value<<"\")\n"<<std::flush;
#endif
*/
    return true;
  }//reads

  //! get a value from device on serial port (i.e. write then read; e.g. ask for a value)
  /** 
   *
   * @param[in]  ask=ask for a variable value (writes: string to send to serial port) 
   * @param[out] value=returned value (reads: value returned by serial port)
   *
   * @return 
   */
  bool gets(std::string ask,std::string value,int number_of_try=3,const int try_wait_time=20)
  {
    if(number_of_try>9) number_of_try=9;
    #if cimg_debug>1
    std::cerr<<class_name<<"::"<<__func__<<"(\""<<ask<<"\", value, number_of_try="<<number_of_try<<", wait_time="<<try_wait_time<<")\n"<<std::flush;
    #endif
    last_message_written=ask;
    //ask.append("\r\n");
    std::string command;
    command="get=";
    command+=ask;
    command+="; for((i=1;i<";
    command+=(char)(number_of_try+'0');//! \bug number_of_try<10
    command+=";i++)); do rm respond.serial; echo '#!/bin/bash' > read.sh; echo 'exec 3<>/dev/ttyUSB0; /bin/echo -n -e \"'$get'\" >&3; read hop <&3 ; echo $hop > respond.serial' >> ./read.sh; chmod u+x read.sh ; ./read.sh & pid=$! ; sleep 1; kill $pid; n=`cat respond.serial | wc -c`; if ((n>1)) ; then break; fi; done; cat respond.serial; echo 'respond in '$i' tries.'";
std::cerr<<"command="<<command<<"\n"<<std::flush;
    //send write/read commands with tries and sleep time
    int error=std::system(command.c_str());
    if(error!=0)
    {
      std::cerr<<"error: get value fail (i.e. std::system error code="<<error<<"); ask=\""<<ask<<"\").\n";
      return false;
    }
    //get the result from file
    std::ifstream is;
    is.open("respond.serial");
    if(!is.good()) return false;
    ///print ok
    std::cerr << "get OK\n" << std::flush;
    is>>value;
    is.close(); 
std::cerr << "get value=\""<<value<<"\"\n" << std::flush;
    std::system("rm respond.serial");
    return true;
  }

  //! Close serial port
  /** 
   *
   * @return 
   */
  bool closes()
  {
#if cimg_debug>1
    std::cerr<<class_name<<"::"<<__func__<<" empty function.\n"<<std::flush;
#endif
    return true;
  }//closes

};//Cserial_system class

#endif //SERIAL_COMMUNICATION

