## Question I'm currently trying to validate some inputs in Express using express-validator. I know that it's typical to pass it as a separate middleware into the route, but I needed access to the res object, so I had to write it in the way you see below. The part that I'm struggling with is the custom validator. I'd like it to call an asynchronous function store.todoListTitleExists(title) that queries a database and checks if a title already exists. If the title doesn't exist, my intention is to save an error message which I can later display as a flash message. Currently, this code doesn't work. I've looked through the documentation but I can't seem to figure out how to make this custom validator + error message work properly since it calls an asynchronous function. Any help would be apprecated. Thanks! ##

## Answer ##

Express-validator is intended to sanitize and validate data being sent between the client and server. In order to handle this in a way that is scalable I would recommend using a file to handle all of your sites post requests (something like routes.js for example).

Here is a sample custom router that displays an error message if the validation fails :

    body("feildName", "Feild must be selected")
        .custom(val => {

            if (val.feildName == "Select...") return false

            return true

        }
    ),
Once you have isolated all routing to a specific file, you can add arguments like the example below for error messages to be served with the page (personnaly I use ejs templates so these error messages are displayed using the following code :

### controller.js ###
    const errors = validationResult(req);
    const {
        body
    } = req;

    if (!errors.isEmpty()) {
        return res.render('index', {
            error: errors.array()[0].msg
        });
    }

    res.render("index");

## index.ejs ###
    <div class="error">
            <% if(typeof error !== 'undefined'){ %>
                  <div class="err-msg"><%= error %></div>
            <% } %>
    </div>
