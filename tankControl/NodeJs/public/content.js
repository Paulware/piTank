        var canvas;
        var context;

        canvas = document.getElementById('myCanvas');
        context = canvas.getContext('2d');  

        function placeImage (filename, x,y) {
           var imageObj = new Image();

           context.beginPath();         
           imageObj.onload = function() {
             context.drawImage(imageObj,x,y);
           };
           imageObj.src = filename;
        }
