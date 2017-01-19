var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var net = require('net');
var fs = require('fs');

net.bufferSize = 2585100;
net.bytesRead = 2585100;

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

    socket.on('key event', function(ch){
	console.log('key event :' + ch);
	client.write(ch);
    });

    socket.on('window size', function(size){
	console.log(size);
	//client.write(size);
    });

    const chunks = []
    client.on('data', function(chunk) {
	console.log(chunk);
	chunks.push(chunk);
    });
    client.on('end', () => {
	console.log("sdfsdfsdfsadfasdfasdf");
	
	const data = Buffer.concat(chunks);

	var width = data.readInt16LE(0);
	var height = data.readInt16LE(4);
	var depth = data.readInt16LE(8);
	var bitmap = data.slice(12);

	console.log("data_len : " + data.length);
	console.log("width : " + width);
	console.log("height : " + height);
	console.log("depth : " + depth);
	
	//var shminfo = JSON.parse(data);
	//console.log(shminfo);

	socket.emit('image', { image: true, buffer: bitmap, width: width, height: height, depth: depth });
	
    });

    

});


http.listen(3000, function(){
    console.log('listening on *:3000');
});
