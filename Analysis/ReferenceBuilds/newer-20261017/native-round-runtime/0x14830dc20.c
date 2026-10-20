// Selected newer-build routine; caller-supplied label: RollSpoilsOfSinLootDrop_URoundManager
// Address: 0x14830dc20
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: RollSpoilsOfSinLootDrop_URoundManager */

undefined1 *
FUN_14830dc20(longlong param_1,undefined1 *param_2,undefined8 *param_3,longlong *param_4,
             byte param_5)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  code *pcVar4;
  ulonglong uVar5;
  char cVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined1 *puVar10;
  longlong lVar11;
  byte *pbVar12;
  uint uVar13;
  byte *pbVar14;
  byte *pbVar15;
  longlong *plVar16;
  undefined8 unaff_retaddr;
  undefined1 auStackX_18 [8];
  byte abStack_58 [8];
  byte *pbStack_50;
  byte *pbStack_48;
  undefined8 uStack_40;
  
  *(undefined2 *)(param_2 + 1) = 0x1608;
  *param_2 = 0;
  *(undefined4 *)(param_2 + 4) = *(undefined4 *)(param_1 + 0x218);
  iVar3 = *(int *)(param_3 + 1);
  if (iVar3 == 0) {
    if (4 < DAT_14edc6208) {
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d21a6d0);
    }
  }
  else {
    pbStack_48 = (byte *)0x0;
    uStack_40 = 0;
    pbVar15 = (byte *)*param_3;
    pbVar14 = pbVar15 + iVar3;
    pbStack_50 = pbVar14;
    while( true ) {
      if (*(int *)(param_3 + 1) != iVar3) {
        auStackX_18[0] = 0;
        cVar6 = FUN_14be5bab0(auStackX_18);
        if (cVar6 != '\0') {
          pcVar4 = (code *)swi(3);
          puVar10 = (undefined1 *)(*pcVar4)();
          return puVar10;
        }
      }
      if (pbVar15 == pbVar14) break;
      abStack_58[0] = *pbVar15;
      if ((abStack_58[0] != 8) && (lVar11 = FUN_1482df780(param_1), lVar11 != 0)) {
        if ((int)param_4[1] != *(int *)((longlong)param_4 + 0x34)) {
          plVar16 = param_4 + 7;
          if ((longlong *)param_4[8] != (longlong *)0x0) {
            plVar16 = (longlong *)param_4[8];
          }
          iVar7 = *(int *)((longlong)plVar16 +
                          ((ulonglong)((int)param_4[9] - 1) & (ulonglong)abStack_58[0]) * 4);
          if (iVar7 != -1) {
            do {
              pbVar1 = (byte *)(*param_4 + (longlong)iVar7 * 0x18);
              if (*pbVar1 == abStack_58[0]) {
                pbVar12 = pbVar1 + 4;
                if (pbVar1 == (byte *)0x0) {
                  pbVar12 = (byte *)0x0;
                }
                if ((pbVar12 != (byte *)0x0) &&
                   ((int)((uint)param_5 + *(int *)(lVar11 + 0x130)) <= *(int *)(pbVar12 + 8)))
                goto LAB_14830de09;
                break;
              }
              iVar7 = *(int *)(pbVar1 + 0x10);
            } while (iVar7 != -1);
          }
        }
        if (pbStack_48 <= abStack_58) {
          if (abStack_58 < pbStack_48 + (int)uStack_40._4_4_) {
            cVar6 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                                  abStack_58,pbStack_48,(longlong)(int)uStack_40._4_4_,
                                  (longlong)(int)uStack_40,1);
            if (cVar6 != '\0') {
              pcVar4 = (code *)swi(3);
              puVar10 = (undefined1 *)(*pcVar4)();
              return puVar10;
            }
          }
        }
        uVar5 = uStack_40;
        lVar11 = (longlong)(int)uStack_40;
        uVar8 = (int)uStack_40 + 1;
        uStack_40 = CONCAT44(uStack_40._4_4_,uVar8);
        if (uStack_40._4_4_ < uVar8) {
          FUN_14830b7f0(&pbStack_48,uVar5 & 0xffffffff);
        }
        pbStack_48[lVar11] = abStack_58[0];
        pbVar14 = pbStack_50;
      }
LAB_14830de09:
      pbVar15 = pbVar15 + 1;
    }
    iVar3 = (int)uStack_40;
    if ((int)uStack_40 == 0) {
      if (4 < DAT_14edc6208) {
        FUN_140f252a0(&DAT_14edc6208,&UNK_14d21a768,*(undefined4 *)(param_1 + 0x218));
      }
    }
    else {
      uVar13 = (int)uStack_40 - 1;
      uVar8 = 0;
      if (0 < (int)uStack_40) {
        uVar8 = rand();
        uVar9 = (uint)((float)(uVar8 & 0x7fff) * (float)iVar3 * _DAT_14bf3cd14);
        uVar8 = uVar13;
        if ((int)uVar9 < (int)uVar13) {
          uVar8 = uVar9;
        }
      }
      *param_2 = 4;
      uVar13 = 0;
      if ((int)uVar8 < (int)uStack_40) {
        uVar13 = ~uVar8 >> 0x1f;
      }
      if ((uVar13 == 0) &&
         (cVar6 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,&UNK_14bf260f0,
                                (longlong)(int)uVar8,(longlong)(int)uStack_40), cVar6 != '\0')) {
        pcVar4 = (code *)swi(3);
        puVar10 = (undefined1 *)(*pcVar4)();
        return puVar10;
      }
      bVar2 = pbStack_48[(int)uVar8];
      param_2[1] = bVar2;
      *(undefined4 *)(param_2 + 4) = 1;
      if (4 < DAT_14edc6208) {
        FUN_140f252a0(&DAT_14edc6208,&UNK_14d21a830,bVar2);
      }
    }
    if (pbStack_48 != (byte *)0x0) {
      FUN_140e289f0();
    }
  }
  return param_2;
}

