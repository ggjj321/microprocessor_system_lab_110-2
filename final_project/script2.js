ledStat = ["off", "off", "off", "off"];

function submitGet() {

    showText();

    const xhttp = new XMLHttpRequest();
    xhttp.onload = function() {
        innerText = "";
        for(var i = 0; i < 4; i++){
            innerText += "LED" + (i+1) + " " + ledStat[i] + "<br>";
        }
        document.getElementById("submitText").innerHTML =innerText;
    }

    params = "";

    if(document.getElementById("on").checked){
        params += "switch=on";
        stat = "on";
    }else{
        params += "switch=off";
        stat = "off";
    }

    for(var index = 1; index < 5; index++){
        if(document.getElementById(`LED${index}`).checked){
            params += `&LED${index}=choose`;
            ledStat[index - 1] = stat;
        }
    }

    url = "submit";

    xhttp.open("GET", url+"?"+params, true);
    xhttp.send();
}

function modeShineGet(){
    const xhttp = new XMLHttpRequest();
    times = document.getElementById("times").value;
    xhttp.onload = function() {
        document.getElementById("shineText").innerHTML = "Mode_Shine_Times:" + times;
    }
    params = "times=" + times;
    xhttp.open("GET", "shine"+"?"+params, true);
    xhttp.send();
}

function rangeBar(){
    let rangeInput = document.querySelector(".range-input input");
    let rangeValue = document.querySelector(".range-input .value div");

    let  start = parseFloat(rangeInput.min);
    let end = parseFloat(rangeInput.max);
    let step = parseFloat(rangeInput.step);

    for(let i=start;i<=end;i+=step){
    rangeValue.innerHTML += '<div>'+i+'</div>';
    }

    rangeInput.addEventListener("input",function(){
    let top = parseFloat(rangeInput.value)/step * -40;
    rangeValue.style.marginTop = top+"px";
    });
}

function showText() {
    var text = document.getElementById("p2");
    var checkBox1 = document.getElementById("LED1");
    var checkBox2 = document.getElementById("LED2");
    if (checkBox1.checked == true && checkBox2.checked == true){
        document.getElementById('p2').innerText = "LED1 = ON , LED2 = ON"
    } 
    else if (checkBox1.checked == true && checkBox2.checked == false){
        document.getElementById('p2').innerText = "LED1 = ON , LED2 = OFF"
    }
    else if (checkBox1.checked == false && checkBox2.checked == false){
        document.getElementById('p2').innerText = "LED1 = OFF , LED2 = OFF"
    }
    else if (checkBox1.checked == false && checkBox2.checked == true){
        document.getElementById('p2').innerText = "LED1 = OFF , LED2 = ON"
    }
    
  }

