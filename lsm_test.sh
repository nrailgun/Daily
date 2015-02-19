#!/usr/bin/env sh

r="DENY FILE_PERMISSION IF { SUBJECT.security < 2; OBJECT.name = 'Admin'; };"

echo "$r" > /proc/actpl

r=`cat <<HERE
DENY FILE_PERMISSION IF {
	SUBJECT.security = 0;
	[ OBJECT.security > 0; OBJECT.role = 'teacher'; ];
};
HERE`

echo "$r" > /proc/actpl
