
/* 14818dbb0 ParseFilenameTags */

/* WARNING: Removing unreachable block (ram,0x0001481907a7) */
/* WARNING: Removing unreachable block (ram,0x000148190563) */
/* WARNING: Removing unreachable block (ram,0x00014819031f) */
/* WARNING: Removing unreachable block (ram,0x0001481900db) */
/* WARNING: Removing unreachable block (ram,0x00014818fe97) */
/* WARNING: Removing unreachable block (ram,0x00014818fc53) */
/* WARNING: Removing unreachable block (ram,0x00014818fa0f) */
/* WARNING: Removing unreachable block (ram,0x00014818f7cb) */
/* WARNING: Removing unreachable block (ram,0x00014818f587) */
/* WARNING: Removing unreachable block (ram,0x00014818f343) */
/* WARNING: Removing unreachable block (ram,0x00014818f0ff) */
/* WARNING: Removing unreachable block (ram,0x00014818eebb) */
/* WARNING: Removing unreachable block (ram,0x00014818ec95) */
/* WARNING: Removing unreachable block (ram,0x00014818ea8d) */
/* WARNING: Removing unreachable block (ram,0x00014818e885) */
/* WARNING: Removing unreachable block (ram,0x00014818e67d) */
/* WARNING: Removing unreachable block (ram,0x00014818e475) */
/* WARNING: Removing unreachable block (ram,0x00014818e26d) */
/* WARNING: Removing unreachable block (ram,0x00014818e065) */
/* WARNING: Removing unreachable block (ram,0x00014818de53) */
/* WARNING: Removing unreachable block (ram,0x00014818dd4f) */
/* WARNING: Removing unreachable block (ram,0x00014818df57) */
/* WARNING: Removing unreachable block (ram,0x00014818e169) */
/* WARNING: Removing unreachable block (ram,0x00014818e371) */
/* WARNING: Removing unreachable block (ram,0x00014818e579) */
/* WARNING: Removing unreachable block (ram,0x00014818e781) */
/* WARNING: Removing unreachable block (ram,0x00014818e989) */
/* WARNING: Removing unreachable block (ram,0x00014818eb91) */
/* WARNING: Removing unreachable block (ram,0x00014818ed99) */
/* WARNING: Removing unreachable block (ram,0x00014818efdd) */
/* WARNING: Removing unreachable block (ram,0x00014818f221) */
/* WARNING: Removing unreachable block (ram,0x00014818f465) */
/* WARNING: Removing unreachable block (ram,0x00014818f6a9) */
/* WARNING: Removing unreachable block (ram,0x00014818f8ed) */
/* WARNING: Removing unreachable block (ram,0x00014818fb31) */
/* WARNING: Removing unreachable block (ram,0x00014818fd75) */
/* WARNING: Removing unreachable block (ram,0x00014818ffb9) */
/* WARNING: Removing unreachable block (ram,0x0001481901fd) */
/* WARNING: Removing unreachable block (ram,0x000148190441) */
/* WARNING: Removing unreachable block (ram,0x000148190685) */
/* WARNING: Removing unreachable block (ram,0x0001481908ab) */

ulonglong * ParseFilenameTags(ulonglong *param_1)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  undefined8 uVar4;
  ulonglong *puVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  undefined8 unaff_retaddr;
  undefined8 in_stack_fffffffffffffba8;
  uint uVar9;
  undefined *puVar8;
  undefined8 in_stack_fffffffffffffbb0;
  undefined4 uVar11;
  undefined8 *puVar10;
  longlong alStack_428 [2];
  undefined8 uStack_418;
  undefined8 uStack_410;
  undefined8 uStack_408;
  undefined8 uStack_400;
  undefined8 uStack_3f8;
  undefined8 uStack_3f0;
  undefined8 uStack_3e8;
  undefined8 uStack_3e0;
  undefined8 uStack_3d8;
  undefined8 uStack_3d0;
  undefined8 uStack_3c8;
  undefined8 uStack_3c0;
  undefined8 uStack_3b8;
  undefined8 uStack_3b0;
  undefined8 uStack_3a8;
  undefined8 uStack_3a0;
  undefined8 uStack_398;
  undefined8 uStack_390;
  undefined8 uStack_388;
  undefined8 uStack_380;
  undefined8 uStack_378;
  undefined8 uStack_370;
  undefined8 uStack_368;
  undefined8 uStack_360;
  undefined8 uStack_358;
  undefined8 uStack_350;
  undefined8 uStack_348;
  undefined8 uStack_340;
  undefined8 uStack_338;
  undefined8 uStack_330;
  undefined8 uStack_328;
  undefined8 uStack_320;
  undefined8 uStack_318;
  undefined8 uStack_310;
  undefined8 uStack_308;
  undefined8 uStack_300;
  undefined8 uStack_2f8;
  undefined8 uStack_2f0;
  undefined8 uStack_2e8;
  undefined8 uStack_2e0;
  undefined8 uStack_2d8;
  undefined8 uStack_2d0;
  undefined8 uStack_2c8;
  undefined8 uStack_2c0;
  undefined8 uStack_2b8;
  undefined8 uStack_2b0;
  undefined8 uStack_2a8;
  undefined8 uStack_2a0;
  undefined8 uStack_298;
  undefined8 uStack_290;
  undefined8 uStack_288;
  undefined8 uStack_280;
  undefined8 uStack_278;
  undefined8 uStack_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  undefined8 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined8 uStack_200;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined4 uStack_188;
  longlong alStack_180 [2];
  longlong alStack_170 [43];
  
  uVar9 = (uint)((ulonglong)in_stack_fffffffffffffba8 >> 0x20);
  uVar11 = (undefined4)((ulonglong)in_stack_fffffffffffffbb0 >> 0x20);
  puVar7 = &uStack_378;
  *param_1 = 0;
  param_1[1] = 0;
  uStack_188 = 1;
  uVar4 = func_0x00014106f2a0(alStack_170);
  uVar4 = func_0x00014106ed70(alStack_180,uVar4,1);
  func_0x000140d2fc80(uVar4,alStack_428);
  if (alStack_180[0] != 0) {
    func_0x000140e282f0();
  }
  if (alStack_170[0] != 0) {
    func_0x000140e282f0();
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)uVar9 << 0x20);
  iVar3 = func_0x000140d101c0(alStack_428,&UNK_14bd8b090,4,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_408,"slow");
    puVar6 = (undefined8 *)*param_1;
    if ((puVar6 <= &uStack_408) &&
       (&uStack_408 < puVar6 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar10 = &uStack_408;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar10,puVar6,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar10 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar6 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar6 = 0;
    *puVar6 = uStack_408;
    uStack_408 = 0;
    *(undefined4 *)(puVar6 + 1) = (undefined4)uStack_400;
    *(undefined4 *)((longlong)puVar6 + 0xc) = uStack_400._4_4_;
    uStack_400 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"fast",4,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_3f8,"fast");
    puVar6 = (undefined8 *)*param_1;
    if ((puVar6 <= &uStack_3f8) &&
       (&uStack_3f8 < puVar6 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar10 = &uStack_3f8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar10,puVar6,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar10 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar6 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar6 = 0;
    *puVar6 = uStack_3f8;
    uStack_3f8 = 0;
    *(undefined4 *)(puVar6 + 1) = (undefined4)uStack_3f0;
    *(undefined4 *)((longlong)puVar6 + 0xc) = uStack_3f0._4_4_;
    uStack_3f0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"medium",6,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_3e8,"medium");
    puVar6 = (undefined8 *)*param_1;
    if ((puVar6 <= &uStack_3e8) &&
       (&uStack_3e8 < puVar6 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar10 = &uStack_3e8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar10,puVar6,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar10 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar6 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar6 = 0;
    *puVar6 = uStack_3e8;
    uStack_3e8 = 0;
    *(undefined4 *)(puVar6 + 1) = (undefined4)uStack_3e0;
    *(undefined4 *)((longlong)puVar6 + 0xc) = uStack_3e0._4_4_;
    uStack_3e0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"anal",4,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_418,"anal");
    puVar6 = (undefined8 *)*param_1;
    if ((puVar6 <= &uStack_418) &&
       (&uStack_418 < puVar6 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar10 = &uStack_418;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar10,puVar6,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar10 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar6 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar6 = 0;
    *puVar6 = uStack_418;
    uStack_418 = 0;
    *(undefined4 *)(puVar6 + 1) = (undefined4)uStack_410;
    *(undefined4 *)((longlong)puVar6 + 0xc) = uStack_410._4_4_;
    uStack_410 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"armpits",7,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_3c8,"armpits");
    puVar6 = (undefined8 *)*param_1;
    if ((puVar6 <= &uStack_3c8) &&
       (&uStack_3c8 < puVar6 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar10 = &uStack_3c8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar10,puVar6,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar10 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar6 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar6 = 0;
    *puVar6 = uStack_3c8;
    uStack_3c8 = 0;
    *(undefined4 *)(puVar6 + 1) = (undefined4)uStack_3c0;
    *(undefined4 *)((longlong)puVar6 + 0xc) = uStack_3c0._4_4_;
    uStack_3c0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,&UNK_14cf61fb0,3,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_3b8,&UNK_14cf61fb8);
    puVar6 = (undefined8 *)*param_1;
    if ((puVar6 <= &uStack_3b8) &&
       (&uStack_3b8 < puVar6 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar10 = &uStack_3b8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar10,puVar6,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar10 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar6 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar6 = 0;
    *puVar6 = uStack_3b8;
    uStack_3b8 = 0;
    *(undefined4 *)(puVar6 + 1) = (undefined4)uStack_3b0;
    *(undefined4 *)((longlong)puVar6 + 0xc) = uStack_3b0._4_4_;
    uStack_3b0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"assjob",6,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_3a8,"assjob");
    puVar6 = (undefined8 *)*param_1;
    if ((puVar6 <= &uStack_3a8) &&
       (&uStack_3a8 < puVar6 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar10 = &uStack_3a8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar10,puVar6,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar10 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar6 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar6 = 0;
    *puVar6 = uStack_3a8;
    uStack_3a8 = 0;
    *(undefined4 *)(puVar6 + 1) = (undefined4)uStack_3a0;
    *(undefined4 *)((longlong)puVar6 + 0xc) = uStack_3a0._4_4_;
    uStack_3a0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"bent_over",9,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_398,"bent_over");
    puVar6 = (undefined8 *)*param_1;
    if ((puVar6 <= &uStack_398) &&
       (&uStack_398 < puVar6 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar10 = &uStack_398;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar10,puVar6,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar10 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar6 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar6 = 0;
    *puVar6 = uStack_398;
    uStack_398 = 0;
    *(undefined4 *)(puVar6 + 1) = (undefined4)uStack_390;
    *(undefined4 *)((longlong)puVar6 + 0xc) = uStack_390._4_4_;
    uStack_390 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"bikini",6,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_3d8,"bikini");
    puVar6 = (undefined8 *)*param_1;
    if ((puVar6 <= &uStack_3d8) &&
       (&uStack_3d8 < puVar6 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar10 = &uStack_3d8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar10,puVar6,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar10 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar6 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar6 = 0;
    *puVar6 = uStack_3d8;
    uStack_3d8 = 0;
    *(undefined4 *)(puVar6 + 1) = (undefined4)uStack_3d0;
    *(undefined4 *)((longlong)puVar6 + 0xc) = uStack_3d0._4_4_;
    uStack_3d0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"blowjob",7,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(puVar7,"blowjob");
    puVar6 = (undefined8 *)*param_1;
    if ((puVar6 <= puVar7) && (puVar7 < puVar6 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar7,puVar6,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar7 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_378;
    uStack_378 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_370;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_370._4_4_;
    uStack_370 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"boobs",5,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_368,"boobs");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_368) &&
       (&uStack_368 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_368;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_368;
    uStack_368 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_360;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_360._4_4_;
    uStack_360 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"bukkake",7,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_358,"bukkake");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_358) &&
       (&uStack_358 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_358;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_358;
    uStack_358 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_350;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_350._4_4_;
    uStack_350 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"cameltoe",8,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_348,"cameltoe");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_348) &&
       (&uStack_348 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_348;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_348;
    uStack_348 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_340;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_340._4_4_;
    uStack_340 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"cowgirl",7,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_338,"cowgirl");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_338) &&
       (&uStack_338 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_338;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_338;
    uStack_338 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_330;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_330._4_4_;
    uStack_330 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,&UNK_14cf620a0,3,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_328,&UNK_14cf620a8);
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_328) &&
       (&uStack_328 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_328;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_328;
    uStack_328 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_320;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_320._4_4_;
    uStack_320 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"cunnilingus",0xb,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_318,"cunnilingus");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_318) &&
       (&uStack_318 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_318;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_318;
    uStack_318 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_310;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_310._4_4_;
    uStack_310 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"doggystyle",10,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_308,"doggystyle");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_308) &&
       (&uStack_308 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_308;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_308;
    uStack_308 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_300;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_300._4_4_;
    uStack_300 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"facesitting",0xb,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_2f8,"facesitting");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_2f8) &&
       (&uStack_2f8 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_2f8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_2f8;
    uStack_2f8 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_2f0;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_2f0._4_4_;
    uStack_2f0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"feet",4,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_2e8,"feet");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_2e8) &&
       (&uStack_2e8 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_2e8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_2e8;
    uStack_2e8 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_2e0;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_2e0._4_4_;
    uStack_2e0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"fingering",9,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_2d8,"fingering");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_2d8) &&
       (&uStack_2d8 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_2d8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_2d8;
    uStack_2d8 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_2d0;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_2d0._4_4_;
    uStack_2d0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"footjob",7,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_2c8,"footjob");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_2c8) &&
       (&uStack_2c8 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_2c8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_2c8;
    uStack_2c8 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_2c0;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_2c0._4_4_;
    uStack_2c0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"futa",4,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_2b8,"futa");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_2b8) &&
       (&uStack_2b8 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_2b8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_2b8;
    uStack_2b8 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_2b0;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_2b0._4_4_;
    uStack_2b0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,&UNK_14cf62198,3,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_2a8,&UNK_14cf621a0);
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_2a8) &&
       (&uStack_2a8 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_2a8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_2a8;
    uStack_2a8 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_2a0;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_2a0._4_4_;
    uStack_2a0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"goth",4,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_298,"goth");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_298) &&
       (&uStack_298 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_298;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_298;
    uStack_298 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_290;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_290._4_4_;
    uStack_290 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,&UNK_14bd8b040,5,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_288,"group");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_288) &&
       (&uStack_288 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_288;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_288;
    uStack_288 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_280;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_280._4_4_;
    uStack_280 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"handjob",7,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_278,"handjob");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_278) &&
       (&uStack_278 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_278;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_278;
    uStack_278 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_270;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_270._4_4_;
    uStack_270 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"latex",5,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_268,"latex");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_268) &&
       (&uStack_268 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_268;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_268;
    uStack_268 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_260;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_260._4_4_;
    uStack_260 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"leggings",8,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_258,"leggings");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_258) &&
       (&uStack_258 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_258;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_258;
    uStack_258 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_250;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_250._4_4_;
    uStack_250 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"lingerie",8,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_248,"lingerie");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_248) &&
       (&uStack_248 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_248;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_248;
    uStack_248 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_240;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_240._4_4_;
    uStack_240 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"nude",4,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_238,"nude");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_238) &&
       (&uStack_238 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_238;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_238;
    uStack_238 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_230;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_230._4_4_;
    uStack_230 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"paizuri",7,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_228,"paizuri");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_228) &&
       (&uStack_228 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_228;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_228;
    uStack_228 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_220;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_220._4_4_;
    uStack_220 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"pussy",5,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_218,"pussy");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_218) &&
       (&uStack_218 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_218;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_218;
    uStack_218 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_210;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_210._4_4_;
    uStack_210 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,&UNK_14cf62290,3,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_208,&UNK_14cf62298);
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_208) &&
       (&uStack_208 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_208;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_208;
    uStack_208 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_200;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_200._4_4_;
    uStack_200 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"small_penis",0xb,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_1f8,"small_penis");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_1f8) &&
       (&uStack_1f8 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_1f8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_1f8;
    uStack_1f8 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_1f0;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_1f0._4_4_;
    uStack_1f0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"spreading",9,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_1e8,"spreading");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_1e8) &&
       (&uStack_1e8 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_1e8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_1e8;
    uStack_1e8 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_1e0;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_1e0._4_4_;
    uStack_1e0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"succubus",8,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_1d8,"succubus");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_1d8) &&
       (&uStack_1d8 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_1d8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_1d8;
    uStack_1d8 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_1d0;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_1d0._4_4_;
    uStack_1d0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"thighjob",8,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_1c8,"thighjob");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_1c8) &&
       (&uStack_1c8 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_1c8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_1c8;
    uStack_1c8 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_1c0;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_1c0._4_4_;
    uStack_1c0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"thighs",6,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_1b8,"thighs");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_1b8) &&
       (&uStack_1b8 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_1b8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_1b8;
    uStack_1b8 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_1b0;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_1b0._4_4_;
    uStack_1b0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"uniform",7,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_1a8,"uniform");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_1a8) &&
       (&uStack_1a8 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_1a8;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_1a8;
    uStack_1a8 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_1a0;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_1a0._4_4_;
    uStack_1a0 = 0;
  }
  uVar4 = CONCAT44(uVar11,0xffffffff);
  puVar8 = (undefined *)((ulonglong)puVar8 & 0xffffffff00000000);
  iVar3 = func_0x000140d101c0(alStack_428,L"upskirt",7,1,puVar8,uVar4);
  uVar11 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_198,"upskirt");
    puVar7 = (undefined8 *)*param_1;
    if ((puVar7 <= &uStack_198) &&
       (&uStack_198 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) {
      puVar6 = &uStack_198;
      puVar8 = &UNK_14bce6d80;
      cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  puVar6,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                  (longlong)(int)param_1[1],0x10);
      uVar11 = (undefined4)((ulonglong)puVar6 >> 0x20);
      if (cVar2 != '\0') {
        pcVar1 = (code *)swi(3);
        puVar5 = (ulonglong *)(*pcVar1)();
        return puVar5;
      }
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_198;
    uStack_198 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_190;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_190._4_4_;
    uStack_190 = 0;
  }
  iVar3 = func_0x000140d101c0(alStack_428,L"vaginal",7,1,(ulonglong)puVar8 & 0xffffffff00000000,
                              CONCAT44(uVar11,0xffffffff));
  if (iVar3 != -1) {
    func_0x000140cf7080(&uStack_388,"vaginal");
    puVar7 = (undefined8 *)*param_1;
    if (((puVar7 <= &uStack_388) &&
        (&uStack_388 < puVar7 + (longlong)*(int *)((longlong)param_1 + 0xc) * 2)) &&
       (cVar2 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80
                                    ,&uStack_388,puVar7,(longlong)*(int *)((longlong)param_1 + 0xc),
                                    (longlong)(int)param_1[1],0x10), cVar2 != '\0')) {
      pcVar1 = (code *)swi(3);
      puVar5 = (ulonglong *)(*pcVar1)();
      return puVar5;
    }
    iVar3 = (int)param_1[1];
    *(uint *)(param_1 + 1) = iVar3 + 1U;
    if (*(uint *)((longlong)param_1 + 0xc) < iVar3 + 1U) {
      func_0x000140ca4b30(param_1,iVar3);
    }
    puVar7 = (undefined8 *)((longlong)iVar3 * 0x10 + *param_1);
    *puVar7 = 0;
    *puVar7 = uStack_388;
    uStack_388 = 0;
    *(undefined4 *)(puVar7 + 1) = (undefined4)uStack_380;
    *(undefined4 *)((longlong)puVar7 + 0xc) = uStack_380._4_4_;
    uStack_380 = 0;
  }
  if (alStack_428[0] != 0) {
    func_0x000140e282f0();
  }
  return param_1;
}


