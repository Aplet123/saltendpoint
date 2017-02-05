module.exports = {
    init: function(app, config) {
        var base = config.BASE || "/api/v0/";
        app.get(base + "identity/:value", function(req, res) {
            res.end(req.params.value);
        });
    }
};