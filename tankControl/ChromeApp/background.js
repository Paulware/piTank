var socket;
var socketInfo;

document.addEventListener ('DOMContentLoaded', function () { 
   console.log ( 'Adding DOMContentLoaded Listener' );
   
   socket = chrome.sockets.udp;
   socket.create({}, function(_socketInfo) {
      socketInfo = _socketInfo;

      socket.bind(socketInfo.socketId, '127.0.0.1', 0, function(connectResult) {
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
  socket.send(socketInfo.socketId, new Uint8Array(data).buffer, '127.0.0.1', 3333, function(sendResult) {   
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


function sendpack() {
    console.log ( 'sendpack yo 2' );
    // Create the Socket
    chrome.sockets.udp.create({}, function(socketInfo) {
        // The socket is created, now we can send some data
        var socketId = socketInfo.socketId;

        chrome.sockets.udp.bind(socketId, '255.255.255.255', 1345, function(result){
            console.log('chrome.socket.bind: result = ' + result.toString());
        });

        var arrayBuffer=new ArrayBuffer(2);
        arrayBuffer[0]=65;
        arrayBuffer[1]=66;
        chrome.sockets.udp.send(socketId, arrayBuffer,'255.255.255.255', 3000,function(sendInfo) {
            console.log("sent " + sendInfo.bytesSent);
            
        });
    });
}

