select department.name as Department, xname as Employee, xsalary as Salary
from (
    select x.departmentid as xdid, x.name as xname, x.salary as xsalary
    from employee as x
    join (
        select departmentid, max(salary) as maxsalary
        from employee
        group by departmentid
    ) as y
    on (
        x.departmentid = y.departmentid
        and
        x.salary = y.maxsalary
    )
) as z
join department
on z.xdid = department.id
