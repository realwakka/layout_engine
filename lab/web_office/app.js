var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var net = require('net');
var fs = require('fs');
var jimp = require('jimp');

http.listen(3000, '0.0.0.0', function(){
    console.log('listening on *:3000');
});

app.get('/', function(req, res){
    res.sendfile('index.html');
});

io.on('connection', function(socket){
    
    var client = net.createConnection("/tmp/sock1", function() {
	console.log('connected to c++ server!');
    });

    console.log('a user connected');
    console.log('give me the window size!');
    socket.emit('window size request');
    
    socket.on('disconnect', function(){
	console.log('user disconnected');
    });

    socket.on('keypress event', function(event){
	console.log(event);
	client.write(JSON.stringify(event));
    });

    socket.on('mousedown event', function(event){
	console.log(event);
	client.write(JSON.stringify(event));
    });


    socket.on('window size', function(size){
	console.log(size);
	//client.write(size);
    });

    var buffer_len = 0;
    var chunks_len = 0;
    const chunks = [];
    client.on('data', function(data) {
	console.log("received image");
	console.log(data);
	socket.emit('image', { image: true, buffer: data.toString("base64")});
    });

});


