print ( 'MAC:'..MAC)
local ws = websocket.createClient()
ws:on("connection", function(ws)
  print ( 'SsUu' )
  ws:send ("Hello")
end)
ws:on("receive", function(_, msg, opcode)
  -- print('got message:', msg, opcode) -- opcode is 1 for text message, 2 for binary
  i, j = string.find(msg, "forward")
  if i ~= nil then
     print ("LR")
  else 
     i,j = string.find (msg, "reverse")
     if i ~= nil then 
        print ("lr")   
     else
        i,j = string.find (msg, "stop")
        if i ~= nil then
           print ("Ss")
        else 
           i,j = string.find (msg, "right")
           if i ~= nil then
              print ("Lr")
           else
              i,j = string.find (msg, "left")
              if i ~= nil then
                 print ("lR")
              else 
                 i,j = string.find (msg, "fire")
                 if i ~= nil then
                    print ("F")
                 end
              end
           end 
        end 
     end      
  end 
end)
ws:on("close", function(_, status)
  print('connection closed', status)
  ws = nil -- required to lua gc the websocket client
end)
msg = 'ws://'..serverAddress..':5678'
print ( 'connect to: '..msg)
ws:connect(msg)
