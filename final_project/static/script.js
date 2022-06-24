var refreshIntervalId;

function sendDevice(led, open){
  const xhttp = new XMLHttpRequest();
  xhttp.onload = function() {}
  xhttp.open("GET", "drive?" + "led=" + led +"&open=" + open, true);
  xhttp.send();
}

function openLamp(){
  if(document.getElementById("a").checked){
    sendDevice("LED1", "on");
  }else{
    sendDevice("LED1", "off");
  }  
}

function openAir(){
  if(document.getElementById("c").checked){
    sendDevice("LED2", "on");
  }else{
    sendDevice("LED2", "off");
  }  
}

function openFridge(){
  if(document.getElementById("d").checked){
    sendDevice("LED3", "on");
  }else{
    sendDevice("LED3", "off");
  }  
}

function checkDetect(){
  const xhttp = new XMLHttpRequest();
  xhttp.onload = function() {}
  var text = document.getElementById("p2");

  if(document.getElementById("detect").checked){
    text.style.display = "inline-block";
    xhttp.open("GET", "mode?detect=yes", true);
    xhttp.send();
    refreshIntervalId = setInterval(setDetectValue, 1000);
    
  }else{
    clearInterval(refreshIntervalId);   
    text.style.display = "none";
    xhttp.open("GET", "mode?detect=no", true);
    xhttp.send(); 
  }
}

function setDetectValue() {
  $.ajax({
    type:"get",
    url:"/catchValue",
    success:function (result) {				
    console.log(result);
       $("#p2").text(`ADC_VALUE = :${result}`);
    },
  error: function() {			
    console.log("error");
  }
})    
}