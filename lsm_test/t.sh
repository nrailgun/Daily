#!/usr/bin/env sh

# Construct policies
for i in lsm_test/pls/*; do
	cat $i > /proc/actpl
done

# Deny
attr -qS -s attrs -V "name='John';role='Student';security=0;" '/bin/cat'
attr -qS -s attrs -V "name='Admin';security=0;" testf
cat testf

# Deny
attr -qS -s attrs -V "name='John';role='Student';security=0;" '/bin/cat'
attr -qS -s attrs -V "role='Teacher';security=5;" testf
cat testf

# Allow
attr -qS -s attrs -V "name='John';role='Student';security=5;" '/bin/cat'
attr -qS -s attrs -V "name='Admin'" testf
cat testf
