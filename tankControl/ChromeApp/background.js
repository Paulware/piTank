var socket;
var socketInfo;
var lastButton;

document.addEventListener ('DOMContentLoaded', function () { 
   console.log ( 'Adding DOMContentLoaded Listener' );
   
   chrome.alarms.onAlarm.addListener(function(alarm){
       chrome.alarms.create("myAlarm", {delayInMinutes: 0.005} ); // 3 times a second if possible
       if (lastButton == 'stop') {
          sendData ('SsUu');
       } else if (lastButton == 'left') {
          sendData ( 'lRUu' );
       } else if (lastButton == 'right') {
          sendData ( 'LrUu' );
       } else if (lastButton == 'fire' ) {
          sendData ( 'SsUuF');
          lastButton = 'stop';
       } else if (lastButton == 'forward' ) {
          sendData ( 'LRUu' );
       } else if (lastButton == 'reverse' ) {
          sendData ( 'lrUu' );
       }           
   });   
   
   socket = chrome.sockets.udp;
   socket.create({}, function(_socketInfo) {
      socketInfo = _socketInfo;
      socket.bind(socketInfo.socketId, '0.0.0.0', 0, function(connectResult) {
        chrome.sockets.udp.setBroadcast(socketInfo.socketId, true, function broadcastResult(result){});
      });
      
   });   
   
   document.getElementById ("forward").addEventListener ("mousedown", forward);
   document.getElementById ("forward").addEventListener ("mouseup", stop);
   document.getElementById ("reverse").addEventListener ("mousedown", reverse);
   document.getElementById ("reverse").addEventListener ("mouseup", stop);
   document.getElementById ("left"   ).addEventListener ("mousedown", left);
   document.getElementById ("left"   ).addEventListener ("mouseup", stop);
   document.getElementById ("right"  ).addEventListener ("mousedown", right);
   document.getElementById ("right"  ).addEventListener ("mouseup", stop);
   document.getElementById ("fire"   ).addEventListener ("mousedown", fire);
   
   chrome.alarms.create("myAlarm", {delayInMinutes: 0.01} );
});

function sendData (msg) {
  console.log ( 'sendData [' + msg + ']');
  if (msg == 'SsUu') {
      console.log ( 'lastButton: [' + lastButton + ']' );
  }

  data = []
  for (var i = 0; i < msg.length; i++) {
      data.push(msg.charCodeAt(i));
  }  
  sendAddress = '255.255.255.255';
  socket.send(socketInfo.socketId, new Uint8Array(data).buffer, sendAddress, 3333, function(sendResult) {});  
}
function left() {
   lastButton = 'left';
}
function right(){
   lastButton = 'right';
}
function forward () {
   lastButton = 'forward';
}
function reverse() {
   lastButton = 'reverse';
}
function stop() {
   lastButton = 'stop';
}
function fire() {
   lastButton = 'fire';
}