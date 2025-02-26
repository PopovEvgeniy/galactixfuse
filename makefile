install:
	@echo Installation in progress. Please wait
	@$(CC) galactixfuse.c -g0 -O0 -o /bin/galactixfuse
	@chmod ugo+rx /bin/galactixfuse
	@echo Installation successfully complete
uninstall:
	@rm -f /bin/galactixfuse
	@echo Uninstallation successfully complete