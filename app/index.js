var Hapi = require('hapi');

// fill this in with the token your tinyduino will send as part of the request
var passToken = '558822';

var server = new Hapi.Server('localhost', 8081);

server.route({
    method: 'GET',
    path: '/mailbox',
    handler: function (request, reply) {

      reply('why you gotta troll me, friend :(');
    }
});

server.route({
    method: 'GET',
    path: '/mailbox/token/{token}',
    handler: function (request, reply) {
      if (request.params.token && request.params.token === passToken) {
        reply('you\'ve got mail!');

        // dispatch to Twilio or MailGun here

      } else {
        reply('why you gotta troll me, friend :(');
      }
      
    }
});

// Start the server
server.start();