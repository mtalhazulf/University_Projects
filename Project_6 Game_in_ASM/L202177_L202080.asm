[org 0x0100]
jmp start
;  Bomb and Phase 3 ;
mousecheck:
		pusha
		mov byte[mousevalflag],0
			mov ax,[mousex]
			mov bx,[mousex1]
			mov cx,[mousey]
			mov dx,[mousey1]
			;StartingX = 28
			;StartingY = 6 
			;TotalX = StartingX + BoardSize
			;TotalY = StartingY + BoardSize
			ysame:
					cmp cx,dx
					jne xsame

					right:
						add ax,2
						cmp ax,bx
						je validmouse
						sub ax,2
						
						;Right = mousex + 2
					left:
						sub ax,2
						cmp ax,bx
						je validmouse
						add ax,2
						;Left = mousex - 2 
					jmp endmousecheck
			xsame:
					cmp ax,bx
					jne endmousecheck
					up:
						add cx,1
						cmp cx,dx
						je validmouse
						sub cx,1
						;UP = mousey + 1
					Down:	
						sub cx,1
						cmp cx,dx
						je validmouse
						add cx,1
						;Down = mousey - 1
					jmp endmousecheck
			
			validmouse:
			mov byte[mousevalflag],1
	endmousecheck:

		popa
	ret

;-----------------------------------------------------------------------------------------
changech:
		;Change RandomVal Here
		push bp
		mov bp, sp
		mov ax, 0xb800
		mov es, ax

		getValue:
			call randomNumber
			mov ah, 0
			mov al, [randomNum]
			push ax
			call setRandomChar
		
		; cmp [randomNum], dx
		; je getValue
		; mov di, [bp+4]
		; mov word[es:di], ax

		pop bp
		ret 2
;-----------------------------------------------------------------------------------------
sequencecheck:
		push bp
		mov bp,sp
	pusha
		mov ax,0xb800
		mov es,ax
		mov di,[bp+4] ; LOC 
		mov bx,[es:di]

		mov cx,0 ;Reset the Counter

		samevalupcheck:
					sub di,160
					mov ax,[es:di]
					inc cx
					cmp ax,bx
					jne samevalupcheckexit

					push di
					call changech

					jmp samevalupcheck
		samevalupcheckexit:
					dec cx; If Last Loop Val Not Same
					mov di,[bp+4]

		samevaldowncheck:
					add di,160
					mov ax,[es:di]
					inc cx
					cmp ax,bx
					jne samevaldowncheckexit

					push di
					call changech

					jmp samevaldowncheck
		samevaldowncheckexit:
					dec cx; If Last Loop Val Not Same
					mov di,[bp+4]
		
		samevalleftcheck:
					sub di,4
					mov ax,[es:di]
					inc cx
					cmp ax,bx
					jne samevalleftcheckexit

					push di
					call changech

					jmp samevalleftcheck
		samevalleftcheckexit:
					dec cx; If Last Loop Val Not Same
					mov di,[bp+4]
		
		samevalrightcheck:
					add di,4
					mov ax,[es:di]
					inc cx
					cmp ax,bx
					jne samevalrightcheckexit

					push di
					call changech

					jmp samevalrightcheck
		samevalrightcheckexit:
					dec cx; If Last Loop Val Not Same
		add [score],cx
		;Bomb Logic
		cmp cx, 5
		jb end_condition
		add byte[score], 10
		add byte[blocker_flag], 1

	end_condition:
	popa
		pop bp
	ret 2
;-----------------------------------------------------------------------------------------
concludingscreen:
				call clrscr

				mov ax,7 ;Attribute
				push ax

				mov ax,0610h 
				push ax			;Location of the String

				push word concluding ;MSG
				push word [concludingsize]
				call printsrvc

				pop ax

				mov ax,1056
				push ax
				push word[score]
				call printnum

				mov ax,64 ;Attribute
				push ax

				mov ax,1508h 
				push ax			;Location of the String

				push word concludingend ;MSG
				push word [concludingendsize]
				call printsrvc

				pop ax

		ret
;-----------------------------------------------------------------------------------------

