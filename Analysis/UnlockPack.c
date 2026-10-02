/* 1481d6810 ?UnlockPack@UCHPackStoreController@@QEAA_NAEBVFString@@@Z */

ulonglong _UnlockPack_UCHPackStoreController__QEAA_NAEBVFString___Z
                    (longlong param_1,longlong *param_2)

{
  longlong *plVar1;
  code *pcVar2;
  longlong lVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  ulonglong uVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  undefined *puVar12;
  undefined *puVar13;
  longlong lVar14;
  undefined8 *puVar15;
  longlong lVar16;
  undefined8 *puVar17;
  undefined *puVar18;
  longlong *plVar19;
  wchar_t *pwVar20;
  undefined *puVar21;
  wchar_t *pwVar22;
  undefined *puVar23;
  longlong *plVar24;
  ulonglong uVar25;
  longlong *plVar26;
  bool bVar27;
  undefined8 unaff_retaddr;
  undefined1 auStackX_18 [8];
  undefined1 auStackX_20 [8];
  undefined8 in_stack_fffffffffffffe18;
  undefined4 uVar28;
  undefined *in_stack_fffffffffffffe20;
  undefined8 in_stack_fffffffffffffe28;
  undefined1 uStack_1b8;
  undefined1 auStack_1b7 [7];
  longlong lStack_1b0;
  longlong *plStack_1a8;
  longlong lStack_1a0;
  longlong lStack_198;
  longlong lStack_190;
  ulonglong uStack_188;
  undefined4 uStack_180;
  undefined2 uStack_17c;
  undefined1 uStack_17a;
  undefined8 *puStack_178;
  longlong lStack_170;
  ulonglong uStack_168;
  undefined4 uStack_160;
  undefined2 uStack_15c;
  undefined1 uStack_15a;
  longlong lStack_158;
  longlong lStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined *puStack_118;
  int iStack_110;
  undefined *puStack_108;
  int iStack_100;
  undefined *puStack_f8;
  int iStack_f0;
  undefined *puStack_e8;
  int iStack_e0;
  undefined *puStack_d8;
  int iStack_d0;
  undefined *puStack_c8;
  int iStack_c0;
  undefined *puStack_b8;
  int iStack_b0;
  undefined *puStack_a8;
  int iStack_a0;
  undefined8 *puStack_98;
  int iStack_90;
  longlong lStack_88;
  longlong lStack_80;
  longlong lStack_78;
  longlong lStack_70;
  longlong lStack_68;
  longlong lStack_60;
  longlong lStack_58;
  longlong lStack_50;
  longlong lStack_48;
  longlong lStack_40;
  
  plVar24 = param_2 + 1;
  puVar23 = &UNK_14bce4e94;
  plStack_1a8 = plVar24;
  if (2 < DAT_14eab53c8) {
    if ((int)*plVar24 == 0) {
      puVar21 = &UNK_14bce4e94;
    }
    else {
      puVar21 = (undefined *)*param_2;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7ca68,puVar21);
  }
  uVar8 = 0;
  if (*(longlong *)(param_1 + 0x38) == 0) {
    if (1 < DAT_14eab53c8) {
      uVar8 = func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7cae0);
      return uVar8 & 0xffffffffffffff00;
    }
LAB_1481d68df:
    return uVar8 & 0xffffffffffffff00;
  }
  uVar8 = _IsPackUnlocked_UCHPackStoreController__QEBA_NAEBVFString___Z(param_1,param_2);
  if ((char)uVar8 != '\0') {
    if (2 < DAT_14eab53c8) {
      if ((int)*plVar24 != 0) {
        puVar23 = (undefined *)*param_2;
      }
      uVar8 = func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7cb58,puVar23);
    }
    goto LAB_1481d68df;
  }
  _GetAllPackInfos_UCHPackStoreController__QEAA_AV__TArray_UFCHPackInfo__V__TSizedDefaultAllocator__0CA_____XZ
            (param_1,&puStack_98);
  for (puVar15 = puStack_98; uVar28 = (undefined4)((ulonglong)in_stack_fffffffffffffe18 >> 0x20),
      puVar15 != puStack_98 + (longlong)iStack_90 * 0x22; puVar15 = puVar15 + 0x22) {
    iVar5 = *(int *)(puVar15 + 1);
    if (iVar5 == (int)*plVar24) {
      if (1 < iVar5) {
        iVar5 = func_0x000140d80770(*puVar15,*param_2);
        bVar27 = iVar5 == 0;
        goto LAB_1481d6931;
      }
LAB_1481d6941:
      iVar5 = *(int *)(puVar15 + 10);
      if (2 < DAT_14eab53c8) {
        uVar6 = _GetUnlockPoints_UCHPackStoreController__QEBAHXZ(param_1);
        if ((int)*plVar24 == 0) {
          puVar21 = &UNK_14bce4e94;
        }
        else {
          puVar21 = (undefined *)*param_2;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7cc60,puVar21,iVar5,CONCAT44(uVar28,uVar6));
      }
      iVar7 = _GetUnlockPoints_UCHPackStoreController__QEBAHXZ(param_1);
      if (iVar7 < iVar5) {
        if (2 < DAT_14eab53c8) {
          if ((int)*plVar24 != 0) {
            puVar23 = (undefined *)*param_2;
          }
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7cd08,puVar23,iVar5);
        }
        goto LAB_1481d758c;
      }
      _AddUnlockPoints_UCHPackStoreController__QEAAXH_Z(param_1,-iVar5);
      lVar14 = *(longlong *)(*(longlong *)(param_1 + 0x38) + 0x10);
      func_0x0001411a7b80(&lStack_158,L"UnlockedPacks",0);
      lStack_88 = lStack_158;
      lStack_80 = lStack_158;
      uVar11 = 0;
      uVar8 = uVar11;
      if (lStack_158 == 0) goto LAB_1481d6a77;
      if (lVar14 == 0) {
        uStack_168 = 0;
      }
      else {
        uStack_168 = *(ulonglong *)(lVar14 + 0x50);
      }
      uStack_160 = 0xffffffff;
      uStack_15c = 0x101;
      uStack_15a = 0;
      lStack_170 = lVar14;
      func_0x0001469a93b0(&lStack_170);
      if (uStack_168 == 0) goto LAB_1481d6a77;
      lStack_78 = lStack_158;
      goto LAB_1481d6a3e;
    }
    bVar27 = iVar5 + (int)*plVar24 == 1;
