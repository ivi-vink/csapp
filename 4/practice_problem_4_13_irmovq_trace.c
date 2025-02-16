/*
stage		Generic 		Specific
		irmovq kv, rB		irmovq $128, %rsp

Fetch 		icode:ifun <- M_1[PC]	0x3:0x0 <- M_1[PC]
		rA:rB <- M_1[PC+1]	F:0x4 <- M_1[PC+1]
		valC <- M_8[PC+2]       $0x80 <- M_8[PC+2]
		valP <- PC + 10         valP <- PC + 10

Execute		valE <- 0 + valC	valE <- $0x80

Memory

Write Back 	R[rB] <- valE		%rsp <- $0x80

PC Update	PC <- valP		PC <- PC + 10


PC <- PC + 10
rsp <- $0x80

forgot to substitute the addresses from diagram 4.17.
*/
