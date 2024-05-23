# MAKEFILE DO EP1
# Targets: build, run

CLASS_PATH="lib/GameLib.jar;src;"

## Descomentar se necesário para colocar a JDK aqui!
## JDK_HOME=C:\\Program Files\\Java\\jdk-17\\ 

# Caminho do caminho JAR do java. Apenas usado para compilar o GameLib.jar
JAVA_JAR=$(JDK_HOME)bin/jar

default: build

# Roda o EP sem depurador.
run: build
	java -cp "output;lib/GameLib.jar;" Pong

# Constrói todos os .class necessários mas não executa nada
build: output/Player.class output/Ball.class output/Score.class

# Constrói um .class a partir de um .java
output/%.class: src/%.java
	javac $< -d output --class-path $(CLASS_PATH)

# GameLib: Biblioteca .jar com as classes entregues pelo professor, anexadas do javadoc
gamelib: lib/GameLib.jar
	
# Invoca o comando jar da JDK e inclui todos os arquivos das pastas classes e javadoc no .jar
lib/GameLib.jar:
	$(JAVA_JAR) cvf lib/GameLib.jar -C lib/classes . -C lib/javadoc .

clean:
	del output\\*.class
