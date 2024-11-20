

all: build 

build: akinator

akinator: 
	cd Akr && make

run: 
	cd Akr && ./Akinator

clean: 
	cd Akr && make clean
	