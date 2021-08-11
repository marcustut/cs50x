-- In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
-- *Your query should output a table with a single column for the name of each person.
-- *There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
-- *Kevin Bacon himself should not be included in the resulting list.

-- Query 13
SELECT P.name
FROM People P, Stars S
WHERE S.person_id = P.id
AND P.name != 'Kevin Bacon'
AND S.movie_id IN (
    SELECT movie_id
    FROM People, Stars
    WHERE person_id = id AND name = 'Kevin Bacon' AND birth == 1958
)
GROUP BY P.name;
