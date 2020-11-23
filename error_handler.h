#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

class Error_handler{

public:
  int check_parameters(int argc, char** argv);
  int recognise_parameter(const char* filename);
  int check_character(char &ch);
  int check_plugboard(const char* filename);
  int check_reflector(const char* filename);

};


#endif


  

  
