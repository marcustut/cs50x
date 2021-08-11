-- In 4.sql, write a SQL query to determine the number of movies with an IMDb rating of 10.0.
-- *Your query should output a table with a single column and a single row (plus optional header) containing the number of movies with a 10.0 rating.

-- Query 4
SELECT COUNT(M.title)
FROM Movies M, Ratings R
WHERE R.movie_id = M.id AND R.rating == 10.0;
