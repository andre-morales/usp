default: build

run: build
	java -cp build;lib; Pong

build: build/Player.class build/Ball.class build/Score.class

build/Player.class: src/Player.java
	javac src/Player.java -d build --class-path lib

build/Ball.class: src/Ball.java
	javac src/Ball.java -d build --class-path lib	

build/Score.class: src/Score.java
	javac src/Score.java -d build --class-path lib
	