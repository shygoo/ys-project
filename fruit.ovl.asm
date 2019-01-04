// text:
/*0x80573E90*/ lui       t6, 0x8057
/*0x80573E94*/ lw        t6, 0x4CE0(t6)
/*0x80573E98*/ addiu     sp, sp, 0xFFE8
/*0x80573E9C*/ sw        ra, 0x0014(sp)
/*0x80573EA0*/ bne       t6, r0, 0x80573EF4
/*0x80573EA4*/ sw        a0, 0x0018(sp)
/*0x80573EA8*/ lui       a0, 0x8057
/*0x80573EAC*/ lui       a1, 0x8057
/*0x80573EB0*/ addiu     a1, a1, 0x4F40
/*0x80573EB4*/ addiu     a0, a0, 0x4F30
/*0x80573EB8*/ jal       0x8004667C
/*0x80573EBC*/ addiu     a2, r0, 0x001E
/*0x80573EC0*/ lui       a0, 0x8010
/*0x80573EC4*/ lui       a2, 0x8057
/*0x80573EC8*/ addiu     a2, a2, 0x4B44
/*0x80573ECC*/ lw        a0, 0x8908(a0)
/*0x80573ED0*/ jal       0x80057B28
/*0x80573ED4*/ addiu     a1, r0, 0x0015
/*0x80573ED8*/ addiu     t7, r0, 0x0001
/*0x80573EDC*/ lui       at, 0x8057
/*0x80573EE0*/ sw        t7, 0x4CE0(at)
/*0x80573EE4*/ lui       at, 0x8010
/*0x80573EE8*/ sw        r0, 0x8ACC(at)
/*0x80573EEC*/ lui       at, 0x8010
/*0x80573EF0*/ sw        r0, 0x8AD0(at)
/*0x80573EF4*/ lw        ra, 0x0014(sp)
/*0x80573EF8*/ lui       v0, 0x8057
/*0x80573EFC*/ addiu     v0, v0, 0x42A4
/*0x80573F00*/ jr        ra
/*0x80573F04*/ addiu     sp, sp, 0x0018
/*0x80573F08*/ lui       t6, 0x8010
/*0x80573F0C*/ lw        t6, 0x89D4(t6)
/*0x80573F10*/ lui       v1, 0x800F
/*0x80573F14*/ addiu     v1, v1, 0x7EA4
/*0x80573F18*/ beq       a0, t6, 0x80573F28
/*0x80573F1C*/ lui       v0, 0x800F
/*0x80573F20*/ jr        ra
/*0x80573F24*/ or        v0, r0, r0
/*0x80573F28*/ addiu     v0, v0, 0x7F14
/*0x80573F2C*/ lw        t7, 0x0B34(v1)
/*0x80573F30*/ beql      a0, t7, 0x80573F44
/*0x80573F34*/ lw        t9, 0x0B38(v1)
/*0x80573F38*/ jr        ra
/*0x80573F3C*/ or        v0, r0, r0
/*0x80573F40*/ lw        t9, 0x0B38(v1)
/*0x80573F44*/ beql      a0, t9, 0x80573F58
/*0x80573F48*/ lw        t9, 0x0B3C(v1)
/*0x80573F4C*/ jr        ra
/*0x80573F50*/ or        v0, r0, r0
/*0x80573F54*/ lw        t9, 0x0B3C(v1)
/*0x80573F58*/ beql      a0, t9, 0x80573F6C
/*0x80573F5C*/ lw        t0, 0x0B40(v1)
/*0x80573F60*/ jr        ra
/*0x80573F64*/ or        v0, r0, r0
/*0x80573F68*/ lw        t0, 0x0B40(v1)
/*0x80573F6C*/ addiu     v1, v1, 0x0010
/*0x80573F70*/ beq       a0, t0, 0x80573F80
/*0x80573F74*/ nop
/*0x80573F78*/ jr        ra
/*0x80573F7C*/ or        v0, r0, r0
/*0x80573F80*/ bnel      v1, v0, 0x80573F30
/*0x80573F84*/ lw        t7, 0x0B34(v1)
/*0x80573F88*/ addiu     v0, r0, 0x0001
/*0x80573F8C*/ jr        ra
/*0x80573F90*/ nop
/*0x80573F94*/ addiu     sp, sp, 0xFFE8
/*0x80573F98*/ sw        ra, 0x0014(sp)
/*0x80573F9C*/ lhu       v0, 0x000C(a0)
/*0x80573FA0*/ lui       a2, 0x800F
/*0x80573FA4*/ addiu     a2, a2, 0x7EA0
/*0x80573FA8*/ addiu     at, r0, 0x4035
/*0x80573FAC*/ beq       v0, at, 0x80574050
/*0x80573FB0*/ lw        a1, 0x0B30(a2)
/*0x80573FB4*/ addiu     at, r0, 0x468C
/*0x80573FB8*/ beq       v0, at, 0x80574050
/*0x80573FBC*/ sll       t6, a1, 2
/*0x80573FC0*/ addiu     at, r0, 0x45BC
/*0x80573FC4*/ beq       v0, at, 0x80573FE0
/*0x80573FC8*/ addiu     a0, v0, 0xBFD0
/*0x80573FCC*/ addiu     at, r0, 0x45BF
/*0x80573FD0*/ beq       v0, at, 0x80573FE0
/*0x80573FD4*/ addiu     at, r0, 0x45F3
/*0x80573FD8*/ bnel      v0, at, 0x80573FE8
/*0x80573FDC*/ addu      t7, a2, t6
/*0x80573FE0*/ addiu     a0, r0, 0x0004
/*0x80573FE4*/ addu      t7, a2, t6
/*0x80573FE8*/ sll       t9, a1, 1
/*0x80573FEC*/ lui       at, 0x8010
/*0x80573FF0*/ sw        a0, 0x0B34(t7)
/*0x80573FF4*/ addu      at, at, t9
/*0x80573FF8*/ sh        a0, 0x8AD4(at)
/*0x80573FFC*/ addiu     a1, a1, 0x0001
/*0x80574000*/ slti      at, a1, 0x001E
/*0x80574004*/ bnel      at, r0, 0x80574050
/*0x80574008*/ sw        a1, 0x0B30(a2)
/*0x8057400C*/ lw        t9, 0x0C28(a2)
/*0x80574010*/ bnel      t9, r0, 0x80574044
/*0x80574014*/ addiu     t0, r0, 0x0001
/*0x80574018*/ jal       0x80573F08
/*0x8057401C*/ nop
/*0x80574020*/ lui       a2, 0x800F
/*0x80574024*/ beq       v0, r0, 0x80574040
/*0x80574028*/ addiu     a2, a2, 0x7EA0
/*0x8057402C*/ addiu     a0, r0, 0x00D9
/*0x80574030*/ jal       0x80067818
/*0x80574034*/ or        a1, r0, r0
/*0x80574038*/ lui       a2, 0x800F
/*0x8057403C*/ addiu     a2, a2, 0x7EA0
/*0x80574040*/ addiu     t0, r0, 0x0001
/*0x80574044*/ addiu     a1, r0, 0x001E
/*0x80574048*/ sw        t0, 0x0C28(a2)
/*0x8057404C*/ sw        a1, 0x0B30(a2)
/*0x80574050*/ lw        ra, 0x0014(sp)
/*0x80574054*/ addiu     sp, sp, 0x0018
/*0x80574058*/ jr        ra
/*0x8057405C*/ nop
/*0x80574060*/ lui       v1, 0x800F
/*0x80574064*/ addiu     v1, v1, 0x7EA0
/*0x80574068*/ lw        t6, 0x03EC(v1)
/*0x8057406C*/ addiu     sp, sp, 0xFFE0
/*0x80574070*/ sw        a1, 0x0024(sp)
/*0x80574074*/ andi      a1, a1, 0x00FF
/*0x80574078*/ addiu     at, r0, 0x0066
/*0x8057407C*/ addu      t7, v1, t6
/*0x80574080*/ sw        ra, 0x0014(sp)
/*0x80574084*/ bne       a1, at, 0x805740A0
/*0x80574088*/ lbu       v0, 0x0598(t7)
/*0x8057408C*/ jal       0x80573F94
/*0x80574090*/ sw        v0, 0x0018(sp)
/*0x80574094*/ lui       v1, 0x800F
/*0x80574098*/ addiu     v1, v1, 0x7EA0
/*0x8057409C*/ lw        v0, 0x0018(sp)
/*0x805740A0*/ addiu     at, r0, 0x004E
/*0x805740A4*/ beq       v0, at, 0x80574144
/*0x805740A8*/ slti      at, v0, 0x00A2
/*0x805740AC*/ bne       at, r0, 0x805740BC
/*0x805740B0*/ slti      at, v0, 0x00A6
/*0x805740B4*/ bnel      at, r0, 0x80574148
/*0x805740B8*/ lw        ra, 0x0014(sp)
/*0x805740BC*/ lw        a0, 0x0B30(v1)
/*0x805740C0*/ jal       0x800495AC
/*0x805740C4*/ sw        a0, 0x001C(sp)
/*0x805740C8*/ lw        a0, 0x001C(sp)
/*0x805740CC*/ slti      at, a0, 0x001E
/*0x805740D0*/ bnel      at, r0, 0x80574148
/*0x805740D4*/ lw        ra, 0x0014(sp)
/*0x805740D8*/ jal       0x8004700C
/*0x805740DC*/ nop
/*0x805740E0*/ beq       v0, r0, 0x80574144
/*0x805740E4*/ or        a0, v0, r0
/*0x805740E8*/ lui       t9, 0x8010
/*0x805740EC*/ lw        t9, 0x8454(t9)
/*0x805740F0*/ addiu     t9, t9, 0xFFF7
/*0x805740F4*/ sltiu     at, t9, 0x0010
/*0x805740F8*/ beq       at, r0, 0x8057412C
/*0x805740FC*/ sll       t9, t9, 2
/*0x80574100*/ lui       at, 0x8057
/*0x80574104*/ addu      at, at, t9
/*0x80574108*/ lw        t9, 0x4D30(at)
/*0x8057410C*/ jr        t9
/*0x80574110*/ nop
/*0x80574114*/ or        a1, r0, r0
/*0x80574118*/ addiu     a2, r0, 0x0000
/*0x8057411C*/ jal       0x8002F7AC
/*0x80574120*/ addiu     a3, r0, 0x000B
/*0x80574124*/ beq       r0, r0, 0x8057413C
/*0x80574128*/ nop
/*0x8057412C*/ or        a1, r0, r0
/*0x80574130*/ addiu     a2, r0, 0x0000
/*0x80574134*/ jal       0x8002F7AC
/*0x80574138*/ addiu     a3, r0, 0x000A
/*0x8057413C*/ lui       at, 0x800F
/*0x80574140*/ sb        r0, 0x7EA6(at)
/*0x80574144*/ lw        ra, 0x0014(sp)
/*0x80574148*/ addiu     sp, sp, 0x0020
/*0x8057414C*/ jr        ra
/*0x80574150*/ nop
/*0x80574154*/ lui       at, 0x40C0
/*0x80574158*/ mtc1      at, f4
/*0x8057415C*/ addiu     t6, r0, 0x0007
/*0x80574160*/ addiu     t7, r0, 0x0001
/*0x80574164*/ swc1      f4, 0x001C(a1)
/*0x80574168*/ sh        t6, 0x0144(a0)
/*0x8057416C*/ sb        t7, 0x0165(a0)
/*0x80574170*/ jr        ra
/*0x80574174*/ addiu     v0, r0, 0x0004
/*0x80574178*/ lui       at, 0x40C0
/*0x8057417C*/ mtc1      at, f4
/*0x80574180*/ addiu     t6, r0, 0x0001
/*0x80574184*/ addiu     at, r0, 0x468C
/*0x80574188*/ swc1      f4, 0x001C(a1)
/*0x8057418C*/ lhu       t7, 0x000C(a0)
/*0x80574190*/ sb        t6, 0x0165(a0)
/*0x80574194*/ addiu     t9, r0, 0x0008
/*0x80574198*/ bne       t7, at, 0x805741AC
/*0x8057419C*/ addiu     t9, r0, 0x0007
/*0x805741A0*/ sh        t9, 0x0144(a0)
/*0x805741A4*/ jr        ra
/*0x805741A8*/ addiu     v0, r0, 0x0005
/*0x805741AC*/ sh        t9, 0x0144(a0)
/*0x805741B0*/ jr        ra
/*0x805741B4*/ addiu     v0, r0, 0x0005
/*0x805741B8*/ addiu     sp, sp, 0xFFE8
/*0x805741BC*/ sw        ra, 0x0014(sp)
/*0x805741C0*/ lw        v0, 0x000C(a0)
/*0x805741C4*/ lhu       t6, 0x000C(a0)
/*0x805741C8*/ andi      v0, v0, 0x03FF
/*0x805741CC*/ andi      v1, v0, 0xFFFF
/*0x805741D0*/ slti      at, v1, 0x0200
/*0x805741D4*/ addiu     t7, t6, 0xBFD3
/*0x805741D8*/ beq       at, r0, 0x805741FC
/*0x805741DC*/ sh        t7, 0x0144(a0)
/*0x805741E0*/ lw        t9, 0x0174(a0)
/*0x805741E4*/ addiu     t9, r0, 0x0001
/*0x805741E8*/ lw        t0, 0x0000(t9)
/*0x805741EC*/ jal       0x8005FCA8
/*0x805741F0*/ sh        t9, 0x0012(t0)
/*0x805741F4*/ beq       r0, r0, 0x80574270
/*0x805741F8*/ addiu     v0, r0, 0x0001
/*0x805741FC*/ lw        t1, 0x0180(a0)
/*0x80574200*/ slti      at, v1, 0x0232
/*0x80574204*/ beq       t1, r0, 0x80574244
/*0x80574208*/ nop
/*0x8057420C*/ lui       at, 0x40C0
/*0x80574210*/ mtc1      at, f4
/*0x80574214*/ slti      at, v1, 0x0232
/*0x80574218*/ bne       at, r0, 0x8057423C
/*0x8057421C*/ swc1      f4, 0x001C(a1)
/*0x80574220*/ lw        t3, 0x0174(a0)
/*0x80574224*/ addiu     t2, r0, 0x0001
/*0x80574228*/ lw        t4, 0x0000(t3)
/*0x8057422C*/ jal       0x8005FCA8
/*0x80574230*/ sh        t2, 0x0012(t4)
/*0x80574234*/ beq       r0, r0, 0x80574270
/*0x80574238*/ addiu     v0, r0, 0x0003
/*0x8057423C*/ beq       r0, r0, 0x80574270
/*0x80574240*/ addiu     v0, r0, 0x0002
/*0x80574244*/ beq       at, r0, 0x80574258
/*0x80574248*/ lui       at, 0x40C0
/*0x8057424C*/ mtc1      at, f6
/*0x80574250*/ nop
/*0x80574254*/ swc1      f6, 0x001C(a1)
/*0x80574258*/ lw        t6, 0x0174(a0)
/*0x8057425C*/ addiu     t5, r0, 0x0001
/*0x80574260*/ lw        t7, 0x0000(t6)
/*0x80574264*/ jal       0x8005FCA8
/*0x80574268*/ sh        t5, 0x0012(t7)
/*0x8057426C*/ addiu     v0, r0, 0x0001
/*0x80574270*/ lw        ra, 0x0014(sp)
/*0x80574274*/ addiu     sp, sp, 0x0018
/*0x80574278*/ jr        ra
/*0x8057427C*/ nop
/*0x80574280*/ lui       at, 0x40C0
/*0x80574284*/ mtc1      at, f4
/*0x80574288*/ addiu     t6, r0, 0x0007
/*0x8057428C*/ addiu     t7, r0, 0x0001
/*0x80574290*/ swc1      f4, 0x001C(a1)
/*0x80574294*/ sh        t6, 0x0144(a0)
/*0x80574298*/ sb        t7, 0x0165(a0)
/*0x8057429C*/ jr        ra
/*0x805742A0*/ addiu     v0, r0, 0x0006
/*0x805742A4*/ addiu     sp, sp, 0xFFE0
/*0x805742A8*/ sw        ra, 0x001C(sp)
/*0x805742AC*/ sw        s0, 0x0018(sp)
/*0x805742B0*/ lw        t7, 0x016C(a0)
/*0x805742B4*/ lui       t6, 0x8057
/*0x805742B8*/ sb        r0, 0x0165(a0)
/*0x805742BC*/ addiu     t6, t6, 0x4CE4
/*0x805742C0*/ sw        t6, 0x0000(t7)
/*0x805742C4*/ lui       at, 0x3F00
/*0x805742C8*/ mtc1      at, f2
/*0x805742CC*/ mtc1      r0, f0
/*0x805742D0*/ lhu       v0, 0x000C(a0)
/*0x805742D4*/ lui       t9, 0x8005
/*0x805742D8*/ addiu     t9, r0, 0x00FF
/*0x805742DC*/ addiu     t9, t9, 0x83B8
/*0x805742E0*/ addiu     at, r0, 0x45BC
/*0x805742E4*/ or        s0, a0, r0
/*0x805742E8*/ sw        r0, 0x01E0(a0)
/*0x805742EC*/ sw        t9, 0x0124(a0)
/*0x805742F0*/ sw        t9, 0x0130(a0)
/*0x805742F4*/ swc1      f2, 0x00E8(a0)
/*0x805742F8*/ swc1      f2, 0x00EC(a0)
/*0x805742FC*/ swc1      f0, 0x00DC(a0)
/*0x80574300*/ swc1      f0, 0x00E0(a0)
/*0x80574304*/ beq       v0, at, 0x80574338
/*0x80574308*/ swc1      f0, 0x00F8(a0)
/*0x8057430C*/ addiu     at, r0, 0x45BF
/*0x80574310*/ beq       v0, at, 0x8057434C
/*0x80574314*/ or        a0, s0, r0
/*0x80574318*/ addiu     at, r0, 0x45F3
/*0x8057431C*/ beq       v0, at, 0x8057435C
/*0x80574320*/ addiu     a1, s0, 0x00C4
/*0x80574324*/ addiu     at, r0, 0x468C
/*0x80574328*/ beq       v0, at, 0x8057434C
/*0x8057432C*/ addiu     a1, s0, 0x00C4
/*0x80574330*/ beq       r0, r0, 0x80574388
/*0x80574334*/ nop
/*0x80574338*/ or        a0, s0, r0
/*0x8057433C*/ jal       0x80574154
/*0x80574340*/ addiu     a1, s0, 0x00C4
/*0x80574344*/ beq       r0, r0, 0x80574394
/*0x80574348*/ sb        v0, 0x0018(s0)
/*0x8057434C*/ jal       0x80574178
/*0x80574350*/ addiu     a1, s0, 0x00C4
/*0x80574354*/ beq       r0, r0, 0x80574394
/*0x80574358*/ sb        v0, 0x0018(s0)
/*0x8057435C*/ jal       0x80574280
/*0x80574360*/ or        a0, s0, r0
/*0x80574364*/ lw        t1, 0x0174(s0)
/*0x80574368*/ sb        v0, 0x0018(s0)
/*0x8057436C*/ addiu     t0, r0, 0x0001
/*0x80574370*/ lw        t2, 0x0000(t1)
/*0x80574374*/ sh        t0, 0x004C(t2)
/*0x80574378*/ jal       0x8004A73C
/*0x8057437C*/ lw        a0, 0x0174(s0)
/*0x80574380*/ beq       r0, r0, 0x80574394
/*0x80574384*/ nop
/*0x80574388*/ jal       0x805741B8
/*0x8057438C*/ or        a0, s0, r0
/*0x80574390*/ sb        v0, 0x0018(s0)
/*0x80574394*/ lui       t3, 0x8057
/*0x80574398*/ addiu     t3, t3, 0x4060
/*0x8057439C*/ sw        t3, 0x001C(s0)
/*0x805743A0*/ or        a0, s0, r0
/*0x805743A4*/ jal       0x80574A64
/*0x805743A8*/ lbu       a1, 0x0018(s0)
/*0x805743AC*/ lw        ra, 0x001C(sp)
/*0x805743B0*/ addiu     t4, r0, 0x0001
/*0x805743B4*/ lui       at, 0x800E
/*0x805743B8*/ lw        s0, 0x0018(sp)
/*0x805743BC*/ sb        t4, 0x8150(at)
/*0x805743C0*/ jr        ra
/*0x805743C4*/ addiu     sp, sp, 0x0020
/*0x805743C8*/ addiu     sp, sp, 0xFFE8
/*0x805743CC*/ sw        ra, 0x0014(sp)
/*0x805743D0*/ lh        t6, 0x0144(a0)
/*0x805743D4*/ addiu     at, r0, 0x0007
/*0x805743D8*/ or        a2, a0, r0
/*0x805743DC*/ bnel      t6, at, 0x80574400
/*0x805743E0*/ lw        ra, 0x0014(sp)
/*0x805743E4*/ lw        a0, 0x0034(a0)
/*0x805743E8*/ jal       0x80067BBC
/*0x805743EC*/ lw        a1, 0x0038(a2)
/*0x805743F0*/ addiu     a0, r0, 0x00AC
/*0x805743F4*/ jal       0x80067818
/*0x805743F8*/ or        a1, v0, r0
/*0x805743FC*/ lw        ra, 0x0014(sp)
/*0x80574400*/ addiu     sp, sp, 0x0018
/*0x80574404*/ jr        ra
/*0x80574408*/ nop
/*0x8057440C*/ addiu     sp, sp, 0xFFB0
/*0x80574410*/ sw        ra, 0x001C(sp)
/*0x80574414*/ sw        s0, 0x0018(sp)
/*0x80574418*/ lui       at, 0x4120
/*0x8057441C*/ mtc1      at, f6
/*0x80574420*/ lwc1      f4, 0x0088(a0)
/*0x80574424*/ or        s0, a0, r0
/*0x80574428*/ lwc1      f12, 0x0084(a0)
/*0x8057442C*/ jal       0x80053924
/*0x80574430*/ add.s     f14, f4, f6
/*0x80574434*/ ori       at, r0, 0xFFFF
/*0x80574438*/ beq       v0, at, 0x80574500
/*0x8057443C*/ sh        v0, 0x0026(sp)
/*0x80574440*/ lbu       t6, 0x0026(sp)
/*0x80574444*/ addiu     at, r0, 0x0060
/*0x80574448*/ addiu     t9, r0, 0x0002
/*0x8057444C*/ andi      t7, t6, 0x00F8
/*0x80574450*/ bnel      t7, at, 0x80574504
/*0x80574454*/ lw        ra, 0x001C(sp)
/*0x80574458*/ sw        t9, 0x0028(sp)
/*0x8057445C*/ lwc1      f8, 0x0084(s0)
/*0x80574460*/ lui       at, 0x4040
/*0x80574464*/ mtc1      at, f0
/*0x80574468*/ swc1      f8, 0x002C(sp)
/*0x8057446C*/ lwc1      f10, 0x0088(s0)
/*0x80574470*/ lui       at, 0x8057
/*0x80574474*/ lwc1      f18, 0x4D70(at)
/*0x80574478*/ swc1      f10, 0x0030(sp)
/*0x8057447C*/ lwc1      f16, 0x008C(s0)
/*0x80574480*/ lui       at, 0xC000
/*0x80574484*/ mtc1      r0, f2
/*0x80574488*/ sub.s     f4, f16, f18
/*0x8057448C*/ mtc1      at, f18
/*0x80574490*/ lui       at, 0x8057
/*0x80574494*/ lui       t9, 0x8010
/*0x80574498*/ swc1      f4, 0x0034(sp)
/*0x8057449C*/ lwc1      f6, 0x006C(s0)
/*0x805744A0*/ lwc1      f4, 0x4D74(at)
/*0x805744A4*/ lw        t9, 0x8908(t9)
/*0x805744A8*/ mul.s     f8, f6, f0
/*0x805744AC*/ addiu     a0, sp, 0x0028
/*0x805744B0*/ swc1      f8, 0x0038(sp)
/*0x805744B4*/ lwc1      f10, 0x0070(s0)
/*0x805744B8*/ swc1      f2, 0x0040(sp)
/*0x805744BC*/ swc1      f2, 0x0048(sp)
/*0x805744C0*/ mul.s     f16, f10, f0
/*0x805744C4*/ swc1      f18, 0x0044(sp)
/*0x805744C8*/ swc1      f4, 0x004C(sp)
/*0x805744CC*/ swc1      f16, 0x003C(sp)
/*0x805744D0*/ lw        t0, 0x0010(t9)
/*0x805744D4*/ lw        t9, 0x0028(t0)
/*0x805744D8*/ jalr      t9
/*0x805744DC*/ nop
/*0x805744E0*/ jal       0x80048D4C
/*0x805744E4*/ or        a0, s0, r0
/*0x805744E8*/ lw        a0, 0x0034(s0)
/*0x805744EC*/ jal       0x80067BBC
/*0x805744F0*/ lw        a1, 0x0038(s0)
/*0x805744F4*/ addiu     a0, r0, 0x0278
/*0x805744F8*/ jal       0x80067818
/*0x805744FC*/ or        a1, v0, r0
/*0x80574500*/ lw        ra, 0x001C(sp)
/*0x80574504*/ lw        s0, 0x0018(sp)
/*0x80574508*/ addiu     sp, sp, 0x0050
/*0x8057450C*/ jr        ra
/*0x80574510*/ nop
/*0x80574514*/ addiu     sp, sp, 0xFFE0
/*0x80574518*/ sw        s0, 0x0014(sp)
/*0x8057451C*/ sw        ra, 0x001C(sp)
/*0x80574520*/ sw        s1, 0x0018(sp)
/*0x80574524*/ or        a2, a0, r0
/*0x80574528*/ lw        s1, 0x0174(a0)
/*0x8057452C*/ addiu     s0, a0, 0x00C4
/*0x80574530*/ or        a0, s0, r0
/*0x80574534*/ sw        a2, 0x0020(sp)
/*0x80574538*/ jal       0x80048F84
/*0x8057453C*/ addiu     a1, r0, 0x0001
/*0x80574540*/ lw        v0, 0x0000(s1)
/*0x80574544*/ lhu       t6, 0x004C(v0)
/*0x80574548*/ andi      t7, t6, 0x000F
/*0x8057454C*/ bnel      t7, r0, 0x80574580
/*0x80574550*/ lw        t9, 0x0008(s1)
/*0x80574554*/ lwc1      f4, 0x0004(s0)
/*0x80574558*/ mtc1      r0, f6
/*0x8057455C*/ addiu     t9, r0, 0x0001
/*0x80574560*/ or        a0, s1, r0
/*0x80574564*/ c.le.s    f6, f4
/*0x80574568*/ nop
/*0x8057456C*/ bc1fl     0x80574580
/*0x80574570*/ lw        t9, 0x0008(s1)
/*0x80574574*/ jal       0x8004A73C
/*0x80574578*/ sh        t9, 0x004C(v0)
/*0x8057457C*/ lw        t9, 0x0008(s1)
/*0x80574580*/ or        a0, s0, r0
/*0x80574584*/ andi      t0, t9, 0x0F00
/*0x80574588*/ beq       t0, r0, 0x805745C0
/*0x8057458C*/ nop
/*0x80574590*/ jal       0x80048F84
/*0x80574594*/ or        a1, r0, r0
/*0x80574598*/ lbu       t1, 0x0011(s1)
/*0x8057459C*/ slti      at, t1, 0x0002
/*0x805745A0*/ beq       at, r0, 0x805745C0
/*0x805745A4*/ lui       at, 0x8057
/*0x805745A8*/ lwc1      f10, 0x4D78(at)
/*0x805745AC*/ lwc1      f8, 0x0004(s0)
/*0x805745B0*/ mul.s     f16, f8, f10
/*0x805745B4*/ swc1      f16, 0x0004(s0)
/*0x805745B8*/ jal       0x805743C8
/*0x805745BC*/ lw        a0, 0x0020(sp)
/*0x805745C0*/ jal       0x8057440C
/*0x805745C4*/ lw        a0, 0x0020(sp)
/*0x805745C8*/ lw        ra, 0x001C(sp)
/*0x805745CC*/ lw        s0, 0x0014(sp)
/*0x805745D0*/ lw        s1, 0x0018(sp)
/*0x805745D4*/ jr        ra
/*0x805745D8*/ addiu     sp, sp, 0x0020
/*0x805745DC*/ addiu     sp, sp, 0xFFE8
/*0x805745E0*/ sw        ra, 0x0014(sp)
/*0x805745E4*/ lw        t6, 0x0180(a0)
/*0x805745E8*/ bnel      t6, r0, 0x80574618
/*0x805745EC*/ lw        ra, 0x0014(sp)
/*0x805745F0*/ lw        t9, 0x0174(a0)
/*0x805745F4*/ addiu     t7, r0, 0x0001
/*0x805745F8*/ lw        t9, 0x0000(t9)
/*0x805745FC*/ sh        t7, 0x0012(t9)
/*0x80574600*/ jal       0x8005FCA8
/*0x80574604*/ sw        a0, 0x0018(sp)
/*0x80574608*/ lw        a0, 0x0018(sp)
/*0x8057460C*/ jal       0x80574A64
/*0x80574610*/ addiu     a1, r0, 0x0001
/*0x80574614*/ lw        ra, 0x0014(sp)
/*0x80574618*/ addiu     sp, sp, 0x0018
/*0x8057461C*/ jr        ra
/*0x80574620*/ nop
/*0x80574624*/ addiu     sp, sp, 0xFFE8
/*0x80574628*/ sw        ra, 0x0014(sp)
/*0x8057462C*/ lw        t6, 0x0180(a0)
/*0x80574630*/ bnel      t6, r0, 0x80574644
/*0x80574634*/ lw        ra, 0x0014(sp)
/*0x80574638*/ jal       0x80574A64
/*0x8057463C*/ addiu     a1, r0, 0x0001
/*0x80574640*/ lw        ra, 0x0014(sp)
/*0x80574644*/ addiu     sp, sp, 0x0018
/*0x80574648*/ jr        ra
/*0x8057464C*/ nop
/*0x80574650*/ addiu     sp, sp, 0xFFC0
/*0x80574654*/ sw        ra, 0x0014(sp)
/*0x80574658*/ sw        r0, 0x0018(sp)
/*0x8057465C*/ lwc1      f4, 0x003C(a0)
/*0x80574660*/ lui       at, 0x4040
/*0x80574664*/ mtc1      at, f2
/*0x80574668*/ swc1      f4, 0x001C(sp)
/*0x8057466C*/ lwc1      f6, 0x0040(a0)
/*0x80574670*/ lui       at, 0x8057
/*0x80574674*/ lwc1      f10, 0x4D7C(at)
/*0x80574678*/ swc1      f6, 0x0020(sp)
/*0x8057467C*/ lwc1      f8, 0x0044(a0)
/*0x80574680*/ mtc1      r0, f0
/*0x80574684*/ lui       t6, 0x8010
/*0x80574688*/ sub.s     f16, f8, f10
/*0x8057468C*/ lw        t6, 0x8908(t6)
/*0x80574690*/ swc1      f2, 0x0028(sp)
/*0x80574694*/ swc1      f2, 0x002C(sp)
/*0x80574698*/ swc1      f16, 0x0024(sp)
/*0x8057469C*/ swc1      f0, 0x003C(sp)
/*0x805746A0*/ swc1      f0, 0x0038(sp)
/*0x805746A4*/ swc1      f0, 0x0034(sp)
/*0x805746A8*/ swc1      f0, 0x0030(sp)
/*0x805746AC*/ lw        t7, 0x0010(t6)
/*0x805746B0*/ addiu     a0, sp, 0x0018
/*0x805746B4*/ lw        t9, 0x0028(t7)
/*0x805746B8*/ jalr      t9
/*0x805746BC*/ nop
/*0x805746C0*/ lw        ra, 0x0014(sp)
/*0x805746C4*/ addiu     sp, sp, 0x0040
/*0x805746C8*/ jr        ra
/*0x805746CC*/ nop
/*0x805746D0*/ addiu     sp, sp, 0xFFE0
/*0x805746D4*/ sw        ra, 0x001C(sp)
/*0x805746D8*/ sw        s0, 0x0018(sp)
/*0x805746DC*/ jal       0x80574650
/*0x805746E0*/ or        s0, a0, r0
/*0x805746E4*/ lw        t7, 0x0174(s0)
/*0x805746E8*/ sb        r0, 0x0165(s0)
/*0x805746EC*/ addiu     t6, r0, 0x0001
/*0x805746F0*/ lw        t9, 0x0000(t7)
/*0x805746F4*/ or        a0, s0, r0
/*0x805746F8*/ jal       0x8005FCA8
/*0x805746FC*/ sh        t6, 0x0012(t9)
/*0x80574700*/ or        a0, s0, r0
/*0x80574704*/ jal       0x80574A64
/*0x80574708*/ addiu     a1, r0, 0x0001
/*0x8057470C*/ lh        t9, 0x00C0(s0)
/*0x80574710*/ lh        t2, 0x00C2(s0)
/*0x80574714*/ lui       at, 0x8057
/*0x80574718*/ mtc1      t9, f4
/*0x8057471C*/ mtc1      t2, f18
/*0x80574720*/ lwc1      f8, 0x4D80(at)
/*0x80574724*/ cvt.s.w   f6, f4
/*0x80574728*/ lui       at, 0x3FC0
/*0x8057472C*/ lhu       v0, 0x000C(s0)
/*0x80574730*/ cvt.s.w   f4, f18
/*0x80574734*/ mul.s     f10, f6, f8
/*0x80574738*/ mtc1      at, f6
/*0x8057473C*/ addiu     at, r0, 0x4035
/*0x80574740*/ mul.s     f8, f4, f6
/*0x80574744*/ trunc.w.s f16, f10
/*0x80574748*/ trunc.w.s f10, f8
/*0x8057474C*/ mfc1      t1, f16
/*0x80574750*/ mfc1      t4, f10
/*0x80574754*/ sh        t1, 0x00C0(s0)
/*0x80574758*/ beq       v0, at, 0x8057476C
/*0x8057475C*/ sh        t4, 0x00C2(s0)
/*0x80574760*/ addiu     at, r0, 0x468C
/*0x80574764*/ bne       v0, at, 0x80574788
/*0x80574768*/ nop
/*0x8057476C*/ jal       0x80067E68
/*0x80574770*/ addiu     a0, r0, 0x0005
/*0x80574774*/ addiu     a0, r0, 0x0251
/*0x80574778*/ jal       0x80067818
/*0x8057477C*/ or        a1, v0, r0
/*0x80574780*/ beq       r0, r0, 0x805747A0
/*0x80574784*/ lw        ra, 0x001C(sp)
/*0x80574788*/ jal       0x80067E68
/*0x8057478C*/ or        a0, r0, r0
/*0x80574790*/ addiu     a0, r0, 0x0251
/*0x80574794*/ jal       0x80067818
/*0x80574798*/ or        a1, v0, r0
/*0x8057479C*/ lw        ra, 0x001C(sp)
/*0x805747A0*/ addiu     t5, r0, 0x0001
/*0x805747A4*/ lui       at, 0x800E
/*0x805747A8*/ lw        s0, 0x0018(sp)
/*0x805747AC*/ sb        t5, 0x8150(at)
/*0x805747B0*/ jr        ra
/*0x805747B4*/ addiu     sp, sp, 0x0020
/*0x805747B8*/ lui       v0, 0x800F
/*0x805747BC*/ addiu     v0, v0, 0x7EA0
/*0x805747C0*/ lw        t6, 0x0C2C(v0)
/*0x805747C4*/ lw        t7, 0x0C30(v0)
/*0x805747C8*/ addiu     sp, sp, 0xFFE8
/*0x805747CC*/ sw        ra, 0x0014(sp)
/*0x805747D0*/ slt       at, t6, t7
/*0x805747D4*/ bnel      at, r0, 0x805747E8
/*0x805747D8*/ lw        ra, 0x0014(sp)
/*0x805747DC*/ jal       0x805746D0
/*0x805747E0*/ nop
/*0x805747E4*/ lw        ra, 0x0014(sp)
/*0x805747E8*/ addiu     sp, sp, 0x0018
/*0x805747EC*/ jr        ra
/*0x805747F0*/ nop
/*0x805747F4*/ addiu     sp, sp, 0xFFC8
/*0x805747F8*/ sw        s1, 0x0018(sp)
/*0x805747FC*/ sll       s1, a1, 16
/*0x80574800*/ sra       s1, s1, 16
/*0x80574804*/ sw        s0, 0x0014(sp)
/*0x80574808*/ or        s0, a0, r0
/*0x8057480C*/ sw        ra, 0x0034(sp)
/*0x80574810*/ sw        s7, 0x0030(sp)
/*0x80574814*/ sw        s6, 0x002C(sp)
/*0x80574818*/ sw        s5, 0x0028(sp)
/*0x8057481C*/ sw        s4, 0x0024(sp)
/*0x80574820*/ sw        s3, 0x0020(sp)
/*0x80574824*/ sw        s2, 0x001C(sp)
/*0x80574828*/ beq       s1, r0, 0x805748E8
/*0x8057482C*/ sw        a1, 0x003C(sp)
/*0x80574830*/ addiu     s7, r0, 0x4001
/*0x80574834*/ addiu     s6, r0, 0x0009
/*0x80574838*/ addiu     s5, r0, 0x000B
/*0x8057483C*/ addiu     s4, r0, 0x000A
/*0x80574840*/ addiu     s3, r0, 0x0001
/*0x80574844*/ addiu     s2, r0, 0x0001
/*0x80574848*/ lw        v1, 0x0000(s0)
/*0x8057484C*/ beq       v1, r0, 0x805748E0
/*0x80574850*/ nop
/*0x80574854*/ beql      s2, v1, 0x805748D8
/*0x80574858*/ addiu     s1, s1, 0xFFFF
/*0x8057485C*/ lh        a1, 0x0184(v1)
/*0x80574860*/ beql      a1, r0, 0x80574884
/*0x80574864*/ lw        v1, 0x0000(s0)
/*0x80574868*/ jal       0x805747F4
/*0x8057486C*/ addiu     a0, v1, 0x0188
/*0x80574870*/ beql      v0, r0, 0x80574884
/*0x80574874*/ lw        v1, 0x0000(s0)
/*0x80574878*/ beq       r0, r0, 0x805748F0
/*0x8057487C*/ lw        ra, 0x0034(sp)
/*0x80574880*/ lw        v1, 0x0000(s0)
/*0x80574884*/ lw        t6, 0x000C(v1)
/*0x80574888*/ srl       t7, t6, 30
/*0x8057488C*/ bnel      s3, t7, 0x805748D8
/*0x80574890*/ addiu     s1, s1, 0xFFFF
/*0x80574894*/ lhu       v0, 0x000E(v1)
/*0x80574898*/ srl       v0, v0, 10
/*0x8057489C*/ andi      v0, v0, 0x000F
/*0x805748A0*/ beql      s4, v0, 0x805748C4
/*0x805748A4*/ lhu       t9, 0x000C(v1)
/*0x805748A8*/ beql      s5, v0, 0x805748C4
/*0x805748AC*/ lhu       t9, 0x000C(v1)
/*0x805748B0*/ beql      v0, r0, 0x805748C4
/*0x805748B4*/ lhu       t9, 0x000C(v1)
/*0x805748B8*/ bnel      s6, v0, 0x805748D8
/*0x805748BC*/ addiu     s1, s1, 0xFFFF
/*0x805748C0*/ lhu       t9, 0x000C(v1)
/*0x805748C4*/ beql      s7, t9, 0x805748D8
/*0x805748C8*/ addiu     s1, s1, 0xFFFF
/*0x805748CC*/ beq       r0, r0, 0x805748EC
/*0x805748D0*/ or        v0, v1, r0
/*0x805748D4*/ addiu     s1, s1, 0xFFFF
/*0x805748D8*/ sll       s1, s1, 16
/*0x805748DC*/ sra       s1, s1, 16
/*0x805748E0*/ bne       s1, r0, 0x80574848
/*0x805748E4*/ addiu     s0, s0, 0x0004
/*0x805748E8*/ or        v0, r0, r0
/*0x805748EC*/ lw        ra, 0x0034(sp)
/*0x805748F0*/ lw        s0, 0x0014(sp)
/*0x805748F4*/ lw        s1, 0x0018(sp)
/*0x805748F8*/ lw        s2, 0x001C(sp)
/*0x805748FC*/ lw        s3, 0x0020(sp)
/*0x80574900*/ lw        s4, 0x0024(sp)
/*0x80574904*/ lw        s5, 0x0028(sp)
/*0x80574908*/ lw        s6, 0x002C(sp)
/*0x8057490C*/ lw        s7, 0x0030(sp)
/*0x80574910*/ jr        ra
/*0x80574914*/ addiu     sp, sp, 0x0038
/*0x80574918*/ lui       v0, 0x8010
/*0x8057491C*/ lw        v0, 0x8810(v0)
/*0x80574920*/ addiu     sp, sp, 0xFFE8
/*0x80574924*/ sw        ra, 0x0014(sp)
/*0x80574928*/ sw        a0, 0x0018(sp)
/*0x8057492C*/ lh        a1, 0x0006(v0)
/*0x80574930*/ jal       0x805747F4
/*0x80574934*/ lw        a0, 0x0010(v0)
/*0x80574938*/ lui       v1, 0x800F
/*0x8057493C*/ bne       v0, r0, 0x80574960
/*0x80574940*/ addiu     v1, v1, 0x7EA0
/*0x80574944*/ lw        a0, 0x09B0(v1)
/*0x80574948*/ jal       0x805747F4
/*0x8057494C*/ lh        a1, 0x09A6(v1)
/*0x80574950*/ bnel      v0, r0, 0x80574964
/*0x80574954*/ lw        ra, 0x0014(sp)
/*0x80574958*/ jal       0x805746D0
/*0x8057495C*/ lw        a0, 0x0018(sp)
/*0x80574960*/ lw        ra, 0x0014(sp)
/*0x80574964*/ addiu     sp, sp, 0x0018
/*0x80574968*/ jr        ra
/*0x8057496C*/ nop
/*0x80574970*/ lui       t6, 0x8010
/*0x80574974*/ lw        t6, 0x9388(t6)
/*0x80574978*/ addiu     sp, sp, 0xFFE8
/*0x8057497C*/ sw        ra, 0x0014(sp)
/*0x80574980*/ beq       t6, r0, 0x8057499C
/*0x80574984*/ sw        a0, 0x0018(sp)
/*0x80574988*/ jal       0x805746D0
/*0x8057498C*/ nop
/*0x80574990*/ lw        a0, 0x0018(sp)
/*0x80574994*/ jal       0x80574A64
/*0x80574998*/ addiu     a1, r0, 0x0007
/*0x8057499C*/ lw        ra, 0x0014(sp)
/*0x805749A0*/ addiu     sp, sp, 0x0018
/*0x805749A4*/ jr        ra
/*0x805749A8*/ nop
/*0x805749AC*/ addiu     sp, sp, 0xFFE0
/*0x805749B0*/ sw        ra, 0x001C(sp)
/*0x805749B4*/ sw        s0, 0x0018(sp)
/*0x805749B8*/ lw        v0, 0x0174(a0)
/*0x805749BC*/ or        s0, a0, r0
/*0x805749C0*/ lw        t6, 0x0008(v0)
/*0x805749C4*/ andi      t7, t6, 0x0F00
/*0x805749C8*/ beql      t7, r0, 0x805749F4
/*0x805749CC*/ lwc1      f12, 0x00C8(s0)
/*0x805749D0*/ lbu       t9, 0x0011(v0)
/*0x805749D4*/ slti      at, t9, 0x0002
/*0x805749D8*/ beq       at, r0, 0x805749F0
/*0x805749DC*/ lui       at, 0x8057
/*0x805749E0*/ lwc1      f6, 0x4D84(at)
/*0x805749E4*/ lwc1      f4, 0x00C8(a0)
/*0x805749E8*/ mul.s     f8, f4, f6
/*0x805749EC*/ swc1      f8, 0x00C8(a0)
/*0x805749F0*/ lwc1      f12, 0x00C8(s0)
/*0x805749F4*/ lwc1      f14, 0x00EC(s0)
/*0x805749F8*/ jal       0x80065ABC
/*0x805749FC*/ lw        a2, 0x00E0(s0)
/*0x80574A00*/ swc1      f0, 0x00C8(s0)
/*0x80574A04*/ lui       t9, 0x8010
/*0x80574A08*/ lw        t9, 0x9388(t9)
/*0x80574A0C*/ bnel      t9, r0, 0x80574A54
/*0x80574A10*/ lw        ra, 0x001C(sp)
/*0x80574A14*/ jal       0x80574650
/*0x80574A18*/ or        a0, s0, r0
/*0x80574A1C*/ or        a0, s0, r0
/*0x80574A20*/ jal       0x80574A64
/*0x80574A24*/ addiu     a1, r0, 0x0006
/*0x80574A28*/ lw        t1, 0x0174(s0)
/*0x80574A2C*/ addiu     t0, r0, 0x0001
/*0x80574A30*/ sb        t0, 0x0165(s0)
/*0x80574A34*/ lw        t2, 0x0000(t1)
/*0x80574A38*/ or        a0, s0, r0
/*0x80574A3C*/ jal       0x8005FD1C
/*0x80574A40*/ sh        r0, 0x0012(t2)
/*0x80574A44*/ mtc1      r0, f10
/*0x80574A48*/ nop
/*0x80574A4C*/ swc1      f10, 0x00C8(s0)
/*0x80574A50*/ lw        ra, 0x001C(sp)
/*0x80574A54*/ lw        s0, 0x0018(sp)
/*0x80574A58*/ addiu     sp, sp, 0x0020
/*0x80574A5C*/ jr        ra
/*0x80574A60*/ nop
/*0x80574A64*/ andi      t6, a1, 0x00FF
/*0x80574A68*/ sw        a1, 0x0004(sp)
/*0x80574A6C*/ sll       t7, t6, 2
/*0x80574A70*/ lui       t9, 0x8057
/*0x80574A74*/ sb        a1, 0x0018(a0)
/*0x80574A78*/ addu      t9, t9, t7
/*0x80574A7C*/ lw        t9, 0x4CEC(t9)
/*0x80574A80*/ jr        ra
/*0x80574A84*/ sw        t9, 0x0020(a0)
/*0x80574A88*/ slti      at, a0, 0x45C0
/*0x80574A8C*/ bne       at, r0, 0x80574AAC
/*0x80574A90*/ addiu     at, r0, 0x45F3
/*0x80574A94*/ beq       a0, at, 0x80574B28
/*0x80574A98*/ addiu     at, r0, 0x468C
/*0x80574A9C*/ beq       a0, at, 0x80574B30
/*0x80574AA0*/ nop
/*0x80574AA4*/ beq       r0, r0, 0x80574B3C
/*0x80574AA8*/ addiu     v1, r0, 0x0006
/*0x80574AAC*/ slti      at, a0, 0x45BD
/*0x80574AB0*/ bne       at, r0, 0x80574AC8
/*0x80574AB4*/ addiu     at, r0, 0x45BF
/*0x80574AB8*/ beq       a0, at, 0x80574B28
/*0x80574ABC*/ nop
/*0x80574AC0*/ beq       r0, r0, 0x80574B3C
/*0x80574AC4*/ addiu     v1, r0, 0x0006
/*0x80574AC8*/ slti      at, a0, 0x4036
/*0x80574ACC*/ bne       at, r0, 0x80574AE8
/*0x80574AD0*/ addiu     t6, a0, 0xBFD0
/*0x80574AD4*/ addiu     at, r0, 0x45BC
/*0x80574AD8*/ beq       a0, at, 0x80574B28
/*0x80574ADC*/ nop
/*0x80574AE0*/ beq       r0, r0, 0x80574B3C
/*0x80574AE4*/ addiu     v1, r0, 0x0006
/*0x80574AE8*/ sltiu     at, t6, 0x0006
/*0x80574AEC*/ beq       at, r0, 0x80574B38
/*0x80574AF0*/ sll       t6, t6, 2
/*0x80574AF4*/ lui       at, 0x8057
/*0x80574AF8*/ addu      at, at, t6
/*0x80574AFC*/ lw        t6, 0x4D88(at)
/*0x80574B00*/ jr        t6
/*0x80574B04*/ nop
/*0x80574B08*/ jr        ra
/*0x80574B0C*/ or        v0, r0, r0
/*0x80574B10*/ jr        ra
/*0x80574B14*/ addiu     v0, r0, 0x0001
/*0x80574B18*/ jr        ra
/*0x80574B1C*/ addiu     v0, r0, 0x0002
/*0x80574B20*/ jr        ra
/*0x80574B24*/ addiu     v0, r0, 0x0003
/*0x80574B28*/ jr        ra
/*0x80574B2C*/ addiu     v0, r0, 0x0004
/*0x80574B30*/ jr        ra
/*0x80574B34*/ addiu     v0, r0, 0x0005
/*0x80574B38*/ addiu     v1, r0, 0x0006
/*0x80574B3C*/ jr        ra
/*0x80574B40*/ or        v0, v1, r0
/*0x80574B44*/ addiu     sp, sp, 0xFFC8
/*0x80574B48*/ sw        s1, 0x0020(sp)
/*0x80574B4C*/ or        s1, a0, r0
/*0x80574B50*/ sw        ra, 0x0024(sp)
/*0x80574B54*/ sw        s0, 0x001C(sp)
/*0x80574B58*/ lhu       a1, 0x0004(s1)
/*0x80574B5C*/ lwc1      f4, 0x0010(s1)
/*0x80574B60*/ lw        a3, 0x000C(s1)
/*0x80574B64*/ lw        a2, 0x0008(s1)
/*0x80574B68*/ lui       a0, 0x8057
/*0x80574B6C*/ sll       a1, a1, 16
/*0x80574B70*/ ori       a1, a1, 0x1800
/*0x80574B74*/ addiu     a0, a0, 0x4F30
/*0x80574B78*/ jal       0x80046804
/*0x80574B7C*/ swc1      f4, 0x0010(sp)
/*0x80574B80*/ bne       v0, r0, 0x80574B90
/*0x80574B84*/ or        s0, v0, r0
/*0x80574B88*/ beq       r0, r0, 0x80574CC0
/*0x80574B8C*/ or        v0, r0, r0
/*0x80574B90*/ sw        r0, 0x0180(s0)
/*0x80574B94*/ jal       0x80574A88
/*0x80574B98*/ lhu       a0, 0x0004(s1)
/*0x80574B9C*/ lw        a1, 0x0174(s0)
/*0x80574BA0*/ lui       t7, 0x8057
/*0x80574BA4*/ addiu     t7, t7, 0x4D0C
/*0x80574BA8*/ sll       t6, v0, 2
/*0x80574BAC*/ addu      v1, t6, t7
/*0x80574BB0*/ lhu       t9, 0x0000(v1)
/*0x80574BB4*/ lw        t9, 0x0000(a1)
/*0x80574BB8*/ or        a0, s0, r0
/*0x80574BBC*/ sh        t9, 0x0018(t9)
/*0x80574BC0*/ lhu       t0, 0x0002(v1)
/*0x80574BC4*/ lw        t1, 0x0000(a1)
/*0x80574BC8*/ sh        t0, 0x001A(t1)
/*0x80574BCC*/ jal       0x80052BA4
/*0x80574BD0*/ sw        a1, 0x0028(sp)
/*0x80574BD4*/ jal       0x8005FDC4
/*0x80574BD8*/ or        a0, s0, r0
/*0x80574BDC*/ lw        a0, 0x0028(sp)
/*0x80574BE0*/ lw        t2, 0x0000(a0)
/*0x80574BE4*/ jal       0x8004A73C
/*0x80574BE8*/ sh        r0, 0x004C(t2)
/*0x80574BEC*/ lwc1      f6, 0x0014(s1)
/*0x80574BF0*/ swc1      f6, 0x00C4(s0)
/*0x80574BF4*/ lwc1      f8, 0x0018(s1)
/*0x80574BF8*/ swc1      f8, 0x00C8(s0)
/*0x80574BFC*/ jal       0x80047090
/*0x80574C00*/ lhu       a0, 0x0004(s1)
/*0x80574C04*/ lhu       t5, 0x000E(s0)
/*0x80574C08*/ andi      t4, v0, 0x03FF
/*0x80574C0C*/ addiu     a2, v0, 0x0032
/*0x80574C10*/ andi      t6, t5, 0xFC00
/*0x80574C14*/ or        t7, t4, t6
/*0x80574C18*/ sh        t7, 0x000E(s0)
/*0x80574C1C*/ lw        v1, 0x001C(s1)
/*0x80574C20*/ andi      a2, a2, 0xFFFF
/*0x80574C24*/ addiu     at, r0, 0x0001
/*0x80574C28*/ beql      v1, r0, 0x80574C54
/*0x80574C2C*/ lhu       t0, 0x000E(s0)
/*0x80574C30*/ beq       v1, at, 0x80574C74
/*0x80574C34*/ addiu     at, r0, 0x0002
/*0x80574C38*/ beq       v1, at, 0x80574C84
/*0x80574C3C*/ addiu     at, r0, 0x0003
/*0x80574C40*/ beq       v1, at, 0x80574CB4
/*0x80574C44*/ or        a1, s0, r0
/*0x80574C48*/ beq       r0, r0, 0x80574CC0
/*0x80574C4C*/ or        v0, s0, r0
/*0x80574C50*/ lhu       t0, 0x000E(s0)
/*0x80574C54*/ andi      t9, a2, 0x03FF
/*0x80574C58*/ or        a0, s0, r0
/*0x80574C5C*/ andi      t1, t0, 0xFC00
/*0x80574C60*/ or        t2, t9, t1
/*0x80574C64*/ jal       0x80044194
/*0x80574C68*/ sh        t2, 0x000E(s0)
/*0x80574C6C*/ beq       r0, r0, 0x80574CC0
/*0x80574C70*/ or        v0, s0, r0
/*0x80574C74*/ jal       0x80044194
/*0x80574C78*/ or        a0, s0, r0
/*0x80574C7C*/ beq       r0, r0, 0x80574CC0
/*0x80574C80*/ or        v0, s0, r0
/*0x80574C84*/ lhu       t4, 0x000E(s0)
/*0x80574C88*/ andi      t5, a2, 0x03FF
/*0x80574C8C*/ or        a1, s0, r0
/*0x80574C90*/ andi      t6, t4, 0xFC00
/*0x80574C94*/ or        t7, t5, t6
/*0x80574C98*/ sh        t7, 0x000E(s0)
/*0x80574C9C*/ jal       0x80047F9C
/*0x80574CA0*/ lw        a0, 0x0000(s1)
/*0x80574CA4*/ jal       0x8005FDC4
/*0x80574CA8*/ or        a0, s0, r0
/*0x80574CAC*/ beq       r0, r0, 0x80574CC0
/*0x80574CB0*/ or        v0, s0, r0
/*0x80574CB4*/ jal       0x80047F9C
/*0x80574CB8*/ lw        a0, 0x0000(s1)
/*0x80574CBC*/ or        v0, s0, r0
/*0x80574CC0*/ lw        ra, 0x0024(sp)
/*0x80574CC4*/ lw        s0, 0x001C(sp)
/*0x80574CC8*/ lw        s1, 0x0020(sp)
/*0x80574CCC*/ jr        ra
/*0x80574CD0*/ addiu     sp, sp, 0x0038
/*0x80574CD4*/ nop
/*0x80574CD8*/ nop
/*0x80574CDC*/ nop

