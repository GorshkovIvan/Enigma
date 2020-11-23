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

  /*Testing Errors*/
  
  error_code = error_handler.error_testing(argc, argv);

  if(error_code != NO_ERROR){

    return error_code;

  }

  /*Getting user input and checking its validity. */
  
  while(cin >> ws >> ch){

    error_code = error_handler.check_character(ch);

    if(error_code != 0){
      
      break;
      
    }else{

    message.push_back(ch);
    
    }
  }

  /*Creating Enigma and initialising its components with input files. */
  
  auto machine = Enigma(argc, argv);

  /*Encrypting a message by passing it by reference. */
  
  machine.encrypt_message(message);

  /*Printing message*/
  
  for(auto char_index = 0u; char_index < message.size(); char_index++){
      
    cout << message[char_index];
      
  }



  return error_code;
}
