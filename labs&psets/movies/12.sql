SELECT DISTINCT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id AND people.name = 'Bradley Cooper'
JOIN stars AS stars_2 ON movies.id = stars_2.movie_id
JOIN people AS people_2 ON people_2.id = stars_2.person_id AND people_2.name = 'Jennifer Lawrence';
