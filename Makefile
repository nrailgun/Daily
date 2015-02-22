obj-$(CONFIG_SECURITY_ACT) += act.o

act-y := attr_repo.o attr_repo_ctx.o attr_repo_help.o parse.o policy.o \
	actfs.o lsm_file.o lsm.o 
