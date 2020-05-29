var express = require('express')
var app = express();
var multer = require ('multer');
var upload =   multer({ dest: './uploads/'});
var http = require('http').Server(app);
var io = require('socket.io')(http);
var fs = require ('fs');
var pythonShell = require ('python-shell');

var serverAddress
app.use(multer({ dest: './uploads/',
    rename: function (fieldname, filename) {
        return filename+Date.now();
    },
    onFileUploadStart: function (file) {
        console.log(file.originalname + ' is starting ...');
    },
    onFileUploadComplete: function (file) {
        console.log(file.fieldname + ' uploaded to  ' + file.path);
        console.log('rename ' + file.path + ' back to: ' + file.originalname );
        
        fs.rename (file.path, './public/images/' + file.originalname, function (err) {
          if (err) throw err;
          fs.unlink(file.path, function(){
             if (err) throw err;
             console.log ('File uploaded to: ./public/images/' + file.originalname ); //  + ' - ' + req.files.thumbnail.size + ' bytes ');
          });
        });        
        
    }
}));


function nowDate() {
  var d = new Date(); 
  return (d.getMonth() + 1) + '/' + d.getDate() + '/' + d.getFullYear() ;
}

function multicastNew () {
  var message = new Buffer ("Multicast message!");
  udpServer.send (message, 0, message.length, 3333, '239.255.255.255', function () {
    console.log ('Multicast message containing server address sent.');
  });
}

// npm install --save my-local-ip
var os = require ( 'os' );
var ifaces = os.networkInterfaces();

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
filename = __dirname + '/public/serverAddress.js';
fs.open ( filename, 'w+', function (err,data) {
  if (err) {
    console.log ( 'err: ' + err);
  } else {
    msg = 'var serverAddress = \'' + serverAddress + '\';\n'; 
    fs.write (data, msg, 0, 'content length', null, 
    function (err) {
      if (err)
        console.log ( 'Err1: ' + err);
    });
    fs.close (data, function() {
      console.log ( 'Successfully wrote ' + msg + ' to ' + filename);
    });                 
  }    
}); 
console.log (filename + ' written');   
var response;

function appendFile ( filename, msg) {
   fs.open ( filename, 'a+', function (err,data) {
     if (err) {
       console.log ( 'err: ' + err);
     } else {
       fs.write (data, msg, 0, 'content length', null, 
       function (err) {
         if (err)
           console.log ( 'Err1: ' + err);
       });
       fs.close (data, function() {
         console.log ( 'Successfully appended ' + msg + ' to ' + filename);
       });                 
     }    
   }); 
   console.log (filename + ' appended');   
}

function appendPage ( msg , filename, response) {
   fs.open ( filename, 'a+', function (err,data) {
     if (err) {
       console.log ( 'err: ' + err);
     } else {
       fs.write (data, msg, 0, 'content length', null, 
       function (err) {
         if (err)
           console.log ( 'Err1: ' + err);
       });
       fs.close (data, function() {
         console.log ( 'Write successful');
         response.sendFile (filename)     
         console.log ( 'Response sent')
       });                 
     }    
   }); 
   console.log (filename + ' appended');   
}

function emit (msg){
   io.emit ('chat message', msg);
   console.log ( 'Emitting: ' + msg);
}

function copyFile ( source, destination) {
  fs.writeFileSync(destination, fs.readFileSync(source));
  // fs.createReadStream (source).pipe(fs.createWriteStream(destination));
  console.log ( source + ' copied to ' + destination);
}

function createPage ( filename) {
   fs.open ( filename, 'w+', function (err,data) {
     if (err) {
       console.log ( 'err: ' + err);
     } else {
       fs.write (data, 
       '<html>\n<body>\ndynamic page content3\n</body>\n</html>\n', 
       0, 'content length', null, 
       function (err) {
         if (err)
           console.log ( 'Err1: ' + err);
       });
       fs.close (data, function() {
         console.log ( 'Write successful');
         response.sendFile ( __dirname + '/temp.html')     
         console.log ( 'Response sent')
         io.emit('chat message', 'pageReady');
       });                 
     }    
   });  
}

