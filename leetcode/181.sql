-- ok but not good.
select name as employee
from employee as x
where x.managerid is not NULL and x.salary > (
    select salary
    from employee as y
    where y.id = x.managerid
)

-- good.
select x.name as employee
from employee as x
join (
    select id, salary from employee
) as y
on y.id = x.managerid
where x.salary > y.salary
