-- In 5.sql, write a SQL query to list the titles and release years of all Harry Potter movies, in chronological order.
-- *Your query should output a table with two columns, one for the title of each movie and one for the release year of each movie.
-- *You may assume that the title of all Harry Potter movies will begin with the words “Harry Potter”, and that if a movie title begins with the words “Harry Potter”, it is a Harry Potter movie.

-- Query 5
SELECT M.title, M.year
FROM Movies M
WHERE M.title LIKE 'Harry Potter%'
ORDER BY M.year;
