var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var net = require('net');
var fs = require('fs');
var shm = require('shm');

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


    client.on('data',function(data){
	
	var shminfo = JSON.parse(data);
	console.log(shminfo);
	var shmsize = shminfo.width * shminfo.height * shminfo.depth;
	var shmid = shm.openSHM(shminfo.shmkey, 'a', 0, shmsize);

	var buf = shm.readSHM(shmid, 0, shmsize);

	socket.emit('image', { image: true, buffer: buf, width: shminfo.width, height: shminfo.height, depth: shminfo.depth });

    });

});


http.listen(3000, function(){
    console.log('listening on *:3000');
});
