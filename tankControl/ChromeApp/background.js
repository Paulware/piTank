var socket;
var socketInfo;
document.addEventListener ('DOMContentLoaded', function () { 
   console.log ( 'Adding DOMContentLoaded Listener' );
   
   socket = chrome.sockets.udp;
   socket.create({}, function(_socketInfo) {
      socketInfo = _socketInfo;
      socket.bind(socketInfo.socketId, '0.0.0.0', 0, function(connectResult) {
        chrome.sockets.udp.setBroadcast(socketInfo.socketId, true, function broadcastResult(result){});
      });
      
   });   
   
   document.getElementById ( "forward").addEventListener ("mousedown", forward);
   document.getElementById ( "forward").addEventListener ("mouseup", stop);
   document.getElementById ( "reverse").addEventListener ("mousedown", reverse);
   document.getElementById ( "reverse").addEventListener ("mouseup", stop);
   document.getElementById ( "left"   ).addEventListener ("mousedown", left);
   document.getElementById ( "left"   ).addEventListener ("mouseup", stop);
   document.getElementById ( "right"  ).addEventListener ("mousedown", right);
   document.getElementById ( "right"  ).addEventListener ("mouseup", stop);
   document.getElementById ( "fire"  ).addEventListener ("mousedown", fire);
});

function sendData (command, parameter) {
  if (parameter == undefined) {
     msg = command;
  } else {      
     msg = command + ' ' + parameter;
  }
  console.log ( 'sendData [' + msg + ']');

  data = []
  for (var i = 0; i < msg.length; i++) {
      data.push(msg.charCodeAt(i));
  }  
  sendAddress = '255.255.255.255';
  socket.send(socketInfo.socketId, new Uint8Array(data).buffer, sendAddress, 3333, function(sendResult) {});  
}
function left() {
   sendData ( 'left'  );
}
function right(){
   sendData ( 'right' );
}
function forward () {
   sendData ( 'forward' );
}
function reverse() {
   sendData ( 'reverse');
}
function stop() {
   sendData ( 'stop' );
}
function fire() {
   sendData ( 'fire' );
}