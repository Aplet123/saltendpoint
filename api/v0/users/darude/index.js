module.exports = {
    init: function(app, bot, ftp, config) {
        var base = config.BASE;
        var passwords = config.PASSWORDS || ["password", "thissupersecurepasswordisneededtodosupersecretstuff", "916154e5dadca8295894fdc961d3ca4849f84eff27edf9913c4d688adf9ea6905875b637c8966e3b4154b2d70d7fe69f5ebabc4fccd085c002625c881ac2bdf5", "I4BywAZWHSXhib2BPMjvBaQ1S.HKY.eBNqArmDS66rYgpQ6cGO"];
        var path = require("path");
        var fs = require("fs");
        for (let dir of fs.readdirSync(__dirname)) {
            if(!/^.+\.js$/i.test(dir)) {
                require(path.join(__dirname, dir, "index.js")).init(app, bot, ftp, {
                    BASE: base + dir + "/",
                    PASSWORDS: passwords
                });
            }
        }
        app.get(base + ":id", function(req, res) {
            if(req.query.password !== passwords[2]) {
                res.status(403).end(new Error("Incorrect password").stack);
            } else {
                var user = bot.users.get(req.params.id);
                if (user) {
                    user.sendMessage("DARUDE SANDSTROM").then(v => {
                        res.end("Sent");
                    }).catch(err => {
                        console.error(err.message);
                        res.status(403).end(new Error("Message cannot be sent").stack);
                    });
                } else {
                    res.status(403).end(new Error("User not found").stack);
                }
            }
        });
    }
};