/* Instruction evidence:
14818dbb0 MOV qword ptr [RSP + 0x10],RBX
14818dbb5 MOV qword ptr [RSP + 0x18],RSI
14818dbba MOV qword ptr [RSP + 0x8],RCX
14818dbbf PUSH RBP
14818dbc0 PUSH RDI
14818dbc1 PUSH R14
14818dbc3 LEA RBP,[RSP + -0x360]
14818dbcb SUB RSP,0x460
14818dbd2 MOV RBX,RCX
14818dbd5 XOR ESI,ESI
14818dbd7 MOV dword ptr [RBP + 0x1f0],ESI
14818dbdd MOV qword ptr [RCX],RSI
14818dbe0 MOV qword ptr [RCX + 0x8],RSI
14818dbe4 MOV dword ptr [RBP + 0x1f0],0x1
14818dbee LEA RCX,[RBP + 0x208]
14818dbf5 CALL 0x14106f2a0
14818dbfa NOP
14818dbfb MOV R8B,0x1
14818dbfe MOV RDX,RAX
14818dc01 LEA RCX,[RBP + 0x1f8]
14818dc08 CALL 0x14106ed70
14818dc0d NOP
14818dc0e LEA RDX,[RSP + 0x50]
14818dc13 MOV RCX,RAX
14818dc16 CALL 0x140d2fc80
14818dc1b NOP
14818dc1c MOV RCX,qword ptr [RBP + 0x1f8]
14818dc23 TEST RCX,RCX
14818dc26 JZ 0x14818dc2e
14818dc28 CALL 0x140e282f0
14818dc2d NOP
14818dc2e MOV RCX,qword ptr [RBP + 0x208]
14818dc35 TEST RCX,RCX
14818dc38 JZ 0x14818dc40
14818dc3a CALL 0x140e282f0
14818dc3f NOP
14818dc40 MOV dword ptr [RSP + 0x28],0xffffffff
14818dc48 MOV dword ptr [RSP + 0x20],ESI
14818dc4c MOV R9D,0x1
14818dc52 LEA R8D,[R9 + 0x3]
14818dc56 LEA RDX,[0x14bd8b090]
14818dc5d LEA RCX,[RSP + 0x50]
14818dc62 CALL 0x140d101c0
14818dc67 LEA R14,[0x14bce6d80]
14818dc6e CMP EAX,-0x1
14818dc71 JZ 0x14818dd55
14818dc77 LEA RDX,[0x14cf61f48]
14818dc7e LEA RCX,[RSP + 0x70]
14818dc83 CALL 0x140cf7080
14818dc88 NOP
14818dc89 MOV RCX,qword ptr [RBX]
14818dc8c LEA RAX,[RSP + 0x70]
14818dc91 CMP RAX,RCX
14818dc94 JC 0x14818dcff
14818dc96 MOVSXD RDX,dword ptr [RBX + 0xc]
14818dc9a MOV RAX,RDX
14818dc9d SHL RAX,0x4
14818dca1 ADD RAX,RCX
14818dca4 LEA R8,[RSP + 0x70]
14818dca9 CMP R8,RAX
14818dcac JNC 0x14818dcff
14818dcae MOVSXD RAX,dword ptr [RBX + 0x8]
14818dcb2 MOV R9,qword ptr [RBP + 0x378]
14818dcb9 MOV qword ptr [RSP + 0x48],0x10
14818dcc2 MOV qword ptr [RSP + 0x40],RAX
14818dcc7 MOV qword ptr [RSP + 0x38],RDX
14818dccc MOV qword ptr [RSP + 0x30],RCX
14818dcd1 LEA RAX,[RSP + 0x70]
14818dcd6 MOV qword ptr [RSP + 0x28],RAX
14818dcdb MOV qword ptr [RSP + 0x20],R14
14818dce0 MOV R8D,0x63e
14818dce6 LEA RDX,[0x14cf27ac0]
14818dced LEA RCX,[0x14bce6eb8]
14818dcf4 CALL 0x140f8dfd0
14818dcf9 TEST AL,AL
14818dcfb JZ 0x14818dcff
14818dcfd NOP
14818dcfe INT3
14818dcff MOVSXD RDI,dword ptr [RBX + 0x8]
14818dd03 LEA EAX,[RDI + 0x1]
14818dd06 MOV dword ptr [RBX + 0x8],EAX
14818dd09 CMP EAX,dword ptr [RBX + 0xc]
14818dd0c JBE 0x14818dd18
14818dd0e MOV EDX,EDI
14818dd10 MOV RCX,RBX
14818dd13 CALL 0x140ca4b30
14818dd18 MOV RCX,RDI
14818dd1b SHL RCX,0x4
14818dd1f ADD RCX,qword ptr [RBX]
14818dd22 MOV qword ptr [RCX],RSI
14818dd25 MOV RAX,qword ptr [RSP + 0x70]
14818dd2a MOV qword ptr [RCX],RAX
14818dd2d MOV qword ptr [RSP + 0x70],RSI
14818dd32 MOV EAX,dword ptr [RSP + 0x78]
14818dd36 MOV dword ptr [RCX + 0x8],EAX
14818dd39 MOV EAX,dword ptr [RSP + 0x7c]
14818dd3d MOV dword ptr [RCX + 0xc],EAX
14818dd40 MOV qword ptr [RSP + 0x78],RSI
14818dd45 MOV RCX,qword ptr [RSP + 0x70]
14818dd4a TEST RCX,RCX
14818dd4d JZ 0x14818dd55
14818dd4f CALL 0x140e282f0
14818dd54 NOP
14818dd55 MOV dword ptr [RSP + 0x28],0xffffffff
14818dd5d MOV dword ptr [RSP + 0x20],ESI
14818dd61 MOV R9D,0x1
14818dd67 LEA R8D,[R9 + 0x3]
14818dd6b LEA RDX,[0x14cf61f50]
14818dd72 LEA RCX,[RSP + 0x50]
14818dd77 CALL 0x140d101c0
14818dd7c CMP EAX,-0x1
14818dd7f JZ 0x14818de59
14818dd85 LEA RDX,[0x14cf61f5c]
14818dd8c LEA RCX,[RBP + -0x80]
14818dd90 CALL 0x140cf7080
14818dd95 NOP
14818dd96 MOV RCX,qword ptr [RBX]
14818dd99 LEA RAX,[RBP + -0x80]
14818dd9d CMP RAX,RCX
14818dda0 JC 0x14818de09
14818dda2 MOVSXD RDX,dword ptr [RBX + 0xc]
14818dda6 MOV RAX,RDX
14818dda9 SHL RAX,0x4
14818ddad ADD RAX,RCX
14818ddb0 LEA R8,[RBP + -0x80]
14818ddb4 CMP R8,RAX
14818ddb7 JNC 0x14818de09
14818ddb9 MOVSXD RAX,dword ptr [RBX + 0x8]
14818ddbd MOV R9,qword ptr [RBP + 0x378]
14818ddc4 MOV qword ptr [RSP + 0x48],0x10
14818ddcd MOV qword ptr [RSP + 0x40],RAX
14818ddd2 MOV qword ptr [RSP + 0x38],RDX
14818ddd7 MOV qword ptr [RSP + 0x30],RCX
14818dddc LEA RAX,[RBP + -0x80]
14818dde0 MOV qword ptr [RSP + 0x28],RAX
14818dde5 MOV qword ptr [RSP + 0x20],R14
14818ddea MOV R8D,0x63e
14818ddf0 LEA RDX,[0x14cf27ac0]
14818ddf7 LEA RCX,[0x14bce6eb8]
14818ddfe CALL 0x140f8dfd0
14818de03 TEST AL,AL
14818de05 JZ 0x14818de09
14818de07 NOP
14818de08 INT3
14818de09 MOVSXD RDI,dword ptr [RBX + 0x8]
14818de0d LEA EAX,[RDI + 0x1]
14818de10 MOV dword ptr [RBX + 0x8],EAX
14818de13 CMP EAX,dword ptr [RBX + 0xc]
14818de16 JBE 0x14818de22
14818de18 MOV EDX,EDI
14818de1a MOV RCX,RBX
14818de1d CALL 0x140ca4b30
14818de22 MOV RCX,RDI
14818de25 SHL RCX,0x4
14818de29 ADD RCX,qword ptr [RBX]
14818de2c MOV qword ptr [RCX],RSI
14818de2f MOV RAX,qword ptr [RBP + -0x80]
14818de33 MOV qword ptr [RCX],RAX
14818de36 MOV qword ptr [RBP + -0x80],RSI
14818de3a MOV EAX,dword ptr [RBP + -0x78]
14818de3d MOV dword ptr [RCX + 0x8],EAX
14818de40 MOV EAX,dword ptr [RBP + -0x74]
14818de43 MOV dword ptr [RCX + 0xc],EAX
14818de46 MOV qword ptr [RBP + -0x78],RSI
14818de4a MOV RCX,qword ptr [RBP + -0x80]
14818de4e TEST RCX,RCX
14818de51 JZ 0x14818de59
14818de53 CALL 0x140e282f0
14818de58 NOP
14818de59 MOV dword ptr [RSP + 0x28],0xffffffff
14818de61 MOV dword ptr [RSP + 0x20],ESI
14818de65 MOV R9D,0x1
14818de6b LEA R8D,[R9 + 0x5]
14818de6f LEA RDX,[0x14cf61f68]
14818de76 LEA RCX,[RSP + 0x50]
14818de7b CALL 0x140d101c0
14818de80 CMP EAX,-0x1
14818de83 JZ 0x14818df5d
14818de89 LEA RDX,[0x14cf61f78]
14818de90 LEA RCX,[RBP + -0x70]
14818de94 CALL 0x140cf7080
14818de99 NOP
14818de9a MOV RCX,qword ptr [RBX]
14818de9d LEA RAX,[RBP + -0x70]
14818dea1 CMP RAX,RCX
14818dea4 JC 0x14818df0d
14818dea6 MOVSXD RDX,dword ptr [RBX + 0xc]
14818deaa MOV RAX,RDX
14818dead SHL RAX,0x4
14818deb1 ADD RAX,RCX
14818deb4 LEA R8,[RBP + -0x70]
14818deb8 CMP R8,RAX
14818debb JNC 0x14818df0d
14818debd MOVSXD RAX,dword ptr [RBX + 0x8]
14818dec1 MOV R9,qword ptr [RBP + 0x378]
14818dec8 MOV qword ptr [RSP + 0x48],0x10
14818ded1 MOV qword ptr [RSP + 0x40],RAX
14818ded6 MOV qword ptr [RSP + 0x38],RDX
14818dedb MOV qword ptr [RSP + 0x30],RCX
14818dee0 LEA RAX,[RBP + -0x70]
14818dee4 MOV qword ptr [RSP + 0x28],RAX
14818dee9 MOV qword ptr [RSP + 0x20],R14
14818deee MOV R8D,0x63e
14818def4 LEA RDX,[0x14cf27ac0]
14818defb LEA RCX,[0x14bce6eb8]
14818df02 CALL 0x140f8dfd0
14818df07 TEST AL,AL
14818df09 JZ 0x14818df0d
14818df0b NOP
14818df0c INT3
14818df0d MOVSXD RDI,dword ptr [RBX + 0x8]
14818df11 LEA EAX,[RDI + 0x1]
14818df14 MOV dword ptr [RBX + 0x8],EAX
14818df17 CMP EAX,dword ptr [RBX + 0xc]
14818df1a JBE 0x14818df26
14818df1c MOV EDX,EDI
14818df1e MOV RCX,RBX
14818df21 CALL 0x140ca4b30
14818df26 MOV RCX,RDI
14818df29 SHL RCX,0x4
14818df2d ADD RCX,qword ptr [RBX]
14818df30 MOV qword ptr [RCX],RSI
14818df33 MOV RAX,qword ptr [RBP + -0x70]
14818df37 MOV qword ptr [RCX],RAX
14818df3a MOV qword ptr [RBP + -0x70],RSI
14818df3e MOV EAX,dword ptr [RBP + -0x68]
14818df41 MOV dword ptr [RCX + 0x8],EAX
14818df44 MOV EAX,dword ptr [RBP + -0x64]
14818df47 MOV dword ptr [RCX + 0xc],EAX
14818df4a MOV qword ptr [RBP + -0x68],RSI
14818df4e MOV RCX,qword ptr [RBP + -0x70]
14818df52 TEST RCX,RCX
14818df55 JZ 0x14818df5d
14818df57 CALL 0x140e282f0
14818df5c NOP
14818df5d MOV dword ptr [RSP + 0x28],0xffffffff
14818df65 MOV dword ptr [RSP + 0x20],ESI
14818df69 MOV R9D,0x1
14818df6f LEA R8D,[R9 + 0x3]
14818df73 LEA RDX,[0x14cf61f80]
14818df7a LEA RCX,[RSP + 0x50]
14818df7f CALL 0x140d101c0
14818df84 CMP EAX,-0x1
14818df87 JZ 0x14818e06b
14818df8d LEA RDX,[0x14cf61f8c]
14818df94 LEA RCX,[RSP + 0x60]
14818df99 CALL 0x140cf7080
14818df9e NOP
14818df9f MOV RCX,qword ptr [RBX]
14818dfa2 LEA RAX,[RSP + 0x60]
14818dfa7 CMP RAX,RCX
14818dfaa JC 0x14818e015
14818dfac MOVSXD RDX,dword ptr [RBX + 0xc]
14818dfb0 MOV RAX,RDX
14818dfb3 SHL RAX,0x4
14818dfb7 ADD RAX,RCX
14818dfba LEA R8,[RSP + 0x60]
14818dfbf CMP R8,RAX
14818dfc2 JNC 0x14818e015
14818dfc4 MOVSXD RAX,dword ptr [RBX + 0x8]
14818dfc8 MOV R9,qword ptr [RBP + 0x378]
14818dfcf MOV qword ptr [RSP + 0x48],0x10
14818dfd8 MOV qword ptr [RSP + 0x40],RAX
14818dfdd MOV qword ptr [RSP + 0x38],RDX
14818dfe2 MOV qword ptr [RSP + 0x30],RCX
14818dfe7 LEA RAX,[RSP + 0x60]
14818dfec MOV qword ptr [RSP + 0x28],RAX
14818dff1 MOV qword ptr [RSP + 0x20],R14
14818dff6 MOV R8D,0x63e
14818dffc LEA RDX,[0x14cf27ac0]
14818e003 LEA RCX,[0x14bce6eb8]
14818e00a CALL 0x140f8dfd0
14818e00f TEST AL,AL
14818e011 JZ 0x14818e015
14818e013 NOP
14818e014 INT3
14818e015 MOVSXD RDI,dword ptr [RBX + 0x8]
14818e019 LEA EAX,[RDI + 0x1]
14818e01c MOV dword ptr [RBX + 0x8],EAX
14818e01f CMP EAX,dword ptr [RBX + 0xc]
14818e022 JBE 0x14818e02e
14818e024 MOV EDX,EDI
14818e026 MOV RCX,RBX
14818e029 CALL 0x140ca4b30
14818e02e MOV RCX,RDI
14818e031 SHL RCX,0x4
14818e035 ADD RCX,qword ptr [RBX]
14818e038 MOV qword ptr [RCX],RSI
14818e03b MOV RAX,qword ptr [RSP + 0x60]
14818e040 MOV qword ptr [RCX],RAX
14818e043 MOV qword ptr [RSP + 0x60],RSI
14818e048 MOV EAX,dword ptr [RSP + 0x68]
14818e04c MOV dword ptr [RCX + 0x8],EAX
14818e04f MOV EAX,dword ptr [RSP + 0x6c]
14818e053 MOV dword ptr [RCX + 0xc],EAX
14818e056 MOV qword ptr [RSP + 0x68],RSI
14818e05b MOV RCX,qword ptr [RSP + 0x60]
14818e060 TEST RCX,RCX
14818e063 JZ 0x14818e06b
14818e065 CALL 0x140e282f0
14818e06a NOP
14818e06b MOV dword ptr [RSP + 0x28],0xffffffff
14818e073 MOV dword ptr [RSP + 0x20],ESI
14818e077 MOV R9D,0x1
14818e07d LEA R8D,[R9 + 0x6]
14818e081 LEA RDX,[0x14cf61f98]
14818e088 LEA RCX,[RSP + 0x50]
14818e08d CALL 0x140d101c0
14818e092 CMP EAX,-0x1
14818e095 JZ 0x14818e16f
14818e09b LEA RDX,[0x14cf61fa8]
14818e0a2 LEA RCX,[RBP + -0x50]
14818e0a6 CALL 0x140cf7080
14818e0ab NOP
14818e0ac MOV RCX,qword ptr [RBX]
14818e0af LEA RAX,[RBP + -0x50]
14818e0b3 CMP RAX,RCX
14818e0b6 JC 0x14818e11f
14818e0b8 MOVSXD RDX,dword ptr [RBX + 0xc]
14818e0bc MOV RAX,RDX
14818e0bf SHL RAX,0x4
14818e0c3 ADD RAX,RCX
14818e0c6 LEA R8,[RBP + -0x50]
14818e0ca CMP R8,RAX
14818e0cd JNC 0x14818e11f
14818e0cf MOVSXD RAX,dword ptr [RBX + 0x8]
14818e0d3 MOV R9,qword ptr [RBP + 0x378]
14818e0da MOV qword ptr [RSP + 0x48],0x10
14818e0e3 MOV qword ptr [RSP + 0x40],RAX
14818e0e8 MOV qword ptr [RSP + 0x38],RDX
14818e0ed MOV qword ptr [RSP + 0x30],RCX
14818e0f2 LEA RAX,[RBP + -0x50]
14818e0f6 MOV qword ptr [RSP + 0x28],RAX
14818e0fb MOV qword ptr [RSP + 0x20],R14
14818e100 MOV R8D,0x63e
14818e106 LEA RDX,[0x14cf27ac0]
14818e10d LEA RCX,[0x14bce6eb8]
14818e114 CALL 0x140f8dfd0
14818e119 TEST AL,AL
14818e11b JZ 0x14818e11f
14818e11d NOP
14818e11e INT3
14818e11f MOVSXD RDI,dword ptr [RBX + 0x8]
14818e123 LEA EAX,[RDI + 0x1]
14818e126 MOV dword ptr [RBX + 0x8],EAX
14818e129 CMP EAX,dword ptr [RBX + 0xc]
14818e12c JBE 0x14818e138
14818e12e MOV EDX,EDI
14818e130 MOV RCX,RBX
14818e133 CALL 0x140ca4b30
14818e138 MOV RCX,RDI
14818e13b SHL RCX,0x4
14818e13f ADD RCX,qword ptr [RBX]
14818e142 MOV qword ptr [RCX],RSI
14818e145 MOV RAX,qword ptr [RBP + -0x50]
14818e149 MOV qword ptr [RCX],RAX
14818e14c MOV qword ptr [RBP + -0x50],RSI
14818e150 MOV EAX,dword ptr [RBP + -0x48]
14818e153 MOV dword ptr [RCX + 0x8],EAX
14818e156 MOV EAX,dword ptr [RBP + -0x44]
14818e159 MOV dword ptr [RCX + 0xc],EAX
14818e15c MOV qword ptr [RBP + -0x48],RSI
14818e160 MOV RCX,qword ptr [RBP + -0x50]
14818e164 TEST RCX,RCX
14818e167 JZ 0x14818e16f
14818e169 CALL 0x140e282f0
14818e16e NOP
14818e16f MOV dword ptr [RSP + 0x28],0xffffffff
14818e177 MOV dword ptr [RSP + 0x20],ESI
14818e17b MOV R9D,0x1
14818e181 LEA R8D,[R9 + 0x2]
14818e185 LEA RDX,[0x14cf61fb0]
14818e18c LEA RCX,[RSP + 0x50]
14818e191 CALL 0x140d101c0
14818e196 CMP EAX,-0x1
14818e199 JZ 0x14818e273
14818e19f LEA RDX,[0x14cf61fb8]
14818e1a6 LEA RCX,[RBP + -0x40]
14818e1aa CALL 0x140cf7080
14818e1af NOP
14818e1b0 MOV RCX,qword ptr [RBX]
14818e1b3 LEA RAX,[RBP + -0x40]
14818e1b7 CMP RAX,RCX
14818e1ba JC 0x14818e223
14818e1bc MOVSXD RDX,dword ptr [RBX + 0xc]
14818e1c0 MOV RAX,RDX
14818e1c3 SHL RAX,0x4
14818e1c7 ADD RAX,RCX
14818e1ca LEA R8,[RBP + -0x40]
14818e1ce CMP R8,RAX
14818e1d1 JNC 0x14818e223
14818e1d3 MOVSXD RAX,dword ptr [RBX + 0x8]
14818e1d7 MOV R9,qword ptr [RBP + 0x378]
14818e1de MOV qword ptr [RSP + 0x48],0x10
14818e1e7 MOV qword ptr [RSP + 0x40],RAX
14818e1ec MOV qword ptr [RSP + 0x38],RDX
14818e1f1 MOV qword ptr [RSP + 0x30],RCX
14818e1f6 LEA RAX,[RBP + -0x40]
14818e1fa MOV qword ptr [RSP + 0x28],RAX
14818e1ff MOV qword ptr [RSP + 0x20],R14
14818e204 MOV R8D,0x63e
14818e20a LEA RDX,[0x14cf27ac0]
14818e211 LEA RCX,[0x14bce6eb8]
14818e218 CALL 0x140f8dfd0
14818e21d TEST AL,AL
14818e21f JZ 0x14818e223
14818e221 NOP
14818e222 INT3
14818e223 MOVSXD RDI,dword ptr [RBX + 0x8]
14818e227 LEA EAX,[RDI + 0x1]
14818e22a MOV dword ptr [RBX + 0x8],EAX
14818e22d CMP EAX,dword ptr [RBX + 0xc]
14818e230 JBE 0x14818e23c
14818e232 MOV EDX,EDI
14818e234 MOV RCX,RBX
14818e237 CALL 0x140ca4b30
14818e23c MOV RCX,RDI
14818e23f SHL RCX,0x4
14818e243 ADD RCX,qword ptr [RBX]
14818e246 MOV qword ptr [RCX],RSI
14818e249 MOV RAX,qword ptr [RBP + -0x40]
14818e24d MOV qword ptr [RCX],RAX
14818e250 MOV qword ptr [RBP + -0x40],RSI
14818e254 MOV EAX,dword ptr [RBP + -0x38]
14818e257 MOV dword ptr [RCX + 0x8],EAX
14818e25a MOV EAX,dword ptr [RBP + -0x34]
14818e25d MOV dword ptr [RCX + 0xc],EAX
14818e260 MOV qword ptr [RBP + -0x38],RSI
14818e264 MOV RCX,qword ptr [RBP + -0x40]
14818e268 TEST RCX,RCX
14818e26b JZ 0x14818e273
14818e26d CALL 0x140e282f0
14818e272 NOP
14818e273 MOV dword ptr [RSP + 0x28],0xffffffff
14818e27b MOV dword ptr [RSP + 0x20],ESI
14818e27f MOV R9D,0x1
14818e285 LEA R8D,[R9 + 0x5]
14818e289 LEA RDX,[0x14cf61fc0]
14818e290 LEA RCX,[RSP + 0x50]
14818e295 CALL 0x140d101c0
14818e29a CMP EAX,-0x1
14818e29d JZ 0x14818e377
14818e2a3 LEA RDX,[0x14cf61fd0]
14818e2aa LEA RCX,[RBP + -0x30]
14818e2ae CALL 0x140cf7080
14818e2b3 NOP
14818e2b4 MOV RCX,qword ptr [RBX]
14818e2b7 LEA RAX,[RBP + -0x30]
14818e2bb CMP RAX,RCX
14818e2be JC 0x14818e327
14818e2c0 MOVSXD RDX,dword ptr [RBX + 0xc]
14818e2c4 MOV RAX,RDX
14818e2c7 SHL RAX,0x4
14818e2cb ADD RAX,RCX
14818e2ce LEA R8,[RBP + -0x30]
14818e2d2 CMP R8,RAX
14818e2d5 JNC 0x14818e327
14818e2d7 MOVSXD RAX,dword ptr [RBX + 0x8]
14818e2db MOV R9,qword ptr [RBP + 0x378]
14818e2e2 MOV qword ptr [RSP + 0x48],0x10
14818e2eb MOV qword ptr [RSP + 0x40],RAX
14818e2f0 MOV qword ptr [RSP + 0x38],RDX
14818e2f5 MOV qword ptr [RSP + 0x30],RCX
14818e2fa LEA RAX,[RBP + -0x30]
14818e2fe MOV qword ptr [RSP + 0x28],RAX
14818e303 MOV qword ptr [RSP + 0x20],R14
14818e308 MOV R8D,0x63e
14818e30e LEA RDX,[0x14cf27ac0]
14818e315 LEA RCX,[0x14bce6eb8]
14818e31c CALL 0x140f8dfd0
14818e321 TEST AL,AL
14818e323 JZ 0x14818e327
14818e325 NOP
14818e326 INT3
14818e327 MOVSXD RDI,dword ptr [RBX + 0x8]
14818e32b LEA EAX,[RDI + 0x1]
14818e32e MOV dword ptr [RBX + 0x8],EAX
14818e331 CMP EAX,dword ptr [RBX + 0xc]
14818e334 JBE 0x14818e340
14818e336 MOV EDX,EDI
14818e338 MOV RCX,RBX
14818e33b CALL 0x140ca4b30
14818e340 MOV RCX,RDI
14818e343 SHL RCX,0x4
14818e347 ADD RCX,qword ptr [RBX]
14818e34a MOV qword ptr [RCX],RSI
14818e34d MOV RAX,qword ptr [RBP + -0x30]
14818e351 MOV qword ptr [RCX],RAX
14818e354 MOV qword ptr [RBP + -0x30],RSI
14818e358 MOV EAX,dword ptr [RBP + -0x28]
14818e35b MOV dword ptr [RCX + 0x8],EAX
14818e35e MOV EAX,dword ptr [RBP + -0x24]
14818e361 MOV dword ptr [RCX + 0xc],EAX
14818e364 MOV qword ptr [RBP + -0x28],RSI
14818e368 MOV RCX,qword ptr [RBP + -0x30]
14818e36c TEST RCX,RCX
14818e36f JZ 0x14818e377
14818e371 CALL 0x140e282f0
14818e376 NOP
14818e377 MOV dword ptr [RSP + 0x28],0xffffffff
14818e37f MOV dword ptr [RSP + 0x20],ESI
14818e383 MOV R9D,0x1
14818e389 LEA R8D,[R9 + 0x8]
14818e38d LEA RDX,[0x14cf61fd8]
14818e394 LEA RCX,[RSP + 0x50]
14818e399 CALL 0x140d101c0
14818e39e CMP EAX,-0x1
14818e3a1 JZ 0x14818e47b
14818e3a7 LEA RDX,[0x14cf61ff0]
14818e3ae LEA RCX,[RBP + -0x20]
14818e3b2 CALL 0x140cf7080
14818e3b7 NOP
14818e3b8 MOV RCX,qword ptr [RBX]
14818e3bb LEA RAX,[RBP + -0x20]
14818e3bf CMP RAX,RCX
14818e3c2 JC 0x14818e42b
14818e3c4 MOVSXD RDX,dword ptr [RBX + 0xc]
14818e3c8 MOV RAX,RDX
14818e3cb SHL RAX,0x4
14818e3cf ADD RAX,RCX
14818e3d2 LEA R8,[RBP + -0x20]
14818e3d6 CMP R8,RAX
14818e3d9 JNC 0x14818e42b
14818e3db MOVSXD RAX,dword ptr [RBX + 0x8]
14818e3df MOV R9,qword ptr [RBP + 0x378]
14818e3e6 MOV qword ptr [RSP + 0x48],0x10
14818e3ef MOV qword ptr [RSP + 0x40],RAX
14818e3f4 MOV qword ptr [RSP + 0x38],RDX
14818e3f9 MOV qword ptr [RSP + 0x30],RCX
14818e3fe LEA RAX,[RBP + -0x20]
14818e402 MOV qword ptr [RSP + 0x28],RAX
14818e407 MOV qword ptr [RSP + 0x20],R14
14818e40c MOV R8D,0x63e
14818e412 LEA RDX,[0x14cf27ac0]
14818e419 LEA RCX,[0x14bce6eb8]
14818e420 CALL 0x140f8dfd0
14818e425 TEST AL,AL
14818e427 JZ 0x14818e42b
14818e429 NOP
14818e42a INT3
14818e42b MOVSXD RDI,dword ptr [RBX + 0x8]
14818e42f LEA EAX,[RDI + 0x1]
14818e432 MOV dword ptr [RBX + 0x8],EAX
14818e435 CMP EAX,dword ptr [RBX + 0xc]
14818e438 JBE 0x14818e444
14818e43a MOV EDX,EDI
14818e43c MOV RCX,RBX
14818e43f CALL 0x140ca4b30
14818e444 MOV RCX,RDI
14818e447 SHL RCX,0x4
14818e44b ADD RCX,qword ptr [RBX]
14818e44e MOV qword ptr [RCX],RSI
14818e451 MOV RAX,qword ptr [RBP + -0x20]
14818e455 MOV qword ptr [RCX],RAX
14818e458 MOV qword ptr [RBP + -0x20],RSI
14818e45c MOV EAX,dword ptr [RBP + -0x18]
14818e45f MOV dword ptr [RCX + 0x8],EAX
14818e462 MOV EAX,dword ptr [RBP + -0x14]
14818e465 MOV dword ptr [RCX + 0xc],EAX
14818e468 MOV qword ptr [RBP + -0x18],RSI
14818e46c MOV RCX,qword ptr [RBP + -0x20]
14818e470 TEST RCX,RCX
14818e473 JZ 0x14818e47b
14818e475 CALL 0x140e282f0
14818e47a NOP
14818e47b MOV dword ptr [RSP + 0x28],0xffffffff
14818e483 MOV dword ptr [RSP + 0x20],ESI
14818e487 MOV R9D,0x1
14818e48d LEA R8D,[R9 + 0x5]
14818e491 LEA RDX,[0x14cf62000]
14818e498 LEA RCX,[RSP + 0x50]
14818e49d CALL 0x140d101c0
14818e4a2 CMP EAX,-0x1
14818e4a5 JZ 0x14818e57f
14818e4ab LEA RDX,[0x14cf62010]
14818e4b2 LEA RCX,[RBP + -0x60]
14818e4b6 CALL 0x140cf7080
14818e4bb NOP
14818e4bc MOV RCX,qword ptr [RBX]
14818e4bf LEA RAX,[RBP + -0x60]
14818e4c3 CMP RAX,RCX
14818e4c6 JC 0x14818e52f
14818e4c8 MOVSXD RDX,dword ptr [RBX + 0xc]
14818e4cc MOV RAX,RDX
14818e4cf SHL RAX,0x4
14818e4d3 ADD RAX,RCX
14818e4d6 LEA R8,[RBP + -0x60]
14818e4da CMP R8,RAX
14818e4dd JNC 0x14818e52f
14818e4df MOVSXD RAX,dword ptr [RBX + 0x8]
14818e4e3 MOV R9,qword ptr [RBP + 0x378]
14818e4ea MOV qword ptr [RSP + 0x48],0x10
14818e4f3 MOV qword ptr [RSP + 0x40],RAX
14818e4f8 MOV qword ptr [RSP + 0x38],RDX
14818e4fd MOV qword ptr [RSP + 0x30],RCX
14818e502 LEA RAX,[RBP + -0x60]
14818e506 MOV qword ptr [RSP + 0x28],RAX
14818e50b MOV qword ptr [RSP + 0x20],R14
14818e510 MOV R8D,0x63e
14818e516 LEA RDX,[0x14cf27ac0]
14818e51d LEA RCX,[0x14bce6eb8]
14818e524 CALL 0x140f8dfd0
14818e529 TEST AL,AL
14818e52b JZ 0x14818e52f
14818e52d NOP
14818e52e INT3
14818e52f MOVSXD RDI,dword ptr [RBX + 0x8]
14818e533 LEA EAX,[RDI + 0x1]
14818e536 MOV dword ptr [RBX + 0x8],EAX
14818e539 CMP EAX,dword ptr [RBX + 0xc]
14818e53c JBE 0x14818e548
14818e53e MOV EDX,EDI
14818e540 MOV RCX,RBX
14818e543 CALL 0x140ca4b30
14818e548 MOV RCX,RDI
14818e54b SHL RCX,0x4
14818e54f ADD RCX,qword ptr [RBX]
14818e552 MOV qword ptr [RCX],RSI
14818e555 MOV RAX,qword ptr [RBP + -0x60]
14818e559 MOV qword ptr [RCX],RAX
14818e55c MOV qword ptr [RBP + -0x60],RSI
14818e560 MOV EAX,dword ptr [RBP + -0x58]
14818e563 MOV dword ptr [RCX + 0x8],EAX
14818e566 MOV EAX,dword ptr [RBP + -0x54]
14818e569 MOV dword ptr [RCX + 0xc],EAX
14818e56c MOV qword ptr [RBP + -0x58],RSI
14818e570 MOV RCX,qword ptr [RBP + -0x60]
14818e574 TEST RCX,RCX
14818e577 JZ 0x14818e57f
14818e579 CALL 0x140e282f0
14818e57e NOP
14818e57f MOV dword ptr [RSP + 0x28],0xffffffff
14818e587 MOV dword ptr [RSP + 0x20],ESI
14818e58b MOV R9D,0x1
14818e591 LEA R8D,[R9 + 0x6]
14818e595 LEA RDX,[0x14cf62018]
14818e59c LEA RCX,[RSP + 0x50]
14818e5a1 CALL 0x140d101c0
14818e5a6 CMP EAX,-0x1
14818e5a9 JZ 0x14818e683
14818e5af LEA RDX,[0x14cf62028]
14818e5b6 LEA RCX,[RBP]
14818e5ba CALL 0x140cf7080
14818e5bf NOP
14818e5c0 MOV RCX,qword ptr [RBX]
14818e5c3 LEA RAX,[RBP]
14818e5c7 CMP RAX,RCX
14818e5ca JC 0x14818e633
14818e5cc MOVSXD RDX,dword ptr [RBX + 0xc]
14818e5d0 MOV RAX,RDX
14818e5d3 SHL RAX,0x4
14818e5d7 ADD RAX,RCX
14818e5da LEA R8,[RBP]
14818e5de CMP R8,RAX
14818e5e1 JNC 0x14818e633
14818e5e3 MOVSXD RAX,dword ptr [RBX + 0x8]
14818e5e7 MOV R9,qword ptr [RBP + 0x378]
14818e5ee MOV qword ptr [RSP + 0x48],0x10
14818e5f7 MOV qword ptr [RSP + 0x40],RAX
14818e5fc MOV qword ptr [RSP + 0x38],RDX
14818e601 MOV qword ptr [RSP + 0x30],RCX
14818e606 LEA RAX,[RBP]
14818e60a MOV qword ptr [RSP + 0x28],RAX
14818e60f MOV qword ptr [RSP + 0x20],R14
14818e614 MOV R8D,0x63e
14818e61a LEA RDX,[0x14cf27ac0]
14818e621 LEA RCX,[0x14bce6eb8]
14818e628 CALL 0x140f8dfd0
14818e62d TEST AL,AL
14818e62f JZ 0x14818e633
14818e631 NOP
14818e632 INT3
14818e633 MOVSXD RDI,dword ptr [RBX + 0x8]
14818e637 LEA EAX,[RDI + 0x1]
14818e63a MOV dword ptr [RBX + 0x8],EAX
14818e63d CMP EAX,dword ptr [RBX + 0xc]
14818e640 JBE 0x14818e64c
14818e642 MOV EDX,EDI
14818e644 MOV RCX,RBX
14818e647 CALL 0x140ca4b30
14818e64c MOV RCX,RDI
14818e64f SHL RCX,0x4
14818e653 ADD RCX,qword ptr [RBX]
14818e656 MOV qword ptr [RCX],RSI
14818e659 MOV RAX,qword ptr [RBP]
14818e65d MOV qword ptr [RCX],RAX
14818e660 MOV qword ptr [RBP],RSI
14818e664 MOV EAX,dword ptr [RBP + 0x8]
14818e667 MOV dword ptr [RCX + 0x8],EAX
14818e66a MOV EAX,dword ptr [RBP + 0xc]
14818e66d MOV dword ptr [RCX + 0xc],EAX
14818e670 MOV qword ptr [RBP + 0x8],RSI
14818e674 MOV RCX,qword ptr [RBP]
14818e678 TEST RCX,RCX
14818e67b JZ 0x14818e683
14818e67d CALL 0x140e282f0
14818e682 NOP
14818e683 MOV dword ptr [RSP + 0x28],0xffffffff
14818e68b MOV dword ptr [RSP + 0x20],ESI
14818e68f MOV R9D,0x1
14818e695 LEA R8D,[R9 + 0x4]
14818e699 LEA RDX,[0x14cf62030]
14818e6a0 LEA RCX,[RSP + 0x50]
14818e6a5 CALL 0x140d101c0
14818e6aa CMP EAX,-0x1
14818e6ad JZ 0x14818e787
14818e6b3 LEA RDX,[0x14cf6203c]
14818e6ba LEA RCX,[RBP + 0x10]
14818e6be CALL 0x140cf7080
14818e6c3 NOP
14818e6c4 MOV RCX,qword ptr [RBX]
14818e6c7 LEA RAX,[RBP + 0x10]
14818e6cb CMP RAX,RCX
14818e6ce JC 0x14818e737
14818e6d0 MOVSXD RDX,dword ptr [RBX + 0xc]
14818e6d4 MOV RAX,RDX
14818e6d7 SHL RAX,0x4
14818e6db ADD RAX,RCX
14818e6de LEA R8,[RBP + 0x10]
14818e6e2 CMP R8,RAX
14818e6e5 JNC 0x14818e737
14818e6e7 MOVSXD RAX,dword ptr [RBX + 0x8]
14818e6eb MOV R9,qword ptr [RBP + 0x378]
14818e6f2 MOV qword ptr [RSP + 0x48],0x10
14818e6fb MOV qword ptr [RSP + 0x40],RAX
14818e700 MOV qword ptr [RSP + 0x38],RDX
14818e705 MOV qword ptr [RSP + 0x30],RCX
14818e70a LEA RAX,[RBP + 0x10]
14818e70e MOV qword ptr [RSP + 0x28],RAX
14818e713 MOV qword ptr [RSP + 0x20],R14
14818e718 MOV R8D,0x63e
14818e71e LEA RDX,[0x14cf27ac0]
14818e725 LEA RCX,[0x14bce6eb8]
14818e72c CALL 0x140f8dfd0
14818e731 TEST AL,AL
14818e733 JZ 0x14818e737
14818e735 NOP
14818e736 INT3
14818e737 MOVSXD RDI,dword ptr [RBX + 0x8]
14818e73b LEA EAX,[RDI + 0x1]
14818e73e MOV dword ptr [RBX + 0x8],EAX
14818e741 CMP EAX,dword ptr [RBX + 0xc]
14818e744 JBE 0x14818e750
14818e746 MOV EDX,EDI
14818e748 MOV RCX,RBX
14818e74b CALL 0x140ca4b30
14818e750 MOV RCX,RDI
14818e753 SHL RCX,0x4
14818e757 ADD RCX,qword ptr [RBX]
14818e75a MOV qword ptr [RCX],RSI
14818e75d MOV RAX,qword ptr [RBP + 0x10]
14818e761 MOV qword ptr [RCX],RAX
14818e764 MOV qword ptr [RBP + 0x10],RSI
14818e768 MOV EAX,dword ptr [RBP + 0x18]
14818e76b MOV dword ptr [RCX + 0x8],EAX
14818e76e MOV EAX,dword ptr [RBP + 0x1c]
14818e771 MOV dword ptr [RCX + 0xc],EAX
14818e774 MOV qword ptr [RBP + 0x18],RSI
14818e778 MOV RCX,qword ptr [RBP + 0x10]
14818e77c TEST RCX,RCX
14818e77f JZ 0x14818e787
14818e781 CALL 0x140e282f0
14818e786 NOP
14818e787 MOV dword ptr [RSP + 0x28],0xffffffff
14818e78f MOV dword ptr [RSP + 0x20],ESI
14818e793 MOV R9D,0x1
14818e799 LEA R8D,[R9 + 0x6]
14818e79d LEA RDX,[0x14cf62048]
14818e7a4 LEA RCX,[RSP + 0x50]
14818e7a9 CALL 0x140d101c0
14818e7ae CMP EAX,-0x1
14818e7b1 JZ 0x14818e88b
14818e7b7 LEA RDX,[0x14cf62058]
14818e7be LEA RCX,[RBP + 0x20]
14818e7c2 CALL 0x140cf7080
14818e7c7 NOP
14818e7c8 MOV RCX,qword ptr [RBX]
14818e7cb LEA RAX,[RBP + 0x20]
14818e7cf CMP RAX,RCX
14818e7d2 JC 0x14818e83b
14818e7d4 MOVSXD RDX,dword ptr [RBX + 0xc]
14818e7d8 MOV RAX,RDX
14818e7db SHL RAX,0x4
14818e7df ADD RAX,RCX
14818e7e2 LEA R8,[RBP + 0x20]
14818e7e6 CMP R8,RAX
14818e7e9 JNC 0x14818e83b
14818e7eb MOVSXD RAX,dword ptr [RBX + 0x8]
14818e7ef MOV R9,qword ptr [RBP + 0x378]
14818e7f6 MOV qword ptr [RSP + 0x48],0x10
14818e7ff MOV qword ptr [RSP + 0x40],RAX
14818e804 MOV qword ptr [RSP + 0x38],RDX
14818e809 MOV qword ptr [RSP + 0x30],RCX
14818e80e LEA RAX,[RBP + 0x20]
14818e812 MOV qword ptr [RSP + 0x28],RAX
14818e817 MOV qword ptr [RSP + 0x20],R14
14818e81c MOV R8D,0x63e
14818e822 LEA RDX,[0x14cf27ac0]
14818e829 LEA RCX,[0x14bce6eb8]
14818e830 CALL 0x140f8dfd0
14818e835 TEST AL,AL
14818e837 JZ 0x14818e83b
14818e839 NOP
14818e83a INT3
14818e83b MOVSXD RDI,dword ptr [RBX + 0x8]
14818e83f LEA EAX,[RDI + 0x1]
14818e842 MOV dword ptr [RBX + 0x8],EAX
14818e845 CMP EAX,dword ptr [RBX + 0xc]
14818e848 JBE 0x14818e854
14818e84a MOV EDX,EDI
14818e84c MOV RCX,RBX
14818e84f CALL 0x140ca4b30
14818e854 MOV RCX,RDI
14818e857 SHL RCX,0x4
14818e85b ADD RCX,qword ptr [RBX]
14818e85e MOV qword ptr [RCX],RSI
14818e861 MOV RAX,qword ptr [RBP + 0x20]
14818e865 MOV qword ptr [RCX],RAX
14818e868 MOV qword ptr [RBP + 0x20],RSI
14818e86c MOV EAX,dword ptr [RBP + 0x28]
14818e86f MOV dword ptr [RCX + 0x8],EAX
14818e872 MOV EAX,dword ptr [RBP + 0x2c]
14818e875 MOV dword ptr [RCX + 0xc],EAX
14818e878 MOV qword ptr [RBP + 0x28],RSI
14818e87c MOV RCX,qword ptr [RBP + 0x20]
14818e880 TEST RCX,RCX
14818e883 JZ 0x14818e88b
14818e885 CALL 0x140e282f0
14818e88a NOP
14818e88b MOV dword ptr [RSP + 0x28],0xffffffff
14818e893 MOV dword ptr [RSP + 0x20],ESI
14818e897 MOV R9D,0x1
14818e89d LEA R8D,[R9 + 0x7]
14818e8a1 LEA RDX,[0x14cf62060]
14818e8a8 LEA RCX,[RSP + 0x50]
14818e8ad CALL 0x140d101c0
14818e8b2 CMP EAX,-0x1
14818e8b5 JZ 0x14818e98f
14818e8bb LEA RDX,[0x14cf62078]
14818e8c2 LEA RCX,[RBP + 0x30]
14818e8c6 CALL 0x140cf7080
14818e8cb NOP
14818e8cc MOV RCX,qword ptr [RBX]
14818e8cf LEA RAX,[RBP + 0x30]
14818e8d3 CMP RAX,RCX
14818e8d6 JC 0x14818e93f
14818e8d8 MOVSXD RDX,dword ptr [RBX + 0xc]
14818e8dc MOV RAX,RDX
14818e8df SHL RAX,0x4
14818e8e3 ADD RAX,RCX
14818e8e6 LEA R8,[RBP + 0x30]
14818e8ea CMP R8,RAX
14818e8ed JNC 0x14818e93f
14818e8ef MOVSXD RAX,dword ptr [RBX + 0x8]
14818e8f3 MOV R9,qword ptr [RBP + 0x378]
14818e8fa MOV qword ptr [RSP + 0x48],0x10
14818e903 MOV qword ptr [RSP + 0x40],RAX
14818e908 MOV qword ptr [RSP + 0x38],RDX
14818e90d MOV qword ptr [RSP + 0x30],RCX
14818e912 LEA RAX,[RBP + 0x30]
14818e916 MOV qword ptr [RSP + 0x28],RAX
14818e91b MOV qword ptr [RSP + 0x20],R14
14818e920 MOV R8D,0x63e
14818e926 LEA RDX,[0x14cf27ac0]
14818e92d LEA RCX,[0x14bce6eb8]
14818e934 CALL 0x140f8dfd0
14818e939 TEST AL,AL
14818e93b JZ 0x14818e93f
14818e93d NOP
14818e93e INT3
14818e93f MOVSXD RDI,dword ptr [RBX + 0x8]
14818e943 LEA EAX,[RDI + 0x1]
14818e946 MOV dword ptr [RBX + 0x8],EAX
14818e949 CMP EAX,dword ptr [RBX + 0xc]
14818e94c JBE 0x14818e958
14818e94e MOV EDX,EDI
14818e950 MOV RCX,RBX
14818e953 CALL 0x140ca4b30
14818e958 MOV RCX,RDI
14818e95b SHL RCX,0x4
14818e95f ADD RCX,qword ptr [RBX]
14818e962 MOV qword ptr [RCX],RSI
14818e965 MOV RAX,qword ptr [RBP + 0x30]
14818e969 MOV qword ptr [RCX],RAX
14818e96c MOV qword ptr [RBP + 0x30],RSI
14818e970 MOV EAX,dword ptr [RBP + 0x38]
14818e973 MOV dword ptr [RCX + 0x8],EAX
14818e976 MOV EAX,dword ptr [RBP + 0x3c]
14818e979 MOV dword ptr [RCX + 0xc],EAX
14818e97c MOV qword ptr [RBP + 0x38],RSI
14818e980 MOV RCX,qword ptr [RBP + 0x30]
14818e984 TEST RCX,RCX
14818e987 JZ 0x14818e98f
14818e989 CALL 0x140e282f0
14818e98e NOP
14818e98f MOV dword ptr [RSP + 0x28],0xffffffff
14818e997 MOV dword ptr [RSP + 0x20],ESI
14818e99b MOV R9D,0x1
14818e9a1 LEA R8D,[R9 + 0x6]
14818e9a5 LEA RDX,[0x14cf62088]
14818e9ac LEA RCX,[RSP + 0x50]
14818e9b1 CALL 0x140d101c0
14818e9b6 CMP EAX,-0x1
14818e9b9 JZ 0x14818ea93
14818e9bf LEA RDX,[0x14cf62098]
14818e9c6 LEA RCX,[RBP + 0x40]
14818e9ca CALL 0x140cf7080
14818e9cf NOP
14818e9d0 MOV RCX,qword ptr [RBX]
14818e9d3 LEA RAX,[RBP + 0x40]
14818e9d7 CMP RAX,RCX
14818e9da JC 0x14818ea43
14818e9dc MOVSXD RDX,dword ptr [RBX + 0xc]
14818e9e0 MOV RAX,RDX
14818e9e3 SHL RAX,0x4
14818e9e7 ADD RAX,RCX
14818e9ea LEA R8,[RBP + 0x40]
14818e9ee CMP R8,RAX
14818e9f1 JNC 0x14818ea43
14818e9f3 MOVSXD RAX,dword ptr [RBX + 0x8]
14818e9f7 MOV R9,qword ptr [RBP + 0x378]
14818e9fe MOV qword ptr [RSP + 0x48],0x10
14818ea07 MOV qword ptr [RSP + 0x40],RAX
14818ea0c MOV qword ptr [RSP + 0x38],RDX
14818ea11 MOV qword ptr [RSP + 0x30],RCX
14818ea16 LEA RAX,[RBP + 0x40]
14818ea1a MOV qword ptr [RSP + 0x28],RAX
14818ea1f MOV qword ptr [RSP + 0x20],R14
14818ea24 MOV R8D,0x63e
14818ea2a LEA RDX,[0x14cf27ac0]
14818ea31 LEA RCX,[0x14bce6eb8]
14818ea38 CALL 0x140f8dfd0
14818ea3d TEST AL,AL
14818ea3f JZ 0x14818ea43
14818ea41 NOP
14818ea42 INT3
14818ea43 MOVSXD RDI,dword ptr [RBX + 0x8]
14818ea47 LEA EAX,[RDI + 0x1]
14818ea4a MOV dword ptr [RBX + 0x8],EAX
14818ea4d CMP EAX,dword ptr [RBX + 0xc]
14818ea50 JBE 0x14818ea5c
14818ea52 MOV EDX,EDI
14818ea54 MOV RCX,RBX
14818ea57 CALL 0x140ca4b30
14818ea5c MOV RCX,RDI
14818ea5f SHL RCX,0x4
14818ea63 ADD RCX,qword ptr [RBX]
14818ea66 MOV qword ptr [RCX],RSI
14818ea69 MOV RAX,qword ptr [RBP + 0x40]
14818ea6d MOV qword ptr [RCX],RAX
14818ea70 MOV qword ptr [RBP + 0x40],RSI
14818ea74 MOV EAX,dword ptr [RBP + 0x48]
14818ea77 MOV dword ptr [RCX + 0x8],EAX
14818ea7a MOV EAX,dword ptr [RBP + 0x4c]
14818ea7d MOV dword ptr [RCX + 0xc],EAX
14818ea80 MOV qword ptr [RBP + 0x48],RSI
14818ea84 MOV RCX,qword ptr [RBP + 0x40]
14818ea88 TEST RCX,RCX
14818ea8b JZ 0x14818ea93
14818ea8d CALL 0x140e282f0
14818ea92 NOP
14818ea93 MOV dword ptr [RSP + 0x28],0xffffffff
14818ea9b MOV dword ptr [RSP + 0x20],ESI
14818ea9f MOV R9D,0x1
14818eaa5 LEA R8D,[R9 + 0x2]
14818eaa9 LEA RDX,[0x14cf620a0]
14818eab0 LEA RCX,[RSP + 0x50]
14818eab5 CALL 0x140d101c0
14818eaba CMP EAX,-0x1
14818eabd JZ 0x14818eb97
14818eac3 LEA RDX,[0x14cf620a8]
14818eaca LEA RCX,[RBP + 0x50]
14818eace CALL 0x140cf7080
14818ead3 NOP
14818ead4 MOV RCX,qword ptr [RBX]
14818ead7 LEA RAX,[RBP + 0x50]
14818eadb CMP RAX,RCX
14818eade JC 0x14818eb47
14818eae0 MOVSXD RDX,dword ptr [RBX + 0xc]
14818eae4 MOV RAX,RDX
14818eae7 SHL RAX,0x4
14818eaeb ADD RAX,RCX
14818eaee LEA R8,[RBP + 0x50]
14818eaf2 CMP R8,RAX
14818eaf5 JNC 0x14818eb47
14818eaf7 MOVSXD RAX,dword ptr [RBX + 0x8]
14818eafb MOV R9,qword ptr [RBP + 0x378]
14818eb02 MOV qword ptr [RSP + 0x48],0x10
14818eb0b MOV qword ptr [RSP + 0x40],RAX
14818eb10 MOV qword ptr [RSP + 0x38],RDX
14818eb15 MOV qword ptr [RSP + 0x30],RCX
14818eb1a LEA RAX,[RBP + 0x50]
14818eb1e MOV qword ptr [RSP + 0x28],RAX
14818eb23 MOV qword ptr [RSP + 0x20],R14
14818eb28 MOV R8D,0x63e
14818eb2e LEA RDX,[0x14cf27ac0]
14818eb35 LEA RCX,[0x14bce6eb8]
14818eb3c CALL 0x140f8dfd0
14818eb41 TEST AL,AL
14818eb43 JZ 0x14818eb47
14818eb45 NOP
14818eb46 INT3
14818eb47 MOVSXD RDI,dword ptr [RBX + 0x8]
14818eb4b LEA EAX,[RDI + 0x1]
14818eb4e MOV dword ptr [RBX + 0x8],EAX
14818eb51 CMP EAX,dword ptr [RBX + 0xc]
14818eb54 JBE 0x14818eb60
14818eb56 MOV EDX,EDI
14818eb58 MOV RCX,RBX
14818eb5b CALL 0x140ca4b30
14818eb60 MOV RCX,RDI
14818eb63 SHL RCX,0x4
14818eb67 ADD RCX,qword ptr [RBX]
14818eb6a MOV qword ptr [RCX],RSI
14818eb6d MOV RAX,qword ptr [RBP + 0x50]
14818eb71 MOV qword ptr [RCX],RAX
14818eb74 MOV qword ptr [RBP + 0x50],RSI
14818eb78 MOV EAX,dword ptr [RBP + 0x58]
14818eb7b MOV dword ptr [RCX + 0x8],EAX
14818eb7e MOV EAX,dword ptr [RBP + 0x5c]
14818eb81 MOV dword ptr [RCX + 0xc],EAX
14818eb84 MOV qword ptr [RBP + 0x58],RSI
14818eb88 MOV RCX,qword ptr [RBP + 0x50]
14818eb8c TEST RCX,RCX
14818eb8f JZ 0x14818eb97
14818eb91 CALL 0x140e282f0
14818eb96 NOP
14818eb97 MOV dword ptr [RSP + 0x28],0xffffffff
14818eb9f MOV dword ptr [RSP + 0x20],ESI
14818eba3 MOV R9D,0x1
14818eba9 LEA R8D,[R9 + 0xa]
14818ebad LEA RDX,[0x14cf620b0]
14818ebb4 LEA RCX,[RSP + 0x50]
14818ebb9 CALL 0x140d101c0
14818ebbe CMP EAX,-0x1
14818ebc1 JZ 0x14818ec9b
14818ebc7 LEA RDX,[0x14cf620c8]
14818ebce LEA RCX,[RBP + 0x60]
14818ebd2 CALL 0x140cf7080
14818ebd7 NOP
14818ebd8 MOV RCX,qword ptr [RBX]
14818ebdb LEA RAX,[RBP + 0x60]
14818ebdf CMP RAX,RCX
14818ebe2 JC 0x14818ec4b
14818ebe4 MOVSXD RDX,dword ptr [RBX + 0xc]
14818ebe8 MOV RAX,RDX
14818ebeb SHL RAX,0x4
14818ebef ADD RAX,RCX
14818ebf2 LEA R8,[RBP + 0x60]
14818ebf6 CMP R8,RAX
14818ebf9 JNC 0x14818ec4b
14818ebfb MOVSXD RAX,dword ptr [RBX + 0x8]
14818ebff MOV R9,qword ptr [RBP + 0x378]
14818ec06 MOV qword ptr [RSP + 0x48],0x10
14818ec0f MOV qword ptr [RSP + 0x40],RAX
14818ec14 MOV qword ptr [RSP + 0x38],RDX
14818ec19 MOV qword ptr [RSP + 0x30],RCX
14818ec1e LEA RAX,[RBP + 0x60]
14818ec22 MOV qword ptr [RSP + 0x28],RAX
14818ec27 MOV qword ptr [RSP + 0x20],R14
14818ec2c MOV R8D,0x63e
14818ec32 LEA RDX,[0x14cf27ac0]
14818ec39 LEA RCX,[0x14bce6eb8]
14818ec40 CALL 0x140f8dfd0
14818ec45 TEST AL,AL
14818ec47 JZ 0x14818ec4b
14818ec49 NOP
14818ec4a INT3
14818ec4b MOVSXD RDI,dword ptr [RBX + 0x8]
14818ec4f LEA EAX,[RDI + 0x1]
14818ec52 MOV dword ptr [RBX + 0x8],EAX
14818ec55 CMP EAX,dword ptr [RBX + 0xc]
14818ec58 JBE 0x14818ec64
14818ec5a MOV EDX,EDI
14818ec5c MOV RCX,RBX
14818ec5f CALL 0x140ca4b30
14818ec64 MOV RCX,RDI
14818ec67 SHL RCX,0x4
14818ec6b ADD RCX,qword ptr [RBX]
14818ec6e MOV qword ptr [RCX],RSI
14818ec71 MOV RAX,qword ptr [RBP + 0x60]
14818ec75 MOV qword ptr [RCX],RAX
14818ec78 MOV qword ptr [RBP + 0x60],RSI
14818ec7c MOV EAX,dword ptr [RBP + 0x68]
14818ec7f MOV dword ptr [RCX + 0x8],EAX
14818ec82 MOV EAX,dword ptr [RBP + 0x6c]
14818ec85 MOV dword ptr [RCX + 0xc],EAX
14818ec88 MOV qword ptr [RBP + 0x68],RSI
14818ec8c MOV RCX,qword ptr [RBP + 0x60]
14818ec90 TEST RCX,RCX
14818ec93 JZ 0x14818ec9b
14818ec95 CALL 0x140e282f0
14818ec9a NOP
14818ec9b MOV dword ptr [RSP + 0x28],0xffffffff
14818eca3 MOV dword ptr [RSP + 0x20],ESI
14818eca7 MOV R9D,0x1
14818ecad LEA R8D,[R9 + 0x9]
14818ecb1 LEA RDX,[0x14cf620d8]
14818ecb8 LEA RCX,[RSP + 0x50]
14818ecbd CALL 0x140d101c0
14818ecc2 CMP EAX,-0x1
14818ecc5 JZ 0x14818ed9f
14818eccb LEA RDX,[0x14cf620f0]
14818ecd2 LEA RCX,[RBP + 0x70]
14818ecd6 CALL 0x140cf7080
14818ecdb NOP
14818ecdc MOV RCX,qword ptr [RBX]
14818ecdf LEA RAX,[RBP + 0x70]
14818ece3 CMP RAX,RCX
14818ece6 JC 0x14818ed4f
14818ece8 MOVSXD RDX,dword ptr [RBX + 0xc]
14818ecec MOV RAX,RDX
14818ecef SHL RAX,0x4
14818ecf3 ADD RAX,RCX
14818ecf6 LEA R8,[RBP + 0x70]
14818ecfa CMP R8,RAX
14818ecfd JNC 0x14818ed4f
14818ecff MOVSXD RAX,dword ptr [RBX + 0x8]
14818ed03 MOV R9,qword ptr [RBP + 0x378]
14818ed0a MOV qword ptr [RSP + 0x48],0x10
14818ed13 MOV qword ptr [RSP + 0x40],RAX
14818ed18 MOV qword ptr [RSP + 0x38],RDX
14818ed1d MOV qword ptr [RSP + 0x30],RCX
14818ed22 LEA RAX,[RBP + 0x70]
14818ed26 MOV qword ptr [RSP + 0x28],RAX
14818ed2b MOV qword ptr [RSP + 0x20],R14
14818ed30 MOV R8D,0x63e
14818ed36 LEA RDX,[0x14cf27ac0]
14818ed3d LEA RCX,[0x14bce6eb8]
14818ed44 CALL 0x140f8dfd0
14818ed49 TEST AL,AL
14818ed4b JZ 0x14818ed4f
14818ed4d NOP
14818ed4e INT3
14818ed4f MOVSXD RDI,dword ptr [RBX + 0x8]
14818ed53 LEA EAX,[RDI + 0x1]
14818ed56 MOV dword ptr [RBX + 0x8],EAX
14818ed59 CMP EAX,dword ptr [RBX + 0xc]
14818ed5c JBE 0x14818ed68
14818ed5e MOV EDX,EDI
14818ed60 MOV RCX,RBX
14818ed63 CALL 0x140ca4b30
14818ed68 MOV RCX,RDI
14818ed6b SHL RCX,0x4
14818ed6f ADD RCX,qword ptr [RBX]
14818ed72 MOV qword ptr [RCX],RSI
14818ed75 MOV RAX,qword ptr [RBP + 0x70]
14818ed79 MOV qword ptr [RCX],RAX
14818ed7c MOV qword ptr [RBP + 0x70],RSI
14818ed80 MOV EAX,dword ptr [RBP + 0x78]
14818ed83 MOV dword ptr [RCX + 0x8],EAX
14818ed86 MOV EAX,dword ptr [RBP + 0x7c]
14818ed89 MOV dword ptr [RCX + 0xc],EAX
14818ed8c MOV qword ptr [RBP + 0x78],RSI
14818ed90 MOV RCX,qword ptr [RBP + 0x70]
14818ed94 TEST RCX,RCX
14818ed97 JZ 0x14818ed9f
14818ed99 CALL 0x140e282f0
14818ed9e NOP
14818ed9f MOV dword ptr [RSP + 0x28],0xffffffff
14818eda7 MOV dword ptr [RSP + 0x20],ESI
14818edab MOV R9D,0x1
14818edb1 LEA R8D,[R9 + 0xa]
14818edb5 LEA RDX,[0x14cf62100]
14818edbc LEA RCX,[RSP + 0x50]
14818edc1 CALL 0x140d101c0
14818edc6 CMP EAX,-0x1
14818edc9 JZ 0x14818eec1
14818edcf LEA RDX,[0x14cf62118]
14818edd6 LEA RCX,[RBP + 0x80]
14818eddd CALL 0x140cf7080
14818ede2 NOP
14818ede3 MOV RCX,qword ptr [RBX]
14818ede6 LEA RAX,[RBP + 0x80]
14818eded CMP RAX,RCX
14818edf0 JC 0x14818ee5f
14818edf2 MOVSXD RDX,dword ptr [RBX + 0xc]
14818edf6 MOV RAX,RDX
14818edf9 SHL RAX,0x4
14818edfd ADD RAX,RCX
14818ee00 LEA R8,[RBP + 0x80]
14818ee07 CMP R8,RAX
14818ee0a JNC 0x14818ee5f
14818ee0c MOVSXD RAX,dword ptr [RBX + 0x8]
14818ee10 MOV R9,qword ptr [RBP + 0x378]
14818ee17 MOV qword ptr [RSP + 0x48],0x10
14818ee20 MOV qword ptr [RSP + 0x40],RAX
14818ee25 MOV qword ptr [RSP + 0x38],RDX
14818ee2a MOV qword ptr [RSP + 0x30],RCX
14818ee2f LEA RAX,[RBP + 0x80]
14818ee36 MOV qword ptr [RSP + 0x28],RAX
14818ee3b MOV qword ptr [RSP + 0x20],R14
14818ee40 MOV R8D,0x63e
14818ee46 LEA RDX,[0x14cf27ac0]
14818ee4d LEA RCX,[0x14bce6eb8]
14818ee54 CALL 0x140f8dfd0
14818ee59 TEST AL,AL
14818ee5b JZ 0x14818ee5f
14818ee5d NOP
14818ee5e INT3
14818ee5f MOVSXD RDI,dword ptr [RBX + 0x8]
14818ee63 LEA EAX,[RDI + 0x1]
14818ee66 MOV dword ptr [RBX + 0x8],EAX
14818ee69 CMP EAX,dword ptr [RBX + 0xc]
14818ee6c JBE 0x14818ee78
14818ee6e MOV EDX,EDI
14818ee70 MOV RCX,RBX
14818ee73 CALL 0x140ca4b30
14818ee78 MOV RCX,RDI
14818ee7b SHL RCX,0x4
14818ee7f ADD RCX,qword ptr [RBX]
14818ee82 MOV qword ptr [RCX],RSI
14818ee85 MOV RAX,qword ptr [RBP + 0x80]
14818ee8c MOV qword ptr [RCX],RAX
14818ee8f MOV qword ptr [RBP + 0x80],RSI
14818ee96 MOV EAX,dword ptr [RBP + 0x88]
14818ee9c MOV dword ptr [RCX + 0x8],EAX
14818ee9f MOV EAX,dword ptr [RBP + 0x8c]
14818eea5 MOV dword ptr [RCX + 0xc],EAX
14818eea8 MOV qword ptr [RBP + 0x88],RSI
14818eeaf MOV RCX,qword ptr [RBP + 0x80]
14818eeb6 TEST RCX,RCX
14818eeb9 JZ 0x14818eec1
14818eebb CALL 0x140e282f0
14818eec0 NOP
14818eec1 MOV dword ptr [RSP + 0x28],0xffffffff
14818eec9 MOV dword ptr [RSP + 0x20],ESI
14818eecd MOV R9D,0x1
14818eed3 LEA R8D,[R9 + 0x3]
14818eed7 LEA RDX,[0x14cf62128]
14818eede LEA RCX,[RSP + 0x50]
14818eee3 CALL 0x140d101c0
14818eee8 CMP EAX,-0x1
14818eeeb JZ 0x14818efe3
14818eef1 LEA RDX,[0x14cf62134]
14818eef8 LEA RCX,[RBP + 0x90]
14818eeff CALL 0x140cf7080
14818ef04 NOP
14818ef05 MOV RCX,qword ptr [RBX]
14818ef08 LEA RAX,[RBP + 0x90]
14818ef0f CMP RAX,RCX
14818ef12 JC 0x14818ef81
14818ef14 MOVSXD RDX,dword ptr [RBX + 0xc]
14818ef18 MOV RAX,RDX
14818ef1b SHL RAX,0x4
14818ef1f ADD RAX,RCX
14818ef22 LEA R8,[RBP + 0x90]
14818ef29 CMP R8,RAX
14818ef2c JNC 0x14818ef81
14818ef2e MOVSXD RAX,dword ptr [RBX + 0x8]
14818ef32 MOV R9,qword ptr [RBP + 0x378]
14818ef39 MOV qword ptr [RSP + 0x48],0x10
14818ef42 MOV qword ptr [RSP + 0x40],RAX
14818ef47 MOV qword ptr [RSP + 0x38],RDX
14818ef4c MOV qword ptr [RSP + 0x30],RCX
14818ef51 LEA RAX,[RBP + 0x90]
14818ef58 MOV qword ptr [RSP + 0x28],RAX
14818ef5d MOV qword ptr [RSP + 0x20],R14
14818ef62 MOV R8D,0x63e
14818ef68 LEA RDX,[0x14cf27ac0]
14818ef6f LEA RCX,[0x14bce6eb8]
14818ef76 CALL 0x140f8dfd0
14818ef7b TEST AL,AL
14818ef7d JZ 0x14818ef81
14818ef7f NOP
14818ef80 INT3
14818ef81 MOVSXD RDI,dword ptr [RBX + 0x8]
14818ef85 LEA EAX,[RDI + 0x1]
14818ef88 MOV dword ptr [RBX + 0x8],EAX
14818ef8b CMP EAX,dword ptr [RBX + 0xc]
14818ef8e JBE 0x14818ef9a
14818ef90 MOV EDX,EDI
14818ef92 MOV RCX,RBX
14818ef95 CALL 0x140ca4b30
14818ef9a MOV RCX,RDI
14818ef9d SHL RCX,0x4
14818efa1 ADD RCX,qword ptr [RBX]
14818efa4 MOV qword ptr [RCX],RSI
14818efa7 MOV RAX,qword ptr [RBP + 0x90]
14818efae MOV qword ptr [RCX],RAX
14818efb1 MOV qword ptr [RBP + 0x90],RSI
14818efb8 MOV EAX,dword ptr [RBP + 0x98]
14818efbe MOV dword ptr [RCX + 0x8],EAX
14818efc1 MOV EAX,dword ptr [RBP + 0x9c]
14818efc7 MOV dword ptr [RCX + 0xc],EAX
14818efca MOV qword ptr [RBP + 0x98],RSI
14818efd1 MOV RCX,qword ptr [RBP + 0x90]
14818efd8 TEST RCX,RCX
14818efdb JZ 0x14818efe3
14818efdd CALL 0x140e282f0
14818efe2 NOP
14818efe3 MOV dword ptr [RSP + 0x28],0xffffffff
14818efeb MOV dword ptr [RSP + 0x20],ESI
14818efef MOV R9D,0x1
14818eff5 LEA R8D,[R9 + 0x8]
14818eff9 LEA RDX,[0x14cf62140]
14818f000 LEA RCX,[RSP + 0x50]
14818f005 CALL 0x140d101c0
14818f00a CMP EAX,-0x1
14818f00d JZ 0x14818f105
14818f013 LEA RDX,[0x14cf62158]
14818f01a LEA RCX,[RBP + 0xa0]
14818f021 CALL 0x140cf7080
14818f026 NOP
14818f027 MOV RCX,qword ptr [RBX]
14818f02a LEA RAX,[RBP + 0xa0]
14818f031 CMP RAX,RCX
14818f034 JC 0x14818f0a3
14818f036 MOVSXD RDX,dword ptr [RBX + 0xc]
14818f03a MOV RAX,RDX
14818f03d SHL RAX,0x4
14818f041 ADD RAX,RCX
14818f044 LEA R8,[RBP + 0xa0]
14818f04b CMP R8,RAX
14818f04e JNC 0x14818f0a3
14818f050 MOVSXD RAX,dword ptr [RBX + 0x8]
14818f054 MOV R9,qword ptr [RBP + 0x378]
14818f05b MOV qword ptr [RSP + 0x48],0x10
14818f064 MOV qword ptr [RSP + 0x40],RAX
14818f069 MOV qword ptr [RSP + 0x38],RDX
14818f06e MOV qword ptr [RSP + 0x30],RCX
14818f073 LEA RAX,[RBP + 0xa0]
14818f07a MOV qword ptr [RSP + 0x28],RAX
14818f07f MOV qword ptr [RSP + 0x20],R14
14818f084 MOV R8D,0x63e
14818f08a LEA RDX,[0x14cf27ac0]
14818f091 LEA RCX,[0x14bce6eb8]
14818f098 CALL 0x140f8dfd0
14818f09d TEST AL,AL
14818f09f JZ 0x14818f0a3
14818f0a1 NOP
14818f0a2 INT3
14818f0a3 MOVSXD RDI,dword ptr [RBX + 0x8]
14818f0a7 LEA EAX,[RDI + 0x1]
14818f0aa MOV dword ptr [RBX + 0x8],EAX
14818f0ad CMP EAX,dword ptr [RBX + 0xc]
14818f0b0 JBE 0x14818f0bc
14818f0b2 MOV EDX,EDI
14818f0b4 MOV RCX,RBX
14818f0b7 CALL 0x140ca4b30
14818f0bc MOV RCX,RDI
14818f0bf SHL RCX,0x4
14818f0c3 ADD RCX,qword ptr [RBX]
14818f0c6 MOV qword ptr [RCX],RSI
14818f0c9 MOV RAX,qword ptr [RBP + 0xa0]
14818f0d0 MOV qword ptr [RCX],RAX
14818f0d3 MOV qword ptr [RBP + 0xa0],RSI
14818f0da MOV EAX,dword ptr [RBP + 0xa8]
14818f0e0 MOV dword ptr [RCX + 0x8],EAX
14818f0e3 MOV EAX,dword ptr [RBP + 0xac]
14818f0e9 MOV dword ptr [RCX + 0xc],EAX
14818f0ec MOV qword ptr [RBP + 0xa8],RSI
14818f0f3 MOV RCX,qword ptr [RBP + 0xa0]
14818f0fa TEST RCX,RCX
14818f0fd JZ 0x14818f105
14818f0ff CALL 0x140e282f0
14818f104 NOP
14818f105 MOV dword ptr [RSP + 0x28],0xffffffff
14818f10d MOV dword ptr [RSP + 0x20],ESI
14818f111 MOV R9D,0x1
14818f117 LEA R8D,[R9 + 0x6]
14818f11b LEA RDX,[0x14cf62168]
14818f122 LEA RCX,[RSP + 0x50]
14818f127 CALL 0x140d101c0
14818f12c CMP EAX,-0x1
14818f12f JZ 0x14818f227
14818f135 LEA RDX,[0x14cf62178]
14818f13c LEA RCX,[RBP + 0xb0]
14818f143 CALL 0x140cf7080
14818f148 NOP
14818f149 MOV RCX,qword ptr [RBX]
14818f14c LEA RAX,[RBP + 0xb0]
14818f153 CMP RAX,RCX
14818f156 JC 0x14818f1c5
14818f158 MOVSXD RDX,dword ptr [RBX + 0xc]
14818f15c MOV RAX,RDX
14818f15f SHL RAX,0x4
14818f163 ADD RAX,RCX
14818f166 LEA R8,[RBP + 0xb0]
14818f16d CMP R8,RAX
14818f170 JNC 0x14818f1c5
14818f172 MOVSXD RAX,dword ptr [RBX + 0x8]
14818f176 MOV R9,qword ptr [RBP + 0x378]
14818f17d MOV qword ptr [RSP + 0x48],0x10
14818f186 MOV qword ptr [RSP + 0x40],RAX
14818f18b MOV qword ptr [RSP + 0x38],RDX
14818f190 MOV qword ptr [RSP + 0x30],RCX
14818f195 LEA RAX,[RBP + 0xb0]
14818f19c MOV qword ptr [RSP + 0x28],RAX
14818f1a1 MOV qword ptr [RSP + 0x20],R14
14818f1a6 MOV R8D,0x63e
14818f1ac LEA RDX,[0x14cf27ac0]
14818f1b3 LEA RCX,[0x14bce6eb8]
14818f1ba CALL 0x140f8dfd0
14818f1bf TEST AL,AL
14818f1c1 JZ 0x14818f1c5
14818f1c3 NOP
14818f1c4 INT3
14818f1c5 MOVSXD RDI,dword ptr [RBX + 0x8]
14818f1c9 LEA EAX,[RDI + 0x1]
14818f1cc MOV dword ptr [RBX + 0x8],EAX
14818f1cf CMP EAX,dword ptr [RBX + 0xc]
14818f1d2 JBE 0x14818f1de
14818f1d4 MOV EDX,EDI
14818f1d6 MOV RCX,RBX
14818f1d9 CALL 0x140ca4b30
14818f1de MOV RCX,RDI
14818f1e1 SHL RCX,0x4
14818f1e5 ADD RCX,qword ptr [RBX]
14818f1e8 MOV qword ptr [RCX],RSI
14818f1eb MOV RAX,qword ptr [RBP + 0xb0]
14818f1f2 MOV qword ptr [RCX],RAX
14818f1f5 MOV qword ptr [RBP + 0xb0],RSI
14818f1fc MOV EAX,dword ptr [RBP + 0xb8]
14818f202 MOV dword ptr [RCX + 0x8],EAX
14818f205 MOV EAX,dword ptr [RBP + 0xbc]
14818f20b MOV dword ptr [RCX + 0xc],EAX
14818f20e MOV qword ptr [RBP + 0xb8],RSI
14818f215 MOV RCX,qword ptr [RBP + 0xb0]
14818f21c TEST RCX,RCX
14818f21f JZ 0x14818f227
14818f221 CALL 0x140e282f0
14818f226 NOP
14818f227 MOV dword ptr [RSP + 0x28],0xffffffff
14818f22f MOV dword ptr [RSP + 0x20],ESI
14818f233 MOV R9D,0x1
14818f239 LEA R8D,[R9 + 0x3]
14818f23d LEA RDX,[0x14cf62180]
14818f244 LEA RCX,[RSP + 0x50]
14818f249 CALL 0x140d101c0
14818f24e CMP EAX,-0x1
14818f251 JZ 0x14818f349
14818f257 LEA RDX,[0x14cf6218c]
14818f25e LEA RCX,[RBP + 0xc0]
14818f265 CALL 0x140cf7080
14818f26a NOP
14818f26b MOV RCX,qword ptr [RBX]
14818f26e LEA RAX,[RBP + 0xc0]
14818f275 CMP RAX,RCX
14818f278 JC 0x14818f2e7
14818f27a MOVSXD RDX,dword ptr [RBX + 0xc]
14818f27e MOV RAX,RDX
14818f281 SHL RAX,0x4
14818f285 ADD RAX,RCX
14818f288 LEA R8,[RBP + 0xc0]
14818f28f CMP R8,RAX
14818f292 JNC 0x14818f2e7
14818f294 MOVSXD RAX,dword ptr [RBX + 0x8]
14818f298 MOV R9,qword ptr [RBP + 0x378]
14818f29f MOV qword ptr [RSP + 0x48],0x10
14818f2a8 MOV qword ptr [RSP + 0x40],RAX
14818f2ad MOV qword ptr [RSP + 0x38],RDX
14818f2b2 MOV qword ptr [RSP + 0x30],RCX
14818f2b7 LEA RAX,[RBP + 0xc0]
14818f2be MOV qword ptr [RSP + 0x28],RAX
14818f2c3 MOV qword ptr [RSP + 0x20],R14
14818f2c8 MOV R8D,0x63e
14818f2ce LEA RDX,[0x14cf27ac0]
14818f2d5 LEA RCX,[0x14bce6eb8]
14818f2dc CALL 0x140f8dfd0
14818f2e1 TEST AL,AL
14818f2e3 JZ 0x14818f2e7
14818f2e5 NOP
14818f2e6 INT3
14818f2e7 MOVSXD RDI,dword ptr [RBX + 0x8]
14818f2eb LEA EAX,[RDI + 0x1]
14818f2ee MOV dword ptr [RBX + 0x8],EAX
14818f2f1 CMP EAX,dword ptr [RBX + 0xc]
14818f2f4 JBE 0x14818f300
14818f2f6 MOV EDX,EDI
14818f2f8 MOV RCX,RBX
14818f2fb CALL 0x140ca4b30
14818f300 MOV RCX,RDI
14818f303 SHL RCX,0x4
14818f307 ADD RCX,qword ptr [RBX]
14818f30a MOV qword ptr [RCX],RSI
14818f30d MOV RAX,qword ptr [RBP + 0xc0]
14818f314 MOV qword ptr [RCX],RAX
14818f317 MOV qword ptr [RBP + 0xc0],RSI
14818f31e MOV EAX,dword ptr [RBP + 0xc8]
14818f324 MOV dword ptr [RCX + 0x8],EAX
14818f327 MOV EAX,dword ptr [RBP + 0xcc]
14818f32d MOV dword ptr [RCX + 0xc],EAX
14818f330 MOV qword ptr [RBP + 0xc8],RSI
14818f337 MOV RCX,qword ptr [RBP + 0xc0]
14818f33e TEST RCX,RCX
14818f341 JZ 0x14818f349
14818f343 CALL 0x140e282f0
14818f348 NOP
14818f349 MOV dword ptr [RSP + 0x28],0xffffffff
14818f351 MOV dword ptr [RSP + 0x20],ESI
14818f355 MOV R9D,0x1
14818f35b LEA R8D,[R9 + 0x2]
14818f35f LEA RDX,[0x14cf62198]
14818f366 LEA RCX,[RSP + 0x50]
14818f36b CALL 0x140d101c0
14818f370 CMP EAX,-0x1
14818f373 JZ 0x14818f46b
14818f379 LEA RDX,[0x14cf621a0]
14818f380 LEA RCX,[RBP + 0xd0]
14818f387 CALL 0x140cf7080
14818f38c NOP
14818f38d MOV RCX,qword ptr [RBX]
14818f390 LEA RAX,[RBP + 0xd0]
14818f397 CMP RAX,RCX
14818f39a JC 0x14818f409
14818f39c MOVSXD RDX,dword ptr [RBX + 0xc]
14818f3a0 MOV RAX,RDX
14818f3a3 SHL RAX,0x4
14818f3a7 ADD RAX,RCX
14818f3aa LEA R8,[RBP + 0xd0]
14818f3b1 CMP R8,RAX
14818f3b4 JNC 0x14818f409
14818f3b6 MOVSXD RAX,dword ptr [RBX + 0x8]
14818f3ba MOV R9,qword ptr [RBP + 0x378]
14818f3c1 MOV qword ptr [RSP + 0x48],0x10
14818f3ca MOV qword ptr [RSP + 0x40],RAX
14818f3cf MOV qword ptr [RSP + 0x38],RDX
14818f3d4 MOV qword ptr [RSP + 0x30],RCX
14818f3d9 LEA RAX,[RBP + 0xd0]
14818f3e0 MOV qword ptr [RSP + 0x28],RAX
14818f3e5 MOV qword ptr [RSP + 0x20],R14
14818f3ea MOV R8D,0x63e
14818f3f0 LEA RDX,[0x14cf27ac0]
14818f3f7 LEA RCX,[0x14bce6eb8]
14818f3fe CALL 0x140f8dfd0
14818f403 TEST AL,AL
14818f405 JZ 0x14818f409
14818f407 NOP
14818f408 INT3
14818f409 MOVSXD RDI,dword ptr [RBX + 0x8]
14818f40d LEA EAX,[RDI + 0x1]
14818f410 MOV dword ptr [RBX + 0x8],EAX
14818f413 CMP EAX,dword ptr [RBX + 0xc]
14818f416 JBE 0x14818f422
14818f418 MOV EDX,EDI
14818f41a MOV RCX,RBX
14818f41d CALL 0x140ca4b30
14818f422 MOV RCX,RDI
14818f425 SHL RCX,0x4
14818f429 ADD RCX,qword ptr [RBX]
14818f42c MOV qword ptr [RCX],RSI
14818f42f MOV RAX,qword ptr [RBP + 0xd0]
14818f436 MOV qword ptr [RCX],RAX
14818f439 MOV qword ptr [RBP + 0xd0],RSI
14818f440 MOV EAX,dword ptr [RBP + 0xd8]
14818f446 MOV dword ptr [RCX + 0x8],EAX
14818f449 MOV EAX,dword ptr [RBP + 0xdc]
14818f44f MOV dword ptr [RCX + 0xc],EAX
14818f452 MOV qword ptr [RBP + 0xd8],RSI
14818f459 MOV RCX,qword ptr [RBP + 0xd0]
14818f460 TEST RCX,RCX
14818f463 JZ 0x14818f46b
14818f465 CALL 0x140e282f0
14818f46a NOP
14818f46b MOV dword ptr [RSP + 0x28],0xffffffff
14818f473 MOV dword ptr [RSP + 0x20],ESI
14818f477 MOV R9D,0x1
14818f47d LEA R8D,[R9 + 0x3]
14818f481 LEA RDX,[0x14cf621a8]
14818f488 LEA RCX,[RSP + 0x50]
14818f48d CALL 0x140d101c0
14818f492 CMP EAX,-0x1
14818f495 JZ 0x14818f58d
14818f49b LEA RDX,[0x14cf621b4]
14818f4a2 LEA RCX,[RBP + 0xe0]
14818f4a9 CALL 0x140cf7080
14818f4ae NOP
14818f4af MOV RCX,qword ptr [RBX]
14818f4b2 LEA RAX,[RBP + 0xe0]
14818f4b9 CMP RAX,RCX
14818f4bc JC 0x14818f52b
14818f4be MOVSXD RDX,dword ptr [RBX + 0xc]
14818f4c2 MOV RAX,RDX
14818f4c5 SHL RAX,0x4
14818f4c9 ADD RAX,RCX
14818f4cc LEA R8,[RBP + 0xe0]
14818f4d3 CMP R8,RAX
14818f4d6 JNC 0x14818f52b
14818f4d8 MOVSXD RAX,dword ptr [RBX + 0x8]
14818f4dc MOV R9,qword ptr [RBP + 0x378]
14818f4e3 MOV qword ptr [RSP + 0x48],0x10
14818f4ec MOV qword ptr [RSP + 0x40],RAX
14818f4f1 MOV qword ptr [RSP + 0x38],RDX
14818f4f6 MOV qword ptr [RSP + 0x30],RCX
14818f4fb LEA RAX,[RBP + 0xe0]
14818f502 MOV qword ptr [RSP + 0x28],RAX
14818f507 MOV qword ptr [RSP + 0x20],R14
14818f50c MOV R8D,0x63e
14818f512 LEA RDX,[0x14cf27ac0]
14818f519 LEA RCX,[0x14bce6eb8]
14818f520 CALL 0x140f8dfd0
14818f525 TEST AL,AL
14818f527 JZ 0x14818f52b
14818f529 NOP
14818f52a INT3
14818f52b MOVSXD RDI,dword ptr [RBX + 0x8]
14818f52f LEA EAX,[RDI + 0x1]
14818f532 MOV dword ptr [RBX + 0x8],EAX
14818f535 CMP EAX,dword ptr [RBX + 0xc]
14818f538 JBE 0x14818f544
14818f53a MOV EDX,EDI
14818f53c MOV RCX,RBX
14818f53f CALL 0x140ca4b30
14818f544 MOV RCX,RDI
14818f547 SHL RCX,0x4
14818f54b ADD RCX,qword ptr [RBX]
14818f54e MOV qword ptr [RCX],RSI
14818f551 MOV RAX,qword ptr [RBP + 0xe0]
14818f558 MOV qword ptr [RCX],RAX
14818f55b MOV qword ptr [RBP + 0xe0],RSI
14818f562 MOV EAX,dword ptr [RBP + 0xe8]
14818f568 MOV dword ptr [RCX + 0x8],EAX
14818f56b MOV EAX,dword ptr [RBP + 0xec]
14818f571 MOV dword ptr [RCX + 0xc],EAX
14818f574 MOV qword ptr [RBP + 0xe8],RSI
14818f57b MOV RCX,qword ptr [RBP + 0xe0]
14818f582 TEST RCX,RCX
14818f585 JZ 0x14818f58d
14818f587 CALL 0x140e282f0
14818f58c NOP
14818f58d MOV dword ptr [RSP + 0x28],0xffffffff
14818f595 MOV dword ptr [RSP + 0x20],ESI
14818f599 MOV R9D,0x1
14818f59f LEA R8D,[R9 + 0x4]
14818f5a3 LEA RDX,[0x14bd8b040]
14818f5aa LEA RCX,[RSP + 0x50]
14818f5af CALL 0x140d101c0
14818f5b4 CMP EAX,-0x1
14818f5b7 JZ 0x14818f6af
14818f5bd LEA RDX,[0x14cf621bc]
14818f5c4 LEA RCX,[RBP + 0xf0]
14818f5cb CALL 0x140cf7080
14818f5d0 NOP
14818f5d1 MOV RCX,qword ptr [RBX]
14818f5d4 LEA RAX,[RBP + 0xf0]
14818f5db CMP RAX,RCX
14818f5de JC 0x14818f64d
14818f5e0 MOVSXD RDX,dword ptr [RBX + 0xc]
14818f5e4 MOV RAX,RDX
14818f5e7 SHL RAX,0x4
14818f5eb ADD RAX,RCX
14818f5ee LEA R8,[RBP + 0xf0]
14818f5f5 CMP R8,RAX
14818f5f8 JNC 0x14818f64d
14818f5fa MOVSXD RAX,dword ptr [RBX + 0x8]
14818f5fe MOV R9,qword ptr [RBP + 0x378]
14818f605 MOV qword ptr [RSP + 0x48],0x10
14818f60e MOV qword ptr [RSP + 0x40],RAX
14818f613 MOV qword ptr [RSP + 0x38],RDX
14818f618 MOV qword ptr [RSP + 0x30],RCX
14818f61d LEA RAX,[RBP + 0xf0]
14818f624 MOV qword ptr [RSP + 0x28],RAX
14818f629 MOV qword ptr [RSP + 0x20],R14
14818f62e MOV R8D,0x63e
14818f634 LEA RDX,[0x14cf27ac0]
14818f63b LEA RCX,[0x14bce6eb8]
14818f642 CALL 0x140f8dfd0
14818f647 TEST AL,AL
14818f649 JZ 0x14818f64d
14818f64b NOP
14818f64c INT3
14818f64d MOVSXD RDI,dword ptr [RBX + 0x8]
14818f651 LEA EAX,[RDI + 0x1]
14818f654 MOV dword ptr [RBX + 0x8],EAX
14818f657 CMP EAX,dword ptr [RBX + 0xc]
14818f65a JBE 0x14818f666
14818f65c MOV EDX,EDI
14818f65e MOV RCX,RBX
14818f661 CALL 0x140ca4b30
14818f666 MOV RCX,RDI
14818f669 SHL RCX,0x4
14818f66d ADD RCX,qword ptr [RBX]
14818f670 MOV qword ptr [RCX],RSI
14818f673 MOV RAX,qword ptr [RBP + 0xf0]
14818f67a MOV qword ptr [RCX],RAX
14818f67d MOV qword ptr [RBP + 0xf0],RSI
14818f684 MOV EAX,dword ptr [RBP + 0xf8]
14818f68a MOV dword ptr [RCX + 0x8],EAX
14818f68d MOV EAX,dword ptr [RBP + 0xfc]
14818f693 MOV dword ptr [RCX + 0xc],EAX
14818f696 MOV qword ptr [RBP + 0xf8],RSI
14818f69d MOV RCX,qword ptr [RBP + 0xf0]
14818f6a4 TEST RCX,RCX
14818f6a7 JZ 0x14818f6af
14818f6a9 CALL 0x140e282f0
14818f6ae NOP
14818f6af MOV dword ptr [RSP + 0x28],0xffffffff
14818f6b7 MOV dword ptr [RSP + 0x20],ESI
14818f6bb MOV R9D,0x1
14818f6c1 LEA R8D,[R9 + 0x6]
14818f6c5 LEA RDX,[0x14cf621c8]
14818f6cc LEA RCX,[RSP + 0x50]
14818f6d1 CALL 0x140d101c0
14818f6d6 CMP EAX,-0x1
14818f6d9 JZ 0x14818f7d1
14818f6df LEA RDX,[0x14cf621d8]
14818f6e6 LEA RCX,[RBP + 0x100]
14818f6ed CALL 0x140cf7080
14818f6f2 NOP
14818f6f3 MOV RCX,qword ptr [RBX]
14818f6f6 LEA RAX,[RBP + 0x100]
14818f6fd CMP RAX,RCX
14818f700 JC 0x14818f76f
14818f702 MOVSXD RDX,dword ptr [RBX + 0xc]
14818f706 MOV RAX,RDX
14818f709 SHL RAX,0x4
14818f70d ADD RAX,RCX
14818f710 LEA R8,[RBP + 0x100]
14818f717 CMP R8,RAX
14818f71a JNC 0x14818f76f
14818f71c MOVSXD RAX,dword ptr [RBX + 0x8]
14818f720 MOV R9,qword ptr [RBP + 0x378]
14818f727 MOV qword ptr [RSP + 0x48],0x10
14818f730 MOV qword ptr [RSP + 0x40],RAX
14818f735 MOV qword ptr [RSP + 0x38],RDX
14818f73a MOV qword ptr [RSP + 0x30],RCX
14818f73f LEA RAX,[RBP + 0x100]
14818f746 MOV qword ptr [RSP + 0x28],RAX
14818f74b MOV qword ptr [RSP + 0x20],R14
14818f750 MOV R8D,0x63e
14818f756 LEA RDX,[0x14cf27ac0]
14818f75d LEA RCX,[0x14bce6eb8]
14818f764 CALL 0x140f8dfd0
14818f769 TEST AL,AL
14818f76b JZ 0x14818f76f
14818f76d NOP
14818f76e INT3
14818f76f MOVSXD RDI,dword ptr [RBX + 0x8]
14818f773 LEA EAX,[RDI + 0x1]
14818f776 MOV dword ptr [RBX + 0x8],EAX
14818f779 CMP EAX,dword ptr [RBX + 0xc]
14818f77c JBE 0x14818f788
14818f77e MOV EDX,EDI
14818f780 MOV RCX,RBX
14818f783 CALL 0x140ca4b30
14818f788 MOV RCX,RDI
14818f78b SHL RCX,0x4
14818f78f ADD RCX,qword ptr [RBX]
14818f792 MOV qword ptr [RCX],RSI
14818f795 MOV RAX,qword ptr [RBP + 0x100]
14818f79c MOV qword ptr [RCX],RAX
14818f79f MOV qword ptr [RBP + 0x100],RSI
14818f7a6 MOV EAX,dword ptr [RBP + 0x108]
14818f7ac MOV dword ptr [RCX + 0x8],EAX
14818f7af MOV EAX,dword ptr [RBP + 0x10c]
14818f7b5 MOV dword ptr [RCX + 0xc],EAX
14818f7b8 MOV qword ptr [RBP + 0x108],RSI
14818f7bf MOV RCX,qword ptr [RBP + 0x100]
14818f7c6 TEST RCX,RCX
14818f7c9 JZ 0x14818f7d1
14818f7cb CALL 0x140e282f0
14818f7d0 NOP
14818f7d1 MOV dword ptr [RSP + 0x28],0xffffffff
14818f7d9 MOV dword ptr [RSP + 0x20],ESI
14818f7dd MOV R9D,0x1
14818f7e3 LEA R8D,[R9 + 0x4]
14818f7e7 LEA RDX,[0x14cf621e0]
14818f7ee LEA RCX,[RSP + 0x50]
14818f7f3 CALL 0x140d101c0
14818f7f8 CMP EAX,-0x1
14818f7fb JZ 0x14818f8f3
14818f801 LEA RDX,[0x14cf621ec]
14818f808 LEA RCX,[RBP + 0x110]
14818f80f CALL 0x140cf7080
14818f814 NOP
14818f815 MOV RCX,qword ptr [RBX]
14818f818 LEA RAX,[RBP + 0x110]
14818f81f CMP RAX,RCX
14818f822 JC 0x14818f891
14818f824 MOVSXD RDX,dword ptr [RBX + 0xc]
14818f828 MOV RAX,RDX
14818f82b SHL RAX,0x4
14818f82f ADD RAX,RCX
14818f832 LEA R8,[RBP + 0x110]
14818f839 CMP R8,RAX
14818f83c JNC 0x14818f891
14818f83e MOVSXD RAX,dword ptr [RBX + 0x8]
14818f842 MOV R9,qword ptr [RBP + 0x378]
14818f849 MOV qword ptr [RSP + 0x48],0x10
14818f852 MOV qword ptr [RSP + 0x40],RAX
14818f857 MOV qword ptr [RSP + 0x38],RDX
14818f85c MOV qword ptr [RSP + 0x30],RCX
14818f861 LEA RAX,[RBP + 0x110]
14818f868 MOV qword ptr [RSP + 0x28],RAX
14818f86d MOV qword ptr [RSP + 0x20],R14
14818f872 MOV R8D,0x63e
14818f878 LEA RDX,[0x14cf27ac0]
14818f87f LEA RCX,[0x14bce6eb8]
14818f886 CALL 0x140f8dfd0
14818f88b TEST AL,AL
14818f88d JZ 0x14818f891
14818f88f NOP
14818f890 INT3
14818f891 MOVSXD RDI,dword ptr [RBX + 0x8]
14818f895 LEA EAX,[RDI + 0x1]
14818f898 MOV dword ptr [RBX + 0x8],EAX
14818f89b CMP EAX,dword ptr [RBX + 0xc]
14818f89e JBE 0x14818f8aa
14818f8a0 MOV EDX,EDI
14818f8a2 MOV RCX,RBX
14818f8a5 CALL 0x140ca4b30
14818f8aa MOV RCX,RDI
14818f8ad SHL RCX,0x4
14818f8b1 ADD RCX,qword ptr [RBX]
14818f8b4 MOV qword ptr [RCX],RSI
14818f8b7 MOV RAX,qword ptr [RBP + 0x110]
14818f8be MOV qword ptr [RCX],RAX
14818f8c1 MOV qword ptr [RBP + 0x110],RSI
14818f8c8 MOV EAX,dword ptr [RBP + 0x118]
14818f8ce MOV dword ptr [RCX + 0x8],EAX
14818f8d1 MOV EAX,dword ptr [RBP + 0x11c]
14818f8d7 MOV dword ptr [RCX + 0xc],EAX
14818f8da MOV qword ptr [RBP + 0x118],RSI
14818f8e1 MOV RCX,qword ptr [RBP + 0x110]
14818f8e8 TEST RCX,RCX
14818f8eb JZ 0x14818f8f3
14818f8ed CALL 0x140e282f0
14818f8f2 NOP
14818f8f3 MOV dword ptr [RSP + 0x28],0xffffffff
14818f8fb MOV dword ptr [RSP + 0x20],ESI
14818f8ff MOV R9D,0x1
14818f905 LEA R8D,[R9 + 0x7]
14818f909 LEA RDX,[0x14cf621f8]
14818f910 LEA RCX,[RSP + 0x50]
14818f915 CALL 0x140d101c0
14818f91a CMP EAX,-0x1
14818f91d JZ 0x14818fa15
14818f923 LEA RDX,[0x14cf62210]
14818f92a LEA RCX,[RBP + 0x120]
14818f931 CALL 0x140cf7080
14818f936 NOP
14818f937 MOV RCX,qword ptr [RBX]
14818f93a LEA RAX,[RBP + 0x120]
14818f941 CMP RAX,RCX
14818f944 JC 0x14818f9b3
14818f946 MOVSXD RDX,dword ptr [RBX + 0xc]
14818f94a MOV RAX,RDX
14818f94d SHL RAX,0x4
14818f951 ADD RAX,RCX
14818f954 LEA R8,[RBP + 0x120]
14818f95b CMP R8,RAX
14818f95e JNC 0x14818f9b3
14818f960 MOVSXD RAX,dword ptr [RBX + 0x8]
14818f964 MOV R9,qword ptr [RBP + 0x378]
14818f96b MOV qword ptr [RSP + 0x48],0x10
14818f974 MOV qword ptr [RSP + 0x40],RAX
14818f979 MOV qword ptr [RSP + 0x38],RDX
14818f97e MOV qword ptr [RSP + 0x30],RCX
14818f983 LEA RAX,[RBP + 0x120]
14818f98a MOV qword ptr [RSP + 0x28],RAX
14818f98f MOV qword ptr [RSP + 0x20],R14
14818f994 MOV R8D,0x63e
14818f99a LEA RDX,[0x14cf27ac0]
14818f9a1 LEA RCX,[0x14bce6eb8]
14818f9a8 CALL 0x140f8dfd0
14818f9ad TEST AL,AL
14818f9af JZ 0x14818f9b3
14818f9b1 NOP
14818f9b2 INT3
14818f9b3 MOVSXD RDI,dword ptr [RBX + 0x8]
14818f9b7 LEA EAX,[RDI + 0x1]
14818f9ba MOV dword ptr [RBX + 0x8],EAX
14818f9bd CMP EAX,dword ptr [RBX + 0xc]
14818f9c0 JBE 0x14818f9cc
14818f9c2 MOV EDX,EDI
14818f9c4 MOV RCX,RBX
14818f9c7 CALL 0x140ca4b30
14818f9cc MOV RCX,RDI
14818f9cf SHL RCX,0x4
14818f9d3 ADD RCX,qword ptr [RBX]
14818f9d6 MOV qword ptr [RCX],RSI
14818f9d9 MOV RAX,qword ptr [RBP + 0x120]
14818f9e0 MOV qword ptr [RCX],RAX
14818f9e3 MOV qword ptr [RBP + 0x120],RSI
14818f9ea MOV EAX,dword ptr [RBP + 0x128]
14818f9f0 MOV dword ptr [RCX + 0x8],EAX
14818f9f3 MOV EAX,dword ptr [RBP + 0x12c]
14818f9f9 MOV dword ptr [RCX + 0xc],EAX
14818f9fc MOV qword ptr [RBP + 0x128],RSI
14818fa03 MOV RCX,qword ptr [RBP + 0x120]
14818fa0a TEST RCX,RCX
14818fa0d JZ 0x14818fa15
14818fa0f CALL 0x140e282f0
14818fa14 NOP
14818fa15 MOV dword ptr [RSP + 0x28],0xffffffff
14818fa1d MOV dword ptr [RSP + 0x20],ESI
14818fa21 MOV R9D,0x1
14818fa27 LEA R8D,[R9 + 0x7]
14818fa2b LEA RDX,[0x14cf62220]
14818fa32 LEA RCX,[RSP + 0x50]
14818fa37 CALL 0x140d101c0
14818fa3c CMP EAX,-0x1
14818fa3f JZ 0x14818fb37
14818fa45 LEA RDX,[0x14cf62238]
14818fa4c LEA RCX,[RBP + 0x130]
14818fa53 CALL 0x140cf7080
14818fa58 NOP
14818fa59 MOV RCX,qword ptr [RBX]
14818fa5c LEA RAX,[RBP + 0x130]
14818fa63 CMP RAX,RCX
14818fa66 JC 0x14818fad5
14818fa68 MOVSXD RDX,dword ptr [RBX + 0xc]
14818fa6c MOV RAX,RDX
14818fa6f SHL RAX,0x4
14818fa73 ADD RAX,RCX
14818fa76 LEA R8,[RBP + 0x130]
14818fa7d CMP R8,RAX
14818fa80 JNC 0x14818fad5
14818fa82 MOVSXD RAX,dword ptr [RBX + 0x8]
14818fa86 MOV R9,qword ptr [RBP + 0x378]
14818fa8d MOV qword ptr [RSP + 0x48],0x10
14818fa96 MOV qword ptr [RSP + 0x40],RAX
14818fa9b MOV qword ptr [RSP + 0x38],RDX
14818faa0 MOV qword ptr [RSP + 0x30],RCX
14818faa5 LEA RAX,[RBP + 0x130]
14818faac MOV qword ptr [RSP + 0x28],RAX
14818fab1 MOV qword ptr [RSP + 0x20],R14
14818fab6 MOV R8D,0x63e
14818fabc LEA RDX,[0x14cf27ac0]
14818fac3 LEA RCX,[0x14bce6eb8]
14818faca CALL 0x140f8dfd0
14818facf TEST AL,AL
14818fad1 JZ 0x14818fad5
14818fad3 NOP
14818fad4 INT3
14818fad5 MOVSXD RDI,dword ptr [RBX + 0x8]
14818fad9 LEA EAX,[RDI + 0x1]
14818fadc MOV dword ptr [RBX + 0x8],EAX
14818fadf CMP EAX,dword ptr [RBX + 0xc]
14818fae2 JBE 0x14818faee
14818fae4 MOV EDX,EDI
14818fae6 MOV RCX,RBX
14818fae9 CALL 0x140ca4b30
14818faee MOV RCX,RDI
14818faf1 SHL RCX,0x4
14818faf5 ADD RCX,qword ptr [RBX]
14818faf8 MOV qword ptr [RCX],RSI
14818fafb MOV RAX,qword ptr [RBP + 0x130]
14818fb02 MOV qword ptr [RCX],RAX
14818fb05 MOV qword ptr [RBP + 0x130],RSI
14818fb0c MOV EAX,dword ptr [RBP + 0x138]
14818fb12 MOV dword ptr [RCX + 0x8],EAX
14818fb15 MOV EAX,dword ptr [RBP + 0x13c]
14818fb1b MOV dword ptr [RCX + 0xc],EAX
14818fb1e MOV qword ptr [RBP + 0x138],RSI
14818fb25 MOV RCX,qword ptr [RBP + 0x130]
14818fb2c TEST RCX,RCX
14818fb2f JZ 0x14818fb37
14818fb31 CALL 0x140e282f0
14818fb36 NOP
14818fb37 MOV dword ptr [RSP + 0x28],0xffffffff
14818fb3f MOV dword ptr [RSP + 0x20],ESI
14818fb43 MOV R9D,0x1
14818fb49 LEA R8D,[R9 + 0x3]
14818fb4d LEA RDX,[0x14cf62248]
14818fb54 LEA RCX,[RSP + 0x50]
14818fb59 CALL 0x140d101c0
14818fb5e CMP EAX,-0x1
14818fb61 JZ 0x14818fc59
14818fb67 LEA RDX,[0x14cf62254]
14818fb6e LEA RCX,[RBP + 0x140]
14818fb75 CALL 0x140cf7080
14818fb7a NOP
14818fb7b MOV RCX,qword ptr [RBX]
14818fb7e LEA RAX,[RBP + 0x140]
14818fb85 CMP RAX,RCX
14818fb88 JC 0x14818fbf7
14818fb8a MOVSXD RDX,dword ptr [RBX + 0xc]
14818fb8e MOV RAX,RDX
14818fb91 SHL RAX,0x4
14818fb95 ADD RAX,RCX
14818fb98 LEA R8,[RBP + 0x140]
14818fb9f CMP R8,RAX
14818fba2 JNC 0x14818fbf7
14818fba4 MOVSXD RAX,dword ptr [RBX + 0x8]
14818fba8 MOV R9,qword ptr [RBP + 0x378]
14818fbaf MOV qword ptr [RSP + 0x48],0x10
14818fbb8 MOV qword ptr [RSP + 0x40],RAX
14818fbbd MOV qword ptr [RSP + 0x38],RDX
14818fbc2 MOV qword ptr [RSP + 0x30],RCX
14818fbc7 LEA RAX,[RBP + 0x140]
14818fbce MOV qword ptr [RSP + 0x28],RAX
14818fbd3 MOV qword ptr [RSP + 0x20],R14
14818fbd8 MOV R8D,0x63e
14818fbde LEA RDX,[0x14cf27ac0]
14818fbe5 LEA RCX,[0x14bce6eb8]
14818fbec CALL 0x140f8dfd0
14818fbf1 TEST AL,AL
14818fbf3 JZ 0x14818fbf7
14818fbf5 NOP
14818fbf6 INT3
14818fbf7 MOVSXD RDI,dword ptr [RBX + 0x8]
14818fbfb LEA EAX,[RDI + 0x1]
14818fbfe MOV dword ptr [RBX + 0x8],EAX
14818fc01 CMP EAX,dword ptr [RBX + 0xc]
14818fc04 JBE 0x14818fc10
14818fc06 MOV EDX,EDI
14818fc08 MOV RCX,RBX
14818fc0b CALL 0x140ca4b30
14818fc10 MOV RCX,RDI
14818fc13 SHL RCX,0x4
14818fc17 ADD RCX,qword ptr [RBX]
14818fc1a MOV qword ptr [RCX],RSI
14818fc1d MOV RAX,qword ptr [RBP + 0x140]
14818fc24 MOV qword ptr [RCX],RAX
14818fc27 MOV qword ptr [RBP + 0x140],RSI
14818fc2e MOV EAX,dword ptr [RBP + 0x148]
14818fc34 MOV dword ptr [RCX + 0x8],EAX
14818fc37 MOV EAX,dword ptr [RBP + 0x14c]
14818fc3d MOV dword ptr [RCX + 0xc],EAX
14818fc40 MOV qword ptr [RBP + 0x148],RSI
14818fc47 MOV RCX,qword ptr [RBP + 0x140]
14818fc4e TEST RCX,RCX
14818fc51 JZ 0x14818fc59
14818fc53 CALL 0x140e282f0
14818fc58 NOP
14818fc59 MOV dword ptr [RSP + 0x28],0xffffffff
14818fc61 MOV dword ptr [RSP + 0x20],ESI
14818fc65 MOV R9D,0x1
14818fc6b LEA R8D,[R9 + 0x6]
14818fc6f LEA RDX,[0x14cf62260]
14818fc76 LEA RCX,[RSP + 0x50]
14818fc7b CALL 0x140d101c0
14818fc80 CMP EAX,-0x1
14818fc83 JZ 0x14818fd7b
14818fc89 LEA RDX,[0x14cf62270]
14818fc90 LEA RCX,[RBP + 0x150]
14818fc97 CALL 0x140cf7080
14818fc9c NOP
14818fc9d MOV RCX,qword ptr [RBX]
14818fca0 LEA RAX,[RBP + 0x150]
14818fca7 CMP RAX,RCX
14818fcaa JC 0x14818fd19
14818fcac MOVSXD RDX,dword ptr [RBX + 0xc]
14818fcb0 MOV RAX,RDX
14818fcb3 SHL RAX,0x4
14818fcb7 ADD RAX,RCX
14818fcba LEA R8,[RBP + 0x150]
14818fcc1 CMP R8,RAX
14818fcc4 JNC 0x14818fd19
14818fcc6 MOVSXD RAX,dword ptr [RBX + 0x8]
14818fcca MOV R9,qword ptr [RBP + 0x378]
14818fcd1 MOV qword ptr [RSP + 0x48],0x10
14818fcda MOV qword ptr [RSP + 0x40],RAX
14818fcdf MOV qword ptr [RSP + 0x38],RDX
14818fce4 MOV qword ptr [RSP + 0x30],RCX
14818fce9 LEA RAX,[RBP + 0x150]
14818fcf0 MOV qword ptr [RSP + 0x28],RAX
14818fcf5 MOV qword ptr [RSP + 0x20],R14
14818fcfa MOV R8D,0x63e
14818fd00 LEA RDX,[0x14cf27ac0]
14818fd07 LEA RCX,[0x14bce6eb8]
14818fd0e CALL 0x140f8dfd0
14818fd13 TEST AL,AL
14818fd15 JZ 0x14818fd19
14818fd17 NOP
14818fd18 INT3
14818fd19 MOVSXD RDI,dword ptr [RBX + 0x8]
14818fd1d LEA EAX,[RDI + 0x1]
14818fd20 MOV dword ptr [RBX + 0x8],EAX
14818fd23 CMP EAX,dword ptr [RBX + 0xc]
14818fd26 JBE 0x14818fd32
14818fd28 MOV EDX,EDI
14818fd2a MOV RCX,RBX
14818fd2d CALL 0x140ca4b30
14818fd32 MOV RCX,RDI
14818fd35 SHL RCX,0x4
14818fd39 ADD RCX,qword ptr [RBX]
14818fd3c MOV qword ptr [RCX],RSI
14818fd3f MOV RAX,qword ptr [RBP + 0x150]
14818fd46 MOV qword ptr [RCX],RAX
14818fd49 MOV qword ptr [RBP + 0x150],RSI
14818fd50 MOV EAX,dword ptr [RBP + 0x158]
14818fd56 MOV dword ptr [RCX + 0x8],EAX
14818fd59 MOV EAX,dword ptr [RBP + 0x15c]
14818fd5f MOV dword ptr [RCX + 0xc],EAX
14818fd62 MOV qword ptr [RBP + 0x158],RSI
14818fd69 MOV RCX,qword ptr [RBP + 0x150]
14818fd70 TEST RCX,RCX
14818fd73 JZ 0x14818fd7b
14818fd75 CALL 0x140e282f0
14818fd7a NOP
14818fd7b MOV dword ptr [RSP + 0x28],0xffffffff
14818fd83 MOV dword ptr [RSP + 0x20],ESI
14818fd87 MOV R9D,0x1
14818fd8d LEA R8D,[R9 + 0x4]
14818fd91 LEA RDX,[0x14cf62278]
14818fd98 LEA RCX,[RSP + 0x50]
14818fd9d CALL 0x140d101c0
14818fda2 CMP EAX,-0x1
14818fda5 JZ 0x14818fe9d
14818fdab LEA RDX,[0x14cf62284]
14818fdb2 LEA RCX,[RBP + 0x160]
14818fdb9 CALL 0x140cf7080
14818fdbe NOP
14818fdbf MOV RCX,qword ptr [RBX]
14818fdc2 LEA RAX,[RBP + 0x160]
14818fdc9 CMP RAX,RCX
14818fdcc JC 0x14818fe3b
14818fdce MOVSXD RDX,dword ptr [RBX + 0xc]
14818fdd2 MOV RAX,RDX
14818fdd5 SHL RAX,0x4
14818fdd9 ADD RAX,RCX
14818fddc LEA R8,[RBP + 0x160]
14818fde3 CMP R8,RAX
14818fde6 JNC 0x14818fe3b
14818fde8 MOVSXD RAX,dword ptr [RBX + 0x8]
14818fdec MOV R9,qword ptr [RBP + 0x378]
14818fdf3 MOV qword ptr [RSP + 0x48],0x10
14818fdfc MOV qword ptr [RSP + 0x40],RAX
14818fe01 MOV qword ptr [RSP + 0x38],RDX
14818fe06 MOV qword ptr [RSP + 0x30],RCX
14818fe0b LEA RAX,[RBP + 0x160]
14818fe12 MOV qword ptr [RSP + 0x28],RAX
14818fe17 MOV qword ptr [RSP + 0x20],R14
14818fe1c MOV R8D,0x63e
14818fe22 LEA RDX,[0x14cf27ac0]
14818fe29 LEA RCX,[0x14bce6eb8]
14818fe30 CALL 0x140f8dfd0
14818fe35 TEST AL,AL
14818fe37 JZ 0x14818fe3b
14818fe39 NOP
14818fe3a INT3
14818fe3b MOVSXD RDI,dword ptr [RBX + 0x8]
14818fe3f LEA EAX,[RDI + 0x1]
14818fe42 MOV dword ptr [RBX + 0x8],EAX
14818fe45 CMP EAX,dword ptr [RBX + 0xc]
14818fe48 JBE 0x14818fe54
14818fe4a MOV EDX,EDI
14818fe4c MOV RCX,RBX
14818fe4f CALL 0x140ca4b30
14818fe54 MOV RCX,RDI
14818fe57 SHL RCX,0x4
14818fe5b ADD RCX,qword ptr [RBX]
14818fe5e MOV qword ptr [RCX],RSI
14818fe61 MOV RAX,qword ptr [RBP + 0x160]
14818fe68 MOV qword ptr [RCX],RAX
14818fe6b MOV qword ptr [RBP + 0x160],RSI
14818fe72 MOV EAX,dword ptr [RBP + 0x168]
14818fe78 MOV dword ptr [RCX + 0x8],EAX
14818fe7b MOV EAX,dword ptr [RBP + 0x16c]
14818fe81 MOV dword ptr [RCX + 0xc],EAX
14818fe84 MOV qword ptr [RBP + 0x168],RSI
14818fe8b MOV RCX,qword ptr [RBP + 0x160]
14818fe92 TEST RCX,RCX
14818fe95 JZ 0x14818fe9d
14818fe97 CALL 0x140e282f0
14818fe9c NOP
14818fe9d MOV dword ptr [RSP + 0x28],0xffffffff
14818fea5 MOV dword ptr [RSP + 0x20],ESI
14818fea9 MOV R9D,0x1
14818feaf LEA R8D,[R9 + 0x2]
14818feb3 LEA RDX,[0x14cf62290]
14818feba LEA RCX,[RSP + 0x50]
14818febf CALL 0x140d101c0
14818fec4 CMP EAX,-0x1
14818fec7 JZ 0x14818ffbf
14818fecd LEA RDX,[0x14cf62298]
14818fed4 LEA RCX,[RBP + 0x170]
14818fedb CALL 0x140cf7080
14818fee0 NOP
14818fee1 MOV RCX,qword ptr [RBX]
14818fee4 LEA RAX,[RBP + 0x170]
14818feeb CMP RAX,RCX
14818feee JC 0x14818ff5d
14818fef0 MOVSXD RDX,dword ptr [RBX + 0xc]
14818fef4 MOV RAX,RDX
14818fef7 SHL RAX,0x4
14818fefb ADD RAX,RCX
14818fefe LEA R8,[RBP + 0x170]
14818ff05 CMP R8,RAX
14818ff08 JNC 0x14818ff5d
14818ff0a MOVSXD RAX,dword ptr [RBX + 0x8]
14818ff0e MOV R9,qword ptr [RBP + 0x378]
14818ff15 MOV qword ptr [RSP + 0x48],0x10
14818ff1e MOV qword ptr [RSP + 0x40],RAX
14818ff23 MOV qword ptr [RSP + 0x38],RDX
14818ff28 MOV qword ptr [RSP + 0x30],RCX
14818ff2d LEA RAX,[RBP + 0x170]
14818ff34 MOV qword ptr [RSP + 0x28],RAX
14818ff39 MOV qword ptr [RSP + 0x20],R14
14818ff3e MOV R8D,0x63e
14818ff44 LEA RDX,[0x14cf27ac0]
14818ff4b LEA RCX,[0x14bce6eb8]
14818ff52 CALL 0x140f8dfd0
14818ff57 TEST AL,AL
14818ff59 JZ 0x14818ff5d
14818ff5b NOP
14818ff5c INT3
14818ff5d MOVSXD RDI,dword ptr [RBX + 0x8]
14818ff61 LEA EAX,[RDI + 0x1]
14818ff64 MOV dword ptr [RBX + 0x8],EAX
14818ff67 CMP EAX,dword ptr [RBX + 0xc]
14818ff6a JBE 0x14818ff76
14818ff6c MOV EDX,EDI
14818ff6e MOV RCX,RBX
14818ff71 CALL 0x140ca4b30
14818ff76 MOV RCX,RDI
14818ff79 SHL RCX,0x4
14818ff7d ADD RCX,qword ptr [RBX]
14818ff80 MOV qword ptr [RCX],RSI
14818ff83 MOV RAX,qword ptr [RBP + 0x170]
14818ff8a MOV qword ptr [RCX],RAX
14818ff8d MOV qword ptr [RBP + 0x170],RSI
14818ff94 MOV EAX,dword ptr [RBP + 0x178]
14818ff9a MOV dword ptr [RCX + 0x8],EAX
14818ff9d MOV EAX,dword ptr [RBP + 0x17c]
14818ffa3 MOV dword ptr [RCX + 0xc],EAX
14818ffa6 MOV qword ptr [RBP + 0x178],RSI
14818ffad MOV RCX,qword ptr [RBP + 0x170]
14818ffb4 TEST RCX,RCX
14818ffb7 JZ 0x14818ffbf
14818ffb9 CALL 0x140e282f0
14818ffbe NOP
14818ffbf MOV dword ptr [RSP + 0x28],0xffffffff
14818ffc7 MOV dword ptr [RSP + 0x20],ESI
14818ffcb MOV R9D,0x1
14818ffd1 LEA R8D,[R9 + 0xa]
14818ffd5 LEA RDX,[0x14cf622a0]
14818ffdc LEA RCX,[RSP + 0x50]
14818ffe1 CALL 0x140d101c0
14818ffe6 CMP EAX,-0x1
14818ffe9 JZ 0x1481900e1
14818ffef LEA RDX,[0x14cf622b8]
14818fff6 LEA RCX,[RBP + 0x180]
14818fffd CALL 0x140cf7080
148190002 NOP
148190003 MOV RCX,qword ptr [RBX]
148190006 LEA RAX,[RBP + 0x180]
14819000d CMP RAX,RCX
148190010 JC 0x14819007f
148190012 MOVSXD RDX,dword ptr [RBX + 0xc]
148190016 MOV RAX,RDX
148190019 SHL RAX,0x4
14819001d ADD RAX,RCX
148190020 LEA R8,[RBP + 0x180]
148190027 CMP R8,RAX
14819002a JNC 0x14819007f
14819002c MOVSXD RAX,dword ptr [RBX + 0x8]
148190030 MOV R9,qword ptr [RBP + 0x378]
148190037 MOV qword ptr [RSP + 0x48],0x10
148190040 MOV qword ptr [RSP + 0x40],RAX
148190045 MOV qword ptr [RSP + 0x38],RDX
14819004a MOV qword ptr [RSP + 0x30],RCX
14819004f LEA RAX,[RBP + 0x180]
148190056 MOV qword ptr [RSP + 0x28],RAX
14819005b MOV qword ptr [RSP + 0x20],R14
148190060 MOV R8D,0x63e
148190066 LEA RDX,[0x14cf27ac0]
14819006d LEA RCX,[0x14bce6eb8]
148190074 CALL 0x140f8dfd0
148190079 TEST AL,AL
14819007b JZ 0x14819007f
14819007d NOP
14819007e INT3
14819007f MOVSXD RDI,dword ptr [RBX + 0x8]
148190083 LEA EAX,[RDI + 0x1]
148190086 MOV dword ptr [RBX + 0x8],EAX
148190089 CMP EAX,dword ptr [RBX + 0xc]
14819008c JBE 0x148190098
14819008e MOV EDX,EDI
148190090 MOV RCX,RBX
148190093 CALL 0x140ca4b30
148190098 MOV RCX,RDI
14819009b SHL RCX,0x4
14819009f ADD RCX,qword ptr [RBX]
1481900a2 MOV qword ptr [RCX],RSI
1481900a5 MOV RAX,qword ptr [RBP + 0x180]
1481900ac MOV qword ptr [RCX],RAX
1481900af MOV qword ptr [RBP + 0x180],RSI
1481900b6 MOV EAX,dword ptr [RBP + 0x188]
1481900bc MOV dword ptr [RCX + 0x8],EAX
1481900bf MOV EAX,dword ptr [RBP + 0x18c]
1481900c5 MOV dword ptr [RCX + 0xc],EAX
1481900c8 MOV qword ptr [RBP + 0x188],RSI
1481900cf MOV RCX,qword ptr [RBP + 0x180]
1481900d6 TEST RCX,RCX
1481900d9 JZ 0x1481900e1
1481900db CALL 0x140e282f0
1481900e0 NOP
1481900e1 MOV dword ptr [RSP + 0x28],0xffffffff
1481900e9 MOV dword ptr [RSP + 0x20],ESI
1481900ed MOV R9D,0x1
1481900f3 LEA R8D,[R9 + 0x8]
1481900f7 LEA RDX,[0x14cf622c8]
1481900fe LEA RCX,[RSP + 0x50]
148190103 CALL 0x140d101c0
148190108 CMP EAX,-0x1
14819010b JZ 0x148190203
148190111 LEA RDX,[0x14cf622e0]
148190118 LEA RCX,[RBP + 0x190]
14819011f CALL 0x140cf7080
148190124 NOP
148190125 MOV RCX,qword ptr [RBX]
148190128 LEA RAX,[RBP + 0x190]
14819012f CMP RAX,RCX
148190132 JC 0x1481901a1
148190134 MOVSXD RDX,dword ptr [RBX + 0xc]
148190138 MOV RAX,RDX
14819013b SHL RAX,0x4
14819013f ADD RAX,RCX
148190142 LEA R8,[RBP + 0x190]
148190149 CMP R8,RAX
14819014c JNC 0x1481901a1
14819014e MOVSXD RAX,dword ptr [RBX + 0x8]
148190152 MOV R9,qword ptr [RBP + 0x378]
148190159 MOV qword ptr [RSP + 0x48],0x10
148190162 MOV qword ptr [RSP + 0x40],RAX
148190167 MOV qword ptr [RSP + 0x38],RDX
14819016c MOV qword ptr [RSP + 0x30],RCX
148190171 LEA RAX,[RBP + 0x190]
148190178 MOV qword ptr [RSP + 0x28],RAX
14819017d MOV qword ptr [RSP + 0x20],R14
148190182 MOV R8D,0x63e
148190188 LEA RDX,[0x14cf27ac0]
14819018f LEA RCX,[0x14bce6eb8]
148190196 CALL 0x140f8dfd0
14819019b TEST AL,AL
14819019d JZ 0x1481901a1
14819019f NOP
1481901a0 INT3
1481901a1 MOVSXD RDI,dword ptr [RBX + 0x8]
1481901a5 LEA EAX,[RDI + 0x1]
1481901a8 MOV dword ptr [RBX + 0x8],EAX
1481901ab CMP EAX,dword ptr [RBX + 0xc]
1481901ae JBE 0x1481901ba
1481901b0 MOV EDX,EDI
1481901b2 MOV RCX,RBX
1481901b5 CALL 0x140ca4b30
1481901ba MOV RCX,RDI
1481901bd SHL RCX,0x4
1481901c1 ADD RCX,qword ptr [RBX]
1481901c4 MOV qword ptr [RCX],RSI
1481901c7 MOV RAX,qword ptr [RBP + 0x190]
1481901ce MOV qword ptr [RCX],RAX
1481901d1 MOV qword ptr [RBP + 0x190],RSI
1481901d8 MOV EAX,dword ptr [RBP + 0x198]
1481901de MOV dword ptr [RCX + 0x8],EAX
1481901e1 MOV EAX,dword ptr [RBP + 0x19c]
1481901e7 MOV dword ptr [RCX + 0xc],EAX
1481901ea MOV qword ptr [RBP + 0x198],RSI
1481901f1 MOV RCX,qword ptr [RBP + 0x190]
1481901f8 TEST RCX,RCX
1481901fb JZ 0x148190203
1481901fd CALL 0x140e282f0
148190202 NOP
148190203 MOV dword ptr [RSP + 0x28],0xffffffff
14819020b MOV dword ptr [RSP + 0x20],ESI
14819020f MOV R9D,0x1
148190215 LEA R8D,[R9 + 0x7]
148190219 LEA RDX,[0x14cf622f0]
148190220 LEA RCX,[RSP + 0x50]
148190225 CALL 0x140d101c0
14819022a CMP EAX,-0x1
14819022d JZ 0x148190325
148190233 LEA RDX,[0x14cf62308]
14819023a LEA RCX,[RBP + 0x1a0]
148190241 CALL 0x140cf7080
148190246 NOP
148190247 MOV RCX,qword ptr [RBX]
14819024a LEA RAX,[RBP + 0x1a0]
148190251 CMP RAX,RCX
148190254 JC 0x1481902c3
148190256 MOVSXD RDX,dword ptr [RBX + 0xc]
14819025a MOV RAX,RDX
14819025d SHL RAX,0x4
148190261 ADD RAX,RCX
148190264 LEA R8,[RBP + 0x1a0]
14819026b CMP R8,RAX
14819026e JNC 0x1481902c3
148190270 MOVSXD RAX,dword ptr [RBX + 0x8]
148190274 MOV R9,qword ptr [RBP + 0x378]
14819027b MOV qword ptr [RSP + 0x48],0x10
148190284 MOV qword ptr [RSP + 0x40],RAX
148190289 MOV qword ptr [RSP + 0x38],RDX
14819028e MOV qword ptr [RSP + 0x30],RCX
148190293 LEA RAX,[RBP + 0x1a0]
14819029a MOV qword ptr [RSP + 0x28],RAX
14819029f MOV qword ptr [RSP + 0x20],R14
1481902a4 MOV R8D,0x63e
1481902aa LEA RDX,[0x14cf27ac0]
1481902b1 LEA RCX,[0x14bce6eb8]
1481902b8 CALL 0x140f8dfd0
1481902bd TEST AL,AL
1481902bf JZ 0x1481902c3
1481902c1 NOP
1481902c2 INT3
1481902c3 MOVSXD RDI,dword ptr [RBX + 0x8]
1481902c7 LEA EAX,[RDI + 0x1]
1481902ca MOV dword ptr [RBX + 0x8],EAX
1481902cd CMP EAX,dword ptr [RBX + 0xc]
1481902d0 JBE 0x1481902dc
1481902d2 MOV EDX,EDI
1481902d4 MOV RCX,RBX
1481902d7 CALL 0x140ca4b30
1481902dc MOV RCX,RDI
1481902df SHL RCX,0x4
1481902e3 ADD RCX,qword ptr [RBX]
1481902e6 MOV qword ptr [RCX],RSI
1481902e9 MOV RAX,qword ptr [RBP + 0x1a0]
1481902f0 MOV qword ptr [RCX],RAX
1481902f3 MOV qword ptr [RBP + 0x1a0],RSI
1481902fa MOV EAX,dword ptr [RBP + 0x1a8]
148190300 MOV dword ptr [RCX + 0x8],EAX
148190303 MOV EAX,dword ptr [RBP + 0x1ac]
148190309 MOV dword ptr [RCX + 0xc],EAX
14819030c MOV qword ptr [RBP + 0x1a8],RSI
148190313 MOV RCX,qword ptr [RBP + 0x1a0]
14819031a TEST RCX,RCX
14819031d JZ 0x148190325
14819031f CALL 0x140e282f0
148190324 NOP
148190325 MOV dword ptr [RSP + 0x28],0xffffffff
14819032d MOV dword ptr [RSP + 0x20],ESI
148190331 MOV R9D,0x1
148190337 LEA R8D,[R9 + 0x7]
14819033b LEA RDX,[0x14cf62318]
148190342 LEA RCX,[RSP + 0x50]
148190347 CALL 0x140d101c0
14819034c CMP EAX,-0x1
14819034f JZ 0x148190447
148190355 LEA RDX,[0x14cf62330]
14819035c LEA RCX,[RBP + 0x1b0]
148190363 CALL 0x140cf7080
148190368 NOP
148190369 MOV RCX,qword ptr [RBX]
14819036c LEA RAX,[RBP + 0x1b0]
148190373 CMP RAX,RCX
148190376 JC 0x1481903e5
148190378 MOVSXD RDX,dword ptr [RBX + 0xc]
14819037c MOV RAX,RDX
14819037f SHL RAX,0x4
148190383 ADD RAX,RCX
148190386 LEA R8,[RBP + 0x1b0]
14819038d CMP R8,RAX
148190390 JNC 0x1481903e5
148190392 MOVSXD RAX,dword ptr [RBX + 0x8]
148190396 MOV R9,qword ptr [RBP + 0x378]
14819039d MOV qword ptr [RSP + 0x48],0x10
1481903a6 MOV qword ptr [RSP + 0x40],RAX
1481903ab MOV qword ptr [RSP + 0x38],RDX
1481903b0 MOV qword ptr [RSP + 0x30],RCX
1481903b5 LEA RAX,[RBP + 0x1b0]
1481903bc MOV qword ptr [RSP + 0x28],RAX
1481903c1 MOV qword ptr [RSP + 0x20],R14
1481903c6 MOV R8D,0x63e
1481903cc LEA RDX,[0x14cf27ac0]
1481903d3 LEA RCX,[0x14bce6eb8]
1481903da CALL 0x140f8dfd0
1481903df TEST AL,AL
1481903e1 JZ 0x1481903e5
1481903e3 NOP
1481903e4 INT3
1481903e5 MOVSXD RDI,dword ptr [RBX + 0x8]
1481903e9 LEA EAX,[RDI + 0x1]
1481903ec MOV dword ptr [RBX + 0x8],EAX
1481903ef CMP EAX,dword ptr [RBX + 0xc]
1481903f2 JBE 0x1481903fe
1481903f4 MOV EDX,EDI
1481903f6 MOV RCX,RBX
1481903f9 CALL 0x140ca4b30
1481903fe MOV RCX,RDI
148190401 SHL RCX,0x4
148190405 ADD RCX,qword ptr [RBX]
148190408 MOV qword ptr [RCX],RSI
14819040b MOV RAX,qword ptr [RBP + 0x1b0]
148190412 MOV qword ptr [RCX],RAX
148190415 MOV qword ptr [RBP + 0x1b0],RSI
14819041c MOV EAX,dword ptr [RBP + 0x1b8]
148190422 MOV dword ptr [RCX + 0x8],EAX
148190425 MOV EAX,dword ptr [RBP + 0x1bc]
14819042b MOV dword ptr [RCX + 0xc],EAX
14819042e MOV qword ptr [RBP + 0x1b8],RSI
148190435 MOV RCX,qword ptr [RBP + 0x1b0]
14819043c TEST RCX,RCX
14819043f JZ 0x148190447
148190441 CALL 0x140e282f0
148190446 NOP
148190447 MOV dword ptr [RSP + 0x28],0xffffffff
14819044f MOV dword ptr [RSP + 0x20],ESI
148190453 MOV R9D,0x1
148190459 LEA R8D,[R9 + 0x5]
14819045d LEA RDX,[0x14cf62340]
148190464 LEA RCX,[RSP + 0x50]
148190469 CALL 0x140d101c0
14819046e CMP EAX,-0x1
148190471 JZ 0x148190569
148190477 LEA RDX,[0x14cf62350]
14819047e LEA RCX,[RBP + 0x1c0]
148190485 CALL 0x140cf7080
14819048a NOP
14819048b MOV RCX,qword ptr [RBX]
14819048e LEA RAX,[RBP + 0x1c0]
148190495 CMP RAX,RCX
148190498 JC 0x148190507
14819049a MOVSXD RDX,dword ptr [RBX + 0xc]
14819049e MOV RAX,RDX
1481904a1 SHL RAX,0x4
1481904a5 ADD RAX,RCX
1481904a8 LEA R8,[RBP + 0x1c0]
1481904af CMP R8,RAX
1481904b2 JNC 0x148190507
1481904b4 MOVSXD RAX,dword ptr [RBX + 0x8]
1481904b8 MOV R9,qword ptr [RBP + 0x378]
1481904bf MOV qword ptr [RSP + 0x48],0x10
1481904c8 MOV qword ptr [RSP + 0x40],RAX
1481904cd MOV qword ptr [RSP + 0x38],RDX
1481904d2 MOV qword ptr [RSP + 0x30],RCX
1481904d7 LEA RAX,[RBP + 0x1c0]
1481904de MOV qword ptr [RSP + 0x28],RAX
1481904e3 MOV qword ptr [RSP + 0x20],R14
1481904e8 MOV R8D,0x63e
1481904ee LEA RDX,[0x14cf27ac0]
1481904f5 LEA RCX,[0x14bce6eb8]
1481904fc CALL 0x140f8dfd0
148190501 TEST AL,AL
148190503 JZ 0x148190507
148190505 NOP
148190506 INT3
148190507 MOVSXD RDI,dword ptr [RBX + 0x8]
14819050b LEA EAX,[RDI + 0x1]
14819050e MOV dword ptr [RBX + 0x8],EAX
148190511 CMP EAX,dword ptr [RBX + 0xc]
148190514 JBE 0x148190520
148190516 MOV EDX,EDI
148190518 MOV RCX,RBX
14819051b CALL 0x140ca4b30
148190520 MOV RCX,RDI
148190523 SHL RCX,0x4
148190527 ADD RCX,qword ptr [RBX]
14819052a MOV qword ptr [RCX],RSI
14819052d MOV RAX,qword ptr [RBP + 0x1c0]
148190534 MOV qword ptr [RCX],RAX
148190537 MOV qword ptr [RBP + 0x1c0],RSI
14819053e MOV EAX,dword ptr [RBP + 0x1c8]
148190544 MOV dword ptr [RCX + 0x8],EAX
148190547 MOV EAX,dword ptr [RBP + 0x1cc]
14819054d MOV dword ptr [RCX + 0xc],EAX
148190550 MOV qword ptr [RBP + 0x1c8],RSI
148190557 MOV RCX,qword ptr [RBP + 0x1c0]
14819055e TEST RCX,RCX
148190561 JZ 0x148190569
148190563 CALL 0x140e282f0
148190568 NOP
148190569 MOV dword ptr [RSP + 0x28],0xffffffff
148190571 MOV dword ptr [RSP + 0x20],ESI
148190575 MOV R9D,0x1
14819057b LEA R8D,[R9 + 0x6]
14819057f LEA RDX,[0x14cf62358]
148190586 LEA RCX,[RSP + 0x50]
14819058b CALL 0x140d101c0
148190590 CMP EAX,-0x1
148190593 JZ 0x14819068b
148190599 LEA RDX,[0x14cf62368]
1481905a0 LEA RCX,[RBP + 0x1d0]
1481905a7 CALL 0x140cf7080
1481905ac NOP
1481905ad MOV RCX,qword ptr [RBX]
1481905b0 LEA RAX,[RBP + 0x1d0]
1481905b7 CMP RAX,RCX
1481905ba JC 0x148190629
1481905bc MOVSXD RDX,dword ptr [RBX + 0xc]
1481905c0 MOV RAX,RDX
1481905c3 SHL RAX,0x4
1481905c7 ADD RAX,RCX
1481905ca LEA R8,[RBP + 0x1d0]
1481905d1 CMP R8,RAX
1481905d4 JNC 0x148190629
1481905d6 MOVSXD RAX,dword ptr [RBX + 0x8]
1481905da MOV R9,qword ptr [RBP + 0x378]
1481905e1 MOV qword ptr [RSP + 0x48],0x10
1481905ea MOV qword ptr [RSP + 0x40],RAX
1481905ef MOV qword ptr [RSP + 0x38],RDX
1481905f4 MOV qword ptr [RSP + 0x30],RCX
1481905f9 LEA RAX,[RBP + 0x1d0]
148190600 MOV qword ptr [RSP + 0x28],RAX
148190605 MOV qword ptr [RSP + 0x20],R14
14819060a MOV R8D,0x63e
148190610 LEA RDX,[0x14cf27ac0]
148190617 LEA RCX,[0x14bce6eb8]
14819061e CALL 0x140f8dfd0
148190623 TEST AL,AL
148190625 JZ 0x148190629
148190627 NOP
148190628 INT3
148190629 MOVSXD RDI,dword ptr [RBX + 0x8]
14819062d LEA EAX,[RDI + 0x1]
148190630 MOV dword ptr [RBX + 0x8],EAX
148190633 CMP EAX,dword ptr [RBX + 0xc]
148190636 JBE 0x148190642
148190638 MOV EDX,EDI
14819063a MOV RCX,RBX
14819063d CALL 0x140ca4b30
148190642 MOV RCX,RDI
148190645 SHL RCX,0x4
148190649 ADD RCX,qword ptr [RBX]
14819064c MOV qword ptr [RCX],RSI
14819064f MOV RAX,qword ptr [RBP + 0x1d0]
148190656 MOV qword ptr [RCX],RAX
148190659 MOV qword ptr [RBP + 0x1d0],RSI
148190660 MOV EAX,dword ptr [RBP + 0x1d8]
148190666 MOV dword ptr [RCX + 0x8],EAX
148190669 MOV EAX,dword ptr [RBP + 0x1dc]
14819066f MOV dword ptr [RCX + 0xc],EAX
148190672 MOV qword ptr [RBP + 0x1d8],RSI
148190679 MOV RCX,qword ptr [RBP + 0x1d0]
148190680 TEST RCX,RCX
148190683 JZ 0x14819068b
148190685 CALL 0x140e282f0
14819068a NOP
14819068b MOV dword ptr [RSP + 0x28],0xffffffff
148190693 MOV dword ptr [RSP + 0x20],ESI
148190697 MOV R9D,0x1
14819069d LEA R8D,[R9 + 0x6]
1481906a1 LEA RDX,[0x14cf62370]
1481906a8 LEA RCX,[RSP + 0x50]
1481906ad CALL 0x140d101c0
1481906b2 CMP EAX,-0x1
1481906b5 JZ 0x1481907ad
1481906bb LEA RDX,[0x14cf62380]
1481906c2 LEA RCX,[RBP + 0x1e0]
1481906c9 CALL 0x140cf7080
1481906ce NOP
1481906cf MOV RCX,qword ptr [RBX]
1481906d2 LEA RAX,[RBP + 0x1e0]
1481906d9 CMP RAX,RCX
1481906dc JC 0x14819074b
1481906de MOVSXD RDX,dword ptr [RBX + 0xc]
1481906e2 MOV RAX,RDX
1481906e5 SHL RAX,0x4
1481906e9 ADD RAX,RCX
1481906ec LEA R8,[RBP + 0x1e0]
1481906f3 CMP R8,RAX
1481906f6 JNC 0x14819074b
1481906f8 MOVSXD RAX,dword ptr [RBX + 0x8]
1481906fc MOV R9,qword ptr [RBP + 0x378]
148190703 MOV qword ptr [RSP + 0x48],0x10
14819070c MOV qword ptr [RSP + 0x40],RAX
148190711 MOV qword ptr [RSP + 0x38],RDX
148190716 MOV qword ptr [RSP + 0x30],RCX
14819071b LEA RAX,[RBP + 0x1e0]
148190722 MOV qword ptr [RSP + 0x28],RAX
148190727 MOV qword ptr [RSP + 0x20],R14
14819072c MOV R8D,0x63e
148190732 LEA RDX,[0x14cf27ac0]
148190739 LEA RCX,[0x14bce6eb8]
148190740 CALL 0x140f8dfd0
148190745 TEST AL,AL
148190747 JZ 0x14819074b
148190749 NOP
14819074a INT3
14819074b MOVSXD RDI,dword ptr [RBX + 0x8]
14819074f LEA EAX,[RDI + 0x1]
148190752 MOV dword ptr [RBX + 0x8],EAX
148190755 CMP EAX,dword ptr [RBX + 0xc]
148190758 JBE 0x148190764
14819075a MOV EDX,EDI
14819075c MOV RCX,RBX
14819075f CALL 0x140ca4b30
148190764 MOV RCX,RDI
148190767 SHL RCX,0x4
14819076b ADD RCX,qword ptr [RBX]
14819076e MOV qword ptr [RCX],RSI
148190771 MOV RAX,qword ptr [RBP + 0x1e0]
148190778 MOV qword ptr [RCX],RAX
14819077b MOV qword ptr [RBP + 0x1e0],RSI
148190782 MOV EAX,dword ptr [RBP + 0x1e8]
148190788 MOV dword ptr [RCX + 0x8],EAX
14819078b MOV EAX,dword ptr [RBP + 0x1ec]
148190791 MOV dword ptr [RCX + 0xc],EAX
148190794 MOV qword ptr [RBP + 0x1e8],RSI
14819079b MOV RCX,qword ptr [RBP + 0x1e0]
1481907a2 TEST RCX,RCX
1481907a5 JZ 0x1481907ad
1481907a7 CALL 0x140e282f0
1481907ac NOP
1481907ad MOV dword ptr [RSP + 0x28],0xffffffff
1481907b5 MOV dword ptr [RSP + 0x20],ESI
1481907b9 MOV R9D,0x1
1481907bf LEA R8D,[R9 + 0x6]
1481907c3 LEA RDX,[0x14cf62388]
1481907ca LEA RCX,[RSP + 0x50]
1481907cf CALL 0x140d101c0
1481907d4 CMP EAX,-0x1
1481907d7 JZ 0x1481908b1
1481907dd LEA RDX,[0x14cf62398]
1481907e4 LEA RCX,[RBP + -0x10]
1481907e8 CALL 0x140cf7080
1481907ed NOP
1481907ee MOV R10,qword ptr [RBX]
1481907f1 LEA RAX,[RBP + -0x10]
1481907f5 CMP RAX,R10
1481907f8 JC 0x148190861
1481907fa MOVSXD R11,dword ptr [RBX + 0xc]
1481907fe MOV RAX,R11
148190801 SHL RAX,0x4
148190805 ADD RAX,R10
148190808 LEA RCX,[RBP + -0x10]
14819080c CMP RCX,RAX
14819080f JNC 0x148190861
148190811 MOVSXD RAX,dword ptr [RBX + 0x8]
148190815 MOV R9,qword ptr [RBP + 0x378]
14819081c MOV qword ptr [RSP + 0x48],0x10
148190825 MOV qword ptr [RSP + 0x40],RAX
14819082a MOV qword ptr [RSP + 0x38],R11
14819082f MOV qword ptr [RSP + 0x30],R10
148190834 LEA RAX,[RBP + -0x10]
148190838 MOV qword ptr [RSP + 0x28],RAX
14819083d MOV qword ptr [RSP + 0x20],R14
148190842 MOV R8D,0x63e
148190848 LEA RDX,[0x14cf27ac0]
14819084f LEA RCX,[0x14bce6eb8]
148190856 CALL 0x140f8dfd0
14819085b TEST AL,AL
14819085d JZ 0x148190861
14819085f NOP
148190860 INT3
148190861 MOVSXD RDI,dword ptr [RBX + 0x8]
148190865 LEA EAX,[RDI + 0x1]
148190868 MOV dword ptr [RBX + 0x8],EAX
14819086b CMP EAX,dword ptr [RBX + 0xc]
14819086e JBE 0x14819087a
148190870 MOV EDX,EDI
148190872 MOV RCX,RBX
148190875 CALL 0x140ca4b30
14819087a MOV RCX,RDI
14819087d SHL RCX,0x4
148190881 ADD RCX,qword ptr [RBX]
148190884 MOV qword ptr [RCX],RSI
148190887 MOV RAX,qword ptr [RBP + -0x10]
14819088b MOV qword ptr [RCX],RAX
14819088e MOV qword ptr [RBP + -0x10],RSI
148190892 MOV EAX,dword ptr [RBP + -0x8]
148190895 MOV dword ptr [RCX + 0x8],EAX
148190898 MOV EAX,dword ptr [RBP + -0x4]
14819089b MOV dword ptr [RCX + 0xc],EAX
14819089e MOV qword ptr [RBP + -0x8],RSI
1481908a2 MOV RCX,qword ptr [RBP + -0x10]
1481908a6 TEST RCX,RCX
1481908a9 JZ 0x1481908b1
1481908ab CALL 0x140e282f0
1481908b0 NOP
1481908b1 MOV RCX,qword ptr [RSP + 0x50]
1481908b6 TEST RCX,RCX
1481908b9 JZ 0x1481908c1
1481908bb CALL 0x140e282f0
1481908c0 NOP
1481908c1 MOV RAX,RBX
1481908c4 LEA R11,[RSP + 0x460]
1481908cc MOV RBX,qword ptr [R11 + 0x28]
1481908d0 MOV RSI,qword ptr [R11 + 0x30]
1481908d4 MOV RSP,R11
1481908d7 POP R14
1481908d9 POP RDI
1481908da POP RBP
1481908db RET
*/

