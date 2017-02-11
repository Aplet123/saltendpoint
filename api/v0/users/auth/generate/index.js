module.exports = {
    init: function(app, bot, ftp, config) {
        var base = config.BASE;
        var passwords = config.PASSWORDS || ["password", "thissupersecurepasswordisneededtodosupersecretstuff", "916154e5dadca8295894fdc961d3ca4849f84eff27edf9913c4d688adf9ea6905875b637c8966e3b4154b2d70d7fe69f5ebabc4fccd085c002625c881ac2bdf5", "I4BywAZWHSXhib2BPMjvBaQ1S.HKY.eBNqArmDS66rYgpQ6cGO"];
        var path = require("path");
        var fs = require("fs");
        for (let dir of fs.readdirSync(__dirname)) {
            if((!/^.+\.js$/i.test(dir) && !/^.+\.disabled$/i.test(dir)) || (/^.+\.folder\.js$/i.test(dir) && !/^.+\.disabled$/i.test(dir))) {
                require(path.join(__dirname, dir, "index.js")).init(app, bot, ftp, {
                    BASE: base + ((/^.+\.unstable$/i.test(dir)) ? "unstable/" : "") + dir.replace(/\.folder\.js$/i, ".js").replace(/\.unstable$/i, "") + "/",
                    PASSWORDS: passwords,
                    MISC: config.MISC
                });
            }
        }
        var rate = Date.now();
        app.get(base + ":id", function(req, res) {
            if(req.query.password !== passwords[2] && req.query.password !== passwords[3]) {
                res.sendStatus(401);
            } else if (req.query.password === passwords[2] && rate >= Date.now()) {
                res.set({
                    "X-Try-Again": String(rate - Date.now())
                });
                res.sendStatus(429);
            } else {
                if (req.query.password === passwords[2]) {
                    rate = Date.now() + 5000;
                }
                var _ = require("lodash");
                var tokenMe = v => _.times(50, v => _.sample("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.")).join``;
                var user = bot.users.get(req.params.id);
                if (user) {
                    var token = tokenMe();
                    config.MISC.AUTH[req.params.id] = token;
                    var AWS = require("aws-sdk");
                    var s3 = new AWS.S3();
                    s3.upload({
                        Bucket: "tranquilitytestbucket",
                        Key: "saltendpoint/auth.json",
                        Body: new Buffer(JSON.stringify(config.MISC.AUTH))
                    }, function (err, data) {
                        if (err) {
                            res.sendStatus(500);
                        } else {
                            res.end(token);
                        }
                    });
                } else {
                    res.sendStatus(403);
                }
            }
        });
    }
};