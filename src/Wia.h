#ifndef __WIA_H
#define __WIA_H

#include "Arduino.h"

class Wia {

public:

  Wia();
  Wia(String access_token);

  int createEvent(String);
  int createEvent(String, String);
  int createEvent(String, int);
  int createEvent(String, double);
  int createEvent(char* , char*);
  int createEvent(char*, int);
  int createEvent(char*, double);

  String getLatestDeploymentId();

private:
  String getAccessToken();
  String _access_token;
};


#endif
