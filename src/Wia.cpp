#include "Wia.h"
#include <Arduino.h>
#include <HTTPClient.h>
#include <Preferences.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_system.h"

Wia::Wia() {}

Wia::Wia(String access_token) {
  _access_token = access_token;
}

String Wia::getAccessToken() {
  if (_access_token == NULL) {
    esp_err_t err = nvs_flash_init();

    if (err == ESP_OK) {
      Preferences preferences;

      preferences.begin("storage", true);
      _access_token = preferences.getString("secret_key");

      if (_access_token != NULL) {
        printf("Could not get access token.\n");
      }
      preferences.end();
    } else {
      printf("Error with nvs_flash_init (%s) !\n", esp_err_to_name(err));
    }
  }

  return _access_token;
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
  http.addHeader("Authorization", "Bearer " + getAccessToken() );
  http.addHeader("Content-Length", String(body.length()));

  int httpCode =  http.POST(body);

  if(httpCode > 0) {
      // USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);

      if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          // USE_SERIAL.println(payload);
      }
  } else {
      // USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();

  return httpCode;
}
