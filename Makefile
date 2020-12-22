all:
	gcc -o compiler driver.c parseTree.c parse.c lexer.c FirstNFollow.c ast.c -lm
