# Question : How can i add a front end and backend validation to a node js user authentication project? #

## Answer : ##

### Frontend Login Validation ###
You should not be validating or authenticating anything on the front end. That being said, you can use HTML attributes to help take some of the load off your backend and to prevent people from seeing the password as they are typing.

    <input type="password" class="input" name="password" autocomplete="off" placeholder="Enter password" required>
    
In this example the password type attribute is key to tell HTML the type of input it should be expecting. Adding required will prevent users from leaving the field blank so it can help take a load off your backend and add another level of very basic security (this is still by no means necessary safe input). For more information on the password input type, check out the MDN entry : https://developer.mozilla.org/en-US/docs/Web/HTML/Element/input/password

### Backend Login Validation for Node JS ###
You can use a routing (routes.js) file on the back end to serve different pages with information being passed through a validator. Deciding whether the login data is valid should always be done in a separate controller file that is connected to a database like MySQL for example. Validation or sanitizing user input should always be done in this file but is specific to the type of database you are using. Usually this involves escaping the user input or using prepared statements when dealing with the database.

However in a more general sense, the best Node JS validator in my opinion is express-validator (especially if you are already using express in your backend). By creating your own, and by using existing middleware, you can control what is being passed between a client and server. This allows you to control whether your server continues with the get/post request or if it should send error pages.

To include express-validator in your project simply install the package using npm and include it in your files using :

    const { body } = require("express-validator");

or if you need to validate data being passed as url parameters :

    const { query } = require("express-validator");
An example of this validator in use for password input in a routes.js file :

    router.post("/login",
        [
            body("password", "The Password must be of minimum 4 characters length")
                .notEmpty()
                .trim()
                .isLength({ min: 4 }),
        ],
        login
    );
This example deals with the login url endpoint and if a post request is made at this endpoint, then validate the ejs/html body element with class name "password" using standard express validation methods. For more examples and information on how to use the express-validator check out : https://express-validator.github.io/docs/.

