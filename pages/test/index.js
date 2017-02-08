module.exports = {
    init: function(app, bot, ftp, config) {
        var base = config.BASE;
        var passwords = config.PASSWORDS || ["password", "thissupersecurepasswordisneededtodosupersecretstuff", "916154e5dadca8295894fdc961d3ca4849f84eff27edf9913c4d688adf9ea6905875b637c8966e3b4154b2d70d7fe69f5ebabc4fccd085c002625c881ac2bdf5", "I4BywAZWHSXhib2BPMjvBaQ1S.HKY.eBNqArmDS66rYgpQ6cGO"];
        var path = require("path");
        var fs = require("fs");
        var _ = require("lodash");
        for (let dir of fs.readdirSync(__dirname)) {
            if((!/^.+\.js$/i.test(dir) && !/^.+\.disabled$/i.test(dir)) || (/^.+\.folder\.js$/i.test(dir) && !/^.+\.disabled$/i.test(dir))) {
                require(path.join(__dirname, dir, "index.js")).init(app, bot, ftp, {
                    BASE: base + ((/^.+\.unstable$/i.test(dir)) ? "unstable/" : "") + dir.replace(/\.folder\.js$/i, ".js").replace(/\.unstable$/i, "") + "/",
                    PASSWORDS: passwords,
                    MISC: config.MISC
                });
            }
        }
        app.get(new RegExp("^" + _.escapeRegExp(base) + "{0}\\.?(?:(?:html?)|(?:pug)|(?:jade)|(?:txt))?$"), function(req, res) {
            res.render("pages/index", {
                title: "Hello",
                message: "My name's Bob",
                favicon: "https://www.google.com/images/branding/googlelogo/1x/googlelogo_color_272x92dp.png"
            });
        });
    }
};