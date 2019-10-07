SHELL := /bin/bash
BUILD_DIR = ./bin

mk_dir:
	if [[ ! -d $(BUILD_DIR) ]]; then mkdir $(BUILD_DIR);fi

clean: 
	rm -rf $(BUILD_DIR)/*


build:
	gcc -o $(BUILD_DIR)/server server.c errmsg.c
	gcc -o $(BUILD_DIR)/client client.c errmsg.c

all: mk_dir clean build
