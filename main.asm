%include "c32.inc"
%include "algo.inc"
%include "io.inc"

BITS 32

section .data
    msg1 db 'Before sorting!', 0
    msg2 db 'After sorting!', 0
    
    arr1 times 210 dd 0
    arr2 times 210 dd 0
    arrrez times 210 dd 0
    
    sizeA1 dd 0
    sizeA2 dd 0
    sizeR dd 0
    
    arr1i dd 0
    arr2i dd 0
    arrrezi dd 0
    
    stack times 1000 dd 0
    sizeStack dd 200
    
    num   dd 20 
    seed dd 0


section .text
    global CMAIN

CMAIN:
    mov ebp, esp
    genMassiv
    printBefore
    printMassiv 
      
    call Timsort
 
    
    printAfter
    printMassivR
    xor eax, eax
    ret    