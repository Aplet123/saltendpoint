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
        const { Storage } = require("saltjs");
        var JIMP = require("jimp");
        var _ = require("lodash");
        app.get(base + ":red-:green-:blue-:opacity-:width-:height", function(req, res) {
            if (Storage.fromObject(req.params).every(v => ! isNaN(Number(v)))) {
                try {
                    var values = ["red", "green", "blue", "opacity"].map(v => Number(req.params[v]));
                    if(values.some(v => v > 255 || v < 0) || Number(req.params.width) < 0 || Number(req.params.height) < 0) {
                        res.sendStatus(400);
                    } else {
                        var color;
                        values = values.map(v => v.toString(16));
                        color = values.map(v => _.padStart(v, 2, "0")).join``;
                        var img = new JIMP(Number(req.params.width), Number(req.params.height), parseInt(color, 16), function(error, canvas) {
                            if (error) {
                                res.sendStatus(500);
                            } else {
                                canvas.getBuffer("image/png", function(error, buffer) {
                                    if (error) {
                                        res.sendStatus(500);
                                    } else {
                                        res.set({
                                            "Content-Type": "image/png",
                                            "Accept": "image/png"
                                        });
                                        res.end(buffer);
                                    }
                                });
                            }
                        });
                    }
                } catch (err) {
                    res.sendStatus(403);
                }
            } else {
                res.sendStatus(400);
            }
        });
        app.get(base + ":hex-:width-:height", function(req, res) {
            if (["hex", "width", "height"].map(v => req.params[v]).every((v, i) => i ? !isNaN(Number(v)) : !isNaN(parseInt(v, 16)))) {
                try {
                    if(!/^[0-9a-fA-F]{1,8}$/.test(req.params.hex) || Number(req.params.width) < 0 || Number(req.params.height) < 0) {
                        res.sendStatus(400);
                    }
                    var img = new JIMP(Number(req.params.width), Number(req.params.height), parseInt(req.params.hex, 16), function(error, canvas) {
                        if (error) {
                            res.sendStatus(500);
                        } else {
                            canvas.getBuffer("image/png", function(error, buffer) {
                                if (error) {
                                    res.sendStatus(500);
                                } else {
                                    res.set({
                                        "Content-Type": "image/png",
                                        "Accept": "image/png"
                                    });
                                    res.end(buffer);
                                }
                            });
                        }
                    });
                } catch (err) {
                    res.sendStatus(403);
                }
            } else {
                res.sendStatus(400);
            }
        });
    }
};