var Hapi = require('hapi');
var request = require('request');

// set up twilio credentials here
var twilioSid = '',
    twilioToken = '',
    twilioNums = { from: '', to: '' },
var Twilio = require('twilio')(twilioSid, twilioToken);

// set up Mailgun credentials here
var mailgunURL = '';
var mailgunPass = '';

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
    path: '/mailbox/token/{token?}',
    handler: function (request, reply) {
      if (request.params.token && request.params.token === passToken) {
        // Twilio
        sendSMS();

        // MailGun
        sendEmail();

        reply('you\'ve got mail!');

      } else {
        reply('why you gotta troll me, friend :(');
      }
    }
});

function sendSMS() {
  // twilio api
  Twilio.messages.create({
      body: 'you have mail!',
      to: twilioNums.to,
      from: twilioNums.from
  }, function(err, message) {
      if (err) {
        process.stdout.write('twilio failed: ' + err);
      }
      process.stdout.write('twilio sms sent: ' + message.sid);
  });
}

function sendEmail() {
  var formData = {
    from: 'Mailbox Monitor <someone@email.com>',
    to: 'Me <me@email.com>',
    subject: 'you have mail!',
    text: 'go check your mailbox, champ.'
  };

  // mailgun API call
  request.post({
    url : mailgunURL,
    auth: {
      user: 'api',
      password: mailgunPass,
    },
    form: formData
    
  }, function(err, mailgunRes) {
    if (err) {
      process.stdout.write('mailgun failed: ' + err);
    } else {
      process.stdout.write('mail sent: ' + mailgunRes.body);
    }
  });
}

// Start the server
server.start();