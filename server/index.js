const websocket = require('ws');

const wss = new websocket.WebSocketServer({ port: 8080 });

wss.on('connection', function connection(ws) {
    console.log("connection");

    ws.on('message', function message(data) {
        console.log('received: %s', data);
    });

    ws.send('something');
});

console.log("End of file");

