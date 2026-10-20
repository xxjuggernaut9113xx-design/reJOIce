// Selected newer-build routine; caller-supplied label: PickWeightedRewardCategory
// Address: 0x1482d1660
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: PickWeightedRewardCategory */

void FUN_1482d1660(longlong *param_1,undefined4 *param_2,undefined1 param_3)

{
  longlong lVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  code *pcVar4;
  int iVar5;
  longlong lVar6;
  char cVar7;
  char cVar8;
  uint uVar9;
  ulonglong uVar10;
  uint uVar11;
  undefined8 uVar12;
  longlong lVar13;
  char *pcVar14;
  char *pcVar15;
  float fVar16;
  undefined8 unaff_retaddr;
  undefined1 auStack_108 [32];
  undefined *puStack_e8;
  longlong lStack_e0;
  longlong lStack_d8;
  char cStack_c8;
  undefined1 uStack_c7;
  undefined1 uStack_c6;
  undefined1 uStack_c5;
  undefined1 auStack_c4 [4];
  longlong lStack_c0;
  ulonglong uStack_b8;
  uint uStack_b0;
  undefined8 *puStack_a8;
  longlong lStack_a0;
  longlong *plStack_98;
  char *pcStack_90;
  char *pcStack_88;
  longlong *plStack_80;
  char acStack_78 [8];
  ulonglong uStack_70;
  
  uStack_70 = _DAT_14ed716f8 ^ (ulonglong)auStack_108;
  lStack_c0 = 0;
  uStack_b8 = 0;
  lStack_a0 = *param_1;
  plStack_98 = &lStack_c0;
  plStack_80 = param_1;
  FUN_1482d1db0(&lStack_a0,1,*param_2);
  FUN_1482d1db0(&lStack_a0,2,param_2[1]);
  FUN_1482d1db0(&lStack_a0,3,param_2[2]);
  FUN_1482d1db0(&lStack_a0,4,param_2[3]);
  FUN_1482d1db0(&lStack_a0,5,param_2[4]);
  fVar16 = 0.0;
  iVar5 = (int)uStack_b8;
  lVar1 = lStack_c0 + (longlong)(int)uStack_b8 * 8;
  lVar13 = lStack_c0;
  while( true ) {
    if ((int)uStack_b8 != iVar5) {
      uStack_c7 = 0;
      cVar7 = FUN_14be5bf60(&uStack_c7);
      if (cVar7 != '\0') {
        pcVar4 = (code *)swi(3);
        (*pcVar4)();
        return;
      }
    }
    if (lVar13 == lVar1) break;
    fVar16 = fVar16 + *(float *)(lVar13 + 4);
    lVar13 = lVar13 + 8;
  }
  if (0.0 < fVar16) {
    uVar9 = rand();
    fVar16 = (float)(uVar9 & 0x7fff) * _DAT_14bf3cd14 * fVar16;
    iVar5 = (int)uStack_b8;
    uVar10 = (ulonglong)(int)uStack_b8;
    lVar1 = lStack_c0 + uVar10 * 8;
    lVar13 = lStack_c0;
    while( true ) {
      if ((int)uVar10 != iVar5) {
        auStack_c4[0] = 0;
        cVar7 = FUN_14be5bf60(auStack_c4);
        if (cVar7 != '\0') {
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
        uVar10 = uStack_b8 & 0xffffffff;
      }
      if (lVar13 == lVar1) break;
      fVar16 = fVar16 - *(float *)(lVar13 + 4);
      if (fVar16 <= 0.0) goto LAB_1482d19d0;
      lVar13 = lVar13 + 8;
    }
    iVar5 = (int)uVar10;
    uVar11 = iVar5 - 1;
    uVar9 = 0;
    if ((int)uVar11 < iVar5) {
      uVar9 = ~uVar11 >> 0x1f;
    }
    if (uVar9 == 0) {
      lStack_d8 = (longlong)iVar5;
      lStack_e0 = (longlong)(int)uVar11;
      puStack_e8 = &UNK_14bf260f0;
      cVar7 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr);
      if (cVar7 != '\0') {
        pcVar4 = (code *)swi(3);
        (*pcVar4)();
        return;
      }
    }
  }
  else {
    cVar7 = FUN_1482d1490(*param_1,param_3);
    if (cVar7 == '\0') {
      builtin_strncpy(acStack_78,"\x05\x03\x04\x02\x01",5);
      pcVar14 = acStack_78;
      cVar7 = '\x05';
      do {
        puVar2 = (undefined8 *)*param_1;
        cStack_c8 = cVar7;
        if (cVar7 != '\0') {
          switch(cVar7) {
          default:
            uVar12 = 0;
            break;
          case '\x02':
            uVar12 = 0x140000001;
            break;
          case '\x03':
            uVar12 = 0x140000003;
            break;
          case '\x04':
            uVar12 = 0x140000002;
            break;
          case '\x05':
            uVar12 = 0x140000005;
          }
          pcStack_90 = pcVar14;
          cVar8 = FUN_1482d2ce0(*puVar2,uVar12);
          if (cVar8 == '\0') {
            if ((cVar7 == '\x01') || (cVar7 == '\x02')) break;
            if (cVar7 == '\x03') {
              uVar12 = puVar2[3];
LAB_1482d18c6:
              cVar7 = FUN_1482d2e50(puVar2[2],uVar12);
            }
            else {
              if (cVar7 == '\x04') {
                uVar12 = puVar2[4];
                goto LAB_1482d18c6;
              }
              if (cVar7 != '\x05') goto LAB_1482d18de;
              puStack_a8 = (undefined8 *)puVar2[5];
              puVar2 = (undefined8 *)puVar2[6];
              pcVar15 = (char *)*puVar2;
              uStack_b0 = *(uint *)(puVar2 + 1);
              uVar10 = (ulonglong)(int)uStack_b0;
              pcVar14 = pcVar15 + uVar10;
              pcStack_88 = pcVar14;
              while( true ) {
                if (*(int *)(puVar2 + 1) != (int)uVar10) {
                  uStack_c6 = 0;
                  cVar7 = FUN_14be5bb00(&uStack_c6);
                  if (cVar7 != '\0') {
                    pcVar4 = (code *)swi(3);
                    (*pcVar4)();
                    return;
                  }
                }
                if (pcVar15 == pcVar14) break;
                cVar7 = *pcVar15;
                if (cVar7 != '\x16') {
                  plVar3 = *(longlong **)*puStack_a8;
                  lVar13 = *plVar3;
                  lVar6 = plVar3[1];
                  lVar1 = lVar13 + (longlong)(int)lVar6 * 8;
                  while( true ) {
                    if ((int)plVar3[1] != (int)lVar6) {
                      uStack_c5 = 0;
                      cVar8 = FUN_14be5bf10(&uStack_c5);
                      if (cVar8 != '\0') {
                        pcVar4 = (code *)swi(3);
                        (*pcVar4)();
                        return;
                      }
                    }
                    if (lVar13 == lVar1) {
                      cVar7 = '\x01';
                      pcVar14 = pcStack_90;
                      param_1 = plStack_80;
                      goto LAB_1482d18cf;
                    }
                    pcVar14 = pcStack_88;
                    if (*(char *)(lVar13 + 2) == cVar7) break;
                    lVar13 = lVar13 + 8;
                  }
                }
                pcVar15 = pcVar15 + 1;
                uVar10 = (ulonglong)uStack_b0;
              }
              cVar7 = '\0';
              pcVar14 = pcStack_90;
              param_1 = plStack_80;
            }
LAB_1482d18cf:
            if (cVar7 != '\0') break;
          }
        }
LAB_1482d18de:
        pcVar14 = pcVar14 + 1;
        pcStack_90 = pcVar14;
        if (pcVar14 == acStack_78 + 5) break;
        cVar7 = *pcVar14;
      } while( true );
    }
  }
LAB_1482d19d0:
  if (lStack_c0 != 0) {
    FUN_140e289f0();
  }
  FUN_14b9fb8d0(uStack_70 ^ (ulonglong)auStack_108);
  return;
}

