v#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include<Wire.h>
const char* ssid = "Error:404";//Replace with your network SSID
const char* password = "etdu2614";//Replace with your network password
ESP8266WebServer server(80);
String page = "";
char input[12];
int count = 0;

int a;
int p1=0,p2=0,p3=0,p4=0;
int c1=0,c2=0,c3=0,c4=0;
double total = 0;
int count_prod = 0;
void setup()
{
  pinMode(D3,INPUT_PULLUP);
  pinMode(D4,OUTPUT);
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Wire.begin(D2, D1);
  Serial.print("   WELCOME TO       \n");
  Serial.print("   SMART CART       \n");
  delay(2000);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  Serial.print("WiFi Connecting...  \n");
  }
  Serial.print(WiFi.localIP());
  Serial.print("\nWiFi Connected\n");
  Serial.print(WiFi.localIP());
  delay(1000);
  
 
  Serial.print(" PLZ ADD ITEMS     ");
  Serial.print("    TO CART          ");
server.on("/", []()
  {
    page = "<html><head><title>E Cart using IoT</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  #3498db ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Smart Shopping Cart using IoT</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>ITEMS</th><th>QUANTITY</th><th>COST</th></tr><tr><td>Biscuit</td><td>"+String(p1)+"</td><td>"+String(c1)+"</td></tr>";
    page += "<tr><td>Soap</td><td>"+String(p2)+"</td><td>"+String(c2)+"</td></tr><tr><td>Rice(1KG)</td><td>"+String(p3)+"</td><td>"+String(c3)+"</td>";
    page += "</tr><tr><td>Tea(50g)</td><td>"+String(p4)+"</td><td>"+String(c4)+"</td></tr><tr><th>Grand Total</th><th>"+String(count_prod)+"</th><th>"+String(total)+"</th>";
    page += "</tr></table><br><a href=\"pay\" style=\"width:200px;height:40px; background-color:blue;color:white;  padding:10px 20px;\" >Pay Now</a> </center></body></html>";
    page += "<meta http-equiv=\"refresh\" content=\"2\">";
    server.send(200, "text/html", page);
  });
  server.on("/pay", [](){
    page = "<html><head><title>E Cart Payment</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  #3498db ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1> Payment Page</h1><br><br>";
    page += "<h2> Total Bill </h2><p> Rs." + String(total) + "</p>";
    page += "<input type=\"button\" name=\"Pay\" value=\"Pay\" style=\"width:200px;height:40px; background-color:green;color:white;  \" > ";
    page += "</center></body></html>";
    page += "<meta http-equiv=\"refresh\" content=\"2\">";
    server.send(200, "text/html", page);
  });
  server.begin();
}
void loop()
{
  int a=digitalRead(D3);
  if (Serial.available())
  {
    count = 0;
    while (Serial.available() && count < 12)
    {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    if (count == 12)
    {
      if ((strncmp(input, "7900844E3380", 12) == 0) && (a == 1))
      {
        Serial.print("Biscuit Added       ");
        Serial.print("Price(Rs):35.00      ");
        p1++;
        digitalWrite(D4,HIGH);
        delay(2000);
        total = total + 35.00;
        count_prod++;
        digitalWrite(D4,LOW);
      }
      else if (strncmp(input, "0B00292BADA4", 12) == 0)
      {
        Serial.print("Total Prod:");
        Serial.print(count_prod);
        Serial.print("Price:");
        Serial.print(total);
        
        digitalWrite(D4,HIGH);
        delay(2000);
        digitalWrite(D5,LOW);
        Serial.print("   Thank you        ");
        Serial.print("  for Shopping        ");
        digitalWrite(D4,LOW);
      }
    }
    c1=p1*35.00;
  }
server.handleClient();
}