function contentHead() {
   console.log ( 'contentHead')
   msg = '<head><title>Normal Content Page</title>\n' +
         '<style>\n' + 
         'footer {\n' +
         '    background-color:#0099FF;\n' +
         '    color:white;\n' +
         '    clear:both;\n' +
         '    text-align:center;\n' +
         '    padding:5px;\n' +	 	 
         '}\n' +
         '</style>\n' +
         '</head>\n';
   return msg;
}

function addRoom (room1, room2) {
  
  if ((room1 == 'true') && (room2 == 'true')) {
     msg = '<br>In both rooms<br>\n';
  } else if (room1 == 'true') {
     msg = '<br>Only in room1<br>\n';
  } else if (room2 == 'true') {
     msg = '<br>Only in room2<br>\n';
  } else {   // no room selected
     msg = '<br><h1>Oops room not marked</h1>\n' 
  }
  return msg;
}

function contentBody(sessionName, description, startingTime, endingTime, room1, room2, imageSrc) { 
  console.log ( 'contentBody, startingTime: ' + startingTime + ' endingTime: ' + endingTime)
  msg =  '<body><img src=\"images/' + imageSrc + '\"><br>\n' +
         '<h1><label>' + sessionName + '</label></h1>\n' + 
         '<p><br><h2>' + nowDate() + ' ' + startingTime + '-' + endingTime + '</h2><br>\n' + 
         '<br>' + description + '\n' +  addRoom (room1,room2) + '<br>' +         
         '<footer>some footer text</footer>\n' + 
         '</body>\n'
  return msg; 
}

function waitHead() {
   msg = '<head><title>Waiting Page</title>\n' +  
		       '<script src=\"jquery.min.js\"></script>\n';
   return msg;
}

function waitBody(sessionName,description, seconds, startDate, startTime, room1, room2, imageSrc) {
  var msg; 
  if (sessionName == undefined) {
     msg =  '<body>\n' +
            '<h1>NO MORE SESSIONS IN DATABASE<br><a href=\"' + serverAddress + 
            '/config\">Add more sessions</a></h1>\n' +
            '</body>\n'             
  } else {
     msg = '<body><h2>' + startDate + ' </h2><br>\n';      
     msg = msg + '<h1><label>' + sessionName + '<br>' + description + '<br></label></h1>\n';
     
     if (seconds > -1) {  
        msg = msg + 'Add start time';
     }  
     msg = msg + addRoom (room1,room2);
     if (imageSrc != undefined) {
        msg = msg + '<hr><img src=\"images/' + imageSrc + '\">\n'; 
     }
     msg = msg + '</body>\n';  
  }   
  return msg; 
}

