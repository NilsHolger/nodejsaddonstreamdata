# nodejsaddonstreamdata
nodejs addon javascript c++ v8 libuv asynch streaming

stream data from c++ to nodejs
addon can be listened to as an event emitter or as an input stream
sensor addon code executes in worker thread, the javascript code is completely asynchronous
streaming worker has two event emitter interfaces to and from, to emit events to the addon, from listen for events sent from addon
in the addon the c++ code sends updates using the writeToNode method
using the streaming api
to capture the output from c++ use the stream() method on from object then pipe it through
use through and a queue to have stream created only when invoked then pipe the queue through

there are many use cases for asynchronous and streaming data addons, the data on the screen and from whatever source will always be synchronized
