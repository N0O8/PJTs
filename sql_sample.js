var mysql      = require('mysql');
var connection = mysql.createConnection({
	        host     : '34.85.84.78',
	        user     : 'root',
	        password : 'noob12',
	        database : 'test'
});

connection.connect();
var chatlist;
var exports = module.exports = {};

exports.get_chatlist = function()
{	
	connection.query('SELECT * FROM chat', function (error, results, fields) {
		chatlist = "";
		if (error) {
			console.log(error);
		}		    

		var i = 0;
		while(i < results.length){
			chatlist = chatlist + `<br>${results[i].user_name} : ${results[i].content}`;
			i++;
		}
	});
	return chatlist;
};

exports.send_message = function(name, message)
{
	connection.query(`insert into chat(user_name, content) values('${name}', '${message}')`, function (error, result, fields) {
		if(error) {
			console.log(error);
		}
	});
};
