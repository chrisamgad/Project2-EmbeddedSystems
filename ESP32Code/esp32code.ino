#define led 2   
#define RXD2 16    //port number on ESP32 (GPIO16)
#define TXD2 17   //port number on ESP32  (GPIO17)
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>     // Include the WebServer library

float depth=0;
String text= "";  
const String page PROGMEM = "<head>"
            " <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js\"></script>"
            " </head>"
            " <body>"
            " <h1>Sensor to ESP32 Web Server</h1><span style=\"font-size:30px;\">Current Depth :</span> <span style=\"font-size:30px; \" id=\"depth\">""</span><span style=\"font-size:30px; \">cm</span>\r\n"
            " <script>\r\n"
            " $(document).ready(function(){\r\n"
            " setInterval(getData,1000);\r\n"
            " function getData(){\r\n"
            " $.ajax({\r\n"
            "  type:\"GET\",\r\n"
            "  url:\"data\",\r\n"
            "  success: function(data){\r\n"
            "  var s = data.split(\'-\');\r\n"
            "  $('#depth').html(s[0]);\r\n"
            "}\r\n"
            "}).done(function() {\r\n"
            "  console.log('ok');\r\n"
            "})\r\n"
            "}\r\n"
            "});"
            "</script>\r\n"
            "</body>";

WebServer server(80);    // Start the Serial communication to send messages to the computer
const char* ssid = "Te-data_EXT";   //SSID 
const char* password = "meshmeshh"; //password
//----------------------------------------------------------------
void setup()   // put your setup code here, to run once:
{
  Serial.begin(9600);      //Baud rate for UART2
  Serial2.begin(9600,SERIAL_8N1,RXD2,TXD2);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));
  pinMode(led,OUTPUT);
//ESP32 connects to your wifi -----------------------------------
  WiFi.mode(WIFI_STA); //Connect to your wifi
  WiFi.begin(ssid, password);

  Serial.println("Connecting to ");
  Serial.print(ssid);

  //Wait for WiFi to connect, scan for Wi-Fi networks, and connect to the strongest of the networks 
  while(WiFi.waitForConnectResult() != WL_CONNECTED)
  {      
      Serial.print(".");
  }    
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
//----------------------------------------------------------------
   server.on("/data", [](){ //This specifies what the server does when a client accesses the data page
     delay(200);    //delay for 200 
     text = (String)depth; //change Depth to string
     Serial.println(text); //print on serial
     server.send(200, "text/plain", text); //send this value to webserver
    }); 
   server.on("/", []() {    // This is the homepage
     server.send(200, "text/html", page);
    });  
  server.begin();                  //Start server
  Serial.println("HTTP server started");  
}
//----------------------------------------------------------------
void loop() 
{  
  while(Serial2.available()) //while we're receiving data through the uart from the STM32 board microcontroller
  { 
    depth=Serial2.parseFloat(); //converts the received depth into float
    Serial.println(depth);   //print the final result of the water depth
    server.handleClient();  // Listen for HTTP requests from clients
  }  
}