/* 14818c770 FilterActionConstructor */

undefined8 *
FilterActionConstructor
          (undefined8 *param_1,undefined4 *param_2,undefined8 *param_3,undefined8 *param_4,
          undefined1 param_5,undefined1 param_6,undefined1 param_7,undefined8 param_8,
          undefined8 param_9,undefined8 param_10,undefined8 param_11,undefined8 param_12,
          undefined8 param_13,undefined8 param_14,undefined8 param_15,undefined8 param_16,
          undefined8 param_17,undefined4 param_18)

{
  *param_1 = &UNK_14cf63880;
  param_1[1] = *(undefined8 *)(param_2 + 2);
  *(undefined4 *)(param_1 + 2) = *param_2;
  *(undefined8 *)((longlong)param_1 + 0x14) = 0;
  func_0x00014190e290((undefined8 *)((longlong)param_1 + 0x14),*(undefined8 *)(param_2 + 4));
  param_1[4] = 0;
  func_0x0001481415f0(param_1 + 4,*param_3,*(undefined4 *)(param_3 + 1),0);
  param_1[6] = 0;
  func_0x000140c64610(param_1 + 6,*param_4,*(undefined4 *)(param_4 + 1),0);
  *(undefined1 *)(param_1 + 8) = param_5;
  *(undefined1 *)((longlong)param_1 + 0x41) = param_6;
  *(undefined1 *)((longlong)param_1 + 0x42) = param_7;
  param_1[9] = param_8;
  param_1[10] = param_9;
  param_1[0xb] = param_10;
  param_1[0xc] = param_11;
  param_1[0xd] = param_12;
  param_1[0xe] = param_13;
  param_1[0xf] = param_14;
  param_1[0x10] = param_15;
  param_1[0x11] = param_16;
  param_1[0x12] = param_17;
  *(undefined4 *)(param_1 + 0x13) = 0;
  *(undefined4 *)((longlong)param_1 + 0x9c) = param_18;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  param_1[0x1c] = 0;
  param_1[0x1d] = 0;
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  param_1[0x20] = 0;
  param_1[0x21] = 0;
  *(undefined4 *)(param_1 + 0x22) = 0;
  if ((undefined4 *)param_1[0x12] != (undefined4 *)0x0) {
    *(undefined4 *)param_1[0x12] = *(undefined4 *)(param_1 + 5);
  }
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf638a0,*(undefined4 *)(param_1 + 5));
  }
  if ((((*(char *)(param_1 + 8) != '\0') || (*(char *)((longlong)param_1 + 0x41) != '\0')) ||
      (*(char *)((longlong)param_1 + 0x42) != '\0')) && (2 < DAT_14eab53c8)) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf63930,*(char *)(param_1 + 8),
                        *(undefined1 *)((longlong)param_1 + 0x41),
                        *(undefined1 *)((longlong)param_1 + 0x42));
  }
  return param_1;
}


