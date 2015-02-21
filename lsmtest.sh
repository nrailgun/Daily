#!/usr/bin/env sh

# Allow
attr -qS -s attrs -V "name='John';role='Student';security=0;" '/bin/cat'
attr -qS -s attrs -V "name='Admin';security=0;" testf
cat testf

r="DENY FILE_PERMISSION IF { SUBJECT.security < 2; OBJECT.name = 'Admin'; };"

echo "$r" > /proc/actpl

# Deny
attr -qS -s attrs -V "name='John';role='Student';security=1;" '/bin/cat'
attr -qS -s attrs -V "name='Admin';security=0;" testf
cat testf

# Allow
attr -qS -s attrs -V "name='John';role='Student';security=1;" '/bin/cat'
attr -qS -s attrs -V "name='Damin';security=0;" testf
cat testf

r="DENY FILE_PERMISSION IF { SUBJECT.security = 0; [ OBJECT.security > 0; OBJECT.role = 'Teacher'; ]; };"
echo "$r" > /proc/actpl

# Deny
attr -qS -s attrs -V "name='John';role='Student';security=1;" '/bin/cat'
attr -qS -s attrs -V "name='Admin';security=0;" testf
cat testf

# Deny
attr -qS -s attrs -V "name='John';role='Student';security=0;" '/bin/cat'
attr -qS -s attrs -V "role='Teacher';security=0;" testf
cat testf

# Deny
attr -qS -s attrs -V "name='John';role='Student';security=0;" '/bin/cat'
attr -qS -s attrs -V "role='Student';security=5;" testf
cat testf

# Allow
attr -qS -s attrs -V "name='John';role='Student';security=5;" '/bin/cat'
attr -qS -s attrs -V "name='Admin';role='Teacher';" testf
cat testf
