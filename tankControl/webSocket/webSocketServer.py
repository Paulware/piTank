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

#Tell the user the count of users.
def users_event():
    return json.dumps({"type": "users", "count": len(USERS)})

async def notify_state():
    try: 
        if USERS:  # asyncio.wait doesn't accept an empty list
            message = state_event()
            print (message)
            print ( 'send [' + message + '] to: ' + str(USERS))
            await asyncio.wait([user.send(message) for user in USERS])
    except Exception as ex:
        print ( 'notify_state, exception: ' + str(ex)) 

async def notify_users():
    try: 
        if USERS:  # asyncio.wait doesn't accept an empty list
            message = users_event()
            print ( message )
            await asyncio.wait([user.send(message) for user in USERS])
    except Exception as ex:
        print ( 'notify_users, exception: ' + str(ex)) 

async def register(websocket):
    try: 
        USERS.add(websocket)    
        print ('user registered'+str(websocket))

        for tank in TANKS:
           print ( 'This tank has already joined the webserver: ' + tank[0] ) 
           tankName = tank[0]
           if tankName in cameraIpAddresses.keys():
              cameraAddress = cameraIpAddresses[tankName]
              action = json.dumps({"type": "tankonline", "name": tankName, "cameraAddress":cameraAddress})
              print ( "Got a cameraAddress of : " + cameraAddress )
           else:
              action = json.dumps({"type": "tankonline", "name": tankName})                  
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

async def handleEvents(websocket, path):
    global quit

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
                  print ( 'add list [name,websocket] to TANKS')
                  TANKS.append ([name,websocket])
                  print ( 'Number of tanks in system: ' + str(len(TANKS))) 
                  print ( 'This tank is joining the webserver: ' + name + ' with cameraIp: ' + cameraIp + ':' + cameraPort) 
                  for user in USERS:# Notify users that a tank has joined. 
                     action = json.dumps({"type": "tankonline", "name": name, "cameraAddress":cameraIp, "cameraPort":cameraPort})
                     await asyncio.wait ([user.send (action)]);
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
      if (time.time() - startTime) > 60: 
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