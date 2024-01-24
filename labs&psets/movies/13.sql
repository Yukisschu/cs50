SELECT DISTINCT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.id IN
(
    SELECT DISTINCT movie_id
    FROM stars
    WHERE person_id IN
    (
        SELECT DISTINCT id
        FROM people
        WHERE name = 'Kevin Bacon'
    )
) AND people.name != 'Kevin Bacon';




