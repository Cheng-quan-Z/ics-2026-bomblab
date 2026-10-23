0000000000401470 <tutorial_mix>:
  401470:	endbr64
  401474:	lea    eax,[rdi+rdi*2+0x7]
  401478:	ret
  401479:	nop    DWORD PTR [rax+0x0]

0000000000401480 <phase_00>:
  401480:	endbr64
  401484:	push   rbp
  401485:	mov    rbp,rsp
  401488:	push   r14
  40148a:	push   rbx
  40148b:	mov    rbx,rdi
  40148e:	sub    rsp,0x10
  401492:	mov    r14,QWORD PTR fs:0x28
  40149b:	mov    QWORD PTR [rbp-0x18],r14
  40149f:	mov    r14,rsi
  4014a2:	mov    esi,0x2
  4014a7:	call   401540 <valid_u32_fields>
  4014ac:	test   al,al
  4014ae:	jne    4014d0 <phase_00+0x50>
  4014b0:	xor    eax,eax
  4014b2:	mov    rdx,QWORD PTR [rbp-0x18]
  4014b6:	sub    rdx,QWORD PTR fs:0x28
  4014bf:	jne    40150c <phase_00+0x8c>
  4014c1:	add    rsp,0x10
  4014c5:	pop    rbx
  4014c6:	pop    r14
  4014c8:	pop    rbp
  4014c9:	ret
  4014ca:	nop    WORD PTR [rax+rax*1+0x0]
  4014d0:	xor    eax,eax
  4014d2:	lea    rdx,[rbp-0x20]
  4014d6:	lea    rcx,[rbp-0x1c]
  4014da:	mov    esi,0x402041
  4014df:	mov    rdi,rbx
  4014e2:	call   401150 <__isoc99_sscanf@plt>
  4014e7:	cmp    eax,0x2
  4014ea:	jne    4014b0 <phase_00+0x30>
  4014ec:	mov    rdi,r14
  4014ef:	shr    rdi,0x5
  4014f3:	movzx  edi,dil
  4014f7:	xor    edi,0x2a
  4014fa:	cmp    DWORD PTR [rbp-0x20],edi
  4014fd:	jne    4014b0 <phase_00+0x30>
  4014ff:	call   401470 <tutorial_mix>
  401504:	cmp    DWORD PTR [rbp-0x1c],eax
  401507:	sete   al
  40150a:	jmp    4014b2 <phase_00+0x32>
  40150c:	call   401120 <__stack_chk_fail@plt>
  401511:	cs nop WORD PTR [rax+rax*1+0x0]
  40151b:	cs nop WORD PTR [rax+rax*1+0x0]
  401525:	cs nop WORD PTR [rax+rax*1+0x0]
  40152f:	cs nop WORD PTR [rax+rax*1+0x0]
  401539:	nop    DWORD PTR [rax+0x0]

