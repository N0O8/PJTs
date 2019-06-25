var history = require('./libs/history.js');
var trade = require('./libs/trade.js');
var express = require('express');
var app = express();
var bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

var port = process.env.PORT || 3000;

var connection = require('./libs/connection')(app);

app.listen(3000);
console.log('Listening on port 3000...');
