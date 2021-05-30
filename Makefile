cc: parser.y scanner.l 
	bison -d parser.y -o parser.tab.cc
	flex  -o lex.yy.cc scanner.l
	g++ -Wall -o cc lex.yy.cc parser.tab.cc driver.cc -lfl -lm
	

clean:
	rm -rf cc