var express = require('express')
var app = express();
app.use(express.static(__dirname + '/public'));

var http = require('http').Server(app);
var io = require('socket.io')(http);
var fs = require ('fs');
var pythonShell = require ('python-shell');
var net = require ( 'net' );
const dgram = require ( 'dgram' );
var mysql      = require('mysql');
var url        = require ( 'url' );
var dbConnection = mysql.createConnection({
  host     : 'localhost',
  user     : 'root',
  password : 'pi',
  database : 'Paulware'
});
dbConnection.connect(function(err){
  if(!err) {
    console.log("Database is connected ... nn");    
  } else {
    console.log("Error connecting database ... nn");    
  }
});
var client = new net.Socket();
var serverAddress
var os = require ( 'os' );
var ifaces = os.networkInterfaces();

// Get serverAddress
serverAddress = '';
Object.keys(ifaces).forEach(function (ifname){
   var alias = 0;  
   ifaces[ifname].forEach(function(iface){
      if ('IPv4' !== iface.family  || iface.internal !== false){
         // skip over internal (i.e. 127.0.0.1) and non-ipv4 addresses
         return;
      }
      if (alias >= 1) {
         console.log(ifname + ':' + alias, iface.address);
      } else {
        // this interface has only one ip4 address
        serverAddress = 'http://' + iface.address + ':3000'; 
      }    
   });
});
console.log ( 'serverAddress: ' + serverAddress ); 
var response;

function emit (msg){
   io.emit ('chat message', msg);
   console.log ( 'Emitting: ' + msg);
}

