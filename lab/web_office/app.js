var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var net = require('net');
var fs = require('fs');

app.get('/', function(req, res){
    res.sendfile('index.html');
});

var client = net.createConnection("/tmp/sock1", function() {
    console.log('connected to c++ server!');

    io.on('connection', function(socket){
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
	    client.write(size);
	});


	client.on('data',function(data){
	    fs.readFile('/home/sidong/layout_engine/build/output.bmp', function(err, buf){
		socket.emit('image', { image: true, buffer: buf.toString('base64') });
		console.log('image file is initialized');
	    });
	});

    });
    

});



http.listen(3000, function(){
    console.log('listening on *:3000');
});
