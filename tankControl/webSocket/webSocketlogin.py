#!/usr/bin/env python

import asyncio
import json   
import logging # Necessary?
import websockets
from threading import Thread
import socket
import time
from subprocess import check_output
import sys

cameraIpAddresses = {}

udpCount = 0
quit = False 
loginNames = {} 
hitCounts = {}

def getVehicleAssignment (username): 
   vehicle = 'None'
   if username == 'Sean': 
      vehicle = 'M26b'
   elif username == 'Bryce':
      vehicle = 'King Tiger A'
   elif username == 'Paul':
      vehicle = 'Tiger1 A'
   return vehicle 
   
def findUser (tank):
   user = ""
   if getVehicleAssignment('Paul') == tank: 
      user = 'Paul'
   elif getVehicleAssignment ('Sean') == tank:
      user = 'Sean'
   elif getVehicleAssignment ('Bryce') == tank:
      user = 'Bryce'   
   if user == "": 
      print ( "Count not find a user for tank: " + tank)
   else:
      print ( user + " is using " + tank)
   return user
      
def goodPassword ( username, password ):
   good = False 
   if (username == 'Sean') and (password == 'naeS'): 
      good = True
   elif (username == 'Bryce') and (password == 'ecyrB'):
      good = True
   elif (username=='Paul') and (password == 'luaP'):
      good = True
   return good   
   
'''
   Send the address of the server to the tank receivers so that they can login. 
'''
def broadcastAddress(): 
   global sock
   global udpCount
   
   port = 3333
   if sys.platform == 'win32': 
      myAddress = socket.gethostbyname(socket.gethostname())   
   else:
      myAddress = check_output (['hostname','-I']).decode().strip()
      if myAddress.find (' ') > -1: 
         data = myAddress.split ( ' ')
         myAddress = data[1]
         
   gethostname = socket.gethostbyname(socket.gethostname()) 
   print ('[gethostname]: [' + gethostname + ']')
   print ('[myAddress]: [' + myAddress + ']')
   index = myAddress.rfind ('.')
   clientIp = myAddress[0:index] + '.255'
   msg = 'server ' + myAddress
   udpCount = udpCount + 1
   print (str(udpCount) + ' Send ' + msg + ' to ' + clientIp + ':' + str(port) + '\n')
   sock.sendto(msg.encode(), (clientIp, port))  
   
def state_event():
    print ( "STATE: " + str(STATE)) 
    return json.dumps({"type": "state", **STATE})

async def notify_state():
    try: 
        if USERS:  # asyncio.wait doesn't accept an empty list
            message = state_event()
            print (message)
            print ( 'send [' + message + '] to: ' + str(USERS))
            await asyncio.wait([user.send(message) for user in USERS])
    except Exception as ex:
        print ( 'notify_state, exception: ' + str(ex)) 

# Update all users with an updated count of users        
async def notify_users():
    try: 
        if USERS:  # asyncio.wait doesn't accept an empty list
            message = json.dumps({"type": "users", "count": len(USERS)})
            print ( message )
            await asyncio.wait([user.send(message) for user in USERS])
    except Exception as ex:
        print ( 'notify_users, exception: ' + str(ex)) 

# A player is registering...        
async def register(websocket):
    print ( 'A player is registering...')
    try: 
        USERS.add(websocket)    
        print ('user registered'+str(websocket))
        action = json.dumps({"type": "login", "name": "You"})        
        await asyncio.wait ([websocket.send (action)]); 
        
        await notify_users() # Update all users with the new count of users
    except Exception as ex:
        print ( 'register, exception: ' + str(ex)) 

async def unregister(websocket):
    try: 
       USERS.remove(websocket)
       await notify_users()
    except Exception as ex:
       print ( 'unregister, exception: ' + str(ex)) 
      
def lookupPortForwarded (cameraIp):
   portForwarded='79';
   if cameraIp == '192.168.0.18':
      portForwarded = '85'
   elif cameraIp == '192.168.0.4':
      portForwarded = '81'
   elif cameraIp == '192.168.0.16':
      portForwarded = '83'
   elif cameraIp == '192.168.0.17':
      portForwarded = '84'
   elif cameraIp == '192.168.0.19':
      portForwarded = '86'
   elif cameraIp == '192.168.0.20':
      portForwarded = '87'
   elif cameraIp == '192.168.0.21':
      portForwarded = '88'

   return portForwarded;
      
      
