-- In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
-- *Your query should output a table with a single column for the title of each movie.
-- *You may assume that there is only one person in the database with the name Johnny Depp.
-- *You may assume that there is only one person in the database with the name Helena Bonham Carter.

-- Query 12
SELECT M.title
FROM Movies M, People P, Stars S
WHERE M.id = S.movie_id AND S.person_id = P.id
AND P.name == 'Johnny Depp'
AND S.movie_id IN (
    SELECT movie_id
    FROM Stars, People
    WHERE Stars.person_id = People.id AND People.name == 'Helena Bonham Carter'
);
