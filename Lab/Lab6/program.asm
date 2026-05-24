MOV O, 1
increase:
    ADD O, 1
    CMP O, 5
JO increase
decrease:
    SUB O, 1
    CMP O, 0
JZ increase
JMP decrease