#include<iostream>
#include<fstream>
#include<vector>
#include"error_handler.h"
#include"errors.h"
#include"enigma.h"
#include<string>
#include<sstream>

using namespace std;

/*load_data is used to setup plugboard and reflector objects.*/
int load_data(const char* filename, int wiring[]){
    
  ifstream in_stream;
  string input;
  int count = 0;
  
  
  in_stream.open(filename);
  if(!in_stream){
    return -11;
  }
  
  while(in_stream >> input){

    if(count ==  NUM_LETTERS){
      
      in_stream.close();
      return -610;
      
    }

    for(auto i = 0u; i < input.length(); i++){ //checks whether input is an integer
      
      if(!(isdigit(input[i]))){
	in_stream.close();
	return -4;
	
      }
    }

    stringstream ss(input);
    ss >> wiring[count];
    if(wiring[count] > 25 || wiring[count] < 0){ //checks whether input is in range 
      in_stream.close();
      return -3;
    }
    
    ss.str("");
       
    count++;
    if(count > 1){                               //searches for duplicates 
      for(int i = 0; i < count-1; i++){
	for(int j = 1; j < count - i; j++){
	  if(wiring[i] == wiring[i+j]){
	    in_stream.close();
	    return -59;
	    
	  }
	}
      }
    }
  }

  in_stream.close();

  return count;
  
}

/*load_data_rotors is used to setup rotor objects.*/
int load_data_rotors(const char* filename, int wiring[]){
    
  ifstream in_stream;
  string input;
  int count = 0;
  
  
  in_stream.open(filename);
  if(!in_stream){
    return -11;
  }
  
  while(in_stream >> input){
    
     if(count ==  NUM_LETTERS*2){
      
      in_stream.close();
      cerr << "Too many parameters";
      return INVALID_ROTOR_MAPPING;
      
    }

    for(auto i = 0u; i < input.length(); i++){  //Checks whether input is an integer
      
      if(!(isdigit(input[i]))){
	in_stream.close();
	return -4;
   
      }
    }

    stringstream ss(input);
    ss >> wiring[count];
    if(wiring[count] > 25 || wiring[count] < 0){  //Checks that whether input is in range 
      in_stream.close();
      return -3;
    }
    
    ss.str("");

    if(count > 1 && count < NUM_LETTERS){          //Searches for duplicates
      for(int i = 0; i < count-1; i++){
	for(int j = 1; j < count - i -1; j++){
	  if(wiring[i] == wiring[i+j]){
	    cerr << "Invalid mapping of input " << i+j << " to output " << wiring[i+j] << " (output " << wiring[i+j] << " is already mapped to from input) " << i << " in " << filename;
	    in_stream.close();
	    return -7;
	    
	  }
	}
      }
    }
	
    count++;
    
  }

  in_stream.close();

  return count;
  
}

/*load_data_starting positions is used to setup rotor rotor starting positions.*/
int load_data_starting_positions(const char* filename, int positions[]){
    
  ifstream in_stream;
  string input;
  int count = 0;
  
  in_stream.open(filename);
  if(!in_stream){
    return -11;
  }
  
  while(in_stream >> input){
    
    for(auto i = 0u; i < input.length(); i++){   //checks whether input is an integer
      
      if(!(isdigit(input[i]))){
	
	in_stream.close();
	return -4;
   
      }
    }

    stringstream ss(input);
    
    ss >> positions[count];
    if(positions[count] > 25 || positions[count] < 0){   //checks that whether input is in range 
      
      in_stream.close();
      return -3;
      
    }
    
    ss.str("");
	
    count++;
    
  }

  in_stream.close();
  
  return count;
  
}
  
 
