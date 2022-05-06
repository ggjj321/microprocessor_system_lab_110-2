function test() {
    return new Promise(function(resolve, reject) {

        let child_process = require("child_process");

        let process = child_process.spawn('python', [
            "./python/test.py"
        ]);
        
        process.stdout.on('data', (data) => {
            console.log('stdout : ${data}');
            resolve(data)
        });

        process.stderr.on('data', (data) => {
            console.assert.error('stderr: ${data}');
            reject(data)
        });
    })
}