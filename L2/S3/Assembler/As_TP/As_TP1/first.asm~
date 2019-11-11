extern printf
extern scanf

segment .data
promptsaut db "",10,0
promptq1 db "Question 1",10,10,0
prompta db "Entrez un premier entier a : ",0
promptb db "Entrez un second entier b : ",0
formatSortie1 db " a Or b = %ld",10,10,0
formatEntree db "%ld",0

promptq2 db "Question 2",10,10,0
prompts db "Quel est votre sexe (H: 1 | F: 0) : ",0
manend db "Bonjour Monsieur",10,10,0
womanend db "Bonjour Madame",10,10,0

promptq3 db "Question 3",10,10,0
promptn db "Entrez un nombre : ",0
oddend db "Impair.",10,10,0
evenend db "Pair.",10,10,0

promptq4 db "Question 4",10,10,0
p2trueend db "C'est une puissance de 2",10,10,0
p2falseend db "Ce n'est pas une puissance de 2",10,10,0

promptq5 db "Question 5",10,10,0
formatSortie2 db "a * b = %ld",10,10,0

promptq6 db "Question 6",10,10,0
q6goodend db "0k1n0n Ok.",10,10,0
q6badend db "0k1n0n fail.",10,10,0

segment .bss
entier resq 1
entiera resq 1
entierb resq 1
res resq 1

segment .text
	global asm_main
asm_main:
	push rbp
	push rbx
	push rcx

	mov rdi,promptsaut
	mov rax,0
	call printf
	
	jmp EndQ5

	mov rdi,promptq1
	mov rax,0
	call printf	
	
	mov rdi,prompta
	mov rax,0
	call printf

	mov rdi,formatEntree
	mov rsi,entiera
	mov rax,0
	call scanf
	mov rbx,[entiera]

	mov rdi,promptb
	mov rax,0
	call printf

	mov rdi,formatEntree
	mov rsi,entierb
	mov rax,0
	call scanf
	mov rcx,[entierb]

	or rbx,rcx
	mov [res],rbx
	
	mov rdi,formatSortie1
	mov rsi,[res]
	mov rax,0
	call printf
	
EndQ1:
	mov rdi,promptq2
	mov rax,0
	call printf

	mov rdi,prompts
	mov rax,0
	call printf

	mov rdi,formatEntree
	mov rsi,entier
	mov rax,0
	call scanf
	mov rbx,[entier]

if1:
	mov rax,0
	cmp rax,rbx
	je WomanEnd
	jmp ManEnd

WomanEnd:
	mov rdi,womanend
	mov rax,0
	call printf
	jmp EndQ2

ManEnd:
	mov rdi,manend
	mov rax,0
	call printf

EndQ2:
	mov rdi,promptq3
	mov rax,0
	call printf

	mov rdi,promptn
	mov rax,0
	call printf
	
	mov rdi,formatEntree
	mov rsi,entier
	mov rax,0
	call scanf
	
	mov rbx,[entier]
	mov rax,2
	mov rdx,0
	idiv rbx

if2:
	cmp rdx,0
	je EvenEnd
	jmp OddEnd

EvenEnd:
	mov rdi,evenend
	mov rax,0
	call printf
	jmp EndQ3

OddEnd:
	mov rdi,oddend
	mov rax,0
	call printf

EndQ3:
	mov rdi,promptq4
	mov rax,0
	call printf

	mov rdi,promptn
	mov rax,0
	call printf

	mov rdi,formatEntree
	mov rsi,entier
	mov rax,0
	call scanf
	mov rbx,[entier]
	mov rcx,0
	mov r9,1

while1:
	cmp rcx,64
	je p2FalseEnd

test1:
	cmp rbx,r9
	je p2TrueEnd
	inc rcx
	shl r9,1
	jmp while1


p2TrueEnd:
	mov rdi,p2trueend
	mov rax,0
	call printf
	jmp EndQ4

p2FalseEnd:
	mov rdi,p2falseend
	mov rax,0
	call printf 

EndQ4:
	mov rdi,promptq5
	mov rax,0
	call printf

	mov rdi,prompta
	mov rax,0
	call printf

	mov rdi,formatEntree
	mov rsi,entiera
	mov rax,0
	call scanf
	mov rbx,[entiera]

	mov rdi,promptb
	mov rax,0
	call printf

	mov rdi,formatEntree
	mov rsi,entierb
	mov rax,0
	call scanf
	mov rcx,[entierb]

	mov r9,0
while2:
	cmp rcx,0
	je EndWhile2
if3:
	mov r8,rcx
	and r8,1
	cmp r8,1
	jne Endif3
	add r9,rbx
Endif3:
	shl rbx,1
	shr rcx,1
	jmp while2	

EndWhile2:
	mov [res],r9
	mov rdi,formatSortie2
	mov rsi,[res]
	mov rax,0
	call printf
EndQ5:
	mov rdi,promptq5
	mov rax,0
	call printf

	mov rdi,promptn
	mov rax,0
	call printf

	mov rdi,formatEntree
	mov rsi,entier
	mov rax,0
	call scanf
	mov rdi,[entier]
	call fonc1

if4:
	cmp rax,0
	je endif4
	mov rdi,q6goodend
	mov rax,0
	call printf
	jmp EndQ6
endif4:
	mov rdi,q6badend
	mov rax,0
	call printf
EndQ6:
	
	pop rcx
	pop rbx
	pop rbp
	mov rax,0
	ret

fonc1:
	push rbp
	mov rbp,rsp
	mov r13,rdi
	mov r15,-1
	push r15
	mov r14,1
	mov rcx,0
while3:
	cmp rcx,33
	je q6badend

	and r13,1
	cmp r13,0
	jne Endwhile3
	push r14
	inc rcx	
	shr rbx,1
	mov r13,rbx
	jmp while3

Endwhile3:
	cmp rcx,64
	je q6BadEnd
	
	and r13,1
	cmp r13,1
	jne q6Test
	inc rcx
	pop r14
	cmp r14,-1
	je q6BadEnd
	shr rbx,1
	mov r13,rbx
	jmp Endwhile3
	
q6Test:	
	pop r14
	cmp r14,-1
	je q6GoodEnd
	cmp r14,1
	

while4:
	cmp r14,-1
	je q6BadEnd
	pop r14
	jmp while4
	
q6BadEnd:
	mov rax,0
	mov rsp,rbp
	pop rbp
	ret

q6GoodEnd:
	mov rax,1
	mov rsp,rbp
	pop rbp
	ret
