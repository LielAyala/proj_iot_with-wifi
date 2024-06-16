#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> 

IPAddress    apIP(55, 55, 55, 55); // כתובת IP מורכבת מ 4 ספרות בין 0 ל 255

const char* ssid = "myServerWifi"; //שם הרשת שיוצג
const char* password = "88888888";// הסיסמה לרשת אם נרצה להשתמש בה 
ESP8266WebServer server(80); 

void WifiSetup(){
 WiFi.mode(WIFI_AP_STA); // הגדר את כתובת ה-IP המותאמת אישית
 WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); // רשת משנה FF FF FF 00
 WiFi.softAP(ssid); /* אתה יכול להסיר את פרמטר הסיסמה אם אתה רוצה שה-AP יהיה פתוח. */
 // WiFi.softAP(ssid, password);
 server.on("/", handleRoot); // פרמטר ראשון מה הכתובת על השרת (כמו בנוד) הפרמטר השני מה יופעל
 server.onNotFound(handleNotFound); // מה קורה במידה ויש לי אנד פויינט שלא נמצא
 server.begin(); // מפעיל את הסרוור (מוציא לפועל את כל ההכנות)
}
//יוכנס לתוך לופ
void wifi_loop() {
  server.handleClient();// שואל את הסרוור אם מישהו פנה אליו
  delay(10);
} 
//פונק שמציגה שגיאה ברגע שמגיעים לאנדפויינט שלא נמצא 
void handleNotFound(){
  String message = "File Not Found \n \n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}
//מה שיקרה ברגע שנגיע ל/ באנדפויינט 
void handleRoot(){
  //בדיקה האם לחצו על הכפתור 
  if (server.hasArg("btn_pressed")) {
    //  MapDirובהתאם לכך מעדכן את  btn_pressed שואל מה המספר שיתקבל מ
    //אופציה1
    //MapDir = (server.arg("btn_pressed")=="1") ? 1 : 2;
    //אופציה 2
    MapDir = server.arg("btn_pressed").toInt();
  }
  

  char html[2000]="";
	strcat(html, "<html>");
	strcat(html, "<head>");
	strcat(html, "<meta charset=\"UTF-8\">");
	strcat(html, "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
	strcat(html, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
	strcat(html, "<META HTTP-EQUIV=\"refresh\" CONTENT=\"1\">");
	strcat(html, "<title>שיעור IOT</title>");
  //beginig of my css
  strcat(html, "<style>");
  // the css body 
  strcat(html, "body{");
  strcat(html, " justify-content: center;");
  strcat(html, " align-items: center;");
  strcat(html, "  background-color: yellow;");
  strcat(html, "  };");
  //the css for big number 
  strcat(html, "  .BigNumber{");
  strcat(html, "  font-size: 100px;;");
  strcat(html, "  width: 30px;");
  strcat(html, "  align-items: center;");
  strcat(html, "  justify-content: center;;");
  strcat(html, "  };");
  // THE END OF MY CSS 
  strcat(html, "</style>");
  //the end of the head
  strcat(html, "</head>");
  // beginig of the body 
  strcat(html, "<body>");
  strcat(html, "<h2>LDR value</h2>");
  // LdrVal is from main tab
  char strTmp[5];
  itoa(LdrVal,strTmp,10);
  //itoa מקבלת שלושה פרמטרים:
  //int value - המספר השלם אותו רוצים להמיר למחרוזת.
  //char []str - מצביע למערך תווים  שבו תישמר המחרוזת המתקבלת.
  //int base - הבסיס שבו רוצים לבצע את ההמרה (למשל: 10 לבסיס עשרוני, 2 לבסיס בינארי, 16 לבסיס הקסדצימלי וכדומה).
  strcat(html, "<div class=\"BigNumber\" id='LdrVal'>");
  strcat(html, strTmp);
  strcat(html, "</div>");

  strcat(html, "<form action='' method='get'>");
  strcat(html, "<button name='btn_pressed' value='1'>אור סינכרוני</button>");
  strcat(html, "<button name='btn_pressed' value='2'>אור הפוך</button>");
  strcat(html, "</form>");

  strcat(html, "<script>");
  strcat(html, "async function logMovies() {");
  strcat(html, "const response = await fetch('/GetValue');");
  strcat(html, "const movies = await response.json();");//{Ldr:13}
  strcat(html, "document.getElementById('LdrVal').innerHTML=movies.Ldr;");
  strcat(html, "}");
  strcat(html, "setInterval(logMovies, 1000)");

  strcat(html, "</script>");
  // the end of the body
  strcat(html, "</body>");
  // the end of my html documnet
 strcat(html, "</html>");

  server.send(200, "text/html", html);
}





