#!/usr/bin/env python

import asyncio
import json    # Necessary?
import logging # Necessary?
import websockets
from threading import Thread
import socket
import time

def broadcastAddress(): 
   global sock
   port = 3333
   myAddress = socket.gethostbyname(socket.gethostname())
   print (myAddress)
   index = myAddress.rfind ('.')
   clientIp = myAddress[0:index] + '.255'
   msg = 'server ' + myAddress
   print ('Send ' + msg + ' to ' + clientIp + ':' + str(port) + '\n')
   msg = msg.encode()
   sock.sendto(msg, (clientIp, port))  
   
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
    print ('user registered')
    await notify_users()

async def unregister(websocket):
    USERS.remove(websocket)
    await notify_users()

async def counter(websocket, path):
    # register(websocket) sends user_event() to websocket
    await register(websocket)
    try:
        await websocket.send(state_event())
        async for message in websocket:
            print ( 'client: [' + str(message) + ']' )
    finally:
        await unregister(websocket)

def broadcastServerAddress(): 
   quit = False # TODO provide a mechanism to stop 
   while not quit:
      time.sleep (30)         
      broadcastAddress ()
      
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        
logging.basicConfig()
STATE = {"value": 0}
USERS = set()        

broadcastThread = Thread(target=broadcastServerAddress)
broadcastThread.start()

        
print ( "Serve 0.0.0.0:5678")
start_server = websockets.serve(counter, "0.0.0.0", 5678)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()


