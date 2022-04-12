const express = require("express");
const app = express();

app.use(express.static('./public'));

app.get("/submit",(req,res)=>{
    let response = {
        "led1": req.query.LED1,
        "led2": req.query.LED2,
        "led3": req.query.LED3,
        "led4": req.query.LED4,
        "Switch": req.query.switch,
    }
    for(var index = 1; index < 5; index++){
        if(response[`led${index}`] == "choose"){
            ledSubmit(`LED${index}`, req.query.switch);
        } 
    }
    res.send(JSON.stringify(response));
})
function ledSubmit(LED, POWER){
    console.log(LED); // test
    console.log(POWER);

    // let child_pocess = require("child_process");

    // let process = child_pocess.execFile('sudo',[
    //     "./c++/lab2", LED ,POWER
    // ]);

    // process.stdout.on('data',(data) => {
    //     console.log(`stdout: ${data}`);
    // })

    // process.stdout.on('data',(data) => {
    //     console.error(`stdout: ${data}`);
    // })
}
app.get("/shine",(req,res)=>{
    ledShine(req.query.times);
    res.send(req.query.times);
})

function ledShine(times){
    console.log(times);

    // let child_pocess = require("child_process");

    // let process = child_pocess.execFile('sudo',[
    //     "./c++/lab2", "Mode_Shine" ,times
    // ]);

    // process.stdout.on('data',(data) => {
    //     console.log(`stdout: ${data}`);
    // })

    // process.stdout.on('data',(data) => {
    //     console.error(`stdout: ${data}`);
    // })
}

const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
    console.log(`Server is running on port${PORT}`);
});

