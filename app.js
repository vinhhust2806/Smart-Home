//Use app in strict mode
'use strict';

//Using actions on google library
const {
  dialogflow,
} = require('actions-on-google');

//Using expressjs
var express = require('express');
var bodyParser = require('body-parser');
var cors = require('cors');
var request = require("request");

const app = dialogflow({debug: true});
var expressApp = express();

var ip_add = "http://192.168.2.3/";

var url;



expressApp.use(bodyParser());
expressApp.use(bodyParser.json()); 
expressApp.use(cors());

expressApp.post('/fulfillment', app);


app.intent('devicecontrol', (conv,{devicename,devicestatus}) => {
    // speech = "I got "+lednumber+" and "+status;
    var device_name = devicename;
    var device_status = devicestatus;
     if(device_name == "fan" && device_status == "on"){
         url = "onD0";
     }
     else if(device_name == "fan" && device_status == "off"){
         url = "offD0";
     }
     else if(device_name == "indoor light" && device_status == "on"){
         url = "onD1";
     }
     else if(device_name == "indoor light" && device_status == "off"){
         url = "offD1";
     }
     else if(device_name == "outdoor light" && device_status == "on"){
            url = "onD2";
        }
     else if(device_name == "outdoor light" && device_status == "off"){
            url = "offD2";
     }
     else if(device_name == "door" && device_status == "open"){
        url = "onD3";
    }
    else if(device_name == "door" && device_status == "close"){
        url = "offD3";}
    else{
        // conv.ask("Inputs not clear. Please renter your input.");
     }
    return new Promise((resolve, reject) => {
        var options = { 
            method: 'GET',
            url: ip_add+url,
            headers: 
            { 
                'cache-control': 'no-cache'
            } 
        };
    
        request(options, function (error, response, body) {
            if (error) {
                reject(conv.ask("I am not able to process it."));
            }
            else{
                resolve(conv.ask(device_status+ " "+device_name));
            }
           
        });
  });
});

app.intent('readhuma', (conv,{devicename}) => {
    // speech = "I got "+lednumber+" and "+status;
    var device_name = devicename;
    return new Promise((resolve, reject) => {
        var options = { 
            method: 'GET',
            url: ip_add+'humidity',
            headers: 
            { 
                'cache-control': 'no-cache'
            } 
        };
    
        request(options, function (error, response, body) {
            if (error) {
                reject(conv.ask("I am not able to process it."));
            }
            else{
                var doam_data = (JSON.parse(body).humidity);
                console.log(doam_data);
                resolve(conv.ask(device_name +" is " +doam_data + "%"));
            }
           
        });
  });
});

app.intent('readtemp', (conv,{devicename}) => {
    // speech = "I got "+lednumber+" and "+status;
    var device_name = devicename;
    return new Promise((resolve, reject) => {
        var options = { 
            method: 'GET',
            url: ip_add+'temperature',
            headers: 
            { 
                'cache-control': 'no-cache'
            } 
        };
    
        request(options, function (error, response, body) {
            if (error) {
                reject(conv.ask("I am not able to process it."));
            }
            else{
                var temp_data = (JSON.parse(body).temperature);
                console.log(temp_data);
                resolve(conv.ask(device_name +" is " +temp_data + " degree"));
            }
           
        });
  });
});
expressApp.listen(8050);
console.log('Listening on port 8050...');
