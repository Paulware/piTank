local SSID
local Password
local filename = "ssidPassword.txt"
local timer1 = tmr.create()

sensorAddress = nil
command = ""
ip = nil
MAC = wifi.sta.getmac()
uart.setup (0,9600,8,0,1) -- Setup to read from usb port 
wifi.setmode(wifi.STATION)

function trim(s)
  return s:match "^%s*(.-)%s*$"
end

function readInfo() 
   f = file.open (filename, "r")
   if (f ~= nil) then 
      SSID = trim(file.readline())
      Password = trim(file.readline())
      file.close()
   end    
end

function init() 
  file.open (filename, "w")
  file.writeline ("MySSID")
  file.writeline ("MyPassword")
  file.close()
end

function joinNetwork()
   ip = wifi.sta.getip()      
   if ip == nil then
      configStation() 
      timer1:alarm(6000, tmr.ALARM_SINGLE, joinNetwork)       
      print ("?")
   else   
      print (ip) 
   end
end

function writeInfo() 
  print ("Writing info to "..filename )
  file.open (filename, "w")
  file.writeline (SSID)
  file.writeline (Password)
  file.close()
end 

function login (ssid,password) 
  SSID = ssid
  Password = password
  writeInfo()
  timer1:alarm(2000, tmr.ALARM_SINGLE, loginNetwork) 
end

function oldConfig() 
   wifi.sta.config(SSID, Password)
end 
function newConfig()
   station_cfg={}
   station_cfg.ssid=SSID
   station_cfg.pwd=Password
   station_cfg.save=true   
   wifi.sta.config(station_cfg)
end 
function configStation () 
   if not pcall (oldConfig) then   
      newConfig() 
   end 
end 

function loginNetwork()
   if SSID == nil then 
      timer1:alarm(2000, tmr.ALARM_SINGLE, loginNetwork) 
   else
      configStation()
      timer1:alarm(6000, tmr.ALARM_SINGLE, joinNetwork) 
   end
end 

function startListening()
  -- Listen on udp port 3333 for a broadcast of server address
  srv=net.createServer(net.UDP)
  srv:on("receive", function(connection, pl)
     print("Command Received "..pl)
     
     -- Get server address
     if string.sub (pl,0,6) == "server" then
         print ("Server address received.") 
         if serverAddress == nil then          
            serverAddress = string.sub (pl, 8) 
            print ("serverAddress:"..serverAddress )
            dofile ("sensor.lua")
         end
     end
   end)
  srv:listen(3333) -- port == 3333
end 

function delFiles()
   for k,v in pairs(file.list()) do 
      file.remove (k)
   end
   for k,v in pairs(file.list()) do 
      l = string.format("%-15s",k)
   end
end

-- This function only needs to be called once to login to the network
function initReceiver()
  readInfo()
  wifi.setmode(wifi.STATION)
  loginNetwork()
end 

startListening()
print ("login if you are ready")
