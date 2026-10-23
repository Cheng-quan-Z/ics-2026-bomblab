0000000000402020 <p1_step0>:
  402020:	endbr64
  402024:	lea    eax,[rdi+rdi*4]
  402027:	add    esi,0xd209
  40202d:	xor    eax,esi
  40202f:	ret

0000000000402030 <p1_step1>:
  402030:	endbr64
  402034:	sub    edi,esi
  402036:	lea    eax,[rdi+rdi*4+0xef90]
  40203d:	ret
  40203e:	xchg   ax,ax

0000000000402040 <p1_step2>:
  402040:	endbr64
  402044:	lea    eax,[rsi+0x510d]
  40204a:	xor    eax,edi
  40204c:	ret
  40204d:	nop    DWORD PTR [rax]

0000000000402050 <p1_compute>:
  402050:	endbr64
  402054:	push   rbp
  402055:	mov    rax,rdi
  402058:	mov    rdx,rdi
  40205b:	mov    r8d,edi
  40205e:	shr    rax,0x20
  402062:	shr    rdx,0x10
  402066:	mov    r9d,eax
  402069:	mov    esi,eax
  40206b:	mov    rbp,rsp
  40206e:	call   402020 <p1_step0>
  402073:	mov    rsi,rdx
  402076:	mov    edi,r9d
  402079:	mov    ecx,eax
  40207b:	call   402030 <p1_step1>
  402080:	mov    esi,r8d
  402083:	mov    edi,eax
  402085:	call   402040 <p1_step2>
  40208a:	pop    rbp
  40208b:	xor    eax,ecx
  40208d:	ret
  40208e:	xchg   ax,ax

0000000000402090 <phase_01>:
  402090:	endbr64
  402094:	push   rbp
  402095:	mov    rbp,rsp
  402098:	push   r12
  40209a:	mov    r12,rsi
  40209d:	mov    esi,0x1
  4020a2:	push   rbx
  4020a3:	mov    rbx,rdi
  4020a6:	sub    rsp,0x10
  4020aa:	call   402c40 <valid_u32_fields>
  4020af:	test   al,al
  4020b1:	jne    4020c0 <phase_01+0x30>
  4020b3:	add    rsp,0x10
  4020b7:	xor    eax,eax
  4020b9:	pop    rbx
  4020ba:	pop    r12
  4020bc:	pop    rbp
  4020bd:	ret
  4020be:	xchg   ax,ax
  4020c0:	xor    eax,eax
  4020c2:	lea    rdx,[rbp-0x14]
  4020c6:	mov    esi,0x403189
  4020cb:	mov    rdi,rbx
  4020ce:	call   4011e0 <__isoc99_sscanf@plt>
  4020d3:	cmp    eax,0x1
  4020d6:	jne    4020b3 <phase_01+0x23>
  4020d8:	mov    rdi,r12
  4020db:	call   402050 <p1_compute>
  4020e0:	cmp    DWORD PTR [rbp-0x14],eax
  4020e3:	sete   al
  4020e6:	add    rsp,0x10
  4020ea:	pop    rbx
  4020eb:	pop    r12
  4020ed:	pop    rbp
  4020ee:	ret
  4020ef:	nop

00000000004020f0 <phase_02>:
