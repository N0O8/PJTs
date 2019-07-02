var mongoose = require('mongoose');
var db = mongoose.connection;

// make connection
db.on('error', console.error);
db.once('open', function(){
	  console.log("Connected to mongod server");
});

mongoose.connect('mongodb://35.200.87.174:27017/stockdb', { useNewUrlParser: true });

// make schema
var Schema = mongoose.Schema;
var stockSchema = new Schema({
	  name: String,
	  Date: String
});

var Stock = mongoose.model('stock', stockSchema);

module.exports = function(app)
{
	    // CREATE
	    app.post('/template/create', function(req, res){
		          var stock = new Stock({
				            name: req.body.name,
				            Date: req.body.date
				        });

		          stock.save(function(err){
				          if(err)
					          {
						            console.error(err);
						            res.json({result: 0});
						            return;
						          }
				          res.json({result: 1});
				        });
		        });

	    // GET ALL
	    app.get('/template', function(req,res){
		          Stock.find(function(err, template){
				          if(err)
					          {
						            console.log("db failed");
						            return res.status(500).send({error: 'database failure'});
						          }
				          res.json(template);
				        });
		        });

	    // GET SINGLE
	    app.get('/template/:name', function(req, res){
		          Stock.findOne({name: req.params.name}, function(err, template){
				          if(err) return res.status(500).json({error: err});
				          if(!template) return res.status(404).json({error: 'data not found'});
				          res.json(template);
				        });
		        });

	    // UPDATE
	    app.put('/template/update', function(req, res){
	          Stock.findOneAndUpdate({name: req.body.name}, {Date: req.body.date}, {new: true, useFindAndModify: false}, function(err, template){
			          if(err) return res.status(500).json({error: err});
			          if(!template) return res.status(404).json({error: 'data not found'});
			          res.json({message: 'data updated'});
			        });
	        });

	    // DELETE
	    app.delete('/template/:name', function(req, res){
		          Stock.remove({name: req.params.name}, function(err, output){
				          if(err) return res.status(500).send({error: 'database failure'});

				          if(!output.result.n) return res.status(404).json({error: 'delete data not found'});
				          res.json({message: 'data removed'});
				        });
		            res.status(204).end();
		        });

	    console.log("CRD finished");
}

