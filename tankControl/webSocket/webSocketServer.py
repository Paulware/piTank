#!/usr/bin/env python

import asyncio
import json   
import logging # Necessary?
import websockets
from threading import Thread
import socket
import time


udpCount = 0
quit = False 
def broadcastAddress(): 
   global sock
   global udpCount
   
   port = 3333
   myAddress = socket.gethostbyname(socket.gethostname())
   print (myAddress)
   index = myAddress.rfind ('.')
   clientIp = myAddress[0:index] + '.255'
   msg = 'server ' + myAddress
   udpCount = udpCount + 1
   print (str(udpCount) + ' Send ' + msg + ' to ' + clientIp + ':' + str(port) + '\n')
   sock.sendto(msg.encode(), (clientIp, port))  
   
def state_event():
    return json.dumps({"type": "state", **STATE})

def users_event():
    return json.dumps({"type": "users", "count": len(USERS)})

async def notify_state():
    if USERS:  # asyncio.wait doesn't accept an empty list
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
    await notify_users()

async def unregister(websocket):
    USERS.remove(websocket)
    await notify_users()

async def counter(websocket, path):
    global quit
    # register(websocket) sends user_event() to websocket
    await register(websocket)
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
                  if (action in ['left','right','forward','reverse','stop','fire','left turret','right turret', 'up turret', 'down turret', 'stop turret']):
                     await asyncio.wait([user.send(action) for user in USERS])
            except Exception as ex: 
               print ( 'Not a json object: ' + message)
    finally:
        await unregister(websocket)
        quit = True 

def broadcastServerAddress(): 
   global quit
   startTime = time.time() 
   while not quit:
      if (time.time() - startTime) > 10: 
         broadcastAddress ()
         startTime = time.time()
      time.sleep (1)         
      
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        
logging.basicConfig()
STATE = {"value": 0}
USERS = set()        

broadcastAddress()
broadcastThread = Thread(target=broadcastServerAddress)
broadcastThread.start()

print ( 'ident: ' + str(broadcastThread.ident ))
        
print ( "Serve 0.0.0.0:5678")
start_server = websockets.serve(counter, "0.0.0.0", 5678)

asyncio.get_event_loop().run_until_complete(start_server)
try: 
   asyncio.get_event_loop().run_forever()
finally: 
   quit = True


