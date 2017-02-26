document.addEventListener("keydown", function(event) {

    console.log(event);
    event.preventDefault();
    
    websocket.send(JSON.stringify({type: "keydown", key: event.key,keyCode: event.keyCode, ctrlKey: event.ctrlKey, altKey: event.altKey, shiftKey: event.shiftKey}));
    websocket.send(JSON.stringify({type: "paint"}));
}, true );






canvas.addEventListener("mousedown", function(event) {
    console.log(event);
    websocket.send(JSON.stringify({type: "mousedown", x: event.clientX, y: event.clientY}));

} );

var websocket = new WebSocket('ws://127.0.0.1:8080','le_web_protocol');
websocket.onopen = function() {
    console.log("onopen");
}

websocket.onerror = function() {
    console.log("onerror");
}

websocket.onmessage = function(message) {
    console.log("onmessage!!");
    var reader = new FileReader();

    reader.onload = function(e) {
	var img = new Image();
	var canvas = document.getElementById('canvas');
	var ctx = canvas.getContext('2d');
	
	img.src = e.target.result;
	canvas.width = img.width;
	canvas.height = img.height;
	ctx.drawImage(img, 0, 0);
	console.log(img.width);
	console.log(img.height);
    };

    reader.readAsDataURL(message.data);
    
}
