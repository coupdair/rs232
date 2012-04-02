//#ifndef serial
//#define serial

class serialCOM
{ 
 public:
  string port;
  string message;
  string value;

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
	cerr << "port is open"<<endl;
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
   * @param[in] fd= File descriptor for the port 
   * @param[out] value= value returned by serial port
   *
   * @return 
   */
  int reads(int fd,string& value)
  {
    char buffer[255];  /* Input buffer */
    char *bufptr;      /* Current char in buffer */
    int  nbytes;       /* Number of bytes read */
    //string value;

    bufptr = buffer;
    while ((nbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1)) > 0)
      {
	cerr << "reading buffer" << endl;
	//cout<<"nbytes="<<nbytes<<"\n";
	bufptr += nbytes;
	if (bufptr[-1] == '\n' || bufptr[-1] == '\r')
	  break;
      }
    cerr << "read OK" << endl;
    buffer[bufptr-buffer-1]='\0';
    //cout << buffer << endl;
    close(fd);
    value=buffer;
    return (0);
  } 
};//serialCOM class


//#endif// serial














