-- In 1.sql, write a SQL query to list the titles of all movies released in 2008.
-- *Your query should output a table with a single column for the title of each movie.

-- Query 1
SELECT M.title
FROM Movies M
WHERE M.year == 2008;
