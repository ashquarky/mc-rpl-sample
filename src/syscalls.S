.section .text.SC_KernelCopyData
.global SC_KernelCopyData
.type SC_KernelCopyData, @function
SC_KernelCopyData:
    li %r0, 0x2500
    sc
    blr

.section .text.OSGetTitleVersion
.global OSGetTitleVersion
.type OSGetTitleVersion, @function
OSGetTitleVersion:
    li %r0, 0x7000
    sc
    blr
