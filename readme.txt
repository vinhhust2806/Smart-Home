Các thư viện và phần mềm cần thiết :

- Phần mềm ngrok
- Nền tảng thực thi code javascript ( visual stdio code, .. )
- Diaglogflow
- Google assistant
- Phần mềm arduino code ( chúng tôi sử dụng 1.8.19 ) bao gồm các thư viện : 

Code gồm 2 file chính :

- File arduino IOT.ino chứa code giao diện websever và điều khiển các các thiết bị thông qua esp8266 
- File javascript app.js chạy backends xử lý điều khiển thông qua google assistant

Phần 1.

Điều khiển thông qua giao diện websever :

- Bước 1 : 
+ Thay đổi tên và mật khẩu wifi tương ứng muốn kết nối trong file arduino IOT.ino
+ Nạp code arduino cho esp8266

Ví dụ như wifi chúng tôi sử dụng :
char* ssid = "P305";                 # khai báo tên wifi
char* pass = "0396482815";           # khai báo pass wifi 

- Bước 2 : 
+ Lấy IP của Esp8266 sau khi đã kết nối vào wifi qua Serial Monitor

Ví dụ IP Esp8266 của chúng tôi : 192.168.2.3

+ Chạy web brower bằng http://192.168.2.3/ để đi tới giao diện websever, thực hiện điều khiển thông qua websever

Nếu muốn thực hiện điều khiển bằng điện thoại, yêu cầu diện thoại cũng kết nối tới wifi đó để có thể giao tiếp với websever

Phần 2.

Điều khiển bằng google assistant :

- Bước 1 : 
+ Sửa khai báo ip_add theo IP Esp8266 của bạn trong code javascript app.js
Ví dụ khai báo của chúng tôi :
var ip_add = "http://192.168.2.3/";

+ Chạy code javascript app.js băng dòng lệnh sau trên terminal :
npm test

- Bước 2 :
+ Tạo intent và intergration để tạo các action của google assistant lên dialogflow

- Bước 3 :
+ Truy cập command prompt của máy

+ Thực hiện lần lượt các dòng lệnh sau :
ngrok
ngrok http 8050

+ Copy địa chỉ global
Ví dụ của chúng tôi :
Forwarding                    https://b926-171-224-179-200.ngrok.io -> h

+ Copy địa chỉ https://b926-171-224-179-200.ngrok.io lên fulfillment webhook của dialogflow
+ Save lại
+ Bây giờ, bạn có thể điều khiển thông qua google assistant dựa vào các intent bạn tự tạo

