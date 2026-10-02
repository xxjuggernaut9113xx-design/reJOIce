/* 1481d2bf0 ?StopSequence@UBeatSpawnerManager@@QEAAXXZ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Possible PIC construction at 0x0001481d2c16: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0001481d2c64: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0001481d2cae: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0001481d2d08: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0001481d2d6c: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0001481d2cb3) */
/* WARNING: Removing unreachable block (ram,0x0001481d2c69) */
/* WARNING: Removing unreachable block (ram,0x0001481d2c74) */
/* WARNING: Removing unreachable block (ram,0x0001481d2c99) */
/* WARNING: Removing unreachable block (ram,0x0001481d2c1b) */
/* WARNING: Removing unreachable block (ram,0x0001481d2c2a) */
/* WARNING: Removing unreachable block (ram,0x0001481d2c4f) */
/* WARNING: Removing unreachable block (ram,0x0001481d2d0d) */
/* WARNING: Removing unreachable block (ram,0x0001481d2d16) */

void _StopSequence_UBeatSpawnerManager__QEAAXXZ(longlong param_1)

{
  if (1 < DAT_14eab53c8) {
    halt_baddata();
  }
  if (0 < *(int *)(param_1 + 0x110) - *(int *)(param_1 + 0x118)) {
    if (DAT_14eab53c8 < 2) goto LAB_1481d2d29;
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78c18);
  }
  if (1 < DAT_14eab53c8) {
    halt_baddata();
  }
LAB_1481d2d29:
  *(undefined1 *)(param_1 + 0x108) = 0;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  if (*(int *)(param_1 + 0xf4) != 0) {
    func_0x0001481d2290(param_1 + 0xe8,0);
  }
  *(undefined4 *)(param_1 + 0x110) = 0;
  if ((DAT_14eab53c8 < 2) && (func_0x00014815f7b0(param_1 + 0xa8), DAT_14eab53c8 < 3)) {
    return;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



