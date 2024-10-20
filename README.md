## 🌱 Installation
- Ngrok
- Diaglogflow
- Visual Stdio Code
- Google Assistant
- Arduino Code

## 🍓 Preparation
Change id and pass of wifi in ```IOT.ino``` file

## 🚀 Running
```python
# Control via Web Sever
- Run IOT.ino
- Run http://192.168.2.3/ (http://192.168.2.3/ is Esp8266 IP)

# Control via Google Assistant
- Change Esp8266 IP in javascript ```app.js``` file

- Run in Terminal of app.js:
npm test

- Create intent and intergration of google assistant on dialogflow

- Command Prompt
ngrok
ngrok http 8050

-> Forwarding https://b926-171-224-179-200.ngrok.io -> h
Copy https://b926-171-224-179-200.ngrok.io to fulfillment webhook of dialogflow
``` 
