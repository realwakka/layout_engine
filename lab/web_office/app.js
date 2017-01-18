var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var net = require('net');
var fs = require('fs');

app.get('/', function(req, res){
    res.sendfile('index.html');
});

io.on('connection', function(socket){
    console.log('a user connected');

    var client = net.createConnection("/tmp/sock1", function() {
	console.log('connected to server!');
	var data  = 'world!';
	console.log('serve send data : '+data);
    });

    
    socket.on('disconnect', function(){
	console.log('user disconnected');
    });

    socket.on('chat message', function(ch){
	console.log(ch);
	client.write(ch);
    });

    client.on('data',function(data){
	fs.readFile('/home/sidong/layout_engine/build/output.bmp', function(err, buf){
	    socket.emit('image', { image: true, buffer: buf.toString('base64') });
	    console.log('image file is initialized');
	});
    });

});

http.listen(3000, function(){
    console.log('listening on *:3000');
});
