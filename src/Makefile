all:
	@echo "Installing required Repos....           [connecting... https://kali.kalilinux.org/kansas_server]"
	sudo apt-get install figlet
	gcc server.c -o ../chatapp -pthread
	echo "Build Successfull"
	@echo "Usage : goto chat app directory-------> run ./chatapp command"
	../chatapp

build:
	@echo "Installing required Repos....           [connecting... https://kali.kalilinux.org/kansas_server]"
	sudo apt-get install figlet
	gcc server.c -o ../chatapp -pthread
	echo "Build Successfull"
	@echo "Usage : ./chatapp"

doit:
	./chatapp

clean:
	rm ../chatapp
