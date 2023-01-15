#include <FastLED.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 143
#define DATA_PIN 21

int fadeamt       = 48;
int speed         = 200;
int NUM_RUN       = 12;
int NUM_SOL       = NUM_RUN;
int NUM_RINGS     = 6;
int beacon_light     = 0;
int party_light   = 0;
int party_spots   = 5;
int matrix_light  = 0;
int off_light     = 0;
int lantern_light = 0;
int blink_light   = 0;
 
const char* ssid     = "ELF";
const char* password = "Happyelf";

int blinkoff = 2500;
int blink    = 100;
int blinkstate = 0;
unsigned long remembertime = 0;

WiFiServer server(80);
CRGB leds[NUM_LEDS];


void setup() {
  
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  Clearall();
  Wifisetup();
   
}

void loop  () {
  
  Party    ();
  Beacon   ();
  Matrix   ();
  Lantern  ();
  Blink    ();
  Clearall ();
  Wifi     ();
  
 
}

void Blink() {

  if (blink_light == 1 ) {

  if (blinkstate == 1) 
  
  {
    FastLED.setBrightness(100);
    if( (millis() - remembertime) >= blinkoff) {
      fill_solid( &(leds[96]), 47, CRGB(255, 0, 0));
      FastLED.show();
      blinkstate = 0;
      remembertime = millis();

    }
  }
  else 
  {
    if( (millis() - remembertime) >= blink) {
      fill_solid( &(leds[96]), 47, CRGB(0, 0, 0));
      FastLED.show();
      blinkstate = 1;
      remembertime = millis();

    }
  }
}
}

void Matrix() {

              
               if (matrix_light == 1) {
                           
                FastLED.setBrightness(255);
                
                for (int spot = 0; spot < party_spots; spot++) {
                  
                  int spot_n = random(spot % 2, 72);
                  leds[spot_n - spot % 2, spot_n * 2 - spot % 2] = CRGB(0, 255, 0);
                  
                } 
                
                for (int fade = 0; fade < NUM_LEDS; fade++){
                  leds[fade] = leds[fade].fadeToBlackBy(fadeamt); 

                }
                
                FastLED.show();
                delay(50);
                
              }
    }

void Party() {

              
               if (party_light == 1) {                
    
                FastLED.setBrightness(255);
                
                
                for (int spot = 0; spot < party_spots; spot++) {
                  
                  int spot_n = random(spot % 2, 72);
                  leds[spot_n - spot % 2, spot_n * 2 - spot % 2] = CHSV(random8() , 255 , 255);
                  
                    } 
                
                for (int fade = 0; fade < NUM_LEDS; fade++){
                  leds[fade] = leds[fade].fadeToBlackBy(fadeamt);                      
                                
                }
                
                FastLED.show();
                delay(50);
                
               }
    }
   
  

void Beacon(){

  
         if (beacon_light == 1) { 

                        
        FastLED.setBrightness(100);

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

void Lantern(){

     if (lantern_light == 1 ) {

     FastLED.setBrightness(10);

     fill_solid(leds, NUM_LEDS, CRGB::White);

     FastLED.show();
  
  }
}

void Clearall(){

     if (off_light == 1 ) {

      FastLED.clear(true);
       
      off_light = 0;
  
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
            client.print("Click <a href=\"/Beacon\">here</a> to Turn Beacon on.<br>");
            client.print("Click <a href=\"/Party\">here</a> to Turn Party mode on.<br>");
            client.print("Click <a href=\"/Matrix\">here</a> to Turn Matrix mode on.<br>");
            client.print("Click <a href=\"/Blink\">here</a> to Turn Blink mode on.<br>");
            client.print("Click <a href=\"/Lantern\">here</a> to Turn Lantern on.<br>");
            client.print("Click <a href=\"/Off\">here</a> to Turn the Beacon OFF.<br>");

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
          if (currentLine.endsWith("GET /Beacon"))  { 
            
            beacon_light = 1;        
          
        }

          if (currentLine.endsWith("GET /Party"))  { 
            
             party_light = 1;        
          
        }

        if (currentLine.endsWith("GET /Matrix"))  { 
            
             matrix_light = 1;        
          
        }

        if (currentLine.endsWith("GET /Blink"))  { 
            
             blink_light = 1;        
          
        }
        
        if (currentLine.endsWith("GET /Lantern"))  { 
            
             lantern_light = 1;        
          
        }
        
                           
        if (currentLine.endsWith("GET /Off")) { 
            
            off_light     = 1;
            beacon_light     = 0;
            party_light   = 0;
            matrix_light  = 0;
            lantern_light = 0;
            blink_light   = 0; 
            
           
    }
   }
  }
 }
}
