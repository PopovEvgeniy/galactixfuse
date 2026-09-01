install:
	@echo Installation in progress. Please wait
	@$(CC) galactixfuse.c -g0 -O0 -o /bin/galactixfuse
	@chmod ugo+rx /bin/galactixfuse
	@echo Installation was successfully completed
uninstall:
	@rm /bin/galactixfuse
	@echo Uninstallation was successfully completed