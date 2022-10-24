# Question : What is the Variable Scope in ejs/express? #

## Answer : ##
What you are doing with your code is rendering the page using ejs and passing the params object to the page. By passing it to the page you can render the page with access to the variables you passed in using the following tags : <%= *variable* =>

In terms of scope, you have now rendered the page to have access to all the variables you have passed in under the name **params** during the operation : res.render("server/edit", params);

If you have passed other variables through api calls to your backend you will also be able to access them in their according scope, but **unless you include other variables to be passed as parameters you will not be able to access other variables from your backend.**

Example :

--> userController.js

    var outOfScope = True;
    const params = {
      versions: versions,
      user: user,
      statsParams: statsParams,
      csrfToken: csurf.createToken(req),
    };
    res.render("index", params);
    return;

--> index.html

    ...
    <h1>Variable</h1>
    <p><%= params.user %></p>
    ...

**This will not work**

    ...
    <h1>Variable</h1>
    <p><%= outOfScope %></p>
    ...

If you still have issues regarding access to variables you haven't passed it is possible you may have included them from another file by accident (ex. a header that is included).

I hope this helps, but if you are having trouble with specific variables please include them in your question as well as how you are accessing them.