/* Instruction evidence:
14818c770 MOV qword ptr [RSP + 0x18],RBX
14818c775 MOV qword ptr [RSP + 0x8],RCX
14818c77a PUSH RBP
14818c77b PUSH RSI
14818c77c PUSH RDI
14818c77d SUB RSP,0x30
14818c781 MOV RDI,R9
14818c784 MOV RBX,R8
14818c787 MOV RSI,RCX
14818c78a LEA RAX,[0x14cf63880]
14818c791 MOV qword ptr [RCX],RAX
14818c794 MOV RAX,qword ptr [RDX + 0x8]
14818c798 MOV qword ptr [RCX + 0x8],RAX
14818c79c MOV EAX,dword ptr [RDX]
14818c79e MOV dword ptr [RCX + 0x10],EAX
14818c7a1 ADD RCX,0x14
14818c7a5 XOR EBP,EBP
14818c7a7 MOV qword ptr [RCX],RBP
14818c7aa MOV RDX,qword ptr [RDX + 0x10]
14818c7ae CALL 0x14190e290
14818c7b3 LEA RCX,[RSI + 0x20]
14818c7b7 MOV qword ptr [RSP + 0x58],RCX
14818c7bc MOV qword ptr [RCX],RBP
14818c7bf XOR R9D,R9D
14818c7c2 MOV R8D,dword ptr [RBX + 0x8]
14818c7c6 MOV RDX,qword ptr [RBX]
14818c7c9 CALL 0x1481415f0
14818c7ce NOP
14818c7cf LEA RCX,[RSI + 0x30]
14818c7d3 MOV qword ptr [RSP + 0x58],RCX
14818c7d8 MOV qword ptr [RCX],RBP
14818c7db XOR R9D,R9D
14818c7de MOV R8D,dword ptr [RDI + 0x8]
14818c7e2 MOV RDX,qword ptr [RDI]
14818c7e5 CALL 0x140c64610
14818c7ea NOP
14818c7eb MOVZX EAX,byte ptr [RSP + 0x70]
14818c7f0 MOV byte ptr [RSI + 0x40],AL
14818c7f3 MOVZX EAX,byte ptr [RSP + 0x78]
14818c7f8 MOV byte ptr [RSI + 0x41],AL
14818c7fb MOVZX EAX,byte ptr [RSP + 0x80]
14818c803 MOV byte ptr [RSI + 0x42],AL
14818c806 MOV RAX,qword ptr [RSP + 0x88]
14818c80e MOV qword ptr [RSI + 0x48],RAX
14818c812 MOV RAX,qword ptr [RSP + 0x90]
14818c81a MOV qword ptr [RSI + 0x50],RAX
14818c81e MOV RAX,qword ptr [RSP + 0x98]
14818c826 MOV qword ptr [RSI + 0x58],RAX
14818c82a MOV RAX,qword ptr [RSP + 0xa0]
14818c832 MOV qword ptr [RSI + 0x60],RAX
14818c836 MOV RAX,qword ptr [RSP + 0xa8]
14818c83e MOV qword ptr [RSI + 0x68],RAX
14818c842 MOV RAX,qword ptr [RSP + 0xb0]
14818c84a MOV qword ptr [RSI + 0x70],RAX
14818c84e MOV RAX,qword ptr [RSP + 0xb8]
14818c856 MOV qword ptr [RSI + 0x78],RAX
14818c85a MOV RAX,qword ptr [RSP + 0xc0]
14818c862 MOV qword ptr [RSI + 0x80],RAX
14818c869 MOV RAX,qword ptr [RSP + 0xc8]
14818c871 MOV qword ptr [RSI + 0x88],RAX
14818c878 MOV RAX,qword ptr [RSP + 0xd0]
14818c880 MOV qword ptr [RSI + 0x90],RAX
14818c887 MOV dword ptr [RSI + 0x98],EBP
14818c88d MOV EAX,dword ptr [RSP + 0xd8]
14818c894 MOV dword ptr [RSI + 0x9c],EAX
14818c89a MOV qword ptr [RSI + 0xa0],RBP
14818c8a1 MOV qword ptr [RSI + 0xa8],RBP
14818c8a8 MOV qword ptr [RSI + 0xb0],RBP
14818c8af MOV qword ptr [RSI + 0xb8],RBP
14818c8b6 MOV qword ptr [RSI + 0xc0],RBP
14818c8bd MOV qword ptr [RSI + 0xc8],RBP
14818c8c4 MOV qword ptr [RSI + 0xd0],RBP
14818c8cb MOV qword ptr [RSI + 0xd8],RBP
14818c8d2 MOV qword ptr [RSI + 0xe0],RBP
14818c8d9 MOV qword ptr [RSI + 0xe8],RBP
14818c8e0 MOV qword ptr [RSI + 0xf0],RBP
14818c8e7 MOV qword ptr [RSI + 0xf8],RBP
14818c8ee MOV qword ptr [RSI + 0x100],RBP
14818c8f5 MOV qword ptr [RSI + 0x108],RBP
14818c8fc MOV dword ptr [RSI + 0x110],EBP
14818c902 MOV RCX,qword ptr [RSI + 0x90]
14818c909 TEST RCX,RCX
14818c90c JZ 0x14818c913
14818c90e MOV EAX,dword ptr [RSI + 0x28]
14818c911 MOV dword ptr [RCX],EAX
14818c913 MOVZX EAX,byte ptr [0x14eab53c8]
14818c91a CMP AL,0x3
14818c91c JC 0x14818c93c
14818c91e MOV R8D,dword ptr [RSI + 0x28]
14818c922 LEA RDX,[0x14cf638a0]
14818c929 LEA RCX,[0x14eab53c8]
14818c930 CALL 0x140f24ba0
14818c935 MOVZX EAX,byte ptr [0x14eab53c8]
14818c93c MOVZX ECX,byte ptr [RSI + 0x40]
14818c940 TEST CL,CL
14818c942 JNZ 0x14818c94e
14818c944 CMP byte ptr [RSI + 0x41],CL
14818c947 JNZ 0x14818c94e
14818c949 CMP byte ptr [RSI + 0x42],CL
14818c94c JZ 0x14818c976
14818c94e CMP AL,0x3
14818c950 JC 0x14818c976
14818c952 MOVZX EAX,byte ptr [RSI + 0x42]
14818c956 MOVZX R9D,byte ptr [RSI + 0x41]
14818c95b MOV R8D,ECX
14818c95e MOV dword ptr [RSP + 0x20],EAX
14818c962 LEA RDX,[0x14cf63930]
14818c969 LEA RCX,[0x14eab53c8]
14818c970 CALL 0x140f24ba0
14818c975 NOP
14818c976 MOV RAX,RSI
14818c979 MOV RBX,qword ptr [RSP + 0x60]
14818c97e ADD RSP,0x30
14818c982 POP RDI
14818c983 POP RSI
14818c984 POP RBP
14818c985 RET
*/

