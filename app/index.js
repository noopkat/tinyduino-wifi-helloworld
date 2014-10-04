var Hapi = require('hapi');
var request = require('request');

// set up Mailgun credentials here
var mailgunOpts = {
  url: '',
  pass: '',
  formData: {
    from: '',
    to: '',
    subject: 'you have mail!',
    text: 'go check your mailbox, champ.'
  }
};

// set up Twilio credentials here
var twilioOpts = {
  sid: '',
  token: '',
  from: '', 
  to: '' 
};
var Twilio = require('twilio')(twilioOpts.sid, twilioOpts.token);

// fill this in with the token your tinyduino will send as part of the request
var passToken = '558822';

var server = new Hapi.Server('10.0.1.4', 8081);

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
      to: twilioOpts.to,
      from: twilioOpts.from
  }, function(err, message) {
      if (err) {
        process.stdout.write('twilio failed: ' + err);
      }
      process.stdout.write('twilio sms sent: ' + message.sid);
  });
}

function sendEmail() {
  // mailgun API call
  request.post({
    url : mailgunOpts.url,
    auth: {
      user: 'api',
      password: mailgunOpts.pass,
    },
    form: mailgunOpts.formData
    
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