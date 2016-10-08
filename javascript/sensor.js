"use strict"

const worker = require("streaming-worker");
const through = require("through");
const path = require("path");

const addon_path = path.join(__dirname, "../nodeaddon/build/Release/sensor");
const my_super_sensor = worker(addon_path, {name : "Stream My Data"});

//option 1 emitter interface
//my_super_sensor.from.on("position_sample", (sample) => {console.log(JSON.parse(sample));});

//option 2 create streams to and from c++ addon. capture output from c++ addon use stream() method
//on from object
//const outstream = my_super_sensor.from.stream();
//pipe this to something
//outstream.pipe(through((sample) => {console.log(sample)}));


//option 3 work with streaming interface
const stream_and_parse = through(function(data) { this.queue(JSON.parse(data[1]));});
//stream isn't created untill invoked
const out = my_super_sensor.from.stream();
//pipe this to something
out.pipe(stream_and_parse).pipe(through((queuedstream) => {console.log(queuedstream)}));


setTimeout(() => {my_super_sensor.close()}, 5000);
//run npm start in the javascript folder, for 5 seconds view the data streaming from the c++ addon