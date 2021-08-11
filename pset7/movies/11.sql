-- In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
-- *Your query should output a table with a single column for the title of each movie.
-- *You may assume that there is only one person in the database with the name Chadwick Boseman.

-- Query 11
SELECT M.title
FROM Movies M, Ratings R, People P, Stars S
WHERE M.id = R.movie_id AND M.id = S.movie_id AND S.person_id = P.id
AND P.name == 'Chadwick Boseman'
ORDER BY R.rating DESC
LIMIT 5;
