// armips patch to make yoshi's story ique work in pj64

.n64
.open "ys-ique.z64", "ys-ique-emumod.z64", 0

.headersize 0x7FFFF400

.org 0x8007A574 :: nop // remove permanent loop
.org 0x8008C298 :: nop // remove invalid register access (A430003C)
.org 0x8008C2A0 :: nop // remove invalid register access (A430003C)
.org 0x8008C2B4 :: nop // remove invalid register access (A430003C)
.org 0x8008C2BC :: nop // remove invalid register access (A430003C)

.close