// Selected newer-build routine; caller-supplied label: RollLootDrop_URoundManager
// Address: 0x14830d430
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: RollLootDrop_URoundManager */

undefined2 *
FUN_14830d430(longlong param_1,undefined2 *param_2,undefined8 *param_3,longlong *param_4,
             char param_5,byte param_6,char param_7,char param_8,char param_9,char param_10)

{
  byte *pbVar1;
  byte *pbVar2;
  undefined4 *puVar3;
  float fVar4;
  byte bVar5;
  undefined1 uVar6;
  int iVar7;
  code *pcVar8;
  ulonglong uVar9;
  char cVar10;
  int iVar11;
  uint uVar12;
  undefined2 *puVar13;
  longlong lVar14;
  byte *pbVar15;
  undefined *puVar16;
  longlong lVar17;
  undefined4 *puVar18;
  byte *pbVar19;
  longlong *plVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  undefined8 unaff_retaddr;
  undefined1 auStack_b8 [4];
  float fStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 *puStack_a8;
  undefined8 uStack_a0;
  undefined4 **ppuStack_98;
  float *pfStack_90;
  
  *(undefined2 *)((longlong)param_2 + 1) = 0x1608;
  *(undefined1 *)param_2 = 0;
  *(undefined4 *)(param_2 + 2) = *(undefined4 *)(param_1 + 0x218);
  if (param_9 != '\0') {
    if (DAT_14edc6208 < 5) {
      return param_2;
    }
    puVar16 = &UNK_14d219ea8;
    goto LAB_14830d9ef;
  }
  if (*(longlong *)(param_1 + 0x208) != 0) {
    iVar7 = *(int *)(param_3 + 1);
    if (iVar7 != 0) {
      puStack_a8 = (undefined4 *)0x0;
      uStack_a0 = 0;
      fStack_b4 = 0.0;
      pbVar19 = (byte *)*param_3;
      pbVar1 = pbVar19 + iVar7;
      while( true ) {
        if (*(int *)(param_3 + 1) != iVar7) {
          param_9 = '\0';
          cVar10 = FUN_14be5bab0(&param_9);
          if (cVar10 != '\0') {
            pcVar8 = (code *)swi(3);
            puVar13 = (undefined2 *)(*pcVar8)();
            return puVar13;
          }
        }
        if (pbVar19 == pbVar1) break;
        bVar5 = *pbVar19;
        if ((bVar5 != 8) && (lVar14 = FUN_1482df780(param_1,bVar5), lVar14 != 0)) {
          if ((int)param_4[1] != *(int *)((longlong)param_4 + 0x34)) {
            plVar20 = param_4 + 7;
            if ((longlong *)param_4[8] != (longlong *)0x0) {
              plVar20 = (longlong *)param_4[8];
            }
            iVar11 = *(int *)((longlong)plVar20 +
                             ((ulonglong)((int)param_4[9] - 1) & (ulonglong)bVar5) * 4);
            if (iVar11 != -1) {
              do {
                pbVar2 = (byte *)(*param_4 + (longlong)iVar11 * 0x18);
                if (*pbVar2 == bVar5) {
                  pbVar15 = pbVar2 + 4;
                  if (pbVar2 == (byte *)0x0) {
                    pbVar15 = (byte *)0x0;
                  }
                  if ((pbVar15 != (byte *)0x0) &&
                     ((int)((uint)param_6 + *(int *)(lVar14 + 0x130)) <= *(int *)(pbVar15 + 8)))
                  goto LAB_14830d669;
                  break;
                }
                iVar11 = *(int *)(pbVar2 + 0x10);
              } while (iVar11 != -1);
            }
          }
          uStack_b0 = CONCAT31(uStack_b0._1_3_,bVar5);
          uStack_ac = *(undefined4 *)(lVar14 + 0x15c);
          if (puStack_a8 <= &uStack_b0) {
            if (&uStack_b0 < puStack_a8 + (longlong)(int)uStack_a0._4_4_ * 2) {
              cVar10 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,
                                     &UNK_14bf25f80,&uStack_b0,puStack_a8,
                                     (longlong)(int)uStack_a0._4_4_,(longlong)(int)uStack_a0,8);
              if (cVar10 != '\0') {
                pcVar8 = (code *)swi(3);
                puVar13 = (undefined2 *)(*pcVar8)();
                return puVar13;
              }
            }
          }
          uVar9 = uStack_a0;
          lVar17 = (longlong)(int)uStack_a0;
          uVar12 = (int)uStack_a0 + 1;
          uStack_a0 = CONCAT44(uStack_a0._4_4_,uVar12);
          if (uStack_a0._4_4_ < uVar12) {
            FUN_14830acb0(&puStack_a8,uVar9 & 0xffffffff);
          }
          *(ulonglong *)(puStack_a8 + lVar17 * 2) = CONCAT44(uStack_ac,uStack_b0);
          fStack_b4 = fStack_b4 + *(float *)(lVar14 + 0x15c);
        }
LAB_14830d669:
        pbVar19 = pbVar19 + 1;
      }
      if ((int)uStack_a0 == 0) {
        if (4 < DAT_14edc6208) {
          FUN_140f252a0(&DAT_14edc6208,&UNK_14d21a010,*(undefined4 *)(param_1 + 0x218));
        }
        goto LAB_14830d97a;
      }
      ppuStack_98 = &puStack_a8;
      pfStack_90 = &fStack_b4;
      fVar24 = _DAT_14bf3cd58;
      if (param_5 == '\0') {
        fVar22 = _DAT_14bf2ebec;
        if (param_7 != '\0') {
          fVar22 = 0.0;
          goto LAB_14830d6f7;
        }
      }
      else {
        fVar22 = _DAT_14bf56a24;
        if (param_7 == '\0') {
          fVar24 = 0.0;
        }
LAB_14830d6f7:
        fVar22 = fVar24 + fVar22;
      }
      if ((_DAT_14bf569c8 < (float)((uint)(fVar22 - _DAT_14bf2ebec) & _DAT_14bf56a80)) &&
         (FUN_1482d21a0(&ppuStack_98,fVar22 * fStack_b4), 4 < DAT_14edc6208)) {
        FUN_140f252a0(&DAT_14edc6208,&UNK_14d21a0d8,(double)fVar22,(double)fStack_b4);
      }
      if ((param_8 != '\0') &&
         (FUN_1482d21a0(&ppuStack_98,fStack_b4 - _DAT_14bfb66c0), 4 < DAT_14edc6208)) {
        FUN_140f252a0(&DAT_14edc6208,&UNK_14d21a1b0,(double)fStack_b4);
      }
      fVar24 = _DAT_14bf56a6c;
      if ((_DAT_14bf56a6c < fStack_b4) &&
         (FUN_1482d21a0(&ppuStack_98,_DAT_14bf56a6c), 2 < DAT_14edc6208)) {
        FUN_140f252a0(&DAT_14edc6208,&UNK_14d21a258);
      }
      fVar22 = 0.0;
      if ((param_10 != '\0') && (0.0 < fStack_b4)) {
        fVar22 = *(float *)(param_1 + 0x21c);
        if (fVar24 <= *(float *)(param_1 + 0x21c)) {
          fVar22 = fVar24;
        }
        if (fVar22 <= 0.0) {
          fVar22 = 0.0;
        }
        if (fStack_b4 <= fVar22) {
          fVar22 = fStack_b4;
        }
        FUN_1482d21a0(&ppuStack_98,0);
        if (4 < DAT_14edc6208) {
          FUN_140f252a0(&DAT_14edc6208,&UNK_14d21a308,(double)fVar22);
        }
      }
      fVar24 = (fVar24 - fStack_b4) - fVar22;
      if (fVar24 <= 0.0) {
        fVar24 = 0.0;
      }
      uVar12 = rand();
      fVar23 = (float)(uVar12 & 0x7fff) * _DAT_14c291cb0;
      fVar21 = 0.0;
      iVar7 = (int)uStack_a0;
      puVar3 = puStack_a8 + (longlong)(int)uStack_a0 * 2;
      puVar18 = puStack_a8;
      while( true ) {
        if ((int)uStack_a0 != iVar7) {
          auStack_b8[0] = 0;
          cVar10 = FUN_14be5be20(auStack_b8);
          if (cVar10 != '\0') {
            pcVar8 = (code *)swi(3);
            puVar13 = (undefined2 *)(*pcVar8)();
            return puVar13;
          }
        }
        if (puVar18 == puVar3) {
          if ((fVar22 <= 0.0) || (fVar21 + fVar22 < fVar23)) {
            if (4 < DAT_14edc6208) {
              FUN_140f252a0(&DAT_14edc6208,&UNK_14d21a608,(double)fVar23,
                            *(undefined4 *)(param_1 + 0x218),(double)fVar24);
            }
            if (puStack_a8 == (undefined4 *)0x0) {
              return param_2;
            }
            FUN_140e289f0();
            return param_2;
          }
          *param_2 = 0x806;
          *(undefined4 *)(param_2 + 2) = 1;
          if (4 < DAT_14edc6208) {
            FUN_140f252a0(&DAT_14edc6208,&UNK_14d21a530,(double)fVar23,(double)fVar22,(double)fVar24
                         );
          }
          goto LAB_14830d97a;
        }
        fVar4 = (float)puVar18[1];
        fVar21 = fVar21 + fVar4;
        if ((0.0 < fVar4) && (fVar23 <= fVar21)) break;
        puVar18 = puVar18 + 2;
      }
      *(undefined1 *)param_2 = 4;
      uVar6 = *(undefined1 *)puVar18;
      *(undefined1 *)((longlong)param_2 + 1) = uVar6;
      *(undefined4 *)(param_2 + 2) = 1;
      if (4 < DAT_14edc6208) {
        FUN_140f252a0(&DAT_14edc6208,&UNK_14d21a3f8,(double)fVar23,uVar6,(double)fVar4,
                      (double)fVar22,(double)fVar24);
      }
LAB_14830d97a:
      if (puStack_a8 == (undefined4 *)0x0) {
        return param_2;
      }
      FUN_140e289f0();
      return param_2;
    }
  }
  if (DAT_14edc6208 < 5) {
    return param_2;
  }
  puVar16 = &UNK_14d219f60;
LAB_14830d9ef:
  FUN_140f252a0(&DAT_14edc6208,puVar16);
  return param_2;
}

