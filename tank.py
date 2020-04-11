import inspect

def tankPage():
   global joining 
   global move 
   global iAmHost
   global enemyShot
   global shot
   global explosion
   
   SQUAREWIDTH = 50
   BOARDY = 50
   BOARDX = 100 
   RADIUS = int((SQUAREWIDTH/2) - 10)
   OFFSET = 0   
   shot = None  
   enemyShot = None   
   explosion = None
   Object = type('Object', (object,), {} ) # Generic object definition
   showStatus ( 'iAmHost: ' + str(iAmHost) )    
   move = None
   lost = None
      
   pieces = [  #   id,  image,            image,                                          x   y    angle, health 
                ['white',extractImage ('images/tanks.png', 0, 0, 164, 212, 60, 80) ,     (100,100), 45,   100],\
                ['black',extractImage ('images/tanks.png', 168, 428, 340, 605, 60, 80),  (400,400), 135,  100] \
            ]

   walls = [
                pygame.Rect(150,100,30,200), \
                pygame.Rect(250,300,250,30), \
           ] 
   def wallCollide(x,y): 
      collide = False
      for wall in walls:       
         if wall.collidepoint ((x,y)):
            collide = True
            break            
         
      return collide           
   def inBoard (x,y):
      insideBoard = False
      if (x >= BOARDX) and (y >= BOARDY):
         if (x <= (BOARDX+(8*SQUAREWIDTH))) and (y <= (BOARDY+(8*SQUAREWIDTH))): 
            insideBoard = True
      return insideBoard
      
   def legalMove (selectedIndex, x, y, color):
      legal = True
      if color == 'white':
         (fromX,fromY) = whiteLocations[selectedIndex]
      else:
         (fromX,fromY) = blackLocations[selectedIndex]
      if (fromX == x) and (fromY == y):
         showStatus ( 'Cannot move to same position' )
         legal = False
      return legal
    
   def xToPixel (x):
      return BOARDX + (x * SQUAREWIDTH)
      
   def yToPixel (y):
      return BOARDY + (y * SQUAREWIDTH)
      
   def posToXY (x,y):
      x = int((x - BOARDX)/ 50) 
      y = int((y - BOARDY)/ 50)
      return (x,y)   

   # (x,y) is board square location not pixels       
   def findBlackPiece (x,y):  
      piece = -1
      count = 0
      for location in blackLocations: 
         if (x == location[0]) and (y == location[1]):
            piece = count
            break
         count = count + 1
      return piece 

   # (x,y) is board square location (not pixels)      
   def findWhitePiece (x,y):  
      piece = -1
      count = 0
      for location in whiteLocations: 
         if (x == location[0]) and (y == location[1]):
            piece = count
            break
         count = count + 1
      return piece 
      

   def drawBoard(): 
      global shot
      DISPLAYSURF.fill((WHITE)) 
   
      for wall in walls:
         pygame.draw.rect (DISPLAYSURF, (255, 0, 0), (wall[0],wall[1],wall[2],wall[3])) 
      count = 0
      for piece in pieces:
         x = piece[2][0]
         y = piece[2][1]
         img = piece[1]
         angle = piece[3]
         blitRotate (img, (x,y), angle) # Rotate image to current angle
         (w,h) = img.get_size()
         rect = pygame.Rect ( x, y, w, h) 
         if shot != None: 
            if rect.collidepoint ( (shot.x,shot.y) ):
               udpBroadcast ( 'exec:move=(\'explosion\','+ str(shot.x) + ',' + str(shot.y) + ')')
               image = pygame.image.load ( 'images/explosion.png').convert_alpha()               
               DISPLAYSURF.blit (image, (shot.x-100, shot.y-150 ))
               showStatus ( "You Win Yo" )
               shot = None
         if explosion != None:
            image = pygame.image.load ( 'images/explosion.png').convert_alpha()               
            DISPLAYSURF.blit (image, (explosion.x-100, explosion.y-150 ))
            showStatus ( "You Lost Sorry" )

         count = count + 1
      
      if enemyShot != None: 
         pygame.draw.circle(DISPLAYSURF, BLACK, (enemyShot.x,enemyShot.y), 2, 2)
               
      if shot != None:      
         pygame.draw.circle(DISPLAYSURF, BLACK, (shot.x,shot.y), 2, 2)
      
      pygame.display.update()        
         
   def angleXY(x,y,speed,degrees):
      degrees = degrees - 90.0# adjust for picture direction
      degrees = int(degrees) % 360
      angle_in_radians = float(degrees) / 180.0 * math.pi
      new_x = x + int(float(speed)*math.cos(angle_in_radians))
      new_y = y - int(float(speed)*math.sin(angle_in_radians))
      return new_x, new_y
         
   # Show screen
   pygame.display.set_caption('Play Tank Combat')         
   showStatus ( "Waiting for player to join")
   
   if iAmHost:
      # Set opponents list of games
      udpBroadcast ( 'exec:games=[\'Tank\']')
      joining = ''
      playerJoined = False
      myTurn = True
   else:
      udpBroadcast ( 'exec:joining=\'Tank\'')
      joining = 'Tank' # Opponent should be waiting
      move = None
      myTurn = False

   drawBoard()
   (images,sprites) = showImages (['images/quit.jpg'], [(400,500)] )      
   pygame.display.update()

      
   autoKey = ''
   quit = False    
   selectedIndex = None # necessary?
   autoTime = time.time()
   moveTimeout = 0.09
   shotTimeout = time.time() + 0.01
   shotLifeTimeout = time.time()
   try: 
      moveKeys = [chr(273), 'w', chr(274), 's',  chr(275), 'd', chr (276), 'a']   
   except Exception as ex:
      moveKeys = ['w','s','d','a']

   joinTimeout = time.time() + 1
   while not quit: 
   
      if joining != 'Tank':
         if time.time() > joinTimeout: 
            joinTimeout = time.time() + 1
            udpBroadcast ( 'exec:games=[\'Tank\']')
       
      (eventType,data,addr) = getKeyOrUdp()
         
      if eventType == pygame.MOUSEMOTION:
         pass # Move turret to follow mouse?
      elif eventType == pygame.MOUSEBUTTONDOWN:
         pass # fire tank on mouse click          
         
      if move != None: #Opponent has moved 
         print ( "Got a move from opponent: " + str(move)) 
         objectType = move[0]
         x = int(move[1])
         y = int(move[2])
            
         pieceIndex = 0
         if objectType == 'shot':
            if enemyShot == None:
               enemyShot = Object()
            enemyShot.x = x
            enemyShot.y = y 
         elif objectType == 'explosion':
            explosion = Object()
            explosion.x = x
            explosion.y = y
            lost = True
         else:
            angle = move[3]
            if objectType == 'black':
               pieceIndex = 1    
                     
            pieces[pieceIndex][2] = (x,y)
            pieces[pieceIndex][3] = angle         
         drawBoard()
         (images,sprites) = showImages (['images/quit.jpg'], [(400,500)] )                                          
         #showStatus ( 'Move piece ' + str(pieceIndex) + ' to [' + \
         #             str(x) + ',' + str(y) + '] angle:' + str(angle) ) 
         move = None      
         
      if (eventType == pygame.KEYUP):
         autoKey = ''
         print ( 'Turning off autoKey' )

      if time.time() > autoTime: 
         if autoKey != '':
            print ( 'Detected autokey: ' + autoKey )
            autoTime = time.time() + moveTimeout
            eventType = 'key'
            data = autoKey
            addr = 'key'

      if shot != None: 
         if time.time() > shotTimeout:          
            shotTimeout = time.time() + 0.01
            (x,y) = angleXY(shot.x, shot.y, 10, shot.angle)
            if wallCollide (x,y): 
               shot = None
            else:
               shot.x = x
               shot.y = y
               if (shot.x >= DISPLAYWIDTH) or (shot.y >= DISPLAYHEIGHT) or (shot.x <= 0) or (shot.y <= 0): 
                  shot.angle = int(shot.angle + 90) % 360
                  
               udpBroadcast ( 'exec:move=(\'shot\',' + str(shot.x) + ',' + str(shot.y) + ')')
               drawBoard()
               (images,sprites) = showImages (['images/quit.jpg'], [(400,500)] )                              

         if time.time() > shotLifeTimeout: 
            shot = None
            drawBoard()
            (images,sprites) = showImages (['images/quit.jpg'], [(400,500)] ) 
            
      if eventType == 'key':
         if joining != 'Tank':
            showStatus ( "Waiting for other player to join" )      
         elif lost: 
            showStatus ( "Disabled (due to loss)" )         
         else:
            pieceIndex = 1
            tankType = 'black'
            if iAmHost:
               pieceIndex = 0
               tankType = 'white'
               
            x     = pieces[pieceIndex][2][0]
            y     = pieces[pieceIndex][2][1]
            angle = pieces[pieceIndex][3]
            if (data == ' '): 
               print ("Fire!" )
               shot = Object()
               shot.x = x
               shot.y = y
               shot.angle = angle
               for i in range(8): 
                   # make sure shot starts outside of the firing tank location
                  (shot.x,shot.y) = angleXY(shot.x, shot.y, 13, shot.angle)            
               shotLifeTimeout = time.time() + 2.0
            
            if data in moveKeys:           
               if data == 'w':
                  autoKey = 'w'
                  autoTime = time.time() + moveTimeout
                  x,y = angleXY(x,y,10,angle)
               elif data == 's':
                  autoKey = 's'
                  autoTime = time.time() + moveTimeout
                  x,y = angleXY(x,y,10,angle+180)   
               elif data == 'd':
                  autoKey = 'd' 
                  autoTime = time.time() + moveTimeout
                  pieces[pieceIndex][3] = int(angle - 10) % 360
               elif data == 'a':
                  autoKey = 'a'
                  autoTime = time.time() + 0.19
                  pieces[pieceIndex][3] = int(angle + 10) % 360
                  print ( 'Go Left' )
               
               if wallCollide (x,y): 
                  showStatus ( "Mind the wall!" )
               else:
                  udpBroadcast ( 'exec:move=(\'' + tankType + '\',' + str(x) + ',' + str(y) + ',' + str(angle) + ')')                
                  pieces[pieceIndex][2]= (x,y)
                  drawBoard()
                  (images,sprites) = showImages (['images/quit.jpg'], [(400,500)] )                              
   
      sprite = getSpriteClick (eventType, data, sprites ) 
      if sprite != -1: # Quit is the only other option           
         print ("Selected command: " + str(sprite))
         mainPage (True)
         quit = True  
         
TANK=inspect.getsource(tankPage)