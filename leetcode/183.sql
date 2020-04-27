select name as customers
from customers
where customers.id not in (
    select distinct customerid from orders
)
