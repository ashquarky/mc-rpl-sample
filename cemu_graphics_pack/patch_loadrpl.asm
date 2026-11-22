[MinecraftWiiU_LoadRPL_v688]
moduleMatches = 0x867317DE

.origin = codecave
loaded_rpl:
.int 0
rpl_name:
.string "mc_rpl_sample.rpl"
.byte 0

init_func:
    stwu r1, -16(r1)
    mflr r0
    stw r0, 20(r1)

    lis r4, loaded_rpl@ha
    addi r4, r4, loaded_rpl@l
    lwz r3, 0(r4)
    cmplwi r3, 0
    bne return

    lis r3, rpl_name@ha
    addi r3, r3, rpl_name@l
    bl import.coreinit.OSDynLoad_Acquire

return:
    lwz r0, 20(r1)
    mtlr r0
    addi r1, r1, 16
    li r3, 0
    blr

; using bla here is a bit cheeky
0x0380abec = bla init_func
