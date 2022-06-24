ledStat = ["off", "off", "off", "off"];

function submitGet() {
    const xhttp = new XMLHttpRequest();
    xhttp.onload = function() {}

    params = "";

    if(document.getElementById("on").checked){
        params += "switch=on";
        stat = "on";
    }else{
        params += "switch=off";
        stat = "off";
    }

    for(var index = 1; index < 3; index++){
        if(document.getElementById(`LED${index}`).checked){
            params += `&LED${index}=choose`;
            ledStat[index - 1] = stat;
        }
    }

    url = "submit";

    xhttp.open("GET", url+"?"+params, true);
    xhttp.send();

    document.getElementById('p2').innerText = `LED1 = ${ledStat[0]} , LED2 = ${ledStat[1]}`;
}

function submitMutex(){
    const xhttp = new XMLHttpRequest();
    times = document.getElementById("times").value;
    frequent = document.getElementById("frequent").value
    xhttp.open("GET", "mutex?times=" + times + "&frequent=" + frequent, true);
    xhttp.send();
}

function submitSemphore(){
    const xhttp = new XMLHttpRequest();
    times = document.getElementById("times").value;
    frequent = document.getElementById("frequent").value
    xhttp.open("GET", "semphore?times=" + times + "&frequent=" + frequent, true);
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

function modeDetect() {
    const xhttp = new XMLHttpRequest();
    xhttp.onload = function() {}

    if(document.getElementById("detect").checked){
        xhttp.open("GET", "mode?detect=yes", true);
        xhttp.send();  
    }else if (document.getElementById("no_detect").checked){
        xhttp.open("GET", "mode?detect=no", true);
        xhttp.send(); 
    }
}


