; Listing generated by Microsoft (R) Optimizing Compiler Version 19.16.27034.0 

	TITLE	D:\advcpp\4����\6_�Լ���ü7.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?cmp1@@YA_NHH@Z					; cmp1
PUBLIC	?cmp2@@YA_NHH@Z					; cmp2
PUBLIC	_main
PUBLIC	??$foo@P6A_NHH@Z@@YAXP6A_NHH@Z@Z		; foo<bool (__cdecl*)(int,int)>
PUBLIC	??$foo@ULess@@@@YAXULess@@@Z			; foo<Less>
PUBLIC	??$foo@UGreater@@@@YAXUGreater@@@Z		; foo<Greater>
; Function compile flags: /Odtp
; File d:\advcpp\4����\6_�Լ���ü7.cpp
;	COMDAT ??$foo@UGreater@@@@YAXUGreater@@@Z
_TEXT	SEGMENT
tv69 = -8						; size = 4
_b$ = -1						; size = 1
_f$ = 8							; size = 1
??$foo@UGreater@@@@YAXUGreater@@@Z PROC			; foo<Greater>, COMDAT

; 13   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 8

; 10   : struct Greater {inline bool operator()(int a, int b) { return a > b; } };

	mov	eax, 1
	cmp	eax, 2
	jle	SHORT $LN5@foo
	mov	DWORD PTR tv69[ebp], 1
	jmp	SHORT $LN3@foo
$LN5@foo:
	mov	DWORD PTR tv69[ebp], 0
$LN3@foo:

; 14   : 	bool b = f(1, 2);

	mov	cl, BYTE PTR tv69[ebp]
	mov	BYTE PTR _b$[ebp], cl

; 15   : }

	mov	esp, ebp
	pop	ebp
	ret	0
??$foo@UGreater@@@@YAXUGreater@@@Z ENDP			; foo<Greater>
_TEXT	ENDS
; Function compile flags: /Odtp
; File d:\advcpp\4����\6_�Լ���ü7.cpp
;	COMDAT ??$foo@ULess@@@@YAXULess@@@Z
_TEXT	SEGMENT
tv69 = -8						; size = 4
_b$ = -1						; size = 1
_f$ = 8							; size = 1
??$foo@ULess@@@@YAXULess@@@Z PROC			; foo<Less>, COMDAT

; 13   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 8

; 9    : struct Less    {inline bool operator()(int a, int b) { return a < b; }};

	mov	eax, 1
	cmp	eax, 2
	jge	SHORT $LN5@foo
	mov	DWORD PTR tv69[ebp], 1
	jmp	SHORT $LN3@foo
$LN5@foo:
	mov	DWORD PTR tv69[ebp], 0
$LN3@foo:

; 14   : 	bool b = f(1, 2);

	mov	cl, BYTE PTR tv69[ebp]
	mov	BYTE PTR _b$[ebp], cl

; 15   : }

	mov	esp, ebp
	pop	ebp
	ret	0
??$foo@ULess@@@@YAXULess@@@Z ENDP			; foo<Less>
_TEXT	ENDS
; Function compile flags: /Odtp
; File d:\advcpp\4����\6_�Լ���ü7.cpp
;	COMDAT ??$foo@P6A_NHH@Z@@YAXP6A_NHH@Z@Z
_TEXT	SEGMENT
_b$ = -1						; size = 1
_f$ = 8							; size = 4
??$foo@P6A_NHH@Z@@YAXP6A_NHH@Z@Z PROC			; foo<bool (__cdecl*)(int,int)>, COMDAT

; 13   : {

	push	ebp
	mov	ebp, esp
	push	ecx

; 14   : 	bool b = f(1, 2);

	push	2
	push	1
	call	DWORD PTR _f$[ebp]
	add	esp, 8
	mov	BYTE PTR _b$[ebp], al

; 15   : }

	mov	esp, ebp
	pop	ebp
	ret	0
