#include "Wia.h"
#include <Arduino.h>
#include <HTTPClient.h>
#include <Preferences.h>

#define USE_SERIAL Serial

Wia::Wia(String access_token) {
  if (access_token != NULL) {
    _access_token = access_token;
  }
  else {
    Preferences preferences;

    preferences.begin("storage",false);
      _access_token = preferences.getString("secret_key").c_str();
    preferences.end();

  }
}


Wia::Wia() {
  Preferences preferences;

  preferences.begin("storage",false);
    _access_token = preferences.getString("secret_key").c_str();
  preferences.end();
}


int Wia::createEvent(String name) {
  return createEvent(name, "");
}


int Wia::createEvent(String name, int data) {
  return createEvent(name, String(data));
}


int Wia::createEvent(String name, double data) {
  return createEvent(name, String(data));
}


int Wia::createEvent(char *name, int data) {
  return createEvent(String(name), String(data));
}


int Wia::createEvent(char *name, double data) {
  return createEvent(String(name), String(data));
}


int Wia::createEvent(char *name,  char *data) {
  return createEvent(String(name), String(data));
}


int Wia::createEvent(String name, String data) {
  HTTPClient http;

  String body = "{\"name\":\"" + name +"\",\"data\":\""+ data + "\"}";

  http.begin("http://api.wia.io/v1/events");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + _access_token );
  http.addHeader("Content-Length", String(body.length()));

  int httpCode =  http.POST(body);

  if(httpCode > 0) {
      USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);

      if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          USE_SERIAL.println(payload);
      }
  } else {
      USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  return httpCode;
}
