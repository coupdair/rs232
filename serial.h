#ifndef SERIAL_COMMUNICATION_EXEC
#define SERIAL_COMMUNICATION_EXEC

#include <iostream>

class serial
{
public:
  //! class name for debug only
#if cimg_debug>1
  std::string class_name;
#endif
  //! port path name (e.g. "/dev/ttyUSB0")
  std::string port_path;
  std::string last_message_written;
  std::string last_message_readed;

  //! constructor
  /**
   *
  **/
  serial()
  {
#if cimg_debug>1
    class_name="serial";
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
std::cerr<<class_name<<"::"<<__func__<<": use system command execution (i.e. exec() )\n"<<std::flush;
#endif
    ///check \c port_name validity
    if(port_path.empty()) return false;
    ///check port validity
//    exec("ls /dev/");
//    if(fd == SERIAL_OPEN_ERROR)
    {
      std::cerr<<"open_port: Unable to list "<<port_path<<" port.\n";//e.g. /dev/ttyUSB0
      return false;
    }
    std::cerr<<"port is available"<<std::endl;
    return true;
  }//opens

  //! Open serial port
  /** 
   *
   * @param[in] port 
   *
   * @return 
   */
  bool opens(const std::string& port_path_name)
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
  bool writes(std::string value,const int number_of_try=3,const int try_wait_time=10)
  {
#if cimg_debug>1
std::cerr<<class_name<<"::"<<__func__<<"(\""<<value<<"\""<<","<<number_of_try<<" tries,"<<try_wait_time<<" ms)\n"<<std::flush;
#endif
    last_message_written=value;
    value.append("\r\n");
//    exec();
#if cimg_debug>1
std::cerr<<class_name<<"::"<<__func__<<" empty.\n"<<std::flush;
#endif
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
    std::cerr<<class_name<<"::"<<__func__<<" empty.\n"<<std::flush;
#endif
/*
#if cimg_debug>1
    std::cerr<<class_name<<"::"<<__func__<<"(get \""<<value<<"\")\n"<<std::flush;
#endif
*/
    return true;
  }//reads

  //! Close serial port
  /** 
   *
   * @return 
   */
  bool closes()
  {
#if cimg_debug>1
    std::cerr<<class_name<<"::"<<__func__<<" empty.\n"<<std::flush;
#endif
    return true;
  }//closes

};//serialCOM class

#endif //SERIAL_COMMUNICATION

