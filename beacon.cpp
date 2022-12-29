#include <FastLED.h>
#include <WiFi.h>

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 108
#define DATA_PIN 21

int fadeamt = 48;
int speed = 200;
int NUM_RUN = 12;
int NUM_SOL = NUM_RUN;
int NUM_RINGS = 7;
int run_light = 0;
int party_light = 0;
int party_spots = 3;
 
const char* ssid     = "ELF";
const char* password = "Happyelf";

WiFiServer server(80);
CRGB leds[NUM_LEDS];

void setup() {
  
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  Clearall();
  Wifisetup();
 
}

void loop() {

  Party();
  Beacon();
  Clearall();
  Wifi();
 
}

  void Party() {

              if (party_light == 1) {
                
                unsigned long StartTime = millis();
                
                for (int spot = 0; spot < party_spots; spot++) {
                  
                  int spot_n = random(spot, 54);
                  leds[spot_n - spot, spot_n*2 - spot] = CHSV(random8() , 255 , 255);
           
                for (int fade = 0; fade < NUM_LEDS; fade++)
                  leds[fade] = leds[fade].fadeToBlackBy(fadeamt);                      
                
                unsigned long CurrentTime = millis();
                unsigned long ElapsedTime = CurrentTime - StartTime;
                Serial.print(ElapsedTime);
               
                
                FastLED.show();
                delay(50);
                }
              }
    }
   
  

void Beacon(){
  
      if (run_light == 1) {   

        fill_solid( &(leds[0]),                              NUM_SOL, CRGB(255, 0, 0));
        fill_solid( &(leds[0+NUM_SOL*NUM_RINGS+NUM_SOL]),    NUM_SOL, CRGB(255, 0, 0)); 

              
      for (int dot1 = 0; dot1 < NUM_RUN; dot1++) {
       for (int iteration = 0; iteration < NUM_RINGS; iteration++) {
       int led_num = dot1 + NUM_RUN * iteration;
       leds[NUM_SOL + led_num] = CRGB(255, 255, 255);

    }
      
    FastLED.show();
    
    delay(speed);
    
     for (int iteration = 0; iteration < NUM_RINGS; iteration++) {
      int led_num = dot1 + NUM_RUN * iteration;
      leds[NUM_RUN + led_num ] = CRGB(35, 35, 35  );
    }
    
    for (int iteration = 0; iteration < NUM_RINGS; iteration++) {
      int led_num = dot1 + NUM_RUN * iteration;
      if(dot1 > 0) leds[NUM_RUN + led_num - 1] = CRGB(10, 10, 10 );
      else if(dot1 + iteration == 0) leds[NUM_RUN + NUM_RUN * NUM_RINGS - 1] = CRGB(10, 10, 10);
      else leds[NUM_RUN + led_num - 1] = CRGB(10, 10, 10);
    }
    
    for (int iteration = 0; iteration < NUM_RINGS; iteration++) {
      int led_num = dot1 + NUM_RUN * iteration;
      if(dot1 > 1 || iteration > 0) leds[NUM_RUN + led_num - 2] = CRGB::Black;
      else if(dot1 == 1 && iteration == 0) leds[NUM_RUN + NUM_RUN * NUM_RINGS - 1] = CRGB::Black;
      else if(dot1 + iteration < 2) leds[NUM_RUN + NUM_RUN * NUM_RINGS - 2] = CRGB::Black;
      else leds[NUM_RUN + led_num - 2] = CRGB::Black;
    }
  }
  }
  
}

void Wifisetup(){ 

    delay(10);   // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

void Clearall(){

    if (run_light == 0 && party_light == 0) {

     fill_solid(leds, NUM_LEDS, CRGB::Black);

     FastLED.show();
  
  }
}

void Wifi(){ 
  
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/B\">here</a> to Turn Beacon on.<br>");
            client.print("Click <a href=\"/P\">here</a> to Turn Party mode on.<br>");
            client.print("Click <a href=\"/O\">here</a> to Turn the Beacon OFF.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

              // Check to see if the client request was "GET /H" or "GET /L":
          if (currentLine.endsWith("GET /B"))  { 
            
            run_light = 1;        
          
        }

          if (currentLine.endsWith("GET /P"))  { 
            
             party_light = 1;        
          
        }
        
                           
        if (currentLine.endsWith("GET /O")) { 
          
            run_light = 0;
            party_light = 0;

            
           
    }
   }
  }
 }
}

  