async def handleEvents(websocket, path):
    global quit
    global loginNames
    global hitCounts

    await register(websocket); # Add the user sends all tank data to all users
    try:
        await websocket.send(state_event())
        
        ##if sys.platform == 'win32' you may need the next line instead of the while True 
        #async for message in websocket:
        
        # python 3.5 solution
        while True:
            message = await websocket.recv() # needed for python 3.5
            
            #print ( 'client: [' + str(message) + ']' )
            try: 
               data = json.loads(message)
               #print ( 'got data: ' + str(data)) 
               if 'action' in data:
                  action = data['action'];
                  print ( 'got action: ' + action )                  
                  if action == 'login': # User is logging in
                     username = str(data['username'])
                     password = str(data['password'])
                     print ( "Adding " + username + " to loginNames dictionary" )
                     loginNames[username] = websocket
                     hitCounts[username] = 0
                     print ( 'Got [username,password]: [' + username + ',' + password + ']')
                     if goodPassword ( username,password): 
                       action = json.dumps({"type": "welcome", "message":"Welcome " + username})
                       await asyncio.wait ([websocket.send (action)])
                       vehicle = getVehicleAssignment (username);
                       myTankId = ""
                       for tank in TANKS:
                           tankName = tank[0]
                           if tankName.find (vehicle) > -1: 
                              print ( 'Found tank ' + tankName + ' for vehicle: ' + vehicle)
                              myTankId = tankName
                              print ( 'myTankId: ' + myTankId)
                              break                   
                       if myTankId == "": 
                          action = json.dumps({"type": "alert", "message":"Your tank " + vehicle + " has not logged in yet..."})
                          print ("send command: " + str(action))
                          await asyncio.wait ([websocket.send (action)])
                       else:    
                          cameraIpPort = cameraIpAddresses [myTankId]
                          data = cameraIpPort.split ( ':' )
                          cameraIp = data[0]
                          cameraPort = data[1]
                          externalPort = lookupPortForwarded (cameraIp);
                          action = json.dumps({"type": "tankonline", "name": myTankId, "cameraAddress":cameraIp, "cameraPort":cameraPort, "portForwarded":externalPort})
                          await asyncio.wait ([websocket.send (action)]);                       
                          action = json.dumps({"type": "assign", "id":myTankId})
                          print ( "Send command: " + str(action) )
                          await asyncio.wait ([websocket.send (action)])                                              
                     else: 
                       action = json.dumps({"type": "alert", "message":"Incorrect username or password"})
                       await asyncio.wait ([websocket.send (action)])
                  elif action == 'hit': # this tank has got a hit. 
                     print ( "Received notification that hit detected")
                     tank = str(data['tank'])
                     hitName = findUser (tank)
                     hitCounts[hitName] = hitCounts[hitName] + 1
                     sendSocket = None
                     for name in loginNames:
                        print ( "Does name " + str(name) + "== hitName " + str(hitName) + "?")
                        if name == hitName: 
                           print ( "I found the login name")
                           sendSocket = loginNames[name]
                           action = json.dumps({"type": "hit","count":hitCounts[hitName]})        
                           print ( "sending action: " + str(action))
                           await asyncio.wait ([sendSocket.send (action)]); 
                           break
                  else: 
                     vehicle = data['vehicle'];
                     print ( 'got vehicle: ' + vehicle)
                     name = data['name'];
                     print ( 'got name: ' + name )
                     
                     print ( 'got action: ' + str(action) + ' and name: ' + name )
                     if len(USERS) == 0: 
                        print ( 'No USERS registered yet' )
                     elif (action in ['left','right','forward','reverse','stop','fire','left turret','right turret', 'up turret', 'down turret', 'stop turret', 'start']):
                        print ( 'HandleEvents iterate through tanks')
                        for tank in TANKS:
                           tankName = tank[0]
                           if tankName == name: 
                              print ('Send command: ' + action + ' to tank: ' + tankName )
                              socket = tank[1]
                              await asyncio.wait ([socket.send(action)])
                     else:
                        print ( 'action: [' + action + '] not found in list')
               elif 'tank' in data: # Tank is joining the web-server                  
                  name = str(data['tank'])
                  cameraIp = str(data['cameraIp'])
                  cameraPort = str(data['cameraPort'])
                  print ( 'Adding cameraIp+port to cameraIpAddresses ' + cameraIp + ':' + cameraPort)
                  cameraIpAddresses [name]  = cameraIp + ':' + cameraPort                  
                  print ( 'add [name,websocket] to TANKS: [' + name + ',websocket]')
                  TANKS.append ([name,websocket])
                  print ( 'Number of tanks in system: ' + str(len(TANKS))) 
                  print ( 'This tank is joining the webserver: ' + name + ' with cameraIp: ' + cameraIp + ':' + cameraPort) 
                  #for user in USERS:# Notify users that a tank has joined. 
                  #   action = json.dumps({"type": "tankonline", "name": name, "cameraAddress":cameraIp, "cameraPort":cameraPort})
                  #   await asyncio.wait ([user.send (action)]);
            except Exception as ex:
               print ( 'handleEvents, exception: ' + str(ex))             
               print ( 'message: ' + message )
    except Exception as ex:
        print ( 'perhaps disconnected?' + str(ex) )  
    finally:
        try: 
            await unregister(websocket)
        except Exception as ex:
            print ( "Cannot unregister, perhaps it is disconnected yo" + str(ex)) 

def broadcastServerAddress(): 
   global quit
   startTime = time.time() 
   while not quit:
      if (time.time() - startTime) > 20: 
         broadcastAddress ()
         startTime = time.time()
      time.sleep (1)         
      
   print ("broadcastServerAddress done quit: " + str(quit))
      
if sys.platform == 'linux': 
   print ( "linux platform: ")
   sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
   sock.setsockopt (socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
   sock.setsockopt (socket.SOL_SOCKET, socket.SO_BROADCAST, 1)      
else: # Windows 
   sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        
logging.basicConfig()
STATE = {"value": 0}
USERS = set()   
TANKS = list()     

broadcastAddress()
broadcastThread = Thread(target=broadcastServerAddress)
broadcastThread.start()

print ( 'ident: ' + str(broadcastThread.ident ))
myAddress = socket.gethostbyname(socket.gethostname())
print ("myAddress: " + myAddress)        
print ( "Serve 0.0.0.0:9876")
start_server = websockets.serve(handleEvents, "0.0.0.0", 9876) # Forever handle events 

asyncio.get_event_loop().run_until_complete(start_server)
try: 
   asyncio.get_event_loop().run_forever()
finally: 
   quit = True