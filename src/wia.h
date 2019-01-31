

#ifndef __WIA_H
#define __WIA_H

#include <Arduino.h>

class Wia{
public:
  Wia();
  Wia(String);
  int create_event(String, String);
  int create_event(String, int);
  int create_event(String, double);
  int create_event(char* , char*);
  int create_event(char*, int);
  int create_event(char*, double);


private:
  String _access_token;
};


#endif
