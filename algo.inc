%macro printMassivR 0
mov esi, arrrez
%rep 200
mov eax,[esi]
add esi, 4
PRINT_DEC 4, eax
PRINT_STRING ' '
%endrep 
NEWLINE 
%endmacro

proc array_merge
mov esi, arr1
mov edi, arr2

.while1:
mov ebx, [arr1i]
mov eax, [esi+ebx*4]


mov ebx, [arr2i]
cmp eax, [edi+ebx*4]
JBE .SL1
JA .SL2

.SL1:
mov ebx, [arrrezi]
mov [arrrez+ebx*4], eax
mov ebx, [arr1i]

cmp ebx, [sizeA1]
inc ebx

JB .incA1
jmp .stopSL1

.SL2:
mov eax, [edi+ebx*4]
mov ebx, [arrrezi]
mov [arrrez+ebx*4], eax
mov ebx, [arr2i]

cmp ebx, [sizeA2]
inc ebx

JB .incA2
jmp .stopSL2

.incA1:
mov [arr1i], ebx 
jmp .incR

.incA2:
mov [arr2i], ebx
jmp .incR

.incR:
mov ebx, [arrrezi]
inc ebx
mov [arrrezi], ebx
cmp ebx, [sizeR]
JB .while1

.stopSL1:
mov ebx, [arr2i]
mov eax, [edi+ebx*4]
inc ebx
mov [arr2i], ebx

mov ebx, [arrrezi]
mov [arrrez+ebx*4], eax
inc ebx
mov [arrrezi], ebx
cmp ebx, [sizeR]
JB .stopSL1
JAE .end

.stopSL2:
mov ebx, [arr1i]
mov eax, [esi+ebx*4]
inc ebx
mov [arr1i], ebx

mov ebx, [arrrezi]
mov [arrrez+ebx*4], eax
inc ebx
mov [arrrezi], ebx
cmp ebx, [sizeR]
JB .stopSL2
JAE .end

.end:
endproc	


%macro GetMinRun 0
mov     ecx, 200
cmp     ecx, 63
jle	.end1
mov     eax, 0
.while1:
mov	edx, ecx
and     edx, 1
or      eax, edx
sar     ecx, 1
cmp     ecx, 63
jg	.while1
jmp	.end2
.end1:
mov     eax, 0
.end2:
add     eax,ecx
;PRINT_DEC 4, eax
;NEWLINE
%endmacro

%macro genMassiv 0
mov esi, stack
%rep 210
call _Rand
add [esi], eax 
add esi, 4
%endrep 
%endmacro

proc _sortP
.a2: 
mov eax, [num]

mov ecx, eax
xor ebx, ebx
.a3:
mov eax,[esi+ecx*4-4]
cmp [esi+ecx*4],eax
jnb .a1
setna bl
xchg eax,[esi+ecx*4]
mov [esi+ecx*4-4],eax
.a1:
loop .a3
add esi,4
dec ebx
jnz .exit1

mov edx, [num]
dec edx
mov [num], edx 

jnz .a2
.exit1:

endproc	


%macro printMassiv 0
mov esi, stack
%rep 200
mov eax,[esi]
add esi, 4
PRINT_DEC 4, eax
PRINT_STRING ' '
%endrep 
NEWLINE 
%endmacro

%macro printBefore 0
    PRINT_STRING msg1
    NEWLINE
%endmacro


%macro printAfter 0
	NEWLINE
    PRINT_STRING msg2
    NEWLINE
%endmacro
	
         
proc _Rand
		xor edx, edx
        mov     eax,[seed]
        or      eax,eax
        jnz     .f
        rdtsc
        xor     eax,edx
        mov     [seed],eax
.f:
        xor     edx,edx
        mov     ecx,127773
        div     ecx
        mov     ecx,eax
        mov     eax,16807
        mul     edx
        mov     edx,ecx
        mov     ecx,eax
        mov     eax,2836
        mul     edx
        sub     ecx,eax
        xor     edx,edx
        mov     eax,ecx
        mov     [seed],ecx
        mov     ecx,1000
        div     ecx
        mov     eax,edx
		
		pop edx		
	nop
	nop
	nop
	ret	
endproc	

proc Timsort
    GetMinRun
    mov [sizeA1],eax
    mov [sizeA2],eax
    dec eax
    mov [num],eax
    inc eax
    push eax
    add eax, eax
    mov [sizeR],eax
.init:
    pop eax
    push eax
    mov esi, stack
    mov edi, arr1
.loadA1:    
    mov ecx, [esi]
    mov [edi], ecx
    add esi, 4
    add edi, 4
    dec eax
    cmp eax, 0
    JA .loadA1
    push esi
 
    mov esi, arr1    
    call _sortP
    
    mov edi, arr2
    pop esi
    pop eax
    push eax
    jmp .loadA2

.loadA2:
    mov ecx, [esi]
    mov [edi], ecx   
    add esi, 4
    add edi, 4      
    dec eax
    cmp eax, 0        
    JA .loadA2
    
    mov eax,[sizeA2] 
    dec eax
    mov [num],eax
    mov esi, arr2    
    call _sortP
    call array_merge
    
.nextL:
    mov eax, [sizeR]
    cmp eax, [sizeStack]
    JAE .end
    
    mov edi, arr1 
    mov esi, arrrez
    mov ebx, [sizeR]
.for2:
    mov eax, [esi]
    mov [edi], eax
    add esi, 4
    add edi, 4 
    dec ebx
    cmp ebx, 0
    JA .for2
    
    mov eax, [sizeR]
    mov [sizeA1], eax
    push eax
    add eax, [sizeA2] 
    mov [sizeR], eax
    pop eax
    ;mov esi, [stack+eax*4]
    mov esi, stack
    add esi, eax
    add esi, eax
    add esi, eax
    add esi, eax
    mov edi, arr2
    
    mov eax, 0
    mov [arr1i], eax
    mov [arr2i], eax
    mov [arrrezi], eax
    
    mov eax, [sizeA2]
    jmp .loadA2    
   
    ;jmp .end              
.end:  
endproc	