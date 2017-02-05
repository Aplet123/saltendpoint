var express = require('express');
var app = express();
var fs = require("fs");
var path = require("path");
var Discord = require("discord.js");
var bot = new Discord.Client({
    fetchAllMembers: true
});

if(process.env.DEPLOYED === undefined) {
    require("dotenv").config();
}

bot.login(process.env.TOKEN);

app.set('port', (process.env.PORT || 5000));

app.use(express.static(__dirname + '/public'));

app.set('views', __dirname + '/views');
app.set('view engine', 'pug');

app.get('/', function(request, response) {
  response.render('pages/index', {
      title: process.env.TITLE || "Hello",
      message: process.env.MESSAGE || "Hello",
      favicon: process.env.FAVICON || "https://upload.wikimedia.org/wikipedia/commons/thumb/7/78/Salt_shaker_on_white_background.jpg/220px-Salt_shaker_on_white_background.jpg"
  });
});

for (let dir of fs.readdirSync("api")) {
    require("./" + path.join("api", dir, "index.js")).init(app, bot, {
        BASE: process.env[dir.toUpperCase() + "BASE"],
        PASSWORDS: process.env[dir.toUpperCase() + "PASSWORDS"] ? process.env[dir.toUpperCase() + "PASSWORDS"].split`,` : undefined
    });
}

app.listen(app.get('port'), function() {
  console.log('Node app is running on port', app.get('port'));
});