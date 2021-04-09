build:
	emcc --embed-file scripts janet.c app.c -o janet.html -I./ --shell-file ./shell_minimal.html -s EXPORTED_FUNCTIONS="['_main', '_run_some_janet']" -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']"

run:
	php -S 127.0.0.1:12345
	firefox localhost:12345/janet.html
