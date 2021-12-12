[bits 64]

;=============================
;This Code is from KeepKonect.
;HUGE thx to him
;=============================

GLOBAL LoadTSS

LoadTSS:
    ltr di
    ret