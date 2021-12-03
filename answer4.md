# Question : TL;DR: Vertical or Horizontal scaling for this system design? I have NGINX running as a load balancer for my application. It distributes across 4 EC2 (t2.micro's cuz I'm cheap) to route traffic and those are all currently hitting one server for my MySQL database (also a t2.micro, totalling 6 separate EC2 instances for the whole system). I thinking about horizontally scale my database via Source/Replica distribution, and my thought is that I should route all read queries/GET requests (the highest traffic volume I'll get) to the Replicas and all write queries/POST requests to the Source db. I know that I'll have to programmatically choose which DB my servers point to based on request method, but I'm unsure of how best to approach that or if I'm better off vertically scaling my DB at that point and investing in a larger EC2 instance. Currently I'm connecting to the Source DB using an express server and it's handling everything. I haven't implemented the Source/Replica configuration just yet because I want to get my server-side planned out first. Here's the current static connection setup: **Removed** set up an express middleware function that looks at the request method and connects to the appropriate database by creating 2 configuration templates to put into the createConnection function (I'm unsure of how I would make sure it doesn't try to reconnect if a connection already exists, though) if possible just open two connections simultaneously and route which database takes which method (I'm hopeful this option will work so that I can make things simpler) Is this feasible? Am I going to see worse performance doing this than if I just vertically scaled my EC2 to something with more vCPUs? Please let me know if any additional info is needed. #

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
