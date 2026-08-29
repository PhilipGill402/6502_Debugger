    lda $42 ; load into accumulator value at 0x42
    tax
    inx
    sta $42 ; write new value back to 0x42 
    brk