/* 14818caa0 ParseManifestHelper */

longlong * ParseManifestHelper(longlong *param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  int iVar2;
  longlong *plVar3;
  undefined4 uVar4;
  longlong alStack_30 [3];
  
  *param_1 = 0;
  iVar2 = *(int *)(param_2 + 1);
  uVar1 = *param_2;
  *(int *)(param_1 + 1) = iVar2;
  if (iVar2 == 0) {
    *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  }
  else {
    func_0x000140ca39a0(param_1,iVar2,0);
    func_0x00014b89502e(*param_1,uVar1,(longlong)iVar2 * 2);
  }
  uVar4 = 1;
  plVar3 = (longlong *)func_0x000140d1f4a0(param_1,alStack_30,&UNK_14bcfacfc,&UNK_14bce8d10,1);
  if (param_1 != plVar3) {
    if (*param_1 != 0) {
      func_0x000140e282f0();
    }
    *param_1 = *plVar3;
    *plVar3 = 0;
    *(int *)(param_1 + 1) = (int)plVar3[1];
    *(undefined4 *)((longlong)param_1 + 0xc) = *(undefined4 *)((longlong)plVar3 + 0xc);
    plVar3[1] = 0;
  }
  if (alStack_30[0] != 0) {
    func_0x000140e282f0();
  }
  while( true ) {
    iVar2 = func_0x000140d101c0(param_1,&UNK_14bd2cf68,2,1,0,0xffffffff,uVar4);
    if (iVar2 == -1) break;
    plVar3 = (longlong *)func_0x000140d1f4a0(param_1,alStack_30,&UNK_14bd2cf68,&UNK_14bce8d10,1);
    if (param_1 != plVar3) {
      if (*param_1 != 0) {
        func_0x000140e282f0();
      }
      *param_1 = *plVar3;
      *plVar3 = 0;
      *(int *)(param_1 + 1) = (int)plVar3[1];
      *(undefined4 *)((longlong)param_1 + 0xc) = *(undefined4 *)((longlong)plVar3 + 0xc);
      plVar3[1] = 0;
    }
    if (alStack_30[0] != 0) {
      func_0x000140e282f0();
    }
  }
  plVar3 = (longlong *)func_0x000140d306c0(param_1,alStack_30);
  if (param_1 != plVar3) {
    if (*param_1 != 0) {
      func_0x000140e282f0();
    }
    *param_1 = *plVar3;
    *plVar3 = 0;
    *(int *)(param_1 + 1) = (int)plVar3[1];
    *(undefined4 *)((longlong)param_1 + 0xc) = *(undefined4 *)((longlong)plVar3 + 0xc);
    plVar3[1] = 0;
  }
  if (alStack_30[0] != 0) {
    func_0x000140e282f0();
  }
  return param_1;
}


