var socket;
var socketInfo;

document.addEventListener ('DOMContentLoaded', function () { 
   console.log ( 'Adding DOMContentLoaded Listener' );
   
   socket = chrome.sockets.udp;
   socket.create({}, function(_socketInfo) {
      socketInfo = _socketInfo;

      bindAddress = '0.0.0.0';
      socket.bind(socketInfo.socketId, bindAddress, 0, function(connectResult) {
        connected = (connectResult == 0);

        socket.onReceive.addListener(function(result) {
          console.log ( 'onReceive.addListener: ' + result );
          //if (callbacks.length > 0) {
          //  callbacks.shift()(result);
          //}
        });

        console.log ( 'callback(connected);' );
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
  sendAddress = '10.3.141.255';
  socket.send(socketInfo.socketId, new Uint8Array(data).buffer, sendAddress, 3333, function(sendResult) {   
    //console.log ( 'Got a send result: ' + sendResult );
    // callback(sendResult);
  });  
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