logic:
	looplogic:
		;Reseting Every Crucial Variable
		call printscore
		call printremmove
		call printtheREST

		mov byte[mousevalflag],0
		mov word[swapword1],' '
		mov word[swapword2],' '
		
		call getmouse1
		call calcmouse1;Gets Position in AX
		push swapword1
		push ax
		call getvalfromscr
		

		cmp byte[mousevalflag],1 ; Word Check Whether Exists Or not
		jne restore
		mov byte[mousevalflag],0

		call selectcell;Selects the Cell

		call getmouse2
		
		call mousecheck

		cmp byte[mousevalflag],1 ; Checks The Position Is Adjacent or not.
		jne restore
		mov byte[mousevalflag],0

		call calcmouse2
		push swapword2  ;To Store the Byte
		push ax			;Calculate LOC of 2 Click
		call getvalfromscr
		
		;Verifies the Correct Byte
		cmp byte[mousevalflag],1
		jne restore
		mov byte[mousevalflag],0

		call putvalonscr

		push word[loc1]
		call sequencecheck

		push word[loc2]
		call sequencecheck

		mov ax,1
		sub [remmove],ax

		cmp word[remmove],0		
		je endlogic

		jmp looplogic
	restore : 

		call unselectcell
		jmp looplogic
	endlogic:
	ret
;-----------------------------------------------------------------------------------------

start: 
	   	call init
		call onetimeprint
		call printscore
		push word[boardsize]
        call Characters
		call logic
		call concludingscreen
      
	terminate:		

		mov ax,0x4c00
		int 0x21
;-----------------------------------------------------------------------------------------

clrscr:
        mov ax,0xb800
        mov es,ax
        mov di,0
        mov ah,0x07
        mov al,0x20
        mov cx,2000

        cld
        rep stosw

        mov di,0
        ret;clearing the screen

;-----------------------------------------------------------------------------------------

printsrvc:
		push bp
		mov bp, sp

		mov  cx , [bp+4]
		mov ch,0;clears the Uper Value.
		
		mov word bx , [bp+6] ;Msg Offset
		
		mov dx, [bp+8] ;Location of the Msg

		mov al, [bp+10] ; normal attrib
		
		pop bp  ;Inputing Ends Here 

		mov bp, bx ;Copies the address of Msg to bp

		mov bh, 0 ; output on page 0 
		mov bl , al ;Copying the value of al to bl Attribute

		mov ah, 0x13 ; service 13 - print string 
		mov al, 1 ; subservice 01 – update cursor 
		 
		 
		push cs 
		pop es ; segment of string 
		;mov bp, message ; offset of string 
		int 0x10 

		ret 6

;-----------------------------------------------------------------------------------------

getname:
	mov bx,name
	mov cx,0
	l1:
		mov ax,0
		int 0x16 

		mov [bx],al
		inc bx
		inc cx;service 16 - get keystroke
		
		cmp al,0Dh
		jne l1

		sub cx,1 ;removes the last Return character 
		mov [namesize],cx

		mov ax,7
		push ax
		push word 0614h
		push word name ;MSG 
		push word [namesize]
		
		call printsrvc
		pop ax

	ret 
;-----------------------------------------------------------------------------------------

getBoardSize:

		mov ax,0
		int 0x16 
		
		sub al,30h

		cmp al,5h
		jb invalid
		

		cmp al,9h
		ja alpha
		
        mov [boardsize],al
        ret

			alpha : 
				sub al,21h

				cmp al,10h
				jb invalid

				cmp al,12h
				ja invalid
		found :
			cmp al,10h
			je ten
			cmp al,11h
			je eleven
			cmp al,12h
			je twelve
            
            jmp invalid
		ten: 
			mov word[boardsize],0xA
            jmp endsize
		eleven:
			mov word[boardsize],0xB
            jmp endsize
		twelve:
			mov word[boardsize],0xC
            jmp endsize
        endsize:
				ret
	invalid: 
			mov ax,7
			push ax
		
			mov ax,0703h
			push ax			;Location of the String
			push word invalidinp ;MSG
			mov ax,[invalidinpsize] 
			push ax;size of the string

				call printsrvc

			mov ax,0
			int 0x16 
			
			pop ax

			jmp terminate
