var express    = require("express");
var app = express();
var multer = require ('multer');
var upload =   multer({ dest: './uploads/'});
var http = require('http').Server(app);
var io = require('socket.io')(http);
var fs = require ('fs');
var pythonShell = require ('python-shell');
var mysql      = require('mysql');
var dbConnection = mysql.createConnection({
  host     : 'localhost',
  user     : 'root',
  password : 'pi',
  database : 'Paulware'
});

app.use(express.static(__dirname + '/public'));


console.log ( 'we have net?' );
var response;
var serverAddress = '';

var os = require ( 'os' );
var ifaces = os.networkInterfaces();

dbConnection.connect(function(err){
if(!err) {
    console.log("Database is connected ... nn");    
} else {
    console.log("Error connecting database ... nn");    
}
});

app.get('/drive', function(req, response){
  console.log ( 'serve drive' );
  // Todo: add ip address of vehicle to drive1.html so it can send a message to device
  response.sendFile(__dirname + '/drive1.html'); 
});
app.get('/modify', function(req, response){
  dbConnection.query('SELECT * from pipboys', function(err, rows, fields) {
    if (!err) {
      // console.log('The solution is: ', rows);
      msg = '<html><body>\n' + 
            '<h1>Drive</h1><hr>\n' + 
            '<ul><li><a href=\"' + serverAddress + '/room2\">' + serverAddress + '/room2</a>show room2 session</li>\n' + 
            '</ul>\n'; 
      msg = msg + "<Table border=\"2px\">\n"; 
      msg = msg + "<tr><th>Username</th>";
      msg = msg + "<th>MAC</th></tr>\n";
      for (i=0; i<rows.length; i++) {
        msg = msg + '<tr>';                                
        msg = msg + '<td><input type=\"button\" value=\"' + rows[i].Username + '\" ';
        msg = msg + "onclick=\"window.location.href='" + serverAddress + "/modify'\"></td>\n";
        msg = msg + '<td>' + rows[i].MAC + '</td></tr><br>\n';
      }                   
      msg = msg + "</Table>\n"; 
      msg = msg + '</body></html>';

      response.end ( msg);                  
    }
  });
});
app.get("/",function(req,res){
  response = res;
  dbConnection.query('SELECT * from pipboys', function(err, rows, fields) {
  if (!err) {
    // console.log('The solution is: ', rows);
    msg = '<html><body><img src=\"/images/darth.jpg\">\n' + 
          '<h1>Page Guide</h1><hr>\n' + 
          '<ul>\n' + 
          '<li><a href=\"' + serverAddress + '/config\">' + serverAddress + '/config</a> create sessions</li>\n' + 
          '<li><a href=\"' + serverAddress + '/modify\">' + serverAddress + '/modify</a> change session information</li>\n' + 
          '<li><a href=\"' + serverAddress + '/room1\">' + serverAddress + '/room1</a>show room1 session</li>\n' + 
          '<li><a href=\"' + serverAddress + '/room2\">' + serverAddress + '/room2</a>show room2 session</li>\n' + 
          '</ul>\n' + 
          '<hr>\n' + 
          '<li>\n' + 
          '<h1>Theory of Operation</h1><hr>\n' +
          '<ul>\n' + 
          '<li><h1>Required install libraries</h1><hr><ul>\n' +                   
          '<li>node.js installed from adafruit tutorial: <a href=\"https://learn.adafruit.com/node-embedded-development/installing-node-dot.js\">https://learn.adafruit.com/node-embedded-development/installing-node-dot.js</a><br>\n' + 
          '<li>npm install --save express</li>\n' + 
          '<li>npm install --save socket-io</li>\n' + 
          '<li>npm install --save multer</li>\n' +                   
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
          '<li>Client can request pages listed above</li>\n' + 
          '<li>Client can use a form-upload request which causes a file to be uploaded to the server and placed in public/images</li>\n' +  
          '<li>Client can send a socket_io.emit \'chat message\' to the server to send database session information</li>\n' + 
          '<li>Server saves session information to a text db.txt file</li>\n' +                   
          '</ul>\n' + 
          '</li>\n' + // end Client Server Communication
          '</ul>\n';
          msg = msg + "<Table border=\"2px\">\n"; 
          msg = msg + "<tr><th>Username</th>";
          msg = msg + "<th>MAC</th></tr>\n";
          for (i=0; i<rows.length; i++) {
            msg = msg + '<tr>';                                
            msg = msg + '<td><input type=\"button\" value=\"' + rows[i].Username + '\" ';
            msg = msg + "onclick=\"window.location.href='" + serverAddress + "/drive'\"></td>\n";
            msg = msg + '<td>' + rows[i].MAC + '</td></tr><br>\n';
          }                   
          msg = msg + "</Table>\n"; 
          msg = msg + '</body></html>';

    response.end ( msg);                  
  } else {
    response.end ( '<html><body>Error while performing query</body></html>' );
    console.log('Error while performing Query.');
  }  
  });
});

var os = require ( 'os' );
var ifaces = os.networkInterfaces();
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
console.log ( '__dirname: ' + __dirname );
app.listen(3000);


io.on('connection', function(socket){
  socket.on('chat message', function(msg){ // chat message received on socket
    console.log ( 'got something...' );
  });
});



/* 
console.log ( 'io.on connection' );
io.on('connection', function(sock){
  sock.on('chat message', function(msg){ // chat message received on socket
    console.log ( msg );
    index = msg.indexOf (" ");
    cmd = msg.substring (0,index);
    d = msg.substring (index+1);
    if (cmd == 'config') {
       //buildPythonTime(filename);    
       //runPython (filename)       
    } else {
       console.log ( 'Could not handle command: ' + cmd );
    }   
  });
  console.log ( 'got io socket (chat) connection' );
});
*/
console.log ( 'Done with initialization' );