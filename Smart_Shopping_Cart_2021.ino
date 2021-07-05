#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>

#include <LiquidCrystal.h>

const int RS = 4, EN = 0, d4 = 14 , d5 = 12, d6 = 13, d7 = 15;
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

const char* ssid = "Enter wifi name ";//Replace with your network SSID
const char* password = "Enter Wifi Password";//Replace with your network password
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
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  pinMode(D1,INPUT_PULLUP); //delete
  pinMode(D0,OUTPUT); //buzzer and led green

  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO       ");
  lcd.setCursor(0, 1);
  lcd.print("   SMART CART       ");
  delay(4000);
  lcd.clear();

  while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connecting...  ");
  Serial.println(".");
  
  }
  lcd.clear();
  Serial.println("Wifi Connected....");
  Serial.println(WiFi.localIP());
  
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(30000);
  
  Serial.println("PLZ ADD ITEMS TO CART");
  
  lcd.setCursor(0, 0);
  lcd.print(" PLZ ADD ITEMS     ");
  lcd.setCursor(0, 1);
  lcd.print("    TO CART          ");

server.on("/",[](){

page="<!DOCTYPE html>\n<html>\n<head>\n\t<title>NIRVANA GUITAR SHOP</title>\n\t<style type=\"text/css\">\n\tbody{\n\t\tbackground-color: #99ccff;\n\t\tbackground-image: url(\"https://www.onesiam.com/uploads/b_content_01557995721.jpg\");\n\t\tbackground-repeat: no-repeat;\n\t\tbackground-size: cover;\n\t}\n\ttable, td, th\n\t\t{\n  \t\tborder: 1px solid black;\n\t\ttext-align: center;\n\t\tfont-size: 20px;\n\t\t}\n\t\tth\n\t\t{\n\t\t\tbackground-color: blue;\n\t\t\tcolor: white;\n\t\t\tfont-size: 25px;\n\t\t}\n\t\ttable\n\t\t{\n\t\t\twidth: 50%;\n  \t\tborder-collapse: collapse;\n\t\t\tfont-family: \"Times New Roman\", Times, serif;\n\t\t\t}\n\t\t\ttable.center\n\t\t\t{\n\t\t\t\tmargin-left: auto;\n  \t\t\tmargin-right: auto;\n\t\t\t}\n\t\t\th1{\n\t\t\t\ttext-align: center;\n\t\t\t\tfont-size: 40px;\n\t\t\t\tcolor: #ffff00;\n\t\t\t\tfont-family: \"Times New Roman\", Times, serif;\n\t\t\t}\n\t\t\t.button_sub{\n\t\t\t\tmargin: auto;\n  \t\t\twidth: 10%;\n  \t\t\tpadding: 10px;\n\t\t\t\t\t\t\t}\n\t\t\t.button{\n\t\t\t\tbackground-color: #3399ff;\n\t\t\t\tcolor: white;\n\t\t\t\ttext-align: center;\n\t\t\t\tcursor: pointer;\n\t\t\t\tfont-size: 20px;\n\t\t\t\tborder-radius: 12px;\n\t\t\t\ttransition-duration: 0.4s;\n\t\t\t\tfont-family: \"Times New Roman\", Times, serif;\n\t\t\t}\n\t\t\t.button:hover {\n  \t\t\tbackground-color: #4CAF50;\n  \t\t\tcolor: white;\n\t\t\t\t}\n\t\t\t\tp{\n\t\t\t\t\ttext-align: center;\n\t\t\t\t\tfont-size: 20px;\n\t\t\t\t\tcolor: #000066;\n\t\t\t\t\tfont-family: \"Times New Roman\", Times, serif;\n\t\t\t\t\tfont-weight: bold;\n\t\t\t\t}\n\t\t\t\t.Submit-message{\n\t\t\t\t\tbackground-color:inherit ;\n\t\t\t\t\tmargin: auto;\n\t  \t\t\twidth: 30%;\n\t\t\t\t\tborder-radius: 20px;\n\t\t\t\t}\n\t\t\t\t#billno{\n\t\t\t\t\tfont-size: 20px;\n\t\t\t\t\tcolor: #000066;\n\t\t\t\t\tfont-family: \"Times New Roman\", Times, serif;\n\t\t\t\t\tfont-weight: bold;\n\t\t\t\t}\n\t</style>\n</head>\n<body>\n\t<h1>NIRVANA GUITAR SHOP </h1>\n\t<p id=\"billno\"></p>\n\t<table class=\"center\">\n\t\t<tr>\n\t\t\t<th>ITEMS</th>\n\t\t\t<th>QUANTITY</th>\n\t\t\t<th>COST</th>\n\t\t</tr>\n\t\t<tr>\n\t\t\t<td>Dunlop Picks</td>\n\t\t\t<td>"+String(p1)+"</td>\n\t\t\t<td>"+String(c1)+"</td>\n\t\t</tr>\n\t\t<tr>\n\t\t\t<td>Ernie Strings</td>\n\t\t\t<td>"+String(p2)+"</td>\n\t\t\t<td>"+String(c2)+"</td>\n\t\t</tr>\n\t\t\t<tr><td>Fender Capo</td>\n\t\t\t\t<td>"+String(p3)+"</td>\n\t\t\t<td>"+String(c3)+"</td></tr>\n\t\t\t<tr><td>Guitar Strap</td>\n\t\t\t\t<td>"+String(p4)+"</td>\n\t\t\t<td>"+String(c4)+"</td></tr>\n\t\t\t\t<tr>\n\t\t\t\t\t<th>Total</th>\n\t\t\t\t\t<th>"+String(count_prod)+"</th>\n\t\t\t\t\t<th>"+String(total)+"</th>\n\t\t\t\t</tr>\n\t</table>\n\t<div class=\"button_sub\">\n\t\t<button type=\"submit\" name=\"submit\" class=\"button\" onclick=\"myFunction()\">Submit Bill</button>\n\t</div>\n\t<div class=\"Submit-message\">\n\t\t<p id=\"counter_no\"></p>\n\t\t<p id=\"message\"></p>\n\t</div>\n\t<script type=\"text/javascript\">\nfunction myFunction() {\n\tvar x = Math.floor((Math.random() * 15) + 1);\n\tvar bill_no = Math.floor((Math.random() * 1000000000000000) + 752318);\n  document.getElementById(\"counter_no\").innerHTML = \"Checkout At Counter Number:\"+x;\n\tdocument.getElementById(\"message\").innerHTML = \"Thank You For Shopping! Visit Again!\";\n\tdocument.getElementById(\"billno\").innerHTML = \"Invoice Number: \"+\"#\"+bill_no;\n}\n</script>\n</body>\n</html>\n";    
server.send(200, "text/html", page);
  });
  
  server.begin();
  Serial.println("Web server started!");
 
  
}
void loop()
{
  int a=digitalRead(D1);
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
      if ((strncmp(input, "30004F5B5E7A", 12) == 0) && (a == 1))
      {
        Serial.println("Picks Added : Rs. 300");

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Picks Added");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):300/-");
        p1++;
        digitalWrite(D0,HIGH);
        delay(300);
        total = total + 300.00;
        count_prod++;
        digitalWrite(D0,LOW);
        delay(3000);
        lcd.clear();
      }
      else if ((strncmp(input, "30004F5B5E7A", 12) == 0) && (a == 0))
      {
        if(p1>0)
        {
        Serial.println("Picks Removed");
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Picks Removed!!! ");
        digitalWrite(D0,HIGH);
        delay(500);
        p1--;
        total = total - 300.00;
        count_prod--;
        digitalWrite(D0,LOW);
        delay(3000);
        lcd.clear();
        
        
        }
        else
        {
        Serial.println("Not in Cart");
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!");
        digitalWrite(D0,HIGH);
        delay(500);
        digitalWrite(D0,LOW);
        delay(3000);
        lcd.clear();
        }
      }
      else if ((strncmp(input, "300050E00D8D", 12) == 0) && (a == 1))
      {
        Serial.println("Strings Added : Rs. 400/-");

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Strings Added ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):400/- ");
        total = total + 400.00;
        digitalWrite(D0,HIGH);
        delay(300);
        p2++;
        count_prod++;
        digitalWrite(D0,LOW);
        delay(3000);
        lcd.clear();
      }
      else if ((strncmp(input, "300050E00D8D", 12) == 0) && (a == 0))
      {
         if(p2>0)
        {
        Serial.println("Strings Removed");
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Strings Removed!!! ");
        digitalWrite(D0,HIGH);
        delay(500);
        p2--;
        total = total - 400.00;
        count_prod--;
        digitalWrite(D0,LOW);
        delay(3000);
        lcd.clear();
        
        }
        else
        {
        Serial.println("Not in Cart");
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!! ");
        digitalWrite(D0,HIGH);
        delay(500);
        digitalWrite(D0,LOW);
        delay(3000);
        lcd.clear();
        
        }
      }
      else if ((strncmp(input, "3000506ECBC5", 12) == 0) && (a == 1))
      {
        Serial.println("Capo Added: Rs. 500");
        
        lcd.setCursor(0, 0);
        lcd.print("Fender Capo Added ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):500/- ");
        total = total + 500.00;
        digitalWrite(D0,HIGH);
        delay(300);
        count_prod++;
        p3++;
        digitalWrite(D0,LOW);
        delay(3000);
        lcd.clear();
  
      }
      else if ((strncmp(input, "3000506ECBC5", 12) == 0) && (a==0))
      {
        if(p3>0)
        {
        Serial.println("Fender Capo Removed");
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Fender Capo Removed!!! ");
        digitalWrite(D0,HIGH);
        delay(500);
        total = total - 500.00;
        p3--;
        count_prod--;
        digitalWrite(D0,LOW);
        delay(3000);
        lcd.clear();
        }
        else
        {
        Serial.println("Not in Cart");
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!! ");
        digitalWrite(D0,HIGH);
        delay(500);
        digitalWrite(D0,LOW);
        delay(3000);
        lcd.clear();
        
        }
      }
      else if ((strncmp(input, "30004F5B6743", 12) == 0) && (a == 1))
      {
        Serial.println("Strap Added: Rs. 900");
        
        lcd.setCursor(0, 0);
        lcd.print("Strap  Added ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs): 900/- ");
        total = total + 900.00;
        count_prod++;
        digitalWrite(D0,HIGH);
        delay(300);
        p4++;
        digitalWrite(D0,LOW);
        delay(3000);
        lcd.clear();
        
      }
      else if ((strncmp(input, "30004F5B6743", 12) == 0) && (a == 0))
      {
        if(p4>0)
        {
        Serial.println("Strap Removed");
        
        lcd.clear();
        total = total - 900.00;
        lcd.setCursor(0, 0);
        count_prod--;
        p4--;
        lcd.print("Strap Removed!!! ");
        digitalWrite(D0,HIGH);
        delay(500);
        digitalWrite(D0,LOW);
        delay(3000);
        lcd.clear();
        }
        else
        {
        Serial.println("Not in Cart");
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!! ");
        digitalWrite(D0,HIGH);
        delay(500);
        digitalWrite(D0,LOW);
        delay(3000);
        lcd.clear();
        
        }
      }
      else if (strncmp(input, "30004F5B684C", 12) == 0)
      {
        Serial.print("Total Prod: ");
        Serial.print(count_prod);
        Serial.println("Price ");
        Serial.print(total);
        Serial.println(" Thank You for shopping");
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Total Prod: "); 
        lcd.setCursor(11, 0);
        lcd.print(count_prod);
        lcd.setCursor(0, 1);
        lcd.print("Price: ");
        lcd.setCursor(6, 1);
        lcd.print(total);
        
        digitalWrite(D0,HIGH);
        delay(200);
        digitalWrite(D0,LOW);
        delay(20);
        digitalWrite(D0,HIGH);
        delay(200);
        digitalWrite(D0,LOW);
        delay(10000);
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("   Thank you  ");
        lcd.setCursor(0, 1);
        lcd.print("  for Shopping   ");
        delay(10000);
      }
    }
    c1=p1*300.00;
    c2=p2*400.00;
    c3=p3*500.00;
    c4=p4*900.00;
  }
 
server.handleClient();
}
