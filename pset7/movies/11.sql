select title
from movies
join ratings on ratings.movie_id = movies.id
join stars on stars.movie_id = movies.id
join people on stars.person_id = people.id
where people.name = "Chadwick Boseman"
order by ratings.rating DESC
limit 5;