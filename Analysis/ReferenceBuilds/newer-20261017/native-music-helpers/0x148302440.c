// Newer reference PDB symbol: ParseBeatmapJson_UMusicModeManager
// Address: 0x148302440
// Static inferred pseudocode; external calls/types may be unresolved.


/* Matched newer-build PDB public symbol: ParseBeatmapJson_UMusicModeManager */

ulonglong FUN_148302440(undefined8 param_1,undefined8 param_2,longlong param_3)

{
  int *piVar1;
  longlong lVar2;
  longlong lVar3;
  undefined4 *puVar4;
  longlong *plVar5;
  undefined8 *puVar6;
  code *pcVar7;
  undefined8 uVar8;
  char cVar9;
  undefined4 uVar10;
  int iVar11;
  longlong *plVar12;
  ulonglong uVar13;
  longlong *plVar14;
  undefined1 uVar15;
  undefined *puVar16;
  bool bVar17;
  longlong *plVar18;
  undefined8 unaff_retaddr;
  undefined1 auStackX_20 [8];
  undefined1 auStack_2b8 [8];
  undefined *puStack_2b0;
  undefined8 uStack_2a8;
  longlong lStack_2a0;
  longlong *plStack_298;
  undefined1 uStack_290;
  undefined1 auStack_28f [7];
  longlong *plStack_288;
  longlong *plStack_280;
  longlong *plStack_278;
  longlong *plStack_270;
  undefined8 uStack_268;
  char cStack_260;
  longlong alStack_258 [3];
  longlong *plStack_240;
  longlong *plStack_238;
  undefined *puStack_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  uint uStack_218;
  undefined4 uStack_214;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined *puStack_200;
  int iStack_1f8;
  undefined *puStack_1f0;
  int iStack_1e8;
  undefined *puStack_1e0;
  int iStack_1d8;
  undefined8 uStack_1d0;
  longlong *plStack_1c8;
  longlong *plStack_1c0;
  longlong *plStack_1b8;
  longlong alStack_1b0 [2];
  longlong alStack_1a0 [2];
  longlong alStack_190 [2];
  longlong alStack_180 [2];
  longlong alStack_170 [2];
  longlong alStack_160 [2];
  longlong alStack_150 [2];
  longlong alStack_140 [2];
  longlong alStack_130 [2];
  longlong alStack_120 [2];
  longlong alStack_110 [2];
  longlong alStack_100 [2];
  longlong alStack_f0 [2];
  longlong alStack_e0 [2];
  longlong alStack_d0 [2];
  longlong alStack_c0 [2];
  longlong alStack_b0 [2];
  longlong alStack_a0 [2];
  longlong alStack_90 [2];
  longlong alStack_80 [2];
  longlong alStack_70 [2];
  longlong alStack_60 [2];
  longlong alStack_50 [5];
  
  plStack_288 = (longlong *)0x0;
  plStack_280 = (longlong *)0x0;
  FUN_1414770e0(&uStack_1d0);
  cVar9 = FUN_141467050(uStack_1d0,&plStack_288,0);
  if ((cVar9 == '\0') || (plStack_288 == (longlong *)0x0)) {
    if (1 < DAT_14edc6208) {
      FUN_140f252a0(&DAT_14edc6208,&UNK_14d20d580);
    }
    bVar17 = false;
    goto LAB_14830379b;
  }
  FUN_140cf7e50(&puStack_200,&UNK_14ca45300);
  if (iStack_1f8 == 0) {
    puVar16 = &UNK_14bf24094;
    plVar12 = (longlong *)0x0;
  }
  else {
    plVar12 = (longlong *)(ulonglong)(iStack_1f8 - 1);
    puVar16 = puStack_200;
  }
  uVar10 = FUN_140cf5670(plVar12,puVar16);
  plVar12 = plStack_288;
  iVar11 = FUN_141467a80(plStack_288,uVar10,&puStack_200);
  if (iVar11 == -1) {
LAB_14830251f:
    bVar17 = false;
  }
  else {
    lVar2 = *plVar12 + (longlong)iVar11 * 0x28;
    plVar12 = (longlong *)(lVar2 + 0x10);
    if (lVar2 == 0) {
      plVar12 = (longlong *)0x0;
    }
    if (((plVar12 == (longlong *)0x0) || (*plVar12 == 0)) || (*(int *)(*plVar12 + 8) != 6))
    goto LAB_14830251f;
    bVar17 = true;
  }
  if (puStack_200 != (undefined *)0x0) {
    FUN_140e289f0();
  }
  if (bVar17) {
    FUN_140cf7e50(alStack_1b0,&UNK_14ca45300);
    plVar12 = (longlong *)FUN_14147a3f0(plStack_288,alStack_1b0);
    lVar2 = *plVar12;
    plStack_298 = (longlong *)plVar12[1];
    if (plStack_298 != (longlong *)0x0) {
      LOCK();
      *(int *)(plStack_298 + 1) = (int)plStack_298[1] + 1;
      UNLOCK();
    }
    lStack_2a0 = lVar2;
    if (alStack_1b0[0] != 0) {
      FUN_140e289f0();
    }
    if ((lVar2 == 0) &&
       (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
       cVar9 != '\0')) {
      pcVar7 = (code *)swi(3);
      uVar13 = (*pcVar7)();
      return uVar13;
    }
    FUN_140cf7e50(alStack_1a0,&UNK_14cd73ab8);
    FUN_141484a20(lVar2,alStack_1a0,param_3);
    if (alStack_1a0[0] != 0) {
      FUN_140e289f0();
    }
    if ((lVar2 == 0) &&
       (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
       cVar9 != '\0')) {
      pcVar7 = (code *)swi(3);
      uVar13 = (*pcVar7)();
      return uVar13;
    }
    FUN_140cf7e50(alStack_190,&UNK_14d1ed0e8);
    FUN_141484a20(lVar2,alStack_190,param_3 + 0x10);
    if (alStack_190[0] != 0) {
      FUN_140e289f0();
    }
    if ((lVar2 == 0) &&
       (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
       cVar9 != '\0')) {
      pcVar7 = (code *)swi(3);
      uVar13 = (*pcVar7)();
      return uVar13;
    }
    FUN_140cf7e50(alStack_180,&UNK_14d1ed0f8);
    FUN_141484a20(lVar2,alStack_180,param_3 + 0x20);
    if (alStack_180[0] != 0) {
      FUN_140e289f0();
    }
    if ((lVar2 == 0) &&
       (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
       cVar9 != '\0')) {
      pcVar7 = (code *)swi(3);
      uVar13 = (*pcVar7)();
      return uVar13;
    }
    FUN_140cf7e50(alStack_50,&UNK_14d20d690);
    cVar9 = FUN_141484a20(lVar2,alStack_50,param_3 + 0x30);
    if (alStack_50[0] != 0) {
      FUN_140e289f0();
    }
    if (cVar9 == '\0') {
      uStack_208 = 0;
      if ((lVar2 == 0) &&
         (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
         cVar9 != '\0')) {
        pcVar7 = (code *)swi(3);
        uVar13 = (*pcVar7)();
        return uVar13;
      }
      FUN_140cf7e50(alStack_170,&UNK_14d20d690);
      cVar9 = FUN_141484380(lVar2,alStack_170,&uStack_208);
      if (alStack_170[0] != 0) {
        FUN_140e289f0();
      }
      if (cVar9 != '\0') {
        FUN_140d170d0(alStack_160,&UNK_14bfcb4d0,uStack_208);
        FUN_140cf9980(param_3 + 0x30,alStack_160);
        if (alStack_160[0] != 0) {
          FUN_140e289f0();
        }
      }
    }
    if ((lVar2 == 0) &&
       (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
       cVar9 != '\0')) {
      pcVar7 = (code *)swi(3);
      uVar13 = (*pcVar7)();
      return uVar13;
    }
    FUN_140cf7e50(alStack_150,&UNK_14d1ed108);
    FUN_141484a20(lVar2,alStack_150,param_3 + 0x40);
    if (alStack_150[0] != 0) {
      FUN_140e289f0();
    }
    if ((lVar2 == 0) &&
       (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
       cVar9 != '\0')) {
      pcVar7 = (code *)swi(3);
      uVar13 = (*pcVar7)();
      return uVar13;
    }
    FUN_140cf7e50(alStack_140,&UNK_14d1d3bc8);
    cVar9 = FUN_145e5b470(lVar2,alStack_140);
    if (alStack_140[0] != 0) {
      FUN_140e289f0();
    }
    if (cVar9 != '\0') {
      if ((lVar2 == 0) &&
         (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
         cVar9 != '\0')) {
        pcVar7 = (code *)swi(3);
        uVar13 = (*pcVar7)();
        return uVar13;
      }
      FUN_140cf7e50(alStack_130,&UNK_14d1d3bc8);
      uVar8 = FUN_14147a330(lVar2,alStack_130);
      *(undefined8 *)(param_3 + 0x50) = uVar8;
      if (alStack_130[0] != 0) {
        FUN_140e289f0();
      }
    }
    if ((lVar2 == 0) &&
       (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
       cVar9 != '\0')) {
      pcVar7 = (code *)swi(3);
      uVar13 = (*pcVar7)();
      return uVar13;
    }
    FUN_140cf7e50(alStack_120,&UNK_14d1ed120);
    cVar9 = FUN_145e5b470(lVar2,alStack_120);
    if (alStack_120[0] != 0) {
      FUN_140e289f0();
    }
    if (cVar9 != '\0') {
      if ((lVar2 == 0) &&
         (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
         cVar9 != '\0')) {
        pcVar7 = (code *)swi(3);
        uVar13 = (*pcVar7)();
        return uVar13;
      }
      FUN_140cf7e50(alStack_110,&UNK_14d1ed120);
      uVar8 = FUN_14147a330(lVar2,alStack_110);
      *(undefined8 *)(param_3 + 0x58) = uVar8;
      if (alStack_110[0] != 0) {
        FUN_140e289f0();
      }
    }
    if ((lVar2 == 0) &&
       (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
       cVar9 != '\0')) {
      pcVar7 = (code *)swi(3);
      uVar13 = (*pcVar7)();
      return uVar13;
    }
    FUN_140cf7e50(alStack_100,&UNK_14d1ed128);
    cVar9 = FUN_145e5b470(lVar2,alStack_100);
    if (alStack_100[0] != 0) {
      FUN_140e289f0();
    }
    if (cVar9 != '\0') {
      if ((lVar2 == 0) &&
         (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
         cVar9 != '\0')) {
        pcVar7 = (code *)swi(3);
        uVar13 = (*pcVar7)();
        return uVar13;
      }
      FUN_140cf7e50(alStack_f0,&UNK_14d1ed128);
      uVar8 = FUN_14147a330(lVar2,alStack_f0);
      *(undefined8 *)(param_3 + 0x60) = uVar8;
      if (alStack_f0[0] != 0) {
        FUN_140e289f0();
      }
    }
    plVar12 = plStack_298;
    if (plStack_298 != (longlong *)0x0) {
      LOCK();
      plVar18 = plStack_298 + 1;
      lVar2 = *plVar18;
      *(int *)plVar18 = (int)*plVar18 + -1;
      UNLOCK();
      if ((int)lVar2 == 1) {
        (**(code **)*plStack_298)(plStack_298);
        LOCK();
        piVar1 = (int *)((longlong)plVar12 + 0xc);
        iVar11 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar11 == 1) {
          (**(code **)(*plStack_298 + 8))(plStack_298,1);
        }
      }
    }
  }
  else if (2 < DAT_14edc6208) {
    FUN_140f252a0(&DAT_14edc6208,&UNK_14d20d600);
  }
  if ((plStack_288 == (longlong *)0x0) &&
     (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
     cVar9 != '\0')) {
    pcVar7 = (code *)swi(3);
    uVar13 = (*pcVar7)();
    return uVar13;
  }
  FUN_140cf7e50(alStack_e0,&UNK_14d1ed0d8);
  cVar9 = FUN_141482c90(plStack_288,alStack_e0,&plStack_1c0);
  if (alStack_e0[0] != 0) {
    FUN_140e289f0();
  }
  if (cVar9 != '\0') {
    plVar12 = (longlong *)*plStack_1c0;
    lVar2 = plStack_1c0[1];
    plVar18 = plVar12 + (longlong)(int)lVar2 * 2;
    while( true ) {
      if ((int)plStack_1c0[1] != (int)lVar2) {
        auStackX_20[0] = 0;
        cVar9 = FUN_14bd2d070(auStackX_20);
        if (cVar9 != '\0') {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
      }
      if (plVar12 == plVar18) break;
      if ((*plVar12 == 0) &&
         (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
         cVar9 != '\0')) {
        pcVar7 = (code *)swi(3);
        uVar13 = (*pcVar7)();
        return uVar13;
      }
      if (*(int *)(*plVar12 + 8) == 6) {
        if ((*plVar12 == 0) &&
           (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
           cVar9 != '\0')) {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
        plVar14 = (longlong *)(*(code *)**(undefined8 **)*plVar12)();
        plVar5 = (longlong *)*plVar14;
        plStack_238 = (longlong *)plVar14[1];
        if (plStack_238 != (longlong *)0x0) {
          LOCK();
          *(int *)(plStack_238 + 1) = (int)plStack_238[1] + 1;
          UNLOCK();
        }
        uStack_220 = 0;
        uStack_218 = uStack_218 & 0xffffff00;
        uStack_210 = 0;
        plStack_240 = plVar5;
        if ((plVar5 == (longlong *)0x0) &&
           (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
           cVar9 != '\0')) {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
        FUN_140cf7e50(alStack_d0,&UNK_14ca1ceb8);
        uStack_220 = FUN_14147a330(plVar5,alStack_d0);
        if (alStack_d0[0] != 0) {
          FUN_140e289f0();
        }
        puStack_230 = (undefined *)0x0;
        uStack_228 = 0;
        if ((plVar5 == (longlong *)0x0) &&
           (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
           cVar9 != '\0')) {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
        FUN_140cf7e50(alStack_c0,&UNK_14d169e78);
        cVar9 = FUN_141484a20(plVar5,alStack_c0,&puStack_230);
        if (alStack_c0[0] != 0) {
          FUN_140e289f0();
        }
        if (cVar9 != '\0') {
          puVar16 = &UNK_14bf24094;
          if ((int)uStack_228 != 0) {
            puVar16 = puStack_230;
          }
          iVar11 = func_0x000140d80e70(puVar16,&UNK_14d1ed138);
          if (iVar11 == 0) {
            uStack_218 = CONCAT31(uStack_218._1_3_,1);
          }
          else {
            puVar16 = &UNK_14bf24094;
            if ((int)uStack_228 != 0) {
              puVar16 = puStack_230;
            }
            iVar11 = func_0x000140d80e70(puVar16,&UNK_14d1ed148);
            uVar15 = 0;
            if (iVar11 == 0) {
              uVar15 = 2;
            }
            uStack_218 = CONCAT31(uStack_218._1_3_,uVar15);
          }
        }
        if ((plVar5 == (longlong *)0x0) &&
           (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
           cVar9 != '\0')) {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
        FUN_140cf7e50(&puStack_1f0,&UNK_14d1d3bc8);
        if (iStack_1e8 == 0) {
          puVar16 = &UNK_14bf24094;
          iVar11 = 0;
        }
        else {
          iVar11 = iStack_1e8 + -1;
          puVar16 = puStack_1f0;
        }
        uVar10 = FUN_140cf5670(iVar11,puVar16);
        iVar11 = FUN_141467a80(plVar5,uVar10,&puStack_1f0);
        if (iVar11 == -1) {
LAB_148302eb6:
          bVar17 = false;
        }
        else {
          lVar3 = *plVar5 + (longlong)iVar11 * 0x28;
          plVar14 = (longlong *)(lVar3 + 0x10);
          if (lVar3 == 0) {
            plVar14 = (longlong *)0x0;
          }
          if ((plVar14 == (longlong *)0x0) || (*plVar14 == 0)) goto LAB_148302eb6;
          bVar17 = true;
        }
        if (puStack_1f0 != (undefined *)0x0) {
          FUN_140e289f0();
        }
        if (bVar17) {
          if ((plVar5 == (longlong *)0x0) &&
             (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094
                                   ), cVar9 != '\0')) {
            pcVar7 = (code *)swi(3);
            uVar13 = (*pcVar7)();
            return uVar13;
          }
          FUN_140cf7e50(alStack_b0,&UNK_14d1d3bc8);
          uStack_210 = FUN_14147a330(plVar5,alStack_b0);
          if (alStack_b0[0] != 0) {
            FUN_140e289f0();
          }
        }
        puVar6 = *(undefined8 **)(param_3 + 0x68);
        if (((puVar6 <= &uStack_220) &&
            (&uStack_220 < puVar6 + (longlong)*(int *)(param_3 + 0x74) * 3)) &&
           (cVar9 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                                  &uStack_220,puVar6,(longlong)*(int *)(param_3 + 0x74),
                                  (longlong)*(int *)(param_3 + 0x70),0x18), cVar9 != '\0')) {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
        iVar11 = *(int *)(param_3 + 0x70);
        *(uint *)(param_3 + 0x70) = iVar11 + 1U;
        if (*(uint *)(param_3 + 0x74) < iVar11 + 1U) {
          FUN_1482a3c20(param_3 + 0x68,iVar11);
        }
        lVar3 = *(longlong *)(param_3 + 0x68);
        puVar4 = (undefined4 *)(lVar3 + (longlong)iVar11 * 0x18);
        *puVar4 = (undefined4)uStack_220;
        puVar4[1] = uStack_220._4_4_;
        puVar4[2] = uStack_218;
        puVar4[3] = uStack_214;
        *(undefined8 *)(lVar3 + 0x10 + (longlong)iVar11 * 0x18) = uStack_210;
        if (puStack_230 != (undefined *)0x0) {
          FUN_140e289f0();
        }
        plVar5 = plStack_238;
        if (plStack_238 != (longlong *)0x0) {
          LOCK();
          plVar14 = plStack_238 + 1;
          lVar3 = *plVar14;
          *(int *)plVar14 = (int)*plVar14 + -1;
          UNLOCK();
          if ((int)lVar3 == 1) {
            (**(code **)*plStack_238)(plStack_238);
            LOCK();
            piVar1 = (int *)((longlong)plVar5 + 0xc);
            iVar11 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar11 == 1) {
              (**(code **)(*plStack_238 + 8))(plStack_238,1);
            }
          }
        }
      }
      plVar12 = plVar12 + 2;
    }
  }
  if ((plStack_288 == (longlong *)0x0) &&
     (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
     cVar9 != '\0')) {
    pcVar7 = (code *)swi(3);
    uVar13 = (*pcVar7)();
    return uVar13;
  }
  FUN_140cf7e50(alStack_a0,&UNK_14ca45920);
  cVar9 = FUN_141482c90(plStack_288,alStack_a0,&plStack_1b8);
  if (alStack_a0[0] != 0) {
    FUN_140e289f0();
  }
  if (cVar9 != '\0') {
    plVar12 = (longlong *)*plStack_1b8;
    lVar2 = plStack_1b8[1];
    plVar18 = plVar12 + (longlong)(int)lVar2 * 2;
    while( true ) {
      if ((int)plStack_1b8[1] != (int)lVar2) {
        auStack_2b8[0] = 0;
        cVar9 = FUN_14bd2d070(auStack_2b8);
        if (cVar9 != '\0') {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
      }
      if (plVar12 == plVar18) break;
      if ((*plVar12 == 0) &&
         (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
         cVar9 != '\0')) {
        pcVar7 = (code *)swi(3);
        uVar13 = (*pcVar7)();
        return uVar13;
      }
      if (*(int *)(*plVar12 + 8) == 6) {
        if ((*plVar12 == 0) &&
           (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
           cVar9 != '\0')) {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
        plVar14 = (longlong *)(*(code *)**(undefined8 **)*plVar12)();
        plVar5 = (longlong *)*plVar14;
        plStack_270 = (longlong *)plVar14[1];
        if (plStack_270 != (longlong *)0x0) {
          LOCK();
          *(int *)(plStack_270 + 1) = (int)plStack_270[1] + 1;
          UNLOCK();
        }
        uStack_268 = 0;
        cStack_260 = '\n';
        alStack_258[0] = 0;
        alStack_258[1] = 0;
        alStack_258[2] = 0;
        plStack_278 = plVar5;
        if ((plVar5 == (longlong *)0x0) &&
           (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
           cVar9 != '\0')) {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
        FUN_140cf7e50(alStack_90,&UNK_14ca1ceb8);
        uStack_268 = FUN_14147a330(plVar5,alStack_90);
        if (alStack_90[0] != 0) {
          FUN_140e289f0();
        }
        puStack_2b0 = (undefined *)0x0;
        uStack_2a8 = 0;
        if ((plVar5 == (longlong *)0x0) &&
           (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
           cVar9 != '\0')) {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
        FUN_140cf7e50(alStack_80,&UNK_14d169e78);
        cVar9 = FUN_141484a20(plVar5,alStack_80,&puStack_2b0);
        if (alStack_80[0] != 0) {
          FUN_140e289f0();
        }
        if (cVar9 != '\0') {
          puVar16 = &UNK_14bf24094;
          if ((int)uStack_2a8 != 0) {
            puVar16 = puStack_2b0;
          }
          iVar11 = func_0x000140d80e70(puVar16,&UNK_14d1ed158);
          if (iVar11 != 0) {
            puVar16 = &UNK_14bf24094;
            if ((int)uStack_2a8 != 0) {
              puVar16 = puStack_2b0;
            }
            iVar11 = func_0x000140d80e70(puVar16,&UNK_14d1ed178);
            if (iVar11 != 0) {
              puVar16 = &UNK_14bf24094;
              if ((int)uStack_2a8 != 0) {
                puVar16 = puStack_2b0;
              }
              iVar11 = func_0x000140d80e70(puVar16,&UNK_14d1ed198);
              if (iVar11 == 0) {
                cStack_260 = '\x01';
              }
              else {
                puVar16 = &UNK_14bf24094;
                if ((int)uStack_2a8 != 0) {
                  puVar16 = puStack_2b0;
                }
                iVar11 = func_0x000140d80e70(puVar16,&UNK_14d1d9750);
                if (iVar11 == 0) {
                  cStack_260 = '\x02';
                }
                else {
                  puVar16 = &UNK_14bf24094;
                  if ((int)uStack_2a8 != 0) {
                    puVar16 = puStack_2b0;
                  }
                  iVar11 = func_0x000140d80e70(puVar16,&UNK_14d1ed1b0);
                  if (iVar11 == 0) {
                    cStack_260 = '\x03';
                  }
                  else {
                    puVar16 = &UNK_14bf24094;
                    if ((int)uStack_2a8 != 0) {
                      puVar16 = puStack_2b0;
                    }
                    iVar11 = func_0x000140d80e70(puVar16,&UNK_14d1ed1c8);
                    if (iVar11 == 0) {
                      cStack_260 = '\x04';
                    }
                    else {
                      puVar16 = &UNK_14bf24094;
                      if ((int)uStack_2a8 != 0) {
                        puVar16 = puStack_2b0;
                      }
                      iVar11 = func_0x000140d80e70(puVar16,&UNK_14d1ed1e8);
                      if (iVar11 == 0) {
                        cStack_260 = '\x05';
                      }
                      else {
                        puVar16 = &UNK_14bf24094;
                        if ((int)uStack_2a8 != 0) {
                          puVar16 = puStack_2b0;
                        }
                        iVar11 = func_0x000140d80e70(puVar16,&UNK_14cd782c8);
                        if (iVar11 == 0) {
                          cStack_260 = '\x06';
                        }
                        else {
                          puVar16 = &UNK_14bf24094;
                          if ((int)uStack_2a8 != 0) {
                            puVar16 = puStack_2b0;
                          }
                          iVar11 = func_0x000140d80e70(puVar16,&UNK_14c153fc8);
                          if (iVar11 == 0) {
                            cStack_260 = '\a';
                          }
                          else {
                            puVar16 = &UNK_14bf24094;
                            if ((int)uStack_2a8 != 0) {
                              puVar16 = puStack_2b0;
                            }
                            iVar11 = func_0x000140d80e70(puVar16,&UNK_14d1ed200);
                            if (iVar11 == 0) {
                              cStack_260 = '\b';
                            }
                            else {
                              puVar16 = &UNK_14bf24094;
                              if ((int)uStack_2a8 != 0) {
                                puVar16 = puStack_2b0;
                              }
                              iVar11 = func_0x000140d80e70(puVar16,&UNK_14d1ed220);
                              if (iVar11 == 0) {
                                cStack_260 = '\t';
                              }
                              else {
                                puVar16 = &UNK_14bf24094;
                                if ((int)uStack_2a8 != 0) {
                                  puVar16 = puStack_2b0;
                                }
                                iVar11 = func_0x000140d80e70(puVar16,&UNK_14d1ed238);
                                cStack_260 = (iVar11 == 0) + '\n';
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              goto LAB_148303476;
            }
          }
          cStack_260 = '\0';
        }
LAB_148303476:
        if ((plVar5 == (longlong *)0x0) &&
           (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
           cVar9 != '\0')) {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
        FUN_140cf7e50(alStack_70,&UNK_14cd73970);
        FUN_141484a20(plVar5,alStack_70,alStack_258);
        if (alStack_70[0] != 0) {
          FUN_140e289f0();
        }
        if ((plVar5 == (longlong *)0x0) &&
           (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094),
           cVar9 != '\0')) {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
        FUN_140cf7e50(&puStack_1e0,&UNK_14d1d3bc8);
        if (iStack_1d8 == 0) {
          puVar16 = &UNK_14bf24094;
          iVar11 = 0;
        }
        else {
          iVar11 = iStack_1d8 + -1;
          puVar16 = puStack_1e0;
        }
        uVar10 = FUN_140cf5670(iVar11,puVar16);
        iVar11 = FUN_141467a80(plVar5,uVar10,&puStack_1e0);
        if (iVar11 == -1) {
LAB_148303581:
          bVar17 = false;
        }
        else {
          lVar3 = *plVar5 + (longlong)iVar11 * 0x28;
          plVar14 = (longlong *)(lVar3 + 0x10);
          if (lVar3 == 0) {
            plVar14 = (longlong *)0x0;
          }
          if ((plVar14 == (longlong *)0x0) || (*plVar14 == 0)) goto LAB_148303581;
          bVar17 = true;
        }
        if (puStack_1e0 != (undefined *)0x0) {
          FUN_140e289f0();
        }
        if (bVar17) {
          if ((plVar5 == (longlong *)0x0) &&
             (cVar9 = FUN_140f8e6d0(&UNK_14bf28080,&UNK_14d167350,0x473,unaff_retaddr,&UNK_14bf24094
                                   ), cVar9 != '\0')) {
            pcVar7 = (code *)swi(3);
            uVar13 = (*pcVar7)();
            return uVar13;
          }
          FUN_140cf7e50(alStack_60,&UNK_14d1d3bc8);
          alStack_258[2] = FUN_14147a330(plVar5,alStack_60);
          if (alStack_60[0] != 0) {
            FUN_140e289f0();
          }
        }
        puVar6 = *(undefined8 **)(param_3 + 0x78);
        if (((puVar6 <= &uStack_268) &&
            (&uStack_268 < puVar6 + (longlong)*(int *)(param_3 + 0x84) * 5)) &&
           (cVar9 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                                  &uStack_268,puVar6,(longlong)*(int *)(param_3 + 0x84),
                                  (longlong)*(int *)(param_3 + 0x80),0x28), cVar9 != '\0')) {
          pcVar7 = (code *)swi(3);
          uVar13 = (*pcVar7)();
          return uVar13;
        }
        iVar11 = *(int *)(param_3 + 0x80);
        *(uint *)(param_3 + 0x80) = iVar11 + 1U;
        if (*(uint *)(param_3 + 0x84) < iVar11 + 1U) {
          FUN_1482a3cd0(param_3 + 0x78,iVar11);
        }
        FUN_1482cda20(*(longlong *)(param_3 + 0x78) + (longlong)iVar11 * 0x28,&uStack_268);
        if (puStack_2b0 != (undefined *)0x0) {
          FUN_140e289f0();
        }
        if (alStack_258[0] != 0) {
          FUN_140e289f0();
        }
        plVar5 = plStack_270;
        if (plStack_270 != (longlong *)0x0) {
          LOCK();
          plVar14 = plStack_270 + 1;
          lVar3 = *plVar14;
          *(int *)plVar14 = (int)*plVar14 + -1;
          UNLOCK();
          if ((int)lVar3 == 1) {
            (**(code **)*plStack_270)(plStack_270);
            LOCK();
            piVar1 = (int *)((longlong)plVar5 + 0xc);
            iVar11 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar11 == 1) {
              (**(code **)(*plStack_270 + 8))(plStack_270,1);
            }
          }
        }
      }
      plVar12 = plVar12 + 2;
    }
  }
  FUN_1482cbab0(*(undefined8 *)(param_3 + 0x68),*(undefined4 *)(param_3 + 0x70),auStackX_20[0],
                &uStack_290);
  FUN_1482cbdc0(*(undefined8 *)(param_3 + 0x78),*(undefined4 *)(param_3 + 0x80),auStackX_20[0],
                auStack_28f);
  bVar17 = 0 < *(int *)(param_3 + 0x70);
LAB_14830379b:
  plVar12 = plStack_1c8;
  if (plStack_1c8 != (longlong *)0x0) {
    LOCK();
    plVar18 = plStack_1c8 + 1;
    lVar2 = *plVar18;
    *(int *)plVar18 = (int)*plVar18 + -1;
    UNLOCK();
    if ((int)lVar2 == 1) {
      (**(code **)*plStack_1c8)(plStack_1c8);
      LOCK();
      piVar1 = (int *)((longlong)plVar12 + 0xc);
      iVar11 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar11 == 1) {
        (**(code **)(*plStack_1c8 + 8))(plStack_1c8,1);
      }
    }
  }
  plVar12 = plStack_280;
  if (plStack_280 != (longlong *)0x0) {
    LOCK();
    plVar18 = plStack_280 + 1;
    lVar2 = *plVar18;
    *(int *)plVar18 = (int)*plVar18 + -1;
    UNLOCK();
    if ((int)lVar2 == 1) {
      (**(code **)*plStack_280)(plStack_280);
      LOCK();
      piVar1 = (int *)((longlong)plVar12 + 0xc);
      iVar11 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar11 == 1) {
        (**(code **)(*plStack_280 + 8))(plStack_280,1);
      }
    }
  }
  return (ulonglong)bVar17;
}

