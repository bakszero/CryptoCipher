server:
	[ -e serv ] && rm -f serv
	gcc -g server.c -o serv -lm
client:
	[ -e cli ] && rm -f cli
	gcc -g client.c -o cli -lm
