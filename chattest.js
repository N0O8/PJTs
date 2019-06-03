var http = require('http');
var fs = require('fs');
var qs = require('querystring');
var url = require('url');
var host = '0.0.0.0';
var port = 3000;
var chatTest = require('./sql_sample.js');
var chatList = chatTest.get_chatlist();

var app = http.createServer(function(request,response){
	var _url = request.url;
	var queryData = url.parse(_url, true).query;

	if(_url == '/'){
		chatList = chatTest.get_chatlist();
		var title = 'ChatTest';
		response.writeHead(200);

		var template = `
			<html>
			<head><title>${title}</title></head>
			<body>
				${chatList}
				<br>
				<form action = "/send_message" method = "post">
					<input type = "text" name = "id" value = "jh" size = "5"></input>
					<input type = "text" name = "message" onkeydown = "javascript:if(event.keyCode == 13) submit();"></input>
				</form>
			</body>
			</html>
		`;
		response.end(template);
	}
	else if(_url == '/send_message'){
		var body = '';
		request.on('data', function(data){
			body = body + data;	
		});
		request.on('end', function(){
			var post = qs.parse(body);
			chatTest.send_message(post.id, post.message);
			setTimeout(function()
			{
				var loc = "http://35.200.87.174:3000";
				chatList = chatTest.get_chatlist();
				response.writeHead(302, {'Location' : loc});
				response.end();
			}, 500);
		});
	}
});
app.listen(port, host);

