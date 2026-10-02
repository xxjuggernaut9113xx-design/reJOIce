/* 1481924d0 ?ParseManifestJson@UCHPackManager@@AEAA_NAEBVFString@@AEAUFCHPackManifest@@@Z */

undefined8
_ParseManifestJson_UCHPackManager__AEAA_NAEBVFString__AEAUFCHPackManifest___Z
          (undefined8 param_1,undefined8 param_2,longlong *param_3)

{
  int *piVar1;
  ulonglong *puVar2;
  longlong lVar3;
  code *pcVar4;
  double dVar5;
  bool bVar6;
  char cVar7;
  undefined1 uVar8;
  undefined4 uVar9;
  int iVar10;
  longlong *plVar11;
  longlong *plVar12;
  undefined8 uVar13;
  longlong *plVar14;
  longlong **pplVar15;
  ulonglong uVar16;
  undefined *puVar17;
  undefined8 *puVar18;
  undefined8 *puVar19;
  int iVar20;
  longlong lVar21;
  longlong *plVar22;
  undefined8 unaff_retaddr;
  undefined1 auStackX_20 [8];
  longlong *plStack_358;
  longlong *plStack_350;
  longlong lStack_348;
  longlong *plStack_340;
  longlong lStack_338;
  ulonglong uStack_330;
  longlong lStack_328;
  ulonglong uStack_320;
  longlong *plStack_318;
  longlong *plStack_310;
  longlong lStack_308;
  ulonglong uStack_300;
  undefined8 *puStack_2f8;
  uint uStack_2f0;
  longlong lStack_2e8;
  longlong *plStack_2e0;
  undefined *puStack_2d8;
  int iStack_2d0;
  undefined *puStack_2c8;
  int iStack_2c0;
  undefined *puStack_2b8;
  int iStack_2b0;
  undefined *puStack_2a8;
  int iStack_2a0;
  undefined *puStack_298;
  int iStack_290;
  undefined *puStack_288;
  int iStack_280;
  undefined8 uStack_278;
  longlong *plStack_270;
  longlong *plStack_268;
  longlong *plStack_260;
  longlong *plStack_258;
  int iStack_250;
  longlong alStack_248 [2];
  longlong alStack_238 [2];
  longlong alStack_228 [2];
  longlong alStack_218 [2];
  longlong alStack_208 [2];
  longlong alStack_1f8 [2];
  longlong alStack_1e8 [2];
  longlong alStack_1d8 [2];
  longlong alStack_1c8 [2];
  longlong alStack_1b8 [2];
  longlong alStack_1a8 [2];
  longlong alStack_198 [2];
  longlong alStack_188 [2];
  longlong alStack_178 [2];
  longlong alStack_168 [2];
  longlong alStack_158 [2];
  longlong alStack_148 [2];
  longlong alStack_138 [2];
  longlong alStack_128 [2];
  longlong alStack_118 [2];
  longlong alStack_108 [2];
  longlong alStack_f8 [2];
  longlong alStack_e8 [2];
  longlong alStack_d8 [2];
  longlong alStack_c8 [2];
  longlong alStack_b8 [2];
  longlong alStack_a8 [2];
  undefined8 *puStack_98;
  longlong alStack_90 [2];
  longlong alStack_80 [2];
  longlong alStack_70 [2];
  longlong alStack_60 [2];
  longlong alStack_50 [2];
  longlong alStack_40 [3];
  
  plStack_358 = (longlong *)0x0;
  plStack_350 = (longlong *)0x0;
  func_0x0001414769e0(&uStack_278);
  cVar7 = func_0x000141466950(uStack_278,&plStack_358,0);
  plVar22 = plStack_358;
  if ((cVar7 == '\0') || (plStack_358 == (longlong *)0x0)) {
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf62bc8);
    }
    uVar13 = 0;
    goto LAB_148193849;
  }
  func_0x000140cf7750(alStack_248,&UNK_14cf2b668);
  plVar11 = (longlong *)func_0x00014147a500(plVar22,alStack_b8,alStack_248);
  plVar14 = (longlong *)0x0;
  if (param_3 != plVar11) {
    if (*param_3 != 0) {
      func_0x000140e282f0();
    }
    *param_3 = *plVar11;
    *plVar11 = 0;
    *(int *)(param_3 + 1) = (int)plVar11[1];
    *(undefined4 *)((longlong)param_3 + 0xc) = *(undefined4 *)((longlong)plVar11 + 0xc);
    plVar11[1] = 0;
  }
  if (alStack_b8[0] != 0) {
    func_0x000140e282f0();
  }
  if (alStack_248[0] != 0) {
    func_0x000140e282f0();
  }
  func_0x000140cf7750(alStack_238,&UNK_14ca00b00);
  plVar12 = (longlong *)func_0x00014147a500(plVar22,alStack_a8,alStack_238);
  plVar11 = param_3 + 2;
  if (plVar11 != plVar12) {
    if (*plVar11 != 0) {
      func_0x000140e282f0();
    }
    *plVar11 = *plVar12;
    *plVar12 = 0;
    *(int *)(param_3 + 3) = (int)plVar12[1];
    *(undefined4 *)((longlong)param_3 + 0x1c) = *(undefined4 *)((longlong)plVar12 + 0xc);
    plVar12[1] = 0;
  }
  if (alStack_a8[0] != 0) {
    func_0x000140e282f0();
  }
  if (alStack_238[0] != 0) {
    func_0x000140e282f0();
  }
  func_0x000140cf7750(alStack_228,L"author");
  plVar12 = (longlong *)func_0x00014147a500(plVar22,alStack_40,alStack_228);
  plVar11 = param_3 + 4;
  if (plVar11 != plVar12) {
    if (*plVar11 != 0) {
      func_0x000140e282f0();
    }
    *plVar11 = *plVar12;
    *plVar12 = 0;
    *(int *)(param_3 + 5) = (int)plVar12[1];
    *(undefined4 *)((longlong)param_3 + 0x2c) = *(undefined4 *)((longlong)plVar12 + 0xc);
    plVar12[1] = 0;
  }
  if (alStack_40[0] != 0) {
    func_0x000140e282f0();
  }
  if (alStack_228[0] != 0) {
    func_0x000140e282f0();
  }
  func_0x000140cf7750(alStack_218,&UNK_14cb348a0);
  plVar12 = (longlong *)func_0x00014147a500(plVar22,alStack_90,alStack_218);
  plVar11 = param_3 + 6;
  if (plVar11 != plVar12) {
    if (*plVar11 != 0) {
      func_0x000140e282f0();
    }
    *plVar11 = *plVar12;
    *plVar12 = 0;
    *(int *)(param_3 + 7) = (int)plVar12[1];
    *(undefined4 *)((longlong)param_3 + 0x3c) = *(undefined4 *)((longlong)plVar12 + 0xc);
    plVar12[1] = 0;
  }
  if (alStack_90[0] != 0) {
    func_0x000140e282f0();
  }
  if (alStack_218[0] != 0) {
    func_0x000140e282f0();
  }
  func_0x000140cf7750(alStack_208,L"preview");
  plVar12 = (longlong *)func_0x00014147a500(plVar22,alStack_80,alStack_208);
  plVar11 = param_3 + 8;
  if (plVar11 != plVar12) {
    if (*plVar11 != 0) {
      func_0x000140e282f0();
    }
    *plVar11 = *plVar12;
    *plVar12 = 0;
    *(int *)(param_3 + 9) = (int)plVar12[1];
    *(undefined4 *)((longlong)param_3 + 0x4c) = *(undefined4 *)((longlong)plVar12 + 0xc);
    plVar12[1] = 0;
  }
  if (alStack_80[0] != 0) {
    func_0x000140e282f0();
  }
  if (alStack_208[0] != 0) {
    func_0x000140e282f0();
  }
  func_0x000140cf7750(&puStack_2d8,L"unlock_cost");
  if (iStack_2d0 == 0) {
    puVar17 = &UNK_14bce4e94;
    plVar11 = plVar14;
  }
  else {
    plVar11 = (longlong *)(ulonglong)(iStack_2d0 - 1);
    puVar17 = puStack_2d8;
  }
  uVar9 = func_0x000140cf4f70(plVar11,puVar17);
  iVar10 = func_0x000141467380(plVar22,uVar9,&puStack_2d8);
  if (iVar10 == -1) {
LAB_148192814:
    bVar6 = false;
  }
  else {
    lVar3 = *plVar22 + (longlong)iVar10 * 0x28;
    plVar11 = (longlong *)(lVar3 + 0x10);
    if (lVar3 == 0) {
      plVar11 = plVar14;
    }
    if ((plVar11 == (longlong *)0x0) || (*plVar11 == 0)) goto LAB_148192814;
    bVar6 = true;
  }
  if (puStack_2d8 != (undefined *)0x0) {
    func_0x000140e282f0();
  }
  if (bVar6) {
    func_0x000140cf7750(alStack_1f8,L"unlock_cost");
    dVar5 = (double)func_0x000141479c30(plVar22,alStack_1f8);
    *(int *)(param_3 + 10) = (int)dVar5;
    if (alStack_1f8[0] != 0) {
      func_0x000140e282f0();
    }
  }
  else {
    *(undefined4 *)(param_3 + 10) = 0;
  }
  func_0x000140cf7750(alStack_1e8,L"required_challenge");
  plVar12 = (longlong *)func_0x00014147a500(plVar22,alStack_70,alStack_1e8);
  plVar11 = param_3 + 0xb;
  if (plVar11 != plVar12) {
    if (*plVar11 != 0) {
      func_0x000140e282f0();
    }
    *plVar11 = *plVar12;
    *plVar12 = 0;
    *(int *)(param_3 + 0xc) = (int)plVar12[1];
    *(undefined4 *)((longlong)param_3 + 100) = *(undefined4 *)((longlong)plVar12 + 0xc);
    plVar12[1] = 0;
  }
  if (alStack_70[0] != 0) {
    func_0x000140e282f0();
  }
  if (alStack_1e8[0] != 0) {
    func_0x000140e282f0();
  }
  func_0x000140cf7750(&puStack_2c8,L"image_count");
  if (iStack_2c0 == 0) {
    puVar17 = &UNK_14bce4e94;
    plVar11 = plVar14;
  }
  else {
    plVar11 = (longlong *)(ulonglong)(iStack_2c0 - 1);
    puVar17 = puStack_2c8;
  }
  uVar9 = func_0x000140cf4f70(plVar11,puVar17);
  iVar10 = func_0x000141467380(plVar22,uVar9,&puStack_2c8);
  if (iVar10 == -1) {
LAB_148192951:
    bVar6 = false;
  }
  else {
    lVar3 = *plVar22 + (longlong)iVar10 * 0x28;
    plVar11 = (longlong *)(lVar3 + 0x10);
    if (lVar3 == 0) {
      plVar11 = plVar14;
    }
    if ((plVar11 == (longlong *)0x0) || (*plVar11 == 0)) goto LAB_148192951;
    bVar6 = true;
  }
  if (puStack_2c8 != (undefined *)0x0) {
    func_0x000140e282f0();
  }
  if (bVar6) {
    func_0x000140cf7750(alStack_1d8,L"image_count");
    dVar5 = (double)func_0x000141479c30(plVar22,alStack_1d8);
    *(int *)((longlong)param_3 + 0x124) = (int)dVar5;
    if (alStack_1d8[0] != 0) {
      func_0x000140e282f0();
    }
  }
  else {
    *(undefined4 *)((longlong)param_3 + 0x124) = 0;
  }
  func_0x000140cf7750(&puStack_2b8,L"video_count");
  if (iStack_2b0 == 0) {
    puVar17 = &UNK_14bce4e94;
    plVar11 = plVar14;
  }
  else {
    plVar11 = (longlong *)(ulonglong)(iStack_2b0 - 1);
    puVar17 = puStack_2b8;
  }
  uVar9 = func_0x000140cf4f70(plVar11,puVar17);
  iVar10 = func_0x000141467380(plVar22,uVar9,&puStack_2b8);
  if (iVar10 == -1) {
LAB_148192a14:
    bVar6 = false;
  }
  else {
    lVar3 = *plVar22 + (longlong)iVar10 * 0x28;
    plVar11 = (longlong *)(lVar3 + 0x10);
    if (lVar3 == 0) {
      plVar11 = plVar14;
    }
    if ((plVar11 == (longlong *)0x0) || (*plVar11 == 0)) goto LAB_148192a14;
    bVar6 = true;
  }
  if (puStack_2b8 != (undefined *)0x0) {
    func_0x000140e282f0();
  }
  if (bVar6) {
    func_0x000140cf7750(alStack_1c8,L"video_count");
    dVar5 = (double)func_0x000141479c30(plVar22,alStack_1c8);
    *(int *)(param_3 + 0x25) = (int)dVar5;
    if (alStack_1c8[0] != 0) {
      func_0x000140e282f0();
    }
  }
  else {
    *(undefined4 *)(param_3 + 0x25) = 0;
  }
  func_0x000140cf7750(&puStack_2a8,L"total_media");
  if (iStack_2a0 == 0) {
    puVar17 = &UNK_14bce4e94;
    plVar11 = plVar14;
  }
  else {
    plVar11 = (longlong *)(ulonglong)(iStack_2a0 - 1);
    puVar17 = puStack_2a8;
  }
  uVar9 = func_0x000140cf4f70(plVar11,puVar17);
  iVar10 = func_0x000141467380(plVar22,uVar9,&puStack_2a8);
  if (iVar10 == -1) {
LAB_148192ad7:
    bVar6 = false;
  }
  else {
    lVar3 = *plVar22 + (longlong)iVar10 * 0x28;
    plVar11 = (longlong *)(lVar3 + 0x10);
    if (lVar3 == 0) {
      plVar11 = plVar14;
    }
    if ((plVar11 == (longlong *)0x0) || (*plVar11 == 0)) goto LAB_148192ad7;
    bVar6 = true;
  }
  if (puStack_2a8 != (undefined *)0x0) {
    func_0x000140e282f0();
  }
  if (bVar6) {
    func_0x000140cf7750(alStack_1b8,L"total_media");
    dVar5 = (double)func_0x000141479c30(plVar22,alStack_1b8);
    *(int *)(param_3 + 0x24) = (int)dVar5;
    if (alStack_1b8[0] != 0) {
      func_0x000140e282f0();
    }
  }
  else {
    *(undefined4 *)(param_3 + 0x24) = 0;
  }
  func_0x000140cf7750(&puStack_298,L"patreon_exclusive");
  if (iStack_290 == 0) {
    puVar17 = &UNK_14bce4e94;
    plVar11 = plVar14;
  }
  else {
    plVar11 = (longlong *)(ulonglong)(iStack_290 - 1);
    puVar17 = puStack_298;
  }
  uVar9 = func_0x000140cf4f70(plVar11,puVar17);
  iVar10 = func_0x000141467380(plVar22,uVar9,&puStack_298);
  if (iVar10 == -1) {
LAB_148192b9a:
    bVar6 = false;
  }
  else {
    lVar3 = *plVar22 + (longlong)iVar10 * 0x28;
    plVar11 = (longlong *)(lVar3 + 0x10);
    if (lVar3 == 0) {
      plVar11 = plVar14;
    }
    if ((plVar11 == (longlong *)0x0) || (*plVar11 == 0)) goto LAB_148192b9a;
    bVar6 = true;
  }
  if (puStack_298 != (undefined *)0x0) {
    func_0x000140e282f0();
  }
  if (bVar6) {
    func_0x000140cf7750(alStack_1a8,L"patreon_exclusive");
    uVar8 = func_0x000141479080(plVar22,alStack_1a8);
    *(undefined1 *)(param_3 + 0x1b) = uVar8;
    if (alStack_1a8[0] != 0) {
      func_0x000140e282f0();
    }
  }
  else {
    *(undefined1 *)(param_3 + 0x1b) = 0;
  }
  func_0x000140cf7750(&puStack_288,L"social_links");
  if (iStack_280 == 0) {
    puVar17 = &UNK_14bce4e94;
    plVar11 = plVar14;
  }
  else {
    plVar11 = (longlong *)(ulonglong)(iStack_280 - 1);
    puVar17 = puStack_288;
  }
  uVar9 = func_0x000140cf4f70(plVar11,puVar17);
  iVar10 = func_0x000141467380(plVar22,uVar9,&puStack_288);
  if (iVar10 == -1) {
LAB_148192c61:
    bVar6 = false;
  }
  else {
    lVar3 = *plVar22 + (longlong)iVar10 * 0x28;
    plVar11 = (longlong *)(lVar3 + 0x10);
    if (lVar3 == 0) {
      plVar11 = plVar14;
    }
    if (((plVar11 == (longlong *)0x0) || (*plVar11 == 0)) || (*(int *)(*plVar11 + 8) != 6))
    goto LAB_148192c61;
    bVar6 = true;
  }
  if (puStack_288 != (undefined *)0x0) {
    func_0x000140e282f0();
  }
  if (bVar6) {
    func_0x000140cf7750(alStack_198,L"social_links");
    plVar11 = (longlong *)func_0x000141479cf0(plVar22,alStack_198);
    lVar3 = *plVar11;
    plStack_340 = (longlong *)plVar11[1];
    if (plStack_340 != (longlong *)0x0) {
      LOCK();
      *(int *)(plStack_340 + 1) = (int)plStack_340[1] + 1;
      UNLOCK();
      plVar22 = plStack_358;
    }
    lStack_348 = lVar3;
    if (alStack_198[0] != 0) {
      func_0x000140e282f0();
    }
    if ((lVar3 == 0) &&
       (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,&UNK_14bce4e94
                                   ), cVar7 != '\0')) {
      pcVar4 = (code *)swi(3);
      uVar13 = (*pcVar4)();
      return uVar13;
    }
    func_0x000140cf7750(alStack_188,L"onlyfans");
    func_0x000141484320(lVar3,alStack_188,param_3 + 0xf);
    if (alStack_188[0] != 0) {
      func_0x000140e282f0();
    }
    if ((lVar3 == 0) &&
       (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,&UNK_14bce4e94
                                   ), cVar7 != '\0')) {
      pcVar4 = (code *)swi(3);
      uVar13 = (*pcVar4)();
      return uVar13;
    }
    func_0x000140cf7750(alStack_178,L"fansly");
    func_0x000141484320(lVar3,alStack_178,param_3 + 0x11);
    if (alStack_178[0] != 0) {
      func_0x000140e282f0();
    }
    if ((lVar3 == 0) &&
       (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,&UNK_14bce4e94
                                   ), cVar7 != '\0')) {
      pcVar4 = (code *)swi(3);
      uVar13 = (*pcVar4)();
      return uVar13;
    }
    func_0x000140cf7750(alStack_168,L"twitter");
    func_0x000141484320(lVar3,alStack_168,param_3 + 0x13);
    if (alStack_168[0] != 0) {
      func_0x000140e282f0();
    }
    if ((lVar3 == 0) &&
       (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,&UNK_14bce4e94
                                   ), cVar7 != '\0')) {
      pcVar4 = (code *)swi(3);
      uVar13 = (*pcVar4)();
      return uVar13;
    }
    func_0x000140cf7750(alStack_158,L"linktree");
    func_0x000141484320(lVar3,alStack_158,param_3 + 0x15);
    if (alStack_158[0] != 0) {
      func_0x000140e282f0();
    }
    if ((lVar3 == 0) &&
       (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,&UNK_14bce4e94
                                   ), cVar7 != '\0')) {
      pcVar4 = (code *)swi(3);
      uVar13 = (*pcVar4)();
      return uVar13;
    }
    func_0x000140cf7750(alStack_148,L"manyvids");
    func_0x000141484320(lVar3,alStack_148,param_3 + 0x17);
    if (alStack_148[0] != 0) {
      func_0x000140e282f0();
    }
    if ((lVar3 == 0) &&
       (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,&UNK_14bce4e94
                                   ), cVar7 != '\0')) {
      pcVar4 = (code *)swi(3);
      uVar13 = (*pcVar4)();
      return uVar13;
    }
    func_0x000140cf7750(alStack_138,L"redgifs");
    func_0x000141484320(lVar3,alStack_138,param_3 + 0x19);
    if (alStack_138[0] != 0) {
      func_0x000140e282f0();
    }
    if ((lVar3 == 0) &&
       (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,&UNK_14bce4e94
                                   ), cVar7 != '\0')) {
      pcVar4 = (code *)swi(3);
      uVar13 = (*pcVar4)();
      return uVar13;
    }
    func_0x000140cf7750(alStack_128,L"discord");
    func_0x000141484320(lVar3,alStack_128,param_3 + 0x1c);
    if (alStack_128[0] != 0) {
      func_0x000140e282f0();
    }
    if ((lVar3 == 0) &&
       (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,&UNK_14bce4e94
                                   ), cVar7 != '\0')) {
      pcVar4 = (code *)swi(3);
      uVar13 = (*pcVar4)();
      return uVar13;
    }
    func_0x000140cf7750(alStack_118,L"patreon");
    func_0x000141484320(lVar3,alStack_118,param_3 + 0x1e);
    if (alStack_118[0] != 0) {
      func_0x000140e282f0();
    }
    if ((lVar3 == 0) &&
       (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,&UNK_14bce4e94
                                   ), cVar7 != '\0')) {
      pcVar4 = (code *)swi(3);
      uVar13 = (*pcVar4)();
      return uVar13;
    }
    func_0x000140cf7750(alStack_108,L"subscribestar");
    func_0x000141484320(lVar3,alStack_108,param_3 + 0x20);
    if (alStack_108[0] != 0) {
      func_0x000140e282f0();
    }
    if ((lVar3 == 0) &&
       (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,&UNK_14bce4e94
                                   ), cVar7 != '\0')) {
      pcVar4 = (code *)swi(3);
      uVar13 = (*pcVar4)();
      return uVar13;
    }
    func_0x000140cf7750(alStack_c8,L"kofi");
    func_0x000141484320(lVar3,alStack_c8,param_3 + 0x22);
    if (alStack_c8[0] != 0) {
      func_0x000140e282f0();
    }
    plVar11 = plStack_340;
    if (plStack_340 != (longlong *)0x0) {
      LOCK();
      plVar22 = plStack_340 + 1;
      lVar3 = *plVar22;
      *(int *)plVar22 = (int)*plVar22 + -1;
      UNLOCK();
      plVar22 = plStack_358;
      if ((int)lVar3 == 1) {
        (**(code **)*plStack_340)(plStack_340);
        LOCK();
        piVar1 = (int *)((longlong)plVar11 + 0xc);
        iVar10 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        plVar22 = plStack_358;
        if (iVar10 == 1) {
          (**(code **)(*plStack_340 + 8))(plStack_340,1);
          plVar22 = plStack_358;
        }
      }
    }
  }
  puVar2 = (ulonglong *)(param_3 + 0xd);
  plVar11 = (longlong *)*puVar2;
  for (iVar10 = (int)param_3[0xe]; iVar10 != 0; iVar10 = iVar10 + -1) {
    if (plVar11[6] != 0) {
      func_0x000140e282f0();
    }
    plVar14 = (longlong *)plVar11[4];
    for (iVar20 = (int)plVar11[5]; iVar20 != 0; iVar20 = iVar20 + -1) {
      if (*plVar14 != 0) {
        func_0x000140e282f0();
      }
      plVar14 = plVar14 + 2;
    }
    if (plVar11[4] != 0) {
      func_0x000140e282f0();
    }
    if (plVar11[2] != 0) {
      func_0x000140e282f0();
    }
    if (*plVar11 != 0) {
      func_0x000140e282f0();
    }
    plVar11 = plVar11 + 8;
  }
  *(undefined4 *)(param_3 + 0xe) = 0;
  if (*(int *)((longlong)param_3 + 0x74) != 0) {
    func_0x000148193a50(puVar2,0);
  }
  if ((plVar22 == (longlong *)0x0) &&
     (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,&UNK_14bce4e94),
     cVar7 != '\0')) {
    pcVar4 = (code *)swi(3);
    uVar13 = (*pcVar4)();
    return uVar13;
  }
  func_0x000140cf7750(alStack_f8,L"media");
  cVar7 = func_0x000141482590(plVar22,alStack_f8,&plStack_268);
  if (alStack_f8[0] != 0) {
    func_0x000140e282f0();
  }
  if (cVar7 != '\0') {
    plStack_260 = plStack_268;
    plVar22 = (longlong *)*plStack_268;
    uStack_2f0 = *(uint *)(plStack_268 + 1);
    uVar16 = (ulonglong)(int)uStack_2f0;
    plVar11 = plVar22 + uVar16 * 2;
    while( true ) {
      if ((int)plStack_260[1] != (int)uVar16) {
        auStackX_20[0] = 0;
        cVar7 = func_0x00014baf0070(auStackX_20);
        if (cVar7 != '\0') {
          pcVar4 = (code *)swi(3);
          uVar13 = (*pcVar4)();
          return uVar13;
        }
      }
      if (plVar22 == plVar11) break;
      if ((*plVar22 == 0) &&
         (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,
                                      &UNK_14bce4e94), cVar7 != '\0')) {
        pcVar4 = (code *)swi(3);
        uVar13 = (*pcVar4)();
        return uVar13;
      }
      if (*(int *)(*plVar22 + 8) == 6) {
        if ((*plVar22 == 0) &&
           (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,
                                        &UNK_14bce4e94), cVar7 != '\0')) {
          pcVar4 = (code *)swi(3);
          uVar13 = (*pcVar4)();
          return uVar13;
        }
        plVar14 = (longlong *)(*(code *)**(undefined8 **)*plVar22)();
        lVar3 = *plVar14;
        plStack_2e0 = (longlong *)plVar14[1];
        if (plStack_2e0 != (longlong *)0x0) {
          LOCK();
          *(int *)(plStack_2e0 + 1) = (int)plStack_2e0[1] + 1;
          UNLOCK();
        }
        lStack_338 = 0;
        uStack_330 = 0;
        lStack_328 = 0;
        uStack_320 = 0;
        plStack_318 = (longlong *)0x0;
        plStack_310 = (longlong *)0x0;
        lStack_308 = 0;
        uStack_300 = 0;
        lStack_2e8 = lVar3;
        if ((lVar3 == 0) &&
           (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,
                                        &UNK_14bce4e94), cVar7 != '\0')) {
          pcVar4 = (code *)swi(3);
          uVar13 = (*pcVar4)();
          return uVar13;
        }
        func_0x000140cf7750(alStack_e8,&UNK_14be179c8);
        plVar14 = (longlong *)func_0x00014147a500(lVar3,alStack_60,alStack_e8);
        if (&lStack_338 != plVar14) {
          if (lStack_338 != 0) {
            func_0x000140e282f0();
          }
          lStack_338 = *plVar14;
          *plVar14 = 0;
          uStack_330 = plVar14[1];
          plVar14[1] = 0;
        }
        if (alStack_60[0] != 0) {
          func_0x000140e282f0();
        }
        if (alStack_e8[0] != 0) {
          func_0x000140e282f0();
        }
        if ((lVar3 == 0) &&
           (cVar7 = func_0x000140f8dfd0(&UNK_14bce8e80,&UNK_14cf28150,0x473,unaff_retaddr,
                                        &UNK_14bce4e94), cVar7 != '\0')) {
          pcVar4 = (code *)swi(3);
          uVar13 = (*pcVar4)();
          return uVar13;
        }
        func_0x000140cf7750(alStack_d8,&UNK_14cf2ac78);
        plVar14 = (longlong *)func_0x00014147a500(lVar3,alStack_50,alStack_d8);
        if (&lStack_328 != plVar14) {
          if (lStack_328 != 0) {
            func_0x000140e282f0();
          }
          lStack_328 = *plVar14;
          *plVar14 = 0;
          uStack_320 = plVar14[1];
          plVar14[1] = 0;
        }
        if (alStack_50[0] != 0) {
          func_0x000140e282f0();
        }
        if (alStack_d8[0] != 0) {
          func_0x000140e282f0();
        }
        pplVar15 = (longlong **)func_0x00014818dbb0(&plStack_258,&lStack_338);
        plVar14 = plStack_258;
        iVar10 = iStack_250;
        if (&plStack_318 != pplVar15) {
          plVar14 = plStack_318;
          for (iVar10 = (int)plStack_310; iVar10 != 0; iVar10 = iVar10 + -1) {
            if (*plVar14 != 0) {
              func_0x000140e282f0();
            }
            plVar14 = plVar14 + 2;
          }
          if (plStack_318 != (longlong *)0x0) {
            func_0x000140e282f0(plStack_318);
          }
          plStack_318 = *pplVar15;
          *pplVar15 = (longlong *)0x0;
          plStack_310 = pplVar15[1];
          pplVar15[1] = (longlong *)0x0;
          plVar14 = plStack_258;
          iVar10 = iStack_250;
        }
        for (; iVar10 != 0; iVar10 = iVar10 + -1) {
          if (*plVar14 != 0) {
            func_0x000140e282f0();
          }
          plVar14 = plVar14 + 2;
        }
        if (plStack_258 != (longlong *)0x0) {
          func_0x000140e282f0(plStack_258);
        }
        plVar14 = (longlong *)*puVar2;
        if (((plVar14 <= &lStack_338) &&
            (&lStack_338 < plVar14 + (longlong)*(int *)((longlong)param_3 + 0x74) * 8)) &&
           (cVar7 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                        &UNK_14bce6d80,&lStack_338,plVar14,
                                        (longlong)*(int *)((longlong)param_3 + 0x74),
                                        (longlong)(int)param_3[0xe],0x40), cVar7 != '\0')) {
          pcVar4 = (code *)swi(3);
          uVar13 = (*pcVar4)();
          return uVar13;
        }
        iVar10 = (int)param_3[0xe];
        *(uint *)(param_3 + 0xe) = iVar10 + 1U;
        if (*(uint *)((longlong)param_3 + 0x74) < iVar10 + 1U) {
          func_0x0001481939b0(puVar2,iVar10);
        }
        lVar3 = lStack_338;
        puVar18 = (undefined8 *)((longlong)iVar10 * 0x40 + *puVar2);
        *puVar18 = 0;
        lVar21 = (longlong)(int)uStack_330;
        *(int *)(puVar18 + 1) = (int)uStack_330;
        puStack_98 = puVar18;
        if ((int)uStack_330 == 0) {
          *(undefined4 *)((longlong)puVar18 + 0xc) = 0;
        }
        else {
          puStack_2f8 = puVar18;
          func_0x000140ca39a0(puVar18,uStack_330 & 0xffffffff,0);
          func_0x00014b89502e(*puVar18,lVar3,lVar21 * 2);
        }
        lVar3 = lStack_328;
        puVar19 = puVar18 + 2;
        *puVar19 = 0;
        lVar21 = (longlong)(int)uStack_320;
        *(int *)(puVar18 + 3) = (int)uStack_320;
        if ((int)uStack_320 == 0) {
          *(undefined4 *)((longlong)puVar18 + 0x1c) = 0;
        }
        else {
          puStack_2f8 = puVar19;
          func_0x000140ca39a0(puVar19,uStack_320 & 0xffffffff,0);
          func_0x00014b89502e(*puVar19,lVar3,lVar21 * 2);
        }
        puStack_2f8 = puVar18 + 4;
        *puStack_2f8 = 0;
        func_0x000140c64610(puStack_2f8,plStack_318,(ulonglong)plStack_310 & 0xffffffff,0);
        lVar3 = lStack_308;
        puVar19 = puVar18 + 6;
        *puVar19 = 0;
        lVar21 = (longlong)(int)uStack_300;
        *(int *)(puVar18 + 7) = (int)uStack_300;
        puStack_2f8 = puVar19;
        if ((int)uStack_300 == 0) {
          *(undefined4 *)((longlong)puVar18 + 0x3c) = 0;
        }
        else {
          func_0x000140ca39a0(puVar19,uStack_300 & 0xffffffff,0);
          func_0x00014b89502e(*puVar19,lVar3,lVar21 * 2);
        }
        if (lStack_308 != 0) {
          func_0x000140e282f0();
        }
        plVar14 = plStack_318;
        for (iVar10 = (int)plStack_310; iVar10 != 0; iVar10 = iVar10 + -1) {
          if (*plVar14 != 0) {
            func_0x000140e282f0();
          }
          plVar14 = plVar14 + 2;
        }
        if (plStack_318 != (longlong *)0x0) {
          func_0x000140e282f0(plStack_318);
        }
        if (lStack_328 != 0) {
          func_0x000140e282f0();
        }
        if (lStack_338 != 0) {
          func_0x000140e282f0();
        }
        plVar14 = plStack_2e0;
        if (plStack_2e0 != (longlong *)0x0) {
          LOCK();
          plVar12 = plStack_2e0 + 1;
          lVar3 = *plVar12;
          *(int *)plVar12 = (int)*plVar12 + -1;
          UNLOCK();
          if ((int)lVar3 == 1) {
            (**(code **)*plStack_2e0)(plStack_2e0);
            LOCK();
            piVar1 = (int *)((longlong)plVar14 + 0xc);
            iVar10 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar10 == 1) {
              (**(code **)(*plStack_2e0 + 8))(plStack_2e0,1);
            }
          }
        }
      }
      plVar22 = plVar22 + 2;
      uVar16 = (ulonglong)uStack_2f0;
    }
  }
  uVar13 = 1;
