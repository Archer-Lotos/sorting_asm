; NASM macro set to make interfacing to 32-bit programs easier -*- nasm -*-



%imacro proc 1			; begin a procedure definition

%push proc

          global %1

%1:       push ebp

          mov ebp,esp

%assign %$arg 8

%define %$procname %1

%endmacro



%imacro arg 0-1 4		; used with the argument name as a label

%00	  equ %$arg

%assign %$arg %1+%$arg

%endmacro



%imacro endproc 0

%ifnctx proc

%error Mismatched 'endproc'/'proc'

%else

	  leave

	  ret

__end_%$procname:		; useful for calculating function size

%pop

%endif

%endmacro