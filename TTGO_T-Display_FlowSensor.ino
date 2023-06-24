#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID   "TMPL6TkQj_281"
#define BLYNK_TEMPLATE_NAME "PROJECT"
#define BLYNK_AUTH_TOKEN    "0maGjV7IW3W3PTlmEqK5j9kluzPO7k4C"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <Arduino.h>
#include <FlowSensor.h>
#define type YFS201
#define pin 36 
FlowSensor Sensor(type, pin);
unsigned long timebefore = 0; 
unsigned long reset = 0;

void IRAM_ATTR count()
{ Sensor.count();
}

char ssid[] = "";
char pass[] = "";

void setup()
{ Serial.begin(9600);
  Sensor.begin(count);  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{ Blynk.run();
  getFlow();
}

void getFlow()
{ if (millis() - timebefore >= 1000)
	{ Sensor.read();
		Serial.print("Flow rate (L/minute) : ");
		Serial.println(Sensor.getFlowRate_m());
		Serial.print("Volume (L) : ");
		Serial.println(Sensor.getVolume());
		timebefore = millis();
	}

	if (millis() - reset >= 60000)
	{ Sensor.resetVolume();
		reset = millis();
	}
}