;-----------------------------------------------------------------------------------------

printscore: 
		push bp 
		mov bp, sp 

		push es 
		push ax 
		push bx 
		push cx 
		push dx 
		push di 
			

			mov ax, 0xb800 
			mov es, ax ; point es to video base 
			mov ax, [score] ; load number in ax 
			mov bx, 10 ; use base 10 for division 
			mov cx, 0 ; initialize count of digits 
		nextdigit: 
			mov dx, 0 ; zero upper half of dividend 
			div bx ; divide by 10 
			add dl, 0x30 ; convert digit into ascii value 
			push dx ; save ascii value on stack 
			inc cx ; increment count of values 
			cmp ax, 0 ; is the quotient zero 
			jnz nextdigit ; if no divide it again 
			
			mov di, 426 ; set cursor position
		nextpos: 
			pop dx ; remove a digit from the stack 
			mov dh, 0x2F ; use normal attribute 
			mov [es:di], dx ; print char on screen 
			add di, 2 ; move to next screen location 
			loop nextpos ; repeat for all digits on stack

		pop di 
		pop dx 
		pop cx 
		pop bx 
		pop ax 
		pop es

		pop bp 
	ret
	

;-----------------------------------------------------------------------------------------
printremmove: 
		push bp 
		mov bp, sp 

		push es 
		push ax 
		push bx 
		push cx 
		push dx 
		push di 
		
			mov ax, 0xb800 
			mov es, ax ; point es to video base 
			mov ax, [remmove] ; load number in ax 
			mov bx, 10 ; use base 10 for division 
			mov cx, 0 ; initialize count of digits 
		nextdigit0: 
			mov dx, 0 ; zero upper half of dividend 
			div bx ; divide by 10 
			add dl, 0x30 ; convert digit into ascii value 
			push dx ; save ascii value on stack 
			inc cx ; increment count of values 
			cmp ax, 0 ; is the quotient zero 
			jnz nextdigit0 ; if no divide it again 
			
			mov di, 3420 ; set cursor position
			mov word[es:di],' '
			add di,1
			mov word[es:di],' '
			sub di,1
		nextpos0: 
			pop dx ; remove a digit from the stack 
			mov dh, 0x2F ; use normal attribute 
			mov [es:di], dx ; print char on screen 
			add di, 2 ; move to next screen location 
			loop nextpos0 ; repeat for all digits on stack

		pop di 
		pop dx 
		pop cx 
		pop bx 
		pop ax 
		pop es

		pop bp 
	ret
;-----------------------------------------------------------------------------------------

printtotalmove: 
		push bp 
		mov bp, sp 

		push es 
		push ax 
		push bx 
		push cx 
		push dx 
		push di 
		
			mov ax, 0xb800 
			mov es, ax ; point es to video base 
			mov ax, [totalmove] ; load number in ax 
			mov bx, 10 ; use base 10 for division 
			mov cx, 0 ; initialize count of digits 
		nextdigit1: 
			mov dx, 0 ; zero upper half of dividend 
			div bx ; divide by 10 
			add dl, 0x30 ; convert digit into ascii value 
			push dx ; save ascii value on stack 
			inc cx ; increment count of values 
			cmp ax, 0 ; is the quotient zero 
			jnz nextdigit1 ; if no divide it again 
			
			mov di, 3476 ; set cursor position

		nextpos1: 
			pop dx ; remove a digit from the stack 
			mov dh, 0x2F ; use normal attribute 
			mov [es:di], dx ; print char on screen 
			add di, 2 ; move to next screen location 
			loop nextpos1 ; repeat for all digits on stack

		pop di 
		pop dx 
		pop cx 
		pop bx 
		pop ax 
		pop es

		pop bp 
	ret
