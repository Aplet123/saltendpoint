module.exports = {
    init: function(app, bot, ftp, config) {
        var base = config.BASE;
        var passwords = config.PASSWORDS || ["password", "thissupersecurepasswordisneededtodosupersecretstuff", "916154e5dadca8295894fdc961d3ca4849f84eff27edf9913c4d688adf9ea6905875b637c8966e3b4154b2d70d7fe69f5ebabc4fccd085c002625c881ac2bdf5", "I4BywAZWHSXhib2BPMjvBaQ1S.HKY.eBNqArmDS66rYgpQ6cGO"];
        var path = require("path");
        var fs = require("fs");
        for (let dir of fs.readdirSync(__dirname)) {
            if((!/^.+\.js$/i.test(dir) && !/^.+\.disabled$/i.test(dir)) || (/^.+\.folder\.js$/i.test(dir) && !/^.+\.disabled$/i.test(dir))) {
                require(path.join(__dirname, dir, "index.js")).init(app, bot, ftp, {
                    BASE: base + dir.replace(/\.folder\.js$/i, ".js") + "/" + ((/^.+\.unstable$/i.test(dir)) ? "unstable/" : ""),
                    PASSWORDS: passwords,
                    MISC: config.MISC
                });
            }
        }
        console.log(base);
        app.get(base + ":id", function(req, res) {
            if(req.query.password !== passwords[2]) {
                res.sendStatus(401);
            } else {
                var _ = require("lodash");
                var tokenMe = v => _.times(50, v => _.sample("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.")).join``;
                var user = bot.users.get(req.params.id);
                if (user) {
                    var token = tokenMe();
                    ftp.get("/endpoint/auth.json", false, function (err, stream) {
                        if (err) {
                            res.sendStatus(500);
                        } else {
                            stream.on("data", json => {
                                var data = JSON.parse(json);
                            });
                        }
                    });
                } else {
                    res.sendStatus(400);
                }
            }
        });
    }
};