function createWaitPage (response, sessionName, description, seconds, startDate, startTime, room1, room2, imageSrc) {
 
   filename = __dirname + '/waiting.html'
   fs.open ( filename , 'w+', function (err,data) {
     if (err) {
       console.log ( 'err: ' + err);
     } else {0
       page = '<html>' + waitHead() + waitBody(sessionName,description,seconds, startDate, startTime, room1, room2, imageSrc) + '</html>\n';
       fs.write (data, page, 
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
   response.sendFile(__dirname + '/waiting.html');      
}

function createContentPage (filename, response, sessionName, description, startTime, endTime, room1, room2, imageSrc) {
   fs.open ( filename , 'w+', function (err,data) {
     if (err) {
       console.log ( 'err: ' + err);
     } else {0
       page = '<html>' + contentHead() + contentBody(sessionName, description, startTime, endTime, room1, room2, imageSrc) + '</html>\n';
       fs.write (data, page, 
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
}

/*
app.get('/newpage1', function(req, res){
  filename = __dirname + '/newPage1.html'
  res.sendFile(filename);
});

app.get('/newpage', function(req, res){
  copyFile (__dirname + '/contentHeader.html', __dirname + '/contentPage.html')
  console.log ( 'File has been copied')
  msg = '\nplaceImage (\'images/logo.jpg\',100,100);\nvar socket = io();\nfunction sendData () {\n  msg = \'configData\';\n  socket.emit(\'chat message\',msg);\n}\n</script></body>\n</html>\n'; 
  appendPage (msg,  __dirname + '/contentPage.html', res);
});
*/

// url = http://location/index/config
app.get('/config', function(req, res){
  response = res;
  filename = __dirname + '/configPage.html';
  buildDynamicPage (__dirname + '/configPage.htm', filename);
  response.sendFile(filename);
});

app.get('/modify', function(req, response){
  buildModifyPage (response);  
});

function SecondsUntil(startDate) {
    date1 = new Date ();
    date2 = new Date (startDate);
    var datediff = date2.getTime() - date1.getTime(); //store the getTime diff - or +
    seconds = datediff / 1000;
    console.log ('startDate: ' + startDate + ' difference in seconds: ' + seconds );
    return (seconds); //Convert values to -/+ days and return value      
}

function DaysUntil(startDate) {
    date1 = new Date (nowDate());
    date2 = new Date (startDate);
    var datediff = date2.getTime() - date1.getTime(); //store the getTime diff - or +
    days = datediff / (1000 * 24 * 60 * 60);
    console.log ('startDate: ' + startDate + ' difference in days: ' + days );
    return (days); //Convert values to -/+ days and return value      
}

function modifyLine (lineNumber, newLine, finalCommand) {  
   var number = parseInt (lineNumber);
   var filename = __dirname + '/db.txt';
   var contents = '';
   
   console.log ('modify Line ' + lineNumber + ' newValue: ' + newLine);
   
   var r1 = require ('readline').createInterface ({
     input: require ('fs').createReadStream (filename)
   });   
   
   // Page generation is called from here
   r1.on ('close', function() {    
      fs.open ( filename, 'w+', function (err,data) {
        if (err) {
          console.log ( 'err: ' + err);
        } else {     
          console.log ( 'new Contents: ' + contents);        
          fs.write (data, contents, 0, 'content length', null, 
          function (err) {
            if (err)
              console.log ( 'Err1: ' + err);
          });
          fs.close (data, function() {
            if (newLine == '')
              console.log ( filename + ' updated, line ' + lineNumber + ' deleted');
            else
              console.log ( filename + ' updated, line ' + lineNumber + ' modified');                 
          });  
          // Tell the client to request the modify page again
          emit (finalCommand);       
        }    
      });    
   });

   var lineCount = 0
   // Create a copy of the file
   r1.on ('line', function (line) {
      if (lineCount == number) {
         // Check if this line should be deleted or modified
         if (newLine != '') {
            if (contents == '')
               contents = newLine;
            else
               contents = contents + '\n' + newLine;
         }
      } else {
         if (contents == '')
            contents = line;
         else 
            contents = contents + '\n' + line;
      }
      lineCount = lineCount + 1;
   });
   
}

String.prototype.twoCh = function() {
   var value = String(this);
   var total = parseInt(value);   
   if (!isNaN (total)) {
     if (total < 10) {
        value = "0" + value;
     }
   }   
   return value;
}
function timeStamp() { 
  d = new Date()
  months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];
  days = ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat'];
  stamp = days[d.getDay()].twoCh() + " " + months [d.getMonth()].twoCh() + " " + ("" + d.getDate()).twoCh() +
          " " + ("" + d.getHours()).twoCh() + ":" + (""+d.getMinutes()).twoCh() + ":" + 
         ("" + d.getSeconds()).twoCh() + " " + d.getFullYear();
  return stamp;
}

var serverTime = timeStamp();
function runPython (filename) {
   var python = new pythonShell (filename);
   python.on ('message', function(message){
     console.log ('\n***Got message from ' + filename + ':' + message + '***\n');
   });
   python.end(function(err){
     if (err) throw err;
     console.log ('finished in ' + filename);
   }); 
}

function buildPythonTime (filename) {
   var content = 'import os\nos.system(\"date -s \\\"' + serverTime + '\\\"\\n\")';
   console.log ( 'Write ' + content + ' \n to ' + filename );
   fs.writeFileSync (filename, content);
}

function buildDynamicPage (inFilename,outFilename) {
  var buf = fs.readFileSync (inFilename,"utf8");  
  var lines = buf.split ('\n');
  var line;
  var content = '';
  var varName;
  for (i=0; i<lines.length; i++) {
    line = lines [i];
    index = line.indexOf ("$");
    while (index > -1) {
      index2 = line.indexOf ("$",index+1);
      varName = line.substring(index+1,index2);
      console.log ("eval(" + varName + ")");
      line = line.substring (0,index) + eval(varName) + line.substring(index2+1);      
      console.log ("NewLine:" + line);
      index = line.indexOf ("$", index2+1);
    }
    if (content == '') {
      content = line;
    } else {
      content = content + '\n' + line;
    }
  }
  fs.writeFileSync (outFilename, content);
}

function buildModifyPage (response) {
   var msg = '\n<Table border=\"2\">';
   msg = msg + '\n<tr><th>Header1</th><th>Header2</th><th>Event Date</th><th>Start Time</th><th>End Time</th><th>Room 1</th><th>Room 2</th><th>Image Filename</th><th>Change Image</th><th>Update</th><th>Delete</th></tr>'
 
   var r1 = require ('readline').createInterface ({
     input: require ('fs').createReadStream ( __dirname + '/db.txt')
   });   
   
   // Page generation is called from here
   r1.on ('close', function() {
      filename = __dirname + '/modifyPage.html';
      msg = msg + '\n</Table>\n';
      msg = msg + '<br><input type=\"button\" value=\"Add Session\" onclick=\"location.href=\'' + serverAddress + '/config\';\">' 
      
      fs.open ( filename , 'w+', function (err,data) {
        if (err) {
          console.log ( 'err: ' + err);
        } else {        
                
          fs.write (data, '<html><head>\n' + 
          '<script src=\"socket.io-1.2.0.js\"></script>\n' + 
          '<Script>\nvar socket =io();\n' + 
          'function deleteSession(session) {\n' + 
          '  socket.emit (\"chat message\", \"delete \" + session);\n' + 
          '\n}\n' +
          'function updateImage(value, lineCount) {\n' +
          '  index = value.indexOf ( \'fakepath\');\n' +
          '  val = value.substring (index+9);\n' +
          '  val = \'\\\'\' + val + \'\\\'\';\n' +  
          '  nothing = \'\';\n' +           
          '  //alert ( \"in updateImage\ " + lineCount + \" \" + val );\n' + 
          '  msg = \'document.all.image\' + lineCount + \'.value = \' + val;\n' + 
          '  //alert(msg);\n' + 
          '  eval (msg);\n' +
          '  //alert ( document.all.thumbnail_0.value);\n' + 
          '  msg = \'document.all.thumbnail_\' + lineCount + \'.value=nothing\';\n' +
          '  //alert (msg);\n' +           
          '  //eval (msg);\n' + 
          '}\n' + 
          'function modifySession(session) {\n' +  
          '  msg = eval (\'document.all.n\' + session + \'.value;\');\n' +
          '  msg = msg + \'|\' + eval (\'document.all.description\' + session + \'.value;\');\n' +
          '  msg = msg + \'|\' + eval (\'document.all.eventDate\' + session + \'.value;\');\n' +
          '  msg = msg + \'|\' + eval (\'document.all.startTime\' + session + \'.value;\');\n' +
          '  msg = msg + \'|\' + eval (\'document.all.endTime\' + session + \'.value;\');\n' +
          '  msg = msg + \'|\' + eval (\'document.all.room1_\' + session + \'.checked;\');\n' +
          '  msg = msg + \'|\' + eval (\'document.all.room2_\' + session + \'.checked;\');\n' +
          '  msg = msg + \'|\' + eval (\'document.all.image\' + session + \'.value;\');\n' +
          '  //alert (msg);\n' +
          '  socket.emit (\"chat message\", \"modify \" + session + \" \" + msg );\n' + 
          '}\n' +           
          'socket.on(\'chat message\', function(msg){\n' + 
          '  index = msg.indexOf (\" \");\n' + 
          '   cmd = msg.substring (0,index);\n' + 
          '   parameter = msg.substring (index+1);\n' + 
          '   if (cmd == \'request\'){\n' + 
          '     newLocation = \'' + serverAddress + '/\' + parameter;\n' + 
          '     location.href = newLocation;\n' + 
          '   } else { \n' + 
          '      alert (\'cmd:\' + cmd + \' parameter:\' + parameter + \' message from server not handled.\')\n' + 
          '   }\n' + 
          '});\n' + 
          '</Script></head>' +          
          '<body><src=\"public\images\darth.jpg\">' + msg + '</body></html>\n', 
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

   var lineCount = 0
   r1.on ('line', function (line) {
      console.log ( 'Line from file: ' + line );
      
      data = line.split ('|');
      console.log ( 'data.length: ' + data.length);
      var i;
      msg = msg + '\n<tr>';
      for (i=0; i<data.length; i++) {
         if (i == 0) { // Name
           msg = msg + '<td><input name =\"n' + lineCount + '\"  value=\"' + data[i] + '\" ></td>';          
         } else if (i == 1) { // Description
           msg = msg + '<td><input name=\"description' + lineCount + '\" value=\"' + data[i] + '\" size=\"35\"></td>';          
         } else if (i == 2) { // Event Date
           msg = msg + '<td><input name=\"eventDate' + lineCount + '\" value=\"' + data[i] + '\" size=\"6\"></td>';          
         } else if (i == 3) { // Start time
           msg = msg + '<td><center><input name=\"startTime' + lineCount + '\" value=\"' + data[i] + '\" size=\"6\"></center></td>';          
         } else if (i==4) { // End time
           msg = msg + '<td><center><input name=\"endTime' + lineCount + '\" value=\"' + data[i] + '\" size=\"5\"></center></td>';                    
         } else if (i == 5) {
            if (data[i] == 'true')
              msg = msg + '<td><center><input type=\"checkbox\" name=\"room1_' + lineCount + '\" checked></center></td>'
            else
              msg = msg + '<td><center><input type=\"checkbox\" name=\"room1_' + lineCount + '\"></center></td>'             
         } else if (i == 6) {
            if (data[i] == 'true')
              msg = msg + '<td><center><input type=\"checkbox\" name=\"room2_' + lineCount + '\" checked></center></td>'                        
            else
              msg = msg + '<td><center><input type=\"checkbox\" name=\"room2_' + lineCount + '\"></center></td>'             
         } else if (i == 7) {
           msg = msg + '<td><center><input name=\"image' + lineCount + '\" value=\"' + data[i] + '\" size=\"20\"></center></td>';                    
         } 
      }
      if (data.length == 7) { // no image specified
         msg = msg + '<td><center><input name=\"image' + lineCount + '\" value=\"' + data[i] + '\" size=\"20\"></center></td>';                    
         msg = msg + '<td><input type=\"file\" name=\"thumbnail_' + lineCount + '\" value=\"No Image Defined\" onchange=\"javascript:updateImage(this.value,' + lineCount +');\");"></td>'
      } else {
         msg = msg + '<td><input type=\"file\" name=\"thumbnail_' + lineCount + '\" value=\"' + data[7] + '\" onchange=\"javascript:updateImage(this.value,' + lineCount + ');\"></td>'
      }   

      msg = msg + '<td><input type=\"button\" value=\"save\" onclick=\"modifySession(' + lineCount + ');\"></td><td><input type=\"button\" value=\"delete\" onclick=\"deleteSession(' + lineCount + ');\"></td></tr>\n';         
      lineCount = lineCount + 1;
   });
 
}

function generateHelpPage (response) {
   response.end ( '<html><body><img src=\"/images/darth.jpg\">\n' + 
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
                  '</ul>\n' +                   
                  
                  '</body></html>');
}

function generateContentPage (response, roomNumber) {
   var returnValue;
   var currentSession;
   var waitTime;
   var d = new Date();
   var sessionName;
   var startDate;
   var closestTime;
   var description
   var startingDate
   var startingTime
   var room1
   var room2
   var imageSrc
   
   currentTime = d.getHours() + ':' + d.getMinutes();
   console.log ( 'processStartTimes, currentTime = ' + currentTime);
   var r1 = require ('readline').createInterface ({
     input: require ('fs').createReadStream ( __dirname + '/db.txt')
   });   
   
   // Page generation is called from here
   r1.on ('close', function() {
     console.log ( 'End of file detected, returnvalue: ' + returnValue);
     if (currentSession == undefined) {
        console.log ( "Current time not in any session zones, send waiting page");
        createWaitPage (response,sessionName,description, waitTime, startingDate, startingTime, room1, room2, imageSrc)
     } else {
        console.log ( "Current time in zone for: " + returnValue + " send appropriate content");
        filename = __dirname + '/contentPage.html'
        console.log ( 'sessionName: ' + sessionName + ' description: ' + description )
        createContentPage (filename, response, sessionName, description, startingTime, endingTime, room1, room2,imageSrc );
        response.sendFile(filename);    
     }
   });

   r1.on ('line', function (line) {
      console.log ( 'Line from file: ' + line );
      data = line.split ('|');
      startDate = data[2];
      name = data[0];
      r1 = data[5];
      r2 = data[6];
      timeUntilStart = SecondsUntil (startDate + ' ' + data[3]);
      console.log ( 'data[4]:' + data[4]);
      if (data[4] = '24:00') {
         data[4] = '23:59';
      }
      console.log ('data[4]:' + data[4]);
      timeUntilEnd = SecondsUntil (startDate + ' ' + data[4]);
      if (timeUntilEnd == NaN) {
         timeUntilEnd = SecondsUntil (startDate + ' 23:59')
         console.log ( 'timeUntilEnd == NaN so using 23:59' );
      }
      
      roomMatches = ((r1 == 'true') && (roomNumber == 1)) || ((r2 == 'true') && (roomNumber == 2));       
      if (roomMatches) {
         console.log ( 'Room Matches, timeUntilStart: ' + timeUntilStart + ' timeUntilEnd: ' + timeUntilEnd);
         
         if ((timeUntilStart <= 0) && (timeUntilEnd > 0)) { // We are in the zone 
            console.log ( 'We are in the zone...got a match with ' + line);
            currentSession = name;
            sessionName = name;
            description = data[1];
            startTime = data[3].split(':');
            startingTime = startTime[0] + ':' + startTime[1];
            endTime = data[4].split(':');
            imageSrc = data[7];
            endingTime = endTime[0] + ':' + endTime[1];             
            returnValue = line;         
            console.log ('We are in the zone');    
            closestTime = 0; 
            room1 = r1;
            room2 = r2;  
            closestTime = 0;            
         } else if (timeUntilStart > 0) { // future time          
            if (closestTime == undefined) {
              closestTime = timeUntilStart;
              console.log ( 'Initialize closest time to: ' + startDate + ' ' + data[3]);
              sessionName = name;
              description = data[1];
              startTime = data[3].split(':');
              startingTime = startTime[0] + ':' + startTime[1];
              endTime = data[4].split(':');
              endingTime = endTime[0] + ':' + endTime[1];             
              returnValue = line;   
              imageSrc = data[7];              
              if (timeUntilStart > 86400) 
                 waitTime = -1;
              else
                 waitTime = timeUntilStart;              
              startingDate = startDate + ' ' + startingTime;
              room1 = r1;
              room2 = r2;
            } else if ((timeUntilStart < closestTime) && (closestTime != 0)) {
              console.log ( 'closestTime: ' + closestTime + ' timeUntilStart: ' + timeUntilStart);
              console.log ( 'We have a new closest time: ' + startDate + ' ' + data[3]);
              closestTime = timeUntilStart;
              console.log ( 'Initialize closest time to: ' + startDate + ' ' + data[3]);
              sessionName = name;
              description = data[1];
              startTime = data[3].split(':');
              startingTime = startTime[0] + ':' + startTime[1];
              endTime = data[4].split(':');
              endingTime = endTime[0] + ':' + endTime[1];             
              returnValue = line;  
              imageSrc = data[7];             
              if (timeUntilStart > 86400)
                 waitTime = -1;
              else
                 waitTime = timeUntilStart;              
              startingDate = startDate + ' ' + startingTime;
              room1 = r1;
              room2 = r2;
            }          
         } 
      }          
   });
}


app.post('/file-upload',function(req,res){
    console.log ( 'req: ' + req.body.thumbnail)
    upload(req,res,function(err) {
        if(err) {
            return res.end("Error uploading file.");
        }
        res.end("<html><body>File has been uploaded thank you<script>window.history.back();</script></body></html>");
    });
});
/*
app.post ('/file-upload', function (req,res,next){
   console.log ( 'Got an upload request!');
   console.log (req.params);
   console.log (req.body);
   console.log (req.body.thumbnail);
   console.log (req.files);
   
   var tmp_path = req.files.thumbnail.path;
   var target_path = './public/images/' + req.files.thumbnail.name;
   fs.rename (tmp_path, target_path, function (err) {
     if (err) throw err;
     fs.unlink(tmp_path, function(){
        if (err) throw err;
        res.send ('File uploaded to: ' + target_path + ' - ' + req.files.thumbnail.size + ' bytes ');
     })
   })
   
});
*/


app.get('/content', function(req, res){
  console.log ( '/content is deprecated and should no longer be used')
});

app.get('/room1', function(req, res){
  generateContentPage(res,1);
});

app.get('/room2', function(req, res){
  generateContentPage(res,2);
});

app.get('/writedata', function(req, res){
  console.log ( '/temp.html created')
  response = res;
  createPage ( __dirname + '/temp.html');
});

app.get('/readdata', function(req, res){
  res.sendFile(__dirname + '/readData.html');
  console.log ( 'Data Read:')
  fs.readFile ( 'c:\\fiverr\\ClientServer\\tmp.txt', 'utf8', function (err,data){
     if (err) {
        return console.log(err);
     }
     console.log (data);     
  });
});

app.get('/', function(req, res){
  generateHelpPage(res);
});

app.use(express.static(__dirname + '/public'));
io.on('connection', function(socket){
  socket.on('chat message', function(msg){ // chat message received on socket
    index = msg.indexOf (" ");
    cmd = msg.substring (0,index);
    d = msg.substring (index+1);
    if (cmd == 'config') {
       filename = __dirname + '/db.txt';
       newLine = d;
       index = newLine.indexOf ( '|C:\\fakepath\\');
       if (index >= 0) {
         newLine = newLine.substring (0,index) + '|' + newLine.substring (index+13);
         console.log ( 'new, newLine: ' + newLine);
       }
       appendFile (filename, '\n' + newLine);
       console.log ( 'Got config command');
       var data = d.split ( "|");
       var i;
       for (i=0; i<data.length; i++) {
          console.log ( data[i]);
       }   
       emit ( 'request contentpage');       
    } else if (cmd == 'delete') {
       modifyLine (d, '', 'request modify');
    } else if (cmd == 'modify') {
       var data = msg.split ( " "); 
       session = parseInt(data[1]);
       newLine = msg.substring ( index + data[1].length + 2);
       index = newLine.indexOf ( '|C:\\fakepath\\');
       if (index >= 0) {
         newLine = newLine.substring (0,index) + '|' + newLine.substring (index+13);
         console.log ( 'new, newLine: ' + newLine);
       }  
       modifyLine (session, newLine, 'request modify')
    } else if (cmd == 'time') {
       serverTime = d;
       console.log ( 'Got a new time of: ' + d + ' TODO:create a python file and run it.');         
       var filename = 'public/setTime.py';
       buildPythonTime(filename);    
       runPython (filename)       
    } else {
       console.log ( 'Could not handle command: ' + cmd );
    }   
  });
});

// Set the port that the server will listen on 
http.listen(3000, function(){
  console.log('listening on *:3000');
});