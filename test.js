app.get("/photSen",(req,res)=>{
    let child_process = require("child_process");

    let process = child_process.spawn('python', [
            "./lab5.py"
    ]);

	process.stdout.on('data', (data) => {
            console.log(`stdout : ${data}`);
			return data;
        });

    process.stderr.on('data', (data) => {
            console.log(`stderr: ${data}`);
			return data;
        });  
})

function photSen(){
   
}

app.get("/submit",(req,res)=>{
    let response = {
        "led1": req.query.LED1,
        "led2": req.query.LED2,
        "Switch": req.query.switch,
    }
    for(var index = 1; index < 3; index++){
        if(response[`led${index}`] == "choose"){
            ledSubmit(`LED${index}`, req.query.switch);
        } 
    }
    res.send(JSON.stringify(response));
})
function ledSubmit(LED, POWER){
    console.log(LED); // test
    console.log(POWER);

     let child_pocess = require("child_process");

     let process = child_pocess.execFile('sudo',[
         "./c++/L2Program", LED ,POWER
     ]);

     process.stdout.on('data',(data) => {
         console.log(`stdout: ${data}`);
     })

     process.stdout.on('data',(data) => {
         console.error(`stdout: ${data}`);
     })
}
app.get("/shine",(req,res)=>{
    ledShine(req.query.times);
    res.send(req.query.times);
})

function ledShine(times){
    console.log(times);

     let child_pocess = require("child_process");

     let process = child_pocess.execFile('sudo',[
         "./c++/L2Program", "Mode_Shine" ,times
     ]);

     process.stdout.on('data',(data) => {
         console.log(`stdout: ${data}`);
     })
     process.stdout.on('data',(data) => {
         console.error(`stdout: ${data}`);
     })
}

