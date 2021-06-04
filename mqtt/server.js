var express = require('express'),
    app = express(),
    server = require('http').Server(app),
    io = require('socket.io')(server),
    port = 8888;
var mqtt = require('mqtt')
var client = mqtt.connect('mqtt://192.227.88.110',{clientId:"sub_to_db",username:"kelompok5",password:"kelompok5"})
var mysql = require('mysql');
var connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '',
    database: 'kuliah_iot'
});
connection.connect();
//Server start
server.listen(port, () => console.log('on port' + port))
//user server
app.use(express.static(__dirname + '/public'));
io.on('connection', onConnection);
var connectedSocket = null;
function onConnection(socket) {
    connectedSocket = socket;
}
client.on('connect', function () {
    client.subscribe('presencex', function (err) {
    })
})
client.on('message', function (topic, message) {
    // message is Buffer
    console.log(message.toString())
    connection.query('INSERT INTO vokasipedia VALUES (NULL, "'+message.toString()+'", "40", "ko.jpg")', function (error, results, fields) {
        if (error) throw error;
        console.log('ok');
        io.emit('data', { data: message.toString() }); // bagian untuk meneruskan data ke frontend pakai socket.io
    });
})
