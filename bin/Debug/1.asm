;r0=i
;r1=cin
;r2=addr
:main
	:loop
		iread r1
		imul r2, r0, 4
		imov [r2], r1
		iadd r0, r0, 1
		icmp r0, 1024
		ijle :loop
	:end_loop
	cwrite 10
	ihalt

