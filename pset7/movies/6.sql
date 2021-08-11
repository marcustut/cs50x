-- In 6.sql, write a SQL query to determine the average rating of all movies released in 2012.
-- *Your query should output a table with a single column and a single row (plus optional header) containing the average rating.

-- Query 6
SELECT AVG(R.rating)
FROM Ratings R, Movies M
WHERE R.movie_id = M.id AND M.year == 2012;