/* Instruction evidence:
14818caa0 MOV qword ptr [RSP + 0x18],RBX
14818caa5 MOV qword ptr [RSP + 0x8],RCX
14818caaa PUSH RBP
14818caab PUSH RSI
14818caac PUSH RDI
14818caad SUB RSP,0x50
14818cab1 MOV RBX,RCX
14818cab4 XOR EBP,EBP
14818cab6 MOV dword ptr [RSP + 0x30],EBP
14818caba MOV qword ptr [RSP + 0x78],RCX
14818cabf MOV qword ptr [RCX],RBP
14818cac2 MOVSXD RDI,dword ptr [RDX + 0x8]
14818cac6 MOV RSI,qword ptr [RDX]
14818cac9 MOV dword ptr [RCX + 0x8],EDI
14818cacc TEST EDI,EDI
14818cace JNZ 0x14818cad5
14818cad0 MOV dword ptr [RCX + 0xc],EBP
14818cad3 JMP 0x14818caf1
14818cad5 XOR R8D,R8D
14818cad8 MOV EDX,EDI
14818cada CALL 0x140ca39a0
14818cadf MOV R8,RDI
14818cae2 ADD R8,R8
14818cae5 MOV RDX,RSI
14818cae8 MOV RCX,qword ptr [RBX]
14818caeb CALL 0x14b89502e
14818caf0 NOP
14818caf1 MOV dword ptr [RSP + 0x30],0x1
14818caf9 MOV dword ptr [RSP + 0x20],0x1
14818cb01 LEA R9,[0x14bce8d10]
14818cb08 LEA R8,[0x14bcfacfc]
14818cb0f LEA RDX,[RSP + 0x38]
14818cb14 MOV RCX,RBX
14818cb17 CALL 0x140d1f4a0
14818cb1c MOV RDI,RAX
14818cb1f CMP RBX,RAX
14818cb22 JZ 0x14818cb4a
14818cb24 MOV RCX,qword ptr [RBX]
14818cb27 TEST RCX,RCX
14818cb2a JZ 0x14818cb31
14818cb2c CALL 0x140e282f0
14818cb31 MOV RCX,qword ptr [RDI]
14818cb34 MOV qword ptr [RBX],RCX
14818cb37 MOV qword ptr [RDI],RBP
14818cb3a MOV EAX,dword ptr [RDI + 0x8]
14818cb3d MOV dword ptr [RBX + 0x8],EAX
14818cb40 MOV EAX,dword ptr [RDI + 0xc]
14818cb43 MOV dword ptr [RBX + 0xc],EAX
14818cb46 MOV qword ptr [RDI + 0x8],RBP
14818cb4a MOV RCX,qword ptr [RSP + 0x38]
14818cb4f TEST RCX,RCX
14818cb52 JZ 0x14818cb5a
14818cb54 CALL 0x140e282f0
14818cb59 NOP
14818cb5a NOP word ptr [RAX + RAX*0x1]
14818cb60 MOV dword ptr [RSP + 0x28],0xffffffff
14818cb68 MOV dword ptr [RSP + 0x20],EBP
14818cb6c MOV R9D,0x1
14818cb72 LEA R8D,[R9 + 0x1]
14818cb76 LEA RDX,[0x14bd2cf68]
14818cb7d MOV RCX,RBX
14818cb80 CALL 0x140d101c0
14818cb85 LEA RDX,[RSP + 0x38]
14818cb8a MOV RCX,RBX
14818cb8d CMP EAX,-0x1
14818cb90 JZ 0x14818cbf0
14818cb92 MOV dword ptr [RSP + 0x20],0x1
14818cb9a LEA R9,[0x14bce8d10]
14818cba1 LEA R8,[0x14bd2cf68]
14818cba8 CALL 0x140d1f4a0
14818cbad MOV RDI,RAX
14818cbb0 CMP RBX,RAX
14818cbb3 JZ 0x14818cbdb
14818cbb5 MOV RCX,qword ptr [RBX]
14818cbb8 TEST RCX,RCX
14818cbbb JZ 0x14818cbc2
14818cbbd CALL 0x140e282f0
14818cbc2 MOV RCX,qword ptr [RDI]
14818cbc5 MOV qword ptr [RBX],RCX
14818cbc8 MOV qword ptr [RDI],RBP
14818cbcb MOV EAX,dword ptr [RDI + 0x8]
14818cbce MOV dword ptr [RBX + 0x8],EAX
14818cbd1 MOV EAX,dword ptr [RDI + 0xc]
14818cbd4 MOV dword ptr [RBX + 0xc],EAX
14818cbd7 MOV qword ptr [RDI + 0x8],RBP
14818cbdb MOV RCX,qword ptr [RSP + 0x38]
14818cbe0 TEST RCX,RCX
14818cbe3 JZ 0x14818cbeb
14818cbe5 CALL 0x140e282f0
14818cbea NOP
14818cbeb JMP 0x14818cb60
14818cbf0 CALL 0x140d306c0
14818cbf5 MOV RDI,RAX
14818cbf8 CMP RBX,RAX
14818cbfb JZ 0x14818cc23
14818cbfd MOV RCX,qword ptr [RBX]
14818cc00 TEST RCX,RCX
14818cc03 JZ 0x14818cc0a
14818cc05 CALL 0x140e282f0
14818cc0a MOV RCX,qword ptr [RDI]
14818cc0d MOV qword ptr [RBX],RCX
14818cc10 MOV qword ptr [RDI],RBP
14818cc13 MOV EAX,dword ptr [RDI + 0x8]
14818cc16 MOV dword ptr [RBX + 0x8],EAX
14818cc19 MOV EAX,dword ptr [RDI + 0xc]
14818cc1c MOV dword ptr [RBX + 0xc],EAX
14818cc1f MOV qword ptr [RDI + 0x8],RBP
14818cc23 MOV RCX,qword ptr [RSP + 0x38]
14818cc28 TEST RCX,RCX
14818cc2b JZ 0x14818cc33
14818cc2d CALL 0x140e282f0
14818cc32 NOP
14818cc33 MOV RAX,RBX
14818cc36 MOV RBX,qword ptr [RSP + 0x80]
14818cc3e ADD RSP,0x50
14818cc42 POP RDI
14818cc43 POP RSI
14818cc44 POP RBP
14818cc45 RET
*/