app.get('/', function(req, res){
  response = res;
  dbConnection.query('SELECT * from pipboys', function(err, rows, fields) {
    if (!err) {
      msg = '<html><body><img src=\"/images/darth.jpg\">\n' + 
            '<h1>Page Guide</h1><hr>\n' + 
            '<hr>\n' + 
            '<li>\n' + 
            '<h1>Theory of Operation</h1><hr>\n' +
            '<ul>\n' + 
            '  <li><h1>Required install libraries</h1><hr><ul>\n' +                   
            '  <li>node.js installed from adafruit tutorial: <a href=\"https://learn.adafruit.com/node-embedded-development/installing-node-dot.js\">https://learn.adafruit.com/node-embedded-development/installing-node-dot.js</a><br>\n' + 
            '  <li>npm install --save express</li>\n' + 
            '  <li>npm install --save socket-io</li>\n' + 
            '  <li>npm install --save multer</li>\n' +                   
            '</ul></li>\n' + // end Required install libraries
            '<li>\n' + 
            '<h1>Pi Initialization</h1><hr>\n' +
            '<ul>\n' + 
            '<li>/etc/rc.local contains command: node index.js which starts the server on power up</li>\n' +  
            '</ul>\n' + 
            '</li>\n' + // Initialization
            '<li>\n' + 
            '<h1>Client/Server Communication</h1><hr>\n' +
            '<ul>\n' + 
            '<li>Server can send an socket_io.emit \'chat message\' at any time which should be handled by client socket.on (\'chat message\') function</li>\n' +  
            '<li>Client can send a socket_io.emit \'chat message\' to the server to send database session information</li>\n' + 
            '</li>\n' + // end Client Server Communication
            '</ul>\n';
            msg = msg + "<Table border=\"2px\">\n"; 
            msg = msg + "<tr>";
            msg = msg + "<th>Typename</th>";
            msg = msg + "<th>Username</th>";
            msg = msg + "<th>MAC</th>";
            msg = msg + "<th>IP Address</th>";
            msg = msg + "</tr>\n";
            for (i=0; i<rows.length; i++) {
              msg = msg + '<tr>';                                
              msg = msg + '<td>' + rows[i].Typename + '</td>\n';
              msg = msg + '<td><input type=\"button\" value=\"' + rows[i].Username + '\" ';
              msg = msg + "onclick=\"window.location.href='" + serverAddress + "/" + rows[i].Typename + "?IpAddress=" + rows[i].IpAddress + "';\"></td>\n";
              msg = msg + '<td>' + rows[i].MAC + '</td>\n';
              msg = msg + '<td>' + rows[i].IpAddress + '</td></tr><br>\n';
            }                   
            msg = msg + "</Table>\n"; 
            msg = msg + '</body></html>';

      response.end ( msg);                  
    } else {
      response.end ( '<html><body>Error while performing query' + err + '</body></html>' );
      console.log('Error while performing Query.' + err);
    }  
  });
});
app.get('/Tank', function(req, response){
    var url_parts = url.parse(req.url, true);
    var query = url_parts.query;

    console.log('query.IpAddress: ' + query.IpAddress );
    
    filename = __dirname + '/modifyPage.html';
      
    fs.open ( filename , 'w+', function (err,data) {
        if (err) {
          console.log ( 'err: ' + err);
        } else {        
                
          fs.write (data, '<html><head>\n' + 
          '<script src=\"socket.io-1.2.0.js\"></script>\n' + 
          '<Script>\n' + 
          '  var socket = io();\n' + 
          '  var lastCh = \" \";\n' + 
          '  var lastSlide = 0;\n' +           
          '  var IpAddress = \"' + query.IpAddress + '\";\n' + 
          '  function left() { ' + '\n' +
          '    socket.emit (\"chat message\", \"left \" + IpAddress );\n' + 
          '  }\n' +
          '  function right(){\n' +
          '    socket.emit (\"chat message\", \"right \" + IpAddress );\n' + 
          '  }\n' +
          '  function forward () {\n' +
          '    socket.emit (\"chat message\", \"forward \" + IpAddress );\n' + 
          '  }\n' +
          '  function reverse() {\n' +
          '    socket.emit (\"chat message\", \"reverse \" + IpAddress );\n' + 
          '  }\n' +
          '  function stop() {\n' +
          '    if (lastCh != 32) {\n' + 
          '      socket.emit (\"chat message\", \"stop \" + IpAddress );\n' + 
          '    }\n' + 
          '    lastCh = \' \';\n' + 
          '  }\n' +
          '  function bounce3 () {\n' + 
          '    socket.emit (\"chat message\", \"stop \" + IpAddress); \n' + 
          '  }\n' + 
          '  function bounce2 () {\n' + 
          '    socket.emit (\"chat message\", \"forward \" + IpAddress); \n' + 
          '    setTimeout (bounce3, 350); \n' + 
          '  }\n' + 
          '  function bounce1 () {\n' + 
          '    socket.emit (\"chat message\", \"reverse \" + IpAddress); \n' +
          '    setTimeout (bounce2, 350); \n' + 
          '  }\n' + 
          '  function fire() {\n' +
          '    socket.emit (\"chat message\", \"fire \" + IpAddress); \n' +
          '    setTimeout (bounce1,350);\n' +           
          '  }\n' +
          '  function pollSlider () { \n' + 
          '    val = document.all.slider.value * 255 / 100;\n' + 
          '    if (val != lastSlide) { \n' + 
          '      document.all.speed.value = val;\n' + 
          '      lastSlide = val;\n' + 
          '      socket.emit (\"chat message\", \"slider \" + IpAddress + \" \" + val + \"\\n\");\n' + 
          '    }\n' + 
          '  }\n' + 
          '  function myScript(e) {\n' + 
          '    e = e || event;\n' + 
          '    var chCode = (\"charCode\" in e) ? e.charCode : e.keyCode;\n' +            
          '    if (chCode != lastCh) {\n' + 
          '      lastCh = chCode;\n' + 
          '      if (chCode == 97) { // a \n' + 
          '        left();\n' + 
          '      } else if (chCode == 119) { // w\n' + 
          '        forward(); \n' + 
          '      } else if (chCode == 100) { // d\n' + 
          '        right(); \n' + 
          '      } else if (chCode == 115) { // s\n' + 
          '        reverse(); \n' + 
          '      } else if (chCode == 32) { // space\n' + 
          '        fire(); \n' +           
          '      } else { \n' + 
          '        stop(); \n' + 
          '        // alert ( chCode ); \n' + 
          '      }\n' + 
          '    }\n' + 
          '  }\n' + 
          '  setInterval (pollSlider,500);\n' + 
          '</Script></head>\n' +          
          '<body onkeypress=\"myScript();\" onkeyup=\"stop();\">\n' + 
          '  <div style=\"text-align:center\">\n' + 
          '  <img src=\"/images/forward.jpg\" onmousedown=\"forward();\" onmouseup=\"stop();\">\n' + 
          '  <br>\n' + 
          '  <img src=\"/images/left.jpg\" onmousedown=\"left();\" onmouseup=\"stop();\">\n' + 
          '  <img src=\"/images/right.jpg\" onmousedown=\"right();\" onmouseup=\"stop();\">\n' + 
          '  <br>\n' + 
          '  <img src=\"/images/reverse.jpg\" onmousedown=\"reverse();\" onmouseup=\"stop();\">\n' + 
          '  <br>\n' + 
          '  <img src=\"/images/fire.jpg\" onmousedown=\"fire();\">\n' + 
          '  </div>\n' +
          '  Speed: <input type=\"range\" name=\"slider\">\n' +           
          '  <input name=\"speed\" value=\"0\"><br> \n' +           
          '</body></html>\n', 
          0, 'content length', null, 
                   
          function (err) {
            if (err)
              console.log ( 'Err1: ' + err);
          });
          fs.close (data, function() {
            response.sendFile(filename);
            console.log ( filename + ' created, response sent')
          });                 
        }    
    });
 
});

