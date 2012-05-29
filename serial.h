#ifndef SERIAL_COMMUNICATION
#define SERIAL_COMMUNICATION

#include <iostream>
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
    class_version=VERSION;
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
  virtual bool writes(std::string value,const int number_of_try=3,const int try_wait_time=10)=0;

  //! read on serial port
  /** 
   *
   * @param[out] value= value returned by serial port
   *
   * @return 
   */
  virtual bool reads(std::string& value)=0;

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
  bool writes(std::string value,const int number_of_try=3,const int try_wait_time=10)
  {
#if cimg_debug>1
//std::cerr<<class_name<<"::"<<__func__<<"(\""<<value<<"\""<<","<<number_of_try<<" tries,"<<try_wait_time<<" ms)\n"<<std::flush;
std::cerr<<class_name<<"::"<<__func__<<"(\""<<value<<"\""<<", no try nor wait time implemented, yet! )\n"<<std::flush;
#endif
    last_message_written=value;
    value.append("\r\n");
    ///send message to port
    int error=std::system(std::string("echo "+value+" > "+port_path).c_str());
    if(error!=0)
    {
      std::cerr<<"error: message send fail (i.e. std::system error code="<<error<<"); message=\""<<value<<"\".\n";//e.g. /dev/ttyUSB0
      return false;
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

};//Cserial_system class

#endif //SERIAL_COMMUNICATION

