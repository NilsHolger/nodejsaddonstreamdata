"use strict"

const worker = require("streaming-worker");
const through = require("through");
const path = require("path");

const addon_path = path.join(__dirname, "../nodeaddon/build/Release/sensor");
const my_super_sensor = worker(addon_path, {name : "Stream My Data"});

my_super_sensor.from.on("position_sample", (sample) => {console.log(JSON.parse(sample));});
setTimeout(() => {my_super_sensor.close()}, 5000);

//run npm start in the javascript folder, for 5 seconds view the data streaming from the c++ addon

