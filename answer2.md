# Question : I am working on nodeJs(backend) and (Angular) I want to generate a .ics file URL for google calendar and for Apple and Microsoft as a downloadable file. 
I know there is a node module ics and I am using that, but that only creates a .ics file I want this to be unique for each user and also want this to delete automatically. 
Also, it should automatically sync with the events added. Any suggestion for this? #

## Answer : ##

I have been unable to find a way that would continually update someone's schedule since this would require continuous access to someone's calendar. While building a scheduling site I got around your storage and unique file problem by using a brute force solution.

First, as a client access the download endpoint an unique ics file is generated and stored as schedule_date_client-name.ics. This unique file is then sent to the user using res.download and promptly deleted using fs.unlink(path_to_file).

### Here is an example of this in action : ###

    try {
        res.download(path, function(error){
            if (error) {
                console.log("Error : ", error)
            }
            fs.unlink(path, (error) => {
                // log any error
                if (error) {
                    console.log(error);
                }
            })
        });
    } catch (e) {
        next(e);
    }
The best way I found around this is to generate the .ics file as the user accesses a /download url endpoint. Send the file in a downloadable format using res.download in your controller file. Here is more information on the packages I used for this solution :

Node .ics : https://www.npmjs.com/package/ical-generator Node file : https://nodejs.dev/learn/the-nodejs-fs-module

Require the modules :

  const ical = require('ical-generator');
  
  const fs = require("fs");
