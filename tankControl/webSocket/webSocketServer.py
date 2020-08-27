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
cameraIpAddresses ['Tiger']  = '192.168.0.4:81/stream'
cameraIpAddresses ['King Tiger'] = '192.168.0.8:82/stream'
cameraIpAddresses ['Other'] = '192.168.0.9:83/stream'

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
   print (myAddress)
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
    if USERS:  # asyncio.wait doesn't accept an empty list
        # print ( "USERS: " + str(USERS)) 
        # print ( "STATE: " + str(STATE)) 
        message = state_event()
        print (message)
        await asyncio.wait([user.send(message) for user in USERS])

async def notify_users():
    if USERS:  # asyncio.wait doesn't accept an empty list
        message = users_event()
        print ( message )
        await asyncio.wait([user.send(message) for user in USERS])

async def register(websocket):
    USERS.add(websocket)    
    print ('user registered'+str(websocket))

    for tank in TANKS:
       print ( 'This tank has already joined the webserver: ' + tank ) 
       
       if tank in cameraIpAddresses.keys():
          cameraAddress = cameraIpAddresses[tank]
          action = json.dumps({"type": "tankonline", "name": tank, "cameraAddress":cameraAddress})
       else:
          action = json.dumps({"type": "tankonline", "name": tank})                  
       await asyncio.wait ([websocket.send (action)]);    
    
    await notify_users() # Update all users with the new count of users

async def unregister(websocket):
    USERS.remove(websocket)
    await notify_users()

async def counter(websocket, path):
    global quit
    # register(websocket) sends user_event() to websocket
    await register(websocket);
    try:
        await websocket.send(state_event())
        async for message in websocket:
            #print ( 'client: [' + str(message) + ']' )
            try: 
               data = json.loads(message)
               #print ( 'got data: ' + str(data)) 
               if 'action' in data:
                  action = data['action']
                  print ( 'got action: ' + str(action))
                  if len(USERS) == 0: 
                     print ( 'No USERS registered yet' )
                  elif (action in ['left','right','forward','reverse','stop','fire','left turret','right turret', 'up turret', 'down turret', 'stop turret', 'start']):
                     for user in USERS:
                        print ( 'send action ' + action + ' to ' + str(user)) 
                        await asyncio.wait([user.send(action)])
                  else:
                     print ( 'action: [' + action + '] not found in list')
               elif 'tank' in data:                  
                  name = str(data['tank'])
                  TANKS.add (name)
                  print ( 'This tank is joining the webserver: ' + name ) 
                  for user in USERS:# Notify users that a tank has joined. 
                     if name in cameraIpAddresses.keys():
                        cameraAddress = cameraIpAddresses[name]
                        action = json.dumps({"type": "tankonline", "name": name, "cameraAddress":cameraAddress})
                     else:
                        action = json.dumps({"type": "tankonline", "name": name})                  
                     await asyncio.wait ([user.send (action)]);
            except Exception as ex: 
               print ( 'Not a json object: ' + message + ' ex: ' + str(ex) )
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
      if (time.time() - startTime) > 10: 
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
TANKS = set()     

broadcastAddress()
broadcastThread = Thread(target=broadcastServerAddress)
broadcastThread.start()

print ( 'ident: ' + str(broadcastThread.ident ))
myAddress = socket.gethostbyname(socket.gethostname())
print ("myAddress: " + myAddress)        
print ( "Serve 0.0.0.0:9876")
start_server = websockets.serve(counter, "0.0.0.0", 9876)

asyncio.get_event_loop().run_until_complete(start_server)
try: 
   asyncio.get_event_loop().run_forever()
finally: 
   quit = True


