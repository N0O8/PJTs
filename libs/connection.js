var mysql = require('mysql');
var connection = mysql.createConnection({
	  host     : '34.85.84.78',
	  user     : 'root',
	  password : 'noob12',
	  database : 'stockdb'
});

connection.connect();

module.exports = connection;

