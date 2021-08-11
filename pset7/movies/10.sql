-- In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
-- *Your query should output a table with a single column for the name of each person.

-- Query 10
SELECT P.name
FROM People P, Directors D, Ratings R, Movies M
WHERE P.id = D.person_id AND D.movie_id = M.id AND M.id = R.movie_id
AND R.rating >= 9.0;
