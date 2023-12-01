.section .text
  .set length, 1048576
  .global main

.macro next label
    inc %r8
    cmp %rbp, %r8
    jne \label
    mov %rsi, %r8
    xor %eax, %eax
    syscall
    test %eax, %eax
    jz close
    mov %rsi, %rbp
    add %rax, %rbp
  \label:
.endm

main:
  push %rbx

#rax - 0 (read syscall)
#rdi - 0 (stdin)
#rsi - * (buffer[255])
#rdx - d (size of buffer)
read:
  xor %eax, %eax
  xor %edi, %edi
  lea -length(%rsp), %rsi
  mov $length, %rdx
  syscall

#rdi - * (buffer[0])
#rsi - * (buffer[size-1])
#remove newline
 mov %rsi, %rdi
 add %rax, %rsi
 dec %rsi
 movb $0, (%rsi)

#rax - 2 (open)
#rdi - * (buffer[0])
#rsi - 0 (O_RDONLY)
open:
  mov $2, %rax
  xor %esi, %esi
  syscall

#rax - 0 (read)
#rdi - fd (got from open)
#rsi - * (buffer[0])
#rdx - d (size of buffer)
readfile:
  mov %rdi, %rsi
  mov %rax, %rdi
  xor %eax, %eax
  mov $length, %rdx
  syscall

  mov %rsi, %rbp
  add $length, %rbp

#-----------------------------------------------------------------------------

#r9 - first half
#r10 - second half
#r 12-13,14-15

xor %r9d, %r9d
xor %r10d, %r10d
mov %rsi, %r8

loop:
  xor %r12d, %r12d
  xor %r13d, %r13d
  xor %r14d, %r14d
  xor %r15d, %r15d
  mov (%r8), %r12b
  next a
  cmpb $'-', (%r8)
  je firstpause
  sub $'0', %r12
  imul $10, %r12, %r12
  add (%r8), %r12b
  next b

firstpause:
  next c
  mov (%r8), %r13b
  next d
  cmpb $',', (%r8)
  je comma 
  sub $'0', %r13
  imul $10, %r13, %r13
  add (%r8), %r13b
  next e

comma:
  next f
  mov (%r8), %r14b
  next g
  cmpb $'-', (%r8)
  je secondpause
  sub $'0', %r14
  imul $10, %r14, %r14
  add (%r8), %r14b
  next h

secondpause:
  next i
  mov (%r8), %r15b
  next j
  cmpb $'\n', (%r8)
  je newline 
  sub $'0', %r15
  imul $10, %r15, %r15
  add (%r8), %r15b
  next k

newline:
  cmp %r13, %r14
  jg check
  cmp %r12, %r15
  jl check
  inc %r10
  cmp %r12, %r14
  jl or
  cmp %r13, %r15
  jg or
  inc %r9
  jmp check

or:
  cmp %r14, %r12
  jl check 
  cmp %r15, %r13
  jg check
  inc %r9

check:
  next l
  cmpb $0, (%r8)
  jne loop

#-------------------------------------------------------------------------------

#rax - 3 (close)
#rdi - fd
close:
  mov $3, %rax
  syscall

#-------------------------------------------------------------------------------

#r10 - number
#r8 - pointer
#r12 - temp
#r13 - temp
#r14 - const

  movl $3435973837, %r14d
  mov %rsi, %r8

itoa_second:
  cmp $9, %r10
  jle last_second
  mov %r10, %r13 #r13 = r9
  imul %r14, %r10
  shrq $35, %r10 #r9 = n/10
  lea (%r10,%r10,4), %r12
  add %r12, %r12 #r12 = n/10*10
  sub %r12, %r13 #r13 = r13-r12   (n-n/10*10)
  add $'0', %r13
  movb %r13b, (%r8)
  inc %r8
  jmp itoa_second

last_second:
  add $'0', %r10
  movb %r10b, (%r8)
  inc %r8

  movb $' ', (%r8)
  inc %r8

#r9 - number
#r8 - pointer
#r12 - temp
#r13 - temp
#r14 - const

itoa_first:
  cmp $9, %r9
  jle last_first
  mov %r9, %r13 #r13 = r9
  imul %r14, %r9
  shrq $35, %r9 #r9 = n/10
  lea (%r9,%r9,4), %r12
  add %r12, %r12 #r12 = n/10*10
  sub %r12, %r13 #r13 = r13-r12   (n-n/10*10)
  add $'0', %r13
  movb %r13b, (%r8)
  inc %r8
  jmp itoa_first

last_first:
  add $'0', %r9
  movb %r9b, (%r8)

#-------------------------------------------------------------------------------

  mov %r8, %rdx

  mov %rsi, %r10
  xor %r9d, %r9d
  xor %r12d, %r12d
reverse:
  movb (%r10), %r12b
  movb (%r8), %r9b
  movb %r12b, (%r8)
  movb %r9b, (%r10)
  inc %r10
  dec %r8
  cmp %r10, %r8
  jne reverse

  inc %rdx
  movb $'\n', (%rdx)
  inc %rdx
  movb $0, (%rdx)
  sub %rsi, %rdx

#rax - 1 (write)
#rdi - 1 (stdout)
#rsi - * (buffer[0])
#rdx - d (size of string)
write:
  mov $1, %rax
  mov $1, %rdi
  syscall

  pop %rbx
  mov $0, %rax
  ret
