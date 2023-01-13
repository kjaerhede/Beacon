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
int run_light     = 0;
int party_light   = 0;
int party_spots   = 5;
int matrix_light  = 0;
int off_light     = 0;
int lantern_light = 0;
int name_light    = 0;
 
const char* ssid     = "ELF";
const char* password = "Happyelf";

WiFiServer server(80);
CRGB leds[NUM_LEDS];

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(12, 7, DATA_PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

 int x    = matrix.width();


void setup() {
  
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  Clearall();
  Wifisetup();
   
}

void loop  () {

  Wifi     ();

   if(party_light == 1 ){
  Party();
  }

   if(run_light == 1 ) {
   Beacon();
 }

 if (matrix_light == 1 ){
   Matrix();
 }

 if (lantern_light == 1 ) {
   Lantern();
 }

  if(name_light == 1) {
    Name();

  }

  if(off_light == 1) {
   Clearall();
  }
  
  // Party    ();
  // Beacon   ();
  // Matrix   ();
  // Lantern  ();
  // Name     ();
  // Clearall ();
  // Wifi     ();
  
 
}


void Matrix() {

              
              // if (matrix_light == 1) {
                           
                FastLED.setBrightness(255);
                
                for (int spot = 0; spot < party_spots; spot++) {
                  
                  int spot_n = random(spot % 2, 72);
                  leds[spot_n - spot % 2, spot_n * 2 - spot % 2] = CRGB::Green;
                  
                } 
                
                for (int fade = 0; fade < NUM_LEDS; fade++){
                  leds[fade] = leds[fade].fadeToBlackBy(fadeamt); 

                }
                
                FastLED.show();
                delay(50);
                
              //}
    }

void Party() {

              
              // if (party_light == 1) {                
    
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
                
              // }
    }
   
  

void Beacon(){

  
        // if (run_light == 1) { 

        //off_light = 0;  

        FastLED.setBrightness(100);

        fill_solid( &(leds[0]),                              NUM_SOL, CRGB(255, 0, 0));
        fill_solid( &(leds[0+NUM_SOL*NUM_RINGS+NUM_SOL]),    NUM_SOL, CRGB(255, 0, 0));
        //fill_solid( &(leds[96]),                                  47, CRGB(255, 0, 0));
        
              
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
  //}
  
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

    // if (lantern_light == 1 ) {

      //off_light = 0;

     FastLED.setBrightness(10);

     fill_solid(leds, NUM_LEDS, CRGB::White);

     FastLED.show();
  
  //}
}

void Clearall(){

    // if (off_light == 1 ) {

      FastLED.clear(true);
           
    //  matrix.fillScreen(0);
    //  matrix.Color(0, 0, 0);
   
    //matrix.clear();
    //matrix.show();

    off_light = 0;
  
  //}
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
            client.print("Click <a href=\"/M\">here</a> to Turn Matrix mode on.<br>");
            client.print("Click <a href=\"/N\">here</a> to Turn Name mode on.<br>");
            client.print("Click <a href=\"/L\">here</a> to Turn Lantern on.<br>");
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

        if (currentLine.endsWith("GET /M"))  { 
            
             matrix_light = 1;        
          
        }

        if (currentLine.endsWith("GET /N"))  { 
            
             name_light = 1;        
          
        }
        
        if (currentLine.endsWith("GET /L"))  { 
            
             lantern_light = 1;        
          
        }
        
                           
        if (currentLine.endsWith("GET /O")) { 
            
            off_light     = 1;
            run_light     = 0;
            party_light   = 0;
            matrix_light  = 0;
            lantern_light = 0;
            name_light    = 0; 
            
           
    }
   }
  }
 }
}


void Name(){

   //int x    = matrix.width();

    // if (name_light == 1) { 

     
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
 
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(F("JENSENS"));
  matrix.Color(255, 255, 255);

  if(--x < -50) {
    x = matrix.width();

  }

  matrix.show();
  delay(150);
  
  //}
//}
}
