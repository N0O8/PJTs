var history = require('./libs/history.js');
var trade = require('./libs/trade.js');
var http = require('http');
var qs = require('querystring');
var url = require('url');
var host = '0.0.0.0';
var port = 3000;
var address = "http://localhost:3000";


var app = http.createServer(function(request, response){
	  var _url = request.url;
	  var queryData = url.parse(_url, true).query;

	  if(_url == '/'){
		      response.writeHead(200);
		      var home = `
		        <html>
			          <head></head>
			          <body>
			            <a href = "/history">history</a>
			            <br>
			            <a href = "/trade">trade</a>
			          </body>
			        </html>
			      `;
		      response.end(home);
		    }
	  else if(_url == '/history')
		  {
		      history.set_buylist('123');
		      history.update_buylist();
		      history.get_buylist();

		      response.writeHead(302, {'Location' : address});
		      response.end();
		    }
	  else if(_url == '/trade')
		  {
		      trade.set_buylist();
		      trade.update_buylist();
		      trade.get_buylist();

		      response.writeHead(302, {'Location' : address});
		      response.end();
		    }
});

app.listen(port, host);

