
# BATCH NO. 10
# VISHNU DUTT PALADUGU--- 2010A7PS029P
# MOHIT MINHAS --- 2010A7PS084P



output : driver.o lexer.o parser.o symbolTable.o semanticAnalyzer.o typeChecker.o
    gcc -o toycompiler driver.o lexer.o parser.o symbolTable.o semanticAnalyzer.o typeChecker.o
driver.o : driver.c
    gcc -c driver.c
lexer.o : lexer.c
    gcc -c lexer.c
parser.o : parser.c
    gcc -c -g parser.c
symbolTable.o : symbolTable.c
    gcc -c symbolTable.c
semanticAnalyzer.o : semanticAnalyzer.c
    gcc -c semanticAnalyzer.c
typeChecker.o : typeChecker.c
    gcc -c typeChecker.c   