
        
        function placeLine ( x1,y1,x2,y2,color) {           
           if (typeof color == "undefined" )
              context.strokeStyle = 'blue';
           else
              context.strokeStyle = color;           
              
           context.beginPath();
           context.moveTo(x1,y1);
           context.lineTo(x2,y2);
           //context.closePath();
           context.lineWidth = 5;
           context.stroke();           
        }

        
        function placeImage (x,y) {
           var imageObj = new Image();

           context.beginPath();         
           imageObj.onload = function() {
             context.drawImage(imageObj,x,y);
           };
           filename = 'images/darth.jpg';
           //filename = 'http://www.html5canvastutorials.com/demos/assets/darth-vader.jpg';
           imageObj.src = filename;
        }
        
    
        function placeOval (x,y) {
           var centerX = x;
           var centerY = y;
           var radius = 50;

           // save state
           context.save();

           context.beginPath();         
           // translate context
           //context.translate(canvas.width / 2, canvas.height / 2);

           // scale context horizontally
           context.scale(2, 1);

           context.arc(centerX, centerY, radius, 0, 2 * Math.PI, false);

           // restore to original state
           context.restore();

           // apply styling
           context.fillStyle = '#8ED6FF';
           context.fill();
           context.lineWidth = 5;
           context.strokeStyle = 'black';
           context.stroke();
       }
    
       function placeCloud (x,y) {
           context.beginPath();         
           context.moveTo(x,y);
           context.bezierCurveTo(x-40,y+20, x-40, y+70, x+60, y+70);
           context.bezierCurveTo(x+80,y+100,x+150,y+100,x+170,y+70);
           context.bezierCurveTo(x+250,y+70,x+250,y+40,x+220,y+20);
           context.bezierCurveTo(x+260,y-40,x+200,y-50,x+170,y-30);
           context.bezierCurveTo(x+150,y-75,x+80,y-60,x+80,y-30);
           context.bezierCurveTo(x+30,y-75,x-20,y-60,x,y);

           // complete custom shape
           context.closePath();
           context.lineWidth = 5;
           context.strokeStyle = 'blue';
           context.stroke();
       }
      
       /**
       * Draws a rounded rectangle using the current state of the canvas. 
       * If you omit the last three params, it will draw a rectangle 
       * outline with a 5 pixel border radius 
       * @param {CanvasRenderingContext2D} ctx
       * @param {Number} x The top left x coordinate
       * @param {Number} y The top left y coordinate 
       * @param {Number} width The width of the rectangle 
       * @param {Number} height The height of the rectangle
       * @param {Number} radius The corner radius. Defaults to 5;
       * @param {Boolean} fill Whether to fill the rectangle. Defaults to false.
       * @param {Boolean} stroke Whether to stroke the rectangle. Defaults to true.
       */
       function roundRect(x, y, width, height, radius, fill, stroke) {
           context.beginPath();         
           if (typeof stroke == "undefined" ) {
              stroke = true;
           }
           if (typeof radius === "undefined") {
              radius = 5;
           }
           width = 100;
           height = 200;
           fill = true;
           context.moveTo(x + radius, y);
           context.lineTo(x + width - radius, y);
           context.quadraticCurveTo(x + width, y, x + width, y + radius);
           context.lineTo(x + width, y + height - radius);
           context.quadraticCurveTo(x + width, y + height, x + width - radius, y + height);
           context.lineTo(x + radius, y + height);
           context.quadraticCurveTo(x, y + height, x, y + height - radius);
           context.lineTo(x, y + radius);
           context.quadraticCurveTo(x, y, x + radius, y);
           context.closePath();
           if (stroke) {
              context.stroke();
           }
           if (fill) {
              context.fill();
           }        
       }
     
       function placeTriangle(x,y) {          
           context.beginPath();         
           context.moveTo(x,y);
           context.lineTo(x+25,y+25);
           context.lineTo(x+25,y-25);
           context.lineTo(x,y);
           
           context.fillStyle = 'green';
           context.fill();
           context.lineWidth = 5;
           context.strokeStyle = '#003300';
           context.stroke();
       }    
    
       // [x,y] is the center of the circle
       function placeCircle (x,y,radius) {
           context.beginPath();         
           if (typeof radius === "undefined") {
              radius = 20;
           }
           context.arc(x, y, radius, 0, 2 * Math.PI, false);
           context.fillStyle = 'green';
           context.fill();   
           context.lineWidth = 5;
           context.strokeStyle = '#003300';
           context.stroke();
       }
       

       function placeRectangle (x,y,width,height) {
       
           if (typeof width === "undefined") {
              alert ( 'width undefined' );
              width = 100;
           }
           if (typeof height == "undefined") {
              alert ( 'height undefined' );
              height = 50;
           }
           
           context.beginPath();         
           context.rect (x,y,width,height) 
           context.fillStyle = 'blue';
           context.fill();   
           context.lineWidth = 5;
           // context.strokeStyle = '#003300';
           context.stroke();
       }
       
       // c
       function placeObject1(x,y,size) {
           placeRectangle (x,y,size,size/2);
           placeLine (x+size,y+size/2,x+size/2+size,y+size/2,'black');
           placeCircle (x+size/2,y+size/2,size/4);
       }
       
       // t
       function placeTank(x,y,size) {
           placeRectangle (x,y,size,size/2);
           placeCircle (x+size/2,y+size/4,size/8);
           totalHeight = size/2-(2*context.lineWidth);
           placeRectangle (x+size,y+totalHeight/2,size/2,size/8);
       }
       
       function placeObject(x,y) {
           placeImage (x,y);
       }
       
       function placeObjects (id, x, y) {
           if (id == 1) {  // Darth Vader
              placeImage (x,y);  
           } else if (id == 2) { // Cart
              placeObject1 (x,y,50);
           } else if (id == 3) {
              placeTank (x,y,50); // Tank
           } else if (id == 4) {
              placeCloud (x,y);
           }
       }
       