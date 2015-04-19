ACT Linux Attribute Based Access Control Module
===============================================

ACT is a linux based attribute-based access control prototype. It's just for
personal use, and many feathers are not implemented yet.

## CONFIGs
* `CONFIG_ACT_TEST`: Compile test codes.
* `CONFIG_ACT_LSM_STUB`: Compile `attr_repo` stub code.
* `CONFIG_SECURITY_ACT`: Compile `ACT` module into linux kernel.

## COMPILE
To compile `ACT`, following tools are needed:
* GNU Make
* gcc 4.8+
* GNU ld 2.24+

`cp` or `mv` this repo to `$LINUXSRC/security/`, add CONFIGs to your
`.config`, then start make:
```
cp -r act $LINUXSRC/security
cp .config $LINUXSRC/security
make mrproper
make oldconfig
make
make modules_install install
```
Modify grub config, then reboot your computer.
```
GRUB_CMDLINE_LINUX="security=act"
```

## Policy
Policy bnf-style grammar:
```
PL    = S ACT ’IF’ (AND|OR)
S     = (’ALLOW’|’DENY’)
ACT   = (’FILE_OPEN’|’FILE_READ’|...)
CONDS = ((COND|AND|OR)|(COND|AND|OR) CONDS)
COMP  = (’= ’|’>’|’<’|’HAS’|’IN’)
COND  = (’SUBJECT’|’OBJECT’) ANAME COMP AVAL ’;’
ANAME = [a-z_][a-Z_0-9]+
AVAL  = (VAL|VALS)
VAL   = (NUM|STR)
VALS  = ’(’ _VALS ’)’
_VALS = (VAL|VAL ’,’ VALS)
AND   = ’{’ CONDS ’};’
OR    = ’[’ CONDS ’];’
```
