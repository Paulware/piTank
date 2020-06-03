print ( 'MAC:'..MAC)
local ws = websocket.createClient()
ws:on("connection", function(ws)
  print('got ws connection')
  ws:send ("Hello")
end)
ws:on("receive", function(_, msg, opcode)
  print('got message:', msg, opcode) -- opcode is 1 for text message, 2 for binary
end)
ws:on("close", function(_, status)
  print('connection closed', status)
  ws = nil -- required to lua gc the websocket client
end)
msg = 'ws://'..serverAddress..':5678'
print ( 'connect to: '..msg)
ws:connect(msg)
