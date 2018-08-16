 emcc \
    src/main.c \
   -I /usr/local/include \
   -s USE_SDL=2 \
   -s USE_WEBGL2=1 \
   -DEXPORTED_FUNCTIONS='["_main", "_demo_app_name", "_demo_app_desc", "_demo_app_resize" "_demo_app_link"]' \
   -ansi -Wall -std=c89 -O2 \
   -o ./web_bin/cknet_demo.js

