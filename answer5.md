# Question : How can I preform an SQL query to retrieve values that don't have a specific value? #

## Answer : ##

In order to perform a conditional query you can use the SQL `NOT` operator. In this example where you have multiple conditionals that must be satisfied it may make more sense to use the `NOT IN` operator with a list of values that must be satisfied.

## Examples

#### NOT
`SELECT * FROM table WHERE NOT id = 'A' AND NOT id = 'B';`

More examples - [W3Schools](https://www.w3schools.com/sql/sql_and_or.asp)

#### NOT IN
`SELECT * FROM table WHERE id NOT IN ('A', 'B');`

More examples - [W3Resource](https://www.w3resource.com/mysql/comparision-functions-and-operators/not-in.php)

Also if depending on how you determined which values you need to exclude (if you query to find them for example) you can either nest the Not In with a query or take a look at this stack overflow solution - [Not-in-vs-Not-Exists](https://stackoverflow.com/questions/173041/not-in-vs-not-exists)
