# Write your MySQL query statement below
Update salary Set sex = (Case When sex = 'm' Then 'f' Else 'm' End)
