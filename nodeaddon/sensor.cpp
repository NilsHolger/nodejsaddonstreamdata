#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include "streaming-worker.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;


class Sensor : public StreamingWorker {
    public:
    Sensor(Callback *data, Callback *complete, Callback *error_callback, v8::Local<v8::Object> & options)
    : StreamingWorker(data, complete, error_callback){

        //name is a member variable in Sensor
        name = "My Sensor";
        //interrogate the options object to see if there is a "name" property
        if (options->IsObject()){
            v8::Local<v8::Value> name_ = options->Get(New<v8::String>("name").ToLocalChecked()); 
            if (name_->IsString()){
                v8::String::Utf8Value s(name_);
                name = *s;
            }
        }
    }
    //here make C++ API call to device or data source to get the data in streaming mode
    void Execute (const AsyncProgressWorker::ExecutionProgress& progress){
            std::random_device rd;
            std::uniform_real_distribution<double> pos_dist(-1.0, 1.0);
            while(!closed()){
                json sample;
                sample["name"] = name;
                sample["sensor"]["x"] = pos_dist(rd);
                sample["sensor"]["y"] = pos_dist(rd);
                sample["sensor"]["z"] = pos_dist(rd);

                //serialize the json samplet to a string and send to JavaScript
                Message tosend("position_sample", sample.dump());
                //each writeToNode call queues an event in lib_uv
                //any output collected from addon between events is cached
                //in thread safe queue and sent back to node in event_loop
                //thread when lib_uv processes the event
                writeToNode(progress, tosend);

                std::this_thread::sleep_for(chrono::milliseconds(50));
            }
    }
    private:
    string name;
};

    StreamingWorker * create_worker(Callback *data, Callback *complete,
     Callback *error_callback, v8::Local<v8::Object> & options){
         return new Sensor(data, complete, error_callback, options);
     }


NODE_MODULE(sensor, StreamWorkerWrapper::Init)

