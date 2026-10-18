// Newer reference PDB symbol: Tick_UMusicModeManager
// Address: 0x148315ac0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Removing unreachable block (ram,0x000148316451) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Matched newer-build PDB public symbol: Tick_UMusicModeManager */

void FUN_148315ac0(longlong param_1,float param_2)

{
  double *pdVar1;
  ulonglong *puVar2;
  double *pdVar3;
  double dVar4;
  double dVar5;
  longlong lVar6;
  longlong lVar7;
  code *pcVar8;
  ulonglong uVar9;
  float fVar10;
  double dVar11;
  float fVar12;
  double dVar13;
  char cVar14;
  uint uVar15;
  int iVar16;
  longlong lVar17;
  undefined *puVar18;
  undefined8 uVar19;
  double *pdVar20;
  undefined *puVar21;
  char cVar22;
  uint uVar23;
  longlong lVar24;
  longlong *plVar25;
  double dVar26;
  double dVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  undefined4 uVar31;
  undefined4 uVar32;
  uint uVar33;
  undefined4 uVar34;
  undefined4 uVar35;
  undefined8 unaff_retaddr;
  undefined *puStack_168;
  int iStack_160;
  double dStack_158;
  double dStack_150;
  undefined1 uStack_148;
  double dStack_140;
  undefined8 uStack_138;
  double dStack_130;
  double dStack_128;
  double dStack_120;
  undefined4 uStack_118;
  double dStack_110;
  int iStack_108;
  undefined8 uStack_104;
  longlong lStack_f8;
  undefined8 uStack_f0;
  char cStack_e8;
  undefined4 uStack_e4;
  longlong *plStack_d8;
  int iStack_d0;
  
  fVar30 = _DAT_14bf569d0;
  fVar12 = _DAT_14bf3cd28;
  fVar10 = _DAT_14bf2ebec;
  if (*(char *)(param_1 + 0x541) == '\0') {
    if (*(char *)(param_1 + 0x5e0) != '\0') {
      if ((*(longlong *)(param_1 + 0x470) == 0) ||
         ((*(uint *)(*(longlong *)(param_1 + 0x470) + 8) & 0x60000000) != 0)) {
        *(undefined1 *)(param_1 + 0x5e0) = 0;
      }
      else {
        fVar28 = param_2 + *(float *)(param_1 + 0x5f0);
        *(float *)(param_1 + 0x5f0) = fVar28;
        fVar29 = *(float *)(param_1 + 0x5f4);
        if (*(float *)(param_1 + 0x5f4) <= fVar30) {
          fVar29 = fVar30;
        }
        fVar28 = fVar28 / fVar29;
        if (fVar10 <= fVar28) {
          fVar28 = fVar10;
        }
        if (fVar28 <= 0.0) {
          fVar28 = 0.0;
        }
        fVar29 = fVar28 + fVar28;
        if (fVar12 <= fVar28) {
          fVar28 = fVar10 - (fVar29 - fVar10);
          fVar29 = (fVar10 - fVar28 * fVar28) + fVar10;
        }
        else {
          fVar29 = fVar29 * fVar29;
        }
        *(float *)(param_1 + 0x5e4) =
             (*(float *)(param_1 + 0x5e8) - *(float *)(param_1 + 0x5ec)) * fVar29 * fVar12 +
             *(float *)(param_1 + 0x5ec);
        FUN_1467096e0(*(undefined8 *)(param_1 + 0x470));
        if (fVar10 <= fVar29 * fVar12) {
          *(undefined1 *)(param_1 + 0x5e0) = 0;
          *(float *)(param_1 + 0x5e4) = *(float *)(param_1 + 0x5e8);
          if (_DAT_14c4d1160 <= *(float *)(param_1 + 0x5e8)) {
            FUN_1467094f0(*(undefined8 *)(param_1 + 0x470),0);
          }
        }
      }
    }
    if (*(char *)(param_1 + 0x5f8) != '\0') {
      if ((*(longlong *)(param_1 + 0x470) == 0) ||
         ((*(uint *)(*(longlong *)(param_1 + 0x470) + 8) & 0x60000000) != 0)) {
        *(undefined1 *)(param_1 + 0x5f8) = 0;
      }
      else {
        param_2 = param_2 + *(float *)(param_1 + 0x608);
        *(float *)(param_1 + 0x608) = param_2;
        fVar28 = *(float *)(param_1 + 0x60c);
        if (*(float *)(param_1 + 0x60c) <= fVar30) {
          fVar28 = fVar30;
        }
        param_2 = param_2 / fVar28;
        if (fVar10 <= param_2) {
          param_2 = fVar10;
        }
        if (param_2 <= 0.0) {
          param_2 = 0.0;
        }
        fVar30 = param_2 + param_2;
        if (fVar12 <= param_2) {
          fVar30 = fVar10 - (fVar30 - fVar10);
          fVar30 = (fVar10 - fVar30 * fVar30) + fVar10;
        }
        else {
          fVar30 = fVar30 * fVar30;
        }
        *(float *)(param_1 + 0x5fc) =
             (*(float *)(param_1 + 0x600) - *(float *)(param_1 + 0x604)) * fVar30 * fVar12 +
             *(float *)(param_1 + 0x604);
        FUN_14670a9a0(*(undefined8 *)(param_1 + 0x470));
        if (fVar10 <= fVar30 * fVar12) {
          *(undefined1 *)(param_1 + 0x5f8) = 0;
          *(undefined4 *)(param_1 + 0x5fc) = *(undefined4 *)(param_1 + 0x600);
          FUN_14670a9a0(*(undefined8 *)(param_1 + 0x470));
        }
      }
    }
    if ((*(char *)(param_1 + 0x540) != '\0') && (*(longlong *)(param_1 + 0x488) != 0)) {
      dVar26 = (double)FUN_1482e9b40(param_1 + -0x28);
      FUN_1482decf0(param_1 + -0x28,dVar26);
      dVar13 = _DAT_14bf56a40;
      dVar11 = _DAT_14bf2ec00;
      dVar5 = _DAT_14bf2ebf8;
      if (*(char *)(param_1 + 0x542) == '\0') {
        uVar33 = (uint)_DAT_14bf56a90;
        uVar9 = (ulonglong)_DAT_14bf56a90 >> 0x20;
        uVar34 = (undefined4)_DAT_14bf683b8;
        uVar35 = (undefined4)((ulonglong)_DAT_14bf683b8 >> 0x20);
        do {
          uVar23 = *(uint *)(param_1 + 0x688);
          lVar24 = (longlong)(int)uVar23;
          if (*(int *)(param_1 + 0x280) <= (int)uVar23) break;
          uVar15 = 0;
          if ((int)uVar23 < *(int *)(param_1 + 0x280)) {
            uVar15 = ~uVar23 >> 0x1f;
          }
          if ((uVar15 == 0) &&
             (cVar14 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                     &UNK_14bf260f0,lVar24,(longlong)*(int *)(param_1 + 0x280)),
             cVar14 != '\0')) {
            pcVar8 = (code *)swi(3);
            (*pcVar8)();
            return;
          }
          lVar6 = *(longlong *)(param_1 + 0x278);
          dVar4 = *(double *)(lVar6 + lVar24 * 0x18);
          if (dVar26 + *(double *)(param_1 + 0x690) < dVar4) break;
          cVar22 = '\0';
          uVar23 = *(uint *)(param_1 + 0x6d0);
          cVar14 = '\0';
          if ((int)uVar23 < *(int *)(param_1 + 0x290)) {
            do {
              cVar22 = cVar14;
              uVar15 = 0;
              if ((int)uVar23 < *(int *)(param_1 + 0x290)) {
                uVar15 = ~uVar23 >> 0x1f;
              }
              if ((uVar15 == 0) &&
                 (cVar14 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                         &UNK_14bf260f0,(longlong)(int)uVar23,
                                         (longlong)*(int *)(param_1 + 0x290)), cVar14 != '\0')) {
                pcVar8 = (code *)swi(3);
                (*pcVar8)();
                return;
              }
              lVar17 = (longlong)(int)uVar23;
              lVar7 = *(longlong *)(param_1 + 0x288);
              dVar27 = *(double *)(lVar7 + lVar17 * 0x28);
              if (dVar4 < dVar27) break;
              cVar14 = *(char *)(lVar7 + 8 + lVar17 * 0x28);
              if (cVar14 == '\0') {
                FUN_140cf99e0(param_1 + 0x6c0,lVar7 + 0x10 + lVar17 * 0x28);
              }
              else if ((cVar14 == '\x05') &&
                      (dVar27 = dVar27 - dVar4,
                      (double)CONCAT44((uint)((ulonglong)dVar27 >> 0x20) & (uint)uVar9,
                                       SUB84(dVar27,0) & uVar33) < dVar5)) {
                cVar22 = '\x01';
              }
              uVar23 = *(int *)(param_1 + 0x6d0) + 1;
              *(uint *)(param_1 + 0x6d0) = uVar23;
              cVar14 = cVar22;
            } while ((int)uVar23 < *(int *)(param_1 + 0x290));
          }
          if (*(char *)(lVar6 + 8 + lVar24 * 0x18) != '\x01') {
            dStack_110 = 0.0;
            uStack_104 = 0x3f800000;
            lStack_f8 = 0;
            uStack_f0 = 0;
            cStack_e8 = 1;
            uStack_e4 = 0;
            dStack_120 = dVar4 + *(double *)(param_1 + 0x6a0);
            dStack_128 = dStack_120 - *(double *)(param_1 + 0x698);
            iStack_108 = *(int *)(param_1 + 0x688) + 1;
            uStack_118 = 0;
            iVar16 = *(int *)(param_1 + 0x6c8) + -1;
            if (*(int *)(param_1 + 0x6c8) == 0) {
              iVar16 = 0;
            }
            FUN_140d05200(&lStack_f8,*(undefined8 *)(param_1 + 0x6c0),iVar16);
            cStack_e8 = cVar22;
            if (((*(longlong *)(param_1 + 0x498) != 0) && (cVar22 != '\0')) && (1 < (int)uStack_f0))
            {
              FUN_148267f20(*(longlong *)(param_1 + 0x498),iStack_108,&lStack_f8);
            }
            uStack_104 = CONCAT44(uStack_104._4_4_,0x3fc00000);
            if (*(char *)(lVar6 + 8 + lVar24 * 0x18) != '\x02') {
              uStack_104 = CONCAT44(uStack_104._4_4_,0x3f800000);
            }
            uVar23 = *(int *)(param_1 + 0x688) + 1;
            uVar31 = uVar34;
            uVar32 = uVar35;
            if ((int)uVar23 < *(int *)(param_1 + 0x280)) {
              lVar24 = (longlong)(int)uVar23 * 0x18;
              do {
                uVar15 = 0;
                if ((int)uVar23 < *(int *)(param_1 + 0x280)) {
                  uVar15 = ~uVar23 >> 0x1f;
                }
                if ((uVar15 == 0) &&
                   (cVar14 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                           &UNK_14bf260f0,(longlong)(int)uVar23,
                                           (longlong)*(int *)(param_1 + 0x280)), cVar14 != '\0')) {
                  pcVar8 = (code *)swi(3);
                  (*pcVar8)();
                  return;
                }
                if (*(char *)(lVar24 + 8 + *(longlong *)(param_1 + 0x278)) != '\x01') {
                  uVar15 = 0;
                  if ((int)uVar23 < *(int *)(param_1 + 0x280)) {
                    uVar15 = ~uVar23 >> 0x1f;
                  }
                  if ((uVar15 == 0) &&
                     (cVar14 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                             &UNK_14bf260f0,(longlong)(int)uVar23,
                                             (longlong)*(int *)(param_1 + 0x280)), cVar14 != '\0'))
                  {
                    pcVar8 = (code *)swi(3);
                    (*pcVar8)();
                    return;
                  }
                  uVar19 = *(undefined8 *)
                            (*(longlong *)(param_1 + 0x278) + (longlong)(int)uVar23 * 0x18);
                  uVar31 = (int)uVar19;
                  uVar32 = (int)((ulonglong)uVar19 >> 0x20);
                  break;
                }
                uVar23 = uVar23 + 1;
                lVar24 = lVar24 + 0x18;
              } while ((int)uVar23 < *(int *)(param_1 + 0x280));
            }
            if ((double)CONCAT44(uVar32,uVar31) < dVar4 || (double)CONCAT44(uVar32,uVar31) == dVar4)
            {
              if (*(double *)(param_1 + 0x268) <= 0.0) {
                dStack_110 = dVar11;
              }
              else {
                dStack_110 = dVar13 / *(double *)(param_1 + 0x268);
              }
            }
            else {
              dStack_110 = (double)CONCAT44(uVar32,uVar31) - dVar4;
            }
            FUN_14831d7a0(*(undefined8 *)(param_1 + 0x488),&dStack_128);
            if (lStack_f8 != 0) {
              FUN_140e289f0();
            }
          }
          *(int *)(param_1 + 0x688) = *(int *)(param_1 + 0x688) + 1;
        } while (*(char *)(param_1 + 0x542) == '\0');
      }
      uVar33 = *(uint *)(param_1 + 0x68c);
      if ((int)uVar33 < *(int *)(param_1 + 0x290)) {
        do {
          uVar23 = 0;
          if ((int)uVar33 < *(int *)(param_1 + 0x290)) {
            uVar23 = ~uVar33 >> 0x1f;
          }
          if ((uVar23 == 0) &&
             (cVar14 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,
                                     &UNK_14bf260f0,(longlong)(int)uVar33,
                                     (longlong)*(int *)(param_1 + 0x290)), cVar14 != '\0')) {
            pcVar8 = (code *)swi(3);
            (*pcVar8)();
            return;
          }
          pdVar3 = (double *)(*(longlong *)(param_1 + 0x288) + (longlong)(int)uVar33 * 0x28);
          dVar5 = *pdVar3;
          if (dVar26 < dVar5) break;
          if ((*(char *)(param_1 + 0x543) == '\0') ||
             ((cVar14 = *(char *)(pdVar3 + 1), cVar14 != '\b' && (cVar14 != '\v')))) {
            pdVar1 = pdVar3 + 2;
            if (4 < DAT_14edc6208) {
              if (*(int *)(pdVar3 + 3) == 0) {
                puVar18 = &UNK_14bf24094;
              }
              else {
                puVar18 = (undefined *)*pdVar1;
              }
              FUN_140f252a0(&DAT_14edc6208,&UNK_14d20f038,dVar5,*(undefined1 *)(pdVar3 + 1),puVar18,
                            pdVar3[4]);
            }
            puVar2 = (ulonglong *)(param_1 + 0x668);
            if (0xe < *(int *)(param_1 + 0x670)) {
              if (*(longlong *)(*puVar2 + 0x18) != 0) {
                FUN_140e289f0();
              }
              iVar16 = *(int *)(param_1 + 0x670) + -1;
              if (iVar16 != 0) {
                func_0x00014ba120ea(*puVar2,*puVar2 + 0x30,(longlong)iVar16 * 0x30);
              }
              *(int *)(param_1 + 0x670) = *(int *)(param_1 + 0x670) + -1;
              FUN_14830ba00(puVar2);
            }
            dStack_158 = *pdVar3;
            uStack_148 = *(undefined1 *)(pdVar3 + 1);
            dStack_140 = 0.0;
            iVar16 = *(int *)(pdVar3 + 3);
            dVar5 = *pdVar1;
            uStack_138 = CONCAT44(uStack_138._4_4_,iVar16);
            dStack_150 = dVar26;
            if (iVar16 == 0) {
              uStack_138 = 0;
            }
            else {
              FUN_140ca40a0(&dStack_140,iVar16,0);
              func_0x00014ba120de(dStack_140,dVar5,(longlong)iVar16 * 2);
            }
            dStack_130 = pdVar3[4];
            pdVar20 = (double *)*puVar2;
            if (((pdVar20 <= &dStack_158) &&
                (&dStack_158 < pdVar20 + (longlong)*(int *)(param_1 + 0x674) * 6)) &&
               (cVar14 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,
                                       &UNK_14bf25f80,&dStack_158,pdVar20,
                                       (longlong)*(int *)(param_1 + 0x674),
                                       (longlong)*(int *)(param_1 + 0x670),0x30), cVar14 != '\0')) {
              pcVar8 = (code *)swi(3);
              (*pcVar8)();
              return;
            }
            iVar16 = *(int *)(param_1 + 0x670);
            *(uint *)(param_1 + 0x670) = iVar16 + 1U;
            if (*(uint *)(param_1 + 0x674) < iVar16 + 1U) {
              FUN_14830ad50(puVar2,iVar16);
            }
            pdVar20 = (double *)((longlong)iVar16 * 0x30 + *puVar2);
            *pdVar20 = dStack_158;
            pdVar20[1] = dStack_150;
            *(undefined1 *)(pdVar20 + 2) = uStack_148;
            pdVar20[3] = 0.0;
            pdVar20[3] = dStack_140;
            *(undefined4 *)(pdVar20 + 4) = (undefined4)uStack_138;
            *(undefined4 *)((longlong)pdVar20 + 0x24) = uStack_138._4_4_;
            pdVar20[5] = dStack_130;
            uStack_138 = 0;
            dStack_140 = 0.0;
            switch(*(undefined1 *)(pdVar3 + 1)) {
            case 0:
              FUN_140cf99e0(param_1 + 0x6b0,pdVar1);
              if (4 < DAT_14edc6208) {
                if (*(int *)(pdVar3 + 3) == 0) {
                  puVar18 = &UNK_14bf24094;
                }
                else {
                  puVar18 = (undefined *)*pdVar1;
                }
                FUN_140f252a0(&DAT_14edc6208,&UNK_14d210170,puVar18);
              }
              if (*(longlong *)(param_1 + 0x498) != 0) {
                FUN_1482aad70(*(longlong *)(param_1 + 0x498),pdVar1);
              }
              FUN_1481d2a70(param_1 + 0x1d8,pdVar1);
              break;
            case 1:
              if (4 < DAT_14edc6208) {
                if (*(int *)(pdVar3 + 3) == 0) {
                  puVar18 = &UNK_14bf24094;
                }
                else {
                  puVar18 = (undefined *)*pdVar1;
                }
                FUN_140f252a0(&DAT_14edc6208,&UNK_14d210280,puVar18);
              }
              FUN_1481d29d0(param_1 + 0x1f0,pdVar1);
              break;
            case 2:
              if (4 < DAT_14edc6208) {
                FUN_140f252a0(&DAT_14edc6208,&UNK_14d2101f8,pdVar3[4]);
              }
              break;
            case 3:
              if (((*(char *)(param_1 + 0x4c1) == '\0') || (*(char *)(param_1 + 0x4c3) != '\0')) ||
                 ((*(int *)(param_1 + 0x4c8) < 1 ||
                  (*(int *)(param_1 + 0x4c8) < *(int *)(param_1 + 0x4c4))))) {
                if (4 < DAT_14edc6208) {
                  FUN_140f252a0(&DAT_14edc6208,&UNK_14d210308);
                }
                goto LAB_1483167bf;
              }
              if (4 < DAT_14edc6208) {
                FUN_140f252a0(&DAT_14edc6208,&UNK_14d2103b0);
              }
              break;
            case 4:
              if (4 < DAT_14edc6208) {
                if (*(int *)(pdVar3 + 3) == 0) {
                  puVar18 = &UNK_14bf24094;
                  puVar21 = &UNK_14d20f100;
                }
                else {
                  puVar18 = (undefined *)*pdVar1;
                  puVar21 = &UNK_14d20f100;
                }
code_r0x0001483167a4:
                FUN_140f252a0(&DAT_14edc6208,puVar21,puVar18);
              }
              break;
            case 5:
              iVar16 = FUN_14830c3d0(param_1 + -0x28,*pdVar3);
              FUN_14830caa0(param_1 + -0x28,&puStack_168,SUB84(*pdVar3,0));
              if (((*(longlong *)(param_1 + 0x498) != 0) && (iVar16 != -1)) && (1 < iStack_160)) {
                FUN_1482ac110(*(longlong *)(param_1 + 0x498),&puStack_168,iVar16);
                FUN_1482aad70(*(undefined8 *)(param_1 + 0x498),&puStack_168);
                FUN_148267f20(*(undefined8 *)(param_1 + 0x498),iVar16,&puStack_168);
              }
              if (4 < DAT_14edc6208) {
                puVar18 = &UNK_14bf24094;
                if (iStack_160 != 0) {
                  puVar18 = puStack_168;
                }
                FUN_140f252a0(&DAT_14edc6208,&UNK_14d20f188,iVar16,puVar18);
              }
              if (puStack_168 != (undefined *)0x0) {
                FUN_140e289f0();
              }
              break;
            case 6:
              if (4 < DAT_14edc6208) {
                if (*(int *)(pdVar3 + 3) == 0) {
                  puVar18 = &UNK_14bf24094;
                  puVar21 = &UNK_14d20f220;
                }
                else {
                  puVar18 = (undefined *)*pdVar1;
                  puVar21 = &UNK_14d20f220;
                }
                goto code_r0x0001483167a4;
              }
              break;
            case 7:
              if (4 < DAT_14edc6208) {
                if (*(int *)(pdVar3 + 3) == 0) {
                  puVar18 = &UNK_14bf24094;
                  puVar21 = &UNK_14d20f298;
                }
                else {
                  puVar18 = (undefined *)*pdVar1;
                  puVar21 = &UNK_14d20f298;
                }
                goto code_r0x0001483167a4;
              }
              break;
            case 8:
              if (4 < DAT_14edc6208) {
                if (*(int *)(pdVar3 + 3) == 0) {
                  puVar18 = &UNK_14bf24094;
                }
                else {
                  puVar18 = (undefined *)*pdVar1;
                }
                FUN_140f252a0(&DAT_14edc6208,&UNK_14d20f308,puVar18);
              }
              *(undefined8 *)(param_1 + 0x580) = 0xbff0000000000000;
              *(undefined8 *)(param_1 + 0x588) = 0;
              break;
            case 9:
              if (4 < DAT_14edc6208) {
                FUN_140f252a0(&DAT_14edc6208,&UNK_14d20f380);
              }
              func_0x0001481d29c0(param_1 + 0x78);
              break;
            case 0xb:
              if (4 < DAT_14edc6208) {
                if (*(int *)(pdVar3 + 3) == 0) {
                  puVar18 = &UNK_14bf24094;
                }
                else {
                  puVar18 = (undefined *)*pdVar1;
                }
                puVar21 = &UNK_14d20f3f0;
                goto code_r0x0001483167a4;
              }
            }
            FUN_1481d2810(param_1 + 0x130,pdVar3);
          }
          else if (4 < DAT_14edc6208) {
            if (*(int *)(pdVar3 + 3) == 0) {
              puVar18 = &UNK_14bf24094;
            }
            else {
              puVar18 = (undefined *)pdVar3[2];
            }
            FUN_140f252a0(&DAT_14edc6208,&UNK_14d20ef90,dVar5,cVar14,puVar18);
          }
