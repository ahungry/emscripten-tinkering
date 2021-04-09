build:
	emcc --embed-file scripts \
	--preload-file assets \
	janet.c \
	app.c -o janet.html \
	-I./ --shell-file ./shell_minimal.html \
	-O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' \
	-s EXPORTED_FUNCTIONS="['_main', '_run_some_janet']" \
	-s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']"

run:
	firefox localhost:12345/janet.html
	php -S 127.0.0.1:12345
