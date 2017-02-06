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

if(!process.env.DEPLOYED) {
    require("dotenv").config();
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
            BASE: process.env[dir.toUpperCase() + "BASE"] || "/api/" + dir.replace(/\.folder\.js$/i, ".js") + "/" + ((/^.+\.unstable$/i.test(dir)) ? "unstable/" : ""),
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
            BASE: process.env["PAGES" + dir.toUpperCase() + "BASE"] || ( "/pages/" + dir.replace(/\.folder\.js$/i, ".js") + "/" + ((/^.+\.unstable$/i.test(dir)) ? "unstable/" : "")),
            PASSWORDS: process.env["PAGES" + dir.toUpperCase() + "PASSWORDS"],
            MISC: {
                AUTH: auth
            }
        });
    }
}

app.listen(app.get('port'), function() {
  console.log('Node app is running on port', app.get('port'));
});