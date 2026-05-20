global f1
global f2
global f3
global df1
global df2
global df3

section .data
    ; Коэффициенты функции f1(x)
    c_035      dq 0.35
    c_095      dq 0.95
    c_27       dq 2.7

    ; Коэффициенты функции f2(x)
    c_3        dq 3.0
    c_1        dq 1.0

    ; Константа 2 для функции f3(x)
    c_2        dq 2.0

    ; Коэффициенты производной f1'(x)
    c_07       dq 0.7

    ; Константа -1 для производной f3'(x)
    c_minus_1  dq -1.0

section .text

; double f1(double x)
; f1(x) = 0.35*x^2 - 0.95*x + 2.7
f1:
    push ebp
    mov  ebp, esp

    fld  qword [ebp + 8]     ; st0 = x
    fmul st0, st0            ; st0 = x^2
    fld  qword [c_035]       ; st0 = 0.35, st1 = x^2
    fmulp st1, st0           ; st0 = 0.35*x^2

    fld  qword [ebp + 8]     ; st0 = x, st1 = 0.35*x^2
    fld  qword [c_095]       ; st0 = 0.95, st1 = x, st2 = 0.35*x^2
    fmulp st1, st0           ; st0 = 0.95*x, st1 = 0.35*x^2
    fsubp st1, st0           ; st0 = 0.35*x^2 - 0.95*x

    fld  qword [c_27]        ; st0 = 2.7, st1 = previous
    faddp st1, st0           ; st0 = 0.35*x^2 - 0.95*x + 2.7

    pop  ebp
    ret

; double f2(double x)
; f2(x) = 3*x + 1
f2:
    push ebp
    mov  ebp, esp

    fld  qword [ebp + 8]     ; st0 = x
    fld  qword [c_3]         ; st0 = 3, st1 = x
    fmulp st1, st0           ; st0 = 3*x
    fld  qword [c_1]         ; st0 = 1, st1 = 3*x
    faddp st1, st0           ; st0 = 3*x + 1

    pop  ebp
    ret

; double f3(double x)
; f3(x) = 1 / (x + 2)
f3:
    push ebp
    mov  ebp, esp

    fld  qword [ebp + 8]     ; st0 = x
    fld  qword [c_2]         ; st0 = 2, st1 = x
    faddp st1, st0           ; st0 = x + 2
    fld1                     ; st0 = 1, st1 = x + 2
    fdivrp st1, st0          ; st0 = 1 / (x + 2)

    pop  ebp
    ret

; double df1(double x)
; f1'(x) = 0.7*x - 0.95
df1:
    push ebp
    mov  ebp, esp

    fld  qword [ebp + 8]     ; st0 = x
    fld  qword [c_07]        ; st0 = 0.7, st1 = x
    fmulp st1, st0           ; st0 = 0.7*x
    fld  qword [c_095]       ; st0 = 0.95, st1 = 0.7*x
    fsubp st1, st0           ; st0 = 0.7*x - 0.95

    pop  ebp
    ret

; double df2(double x)
; f2'(x) = 3
df2:
    push ebp
    mov  ebp, esp

    fld  qword [c_3]         ; st0 = 3

    pop  ebp
    ret

; double df3(double x)
; f3'(x) = -1 / (x + 2)^2
df3:
    push ebp
    mov  ebp, esp

    fld  qword [ebp + 8]     ; st0 = x
    fld  qword [c_2]         ; st0 = 2, st1 = x
    faddp st1, st0           ; st0 = x + 2
    fmul st0, st0            ; st0 = (x + 2)^2
    fld  qword [c_minus_1]   ; st0 = -1, st1 = (x + 2)^2
    fdivrp st1, st0          ; st0 = -1 / (x + 2)^2

    pop  ebp
    ret
