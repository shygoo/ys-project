.macro place_object, id, layer, x, y
    .dh id
    .dh layer
    .float x
    .float y
.endmacro

.definelabel R_32, 2
.definelabel R_26, 4
.definelabel R_HI16, 5
.definelabel R_HI16, 6

.definelabel SEC_UNK, 0
.definelabel SEC_TEXT, 1
.definelabel SEC_DATA, 2
.definelabel SEC_RODATA, 3 

.macro ovl_rel, section, reltype, offset
    .dw ((section & 3) << 30) | ((reltype & 0xF) << 16) | (offset & 0xFFFFFF)
.endmacro