app.get('/PickAndDrop', function(req, response){
    var url_parts = url.parse(req.url, true);
    var query = url_parts.query;

    console.log('query.IpAddress: ' + query.IpAddress );
    
    filename = __dirname + '/tmp.html';
      
    fs.open ( filename , 'w+', function (err,data) {
        if (err) {
          console.log ( 'err: ' + err);
        } else {        
                
          fs.write (data, '<html><head>\n' + 
          '<script src=\"socket.io-1.2.0.js\"></script>\n' + 
          '<Script>\n' + 
          '  var socket = io();\n' + 
          '  var IpAddress = \"' + query.IpAddress + '\";\n' + 
          '  var serverAddress = \"' + serverAddress + '\";\n' + 
          '  var lastSlide = 0;\n' + 
          '  function pollSlider () { \n' + 
          '    val = document.all.slider.value;\n' + 
          '    if (val != lastSlide) { \n' + 
          '      document.all.speed.value = val;\n' + 
          '      lastSlide = val;\n' + 
          '      socket.emit (\"chat message\", \"slider \" + IpAddress + \" \" + val + \"\\n\");\n' + 
          '    }\n' + 
          '  }\n' + 
          '  setInterval (pollSlider,500);\n' + 
          '</Script></head>\n' +          
          '<body><img src=\"/images/pickdrop.jpg\" width=\"400px\"><br>\n' + 
          '  Speed: <input type=\"range\" name=\"slider\"><br>\n' +           
          '  <input name=\"speed\" value=\"0\"><br>\n' +
          '  <hr><input type=\"button\" value=\"home\" onclick=\"window.location.href=serverAddress;\">\n' +           
          '</body></html>\n', 
          0, 'content length', null, 
                   
          function (err) {
            if (err)
              console.log ( 'Err1: ' + err);
          });
          fs.close (data, function() {
            response.sendFile(filename);
            console.log ( filename + ' created, response sent')
          });                 
        }    
    }); 
});

io.on('connection', function(socket){
  socket.on('chat message', function(msg){ // chat message received on socket
    console.log ( 'Got chat msg:' + msg + '.' );
    index = msg.indexOf (" ");
    cmd = msg.substring (0,index);
    addr = msg.substring (index+1);  
    parameter = "";    
    if (addr.indexOf (" ") > -1) {
      index = addr.indexOf (" ");
      parameter = addr.substring(index+1);
      addr = addr.substring (0,index);
    }
    if (addr == 'null') {
       console.log ( 'IpAddress of device == null' );
    } else {
      console.log ( 'cmd: ' + cmd + ' To address: ' + addr + ' parameter:' + parameter + '.' );
      if (cmd == 'slider') {
        cmd = cmd + " " + parameter;
      }
      if (cmd == 'top' ) {
         console.log ( 'Could not handle the command: ' + cmd );
      } else {
        console.log ( 'Send the command: ' + cmd );
            
        var udpClient = dgram.createSocket ( 'udp4' );    
        udpClient.send ( cmd, 0, cmd.length, 3333,addr, function (err, bytes ) {
          if (err) throw err;
          console.log ( 'Send message ' + cmd + ' to ' + addr + ':3333' );
          udpClient.close();
        });
      } 
    }      
  });  
});

// Set the port that the server will listen on 
http.listen(3000, function(){
  console.log('listening on *:3000');
});