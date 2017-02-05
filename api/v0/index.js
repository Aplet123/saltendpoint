module.exports = {
    init: function(app, bot, config) {
        var base = config.BASE || "/api/v0/";
        var passwords = config.PASSWORDS || ["password", "thissupersecurepasswordisneededtodosupersecretstuff", "916154e5dadca8295894fdc961d3ca4849f84eff27edf9913c4d688adf9ea6905875b637c8966e3b4154b2d70d7fe69f5ebabc4fccd085c002625c881ac2bdf5"];
        app.get(base + "identity/:value", function(req, res) {
            res.end(req.params.value);
        });
        app.get(base + "users/:id", function(req, res) {
            if (req.query.password !== passwords[2]) {
                res.status(401).end(new Error("Incorrect password").stack);
            } else {
                var user = bot.users.get(req.params.id);
                if (user) {
                    res.end(JSON.stringify({
                        username: user.username
                    }));
                } else {
                    res.status(403).end(new Error("User not found").stack);
                }
            }
        });
    }
};