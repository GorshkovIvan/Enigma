#include<iostream>
#include"enigma.h"
#include"error_handler.h"
#include"errors.h"
#include<vector>
#include<cstring>

using namespace std;

int main(int argc, char** argv){
   
  vector<char> message;
  char ch;
  int error_code;
  Error_handler error_handler;

  error_code = error_handler.check_parameters(argc, argv);
  if(error_code != 0){
    
    return error_code; 

  }

  error_code =  error_handler.check_plugboard(argv[1]);
  if(error_code != 0){
    
    return error_code; 

  }

  error_code = error_handler.check_reflector(argv[2]);
  if(error_code != 0){
    
    return error_code; 

  }

  int file_position = 3;
  
  while(error_handler.recognise_parameter(argv[file_position]) == 2){

    error_code = error_handler.check_rotor(argv[file_position]);
    
    if(error_code != 0)
      return error_code;
    
    file_position ++;

  }
    
  while(cin >> ws >> ch){

    error_code = error_handler.check_character(ch);

    if(error_code != 0){
      
      break;
      
    }else{

    message.push_back(ch);
    
    }
  }

          
  auto machine = Enigma(argc, argv);


  machine.encrypt_message(message);
  
  for(auto char_index = 0u; char_index < message.size(); char_index++){
      
    cout << message[char_index];
      
  }



  return error_code;
}