// data:
/*0x80574CE0*/ .dw 0x00000000
/*0x80574CE4*/ .dw 0x00000000
/*0x80574CE8*/ .dw 0x00000001
/*0x80574CEC*/ .dw 0x805742A4
/*0x80574CF0*/ .dw 0x80574514
/*0x80574CF4*/ .dw 0x805745DC
/*0x80574CF8*/ .dw 0x80574624
/*0x80574CFC*/ .dw 0x805747B8
/*0x80574D00*/ .dw 0x80574918
/*0x80574D04*/ .dw 0x80574970
/*0x80574D08*/ .dw 0x805749AC
/*0x80574D0C*/ .dw 0x24222444
/*0x80574D10*/ .dw 0x22422244
/*0x80574D14*/ .dw 0x42222244
/*0x80574D18*/ .dw 0x22244244
/*0x80574D1C*/ .dw 0x44444444
/*0x80574D20*/ .dw 0x77777777
/*0x80574D24*/ .dw 0x00000000
/*0x80574D28*/ .dw 0x00000000
/*0x80574D2C*/ .dw 0x00000000

// rodata:
/*0x80574D30*/ .dw 0x80574114
/*0x80574D34*/ .dw 0x80574114
/*0x80574D38*/ .dw 0x80574114
/*0x80574D3C*/ .dw 0x80574114
/*0x80574D40*/ .dw 0x8057412C
/*0x80574D44*/ .dw 0x8057412C
/*0x80574D48*/ .dw 0x8057412C
/*0x80574D4C*/ .dw 0x8057412C
/*0x80574D50*/ .dw 0x8057412C
/*0x80574D54*/ .dw 0x8057412C
/*0x80574D58*/ .dw 0x8057412C
/*0x80574D5C*/ .dw 0x8057412C
/*0x80574D60*/ .dw 0x80574114
/*0x80574D64*/ .dw 0x80574114
/*0x80574D68*/ .dw 0x80574114
/*0x80574D6C*/ .dw 0x80574114
/*0x80574D70*/ .dw 0x3B03126F
/*0x80574D74*/ .dw 0x3D4CCCCD
/*0x80574D78*/ .dw 0xBF333333
/*0x80574D7C*/ .dw 0x3C23D70A
/*0x80574D80*/ .dw 0x3FA66666
/*0x80574D84*/ .dw 0xBF333333
/*0x80574D88*/ .dw 0x80574B08
/*0x80574D8C*/ .dw 0x80574B10
/*0x80574D90*/ .dw 0x80574B18
/*0x80574D94*/ .dw 0x80574B20
/*0x80574D98*/ .dw 0x80574B28
/*0x80574D9C*/ .dw 0x80574B30

