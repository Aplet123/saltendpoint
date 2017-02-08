var express = require('express');
var app = express();
var fs = require("fs");
var path = require("path");
var Discord = require("discord.js");
var ftp = require("ftp");
var ftpClient = new ftp();
var auth = {};
var bot = new Discord.Client({
    fetchAllMembers: true
});

bot.on("ready", function() {
    console.log(`Woot signed in as ${bot.user.username}#${bot.user.discriminator} (ID: ${bot.user.id})!`);
});

if(! process.env.DEPLOYED) {
    require("dotenv").config();
} else {
    bot.on("message", function(message) {
        if (/^<=>HALP$/.test(message.content)) {
            message.author.sendMessage("no");
        }
    });
}

ftpClient.connect({
    host: process.env.FTPHOSTNAME,
    port: + process.env.FTPPORT,
    user: process.env.FTPUSERNAME,
    password: process.env.FTPPASSWORD
});

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

for (let dir of fs.readdirSync(path.join(__dirname, "api"))) {
    if((!/^.+\.js$/i.test(dir) && !/^.+\.disabled$/i.test(dir)) || (/^.+\.folder\.js$/i.test(dir) && !/^.+\.disabled$/i.test(dir))) {
        require(path.join(__dirname, "api", dir, "index.js")).init(app, bot, ftpClient, {
            BASE: process.env[dir.toUpperCase() + "BASE"] || ( "/api/" + ((/^.+\.unstable$/i.test(dir)) ? "unstable/" : "") + dir.replace(/\.folder\.js$/i, ".js").replace(/\.unstable$/i, "") + "/" ),
            PASSWORDS: process.env[dir.toUpperCase() + "PASSWORDS"],
            MISC: {
                AUTH: auth
            }
        });
    }
}

for (let dir of fs.readdirSync(path.join(__dirname, "pages"))) {
    if((!/^.+\.js$/i.test(dir) && !/^.+\.disabled$/i.test(dir)) || (/^.+\.folder\.js$/i.test(dir) && !/^.+\.disabled$/i.test(dir))) {
        require(path.join(__dirname, "pages", dir, "index.js")).init(app, bot, ftpClient, {
            BASE: process.env["PAGES" + dir.toUpperCase() + "BASE"] || ( "/pages/" + ((/^.+\.unstable$/i.test(dir)) ? "unstable/" : "") + dir.replace(/\.folder\.js$/i, ".js").replace(/\.unstable$/i, "") + "/" ),
            PASSWORDS: process.env["PAGES" + dir.toUpperCase() + "PASSWORDS"],
            MISC: {
                AUTH: auth
            }
        });
    }
}

app.listen(app.get('port'), function() {
  console.log(`Yo yo yo wazzup iz ya boi ${app.get("port")} which is pretty dank!`);
});