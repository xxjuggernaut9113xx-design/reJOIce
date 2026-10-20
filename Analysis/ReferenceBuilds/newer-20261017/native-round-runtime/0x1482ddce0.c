// Selected newer-build routine; caller-supplied label: EndRoundSession_URoundManager
// Address: 0x1482ddce0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: EndRoundSession_URoundManager */

void FUN_1482ddce0(longlong param_1)

{
  undefined1 auStack_118 [32];
  undefined1 auStack_f8 [16];
  undefined1 auStack_e8 [80];
  undefined1 auStack_98 [64];
  longlong lStack_58;
  undefined4 uStack_50;
  undefined1 *puStack_30;
  ulonglong uStack_18;
  
  if (4 < DAT_14edc6208) {
    puStack_30 = &LAB_1482ddd17;
    FUN_140f252a0(&DAT_14edc6208,&UNK_14d219b20,*(undefined4 *)(param_1 + 0xb8),
                  *(undefined4 *)(param_1 + 0xbc));
  }
  if (*(char *)(param_1 + 0xc1) != '\a') {
    *(undefined1 *)(param_1 + 0xc1) = 7;
    puStack_30 = &LAB_1482ddd32;
    FUN_1481f7370(param_1 + 0x28,7);
  }
  uStack_18 = _DAT_14ed716f8 ^ (ulonglong)auStack_118;
  func_0x0001481f3f20(auStack_f8);
  FUN_1481f5390(auStack_f8,param_1 + 0xb8);
  FUN_141894910(param_1 + 0xa0,auStack_f8);
  if (puStack_30 != (undefined1 *)0x0) {
    FUN_140e289f0();
  }
  uStack_50 = 0;
  if (lStack_58 != 0) {
    FUN_140e289f0();
  }
  FUN_1481f4540(auStack_98);
  FUN_1481f4850(auStack_e8);
  FUN_14b9fb8d0(uStack_18 ^ (ulonglong)auStack_118);
  return;
}

