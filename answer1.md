# Question : How can i add a front end and backend validation to a node js user authentication project? #

## Answer : ##

### Simultaneous MySQL Database Connection ###

I would be hesitant to use any client input to connect to a server, but I understand how this could be something you would need to do in some scenarios. The simplest and quickest way around this issue would be to create a second database connection file. In order to make this dynamic, you can simply require the module based on conditions in your code, so sometimes it will be called and promised at only certain points, after certain conditions. This process could be risky and requires requiring modules in the middle of your code so it isn't ideal but can get the job done. Ex :

    const dbConnection = require("../utils/dbConnection");

//conditional {

         const controlledDBConnection = require("../utils/controlledDBConnection");

         var [row] = await controlledDBConnection.execute("SELECT * FROM `foo`;")

}

Although using more files could potentially have an effect on space constraints and could potentially slow down code while waiting for a new promise, but the overall effect will be minimal. controlledDBConnection.js would just be something close to a duplicate to dbConnection.js with slightly different parameters depending on your needs.

Another path you can take if you want to avoid using multiple files is to export a module with a dynamically set variable from your controller file, and then import it into a standard connection file. This would allow you to change up your connection without rewriting a duplicate, but you will need diligent error checks and a default.

Info on modules in JS : https://javascript.info/import-export

Some other points

Use Environment Variables for your database information like host, etc. since this will allow for you to easily change information for your database all in one place, while also allowing you to include your .env file in .gitignore if you are using github

Here is another great stack overflow question/answer that might help with setting up a dynamic connection file : How to create dynamically database connection in Node.js?

How to set up .env files : https://nodejs.dev/learn/how-to-read-environment-variables-from-nodejs

How to set up .gitignore : https://stackabuse.com/git-ignore-files-with-gitignore/

