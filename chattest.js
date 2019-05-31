var http = require('http');
var fs = require('fs');
var url = require('url');
var host = '0.0.0.0';
var port = 3000;
var chatTest = require('./sql_sample.js');
var chatList
var app = http.createServer(function(request,response){
	    var _url = request.url;
	    var queryData = url.parse(_url, true).query;
	    var title = queryData.id;
	    if(_url == '/'){
		          title = 'ChatTest';
	    }

	    response.writeHead(200);
	    var template = `
	      <html>
		      <script type="text/javascript">
		function test(msg)
	      {
		if(event.keyCode == 13)
		{
			var tmp = "'" + msg + "'";
		          location.reload();
		}
            }
	      </script>
		      <head>
		      </head>
		      <body>

		${chatTest.get_chatlist()}		      
	      <br>
		      <input type = "text" id = "message" onkeydown = "test(this.value)"></input>

		      </body>
		      </html>
		    `;
	    response.end(template);

});
app.listen(port, host);