;-----------------------------------------------------------------------------------------
init: ; Starting Input Handler 
		call clrscr

		mov ax,64 ;Attribute
		push ax
		mov ax,1508h 
		push ax			;Location of the String
		push word concludingend ;MSG
		push word [concludingendsize]
		call printsrvc
		pop ax

		mov ax,7
		push ax
		
		mov ax,0213h
		push ax			;Location of the String
		push word welcome ;MSG
		mov ax,31 
		push ax;size of the string

			call printsrvc

		mov ax,031Bh
		push ax			;Location of the String
		push word input ;MSG
		mov ax,10 
		push ax;size of the string

			call printsrvc

		mov ax,0603h
		push ax			;Location of the String
		push word namemsg ;MSG 
		push word [namemsgsize];size of the string

			call printsrvc

		call getname

		mov ax,0703h
		push ax			;Location of the String
		push word boardmsg ;MSG 
		push word [boardmsgsize];size of the string

			call printsrvc

		call getBoardSize

		pop ax; AX Normal Attrib one Time Enter

		ret

;-----------------------------------------------------------------------------------------
onetimeprint:
		call clrscr

		mov ax,64 ;Attribute
		push ax

		mov ax,020Dh 
		push ax			;Location of the String
		push word nametitle ;MSG
		push word [nametitlesize]

			call printsrvc

		mov ax,0213h
		push ax			;Location of the String
		push word name ;MSG
		mov ax,[namesize]
		push ax

		 	call printsrvc

		pop ax; Atrribute POPED

		mov ax,32
		push ax

		mov ax,022Dh
		push ax			;Location of the String
		push word scoretitle
		push word [scoretitlesize]
		call printsrvc

		mov ax,152Dh
		push ax			;Location of the String
		push word totalmovetitle
		push word [totalmovetitlesize]
		call printsrvc
	
		mov ax,150Dh
		push ax			;Location of the String
		push word remmovetitle
		push word [remmovetitlesize]
		call printsrvc

		call printremmove
		call printtotalmove

		pop ax; Atrribute POPED

	ret
;-----------------------------------------------------------------------------------------

Characters:
	push bp
	mov bp, sp

	push ax
	push bx
	push cx
	push dx
	push di
	push si
	push es
	;--------------
	;Logic

	mov bx, 6      ; required row number
	mov ax, 80 		; total column
	mul bx 	; multiply with row number
	add ax, 28      ; required column number
	shl ax, 1
	mov si, ax

	mov ax, 0xb800
	mov es, ax
	mov dx, 0
	mov bx, [bp+4] ;external counter
	sub bx, 1
	
	print_loop2:
		mov di, si ;zero address in bp to di
		add di, dx ;add next line to di
		mov cx, [bp+4] ; internal counter
		cld
		innerloop2:
			call randomNumber ;get random num
			;push di ;push location
			mov ah, 0
			mov al, [randomNum] 
			push ax ;push random num
			call setRandomChar ;call print
			add di, 4
			loop innerloop2
		add dx, 160 ;next line
		dec bx
		cmp bx, 0
		jne print_loop2
	;Logic End
	;--------------------------------------------

	mov bx, 1
	mov di, si
	add di, dx
	mov cx, [bp+4] ; internal counter
		cld
		innerloop_2:
			mov ah, 0x33
			mov al, ' '
			mov word[es:di],ax
			add di, 4
			loop innerloop_2
	
	pop es
	pop si
	pop di
	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret 2
;-----------------------------------------------------------------------------------------

printtheREST:
	push bp
	mov bp, sp

	push ax
	push bx
	push cx
	push dx
	push di
	push si
	push es
	;--------------
	cmp byte[blocker_flag], 3
	ja out_
	cmp byte[blocker_flag], 3
	jb out_

	mov bx, 6      ; required row number
	mov ax, 80 		; total column
	mul bx 	; multiply with row number
	add ax, 28      ; required column number
	shl ax, 1
	mov si, ax

	mov ax, 0xb800
	mov es, ax
	mov dx, 0
	mov bx, [boardsize] ;external counter
	sub bx, 1
	
	print_loop__:
		mov di, si ;zero address in bp to di
		add di, dx ;add next line to di
		mov cx, [boardsize] ; internal counter
		cld
		innerloop__:
			add di, 4
			loop innerloop__
		add dx, 160 ;next line
		dec bx
		cmp bx, 0
		jne print_loop__

	; mov cx, [boardsize] ;external counter
	; innerloop___:
	; 	call randomNumber ;get random num
	; 	mov ah, 0
	; 	mov al, [randomNum] 
	; 	push ax ;push random num
	; 	call setRandomChar ;call print
	; 	mov word [es:di], ax
	; 	add di, 4
	; 	loop innerloop___

	mov di, si
	add di, dx
	mov cx, [boardsize] ; internal counter
		cld
		innerloop_:
			push di
			call changech
			add di, 4
			loop innerloop_

	out_:
	pop es
	pop si
	pop di
	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret 

