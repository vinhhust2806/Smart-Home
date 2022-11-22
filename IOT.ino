#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#include <Servo.h>

DHT dht(D7, DHT11);
ESP8266WebServer webServer(80);
Servo se;
char* ssid = "P305";
char* pass = "0396482815";
//=========Biến chứa mã HTLM Website==//
const char MainPage[] PROGMEM = R"=====(
  <!DOCTYPE html> 
  <html>
   <head> 
  
       <title>IOT Nhóm 2</title> 
       <style> 
          body {text-align:center;}
          .trongnha { 
    height: 280px;
    width: 500px;
    background: #27d4af;
    position: fixed;
    top: 55%;
    left: 50%;
    border-radius: 50px;
    margin-top: -250px;
    margin-left: 00px;
  }
  
  .Ngoaisan { 
    height: 220px;
    width: 500px;
    background: #27d4af;
    position: fixed;
    top: 55%;
    left: 50%;
    border-radius: 50px;
    margin-top: 50px;
    margin-left: 00px;
  }
  .otrangthai { 
    height: 400px;
    width: 500px;
    background: #27d4af;
    position: fixed;
    top: 55%;
    left: 50%;
    border-radius: 50px;
    margin-top: -200px;
    margin-left: -600px;
  }
  
 
  .button {
    background-color: #4CAF50; /* Green */
    border: none;
    color: white;
    padding: 6px 12px;
    border-radius: 50px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 12px;
    margin: 4px 2px;
    -webkit-transition-duration: 0.4s; /* Safari */
    transition-duration: 0.4s;
    cursor: pointer;
  }

  .button1 {
    background-color: rgb(255, 0, 0); 
    color: yellow; 
  }

  .button1:hover {
    background-color: yellow;
    color: red;
  }

  .button3 {
    background-color: rgb(0, 255, 21); 
    color: rgb(255, 0, 0); 
  }

  .button3:hover {
    background-color: #0400ff;
    color: yellow;
  }
  .button2 {
    background-color: rgb(0, 255, 21); 
    color: rgb(255, 0, 0); 
  }

  .button2:hover {
    background-color: #0400ff;
    color: yellow;
  }
  .button5 {
    background-color: rgb(204, 0, 255); 
    color: rgb(0, 255, 21); 
  }

  .button5:hover {
    background-color: #0c00f7;
    color: white;
  }
  .button7 {
    background-color: rgb(0, 255, 21); 
    color: rgb(255, 0, 0); 
  }

  .button7:hover {
    background-color: #0400ff;
    color: yellow;
  }

       </style>
       <meta charset="UTF-8">
   </head>
   <body> 
     <h1>Chào mừng đến với hệ thống điều khiển nhà bạn</h1> 
     <div class="trongnha">

     <center>
        <h2 style="font-family: Helvetica;color: rgb(0, 0, 0);">Trong nhà</h2>
       <form action="" method="get">
        
      
      <button type="button" onclick="getdata('onD1')" class="button button1" ><h4 <strong>Bật Đèn<strong></h4></button>
      <button type="button" onclick="getdata('offD1')" class="button button3" ><h4 <strong>Tắt đèn<strong></h4></button>
    
        <br>
      
      <button type="button" onclick="getdata('onD0')" class="button button1" ><h4 <strong>Bật Quạt<strong></h4></button>
      <button type="button" onclick="getdata('offD0')" class="button button3" ><h4 <strong>Tắt Quạt<strong></h4></button>
    
        </form>
    <br><br>
   </div>
   <div class="Ngoaisan">


   <center>
      <h2 style="font-family: Helvetica;color: rgb(0, 0, 0);"><h4<strong>Ngoài sân<strong></h2>
      
      <button type="button" onclick="getdata('onD2')" class="button button1" ><h4 <strong>Bật đèn<strong></h4></button>
      <button type="button" onclick="getdata('offD2')" class="button button3" ><h4 <strong>Tắt Đèn<strong></h4></button>
    
      <br>
      <br>
      <button type="button" onclick="getdata('onD3')" class="button button1" ><h4 <strong>Mở cửa<strong></h4></button>
      <button type="button" onclick="getdata('offD3')" class="button button3" ><h4 <strong>Đóng cửa<strong></h4></button>   
          <br>
          <!--
          <textarea rows="1" id="logger" class="ip" placeholder="Trạng thái" readonly></textarea>

          -->
      </form>
  
    </div>
    <body bgcolor="FFB6C1">
    <div class="otrangthai">
    <strong><h2 style="font-family: Helvetica;color: rgb(0, 0, 0);">Trạng thái</h2><strong>
  <left>
     <button type="button"  class="button button2" ><strong><h4 style="font-family: Helvetica;color: rgb(0, 0, 0);">Nhiệt độ: <b><pan id="temperature"><pan></b></h4><strong></button>
     <button type="button"  class="button button2" ><strong><h4 style="font-family: Helvetica;color: rgb(0, 0, 0);">Độ ẩm:  <b><pan id="humidity"><pan></b></h4><strong></button><br>
     <button type="button"  class="button button2" ><strong><h4 style="font-family: Helvetica;color: rgb(0, 0, 0);"> Quạt: <b><pan id="trangthaiquat"><pan></b></h4><strong></button><br>
     <button type="button"  class="button button2" > <strong><h4 style="font-family: Helvetica;color: rgb(0, 0, 0);">Đèn trong nhà:  <b><pan id="trangthaiD1"><pan></b><strong></button><br>
     <button type="button"  class="button button2" > <strong><h4 style="font-family: Helvetica;color: rgb(0, 0, 0);">Đèn ngoài sân: <b><pan id="trangthaiD2"><pan></b></h4><strong></button><br>
     <button type="button"  class="button button2" ><strong><h4 style="font-family: Helvetica;color: rgb(0, 0, 0);"> Cửa: <b><pan id="trangthaiD3"><pan></b></h4><strong></button>
    <br>
   
  </div>
      <script>
        //-----------Tạo đối tượng request----------------
        function create_obj(){
          td = navigator.appName;
          if(td == "Microsoft Internet Explorer"){
            obj = new ActiveXObject("Microsoft.XMLHTTP");
          }else{
            obj = new XMLHttpRequest();
          }
          return obj;
        }
        var xhttp = create_obj();
        //-----------Thiết lập dữ liệu và gửi request-------
        function getdata(url){
          xhttp.open("GET","/"+url,true);
          xhttp.onreadystatechange = process;//nhận reponse 
          xhttp.send();
        }
        //-----------Kiểm tra response--------------------
        function process(){
          if(xhttp.readyState == 4 && xhttp.status == 200){
            //------Updat data sử dụng javascript----------
            ketqua = xhttp.responseText; 
            document.getElementById("reponsetext").innerHTML=ketqua;       
          }
        }
        //------------Kiểm tra trạng thái chân D1 D2------
        function getstatusD1D2(){
          xhttp.open("GET","getstatusD1D2",true);
          xhttp.onreadystatechange = process_json;
          xhttp.send();
        }
        //-----------Kiểm tra response-------------------------------
        function process_json(){
          if(xhttp.readyState == 4 && xhttp.status == 200){
            //------Update data sử dụng javascript-------------------
            var trangthaiD1D2_JSON = xhttp.responseText;
            var Obj = JSON.parse(trangthaiD1D2_JSON);
            document.getElementById("trangthaiquat").innerHTML = Obj.D0;
            document.getElementById("trangthaiD1").innerHTML = Obj.D1;
            document.getElementById("trangthaiD2").innerHTML = Obj.D2;
            document.getElementById("trangthaiD3").innerHTML = Obj.D3;
            document.getElementById("temperature").innerHTML = Obj.temperature;
            document.getElementById("humidity").innerHTML = Obj.humidity;
          }
        }
        //---Ham update duu lieu tu dong---
        setInterval(function() {
          getstatusD1D2();
        }, 1000);
      </script>
   </body> 
  </html>
)=====";
//=========================================//
void setup() {
  se.attach(D4); 
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D0,OUTPUT);
  pinMode(D3,OUTPUT);
   pinMode(D5,OUTPUT);
  digitalWrite(D5,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D0,LOW);
  digitalWrite(D1,LOW);
  digitalWrite(D2,LOW);
  
  WiFi.begin(ssid,pass);
  Serial.begin(9600);
  dht.begin();
  Serial.print("Connecting");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print("...");
  }
  Serial.println(WiFi.localIP());

  webServer.on("/",mainpage);
  webServer.on("/onD0",batquat);
  webServer.on("/offD0",tatquat);
  webServer.on("/onD3",mocua);
  webServer.on("/offD3",dongcua);
  webServer.on("/onD1",batden1);
  webServer.on("/offD1",tatden1);
  webServer.on("/onD2",batden2);
  webServer.on("/offD2",tatden2);
  webServer.on("/temperature",temperature);
  webServer.on("/humidity",humidity);
  webServer.on("/getstatusD1D2",get_statusD1D2);
  webServer.begin();
}
void loop() {
  webServer.handleClient();
}
//==========Chương trình con=================//
void mainpage(){
  String s = FPSTR(MainPage);
  webServer.send(200,"text/html",s);
}
void temperature(){
  float t = dht.readTemperature();
  webServer.send(200,"text/html",String(t,1));
}
void humidity(){
  float h = dht.readHumidity();
  webServer.send(200,"text/html",String(h,1));
}
void batquat(){
  digitalWrite(D2,HIGH);
   String trangthai="{\"FAN\": \"ON\"}";
  webServer.send(200,"application/json",trangthai);
}
void tatquat(){
  digitalWrite(D2,LOW);
   String trangthai="{\"FAN\": \"OFF\"}";
  webServer.send(200,"application/json",trangthai);
}
void tatden1(){
  digitalWrite(D1,LOW);
   digitalWrite(D3,LOW);
    String trangthai="{\"LED1\": \"OFF\"}";
     webServer.send(200,"application/json",trangthai);
}
void batden1(){
  digitalWrite(D1,HIGH);
    digitalWrite(D3,HIGH);
    String trangthai="{\"LED1\": \"ON\"}";
  webServer.send(200,"application/json",trangthai);
}
void tatden2(){
  digitalWrite(D0,LOW);
   String trangthai="{\"LED2\": \"OFF\"}";
    webServer.send(200,"application/json",trangthai);
}
void batden2(){
  digitalWrite(D0,HIGH);
   String trangthai="{\"LED2\": \"ON\"}";
  webServer.send(200,"application/json",trangthai);
}
void dongcua(){
 digitalWrite(D5,LOW);
  String trangthai="{\"DOOR\": \"CLOSE\"}";
  se.write(0); 
   webServer.send(200,"application/json",trangthai);
}
void mocua(){
  digitalWrite(D5,HIGH);
   String trangthai="{\"DOOR\": \"OPEN\"}";
  se.write(180); 
   webServer.send(200,"application/json",trangthai);

}
void get_statusD1D2(){
  String d1,d2,d3,d0,d4,d5;
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  d5=String(t,1);
  d4=String(h,1);
  if(digitalRead(D2)==1){
    d0 = " Đang quay";
  }else{
    d0 = "Đang tắt";
  }
  if(digitalRead(D5)==1){
    d3 = "Đang mở";
  }else{
    d3 = "Đang đóng";
  }
  if(digitalRead(D1)==1){
    d1 = "Đang sáng";
  }else{
    d1 = "Đang tắt";
  }
  if(digitalRead(D0)==1){
    d2 = "Đang sáng";
  }else{
    d2 = "Đang tắt";
  }
  String s = "{\"D0\": \""+ d0 +"\",\"D1\": \""+ d1 +"\",\"D2\": \""+ d2 +"\",\"D3\": \""+ d3 +"\",\"temperature\": \""+ d5 +"\",\"humidity\": \""+ d4 +"\"}";
  webServer.send(200,"application/json",s);
}
