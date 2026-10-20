// Selected newer-build routine; caller-supplied label: GenerateModifiersForRound_URoundManager
// Address: 0x1482e0ad0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: GenerateModifiersForRound_URoundManager */

longlong * FUN_1482e0ad0(longlong param_1,longlong *param_2,int param_3,undefined1 param_4)

{
  longlong **pplVar1;
  undefined1 auVar2 [16];
  code *pcVar3;
  float fVar4;
  undefined4 uVar5;
  char cVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  longlong lVar10;
  longlong *plVar11;
  int iVar12;
  ulonglong uVar13;
  longlong *plVar14;
  longlong **pplVar15;
  longlong *plVar16;
  longlong lVar17;
  int iVar18;
  longlong *plVar19;
  longlong lVar20;
  bool bVar21;
  float fVar22;
  float fVar23;
  undefined8 unaff_retaddr;
  undefined1 auStackX_8 [8];
  longlong *plStackX_10;
  longlong *plStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 uStack_b7;
  undefined1 auStack_b6 [6];
  longlong *plStack_b0;
  undefined8 uStack_a8;
  undefined4 uStack_a0;
  int iStack_9c;
  int iStack_98;
  longlong lStack_90;
  int iStack_88;
  longlong *plStack_80;
  
  *param_2 = 0;
  param_2[1] = 0;
  fVar22 = _DAT_14bf56a6c;
  uStack_a0 = 1;
  if (*(char *)(param_1 + 0x1d0) != '\0') {
    fVar23 = 0.0;
    plStack_c8 = (longlong *)0x0;
    uStack_c0 = 0;
    plStackX_10 = param_2;
    lVar10 = FUN_1482f85c0(param_1,param_3);
    pplVar1 = (longlong **)(param_1 + 0x1c0);
    if (lVar10 == 0) {
      iVar12 = (param_3 + -1) / 2;
      iVar18 = 2;
      if (iVar12 < 2) {
        iVar18 = iVar12;
      }
      iStack_98 = 0;
      if (0 < iVar18) {
        iStack_98 = iVar18;
      }
      iVar18 = 3;
      if (param_3 / 2 < 3) {
        iVar18 = param_3 / 2;
      }
      iStack_9c = 0;
      if (0 < iVar18) {
        iStack_9c = iVar18;
      }
      plVar11 = plStack_c8;
      uVar13 = uStack_c0;
      iVar18 = (int)uStack_c0;
      if (&plStack_c8 != pplVar1) {
        for (; uStack_c0 = uVar13, iVar18 != 0; iVar18 = iVar18 + -1) {
          if (*plVar11 != 0) {
            FUN_140e289f0();
          }
          plVar11 = plVar11 + 2;
          uVar13 = uStack_c0;
        }
        uStack_c0._4_4_ = (undefined4)(uVar13 >> 0x20);
        uVar5 = uStack_c0._4_4_;
        FUN_140c64d10(&plStack_c8,*pplVar1,*(undefined4 *)(param_1 + 0x1c8),uVar5);
      }
    }
    else {
      iStack_98 = *(int *)(lVar10 + 0x28);
      iStack_9c = *(int *)(lVar10 + 0x2c);
      fVar22 = *(float *)(lVar10 + 0x30);
      fVar23 = *(float *)(lVar10 + 0x34);
      pplVar15 = (longlong **)(lVar10 + 0x38);
      if (*(int *)(lVar10 + 0x40) < 1) {
        pplVar15 = pplVar1;
      }
      plVar11 = plStack_c8;
      uVar13 = uStack_c0;
      iVar18 = (int)uStack_c0;
      if (&plStack_c8 != pplVar15) {
        for (; uStack_c0 = uVar13, iVar18 != 0; iVar18 = iVar18 + -1) {
          if (*plVar11 != 0) {
            FUN_140e289f0();
          }
          plVar11 = plVar11 + 2;
          uVar13 = uStack_c0;
        }
        uStack_c0._4_4_ = (undefined4)(uVar13 >> 0x20);
        uVar5 = uStack_c0._4_4_;
        FUN_140c64d10(&plStack_c8,*pplVar15,*(undefined4 *)(pplVar15 + 1),uVar5);
      }
    }
    plStack_b0 = (longlong *)0x0;
    uStack_a8 = 0;
    uVar13 = uStack_c0 & 0xffffffff;
    if ((int)uStack_c0 < 0) {
      FUN_140d15600(uVar13);
      pcVar3 = (code *)swi(3);
      plVar11 = (longlong *)(*pcVar3)();
      return plVar11;
    }
    if (0 < (int)uStack_c0) {
      FUN_140d24a90(&plStack_b0,uVar13);
      uVar13 = uStack_c0 & 0xffffffff;
    }
    iVar18 = (int)uVar13;
    plVar19 = plStack_c8 + (longlong)iVar18 * 2;
    plVar11 = plStack_c8;
    while( true ) {
      if ((int)uVar13 != iVar18) {
        auStackX_8[0] = 0;
        cVar6 = FUN_14bd21c30(auStackX_8);
        if (cVar6 != '\0') {
          pcVar3 = (code *)swi(3);
          plVar11 = (longlong *)(*pcVar3)();
          return plVar11;
        }
        uVar13 = uStack_c0 & 0xffffffff;
      }
      param_2 = plStackX_10;
      if (plVar11 == plVar19) break;
      FUN_140d30dc0(plVar11,&lStack_90);
      if (1 < iStack_88) {
        iVar12 = (int)uStack_a8;
        plVar16 = plStack_b0 + (longlong)(int)uStack_a8 * 2;
        plVar14 = plStack_b0;
        while( true ) {
          if ((int)uStack_a8 != iVar12) {
            uStack_b8 = 0;
            cVar6 = FUN_14bd21c30(&uStack_b8);
            if (cVar6 != '\0') {
              pcVar3 = (code *)swi(3);
              plVar11 = (longlong *)(*pcVar3)();
              return plVar11;
            }
          }
          if (plVar14 == plVar16) break;
          iVar7 = (int)plVar14[1];
          if (iVar7 == iStack_88) {
            if (iVar7 < 2) goto LAB_1482e0e10;
            iVar7 = func_0x000140d80e70(*plVar14,lStack_90);
            bVar21 = iVar7 == 0;
          }
          else {
            bVar21 = iVar7 + iStack_88 == 1;
          }
          if (bVar21) goto LAB_1482e0e10;
          plVar14 = plVar14 + 2;
        }
        if (plStack_b0 <= &lStack_90) {
          if (&lStack_90 < plStack_b0 + (longlong)(int)uStack_a8._4_4_ * 2) {
            cVar6 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                                  &lStack_90,plStack_b0,(longlong)(int)uStack_a8._4_4_,
                                  (longlong)(int)uStack_a8,0x10);
            if (cVar6 != '\0') {
              pcVar3 = (code *)swi(3);
              plVar11 = (longlong *)(*pcVar3)();
              return plVar11;
            }
          }
        }
        uVar13 = uStack_a8;
        lVar10 = (longlong)(int)uStack_a8;
        uVar8 = (int)uStack_a8 + 1;
        uStack_a8 = CONCAT44(uStack_a8._4_4_,uVar8);
        if (uStack_a8._4_4_ < uVar8) {
          FUN_140ca5230(&plStack_b0,uVar13 & 0xffffffff);
        }
        lVar17 = lStack_90;
        plVar14 = plStack_b0 + lVar10 * 2;
        *plVar14 = 0;
        *(int *)(plVar14 + 1) = iStack_88;
        plStack_80 = plVar14;
        if (iStack_88 == 0) {
          *(undefined4 *)((longlong)plVar14 + 0xc) = 0;
        }
        else {
          FUN_140ca40a0(plVar14,iStack_88,0);
          func_0x00014ba120de(*plVar14,lVar17);
        }
      }
LAB_1482e0e10:
      if (lStack_90 != 0) {
        FUN_140e289f0();
      }
      plVar11 = plVar11 + 2;
      uVar13 = uStack_c0 & 0xffffffff;
    }
    uVar8 = (uint)uVar13;
    plVar11 = plStack_c8;
    while (uVar8 != 0) {
      if (*plVar11 != 0) {
        FUN_140e289f0();
      }
      plVar11 = plVar11 + 2;
      uVar8 = (int)uVar13 - 1;
      uVar13 = (ulonglong)uVar8;
    }
    uStack_c0._4_4_ = (undefined4)(uStack_c0 >> 0x20);
    uVar5 = uStack_c0._4_4_;
    FUN_140c64d10(&plStack_c8,plStack_b0,uStack_a8 & 0xffffffff,uVar5);
    uVar8 = (int)uStack_c0 - 1;
    if (-1 < (int)uVar8) {
      lVar20 = (longlong)(int)uVar8;
      lVar17 = lVar20 << 4;
      lVar10 = (longlong)(int)uStack_c0 << 4;
      do {
        uVar9 = 0;
        if ((int)uVar8 < (int)uStack_c0) {
          uVar9 = ~uVar8 >> 0x1f;
        }
        if ((uVar9 == 0) &&
           (cVar6 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,&UNK_14bf260f0,
                                  lVar20,(longlong)(int)uStack_c0), cVar6 != '\0')) {
          pcVar3 = (code *)swi(3);
          plVar11 = (longlong *)(*pcVar3)();
          return plVar11;
        }
        cVar6 = FUN_1482fcc80((longlong)plStack_c8 + lVar17,param_4);
        if (cVar6 == '\0') {
          if (*(longlong *)(lVar17 + (longlong)plStack_c8) != 0) {
            FUN_140e289f0();
          }
          iVar18 = ((int)uStack_c0 - uVar8) + -1;
          if (iVar18 != 0) {
            func_0x00014ba120ea(lVar17 + (longlong)plStack_c8,lVar10 + (longlong)plStack_c8,
                                (longlong)iVar18 << 4);
          }
          uStack_c0 = CONCAT44(uStack_c0._4_4_,(int)uStack_c0 + -1);
          FUN_140d78a80(&plStack_c8);
        }
        lVar20 = lVar20 + -1;
        lVar17 = lVar17 + -0x10;
        lVar10 = lVar10 + -0x10;
        uVar8 = uVar8 - 1;
      } while (-1 < (int)uVar8);
    }
    fVar4 = _DAT_14bf3cd14;
    if ((int)uStack_c0 == 0) {
      uStack_a0 = 0;
      plVar11 = plStack_b0;
      for (iVar18 = (int)uStack_a8; iVar18 != 0; iVar18 = iVar18 + -1) {
        if (*plVar11 != 0) {
          FUN_140e289f0();
        }
        plVar11 = plVar11 + 2;
      }
      if (plStack_b0 != (longlong *)0x0) {
        FUN_140e289f0(plStack_b0);
      }
      plVar11 = plStack_c8;
      for (iVar18 = (int)uStack_c0; iVar18 != 0; iVar18 = iVar18 + -1) {
        if (*plVar11 != 0) {
          FUN_140e289f0();
        }
        plVar11 = plVar11 + 2;
      }
    }
    else {
      if (fVar22 <= 0.0) {
        fVar22 = 0.0;
      }
      if (fVar23 <= 0.0) {
        fVar23 = 0.0;
      }
      if (0.0 < fVar23 + fVar22) {
        if ((fVar23 <= 0.0) ||
           (uVar8 = rand(), fVar23 <= (float)(uVar8 & 0x7fff) * fVar4 * (fVar23 + fVar22))) {
          iVar18 = iStack_98;
          iVar12 = iStack_9c;
          if (iStack_9c < iStack_98) {
            iVar18 = iStack_9c;
            iVar12 = iStack_98;
          }
          iVar7 = (int)uStack_c0;
          if (iVar18 < (int)uStack_c0) {
            iVar7 = iVar18;
          }
          iVar18 = 0;
          if (0 < iVar7) {
            iVar18 = iVar7;
          }
          iVar7 = (int)uStack_c0;
          if (iVar12 < (int)uStack_c0) {
            iVar7 = iVar12;
          }
          iVar12 = iVar18;
          if (iVar18 < iVar7) {
            iVar12 = iVar7;
          }
          iVar12 = iVar12 - iVar18;
          if (iVar12 + 1 < 1) {
            iVar12 = 0;
          }
          else {
            uVar8 = rand();
            iVar7 = (int)((float)(uVar8 & 0x7fff) * (float)(iVar12 + 1) * fVar4);
            if (iVar7 < iVar12) {
              iVar12 = iVar7;
            }
          }
          iStack_9c = iVar12 + iVar18;
          iVar18 = (int)uStack_c0 + -1;
          if (0 < iVar18) {
            lVar10 = (longlong)iVar18 << 4;
            do {
              if (iVar18 + 1 < 1) {
                iVar12 = 0;
              }
              else {
                uVar8 = rand();
                iVar7 = (int)((float)(uVar8 & 0x7fff) * (float)(iVar18 + 1) * fVar4);
                iVar12 = iVar18;
                if (iVar7 < iVar18) {
                  iVar12 = iVar7;
                }
                if ((iVar12 < 0) &&
                   (cVar6 = FUN_140f8e6d0(&UNK_14bf3c4e0,&UNK_14d166cc0,0xab4,unaff_retaddr,
                                          &UNK_14bf24094), cVar6 != '\0')) {
                  pcVar3 = (code *)swi(3);
                  plVar11 = (longlong *)(*pcVar3)();
                  return plVar11;
                }
              }
              if ((((int)uStack_c0 <= iVar18) || ((int)uStack_c0 <= iVar12)) &&
                 (cVar6 = FUN_140f8e6d0(&UNK_14bf3c520,&UNK_14d166cc0,0xab5,unaff_retaddr,
                                        &UNK_14bf24094), cVar6 != '\0')) {
                pcVar3 = (code *)swi(3);
                plVar11 = (longlong *)(*pcVar3)();
                return plVar11;
              }
              if (iVar18 != iVar12) {
                auVar2 = *(undefined1 (*) [16])(lVar10 + (longlong)plStack_c8);
                *(undefined1 (*) [16])(lVar10 + (longlong)plStack_c8) =
                     *(undefined1 (*) [16])(plStack_c8 + (longlong)iVar12 * 2);
                *(undefined1 (*) [16])(plStack_c8 + (longlong)iVar12 * 2) = auVar2;
              }
              iVar18 = iVar18 + -1;
              lVar10 = lVar10 + -0x10;
            } while (0 < iVar18);
          }
          iVar18 = (int)uStack_c0;
          plVar19 = plStack_c8 + (longlong)(int)uStack_c0 * 2;
          plVar11 = plStack_c8;
          while( true ) {
            if ((int)uStack_c0 != iVar18) {
              uStack_b7 = 0;
              cVar6 = FUN_14bd21c30(&uStack_b7);
              if (cVar6 != '\0') {
                pcVar3 = (code *)swi(3);
                plVar11 = (longlong *)(*pcVar3)();
                return plVar11;
              }
            }
            if (plVar11 == plVar19) break;
            lVar10 = *param_2;
            lVar17 = param_2[1];
            lVar20 = (longlong)(int)lVar17 * 0x10 + lVar10;
            while( true ) {
              if ((int)param_2[1] != (int)lVar17) {
                auStack_b6[0] = 0;
                cVar6 = FUN_14bd21c30(auStack_b6);
                if (cVar6 != '\0') {
                  pcVar3 = (code *)swi(3);
                  plVar11 = (longlong *)(*pcVar3)();
                  return plVar11;
                }
              }
              if (lVar10 == lVar20) break;
              cVar6 = FUN_1482d50a0(plVar11,lVar10);
              if (cVar6 != '\0') goto LAB_1482e1378;
              lVar10 = lVar10 + 0x10;
            }
            plVar14 = (longlong *)*param_2;
            if (((plVar14 <= plVar11) &&
                (plVar11 < plVar14 + (longlong)*(int *)((longlong)param_2 + 0xc) * 2)) &&
               (cVar6 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,
                                      &UNK_14bf25f80,plVar11,plVar14,
                                      (longlong)*(int *)((longlong)param_2 + 0xc),
                                      (longlong)(int)param_2[1],0x10), cVar6 != '\0')) {
              pcVar3 = (code *)swi(3);
              plVar11 = (longlong *)(*pcVar3)();
              return plVar11;
            }
            iVar12 = (int)param_2[1];
            *(uint *)(param_2 + 1) = iVar12 + 1U;
            if (*(uint *)((longlong)param_2 + 0xc) < iVar12 + 1U) {
              FUN_140ca5230(param_2,iVar12);
            }
            plVar14 = (longlong *)((longlong)iVar12 * 0x10 + *param_2);
            *plVar14 = 0;
            iVar12 = (int)plVar11[1];
            lVar10 = *plVar11;
            *(int *)(plVar14 + 1) = iVar12;
            plStack_80 = plVar14;
            if (iVar12 == 0) {
              *(undefined4 *)((longlong)plVar14 + 0xc) = 0;
            }
            else {
              FUN_140ca40a0(plVar14,iVar12,0);
              func_0x00014ba120de(*plVar14,lVar10);
            }
            if (iStack_9c <= (int)param_2[1]) break;
LAB_1482e1378:
            plVar11 = plVar11 + 2;
          }
          uStack_a0 = 0;
          plVar11 = plStack_b0;
          for (iVar18 = (int)uStack_a8; iVar18 != 0; iVar18 = iVar18 + -1) {
            if (*plVar11 != 0) {
              FUN_140e289f0();
            }
            plVar11 = plVar11 + 2;
          }
          if (plStack_b0 != (longlong *)0x0) {
            FUN_140e289f0(plStack_b0);
          }
          plVar11 = plStack_c8;
          for (iVar18 = (int)uStack_c0; iVar18 != 0; iVar18 = iVar18 + -1) {
            if (*plVar11 != 0) {
              FUN_140e289f0();
            }
            plVar11 = plVar11 + 2;
          }
        }
        else {
          uStack_a0 = 0;
          plVar11 = plStack_b0;
          for (iVar18 = (int)uStack_a8; iVar18 != 0; iVar18 = iVar18 + -1) {
            if (*plVar11 != 0) {
              FUN_140e289f0();
            }
            plVar11 = plVar11 + 2;
          }
          if (plStack_b0 != (longlong *)0x0) {
            FUN_140e289f0(plStack_b0);
          }
          plVar11 = plStack_c8;
          for (iVar18 = (int)uStack_c0; iVar18 != 0; iVar18 = iVar18 + -1) {
            if (*plVar11 != 0) {
              FUN_140e289f0();
            }
            plVar11 = plVar11 + 2;
          }
        }
      }
      else {
        uStack_a0 = 0;
        plVar11 = plStack_b0;
        for (iVar18 = (int)uStack_a8; iVar18 != 0; iVar18 = iVar18 + -1) {
          if (*plVar11 != 0) {
            FUN_140e289f0();
          }
          plVar11 = plVar11 + 2;
        }
        if (plStack_b0 != (longlong *)0x0) {
          FUN_140e289f0(plStack_b0);
        }
        plVar11 = plStack_c8;
        for (iVar18 = (int)uStack_c0; iVar18 != 0; iVar18 = iVar18 + -1) {
          if (*plVar11 != 0) {
            FUN_140e289f0();
          }
          plVar11 = plVar11 + 2;
        }
      }
    }
    if (plStack_c8 != (longlong *)0x0) {
      FUN_140e289f0(plStack_c8);
    }
  }
  return param_2;
}