LAB_1483167bf:
          *(int *)(param_1 + 0x68c) = *(int *)(param_1 + 0x68c) + 1;
          uVar33 = *(uint *)(param_1 + 0x68c);
        } while ((int)uVar33 < *(int *)(param_1 + 0x290));
      }
      lVar24 = *(longlong *)(param_1 + 0x498);
      if ((lVar24 != 0) && (*(char *)(lVar24 + 0x4c) != '\0')) {
        iVar16 = *(int *)(lVar24 + 0x38);
        if (*(int *)(lVar24 + 0x38) < 1) {
          iVar16 = 1;
        }
        uVar19 = FUN_1482d6f00(param_1 + -0x28,&plStack_d8,SUB84(dVar26,0),iVar16);
        FUN_1482abdd0(lVar24,uVar19);
        plVar25 = plStack_d8;
        for (; iStack_d0 != 0; iStack_d0 = iStack_d0 + -1) {
          if (*plVar25 != 0) {
            FUN_140e289f0();
          }
          plVar25 = plVar25 + 2;
        }
        if (plStack_d8 != (longlong *)0x0) {
          FUN_140e289f0(plStack_d8);
        }
      }
      if (*(double *)(param_1 + 0x260) <= dVar26) {
        if (4 < DAT_14edc6208) {
          FUN_140f252a0(&DAT_14edc6208,&UNK_14d20f460,*(double *)(param_1 + 0x260));
        }
        FUN_1482f9c00(param_1 + -0x28);
      }
    }
  }
  return;
}

