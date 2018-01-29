clean:
	rm cli serv

server:
	gcc -g server.c -o serv -lm
client:
	gcc -g client.c -o cli -lm