??$foo@P6A_NHH@Z@@YAXP6A_NHH@Z@Z ENDP			; foo<bool (__cdecl*)(int,int)>
_TEXT	ENDS
; Function compile flags: /Odtp
; File d:\advcpp\4����\6_�Լ���ü7.cpp
_TEXT	SEGMENT
_f2$ = -2						; size = 1
_f1$ = -1						; size = 1
_main	PROC

; 17   : {

	push	ebp
	mov	ebp, esp
	push	ecx

; 18   : 	Less f1;
; 19   : 	Greater f2;
; 20   : 	foo(cmp1); // T : bool(*)(int, int)

	push	OFFSET ?cmp1@@YA_NHH@Z			; cmp1
	call	??$foo@P6A_NHH@Z@@YAXP6A_NHH@Z@Z	; foo<bool (__cdecl*)(int,int)>
	add	esp, 4

; 21   : 	foo(cmp2); // T : bool(*)(int, int)

	push	OFFSET ?cmp2@@YA_NHH@Z			; cmp2
	call	??$foo@P6A_NHH@Z@@YAXP6A_NHH@Z@Z	; foo<bool (__cdecl*)(int,int)>
	add	esp, 4

; 22   : 	foo(f1);   // T : Less

	movzx	eax, BYTE PTR _f1$[ebp]
	push	eax
	call	??$foo@ULess@@@@YAXULess@@@Z		; foo<Less>
	add	esp, 4

; 23   : 	foo(f2);   // T : Greater

	movzx	ecx, BYTE PTR _f2$[ebp]
	push	ecx
	call	??$foo@UGreater@@@@YAXUGreater@@@Z	; foo<Greater>
	add	esp, 4

; 24   : }

	xor	eax, eax
	mov	esp, ebp
	pop	ebp
	ret	0
_main	ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File d:\advcpp\4����\6_�Լ���ü7.cpp
;	COMDAT ?cmp2@@YA_NHH@Z
_TEXT	SEGMENT
tv65 = -4						; size = 4
_a$ = 8							; size = 4
_b$ = 12						; size = 4
?cmp2@@YA_NHH@Z PROC					; cmp2, COMDAT

; 7    : inline bool cmp2(int a, int b) { return a > b; }

	push	ebp
	mov	ebp, esp
	push	ecx
	mov	eax, DWORD PTR _a$[ebp]
	cmp	eax, DWORD PTR _b$[ebp]
	jle	SHORT $LN3@cmp2
	mov	DWORD PTR tv65[ebp], 1
	jmp	SHORT $LN4@cmp2
$LN3@cmp2:
	mov	DWORD PTR tv65[ebp], 0
$LN4@cmp2:
	mov	al, BYTE PTR tv65[ebp]
	mov	esp, ebp
	pop	ebp
	ret	0
?cmp2@@YA_NHH@Z ENDP					; cmp2
_TEXT	ENDS
; Function compile flags: /Odtp
; File d:\advcpp\4����\6_�Լ���ü7.cpp
;	COMDAT ?cmp1@@YA_NHH@Z
_TEXT	SEGMENT
tv65 = -4						; size = 4
_a$ = 8							; size = 4
_b$ = 12						; size = 4
?cmp1@@YA_NHH@Z PROC					; cmp1, COMDAT

; 6    : inline bool cmp1(int a, int b) { return a < b; }

	push	ebp
	mov	ebp, esp
	push	ecx
	mov	eax, DWORD PTR _a$[ebp]
	cmp	eax, DWORD PTR _b$[ebp]
	jge	SHORT $LN3@cmp1
	mov	DWORD PTR tv65[ebp], 1
	jmp	SHORT $LN4@cmp1
$LN3@cmp1:
	mov	DWORD PTR tv65[ebp], 0
$LN4@cmp1:
	mov	al, BYTE PTR tv65[ebp]
	mov	esp, ebp
	pop	ebp
	ret	0
?cmp1@@YA_NHH@Z ENDP					; cmp1
_TEXT	ENDS
END
