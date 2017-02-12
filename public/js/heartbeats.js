var heartbeats = document.getElementById("heartbeats");
var socket = io("http://localhost/pages/heartbeat/");
function write(text) {
    var p = document.createElement("p");
    p.setAttribute("class", "code");
    p.innerText = text;
    return heartbeats.appendChild(p);
}
scopa: {
    let meta;
    socket.on("connected", function(message) {
        write("Connected");
        meta = message.meta;
        setInterval(function () {
            socket.emit("heartbeat", {
                meta: meta
            });
            write("Heartbeat sent");
        }, 10000);
    });
    socket.on("acknowledged", function(message) {
        if (message.meta === meta) {
            write("Heartbeat acknowledged");
        }
    });
}