import asyncio
import websockets

@asyncio.coroutine
def hello(websocket, path):
    name = yield from websocket.recv()
    print("< {}".format(name))
    greeting = "Hello {}!".format(name)

    yield from websocket.send(greeting)
    print("> {}".format(greeting))

print ( "Example 3 0.0.0.0:5678" )     
start_server = websockets.serve(hello, '0.0.0.0', 5678)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()