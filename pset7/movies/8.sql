-- In 8.sql, write a SQL query to list the names of all people who starred in Toy Story.
-- *Your query should output a table with a single column for the name of each person.
-- *You may assume that there is only one movie in the database with the title Toy Story.

-- Query 8
SELECT P.name
FROM People P, Stars S, Movies M
WHERE P.id = S.person_id AND S.movie_id = M.id AND M.title == 'Toy Story';
