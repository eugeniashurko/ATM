/**
 * Bank subsystem
 * Author: Bogdan Kulynych
 *
 * Main communication router
 */


var fs      = require('fs'),
    https   = require('https'),
    express = require('express'),

    ssl     = require('./config/ssl.json');
    utils   = require('./utils.js');


// CONFIGURATION


var options = {};

// Port
options.port = process.argv[2] || 4443;

// SSL Keys and Certificates
['key', 'cert', 'ca'].map(function(name) {
    if (name in ssl) {
        ssl[name] = fs.readFileSync(ssl[name]);
    }
});


// API SERVER


var api = module.exports = express();

api.use(express.json());
api.disable('x-powered-by');

// Index
api.get('/api', function(req, res) {
    res.send(200);
});

// Authentication
api.get('/api/auth', function(req, res) {
    res.send(501);
});

// Balance
api.get('/api/balance', function(req, res) {
    res.send(501);
});


var server = https.createServer(ssl, api)
    .listen(options.port, function() {
        console.log('Server is up and running on port ' + options.port);
     });

server.on('request', function(req) {
    console.log('[' + utils.getDateTime() + '] Incoming request:',
        req.ip, req.method, req.url);
});
