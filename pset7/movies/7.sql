-- In 7.sql, write a SQL query to list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.
-- *Your query should output a table with two columns, one for the title of each movie and one for the rating of each movie.
-- *Movies that do not have ratings should not be included in the result.

-- Query 7
SELECT M.title, R.rating
FROM Movies M, Ratings R
WHERE R.movie_id = M.id AND M.year == 2010
ORDER BY R.rating DESC, M.title ASC;