LAB_148193849:
  plVar22 = plStack_270;
  if (plStack_270 != (longlong *)0x0) {
    LOCK();
    plVar11 = plStack_270 + 1;
    lVar3 = *plVar11;
    *(int *)plVar11 = (int)*plVar11 + -1;
    UNLOCK();
    if ((int)lVar3 == 1) {
      (**(code **)*plStack_270)(plStack_270);
      LOCK();
      piVar1 = (int *)((longlong)plVar22 + 0xc);
      iVar10 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar10 == 1) {
        (**(code **)(*plStack_270 + 8))(plStack_270,1);
      }
    }
  }
  plVar22 = plStack_350;
  if (plStack_350 != (longlong *)0x0) {
    LOCK();
    plVar11 = plStack_350 + 1;
    lVar3 = *plVar11;
    *(int *)plVar11 = (int)*plVar11 + -1;
    UNLOCK();
    if ((int)lVar3 == 1) {
      (**(code **)*plStack_350)(plStack_350);
      LOCK();
      piVar1 = (int *)((longlong)plVar22 + 0xc);
      iVar10 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar10 == 1) {
        (**(code **)(*plStack_350 + 8))(plStack_350,1);
      }
    }
  }
  return uVar13;
}




/* Resolved referenced strings:
{
  "14be179c8": "file",
  "14bce8e80": "IsValid()",
  "14cf27ac0": "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Array.h",
  "14cb348a0": "description",
  "14ca00b00": "name",
  "14bce6eb8": "Addr < GetData() || Addr >= (GetData() + ArrayMax)",
  "14bce6d80": "Attempting to use a container element (%p) which already comes from the container being modified (%p, ArrayMax: %lld, ArrayNum: %lld, SizeofElement: %d)!",
  "14cf28150": "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Templates\\SharedPointer.h",
  "14cf2b668": "version",
  "14cf2ac78": "type"
}
*/
