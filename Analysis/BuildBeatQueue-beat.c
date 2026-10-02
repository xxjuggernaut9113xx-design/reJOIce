/* 1481d02a0 ?BuildBeatQueue@UBeatSpawnerManager@@AEAAXAEBUFBeatPattern@@NHMN@Z */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _BuildBeatQueue_UBeatSpawnerManager__AEAAXAEBUFBeatPattern__NHMN_Z
               (longlong param_1,longlong param_2,double param_3,int param_4,float param_5,
               double param_6)

{
  ulonglong *puVar1;
  uint *puVar2;
  float fVar3;
  int iVar4;
  ulonglong uVar5;
  code *pcVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  int iVar12;
  char cVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  undefined *puVar17;
  uint uVar18;
  int iVar19;
  double *pdVar20;
  longlong lVar21;
  undefined8 unaff_retaddr;
  double dVar22;
  double dVar23;
  double dVar24;
  double dStack_108;
  double dStack_100;
  uint uStack_f8;
  uint uStack_f4;
  undefined8 uStack_f0;
  int iStack_e8;
  float fStack_e4;
  
  dVar11 = _DAT_14bd17840;
  if ((((((1 < DAT_14eab53c8) &&
         (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7aa80), 1 < DAT_14eab53c8)) &&
        (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7aaf0), 1 < DAT_14eab53c8)) &&
       ((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7ab38,param_3,dVar11 / param_3),
        1 < DAT_14eab53c8 &&
        (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7abb0,param_4), 1 < DAT_14eab53c8)))) &&
      ((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7abf8,(double)param_5), 1 < DAT_14eab53c8 &&
       ((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7ac48,param_6), 1 < DAT_14eab53c8 &&
        (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7ac98,*(undefined4 *)(param_2 + 0x18)),
        1 < DAT_14eab53c8)))))) &&
     (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7ad10,*(undefined8 *)(param_1 + 0xe0)),
     1 < DAT_14eab53c8)) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7ad78);
  }
  uVar18 = 0;
  if (0 < *(int *)(param_2 + 0x18)) {
    lVar21 = 0;
    do {
      if (1 < DAT_14eab53c8) {
        uVar14 = 0;
        if ((int)uVar18 < *(int *)(param_2 + 0x18)) {
          uVar14 = ~uVar18 >> 0x1f;
        }
        if ((uVar14 == 0) &&
           (cVar13 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                         &UNK_14bce6ef0,(longlong)(int)uVar18,
                                         (longlong)*(int *)(param_2 + 0x18)), cVar13 != '\0')) {
          pcVar6 = (code *)swi(3);
          (*pcVar6)();
          return;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7adb8,uVar18,
                            (double)*(float *)(*(longlong *)(param_2 + 0x10) + lVar21));
      }
      uVar18 = uVar18 + 1;
      lVar21 = lVar21 + 4;
    } while ((int)uVar18 < *(int *)(param_2 + 0x18));
  }
  puVar1 = (ulonglong *)(param_1 + 0xe8);
  *(undefined4 *)(param_1 + 0xf0) = 0;
  if (*(int *)(param_1 + 0xf4) != 0) {
    func_0x0001481d2290(puVar1,0);
  }
  iVar16 = *(int *)(param_2 + 0x18);
  if (iVar16 == 0) {
    if (DAT_14eab53c8 < 2) {
      return;
    }
    puVar17 = &UNK_14cf7ae08;
  }
  else {
    iVar19 = 0;
    uVar18 = 0;
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7aeb8);
    }
    dVar11 = param_6;
    if (0 < param_4) {
      dVar7 = (double)param_5;
      dVar8 = _DAT_14bce5180 / dVar7;
      iVar12 = 1;
      do {
        uVar14 = _DAT_14bd17880;
        uVar15 = 0;
        if ((int)uVar18 < *(int *)(param_2 + 0x18)) {
          uVar15 = ~uVar18 >> 0x1f;
        }
        if ((uVar15 == 0) &&
           (cVar13 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                         &UNK_14bce6ef0,(longlong)(int)uVar18,
                                         (longlong)*(int *)(param_2 + 0x18)), cVar13 != '\0')) {
          pcVar6 = (code *)swi(3);
          (*pcVar6)();
          return;
        }
        dVar10 = dVar11 - param_6;
        fVar3 = *(float *)(*(longlong *)(param_2 + 0x10) + (longlong)(int)uVar18 * 4);
        dVar23 = (double)(float)((uint)fVar3 & uVar14) * param_3;
        dVar9 = dVar8 * dVar23;
        if (dVar9 <= *(double *)(param_1 + 0xe0)) {
          dVar9 = *(double *)(param_1 + 0xe0);
        }
        if ((1 < DAT_14eab53c8) &&
           (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7af10,iVar12,uVar18), 1 < DAT_14eab53c8)) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7af60,SUB84((double)fVar3,0));
        }
        if (1 < DAT_14eab53c8) {
          dVar23 = dVar23 * dVar7;
          dVar22 = dVar7;
          dVar24 = dVar9;
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7afb0,(double)(float)((uint)fVar3 & uVar14),
                              param_3,dVar7,dVar23,dVar9);
          if (1 < DAT_14eab53c8) {
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b050,dVar9,_DAT_14bd17840 / dVar9,dVar22,
                                dVar23,dVar24);
          }
        }
        if (0.0 <= fVar3) {
          if (_DAT_14bd4dcfc <= fVar3) {
            if (fVar3 <= _DAT_14cf708e0) {
              if (1 < DAT_14eab53c8) {
                puVar17 = &UNK_14cf7b230;
                goto LAB_1481d07ea;
              }
            }
            else if (1 < DAT_14eab53c8) {
              func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b1b0,SUB84((double)fVar3,0));
              goto LAB_1481d07f6;
            }
          }
          else if (1 < DAT_14eab53c8) {
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b130,(double)(_DAT_14bcef9ec / fVar3));
            goto LAB_1481d07f6;
          }
        }
        else if (1 < DAT_14eab53c8) {
          puVar17 = &UNK_14cf7b0c0;
LAB_1481d07ea:
          func_0x000140f24ba0(&DAT_14eab53c8,puVar17);
LAB_1481d07f6:
          if (1 < DAT_14eab53c8) {
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b280,dVar10,dVar11,dVar11);
          }
        }
        pdVar20 = (double *)*puVar1;
        dStack_108 = dVar10;
        dStack_100 = dVar11;
        uStack_f8 = uVar18;
        uStack_f0 = dVar9;
        iStack_e8 = iVar12;
        fStack_e4 = fVar3;
        if (((pdVar20 <= &dStack_108) &&
            (&dStack_108 < pdVar20 + (longlong)*(int *)(param_1 + 0xf4) * 5)) &&
           (cVar13 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                         &UNK_14bce6d80,&dStack_108,pdVar20,
                                         (longlong)*(int *)(param_1 + 0xf4),
                                         (longlong)*(int *)(param_1 + 0xf0),0x28), cVar13 != '\0'))
        {
          pcVar6 = (code *)swi(3);
          (*pcVar6)();
          return;
        }
        iVar4 = *(int *)(param_1 + 0xf0);
        lVar21 = (longlong)iVar4;
        *(uint *)(param_1 + 0xf0) = iVar4 + 1U;
        if (*(uint *)(param_1 + 0xf4) < iVar4 + 1U) {
          func_0x0001481d2100(puVar1,iVar4);
        }
        uVar5 = *puVar1;
        dVar11 = dVar11 + dVar9;
        pdVar20 = (double *)(uVar5 + lVar21 * 0x28);
        *pdVar20 = dStack_108;
        pdVar20[1] = dStack_100;
        puVar2 = (uint *)(uVar5 + 0x10 + lVar21 * 0x28);
        *puVar2 = uStack_f8;
        puVar2[1] = uStack_f4;
        puVar2[2] = (uint)uStack_f0;
        puVar2[3] = uStack_f0._4_4_;
        *(ulonglong *)(uVar5 + 0x20 + lVar21 * 0x28) = CONCAT44(fStack_e4,iStack_e8);
        if (1 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b318,dVar11);
        }
        iVar4 = iVar19 + 1;
        if (fVar3 < 0.0) {
          iVar4 = iVar19;
        }
        iVar19 = iVar4;
        uVar18 = (int)(uVar18 + 1) % iVar16;
        if (1 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b388);
        }
        iVar12 = iVar12 + 1;
      } while (iVar19 < param_4);
    }
    if (((1 < DAT_14eab53c8) &&
        (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b3f8), 1 < DAT_14eab53c8)) &&
       (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b450,*(undefined4 *)(param_1 + 0xf0),param_4),
       1 < DAT_14eab53c8)) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b4c0,dVar11 - param_6);
    }
    iVar16 = *(int *)(param_1 + 0xf0) + -1;
    if (10 < iVar16) {
      iVar16 = 10;
    }
    if (0 < iVar16) {
      lVar21 = 0;
      uVar18 = 0;
      do {
        uVar14 = 0;
        if ((int)uVar18 < *(int *)(param_1 + 0xf0)) {
          uVar14 = ~uVar18 >> 0x1f;
        }
        if ((uVar14 == 0) &&
           (cVar13 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                         &UNK_14bce6ef0,(longlong)(int)uVar18,
                                         (longlong)*(int *)(param_1 + 0xf0)), cVar13 != '\0')) {
          pcVar6 = (code *)swi(3);
          (*pcVar6)();
          return;
        }
        uVar14 = uVar18 + 1;
        pdVar20 = (double *)(*puVar1 + lVar21);
        uVar15 = 0;
        if ((int)uVar14 < *(int *)(param_1 + 0xf0)) {
          uVar15 = ~uVar14 >> 0x1f;
        }
        if ((uVar15 == 0) &&
           (cVar13 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                         &UNK_14bce6ef0,(longlong)(int)uVar14,
                                         (longlong)*(int *)(param_1 + 0xf0)), cVar13 != '\0')) {
          pcVar6 = (code *)swi(3);
          (*pcVar6)();
          return;
        }
        lVar21 = lVar21 + 0x28;
        if (1 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b530,uVar18,uVar14,
                              *(double *)(lVar21 + *puVar1) - *pdVar20);
        }
        iVar16 = *(int *)(param_1 + 0xf0) + -1;
        if (10 < iVar16) {
          iVar16 = 10;
        }
        uVar18 = uVar14;
      } while ((int)uVar14 < iVar16);
    }
    if (DAT_14eab53c8 < 2) {
      return;
    }
    puVar17 = &UNK_14cf7b5b8;
  }
  func_0x000140f24ba0(&DAT_14eab53c8,puVar17);
  return;
}