// meta:
.dw 0x00000E50 // textSize
.dw 0x00000050 // dataSize
.dw 0x00000070 // rodataSize
.dw 0x00004B10 // bssSize
.dw 0x0000005B // numRelocations

// relocations:
ovl_rel SEC_TEXT, R_HI16, 0x000000
ovl_rel SEC_TEXT, R_LO16, 0x000004
ovl_rel SEC_TEXT, R_HI16, 0x000018
ovl_rel SEC_TEXT, R_LO16, 0x000024
ovl_rel SEC_TEXT, R_HI16, 0x00001C
ovl_rel SEC_TEXT, R_LO16, 0x000020
ovl_rel SEC_TEXT, R_HI16, 0x000034
ovl_rel SEC_TEXT, R_LO16, 0x000038
ovl_rel SEC_TEXT, R_HI16, 0x00004C
ovl_rel SEC_TEXT, R_LO16, 0x000050
ovl_rel SEC_TEXT, R_HI16, 0x000068
ovl_rel SEC_TEXT, R_LO16, 0x00006C
ovl_rel SEC_TEXT, R_26, 0x000188
ovl_rel SEC_TEXT, R_26, 0x0001FC
ovl_rel SEC_TEXT, R_HI16, 0x000270
ovl_rel SEC_TEXT, R_LO16, 0x000278
ovl_rel SEC_TEXT, R_HI16, 0x000424
ovl_rel SEC_TEXT, R_LO16, 0x00042C
ovl_rel SEC_TEXT, R_26, 0x0004AC
ovl_rel SEC_TEXT, R_26, 0x0004BC
ovl_rel SEC_TEXT, R_26, 0x0004CC
ovl_rel SEC_TEXT, R_26, 0x0004F8
ovl_rel SEC_TEXT, R_HI16, 0x000504
ovl_rel SEC_TEXT, R_LO16, 0x000508
ovl_rel SEC_TEXT, R_26, 0x000514
ovl_rel SEC_TEXT, R_HI16, 0x0005E0
ovl_rel SEC_TEXT, R_LO16, 0x0005E4
ovl_rel SEC_TEXT, R_HI16, 0x000600
ovl_rel SEC_TEXT, R_LO16, 0x000610
ovl_rel SEC_TEXT, R_HI16, 0x000714
ovl_rel SEC_TEXT, R_LO16, 0x000718
ovl_rel SEC_TEXT, R_26, 0x000728
ovl_rel SEC_TEXT, R_26, 0x000730
ovl_rel SEC_TEXT, R_26, 0x00077C
ovl_rel SEC_TEXT, R_26, 0x0007A8
ovl_rel SEC_TEXT, R_HI16, 0x0007E0
ovl_rel SEC_TEXT, R_LO16, 0x0007E4
ovl_rel SEC_TEXT, R_26, 0x00084C
ovl_rel SEC_TEXT, R_26, 0x000874
ovl_rel SEC_TEXT, R_HI16, 0x000884
ovl_rel SEC_TEXT, R_LO16, 0x000890
ovl_rel SEC_TEXT, R_26, 0x00094C
ovl_rel SEC_TEXT, R_26, 0x0009D8
ovl_rel SEC_TEXT, R_26, 0x000AA0
ovl_rel SEC_TEXT, R_26, 0x000AB8
ovl_rel SEC_TEXT, R_26, 0x000AC8
ovl_rel SEC_TEXT, R_26, 0x000AF8
ovl_rel SEC_TEXT, R_26, 0x000B04
ovl_rel SEC_TEXT, R_HI16, 0x000B4C
ovl_rel SEC_TEXT, R_LO16, 0x000B50
ovl_rel SEC_TEXT, R_26, 0x000B84
ovl_rel SEC_TEXT, R_26, 0x000B90
ovl_rel SEC_TEXT, R_HI16, 0x000BE0
ovl_rel SEC_TEXT, R_LO16, 0x000BEC
ovl_rel SEC_TEXT, R_HI16, 0x000C64
ovl_rel SEC_TEXT, R_LO16, 0x000C6C
ovl_rel SEC_TEXT, R_HI16, 0x000CD8
ovl_rel SEC_TEXT, R_LO16, 0x000CE4
ovl_rel SEC_TEXT, R_26, 0x000D04
ovl_rel SEC_TEXT, R_HI16, 0x000D10
ovl_rel SEC_TEXT, R_LO16, 0x000D14
ovl_rel SEC_DATA, R_32, 0x00000C
ovl_rel SEC_DATA, R_32, 0x000010
ovl_rel SEC_DATA, R_32, 0x000014
ovl_rel SEC_DATA, R_32, 0x000018
ovl_rel SEC_DATA, R_32, 0x00001C
ovl_rel SEC_DATA, R_32, 0x000020
ovl_rel SEC_DATA, R_32, 0x000024
ovl_rel SEC_DATA, R_32, 0x000028
ovl_rel SEC_RODATA, R_32, 0x000000
ovl_rel SEC_RODATA, R_32, 0x000004
ovl_rel SEC_RODATA, R_32, 0x000008
ovl_rel SEC_RODATA, R_32, 0x00000C
ovl_rel SEC_RODATA, R_32, 0x000010
ovl_rel SEC_RODATA, R_32, 0x000014
ovl_rel SEC_RODATA, R_32, 0x000018
ovl_rel SEC_RODATA, R_32, 0x00001C
ovl_rel SEC_RODATA, R_32, 0x000020
ovl_rel SEC_RODATA, R_32, 0x000024
ovl_rel SEC_RODATA, R_32, 0x000028
ovl_rel SEC_RODATA, R_32, 0x00002C
ovl_rel SEC_RODATA, R_32, 0x000030
ovl_rel SEC_RODATA, R_32, 0x000034
ovl_rel SEC_RODATA, R_32, 0x000038
ovl_rel SEC_RODATA, R_32, 0x00003C
ovl_rel SEC_RODATA, R_32, 0x000058
ovl_rel SEC_RODATA, R_32, 0x00005C
ovl_rel SEC_RODATA, R_32, 0x000060
ovl_rel SEC_RODATA, R_32, 0x000064
ovl_rel SEC_RODATA, R_32, 0x000068
ovl_rel SEC_RODATA, R_32, 0x00006C

.dw 0x00000000
.align 16
.org org()-4
.dw 0x00000190 // metaSize