;-----------------------------------------------------------------------------------------

setRandomChar:
	push bp
	mov bp, sp
	push bx
	push ax
	push es

	mov ax, 0xb800
	mov es, ax


	mov ax, [bp+4] ; number
	
	cmp al, 0
	je Zero
	cmp al, 1 
	je One
	cmp al, 2
	je Two
	cmp al, 3
	je Three
	cmp al, 4
	je Four
	cmp al, 5
	je Five
	cmp al, 6
	je Six
	jmp Seven

	Out_:
		pop es
		pop ax
		pop bx
		pop bp
		ret 2

	Zero:
		mov al, 'A'
		mov ah, 0x30
		mov word [es:di], ax
		jmp Out_
	
	One:
		mov al, 'B'
		mov ah, 0x31
		mov word [es:di], ax
		jmp Out_
	
	Two:
		mov al, 'C'
		mov ah, 0x3A
		mov word [es:di], ax
		jmp Out_
	
	Three:
		mov al, 'D'
		mov ah, 0x3C
		mov word [es:di], ax
		jmp Out_
	
	Four:
		mov al, 'E'
		mov ah, 0x34
		mov word [es:di], ax
		jmp Out_
	
	Five:
		mov al, 'F'
		mov ah, 0x35
		mov word [es:di], ax
		jmp Out_
	
	Six:
		mov al, 'G'
		mov ah, 0x36
		mov word [es:di], ax
		jmp Out_
	
	Seven:
		mov al, 'H'
		mov ah, 0x3B
		mov word [es:di], ax
		jmp Out_
;-----------------------------------------------------------------------------------------

randomNumber:
; generate a random number using the system time
	push cx
	push dx
	push ax

	rdtsc ;getting a random number in ax dx

	xor dx,dx ;making dx 0

	mov cx,10 ;making cx 8

	div cx ;dividing by 8 to get numbers from 0-7

	mov [randomNum],dl ;moving the random number in variable

	pop ax
	pop dx
	pop cx
	ret

;-----------------------------------------------------------------------------------------

printnum:
        push bp
        mov bp, sp
        push es
        push ax
        push bx
        push cx
        push dx
        push di
        mov ax, 0xb800
        mov es, ax 
        mov ax, [bp+4] 
        mov bx, 10 
        mov cx, 0 
        nextdigit00: 
            mov dx, 0 
            div bx
            add dl, 0x30 
            push dx
            inc cx 
            cmp ax, 0 
            jnz nextdigit00
            mov di, [bp+6]
            nextpos11: pop dx 
            mov dh, 0x07 
            mov [es:di], dx 
            add di, 2 
            loop nextpos11 
            pop di
            pop dx
            pop cx
            pop bx
            pop ax
            pop es
            pop bp
            ret 4

;-----------------------------------------------------------------------------------------
getmouse1:
		pusha
			call sleep
			call sleep
			call sleep
			call sleep
		waitForMouseClick:
					mov ax, 0001h 			;to show mouse
					int 33h
					mov ax,0003h
					int 33h
					or bx,bx
					jz short waitForMouseClick
					mov ax, 0002h 			;hide mouse after clicking
					int 33h
					
					mov si,dx                    
					mov dx,0
					mov ax,cx
					mov bx,8
					div bx                         ;dividing by 8 to convert it into row column format.

					mov [mousex],ax
					
					mov ax,si
					mov dx,0
					div bx                         ;dividing by 8 to convert it into row column format.  

					mov [mousey],ax
		popa
	ret