LAB_1481d6931:
    uVar28 = (undefined4)((ulonglong)in_stack_fffffffffffffe18 >> 0x20);
    if (bVar27) goto LAB_1481d6941;
  }
  if (1 < DAT_14eab53c8) {
    if ((int)*plVar24 != 0) {
      puVar23 = (undefined *)*param_2;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7cbe0,puVar23);
  }
  goto LAB_1481d758c;
  while( true ) {
    uStack_168 = *(ulonglong *)(uStack_168 + 0x18);
    func_0x0001469a93b0(&lStack_170);
    uVar8 = uVar11;
    if (uStack_168 == 0) break;
LAB_1481d6a3e:
    lStack_1a0 = *(longlong *)(uStack_168 + 0x20);
    lStack_40 = lStack_158;
    uVar8 = uStack_168;
    lStack_70 = lStack_1a0;
    if (lStack_1a0 == lStack_158) break;
  }
LAB_1481d6a77:
  lVar14 = *(longlong *)(*(longlong *)(param_1 + 0x38) + 0x10);
  func_0x0001411a7b80(&lStack_150,L"EnabledPacks",0);
  uVar28 = (undefined4)((ulonglong)in_stack_fffffffffffffe28 >> 0x20);
  lStack_50 = lStack_150;
  lStack_48 = lStack_150;
  uVar25 = uVar11;
  if (lStack_150 != 0) {
    if (lVar14 == 0) {
      uStack_188 = 0;
    }
    else {
      uStack_188 = *(ulonglong *)(lVar14 + 0x50);
    }
    uStack_180 = 0xffffffff;
    uStack_17c = 0x101;
    uStack_17a = 0;
    lStack_190 = lVar14;
    func_0x0001469a93b0(&lStack_190);
    uVar28 = (undefined4)((ulonglong)in_stack_fffffffffffffe28 >> 0x20);
    if (uStack_188 != 0) {
      lStack_68 = lStack_150;
      do {
        uVar28 = (undefined4)((ulonglong)in_stack_fffffffffffffe28 >> 0x20);
        lStack_198 = *(longlong *)(uStack_188 + 0x20);
        lStack_58 = lStack_150;
        uVar25 = uStack_188;
        lStack_60 = lStack_198;
        if (lStack_198 == lStack_150) break;
        uStack_188 = *(ulonglong *)(uStack_188 + 0x18);
        func_0x0001469a93b0(&lStack_190);
        uVar28 = (undefined4)((ulonglong)in_stack_fffffffffffffe28 >> 0x20);
        uVar25 = uVar11;
      } while (uStack_188 != 0);
    }
  }
  if (2 < DAT_14eab53c8) {
    pwVar20 = L"NULL";
    pwVar22 = L"NULL";
    if (uVar25 != 0) {
      pwVar22 = L"VALID";
    }
    if (uVar8 != 0) {
      pwVar20 = L"VALID";
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7cda8,pwVar20,pwVar22);
  }
  if ((uVar8 == 0) || (uVar25 == 0)) {
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7ce28);
    }
  }
  else {
    lVar14 = *(longlong *)(param_1 + 0x38);
    lStack_1b0 = lVar14;
    if (*(int *)(uVar8 + 0x30) < 1) {
      uVar9 = CONCAT44(uVar28,*(int *)(uVar8 + 0x30));
      in_stack_fffffffffffffe20 =
           (undefined *)((ulonglong)in_stack_fffffffffffffe20 & 0xffffffff00000000);
      cVar4 = func_0x000140f8dfd0(&UNK_14be5bfd0,
                                  "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                  ,0x26f,unaff_retaddr,&UNK_14be5bf60,in_stack_fffffffffffffe20,
                                  uVar9);
      uVar28 = (undefined4)((ulonglong)uVar9 >> 0x20);
      if (cVar4 != '\0') {
        pcVar2 = (code *)swi(3);
        uVar8 = (*pcVar2)();
        return uVar8;
      }
    }
    if ((lVar14 == 0) &&
       (cVar4 = func_0x000140f8dfd0(&UNK_14be5c000,
                                    "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                    ,0x270,unaff_retaddr,&UNK_14bce4e94), cVar4 != '\0')) {
      pcVar2 = (code *)swi(3);
      uVar8 = (*pcVar2)();
      return uVar8;
    }
    cVar4 = func_0x0001418b7d40(lVar14);
    if ((cVar4 == '\0') &&
       (cVar4 = func_0x000140f8dfd0(&UNK_14be86ec0,
                                    "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                    ,0x274,unaff_retaddr,&UNK_14bce4e94), cVar4 != '\0')) {
      pcVar2 = (code *)swi(3);
      uVar8 = (*pcVar2)();
      return uVar8;
    }
    if ((*(longlong *)(lVar14 + 0x10) == 0) &&
       (cVar4 = func_0x000140f8dfd0(&UNK_14be86ef0,
                                    "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                    ,0x275,unaff_retaddr,&UNK_14bce4e94), cVar4 != '\0')) {
      pcVar2 = (code *)swi(3);
      uVar8 = (*pcVar2)();
      return uVar8;
    }
    uVar9 = func_0x0001416099b0();
    cVar4 = func_0x00014169bf20(uVar8 + 0x10,uVar9);
    if (((cVar4 == '\0') || ((*(ulonglong *)(uVar8 + 0x10) & 0xfffffffffffffffe) == 0)) &&
       (cVar4 = func_0x000140f8dfd0(&UNK_14be86f20,
                                    "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                    ,0x276,unaff_retaddr,&UNK_14bce4e94), cVar4 != '\0')) {
      pcVar2 = (code *)swi(3);
      uVar8 = (*pcVar2)();
      return uVar8;
    }
    uVar9 = func_0x0001416099b0();
    cVar4 = func_0x00014169bf20(uVar8 + 0x10,uVar9);
    uVar10 = uVar11;
    if (cVar4 != '\0') {
      uVar10 = *(ulonglong *)(uVar8 + 0x10) & 0xfffffffffffffffe;
    }
    if ((*(int *)(*(longlong *)(lVar14 + 0x10) + 0x38) < *(int *)(uVar10 + 0x38)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)(lVar14 + 0x10) + 0x30) + (longlong)*(int *)(uVar10 + 0x38) * 8
         ) != uVar10 + 0x30)) {
      uVar9 = func_0x0001416099b0();
      cVar4 = func_0x00014169bf20(uVar8 + 0x10,uVar9);
      if (cVar4 != '\0') {
        uVar11 = *(ulonglong *)(uVar8 + 0x10) & 0xfffffffffffffffe;
      }
      uStack_148 = *(undefined8 *)(uVar11 + 0x18);
      func_0x0001411de0e0(&uStack_148,&puStack_e8);
      puVar21 = &UNK_14bce4e94;
      if (iStack_e0 != 0) {
        puVar21 = puStack_e8;
      }
      func_0x0001411de0e0(uVar8 + 0x20,&puStack_f8);
      puVar18 = &UNK_14bce4e94;
      if (iStack_f0 != 0) {
        puVar18 = puStack_f8;
      }
      uStack_140 = *(undefined8 *)(*(longlong *)(lStack_1b0 + 0x10) + 0x18);
      func_0x0001411de0e0(&uStack_140,&puStack_108);
      puVar13 = &UNK_14bce4e94;
      if (iStack_100 != 0) {
        puVar13 = puStack_108;
      }
      uStack_138 = *(undefined8 *)(lStack_1b0 + 0x18);
      func_0x0001411de0e0(&uStack_138,&puStack_118);
      in_stack_fffffffffffffe20 = &UNK_14bce4e94;
      if (iStack_110 != 0) {
        in_stack_fffffffffffffe20 = puStack_118;
      }
      cVar4 = func_0x000140f8dfd0(&UNK_14be86fc8,
                                  "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                  ,0x27d,unaff_retaddr,&UNK_14be86f40,in_stack_fffffffffffffe20,
                                  puVar13,puVar18,puVar21);
      uVar28 = (undefined4)((ulonglong)puVar13 >> 0x20);
      if (puStack_118 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      if (puStack_108 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      if (puStack_f8 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      if (puStack_e8 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      if (cVar4 != '\0') {
        pcVar2 = (code *)swi(3);
        uVar8 = (*pcVar2)();
        return uVar8;
      }
    }
    plVar24 = (longlong *)(*(int *)(uVar8 + 0x44) + lStack_1b0);
    lVar14 = *(longlong *)(param_1 + 0x38);
    lStack_1b0 = lVar14;
    if ((*(int *)(uVar25 + 0x30) < 1) &&
       (cVar4 = func_0x000140f8dfd0(&UNK_14be5bfd0,
                                    "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                    ,0x26f,unaff_retaddr,&UNK_14be5bf60,
                                    (ulonglong)in_stack_fffffffffffffe20 & 0xffffffff00000000,
                                    CONCAT44(uVar28,*(int *)(uVar25 + 0x30))), cVar4 != '\0')) {
      pcVar2 = (code *)swi(3);
      uVar8 = (*pcVar2)();
      return uVar8;
    }
    if ((lVar14 == 0) &&
       (cVar4 = func_0x000140f8dfd0(&UNK_14be5c000,
                                    "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                    ,0x270,unaff_retaddr,&UNK_14bce4e94), cVar4 != '\0')) {
      pcVar2 = (code *)swi(3);
      uVar8 = (*pcVar2)();
      return uVar8;
    }
    cVar4 = func_0x0001418b7d40(lVar14);
    if ((cVar4 == '\0') &&
       (cVar4 = func_0x000140f8dfd0(&UNK_14be86ec0,
                                    "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                    ,0x274,unaff_retaddr,&UNK_14bce4e94), cVar4 != '\0')) {
      pcVar2 = (code *)swi(3);
      uVar8 = (*pcVar2)();
      return uVar8;
    }
    if ((*(longlong *)(lVar14 + 0x10) == 0) &&
       (cVar4 = func_0x000140f8dfd0(&UNK_14be86ef0,
                                    "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                    ,0x275,unaff_retaddr,&UNK_14bce4e94), cVar4 != '\0')) {
      pcVar2 = (code *)swi(3);
      uVar8 = (*pcVar2)();
      return uVar8;
    }
    uVar9 = func_0x0001416099b0();
    cVar4 = func_0x00014169bf20(uVar25 + 0x10,uVar9);
    if (((cVar4 == '\0') || ((*(ulonglong *)(uVar25 + 0x10) & 0xfffffffffffffffe) == 0)) &&
       (cVar4 = func_0x000140f8dfd0(&UNK_14be86f20,
                                    "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                    ,0x276,unaff_retaddr,&UNK_14bce4e94), cVar4 != '\0')) {
      pcVar2 = (code *)swi(3);
      uVar8 = (*pcVar2)();
      return uVar8;
    }
    uVar9 = func_0x0001416099b0();
    cVar4 = func_0x00014169bf20(uVar25 + 0x10,uVar9);
    if (cVar4 == '\0') {
      uVar8 = 0;
    }
    else {
      uVar8 = *(ulonglong *)(uVar25 + 0x10) & 0xfffffffffffffffe;
    }
    if ((*(int *)(*(longlong *)(lVar14 + 0x10) + 0x38) < *(int *)(uVar8 + 0x38)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)(lVar14 + 0x10) + 0x30) + (longlong)*(int *)(uVar8 + 0x38) * 8)
        != uVar8 + 0x30)) {
      uVar9 = func_0x0001416099b0();
      cVar4 = func_0x00014169bf20(uVar25 + 0x10,uVar9);
      if (cVar4 == '\0') {
        uVar8 = 0;
      }
      else {
        uVar8 = *(ulonglong *)(uVar25 + 0x10) & 0xfffffffffffffffe;
      }
      uStack_130 = *(undefined8 *)(uVar8 + 0x18);
      func_0x0001411de0e0(&uStack_130,&puStack_a8);
      puVar21 = &UNK_14bce4e94;
      if (iStack_a0 != 0) {
        puVar21 = puStack_a8;
      }
      func_0x0001411de0e0(uVar25 + 0x20,&puStack_b8);
      puVar18 = &UNK_14bce4e94;
      if (iStack_b0 != 0) {
        puVar18 = puStack_b8;
      }
      uStack_128 = *(undefined8 *)(*(longlong *)(lStack_1b0 + 0x10) + 0x18);
      func_0x0001411de0e0(&uStack_128,&puStack_c8);
      puVar13 = &UNK_14bce4e94;
      if (iStack_c0 != 0) {
        puVar13 = puStack_c8;
      }
      uStack_120 = *(undefined8 *)(lStack_1b0 + 0x18);
      func_0x0001411de0e0(&uStack_120,&puStack_d8);
      puVar12 = &UNK_14bce4e94;
      if (iStack_d0 != 0) {
        puVar12 = puStack_d8;
      }
      cVar4 = func_0x000140f8dfd0(&UNK_14be86fc8,
                                  "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                  ,0x27d,unaff_retaddr,&UNK_14be86f40,puVar12,puVar13,puVar18,
                                  puVar21);
      if (puStack_d8 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      if (puStack_c8 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      if (puStack_b8 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      if (puStack_a8 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      if (cVar4 != '\0') {
        pcVar2 = (code *)swi(3);
        uVar8 = (*pcVar2)();
        return uVar8;
      }
    }
    plVar19 = (longlong *)(*(int *)(uVar25 + 0x44) + lStack_1b0);
    if (2 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7cec0,plVar24,plVar19);
    }
    if ((plVar24 != (longlong *)0x0) && (plVar19 != (longlong *)0x0)) {
      if (2 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7cfc8);
      }
      lVar14 = *plVar24;
      lVar3 = plVar24[1];
      lVar16 = (longlong)(int)lVar3 * 0x10 + lVar14;
      while( true ) {
        if ((int)plVar24[1] != (int)lVar3) {
          auStackX_18[0] = 0;
          cVar4 = func_0x00014bae4c30(auStackX_18);
          if (cVar4 != '\0') {
            pcVar2 = (code *)swi(3);
            uVar8 = (*pcVar2)();
            return uVar8;
          }
        }
        if (lVar14 == lVar16) break;
        if (2 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7d030);
        }
        lVar14 = lVar14 + 0x10;
      }
      if (2 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7d050);
      }
      lVar14 = *plVar19;
      lVar3 = plVar19[1];
      lVar16 = (longlong)(int)lVar3 * 0x10 + lVar14;
      while( true ) {
        if ((int)plVar19[1] != (int)lVar3) {
          auStackX_20[0] = 0;
          cVar4 = func_0x00014bae4c30(auStackX_20);
          if (cVar4 != '\0') {
            pcVar2 = (code *)swi(3);
            uVar8 = (*pcVar2)();
            return uVar8;
          }
        }
        if (lVar14 == lVar16) break;
        if (2 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7d0b0);
        }
        lVar14 = lVar14 + 0x10;
      }
      cVar4 = func_0x000140e6d810(plVar24,param_2);
      plVar26 = plStack_1a8;
      if (cVar4 == '\0') {
        plVar26 = (longlong *)*plVar24;
        if (((plVar26 <= param_2) &&
            (param_2 < plVar26 + (longlong)*(int *)((longlong)plVar24 + 0xc) * 2)) &&
           (cVar4 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                        &UNK_14bce6d80,param_2,plVar26,
                                        (longlong)*(int *)((longlong)plVar24 + 0xc),
                                        (longlong)(int)plVar24[1],0x10), cVar4 != '\0')) {
          pcVar2 = (code *)swi(3);
          uVar8 = (*pcVar2)();
          return uVar8;
        }
        iVar5 = (int)plVar24[1];
        *(uint *)(plVar24 + 1) = iVar5 + 1U;
        if (*(uint *)((longlong)plVar24 + 0xc) < iVar5 + 1U) {
          func_0x000140ca4b30(plVar24,iVar5);
        }
        plVar26 = plStack_1a8;
        puVar15 = (undefined8 *)((longlong)iVar5 * 0x10 + *plVar24);
        *puVar15 = 0;
        iVar5 = (int)*plStack_1a8;
        lStack_1b0 = *param_2;
        *(int *)(puVar15 + 1) = iVar5;
        puStack_178 = puVar15;
        if (iVar5 == 0) {
          *(undefined4 *)((longlong)puVar15 + 0xc) = 0;
        }
        else {
          func_0x000140ca39a0(puVar15,iVar5,0);
          func_0x00014b89502e(*puVar15,lStack_1b0,(longlong)iVar5 * 2);
        }
      }
      cVar4 = func_0x000140e6d810(plVar19,param_2);
      if (cVar4 == '\0') {
        plVar1 = (longlong *)*plVar19;
        if (((plVar1 <= param_2) &&
            (param_2 < plVar1 + (longlong)*(int *)((longlong)plVar19 + 0xc) * 2)) &&
           (cVar4 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                        &UNK_14bce6d80,param_2,plVar1,
                                        (longlong)*(int *)((longlong)plVar19 + 0xc),
                                        (longlong)(int)plVar19[1],0x10), cVar4 != '\0')) {
          pcVar2 = (code *)swi(3);
          uVar8 = (*pcVar2)();
          return uVar8;
        }
        iVar5 = (int)plVar19[1];
        *(uint *)(plVar19 + 1) = iVar5 + 1U;
        if (*(uint *)((longlong)plVar19 + 0xc) < iVar5 + 1U) {
          func_0x000140ca4b30(plVar19,iVar5);
        }
        puVar15 = (undefined8 *)((longlong)iVar5 * 0x10 + *plVar19);
        *puVar15 = 0;
        iVar5 = (int)*plVar26;
        lVar14 = *param_2;
        *(int *)(puVar15 + 1) = iVar5;
        puStack_178 = puVar15;
        if (iVar5 == 0) {
          *(undefined4 *)((longlong)puVar15 + 0xc) = 0;
        }
        else {
          func_0x000140ca39a0(puVar15,iVar5,0);
          func_0x00014b89502e(*puVar15,lVar14,(longlong)iVar5 * 2);
        }
      }
      if (2 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7d0d0);
      }
      puVar15 = (undefined8 *)*plVar24;
      lVar14 = plVar24[1];
      puVar17 = puVar15 + (longlong)(int)lVar14 * 2;
      while( true ) {
        if ((int)plVar24[1] != (int)lVar14) {
          uStack_1b8 = 0;
          cVar4 = func_0x00014bae4c30(&uStack_1b8);
          if (cVar4 != '\0') {
            pcVar2 = (code *)swi(3);
            uVar8 = (*pcVar2)();
            return uVar8;
          }
        }
        if (puVar15 == puVar17) break;
        if (2 < DAT_14eab53c8) {
          if (*(int *)(puVar15 + 1) == 0) {
            puVar21 = &UNK_14bce4e94;
          }
          else {
            puVar21 = (undefined *)*puVar15;
          }
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7d130,puVar21);
        }
        puVar15 = puVar15 + 2;
      }
      if (2 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7d150);
      }
      puVar15 = (undefined8 *)*plVar19;
      lVar14 = plVar19[1];
      puVar17 = puVar15 + (longlong)(int)lVar14 * 2;
      while( true ) {
        if ((int)plVar19[1] != (int)lVar14) {
          auStack_1b7[0] = 0;
          cVar4 = func_0x00014bae4c30(auStack_1b7);
          if (cVar4 != '\0') {
            pcVar2 = (code *)swi(3);
            uVar8 = (*pcVar2)();
            return uVar8;
          }
        }
        if (puVar15 == puVar17) break;
        if (2 < DAT_14eab53c8) {
          if (*(int *)(puVar15 + 1) == 0) {
            puVar21 = &UNK_14bce4e94;
          }
          else {
            puVar21 = (undefined *)*puVar15;
          }
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7d1b0,puVar21);
        }
        puVar15 = puVar15 + 2;
      }
      _Save_UCHPackStoreController__QEAAXXZ(param_1);
      if (2 < DAT_14eab53c8) {
        if ((int)*plStack_1a8 != 0) {
          puVar23 = (undefined *)*param_2;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7d1d0,puVar23);
      }
      uVar8 = 1;
      goto LAB_1481d758e;
    }
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7cf38);
    }
  }
LAB_1481d758c:
  uVar8 = 0;
LAB_1481d758e:
  func_0x000148141b60(&puStack_98);
  return uVar8;
}




/* Resolved referenced strings:
{
  "14cf27ac0": "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Array.h",
  "14bce6eb8": "Addr < GetData() || Addr >= (GetData() + ArrayMax)",
  "14be86f40": "'%s' is of class '%s' however property '%s' belongs to class '%s'",
  "14be5bf60": "Array index out of bounds: %i from an array of size %i",
  "14be5bfd0": "(ArrayIndex >= 0) && (ArrayIndex < ArrayDim)",
  "14be86ec0": "((UObject*)ContainerPtr)->IsValidLowLevel()",
  "14be86ef0": "((UObject*)ContainerPtr)->GetClass() != 0",
  "14be86f20": "GetOwner<UClass>()",
  "14bce6d80": "Attempting to use a container element (%p) which already comes from the container being modified (%p, ArrayMax: %lld, ArrayNum: %lld, SizeofElement: %d)!",
  "14be5c000": "ContainerPtr",
  "14be86fc8": "((UObject*)ContainerPtr)->IsA(GetOwner<UClass>())"
}
*/
