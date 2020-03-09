code	:=code
.PHONY: code fibo $(code) clean
fibo: $(code)
	gcc ./code/main.o ./code/fibo.o -o fibo
$(code):
	make --directory=$@
clean:
	rm -f ./code/*.o
