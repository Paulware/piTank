import asyncio
import datetime
import random
import websockets

@asyncio.coroutine
def time(websocket, path):
    while True:
        now = datetime.datetime.utcnow().isoformat() + 'Z'
        if not websocket.open:
            return
        yield from websocket.send(now)
        yield from asyncio.sleep(random.random() * 3)

print ( "example 4:5678" )
start_server = websockets.serve(time, '0.0.0.0', 5678)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()