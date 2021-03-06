'use strict';
var express = require('express');
var http = require("http");
var app = express();
var server = http.createServer(app);
var io = require("socket.io")(server);
var fs = require("fs");
var path = require("path");
var Discord = require("discord.js");
var ftp = require("ftp");
var _ = require("lodash");
var request = require("request");
const Storage = require("saltjs").Storage;
const { random } = require("./nativeBundle.js");
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
    require("./message.js").init(bot);
    let requestURL;
    setInterval(function() {
        switch (process.env.ENGINE) {
            case "Heroku":
                requestURL = `https://${process.env.DEPLOY_NAME}.herokuapp.com`;
                break;
            case "Cloud9":
                requestURL = `https://${process.env.DEPLOY_NAME}.c9users.io`;
                break;
            default:
                requestURL = `https://www.google.com`;
        }
        request(requestURL, _.noop);
    }, 1200000);
}

var AWS = require("aws-sdk");
var s3 = new AWS.S3();

s3.getObject({
    Bucket: "tranquilitytestbucket",
    Key: "saltendpoint/auth.json"
}, function(err, data) {
    if (err) {
        throw err;
    } else {
        auth = JSON.parse(data.Body.toString("utf8"));
    }
});

bot.login(process.env.TOKEN);

app.set('port', (process.env.PORT || 5000));

app.use(function(req, res, next) {
    if (!/^[-a-zA-Z0-9_.]+(?::\d+)?$/i.test((req.get("Host") || ""))) {
        res.status(400);
        if (req.accepts("text/html")) {
            res.set({
                "Accept": "text/html",
                "Content-Type": "text/html"
            });
            res.render("pages/error", {
                error: "Invalid Host Header",
                status: 400,
                url: _.escape(( req.get("X-Forwarded-Proto") || "http") + "://" + req.get("host") + req.originalUrl),
                method: _.escape(req.method)
            });
        } else if (req.accepts("application/json")) {
            res.set({
                "Accept": "application/json",
                "Content-Type": "application/json"
            });
            res.end(JSON.stringify({
                error: "Invalid Host Header",
                status: 400,
                url: ( req.get("X-Forwarded-Proto") || "http") + "://" + req.get("host") + req.originalUrl,
                method: req.method
            }));
        } else {
            res.set({
                "Accept": "text/plain",
                "Content-Type": "text/plain"
            });
            res.end(`400 on HTTP ${req.method} request: Invalid Host Header | ${( req.get("X-Forwarded-Proto") || "http") + "://" + req.get("host") + req.originalUrl}`);
        }
    } else {
        res.set({
            "X-Powered-By": "Express, Node.js, EJS, GitHub, and " + process.env.ENGINE || "Some Random Computer",
            "X-Nonce": _.times(10, v => String(Math.random() * 10).replace(/\./, "")).join``,
            "X-Salt-Endpoint": process.env.ENGINE || "Some Random Computer",
            "X-State": req.get("X-State") || "Unset",
            "X-Request-Uri": ( req.get("X-Forwarded-Proto") || "http") + "://" + req.get("host") + req.originalUrl,
            "Access-Control-Allow-Origin": "*",
            "Access-Control-Expose-Headers": "Content-Length, X-Powered-By, X-Nonce, X-Salt-Endpoint, X-State, X-Request-Uri",
            "Access-Control-Request-Headers": "Content-Type, Accept, X-Authentication, X-Misc, X-Nonce, X-Seed, X-State"
        });
        next();
    }
});

app.use(function(req, res, next) {
    if (/^\/download\/.+$/.test(req.path)) {
        var downloadPath = req.path.replace(/^\//, "");
        if (/\.\./.test(downloadPath)) {
            res.sendStatus(400);
        } else {
            res.set({
                "Accept": "application/octet-stream",
                "Content-Type": "application/octet-stream"
            });
            var fileExists = true;
            try {
                fs.readFileSync(downloadPath);
            } catch (err) {
                fileExists = false;
                res.sendStatus(403);
            }
            if (fileExists) {
                res.end(fs.readFileSync(downloadPath));
            }
        }
    } else {
        next();
    }
});

app.use(function(req, res, next) {
    if (/^\/download\/.+$/.test(req.path)) {
        var downloadPath = req.path.replace(/^\//, "");
        if (/\.\./.test(downloadPath)) {
            res.sendStatus(400);
        } else {
            res.set({
                "Accept": "application/octet-stream",
                "Content-Type": "application/octet-stream"
            });
            var fileExists = true;
            try {
                fs.readFileSync(downloadPath);
            } catch (err) {
                fileExists = false;
                res.sendStatus(403);
            }
            if (fileExists) {
                res.end(fs.readFileSync(downloadPath));
            }
        }
    } else {
        next();
    }
});

app.use(express.static(__dirname + '/public'));

app.set('views', __dirname + '/views');
app.engine("html", require("express-ejs-extend"));
app.set('view engine', 'html');
app.disable("x-powered-by");

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
            PASSWORDS: (process.env[dir.toUpperCase() + "PASSWORDS"] || "").split`,`.length ? (process.env[dir.toUpperCase() + "PASSWORDS"] || "").split`,` : undefined,
            MISC: {
                AUTH: auth,
                IO: io
            }
        });
    }
}

for (let dir of fs.readdirSync(path.join(__dirname, "pages"))) {
    if((!/^.+\.js$/i.test(dir) && !/^.+\.disabled$/i.test(dir)) || (/^.+\.folder\.js$/i.test(dir) && !/^.+\.disabled$/i.test(dir))) {
        require(path.join(__dirname, "pages", dir, "index.js")).init(app, bot, ftpClient, {
            BASE: process.env["PAGES" + dir.toUpperCase() + "BASE"] || ( "/pages/" + ((/^.+\.unstable$/i.test(dir)) ? "unstable/" : "") + dir.replace(/\.folder\.js$/i, ".js").replace(/\.unstable$/i, "") + "/" ),
            PASSWORDS: (process.env[dir.toUpperCase() + "PASSWORDS"] || "").split`,`.length ? (process.env[dir.toUpperCase() + "PASSWORDS"] || "").split`,` : undefined,
            MISC: {
                AUTH: auth,
                IO: io
            }
        });
    }
}

app.use(function(req, res) {
    res.status(404);
    if (req.accepts("text/html")) {
        res.render("pages/error", {
            error: "Not Found",
            status: 404,
            url: _.escape(( req.get("X-Forwarded-Proto") || "http") + "://" + req.get("host") + req.originalUrl),
            method: _.escape(req.method)
        });
    } else if (req.accepts("application/json")) {
        res.set({
            "Accept": "application/json",
            "Content-Type": "application/json"
        });
        res.end(JSON.stringify({
            error: "Not Found",
            status: 404,
            url: ( req.get("X-Forwarded-Proto") || "http") + "://" + req.get("host") + req.originalUrl,
            method: req.method
        }));
    } else {
        res.set({
            "Accept": "text/plain",
            "Content-Type": "text/plain"
        });
        res.end(`404 on HTTP ${req.method} request: Not Found | ${( req.get("X-Forwarded-Proto") || "http") + "://" + req.get("host") + req.originalUrl}`);
    }
});

app.listen(app.get('port'), function() {
  console.log(`Yo yo yo wazzup iz ya boi ${app.get("port")} which is pretty dank!`);
});