;-----------------------------------------------------------------------------------------
getmouse2:
		pusha
		call sleep
		call sleep
		call sleep
			waitForMouseClick2:
					mov ax, 0001h 			;to show mouse
					int 33h
					mov ax,0003h
					int 33h
					or bx,bx
					jz short waitForMouseClick2
					mov ax, 0002h 			;hide mouse after clicking
					int 33h
					
					mov si,dx                    
					mov dx,0
					mov ax,cx
					mov bx,8
					div bx                         ;dividing by 8 to convert it into row column format.

					mov [mousex1],ax
					
					mov ax,si
					mov dx,0
					div bx                         ;dividing by 8 to convert it into row column format.
    
					mov [mousey1],ax
			popa
		ret
;-----------------------------------------------------------------------------------------
sleep:
	pusha
	mov cx,0xffff
	delay:
		sub cx,1
		cmp cx,0
		jne delay
	popa
	ret
;-----------------------------------------------------------------------------------------
calcmouse1:
		mov al,80
		mul byte[mousey]
		add ax,[mousex]
		
		shl ax,1
		mov [loc1],ax
	ret

calcmouse2:
		mov al,80
		mul byte[mousey1]
		add ax,[mousex1]
		
		shl ax,1
		mov [loc2],ax
	ret
;-----------------------------------------------------------------------------------------
getvalfromscr:
		push bp
		mov bp,sp
	pusha

		mov ax, 0xb800 
 		mov es, ax

		mov ax,[bp+4]
		
		mov di,ax

		mov ax,[es:di]
		mov [es:di],ax

		cmp al,41h
		jb endselect
		cmp al,48h
		ja endselect
		
		mov bx,[bp+6]
		mov [bx],ax
		mov byte[mousevalflag],1

		endselect:
	popa
	pop bp
	
ret 4
;-----------------------------------------------------------------------------------------
resetremmoveloc:
				mov ax,0xb800
				mov es,ax
				mov di,0x150D
				ret
;-----------------------------------------------------------------------------------------

selectcell:
		mov ax, 0xb800 
 		mov es, ax

		mov ax,[loc1]
		
		mov di,ax

		mov ax,[es:di]
		mov ah,0x49
		mov [es:di],ax
ret 
;-----------------------------------------------------------------------------------------
unselectcell:
		mov ax, 0xb800 
 		mov es, ax

		mov ax,[loc1]
		
		mov di,ax
		mov ax,[swapword1]
		mov [es:di],ax
ret 
;-----------------------------------------------------------------------------------------
putvalonscr:
		push bp
		mov bp,sp
	pusha
		mov ax,0xb800; 
		mov es,ax;
		
		mov di,[loc2]
		mov ax,[swapword1]
		mov [es:di],ax
		
		mov di,[loc1]
		mov ax,[swapword2]
		mov [es:di],ax

	popa
		pop bp
ret
;-----------------------------------------------------------------------------------------
;Variables 

;Titles
welcome :db 'Welcome to Character Match Game'
input: db 'Input Menu'

nametitle : db 'Name: '
nametitlesize : db 6

namemsg :db 'Enter your name: '
namemsgsize: db 17

boardmsg :db 'Enter Board Size in Hex (4 < Size < 13): '
boardmsgsize: db 41

scoretitle : db 'Score : '
scoretitlesize : db 8

totalmovetitle : db 'Total Move : '
totalmovetitlesize : db 13

remmovetitle : db 'Remaining Move : '
remmovetitlesize : db 17

invalidinp: db 'Invalid Input.Press any key to terminate.  '
invalidinpsize: db 43

concluding: db 'Game Over. Your Final Score is '
concludingsize: db 31

concludingend: db 'Game Made With Love and Late Night Hardwork By Saad and M Talha'
concludingendsize: db 63

hline: db 95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95
vline: db 95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95

;In Use Game Variables

name : db '                                                                ';Spaces 64 Left Due to MisCharacters(Clashes of Memory Cells) 
nullspace : dw '    ' ;1Bytes in Case More Than 64 Characters 
namesize : db 0

boardsize : dw 0

score : dw 0

remmove : dw 15

totalmove : dw 15

randomNum: db 0

mousex  : dw 0  
mousey  : dw 0  
mousex1  : dw 0  
mousey1 : dw 0 
mousevalflag : db 0
loc1: dw 0
loc2: dw 0

swapword1 : dw ' ',0
swapword2 : dw ' ',0

blocker_flag: db 0
