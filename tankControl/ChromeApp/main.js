chrome.app.runtime.onLaunched.addListener(function() {
  console.log ( 'Launched, run index.html' );
  chrome.app.window.create('index.html', {
  	id: "mainwin",
    innerBounds: {
      width: 680,
      height: 480
    }
  });
  console.log ( 'Index running yo' );
});
