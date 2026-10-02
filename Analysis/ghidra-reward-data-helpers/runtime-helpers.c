
/* 1481c1a60 GetPlayerCardData */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * GetPlayerCardData(longlong param_1,undefined8 *param_2,longlong param_3)

{
  longlong lVar1;
  code *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  char cVar7;
  undefined8 *puVar8;
  longlong lVar9;
  int iVar10;
  undefined8 *puVar11;
  undefined1 auStackX_8 [8];
  undefined8 *puStackX_10;
  undefined8 *apuStack_40 [3];
  
  puStackX_10 = param_2;
  if (*(longlong *)(param_1 + 0x3f8) == 0) {
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf75820);
    }
    *param_2 = 0;
    param_2[1] = 0;
    param_2[2] = 0;
    param_2[3] = 0;
    param_2[4] = 0;
    param_2[5] = 0;
    param_2[6] = 0;
    param_2[7] = 0;
    param_2[8] = 0;
    param_2[9] = 0;
    *param_2 = &UNK_14cf496b0;
    param_2[1] = 0;
    func_0x000140e820a0(param_2 + 2);
    param_2[5] = 0;
    param_2[6] = 0;
    *(undefined4 *)(param_2 + 7) = 0;
    uVar6 = CONCAT44(_UNK_14bd3f824,_UNK_14bd3f820);
    *(ulonglong *)((longlong)param_2 + 0x3c) = CONCAT44(_UNK_14bd3f81c,_DAT_14bd3f818);
    *(undefined8 *)((longlong)param_2 + 0x44) = uVar6;
  }
  else {
    func_0x0001468fb0a0(*(longlong *)(param_1 + 0x3f8),apuStack_40);
    iVar10 = (int)apuStack_40[1];
    puVar8 = apuStack_40[0] + iVar10;
    puVar11 = apuStack_40[0];
    while( true ) {
      if ((int)apuStack_40[1] != iVar10) {
        auStackX_8[0] = 0;
        cVar7 = func_0x00014bae9430(auStackX_8);
        if (cVar7 != '\0') {
          pcVar2 = (code *)swi(3);
          puVar8 = (undefined8 *)(*pcVar2)();
          return puVar8;
        }
      }
      if (puVar11 == puVar8) {
        *param_2 = 0;
        param_2[1] = 0;
        param_2[2] = 0;
        param_2[3] = 0;
        param_2[4] = 0;
        param_2[5] = 0;
        param_2[6] = 0;
        param_2[7] = 0;
        param_2[8] = 0;
        param_2[9] = 0;
        *param_2 = &UNK_14cf496b0;
        param_2[1] = 0;
        func_0x000140e820a0(param_2 + 2);
        param_2[5] = 0;
        param_2[6] = 0;
        *(undefined4 *)(param_2 + 7) = 0;
        uVar5 = _UNK_14bd3f824;
        uVar4 = _UNK_14bd3f820;
        uVar3 = _UNK_14bd3f81c;
        *(undefined4 *)((longlong)param_2 + 0x3c) = _DAT_14bd3f818;
        *(undefined4 *)(param_2 + 8) = uVar3;
        *(undefined4 *)((longlong)param_2 + 0x44) = uVar4;
        *(undefined4 *)(param_2 + 9) = uVar5;
        goto LAB_1481c1bff;
      }
      lVar9 = func_0x0001481b1b00(*(undefined8 *)(param_1 + 0x3f8),*puVar11,&UNK_14bce4e94,1);
      if ((lVar9 != 0) && (*(longlong *)(lVar9 + 8) == param_3)) break;
      puVar11 = puVar11 + 1;
    }
    *param_2 = &UNK_14cf496b0;
    param_2[1] = *(undefined8 *)(lVar9 + 8);
    param_2[2] = *(undefined8 *)(lVar9 + 0x10);
    lVar1 = *(longlong *)(lVar9 + 0x18);
    param_2[3] = lVar1;
    if (lVar1 != 0) {
      LOCK();
      *(int *)(lVar1 + 8) = *(int *)(lVar1 + 8) + 1;
      UNLOCK();
    }
    *(undefined4 *)(param_2 + 4) = *(undefined4 *)(lVar9 + 0x20);
    param_2[5] = *(undefined8 *)(lVar9 + 0x28);
    param_2[6] = *(undefined8 *)(lVar9 + 0x30);
    *(undefined4 *)(param_2 + 7) = *(undefined4 *)(lVar9 + 0x38);
    uVar3 = *(undefined4 *)(lVar9 + 0x40);
    uVar4 = *(undefined4 *)(lVar9 + 0x44);
    uVar5 = *(undefined4 *)(lVar9 + 0x48);
    *(undefined4 *)((longlong)param_2 + 0x3c) = *(undefined4 *)(lVar9 + 0x3c);
    *(undefined4 *)(param_2 + 8) = uVar3;
    *(undefined4 *)((longlong)param_2 + 0x44) = uVar4;
    *(undefined4 *)(param_2 + 9) = uVar5;
LAB_1481c1bff:
    if (apuStack_40[0] != (undefined8 *)0x0) {
      func_0x000140e282f0();
    }
  }
  return param_2;
}


/* Instruction evidence:
1481c1a60 MOV qword ptr [RSP + 0x18],RBX
1481c1a65 MOV qword ptr [RSP + 0x20],RBP
1481c1a6a MOV qword ptr [RSP + 0x10],RDX
1481c1a6f PUSH RSI
1481c1a70 PUSH RDI
1481c1a71 PUSH R12
1481c1a73 PUSH R14
1481c1a75 PUSH R15
1481c1a77 SUB RSP,0x40
1481c1a7b MOV RBX,R8
1481c1a7e MOV RDI,RDX
1481c1a81 MOV R15,RCX
1481c1a84 XOR R12D,R12D
1481c1a87 MOV RCX,qword ptr [RCX + 0x3f8]
1481c1a8e TEST RCX,RCX
1481c1a91 JNZ 0x1481c1af9
1481c1a93 CMP byte ptr [0x14eab53c8],0x2
1481c1a9a JC 0x1481c1aaf
1481c1a9c LEA RDX,[0x14cf75820]
1481c1aa3 LEA RCX,[0x14eab53c8]
1481c1aaa CALL 0x140f24ba0
1481c1aaf XORPS XMM0,XMM0
1481c1ab2 MOVUPS xmmword ptr [RDI],XMM0
1481c1ab5 MOVUPS xmmword ptr [RDI + 0x10],XMM0
1481c1ab9 MOVUPS xmmword ptr [RDI + 0x20],XMM0
1481c1abd MOVUPS xmmword ptr [RDI + 0x30],XMM0
1481c1ac1 MOVUPS xmmword ptr [RDI + 0x40],XMM0
1481c1ac5 LEA RAX,[0x14cf496b0]
1481c1acc MOV qword ptr [RDI],RAX
1481c1acf MOV qword ptr [RDI + 0x8],R12
1481c1ad3 LEA RCX,[RDI + 0x10]
1481c1ad7 CALL 0x140e820a0
1481c1adc NOP
1481c1add MOV qword ptr [RDI + 0x28],R12
1481c1ae1 MOV qword ptr [RDI + 0x30],R12
1481c1ae5 MOV dword ptr [RDI + 0x38],R12D
1481c1ae9 MOVUPS XMM0,xmmword ptr [0x14bd3f818]
1481c1af0 MOVUPS xmmword ptr [RDI + 0x3c],XMM0
1481c1af4 JMP 0x1481c1c0f
1481c1af9 LEA RDX,[RSP + 0x28]
1481c1afe CALL 0x1468fb0a0
1481c1b03 NOP
1481c1b04 MOV RSI,qword ptr [RSP + 0x28]
1481c1b09 MOV RCX,qword ptr [RSP + 0x30]
1481c1b0e MOVSXD RBP,ECX
1481c1b11 LEA R14,[RSI + RBP*0x8]
1481c1b15 CMP ECX,EBP
1481c1b17 JZ 0x1481c1b2e
1481c1b19 MOV byte ptr [RSP + 0x70],0x0
1481c1b1e LEA RCX,[RSP + 0x70]
1481c1b23 CALL 0x14bae9430
1481c1b28 TEST AL,AL
1481c1b2a JZ 0x1481c1b2e
1481c1b2c NOP
1481c1b2d INT3
1481c1b2e CMP RSI,R14
1481c1b31 JZ 0x1481c1bba
1481c1b37 MOV R9B,0x1
1481c1b3a LEA R8,[0x14bce4e94]
1481c1b41 MOV RDX,qword ptr [RSI]
1481c1b44 MOV RCX,qword ptr [R15 + 0x3f8]
1481c1b4b CALL 0x1481b1b00
1481c1b50 MOV RCX,RAX
1481c1b53 TEST RAX,RAX
1481c1b56 JZ 0x1481c1b5e
1481c1b58 CMP qword ptr [RAX + 0x8],RBX
1481c1b5c JZ 0x1481c1b69
1481c1b5e ADD RSI,0x8
1481c1b62 MOV RCX,qword ptr [RSP + 0x30]
1481c1b67 JMP 0x1481c1b15
1481c1b69 LEA RAX,[0x14cf496b0]
1481c1b70 MOV qword ptr [RDI],RAX
1481c1b73 MOV RAX,qword ptr [RCX + 0x8]
1481c1b77 MOV qword ptr [RDI + 0x8],RAX
1481c1b7b MOV RAX,qword ptr [RCX + 0x10]
1481c1b7f MOV qword ptr [RDI + 0x10],RAX
1481c1b83 MOV RAX,qword ptr [RCX + 0x18]
1481c1b87 MOV qword ptr [RDI + 0x18],RAX
1481c1b8b TEST RAX,RAX
1481c1b8e JZ 0x1481c1b94
1481c1b90 INC.LOCK dword ptr [RAX + 0x8]
1481c1b94 MOV EAX,dword ptr [RCX + 0x20]
1481c1b97 MOV dword ptr [RDI + 0x20],EAX
1481c1b9a MOV RAX,qword ptr [RCX + 0x28]
1481c1b9e MOV qword ptr [RDI + 0x28],RAX
1481c1ba2 MOV RAX,qword ptr [RCX + 0x30]
1481c1ba6 MOV qword ptr [RDI + 0x30],RAX
1481c1baa MOV EAX,dword ptr [RCX + 0x38]
1481c1bad MOV dword ptr [RDI + 0x38],EAX
1481c1bb0 MOVUPS XMM0,xmmword ptr [RCX + 0x3c]
1481c1bb4 MOVUPS xmmword ptr [RDI + 0x3c],XMM0
1481c1bb8 JMP 0x1481c1bff
1481c1bba XORPS XMM0,XMM0
1481c1bbd MOVUPS xmmword ptr [RDI],XMM0
1481c1bc0 MOVUPS xmmword ptr [RDI + 0x10],XMM0
1481c1bc4 MOVUPS xmmword ptr [RDI + 0x20],XMM0
1481c1bc8 MOVUPS xmmword ptr [RDI + 0x30],XMM0
1481c1bcc MOVUPS xmmword ptr [RDI + 0x40],XMM0
1481c1bd0 LEA RAX,[0x14cf496b0]
1481c1bd7 MOV qword ptr [RDI],RAX
1481c1bda MOV qword ptr [RDI + 0x8],R12
1481c1bde LEA RCX,[RDI + 0x10]
1481c1be2 CALL 0x140e820a0
1481c1be7 NOP
1481c1be8 MOV qword ptr [RDI + 0x28],R12
1481c1bec MOV qword ptr [RDI + 0x30],R12
1481c1bf0 MOV dword ptr [RDI + 0x38],R12D
1481c1bf4 MOVUPS XMM0,xmmword ptr [0x14bd3f818]
1481c1bfb MOVUPS xmmword ptr [RDI + 0x3c],XMM0
1481c1bff MOV RCX,qword ptr [RSP + 0x28]
1481c1c04 TEST RCX,RCX
1481c1c07 JZ 0x1481c1c0f
1481c1c09 CALL 0x140e282f0
1481c1c0e NOP
1481c1c0f MOV RAX,RDI
1481c1c12 LEA R11,[RSP + 0x40]
1481c1c17 MOV RBX,qword ptr [R11 + 0x40]
1481c1c1b MOV RBP,qword ptr [R11 + 0x48]
1481c1c1f MOV RSP,R11
1481c1c22 POP R15
1481c1c24 POP R14
1481c1c26 POP R12
1481c1c28 POP RDI
1481c1c29 POP RSI
1481c1c2a RET
*/

/* 1481c1380 GetModifierData */

undefined8 * GetModifierData(longlong param_1,undefined8 *param_2,undefined8 param_3)

{
  int *piVar1;
  code *pcVar2;
  longlong *plVar3;
  uint uVar4;
  ulonglong *puVar5;
  char cVar6;
  int iVar7;
  undefined8 *puVar8;
  longlong *plVar9;
  longlong lVar10;
  ulonglong uVar11;
  longlong lVar12;
  longlong *plVar13;
  ulonglong *puVar14;
  longlong *plVar15;
  longlong *plVar16;
  longlong *plVar17;
  bool bVar18;
  undefined8 unaff_retaddr;
  undefined8 uStackX_18;
  undefined1 auStackX_20 [8];
  longlong lStack_130;
  longlong *plStack_128;
  undefined4 uStack_120;
  undefined2 uStack_11c;
  undefined1 uStack_11a;
  ulonglong *puStack_118;
  longlong alStack_110 [2];
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined8 uStack_f8;
  ulonglong *puStack_f0;
  uint uStack_e8;
  undefined8 uStack_e0;
  longlong *plStack_d8;
  undefined4 uStack_d0;
  undefined *puStack_c8;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined8 uStack_a8;
  longlong *plStack_a0;
  undefined4 uStack_98;
  longlong lStack_90;
  longlong lStack_88;
  int iStack_80;
  ulonglong *puStack_70;
  ulonglong uStack_68;
  ulonglong uStack_60;
  ulonglong uStack_58;
  ulonglong uStack_50;
  
  uStackX_18 = param_3;
  if (*(longlong *)(param_1 + 0x450) == 0) {
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf773e8);
    }
    *param_2 = 0;
    param_2[1] = 0;
    param_2[2] = 0;
    param_2[3] = 0;
    param_2[4] = 0;
    param_2[5] = 0;
    param_2[6] = 0;
    param_2[7] = 0;
    *param_2 = &UNK_14cf496c8;
    func_0x000140e820a0(param_2 + 1);
    func_0x000140e820a0(param_2 + 4);
    param_2[7] = 0;
  }
  else {
    func_0x0001411de0e0(&uStackX_18,&lStack_88);
    func_0x0001468fb0a0(*(undefined8 *)(param_1 + 0x450),&puStack_f0);
    uVar4 = uStack_e8;
    uVar11 = (ulonglong)(int)uStack_e8;
    puStack_70 = puStack_f0 + uVar11;
    puVar14 = puStack_f0;
LAB_1481c144d:
    puVar5 = puStack_70;
    puStack_118 = puVar14;
    if (uStack_e8 != (uint)uVar11) {
      auStackX_20[0] = 0;
      cVar6 = func_0x00014bae9430(auStackX_20);
      if (cVar6 != '\0') {
        pcVar2 = (code *)swi(3);
        puVar8 = (undefined8 *)(*pcVar2)();
        return puVar8;
      }
    }
    if (puVar14 != puVar5) {
      uVar11 = *puVar14;
      if ((*(longlong **)(param_1 + 0x450))[5] != 0) {
        plVar9 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x450) + 0x2d8))();
        iVar7 = func_0x0001411c2eb0(uVar11 & 0xffffffff);
        if ((int)plVar9[1] != *(int *)((longlong)plVar9 + 0x34)) {
          plVar13 = plVar9 + 7;
          if ((longlong *)plVar9[8] != (longlong *)0x0) {
            plVar13 = (longlong *)plVar9[8];
          }
          iVar7 = *(int *)((longlong)plVar13 +
                          (ulonglong)((int)plVar9[9] - 1U & (int)(uVar11 >> 0x20) + iVar7) * 4);
          if (iVar7 != -1) {
            do {
              puVar14 = (ulonglong *)(*plVar9 + (longlong)iVar7 * 0x18);
              uStack_60 = *puVar14;
              uStack_68 = uVar11;
              uStack_58 = uStack_60;
              uStack_50 = uVar11;
              if (uStack_60 == uVar11) {
                if (((puVar14 != (ulonglong *)0x0) && (puVar14 + 1 != (ulonglong *)0x0)) &&
                   (uVar11 = puVar14[1], uVar11 != 0)) {
                  plVar9 = (longlong *)0x0;
                  lStack_130 = *(longlong *)(*(longlong *)(param_1 + 0x450) + 0x28);
                  if (lStack_130 == 0) {
                    plStack_128 = (longlong *)0x0;
                  }
                  else {
                    plStack_128 = *(longlong **)(lStack_130 + 0x50);
                  }
                  uStack_120 = 0xffffffff;
                  uStack_11c = 0x101;
                  uStack_11a = 0;
                  func_0x0001416124a0(&lStack_130);
                  plVar13 = (longlong *)0x0;
                  plVar16 = (longlong *)0x0;
                  if (plStack_128 != (longlong *)0x0) goto LAB_1481c1596;
                }
                break;
              }
              iVar7 = (int)puVar14[2];
            } while (iVar7 != -1);
          }
        }
      }
      goto LAB_1481c1736;
    }
    *param_2 = 0;
    param_2[1] = 0;
    param_2[2] = 0;
    param_2[3] = 0;
    param_2[4] = 0;
    param_2[5] = 0;
    param_2[6] = 0;
    param_2[7] = 0;
    *param_2 = &UNK_14cf496c8;
    func_0x000140e820a0(param_2 + 1);
    func_0x000140e820a0(param_2 + 4);
    param_2[7] = 0;
    if (puStack_f0 != (ulonglong *)0x0) {
      func_0x000140e282f0();
    }
LAB_1481c1a0b:
    if (lStack_88 != 0) {
      func_0x000140e282f0();
    }
  }
  return param_2;
LAB_1481c1596:
  do {
    plVar3 = plStack_128;
    func_0x0001411de0e0(plStack_128 + 4,alStack_110);
    cVar6 = func_0x000140d26f80(alStack_110,L"ModifierTitle",0xd);
    plVar15 = plVar3;
    plVar17 = plVar16;
    if (((cVar6 == '\0') &&
        (cVar6 = func_0x000140d26f80(alStack_110,L"ModifierDescription",0x13), plVar15 = plVar13,
        plVar17 = plVar3, cVar6 == '\0')) &&
       (cVar6 = func_0x000140d26f80(alStack_110,L"ModifierIcon",0xc), plVar17 = plVar16,
       cVar6 != '\0')) {
      plVar9 = plVar3;
    }
    if (alStack_110[0] != 0) {
      func_0x000140e282f0();
    }
    plStack_128 = (longlong *)plVar3[3];
    func_0x0001416124a0(&lStack_130);
    plVar13 = plVar15;
    plVar16 = plVar17;
  } while (plStack_128 != (longlong *)0x0);
  if ((plVar15 == (longlong *)0x0) || ((*(uint *)(plVar15[1] + 0x10) >> 0x1e & 1) == 0))
  goto LAB_1481c1736;
  if (((int)plVar15[6] < 1) &&
     (cVar6 = func_0x000140f8dfd0(&UNK_14be5bfd0,
                                  "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                  ,0x261,unaff_retaddr,&UNK_14be5bf60,0,(int)plVar15[6]),
     cVar6 != '\0')) {
    pcVar2 = (code *)swi(3);
    puVar8 = (undefined8 *)(*pcVar2)();
    return puVar8;
  }
  lVar12 = (longlong)*(int *)((longlong)plVar15 + 0x44);
  uStack_e0 = *(undefined8 *)(lVar12 + uVar11);
  plStack_d8 = *(longlong **)(lVar12 + 8 + uVar11);
  if (plStack_d8 != (longlong *)0x0) {
    LOCK();
    *(int *)(plStack_d8 + 1) = (int)plStack_d8[1] + 1;
    UNLOCK();
  }
  uStack_d0 = *(undefined4 *)(lVar12 + 0x10 + uVar11);
  puVar8 = (undefined8 *)func_0x000140ef8a00(&uStack_e0);
  iVar7 = *(int *)(puVar8 + 1);
  if (iVar7 == iStack_80) {
    if (1 < iVar7) {
      iVar7 = func_0x000140d80770(*puVar8,lStack_88);
      bVar18 = iVar7 == 0;
      goto LAB_1481c16ee;
    }
  }
  else {
    bVar18 = iStack_80 + iVar7 == 1;
LAB_1481c16ee:
    plVar13 = plStack_d8;
    if (!bVar18) {
      if (plStack_d8 != (longlong *)0x0) {
        LOCK();
        plVar9 = plStack_d8 + 1;
        lVar12 = *plVar9;
        *(int *)plVar9 = (int)*plVar9 + -1;
        UNLOCK();
        if ((int)lVar12 == 1) {
          (**(code **)*plStack_d8)(plStack_d8);
          LOCK();
          piVar1 = (int *)((longlong)plVar13 + 0xc);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 == 1) {
            (**(code **)(*plVar13 + 8))(plVar13,1);
          }
        }
      }
LAB_1481c1736:
      puVar14 = puStack_118 + 1;
      uVar11 = (ulonglong)uVar4;
      goto LAB_1481c144d;
    }
  }
  puStack_c8 = &UNK_14cf496c8;
  func_0x000140e820a0(&uStack_c0);
  func_0x000140e820a0(&uStack_a8);
  lStack_90 = 0;
  if (plStack_d8 != (longlong *)0x0) {
    LOCK();
    *(int *)(plStack_d8 + 1) = (int)plStack_d8[1] + 1;
    UNLOCK();
  }
  uStack_100 = (undefined4)uStack_e0;
  uStack_fc = (undefined4)((ulonglong)uStack_e0 >> 0x20);
  uStack_f8._0_4_ = SUB84(plStack_d8,0);
  uStack_f8._4_4_ = (undefined4)((ulonglong)plStack_d8 >> 0x20);
  plVar13 = (longlong *)CONCAT44(uStack_b4,uStack_b8);
  uStack_c0 = uStack_100;
  uStack_bc = uStack_fc;
  uStack_b8 = (undefined4)uStack_f8;
  uStack_b4 = uStack_f8._4_4_;
  if (plVar13 != (longlong *)0x0) {
    LOCK();
    plVar16 = plVar13 + 1;
    lVar12 = *plVar16;
    *(int *)plVar16 = (int)*plVar16 + -1;
    UNLOCK();
    if ((int)lVar12 == 1) {
      uStack_f8 = plVar13;
      (**(code **)*plVar13)(plVar13);
      LOCK();
      piVar1 = (int *)((longlong)plVar13 + 0xc);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 == 1) {
        (**(code **)(*uStack_f8 + 8))(uStack_f8,1);
      }
    }
  }
  uStack_b0 = uStack_d0;
  if ((plVar17 != (longlong *)0x0) && ((*(uint *)(plVar17[1] + 0x10) >> 0x1e & 1) != 0)) {
    if (((int)plVar17[6] < 1) &&
       (cVar6 = func_0x000140f8dfd0(&UNK_14be5bfd0,
                                    "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                    ,0x261,unaff_retaddr,&UNK_14be5bf60,0,(int)plVar17[6]),
       cVar6 != '\0')) {
      pcVar2 = (code *)swi(3);
      puVar8 = (undefined8 *)(*pcVar2)();
      return puVar8;
    }
    func_0x000140e8a970(&uStack_a8,(longlong)*(int *)((longlong)plVar17 + 0x44) + uVar11);
  }
  if ((plVar9 != (longlong *)0x0) && ((*(uint *)(plVar9[1] + 0x10) >> 0x10 & 1) != 0)) {
    lVar12 = (**(code **)(*plVar9 + 0x198))(plVar9,uVar11,0);
    if (lVar12 != 0) {
      lVar10 = func_0x0001477cfb50();
      if ((*(int *)(lVar10 + 0x38) <= *(int *)(*(longlong *)(lVar12 + 0x10) + 0x38)) &&
         (lStack_90 = lVar12,
         *(longlong *)
          (*(longlong *)(*(longlong *)(lVar12 + 0x10) + 0x30) +
          (longlong)*(int *)(lVar10 + 0x38) * 8) == lVar10 + 0x30)) goto LAB_1481c18a8;
    }
    lStack_90 = 0;
  }
LAB_1481c18a8:
  *param_2 = &UNK_14cf496c8;
  param_2[1] = CONCAT44(uStack_bc,uStack_c0);
  lVar12 = CONCAT44(uStack_b4,uStack_b8);
  param_2[2] = lVar12;
  if (lVar12 != 0) {
    LOCK();
    *(int *)(lVar12 + 8) = *(int *)(lVar12 + 8) + 1;
    UNLOCK();
  }
  *(undefined4 *)(param_2 + 3) = uStack_b0;
  param_2[4] = uStack_a8;
  param_2[5] = plStack_a0;
  if (plStack_a0 != (longlong *)0x0) {
    LOCK();
    *(int *)(plStack_a0 + 1) = (int)plStack_a0[1] + 1;
    UNLOCK();
  }
  plVar9 = (longlong *)CONCAT44(uStack_b4,uStack_b8);
  *(undefined4 *)(param_2 + 6) = uStack_98;
  param_2[7] = lStack_90;
  if (plStack_a0 != (longlong *)0x0) {
    LOCK();
    plVar9 = plStack_a0 + 1;
    lVar12 = *plVar9;
    *(int *)plVar9 = (int)*plVar9 + -1;
    UNLOCK();
    if ((int)lVar12 == 1) {
      (**(code **)*plStack_a0)(plStack_a0);
      LOCK();
      piVar1 = (int *)((longlong)plStack_a0 + 0xc);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 == 1) {
        (**(code **)(*plStack_a0 + 8))(plStack_a0,1);
      }
    }
    plVar9 = (longlong *)CONCAT44(uStack_b4,uStack_b8);
  }
  if (plVar9 != (longlong *)0x0) {
    LOCK();
    plVar13 = plVar9 + 1;
    lVar12 = *plVar13;
    *(int *)plVar13 = (int)*plVar13 + -1;
    UNLOCK();
    if ((int)lVar12 == 1) {
      (**(code **)*plVar9)(plVar9);
      LOCK();
      piVar1 = (int *)((longlong)plVar9 + 0xc);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 == 1) {
        (**(code **)(*plVar9 + 8))(plVar9,1);
      }
    }
  }
  plVar9 = plStack_d8;
  puStack_c8 = &UNK_14c7543d0;
  if (plStack_d8 != (longlong *)0x0) {
    LOCK();
    plVar13 = plStack_d8 + 1;
    lVar12 = *plVar13;
    *(int *)plVar13 = (int)*plVar13 + -1;
    UNLOCK();
    if ((int)lVar12 == 1) {
      (**(code **)*plStack_d8)(plStack_d8);
      LOCK();
      piVar1 = (int *)((longlong)plVar9 + 0xc);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 == 1) {
        (**(code **)(*plVar9 + 8))(plVar9,1);
      }
    }
  }
  if (puStack_f0 != (ulonglong *)0x0) {
    func_0x000140e282f0();
  }
  goto LAB_1481c1a0b;
}


/* Instruction evidence:
1481c1380 MOV qword ptr [RSP + 0x18],R8
1481c1385 MOV qword ptr [RSP + 0x10],RDX
1481c138a MOV qword ptr [RSP + 0x8],RCX
1481c138f PUSH RBP
1481c1390 PUSH RBX
1481c1391 PUSH RSI
1481c1392 PUSH RDI
1481c1393 PUSH R12
1481c1395 PUSH R13
1481c1397 PUSH R14
1481c1399 PUSH R15
1481c139b LEA RBP,[RSP + -0x38]
1481c13a0 SUB RSP,0x138
1481c13a7 MOV R14,RDX
1481c13aa MOV RDI,RCX
1481c13ad XOR R15D,R15D
1481c13b0 CMP qword ptr [RCX + 0x450],R15
1481c13b7 JNZ 0x1481c1411
1481c13b9 CMP byte ptr [0x14eab53c8],0x2
1481c13c0 JC 0x1481c13d5
1481c13c2 LEA RDX,[0x14cf773e8]
1481c13c9 LEA RCX,[0x14eab53c8]
1481c13d0 CALL 0x140f24ba0
1481c13d5 XORPS XMM0,XMM0
1481c13d8 MOVUPS xmmword ptr [R14],XMM0
1481c13dc MOVUPS xmmword ptr [R14 + 0x10],XMM0
1481c13e1 MOVUPS xmmword ptr [R14 + 0x20],XMM0
1481c13e6 MOVUPS xmmword ptr [R14 + 0x30],XMM0
1481c13eb LEA RDI,[0x14cf496c8]
1481c13f2 MOV qword ptr [R14],RDI
1481c13f5 LEA RCX,[R14 + 0x8]
1481c13f9 CALL 0x140e820a0
1481c13fe NOP
1481c13ff LEA RCX,[R14 + 0x20]
1481c1403 CALL 0x140e820a0
1481c1408 MOV qword ptr [R14 + 0x38],R15
1481c140c JMP 0x1481c1a1a
1481c1411 LEA RDX,[RBP + -0x10]
1481c1415 LEA RCX,[RBP + 0x90]
1481c141c CALL 0x1411de0e0
1481c1421 NOP
1481c1422 LEA RDX,[RBP + -0x78]
1481c1426 MOV RCX,qword ptr [RDI + 0x450]
1481c142d CALL 0x1468fb0a0
1481c1432 NOP
1481c1433 MOV RBX,qword ptr [RBP + -0x78]
1481c1437 MOVSXD RCX,dword ptr [RBP + -0x70]
1481c143b MOV dword ptr [RSP + 0x40],ECX
1481c143f LEA RSI,[RBX + RCX*0x8]
1481c1443 MOV qword ptr [RBP + 0x8],RSI
1481c1447 MOV R13D,0xffffffff
1481c144d MOV qword ptr [RSP + 0x60],RBX
1481c1452 CMP dword ptr [RBP + -0x70],ECX
1481c1455 JZ 0x1481c1470
1481c1457 MOV byte ptr [RBP + 0x98],0x0
1481c145e LEA RCX,[RBP + 0x98]
1481c1465 CALL 0x14bae9430
1481c146a TEST AL,AL
1481c146c JZ 0x1481c1470
1481c146e NOP
1481c146f INT3
1481c1470 CMP RBX,RSI
1481c1473 JZ 0x1481c19c1
1481c1479 MOV RCX,qword ptr [RDI + 0x450]
1481c1480 MOV RBX,qword ptr [RBX]
1481c1483 MOV RSI,RBX
1481c1486 SHR RSI,0x20
1481c148a CMP qword ptr [RCX + 0x28],0x0
1481c148f JZ 0x1481c1736
1481c1495 MOV RAX,qword ptr [RCX]
1481c1498 CALL qword ptr [RAX + 0x2d8]
1481c149e MOV RDI,RAX
1481c14a1 MOV ECX,EBX
1481c14a3 CALL 0x1411c2eb0
1481c14a8 LEA R8D,[RSI + RAX*0x1]
1481c14ac MOV ECX,dword ptr [RDI + 0x8]
1481c14af CMP ECX,dword ptr [RDI + 0x34]
1481c14b2 JZ 0x1481c172f
1481c14b8 LEA RDX,[RDI + 0x38]
1481c14bc MOV RCX,qword ptr [RDX + 0x8]
1481c14c0 TEST RCX,RCX
1481c14c3 CMOVNZ RDX,RCX
1481c14c7 MOV ECX,dword ptr [RDI + 0x48]
1481c14ca DEC ECX
1481c14cc MOV EAX,R8D
1481c14cf AND RCX,RAX
1481c14d2 MOV EAX,dword ptr [RDX + RCX*0x4]
1481c14d5 CMP EAX,-0x1
1481c14d8 JZ 0x1481c172f
1481c14de MOV R8,qword ptr [RDI]
1481c14e1 MOV qword ptr [RBP + 0x10],RBX
1481c14e5 NOP word ptr [RAX + RAX*0x1]
1481c14f0 CDQE
1481c14f2 LEA RCX,[RAX + RAX*0x2]
1481c14f6 LEA RDX,[R8 + RCX*0x8]
1481c14fa MOV RAX,qword ptr [RDX]
1481c14fd MOV qword ptr [RBP + 0x18],RAX
1481c1501 MOV qword ptr [RBP + 0x20],RAX
1481c1505 MOV qword ptr [RBP + 0x28],RBX
1481c1509 CMP RAX,RBX
1481c150c JZ 0x1481c151b
1481c150e MOV EAX,dword ptr [RDX + 0x10]
1481c1511 CMP EAX,-0x1
1481c1514 JNZ 0x1481c14f0
1481c1516 JMP 0x1481c172f
1481c151b TEST RDX,RDX
1481c151e JZ 0x1481c172f
1481c1524 ADD RDX,0x8
1481c1528 JZ 0x1481c172f
1481c152e MOV R12,qword ptr [RDX]
1481c1531 TEST R12,R12
1481c1534 JZ 0x1481c172f
1481c153a XOR EDI,EDI
1481c153c XOR R15D,R15D
1481c153f XOR ESI,ESI
1481c1541 MOV RAX,qword ptr [RBP + 0x80]
1481c1548 MOV RAX,qword ptr [RAX + 0x450]
1481c154f MOV RAX,qword ptr [RAX + 0x28]
1481c1553 MOV qword ptr [RSP + 0x48],RAX
1481c1558 TEST RAX,RAX
1481c155b JZ 0x1481c1568
1481c155d MOV RAX,qword ptr [RAX + 0x50]
1481c1561 MOV qword ptr [RSP + 0x50],RAX
1481c1566 JMP 0x1481c156d
1481c1568 MOV qword ptr [RSP + 0x50],RSI
1481c156d MOV dword ptr [RSP + 0x58],R13D
1481c1572 MOV word ptr [RSP + 0x5c],0x101
1481c1579 MOV byte ptr [RSP + 0x5e],SIL
1481c157e LEA RCX,[RSP + 0x48]
1481c1583 CALL 0x1416124a0
1481c1588 MOV RBX,qword ptr [RSP + 0x50]
1481c158d TEST RBX,RBX
1481c1590 JZ 0x1481c172f
1481c1596 LEA RCX,[RBX + 0x20]
1481c159a LEA RDX,[RSP + 0x68]
1481c159f CALL 0x1411de0e0
1481c15a4 NOP
1481c15a5 MOV R9D,0x1
1481c15ab LEA R8D,[R9 + 0xc]
1481c15af LEA RDX,[0x14cf77408]
1481c15b6 LEA RCX,[RSP + 0x68]
1481c15bb CALL 0x140d26f80
1481c15c0 TEST AL,AL
1481c15c2 JZ 0x1481c15c9
1481c15c4 MOV RDI,RBX
1481c15c7 JMP 0x1481c160e
1481c15c9 MOV R9D,0x1
1481c15cf LEA R8D,[R9 + 0x12]
1481c15d3 LEA RDX,[0x14cf77428]
1481c15da LEA RCX,[RSP + 0x68]
1481c15df CALL 0x140d26f80
1481c15e4 TEST AL,AL
1481c15e6 JZ 0x1481c15ed
1481c15e8 MOV R15,RBX
1481c15eb JMP 0x1481c160e
1481c15ed MOV R9D,0x1
1481c15f3 LEA R8D,[R9 + 0xb]
1481c15f7 LEA RDX,[0x14cf77450]
1481c15fe LEA RCX,[RSP + 0x68]
1481c1603 CALL 0x140d26f80
1481c1608 TEST AL,AL
1481c160a CMOVNZ RSI,RBX
1481c160e MOV RCX,qword ptr [RSP + 0x68]
1481c1613 TEST RCX,RCX
1481c1616 JZ 0x1481c161e
1481c1618 CALL 0x140e282f0
1481c161d NOP
1481c161e MOV RAX,qword ptr [RBX + 0x18]
1481c1622 MOV qword ptr [RSP + 0x50],RAX
1481c1627 LEA RCX,[RSP + 0x48]
1481c162c CALL 0x1416124a0
1481c1631 MOV RBX,qword ptr [RSP + 0x50]
1481c1636 TEST RBX,RBX
1481c1639 JNZ 0x1481c1596
1481c163f TEST RDI,RDI
1481c1642 JZ 0x1481c172f
1481c1648 MOV RAX,qword ptr [RDI + 0x8]
1481c164c MOV ECX,dword ptr [RAX + 0x10]
1481c164f SHR RCX,0x1e
1481c1653 TEST CL,0x1
1481c1656 JZ 0x1481c172f
1481c165c MOV EAX,dword ptr [RDI + 0x30]
1481c165f TEST EAX,EAX
1481c1661 JG 0x1481c169a
1481c1663 MOV R9,qword ptr [RBP + 0x78]
1481c1667 MOV dword ptr [RSP + 0x30],EAX
1481c166b MOV dword ptr [RSP + 0x28],EBX
1481c166f LEA RAX,[0x14be5bf60]
1481c1676 MOV qword ptr [RSP + 0x20],RAX
1481c167b MOV R8D,0x261
1481c1681 LEA RDX,[0x14cf63d80]
1481c1688 LEA RCX,[0x14be5bfd0]
1481c168f CALL 0x140f8dfd0
1481c1694 TEST AL,AL
1481c1696 JZ 0x1481c169a
1481c1698 NOP
1481c1699 INT3
1481c169a MOVSXD RCX,dword ptr [RDI + 0x44]
1481c169e MOV RAX,qword ptr [RCX + R12*0x1]
1481c16a2 MOV qword ptr [RBP + -0x68],RAX
1481c16a6 MOV RAX,qword ptr [RCX + R12*0x1 + 0x8]
1481c16ab MOV qword ptr [RBP + -0x60],RAX
1481c16af TEST RAX,RAX
1481c16b2 JZ 0x1481c16b8
1481c16b4 INC.LOCK dword ptr [RAX + 0x8]
1481c16b8 MOV EAX,dword ptr [RCX + R12*0x1 + 0x10]
1481c16bd MOV dword ptr [RBP + -0x58],EAX
1481c16c0 LEA RCX,[RBP + -0x68]
1481c16c4 CALL 0x140ef8a00
1481c16c9 MOV ECX,dword ptr [RAX + 0x8]
1481c16cc MOV EDX,dword ptr [RBP + -0x8]
1481c16cf CMP ECX,EDX
1481c16d1 JZ 0x1481c16db
1481c16d3 LEA EAX,[RDX + RCX*0x1]
1481c16d6 CMP EAX,0x1
1481c16d9 JMP 0x1481c16ee
1481c16db CMP ECX,0x1
1481c16de JLE 0x1481c174c
1481c16e0 MOV RDX,qword ptr [RBP + -0x10]
1481c16e4 MOV RCX,qword ptr [RAX]
1481c16e7 CALL 0x140d80770
1481c16ec TEST EAX,EAX
1481c16ee SETZ AL
1481c16f1 TEST AL,AL
1481c16f3 JNZ 0x1481c174c
1481c16f5 MOV RBX,qword ptr [RBP + -0x60]
1481c16f9 TEST RBX,RBX
1481c16fc JZ 0x1481c172f
1481c16fe MOV EAX,R13D
1481c1701 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c1706 CMP EAX,0x1
1481c1709 JNZ 0x1481c172f
1481c170b MOV RAX,qword ptr [RBX]
1481c170e MOV RCX,RBX
1481c1711 CALL qword ptr [RAX]
1481c1713 MOV EAX,R13D
1481c1716 XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c171b CMP EAX,0x1
1481c171e JNZ 0x1481c172f
1481c1720 MOV RAX,qword ptr [RBX]
1481c1723 MOV EDX,0x1
1481c1728 MOV RCX,RBX
1481c172b CALL qword ptr [RAX + 0x8]
1481c172e NOP
1481c172f MOV RDI,qword ptr [RBP + 0x80]
1481c1736 MOV RBX,qword ptr [RSP + 0x60]
1481c173b ADD RBX,0x8
1481c173f MOV ECX,dword ptr [RSP + 0x40]
1481c1743 MOV RSI,qword ptr [RBP + 0x8]
1481c1747 JMP 0x1481c144d
1481c174c LEA RDI,[0x14cf496c8]
1481c1753 MOV qword ptr [RBP + -0x50],RDI
1481c1757 LEA RCX,[RBP + -0x48]
1481c175b CALL 0x140e820a0
1481c1760 NOP
1481c1761 LEA RCX,[RBP + -0x30]
1481c1765 CALL 0x140e820a0
1481c176a MOV qword ptr [RBP + -0x18],0x0
1481c1772 MOV RAX,qword ptr [RBP + -0x68]
1481c1776 MOV qword ptr [RSP + 0x78],RAX
1481c177b MOV RBX,qword ptr [RBP + -0x60]
1481c177f MOV qword ptr [RBP + -0x80],RBX
1481c1783 TEST RBX,RBX
1481c1786 JZ 0x1481c178c
1481c1788 INC.LOCK dword ptr [RBX + 0x8]
1481c178c MOVUPS XMM0,xmmword ptr [RSP + 0x78]
1481c1791 MOVUPS XMM1,xmmword ptr [RBP + -0x48]
1481c1795 MOVUPS xmmword ptr [RSP + 0x78],XMM1
1481c179a MOVUPS xmmword ptr [RBP + -0x48],XMM0
1481c179e PSRLDQ XMM1,0x8
1481c17a3 MOVQ RCX,XMM1
1481c17a8 TEST RCX,RCX
1481c17ab JZ 0x1481c17e3
1481c17ad MOV EAX,R13D
1481c17b0 XADD.LOCK dword ptr [RCX + 0x8],EAX
1481c17b5 CMP EAX,0x1
1481c17b8 JNZ 0x1481c17e3
1481c17ba MOV RBX,qword ptr [RBP + -0x80]
1481c17be MOV RAX,qword ptr [RBX]
1481c17c1 MOV RCX,RBX
1481c17c4 CALL qword ptr [RAX]
1481c17c6 MOV EAX,R13D
1481c17c9 XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c17ce CMP EAX,0x1
1481c17d1 JNZ 0x1481c17e3
1481c17d3 MOV RCX,qword ptr [RBP + -0x80]
1481c17d7 MOV RAX,qword ptr [RCX]
1481c17da MOV EDX,0x1
1481c17df CALL qword ptr [RAX + 0x8]
1481c17e2 NOP
1481c17e3 MOV EAX,dword ptr [RBP + -0x58]
1481c17e6 MOV dword ptr [RBP + -0x38],EAX
1481c17e9 TEST R15,R15
1481c17ec JZ 0x1481c1851
1481c17ee MOV RAX,qword ptr [R15 + 0x8]
1481c17f2 MOV ECX,dword ptr [RAX + 0x10]
1481c17f5 SHR RCX,0x1e
1481c17f9 TEST CL,0x1
1481c17fc JZ 0x1481c1851
1481c17fe MOV EAX,dword ptr [R15 + 0x30]
1481c1802 TEST EAX,EAX
1481c1804 JG 0x1481c1841
1481c1806 MOV R9,qword ptr [RBP + 0x78]
1481c180a MOV dword ptr [RSP + 0x30],EAX
1481c180e MOV dword ptr [RSP + 0x28],0x0
1481c1816 LEA RAX,[0x14be5bf60]
1481c181d MOV qword ptr [RSP + 0x20],RAX
1481c1822 MOV R8D,0x261
1481c1828 LEA RDX,[0x14cf63d80]
1481c182f LEA RCX,[0x14be5bfd0]
1481c1836 CALL 0x140f8dfd0
1481c183b TEST AL,AL
1481c183d JZ 0x1481c1841
1481c183f NOP
1481c1840 INT3
1481c1841 MOVSXD RDX,dword ptr [R15 + 0x44]
1481c1845 ADD RDX,R12
1481c1848 LEA RCX,[RBP + -0x30]
1481c184c CALL 0x140e8a970
1481c1851 TEST RSI,RSI
1481c1854 JZ 0x1481c18a8
1481c1856 MOV RAX,qword ptr [RSI + 0x8]
1481c185a MOV R8D,dword ptr [RAX + 0x10]
1481c185e SHR R8,0x10
1481c1862 TEST R8B,0x1
1481c1866 JZ 0x1481c18a8
1481c1868 MOV RAX,qword ptr [RSI]
1481c186b XOR R8D,R8D
1481c186e MOV RDX,R12
1481c1871 MOV RCX,RSI
1481c1874 CALL qword ptr [RAX + 0x198]
1481c187a MOV RBX,RAX
1481c187d TEST RAX,RAX
1481c1880 JZ 0x1481c18a2
1481c1882 CALL 0x1477cfb50
1481c1887 MOV RCX,qword ptr [RBX + 0x10]
1481c188b ADD RAX,0x30
1481c188f MOVSXD RDX,dword ptr [RAX + 0x8]
1481c1893 CMP EDX,dword ptr [RCX + 0x38]
1481c1896 JG 0x1481c18a2
1481c1898 MOV RCX,qword ptr [RCX + 0x30]
1481c189c CMP qword ptr [RCX + RDX*0x8],RAX
1481c18a0 JZ 0x1481c18a4
1481c18a2 XOR EBX,EBX
1481c18a4 MOV qword ptr [RBP + -0x18],RBX
1481c18a8 MOV qword ptr [R14],RDI
1481c18ab MOV RAX,qword ptr [RBP + -0x48]
1481c18af MOV qword ptr [R14 + 0x8],RAX
1481c18b3 MOV RBX,qword ptr [RBP + -0x40]
1481c18b7 MOV qword ptr [R14 + 0x10],RBX
1481c18bb TEST RBX,RBX
1481c18be JZ 0x1481c18c8
1481c18c0 INC.LOCK dword ptr [RBX + 0x8]
1481c18c4 MOV RBX,qword ptr [RBP + -0x40]
1481c18c8 MOV EAX,dword ptr [RBP + -0x38]
1481c18cb MOV dword ptr [R14 + 0x18],EAX
1481c18cf MOV RAX,qword ptr [RBP + -0x30]
1481c18d3 MOV qword ptr [R14 + 0x20],RAX
1481c18d7 MOV RDI,qword ptr [RBP + -0x28]
1481c18db MOV qword ptr [R14 + 0x28],RDI
1481c18df TEST RDI,RDI
1481c18e2 JZ 0x1481c18f0
1481c18e4 INC.LOCK dword ptr [RDI + 0x8]
1481c18e8 MOV RDI,qword ptr [RBP + -0x28]
1481c18ec MOV RBX,qword ptr [RBP + -0x40]
1481c18f0 MOV EAX,dword ptr [RBP + -0x20]
1481c18f3 MOV dword ptr [R14 + 0x30],EAX
1481c18f7 MOV RAX,qword ptr [RBP + -0x18]
1481c18fb MOV qword ptr [R14 + 0x38],RAX
1481c18ff TEST RDI,RDI
1481c1902 JZ 0x1481c1938
1481c1904 MOV EAX,R13D
1481c1907 XADD.LOCK dword ptr [RDI + 0x8],EAX
1481c190c CMP EAX,0x1
1481c190f JNZ 0x1481c1934
1481c1911 MOV RAX,qword ptr [RDI]
1481c1914 MOV RCX,RDI
1481c1917 CALL qword ptr [RAX]
1481c1919 MOV EAX,R13D
1481c191c XADD.LOCK dword ptr [RDI + 0xc],EAX
1481c1921 CMP EAX,0x1
1481c1924 JNZ 0x1481c1934
1481c1926 MOV RAX,qword ptr [RDI]
1481c1929 MOV EDX,0x1
1481c192e MOV RCX,RDI
1481c1931 CALL qword ptr [RAX + 0x8]
1481c1934 MOV RBX,qword ptr [RBP + -0x40]
1481c1938 TEST RBX,RBX
1481c193b JZ 0x1481c196e
1481c193d MOV EAX,R13D
1481c1940 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c1945 CMP EAX,0x1
1481c1948 JNZ 0x1481c196e
1481c194a MOV RAX,qword ptr [RBX]
1481c194d MOV RCX,RBX
1481c1950 CALL qword ptr [RAX]
1481c1952 MOV EAX,R13D
1481c1955 XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c195a CMP EAX,0x1
1481c195d JNZ 0x1481c196e
1481c195f MOV RAX,qword ptr [RBX]
1481c1962 MOV EDX,0x1
1481c1967 MOV RCX,RBX
1481c196a CALL qword ptr [RAX + 0x8]
1481c196d NOP
1481c196e LEA RAX,[0x14c7543d0]
1481c1975 MOV qword ptr [RBP + -0x50],RAX
1481c1979 MOV RBX,qword ptr [RBP + -0x60]
1481c197d TEST RBX,RBX
1481c1980 JZ 0x1481c19b0
1481c1982 MOV EAX,R13D
1481c1985 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c198a CMP EAX,0x1
1481c198d JNZ 0x1481c19b0
1481c198f MOV RAX,qword ptr [RBX]
1481c1992 MOV RCX,RBX
1481c1995 CALL qword ptr [RAX]
1481c1997 XADD.LOCK dword ptr [RBX + 0xc],R13D
1481c199d CMP R13D,0x1
1481c19a1 JNZ 0x1481c19b0
1481c19a3 MOV RAX,qword ptr [RBX]
1481c19a6 MOV EDX,R13D
1481c19a9 MOV RCX,RBX
1481c19ac CALL qword ptr [RAX + 0x8]
1481c19af NOP
1481c19b0 MOV RCX,qword ptr [RBP + -0x78]
1481c19b4 TEST RCX,RCX
1481c19b7 JZ 0x1481c19bf
1481c19b9 CALL 0x140e282f0
1481c19be NOP
1481c19bf JMP 0x1481c1a0b
1481c19c1 XORPS XMM0,XMM0
1481c19c4 MOVUPS xmmword ptr [R14],XMM0
1481c19c8 MOVUPS xmmword ptr [R14 + 0x10],XMM0
1481c19cd MOVUPS xmmword ptr [R14 + 0x20],XMM0
1481c19d2 MOVUPS xmmword ptr [R14 + 0x30],XMM0
1481c19d7 LEA RDI,[0x14cf496c8]
1481c19de MOV qword ptr [R14],RDI
1481c19e1 LEA RCX,[R14 + 0x8]
1481c19e5 CALL 0x140e820a0
1481c19ea NOP
1481c19eb LEA RCX,[R14 + 0x20]
1481c19ef CALL 0x140e820a0
1481c19f4 MOV qword ptr [R14 + 0x38],0x0
1481c19fc MOV RCX,qword ptr [RBP + -0x78]
1481c1a00 TEST RCX,RCX
1481c1a03 JZ 0x1481c1a0b
1481c1a05 CALL 0x140e282f0
1481c1a0a NOP
1481c1a0b MOV RCX,qword ptr [RBP + -0x10]
1481c1a0f TEST RCX,RCX
1481c1a12 JZ 0x1481c1a1a
1481c1a14 CALL 0x140e282f0
1481c1a19 NOP
1481c1a1a MOV RAX,R14
1481c1a1d ADD RSP,0x138
1481c1a24 POP R15
1481c1a26 POP R14
1481c1a28 POP R13
1481c1a2a POP R12
1481c1a2c POP RDI
1481c1a2d POP RSI
1481c1a2e POP RBX
1481c1a2f POP RBP
1481c1a30 RET
*/

/* 1481d6810 UnlockPack */

ulonglong UnlockPack(longlong param_1,longlong *param_2)

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
  uVar8 = IsPackUnlocked(param_1,param_2);
  if ((char)uVar8 != '\0') {
    if (2 < DAT_14eab53c8) {
      if ((int)*plVar24 != 0) {
        puVar23 = (undefined *)*param_2;
      }
      uVar8 = func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7cb58,puVar23);
    }
    goto LAB_1481d68df;
  }
  func_0x0001481d4be0(param_1,&puStack_98);
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
        uVar6 = func_0x0001481d4fe0(param_1);
        if ((int)*plVar24 == 0) {
          puVar21 = &UNK_14bce4e94;
        }
        else {
          puVar21 = (undefined *)*param_2;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7cc60,puVar21,iVar5,CONCAT44(uVar28,uVar6));
      }
      iVar7 = func_0x0001481d4fe0(param_1);
      if (iVar7 < iVar5) {
        if (2 < DAT_14eab53c8) {
          if ((int)*plVar24 != 0) {
            puVar23 = (undefined *)*param_2;
          }
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7cd08,puVar23,iVar5);
        }
        goto LAB_1481d758c;
      }
      func_0x0001481d3580(param_1,-iVar5);
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
      func_0x0001481d5fb0(param_1);
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


/* Instruction evidence:
1481d6810 MOV qword ptr [RSP + 0x10],RBX
1481d6815 MOV qword ptr [RSP + 0x8],RCX
1481d681a PUSH RBP
1481d681b PUSH RSI
1481d681c PUSH RDI
1481d681d PUSH R12
1481d681f PUSH R13
1481d6821 PUSH R14
1481d6823 PUSH R15
1481d6825 LEA RBP,[RSP + -0xd0]
1481d682d SUB RSP,0x1d0
1481d6834 MOV R13,RDX
1481d6837 MOV R15,RCX
1481d683a LEA RSI,[RDX + 0x8]
1481d683e MOV qword ptr [RSP + 0x60],RSI
1481d6843 LEA R12,[0x14bce4e94]
1481d684a MOVZX EAX,byte ptr [0x14eab53c8]
1481d6851 CMP AL,0x3
1481d6853 JC 0x1481d687e
1481d6855 CMP dword ptr [RSI],0x0
1481d6858 JZ 0x1481d685f
1481d685a MOV R8,qword ptr [RDX]
1481d685d JMP 0x1481d6862
1481d685f MOV R8,R12
1481d6862 LEA RDX,[0x14cf7ca68]
1481d6869 LEA RCX,[0x14eab53c8]
1481d6870 CALL 0x140f24ba0
1481d6875 MOVZX EAX,byte ptr [0x14eab53c8]
1481d687c JMP 0x1481d6883
1481d687e MOV qword ptr [RSP + 0x60],RSI
1481d6883 CMP qword ptr [R15 + 0x38],0x0
1481d6888 JNZ 0x1481d68a8
1481d688a CMP AL,0x2
1481d688c JC 0x1481d68df
1481d688e LEA RDX,[0x14cf7cae0]
1481d6895 LEA RCX,[0x14eab53c8]
1481d689c CALL 0x140f24ba0
1481d68a1 XOR AL,AL
1481d68a3 JMP 0x1481d759a
1481d68a8 MOV RDX,R13
1481d68ab MOV RCX,R15
1481d68ae CALL 0x1481d57b0
1481d68b3 TEST AL,AL
1481d68b5 JZ 0x1481d68e6
1481d68b7 CMP byte ptr [0x14eab53c8],0x3
1481d68be JC 0x1481d68df
1481d68c0 CMP dword ptr [RSI],0x0
1481d68c3 JZ 0x1481d68c9
1481d68c5 MOV R12,qword ptr [R13]
1481d68c9 MOV R8,R12
1481d68cc LEA RDX,[0x14cf7cb58]
1481d68d3 LEA RCX,[0x14eab53c8]
1481d68da CALL 0x140f24ba0
1481d68df XOR AL,AL
1481d68e1 JMP 0x1481d759a
1481d68e6 LEA RDX,[RBP + 0x70]
1481d68ea MOV RCX,R15
1481d68ed CALL 0x1481d4be0
1481d68f2 NOP
1481d68f3 MOV RBX,qword ptr [RBP + 0x70]
1481d68f7 MOVSXD RAX,dword ptr [RBP + 0x78]
1481d68fb IMUL RDI,RAX,0x110
1481d6902 ADD RDI,RBX
1481d6905 CMP RBX,RDI
1481d6908 JZ 0x1481d7564
1481d690e MOV EAX,dword ptr [RBX + 0x8]
1481d6911 MOV ECX,dword ptr [RSI]
1481d6913 CMP EAX,ECX
1481d6915 JZ 0x1481d691e
1481d6917 ADD EAX,ECX
1481d6919 CMP EAX,0x1
1481d691c JMP 0x1481d6931
1481d691e CMP EAX,0x1
1481d6921 JLE 0x1481d6941
1481d6923 MOV RDX,qword ptr [R13]
1481d6927 MOV RCX,qword ptr [RBX]
1481d692a CALL 0x140d80770
1481d692f TEST EAX,EAX
1481d6931 SETZ AL
1481d6934 TEST AL,AL
1481d6936 JNZ 0x1481d6941
1481d6938 ADD RBX,0x110
1481d693f JMP 0x1481d6905
1481d6941 MOV EBX,dword ptr [RBX + 0x50]
1481d6944 CMP byte ptr [0x14eab53c8],0x3
1481d694b JC 0x1481d697d
1481d694d MOV RCX,R15
1481d6950 CALL 0x1481d4fe0
1481d6955 CMP dword ptr [RSI],0x0
1481d6958 JZ 0x1481d6960
1481d695a MOV R8,qword ptr [R13]
1481d695e JMP 0x1481d6963
1481d6960 MOV R8,R12
1481d6963 MOV dword ptr [RSP + 0x20],EAX
1481d6967 MOV R9D,EBX
1481d696a LEA RDX,[0x14cf7cc60]
1481d6971 LEA RCX,[0x14eab53c8]
1481d6978 CALL 0x140f24ba0
1481d697d MOV RCX,R15
1481d6980 CALL 0x1481d4fe0
1481d6985 CMP EAX,EBX
1481d6987 JGE 0x1481d69bd
1481d6989 CMP byte ptr [0x14eab53c8],0x3
1481d6990 JC 0x1481d758c
1481d6996 CMP dword ptr [RSI],0x0
1481d6999 JZ 0x1481d699f
1481d699b MOV R12,qword ptr [R13]
1481d699f MOV R9D,EBX
1481d69a2 MOV R8,R12
1481d69a5 LEA RDX,[0x14cf7cd08]
1481d69ac LEA RCX,[0x14eab53c8]
1481d69b3 CALL 0x140f24ba0
1481d69b8 JMP 0x1481d758c
1481d69bd NEG EBX
1481d69bf MOV EDX,EBX
1481d69c1 MOV RCX,R15
1481d69c4 CALL 0x1481d3580
1481d69c9 MOV RAX,qword ptr [R15 + 0x38]
1481d69cd MOV RDI,qword ptr [RAX + 0x10]
1481d69d1 XOR R8D,R8D
1481d69d4 LEA RDX,[0x14cf7d260]
1481d69db LEA RCX,[RBP + -0x50]
1481d69df CALL 0x1411a7b80
1481d69e4 MOV RBX,qword ptr [RBP + -0x50]
1481d69e8 MOV qword ptr [RBP + 0x80],RBX
1481d69ef MOV qword ptr [RBP + 0x88],RBX
1481d69f6 XOR ESI,ESI
1481d69f8 TEST RBX,RBX
1481d69fb JZ 0x1481d6a74
1481d69fd MOV qword ptr [RBP + -0x68],RDI
1481d6a01 TEST RDI,RDI
1481d6a04 JZ 0x1481d6a10
1481d6a06 MOV RAX,qword ptr [RDI + 0x50]
1481d6a0a MOV qword ptr [RBP + -0x60],RAX
1481d6a0e JMP 0x1481d6a14
1481d6a10 MOV qword ptr [RBP + -0x60],RSI
1481d6a14 MOV dword ptr [RBP + -0x58],0xffffffff
1481d6a1b MOV word ptr [RBP + -0x54],0x101
1481d6a21 MOV byte ptr [RBP + -0x52],0x0
1481d6a25 LEA RCX,[RBP + -0x68]
1481d6a29 CALL 0x1469a93b0
1481d6a2e MOV R14,qword ptr [RBP + -0x60]
1481d6a32 TEST R14,R14
1481d6a35 JZ 0x1481d6a74
1481d6a37 MOV qword ptr [RBP + 0x90],RBX
1481d6a3e MOV RAX,qword ptr [R14 + 0x20]
1481d6a42 MOV qword ptr [RSP + 0x68],RAX
1481d6a47 MOV qword ptr [RBP + 0x98],RAX
1481d6a4e MOV qword ptr [RBP + 0xc8],RBX
1481d6a55 CMP RAX,RBX
1481d6a58 JZ 0x1481d6a77
1481d6a5a MOV RAX,qword ptr [R14 + 0x18]
1481d6a5e MOV qword ptr [RBP + -0x60],RAX
1481d6a62 LEA RCX,[RBP + -0x68]
1481d6a66 CALL 0x1469a93b0
1481d6a6b MOV R14,qword ptr [RBP + -0x60]
1481d6a6f TEST R14,R14
1481d6a72 JNZ 0x1481d6a3e
1481d6a74 MOV R14,RSI
1481d6a77 MOV RAX,qword ptr [R15 + 0x38]
1481d6a7b MOV RDI,qword ptr [RAX + 0x10]
1481d6a7f XOR R8D,R8D
1481d6a82 LEA RDX,[0x14cf7d280]
1481d6a89 LEA RCX,[RBP + -0x48]
1481d6a8d CALL 0x1411a7b80
1481d6a92 MOV RBX,qword ptr [RBP + -0x48]
1481d6a96 MOV qword ptr [RBP + 0xb8],RBX
1481d6a9d MOV qword ptr [RBP + 0xc0],RBX
1481d6aa4 TEST RBX,RBX
1481d6aa7 JZ 0x1481d6b23
1481d6aa9 MOV qword ptr [RSP + 0x78],RDI
1481d6aae TEST RDI,RDI
1481d6ab1 JZ 0x1481d6abd
1481d6ab3 MOV RAX,qword ptr [RDI + 0x50]
1481d6ab7 MOV qword ptr [RBP + -0x80],RAX
1481d6abb JMP 0x1481d6ac1
1481d6abd MOV qword ptr [RBP + -0x80],RSI
1481d6ac1 MOV dword ptr [RBP + -0x78],0xffffffff
1481d6ac8 MOV word ptr [RBP + -0x74],0x101
1481d6ace MOV byte ptr [RBP + -0x72],0x0
1481d6ad2 LEA RCX,[RSP + 0x78]
1481d6ad7 CALL 0x1469a93b0
1481d6adc MOV R15,qword ptr [RBP + -0x80]
1481d6ae0 TEST R15,R15
1481d6ae3 JZ 0x1481d6b23
1481d6ae5 MOV qword ptr [RBP + 0xa0],RBX
1481d6aec MOV RAX,qword ptr [R15 + 0x20]
1481d6af0 MOV qword ptr [RSP + 0x70],RAX
1481d6af5 MOV qword ptr [RBP + 0xa8],RAX
1481d6afc MOV qword ptr [RBP + 0xb0],RBX
1481d6b03 CMP RAX,RBX
1481d6b06 JZ 0x1481d6b26
1481d6b08 MOV RAX,qword ptr [R15 + 0x18]
1481d6b0c MOV qword ptr [RBP + -0x80],RAX
1481d6b10 LEA RCX,[RSP + 0x78]
1481d6b15 CALL 0x1469a93b0
1481d6b1a MOV R15,qword ptr [RBP + -0x80]
1481d6b1e TEST R15,R15
1481d6b21 JNZ 0x1481d6aec
1481d6b23 MOV R15,RSI
1481d6b26 MOVZX EAX,byte ptr [0x14eab53c8]
1481d6b2d CMP AL,0x3
1481d6b2f JC 0x1481d6b6a
1481d6b31 LEA RAX,[0x14cf7d2a0]
1481d6b38 LEA R8,[0x14be6ede0]
1481d6b3f MOV R9,R8
1481d6b42 TEST R15,R15
1481d6b45 CMOVNZ R9,RAX
1481d6b49 TEST R14,R14
1481d6b4c CMOVNZ R8,RAX
1481d6b50 LEA RDX,[0x14cf7cda8]
1481d6b57 LEA RCX,[0x14eab53c8]
1481d6b5e CALL 0x140f24ba0
1481d6b63 MOVZX EAX,byte ptr [0x14eab53c8]
1481d6b6a TEST R14,R14
1481d6b6d JZ 0x1481d754b
1481d6b73 TEST R15,R15
1481d6b76 JZ 0x1481d754b
1481d6b7c MOV RBX,qword ptr [RBP + 0x110]
1481d6b83 MOV RBX,qword ptr [RBX + 0x38]
1481d6b87 MOV qword ptr [RSP + 0x58],RBX
1481d6b8c MOV EAX,dword ptr [R14 + 0x30]
1481d6b90 LEA RCX,[0x14be5bf60]
1481d6b97 TEST EAX,EAX
1481d6b99 JG 0x1481d6bce
1481d6b9b MOV R9,qword ptr [RBP + 0x108]
1481d6ba2 MOV dword ptr [RSP + 0x30],EAX
1481d6ba6 MOV dword ptr [RSP + 0x28],ESI
1481d6baa MOV qword ptr [RSP + 0x20],RCX
1481d6baf MOV R8D,0x26f
1481d6bb5 LEA RDX,[0x14cf63d80]
1481d6bbc LEA RCX,[0x14be5bfd0]
1481d6bc3 CALL 0x140f8dfd0
1481d6bc8 TEST AL,AL
1481d6bca JZ 0x1481d6bce
1481d6bcc NOP
1481d6bcd INT3
1481d6bce TEST RBX,RBX
1481d6bd1 JNZ 0x1481d6bfe
1481d6bd3 MOV R9,qword ptr [RBP + 0x108]
1481d6bda MOV qword ptr [RSP + 0x20],R12
1481d6bdf MOV R8D,0x270
1481d6be5 LEA RDX,[0x14cf63d80]
1481d6bec LEA RCX,[0x14be5c000]
1481d6bf3 CALL 0x140f8dfd0
1481d6bf8 TEST AL,AL
1481d6bfa JZ 0x1481d6bfe
1481d6bfc NOP
1481d6bfd INT3
1481d6bfe MOV RCX,RBX
1481d6c01 CALL 0x1418b7d40
1481d6c06 TEST AL,AL
1481d6c08 JNZ 0x1481d6c35
1481d6c0a MOV R9,qword ptr [RBP + 0x108]
1481d6c11 MOV qword ptr [RSP + 0x20],R12
1481d6c16 MOV R8D,0x274
1481d6c1c LEA RDX,[0x14cf63d80]
1481d6c23 LEA RCX,[0x14be86ec0]
1481d6c2a CALL 0x140f8dfd0
1481d6c2f TEST AL,AL
1481d6c31 JZ 0x1481d6c35
1481d6c33 NOP
1481d6c34 INT3
1481d6c35 CMP qword ptr [RBX + 0x10],0x0
1481d6c3a JNZ 0x1481d6c67
1481d6c3c MOV R9,qword ptr [RBP + 0x108]
1481d6c43 MOV qword ptr [RSP + 0x20],R12
1481d6c48 MOV R8D,0x275
1481d6c4e LEA RDX,[0x14cf63d80]
1481d6c55 LEA RCX,[0x14be86ef0]
1481d6c5c CALL 0x140f8dfd0
1481d6c61 TEST AL,AL
1481d6c63 JZ 0x1481d6c67
1481d6c65 NOP
1481d6c66 INT3
1481d6c67 CALL 0x1416099b0
1481d6c6c MOV RDX,RAX
1481d6c6f LEA RCX,[R14 + 0x10]
1481d6c73 CALL 0x14169bf20
1481d6c78 TEST AL,AL
1481d6c7a JZ 0x1481d6c86
1481d6c7c TEST qword ptr [R14 + 0x10],-0x2
1481d6c84 JNZ 0x1481d6cb1
1481d6c86 MOV R9,qword ptr [RBP + 0x108]
1481d6c8d MOV qword ptr [RSP + 0x20],R12
1481d6c92 MOV R8D,0x276
1481d6c98 LEA RDX,[0x14cf63d80]
1481d6c9f LEA RCX,[0x14be86f20]
1481d6ca6 CALL 0x140f8dfd0
1481d6cab TEST AL,AL
1481d6cad JZ 0x1481d6cb1
1481d6caf NOP
1481d6cb0 INT3
1481d6cb1 CALL 0x1416099b0
1481d6cb6 MOV RDX,RAX
1481d6cb9 LEA RCX,[R14 + 0x10]
1481d6cbd CALL 0x14169bf20
1481d6cc2 TEST AL,AL
1481d6cc4 JZ 0x1481d6cd0
1481d6cc6 MOV RAX,qword ptr [R14 + 0x10]
1481d6cca AND RAX,-0x2
1481d6cce JMP 0x1481d6cd3
1481d6cd0 MOV RAX,RSI
1481d6cd3 MOV RDX,qword ptr [RBX + 0x10]
1481d6cd7 LEA R8,[RAX + 0x30]
1481d6cdb MOVSXD RAX,dword ptr [R8 + 0x8]
1481d6cdf CMP EAX,dword ptr [RDX + 0x38]
1481d6ce2 JG 0x1481d6cf5
1481d6ce4 MOV RCX,RAX
1481d6ce7 MOV RAX,qword ptr [RDX + 0x30]
1481d6ceb CMP qword ptr [RAX + RCX*0x8],R8
1481d6cef JZ 0x1481d6e2a
1481d6cf5 CALL 0x1416099b0
1481d6cfa MOV RDX,RAX
1481d6cfd LEA RCX,[R14 + 0x10]
1481d6d01 CALL 0x14169bf20
1481d6d06 TEST AL,AL
1481d6d08 JZ 0x1481d6d14
1481d6d0a MOV RAX,qword ptr [R14 + 0x10]
1481d6d0e AND RAX,-0x2
1481d6d12 JMP 0x1481d6d17
1481d6d14 MOV RAX,RSI
1481d6d17 MOV RAX,qword ptr [RAX + 0x18]
1481d6d1b MOV qword ptr [RBP + -0x40],RAX
1481d6d1f LEA RDX,[RBP + 0x20]
1481d6d23 LEA RCX,[RBP + -0x40]
1481d6d27 CALL 0x1411de0e0
1481d6d2c NOP
1481d6d2d MOV RSI,R12
1481d6d30 CMP dword ptr [RBP + 0x28],0x0
1481d6d34 CMOVNZ RSI,qword ptr [RBP + 0x20]
1481d6d39 LEA RCX,[R14 + 0x20]
1481d6d3d LEA RDX,[RBP + 0x10]
1481d6d41 CALL 0x1411de0e0
1481d6d46 NOP
1481d6d47 MOV RDI,R12
1481d6d4a CMP dword ptr [RBP + 0x18],0x0
1481d6d4e CMOVNZ RDI,qword ptr [RBP + 0x10]
1481d6d53 MOV RAX,qword ptr [RSP + 0x58]
1481d6d58 MOV RAX,qword ptr [RAX + 0x10]
1481d6d5c MOV RCX,qword ptr [RAX + 0x18]
1481d6d60 MOV qword ptr [RBP + -0x38],RCX
1481d6d64 LEA RDX,[RBP]
1481d6d68 LEA RCX,[RBP + -0x38]
1481d6d6c CALL 0x1411de0e0
1481d6d71 NOP
1481d6d72 MOV RBX,R12
1481d6d75 CMP dword ptr [RBP + 0x8],0x0
1481d6d79 CMOVNZ RBX,qword ptr [RBP]
1481d6d7e MOV RAX,qword ptr [RSP + 0x58]
1481d6d83 MOV RAX,qword ptr [RAX + 0x18]
1481d6d87 MOV qword ptr [RBP + -0x30],RAX
1481d6d8b LEA RDX,[RBP + -0x10]
1481d6d8f LEA RCX,[RBP + -0x30]
1481d6d93 CALL 0x1411de0e0
1481d6d98 NOP
1481d6d99 MOV RAX,R12
1481d6d9c CMP dword ptr [RBP + -0x8],0x0
1481d6da0 CMOVNZ RAX,qword ptr [RBP + -0x10]
1481d6da5 MOV R9,qword ptr [RBP + 0x108]
1481d6dac MOV qword ptr [RSP + 0x40],RSI
1481d6db1 MOV qword ptr [RSP + 0x38],RDI
1481d6db6 MOV qword ptr [RSP + 0x30],RBX
1481d6dbb MOV qword ptr [RSP + 0x28],RAX
1481d6dc0 LEA RAX,[0x14be86f40]
1481d6dc7 MOV qword ptr [RSP + 0x20],RAX
1481d6dcc MOV R8D,0x27d
1481d6dd2 LEA RDX,[0x14cf63d80]
1481d6dd9 LEA RCX,[0x14be86fc8]
1481d6de0 CALL 0x140f8dfd0
1481d6de5 MOVZX EBX,AL
1481d6de8 MOV RCX,qword ptr [RBP + -0x10]
1481d6dec TEST RCX,RCX
1481d6def JZ 0x1481d6df7
1481d6df1 CALL 0x140e282f0
1481d6df6 NOP
1481d6df7 MOV RCX,qword ptr [RBP]
1481d6dfb TEST RCX,RCX
1481d6dfe JZ 0x1481d6e06
1481d6e00 CALL 0x140e282f0
1481d6e05 NOP
1481d6e06 MOV RCX,qword ptr [RBP + 0x10]
1481d6e0a TEST RCX,RCX
1481d6e0d JZ 0x1481d6e15
1481d6e0f CALL 0x140e282f0
1481d6e14 NOP
1481d6e15 MOV RCX,qword ptr [RBP + 0x20]
1481d6e19 TEST RCX,RCX
1481d6e1c JZ 0x1481d6e24
1481d6e1e CALL 0x140e282f0
1481d6e23 NOP
1481d6e24 TEST BL,BL
1481d6e26 JZ 0x1481d6e2a
1481d6e28 NOP
1481d6e29 INT3
1481d6e2a MOVSXD R14,dword ptr [R14 + 0x44]
1481d6e2e ADD R14,qword ptr [RSP + 0x58]
1481d6e33 MOV RAX,qword ptr [RBP + 0x110]
1481d6e3a MOV RDI,qword ptr [RAX + 0x38]
1481d6e3e MOV qword ptr [RSP + 0x58],RDI
1481d6e43 MOV EAX,dword ptr [R15 + 0x30]
1481d6e47 TEST EAX,EAX
1481d6e49 JG 0x1481d6e89
1481d6e4b MOV R9,qword ptr [RBP + 0x108]
1481d6e52 MOV dword ptr [RSP + 0x30],EAX
1481d6e56 MOV dword ptr [RSP + 0x28],0x0
1481d6e5e LEA RAX,[0x14be5bf60]
1481d6e65 MOV qword ptr [RSP + 0x20],RAX
1481d6e6a MOV R8D,0x26f
1481d6e70 LEA RDX,[0x14cf63d80]
1481d6e77 LEA RCX,[0x14be5bfd0]
1481d6e7e CALL 0x140f8dfd0
1481d6e83 TEST AL,AL
1481d6e85 JZ 0x1481d6e89
1481d6e87 NOP
1481d6e88 INT3
1481d6e89 TEST RDI,RDI
1481d6e8c JNZ 0x1481d6eb9
1481d6e8e MOV R9,qword ptr [RBP + 0x108]
1481d6e95 MOV qword ptr [RSP + 0x20],R12
1481d6e9a MOV R8D,0x270
1481d6ea0 LEA RDX,[0x14cf63d80]
1481d6ea7 LEA RCX,[0x14be5c000]
1481d6eae CALL 0x140f8dfd0
1481d6eb3 TEST AL,AL
1481d6eb5 JZ 0x1481d6eb9
1481d6eb7 NOP
1481d6eb8 INT3
1481d6eb9 MOV RCX,RDI
1481d6ebc CALL 0x1418b7d40
1481d6ec1 TEST AL,AL
1481d6ec3 JNZ 0x1481d6ef0
1481d6ec5 MOV R9,qword ptr [RBP + 0x108]
1481d6ecc MOV qword ptr [RSP + 0x20],R12
1481d6ed1 MOV R8D,0x274
1481d6ed7 LEA RDX,[0x14cf63d80]
1481d6ede LEA RCX,[0x14be86ec0]
1481d6ee5 CALL 0x140f8dfd0
1481d6eea TEST AL,AL
1481d6eec JZ 0x1481d6ef0
1481d6eee NOP
1481d6eef INT3
1481d6ef0 CMP qword ptr [RDI + 0x10],0x0
1481d6ef5 JNZ 0x1481d6f22
1481d6ef7 MOV R9,qword ptr [RBP + 0x108]
1481d6efe MOV qword ptr [RSP + 0x20],R12
1481d6f03 MOV R8D,0x275
1481d6f09 LEA RDX,[0x14cf63d80]
1481d6f10 LEA RCX,[0x14be86ef0]
1481d6f17 CALL 0x140f8dfd0
1481d6f1c TEST AL,AL
1481d6f1e JZ 0x1481d6f22
1481d6f20 NOP
1481d6f21 INT3
1481d6f22 CALL 0x1416099b0
1481d6f27 MOV RDX,RAX
1481d6f2a LEA RCX,[R15 + 0x10]
1481d6f2e CALL 0x14169bf20
1481d6f33 TEST AL,AL
1481d6f35 JZ 0x1481d6f41
1481d6f37 TEST qword ptr [R15 + 0x10],-0x2
1481d6f3f JNZ 0x1481d6f6c
1481d6f41 MOV R9,qword ptr [RBP + 0x108]
1481d6f48 MOV qword ptr [RSP + 0x20],R12
1481d6f4d MOV R8D,0x276
1481d6f53 LEA RDX,[0x14cf63d80]
1481d6f5a LEA RCX,[0x14be86f20]
1481d6f61 CALL 0x140f8dfd0
1481d6f66 TEST AL,AL
1481d6f68 JZ 0x1481d6f6c
1481d6f6a NOP
1481d6f6b INT3
1481d6f6c CALL 0x1416099b0
1481d6f71 MOV RDX,RAX
1481d6f74 LEA RCX,[R15 + 0x10]
1481d6f78 CALL 0x14169bf20
1481d6f7d TEST AL,AL
1481d6f7f JZ 0x1481d6f8b
1481d6f81 MOV RAX,qword ptr [R15 + 0x10]
1481d6f85 AND RAX,-0x2
1481d6f89 JMP 0x1481d6f8d
1481d6f8b XOR EAX,EAX
1481d6f8d MOV RDX,qword ptr [RDI + 0x10]
1481d6f91 LEA R8,[RAX + 0x30]
1481d6f95 MOVSXD RAX,dword ptr [R8 + 0x8]
1481d6f99 CMP EAX,dword ptr [RDX + 0x38]
1481d6f9c JG 0x1481d6faf
1481d6f9e MOV RCX,RAX
1481d6fa1 MOV RAX,qword ptr [RDX + 0x30]
1481d6fa5 CMP qword ptr [RAX + RCX*0x8],R8
1481d6fa9 JZ 0x1481d70e3
1481d6faf CALL 0x1416099b0
1481d6fb4 MOV RDX,RAX
1481d6fb7 LEA RCX,[R15 + 0x10]
1481d6fbb CALL 0x14169bf20
1481d6fc0 TEST AL,AL
1481d6fc2 JZ 0x1481d6fce
1481d6fc4 MOV RAX,qword ptr [R15 + 0x10]
1481d6fc8 AND RAX,-0x2
1481d6fcc JMP 0x1481d6fd0
1481d6fce XOR EAX,EAX
1481d6fd0 MOV RAX,qword ptr [RAX + 0x18]
1481d6fd4 MOV qword ptr [RBP + -0x28],RAX
1481d6fd8 LEA RDX,[RBP + 0x60]
1481d6fdc LEA RCX,[RBP + -0x28]
1481d6fe0 CALL 0x1411de0e0
1481d6fe5 NOP
1481d6fe6 MOV RSI,R12
1481d6fe9 CMP dword ptr [RBP + 0x68],0x0
1481d6fed CMOVNZ RSI,qword ptr [RBP + 0x60]
1481d6ff2 LEA RCX,[R15 + 0x20]
1481d6ff6 LEA RDX,[RBP + 0x50]
1481d6ffa CALL 0x1411de0e0
1481d6fff NOP
1481d7000 MOV RDI,R12
1481d7003 CMP dword ptr [RBP + 0x58],0x0
1481d7007 CMOVNZ RDI,qword ptr [RBP + 0x50]
1481d700c MOV RAX,qword ptr [RSP + 0x58]
1481d7011 MOV RAX,qword ptr [RAX + 0x10]
1481d7015 MOV RCX,qword ptr [RAX + 0x18]
1481d7019 MOV qword ptr [RBP + -0x20],RCX
1481d701d LEA RDX,[RBP + 0x40]
1481d7021 LEA RCX,[RBP + -0x20]
1481d7025 CALL 0x1411de0e0
1481d702a NOP
1481d702b MOV RBX,R12
1481d702e CMP dword ptr [RBP + 0x48],0x0
1481d7032 CMOVNZ RBX,qword ptr [RBP + 0x40]
1481d7037 MOV RAX,qword ptr [RSP + 0x58]
1481d703c MOV RAX,qword ptr [RAX + 0x18]
1481d7040 MOV qword ptr [RBP + -0x18],RAX
1481d7044 LEA RDX,[RBP + 0x30]
1481d7048 LEA RCX,[RBP + -0x18]
1481d704c CALL 0x1411de0e0
1481d7051 NOP
1481d7052 MOV RAX,R12
1481d7055 CMP dword ptr [RBP + 0x38],0x0
1481d7059 CMOVNZ RAX,qword ptr [RBP + 0x30]
1481d705e MOV R9,qword ptr [RBP + 0x108]
1481d7065 MOV qword ptr [RSP + 0x40],RSI
1481d706a MOV qword ptr [RSP + 0x38],RDI
1481d706f MOV qword ptr [RSP + 0x30],RBX
1481d7074 MOV qword ptr [RSP + 0x28],RAX
1481d7079 LEA RAX,[0x14be86f40]
1481d7080 MOV qword ptr [RSP + 0x20],RAX
1481d7085 MOV R8D,0x27d
1481d708b LEA RDX,[0x14cf63d80]
1481d7092 LEA RCX,[0x14be86fc8]
1481d7099 CALL 0x140f8dfd0
1481d709e MOVZX EBX,AL
1481d70a1 MOV RCX,qword ptr [RBP + 0x30]
1481d70a5 TEST RCX,RCX
1481d70a8 JZ 0x1481d70b0
1481d70aa CALL 0x140e282f0
1481d70af NOP
1481d70b0 MOV RCX,qword ptr [RBP + 0x40]
1481d70b4 TEST RCX,RCX
1481d70b7 JZ 0x1481d70bf
1481d70b9 CALL 0x140e282f0
1481d70be NOP
1481d70bf MOV RCX,qword ptr [RBP + 0x50]
1481d70c3 TEST RCX,RCX
1481d70c6 JZ 0x1481d70ce
1481d70c8 CALL 0x140e282f0
1481d70cd NOP
1481d70ce MOV RCX,qword ptr [RBP + 0x60]
1481d70d2 TEST RCX,RCX
1481d70d5 JZ 0x1481d70dd
1481d70d7 CALL 0x140e282f0
1481d70dc NOP
1481d70dd TEST BL,BL
1481d70df JZ 0x1481d70e3
1481d70e1 NOP
1481d70e2 INT3
1481d70e3 MOVSXD RDI,dword ptr [R15 + 0x44]
1481d70e7 ADD RDI,qword ptr [RSP + 0x58]
1481d70ec CMP byte ptr [0x14eab53c8],0x3
1481d70f3 JC 0x1481d710e
1481d70f5 MOV R9,RDI
1481d70f8 MOV R8,R14
1481d70fb LEA RDX,[0x14cf7cec0]
1481d7102 LEA RCX,[0x14eab53c8]
1481d7109 CALL 0x140f24ba0
1481d710e TEST R14,R14
1481d7111 JZ 0x1481d752d
1481d7117 TEST RDI,RDI
1481d711a JZ 0x1481d752d
1481d7120 CMP byte ptr [0x14eab53c8],0x3
1481d7127 JC 0x1481d713c
1481d7129 LEA RDX,[0x14cf7cfc8]
1481d7130 LEA RCX,[0x14eab53c8]
1481d7137 CALL 0x140f24ba0
1481d713c MOV RBX,qword ptr [R14]
1481d713f MOVSXD R15,dword ptr [R14 + 0x8]
1481d7143 MOV RSI,R15
1481d7146 SHL RSI,0x4
1481d714a ADD RSI,RBX
1481d714d NOP dword ptr [RAX]
1481d7150 CMP dword ptr [R14 + 0x8],R15D
1481d7154 JZ 0x1481d716f
1481d7156 MOV byte ptr [RBP + 0x120],0x0
1481d715d LEA RCX,[RBP + 0x120]
1481d7164 CALL 0x14bae4c30
1481d7169 TEST AL,AL
1481d716b JZ 0x1481d716f
1481d716d NOP
1481d716e INT3
1481d716f CMP RBX,RSI
1481d7172 JZ 0x1481d71a4
1481d7174 CMP byte ptr [0x14eab53c8],0x3
1481d717b JC 0x1481d719e
1481d717d CMP dword ptr [RBX + 0x8],0x0
1481d7181 JZ 0x1481d7188
1481d7183 MOV R8,qword ptr [RBX]
1481d7186 JMP 0x1481d718b
1481d7188 MOV R8,R12
1481d718b LEA RDX,[0x14cf7d030]
1481d7192 LEA RCX,[0x14eab53c8]
1481d7199 CALL 0x140f24ba0
1481d719e ADD RBX,0x10
1481d71a2 JMP 0x1481d7150
1481d71a4 CMP byte ptr [0x14eab53c8],0x3
1481d71ab JC 0x1481d71c0
1481d71ad LEA RDX,[0x14cf7d050]
1481d71b4 LEA RCX,[0x14eab53c8]
1481d71bb CALL 0x140f24ba0
1481d71c0 MOV RBX,qword ptr [RDI]
1481d71c3 MOVSXD R15,dword ptr [RDI + 0x8]
1481d71c7 MOV RSI,R15
1481d71ca SHL RSI,0x4
1481d71ce ADD RSI,RBX
1481d71d1 CMP dword ptr [RDI + 0x8],R15D
1481d71d5 JZ 0x1481d71f0
1481d71d7 MOV byte ptr [RBP + 0x128],0x0
1481d71de LEA RCX,[RBP + 0x128]
1481d71e5 CALL 0x14bae4c30
1481d71ea TEST AL,AL
1481d71ec JZ 0x1481d71f0
1481d71ee NOP
1481d71ef INT3
1481d71f0 CMP RBX,RSI
1481d71f3 JZ 0x1481d7225
1481d71f5 CMP byte ptr [0x14eab53c8],0x3
1481d71fc JC 0x1481d721f
1481d71fe CMP dword ptr [RBX + 0x8],0x0
1481d7202 JZ 0x1481d7209
1481d7204 MOV R8,qword ptr [RBX]
1481d7207 JMP 0x1481d720c
1481d7209 MOV R8,R12
1481d720c LEA RDX,[0x14cf7d0b0]
1481d7213 LEA RCX,[0x14eab53c8]
1481d721a CALL 0x140f24ba0
1481d721f ADD RBX,0x10
1481d7223 JMP 0x1481d71d1
1481d7225 MOV RDX,R13
1481d7228 MOV RCX,R14
1481d722b CALL 0x140e6d810
1481d7230 LEA RBX,[0x14bce6d80]
1481d7237 TEST AL,AL
1481d7239 JNZ 0x1481d7318
1481d723f MOV RCX,qword ptr [R14]
1481d7242 CMP R13,RCX
1481d7245 JC 0x1481d72a6
1481d7247 MOVSXD RDX,dword ptr [R14 + 0xc]
1481d724b MOV RAX,RDX
1481d724e SHL RAX,0x4
1481d7252 ADD RAX,RCX
1481d7255 CMP R13,RAX
1481d7258 JNC 0x1481d72a6
1481d725a MOVSXD RAX,dword ptr [R14 + 0x8]
1481d725e MOV R9,qword ptr [RBP + 0x108]
1481d7265 MOV qword ptr [RSP + 0x48],0x10
1481d726e MOV qword ptr [RSP + 0x40],RAX
1481d7273 MOV qword ptr [RSP + 0x38],RDX
1481d7278 MOV qword ptr [RSP + 0x30],RCX
1481d727d MOV qword ptr [RSP + 0x28],R13
1481d7282 MOV qword ptr [RSP + 0x20],RBX
1481d7287 MOV R8D,0x63e
1481d728d LEA RDX,[0x14cf27ac0]
1481d7294 LEA RCX,[0x14bce6eb8]
1481d729b CALL 0x140f8dfd0
1481d72a0 TEST AL,AL
1481d72a2 JZ 0x1481d72a6
1481d72a4 NOP
1481d72a5 INT3
1481d72a6 MOVSXD RBX,dword ptr [R14 + 0x8]
1481d72aa LEA EAX,[RBX + 0x1]
1481d72ad MOV dword ptr [R14 + 0x8],EAX
1481d72b1 CMP EAX,dword ptr [R14 + 0xc]
1481d72b5 JBE 0x1481d72c1
1481d72b7 MOV EDX,EBX
1481d72b9 MOV RCX,R14
1481d72bc CALL 0x140ca4b30
1481d72c1 SHL RBX,0x4
1481d72c5 ADD RBX,qword ptr [R14]
1481d72c8 MOV qword ptr [RBP + -0x70],RBX
1481d72cc XOR ECX,ECX
1481d72ce MOV qword ptr [RBX],RCX
1481d72d1 MOV R15,qword ptr [RSP + 0x60]
1481d72d6 MOVSXD RSI,dword ptr [R15]
1481d72d9 MOV RAX,qword ptr [R13]
1481d72dd MOV qword ptr [RSP + 0x58],RAX
1481d72e2 MOV dword ptr [RBX + 0x8],ESI
1481d72e5 TEST ESI,ESI
1481d72e7 JNZ 0x1481d72ee
1481d72e9 MOV dword ptr [RBX + 0xc],ECX
1481d72ec JMP 0x1481d730f
1481d72ee XOR R8D,R8D
1481d72f1 MOV EDX,ESI
1481d72f3 MOV RCX,RBX
1481d72f6 CALL 0x140ca39a0
1481d72fb MOV R8,RSI
1481d72fe ADD R8,R8
1481d7301 MOV RDX,qword ptr [RSP + 0x58]
1481d7306 MOV RCX,qword ptr [RBX]
1481d7309 CALL 0x14b89502e
1481d730e NOP
1481d730f LEA RBX,[0x14bce6d80]
1481d7316 JMP 0x1481d731d
1481d7318 MOV R15,qword ptr [RSP + 0x60]
1481d731d MOV RDX,R13
1481d7320 MOV RCX,RDI
1481d7323 CALL 0x140e6d810
1481d7328 TEST AL,AL
1481d732a JNZ 0x1481d73f2
1481d7330 MOV R10,qword ptr [RDI]
1481d7333 CMP R13,R10
1481d7336 JC 0x1481d7397
1481d7338 MOVSXD R11,dword ptr [RDI + 0xc]
1481d733c MOV RAX,R11
1481d733f SHL RAX,0x4
1481d7343 ADD RAX,R10
1481d7346 CMP R13,RAX
1481d7349 JNC 0x1481d7397
1481d734b MOVSXD RAX,dword ptr [RDI + 0x8]
1481d734f MOV R9,qword ptr [RBP + 0x108]
1481d7356 MOV qword ptr [RSP + 0x48],0x10
1481d735f MOV qword ptr [RSP + 0x40],RAX
1481d7364 MOV qword ptr [RSP + 0x38],R11
1481d7369 MOV qword ptr [RSP + 0x30],R10
1481d736e MOV qword ptr [RSP + 0x28],R13
1481d7373 MOV qword ptr [RSP + 0x20],RBX
1481d7378 MOV R8D,0x63e
1481d737e LEA RDX,[0x14cf27ac0]
1481d7385 LEA RCX,[0x14bce6eb8]
1481d738c CALL 0x140f8dfd0
1481d7391 TEST AL,AL
1481d7393 JZ 0x1481d7397
1481d7395 NOP
1481d7396 INT3
1481d7397 MOVSXD RBX,dword ptr [RDI + 0x8]
1481d739b LEA EAX,[RBX + 0x1]
1481d739e MOV dword ptr [RDI + 0x8],EAX
1481d73a1 CMP EAX,dword ptr [RDI + 0xc]
1481d73a4 JBE 0x1481d73b0
1481d73a6 MOV EDX,EBX
1481d73a8 MOV RCX,RDI
1481d73ab CALL 0x140ca4b30
1481d73b0 SHL RBX,0x4
1481d73b4 ADD RBX,qword ptr [RDI]
1481d73b7 MOV qword ptr [RBP + -0x70],RBX
1481d73bb XOR EAX,EAX
1481d73bd MOV qword ptr [RBX],RAX
1481d73c0 MOVSXD RSI,dword ptr [R15]
1481d73c3 MOV R15,qword ptr [R13]
1481d73c7 MOV dword ptr [RBX + 0x8],ESI
1481d73ca TEST ESI,ESI
1481d73cc JNZ 0x1481d73d3
1481d73ce MOV dword ptr [RBX + 0xc],EAX
1481d73d1 JMP 0x1481d73f2
1481d73d3 XOR R8D,R8D
1481d73d6 MOV EDX,ESI
1481d73d8 MOV RCX,RBX
1481d73db CALL 0x140ca39a0
1481d73e0 MOV R8,RSI
1481d73e3 ADD R8,R8
1481d73e6 MOV RDX,R15
1481d73e9 MOV RCX,qword ptr [RBX]
1481d73ec CALL 0x14b89502e
1481d73f1 NOP
1481d73f2 CMP byte ptr [0x14eab53c8],0x3
1481d73f9 JC 0x1481d740e
1481d73fb LEA RDX,[0x14cf7d0d0]
1481d7402 LEA RCX,[0x14eab53c8]
1481d7409 CALL 0x140f24ba0
1481d740e MOV RBX,qword ptr [R14]
1481d7411 MOVSXD R15,dword ptr [R14 + 0x8]
1481d7415 MOV RSI,R15
1481d7418 SHL RSI,0x4
1481d741c ADD RSI,RBX
1481d741f NOP
1481d7420 CMP dword ptr [R14 + 0x8],R15D
1481d7424 JZ 0x1481d743b
1481d7426 MOV byte ptr [RSP + 0x50],0x0
1481d742b LEA RCX,[RSP + 0x50]
1481d7430 CALL 0x14bae4c30
1481d7435 TEST AL,AL
1481d7437 JZ 0x1481d743b
1481d7439 NOP
1481d743a INT3
1481d743b CMP RBX,RSI
1481d743e JZ 0x1481d7470
1481d7440 CMP byte ptr [0x14eab53c8],0x3
1481d7447 JC 0x1481d746a
1481d7449 CMP dword ptr [RBX + 0x8],0x0
1481d744d JZ 0x1481d7454
1481d744f MOV R8,qword ptr [RBX]
1481d7452 JMP 0x1481d7457
1481d7454 MOV R8,R12
1481d7457 LEA RDX,[0x14cf7d130]
1481d745e LEA RCX,[0x14eab53c8]
1481d7465 CALL 0x140f24ba0
1481d746a ADD RBX,0x10
1481d746e JMP 0x1481d7420
1481d7470 CMP byte ptr [0x14eab53c8],0x3
1481d7477 JC 0x1481d748c
1481d7479 LEA RDX,[0x14cf7d150]
1481d7480 LEA RCX,[0x14eab53c8]
1481d7487 CALL 0x140f24ba0
1481d748c MOV RBX,qword ptr [RDI]
1481d748f MOVSXD R14,dword ptr [RDI + 0x8]
1481d7493 MOV RSI,R14
1481d7496 SHL RSI,0x4
1481d749a ADD RSI,RBX
1481d749d NOP dword ptr [RAX]
1481d74a0 CMP dword ptr [RDI + 0x8],R14D
1481d74a4 JZ 0x1481d74bb
1481d74a6 MOV byte ptr [RSP + 0x51],0x0
1481d74ab LEA RCX,[RSP + 0x51]
1481d74b0 CALL 0x14bae4c30
1481d74b5 TEST AL,AL
1481d74b7 JZ 0x1481d74bb
1481d74b9 NOP
1481d74ba INT3
1481d74bb CMP RBX,RSI
1481d74be JZ 0x1481d74f0
1481d74c0 CMP byte ptr [0x14eab53c8],0x3
1481d74c7 JC 0x1481d74ea
1481d74c9 CMP dword ptr [RBX + 0x8],0x0
1481d74cd JZ 0x1481d74d4
1481d74cf MOV R8,qword ptr [RBX]
1481d74d2 JMP 0x1481d74d7
1481d74d4 MOV R8,R12
1481d74d7 LEA RDX,[0x14cf7d1b0]
1481d74de LEA RCX,[0x14eab53c8]
1481d74e5 CALL 0x140f24ba0
1481d74ea ADD RBX,0x10
1481d74ee JMP 0x1481d74a0
1481d74f0 MOV RCX,qword ptr [RBP + 0x110]
1481d74f7 CALL 0x1481d5fb0
1481d74fc CMP byte ptr [0x14eab53c8],0x3
1481d7503 JC 0x1481d7529
1481d7505 MOV RAX,qword ptr [RSP + 0x60]
1481d750a CMP dword ptr [RAX],0x0
1481d750d JZ 0x1481d7513
1481d750f MOV R12,qword ptr [R13]
1481d7513 MOV R8,R12
1481d7516 LEA RDX,[0x14cf7d1d0]
1481d751d LEA RCX,[0x14eab53c8]
1481d7524 CALL 0x140f24ba0
1481d7529 MOV BL,0x1
1481d752b JMP 0x1481d758e
1481d752d CMP byte ptr [0x14eab53c8],0x2
1481d7534 JC 0x1481d758c
1481d7536 LEA RDX,[0x14cf7cf38]
1481d753d LEA RCX,[0x14eab53c8]
1481d7544 CALL 0x140f24ba0
1481d7549 JMP 0x1481d758c
1481d754b CMP AL,0x2
1481d754d JC 0x1481d758c
1481d754f LEA RDX,[0x14cf7ce28]
1481d7556 LEA RCX,[0x14eab53c8]
1481d755d CALL 0x140f24ba0
1481d7562 JMP 0x1481d758c
1481d7564 CMP byte ptr [0x14eab53c8],0x2
1481d756b JC 0x1481d758c
1481d756d CMP dword ptr [RSI],0x0
1481d7570 JZ 0x1481d7576
1481d7572 MOV R12,qword ptr [R13]
1481d7576 MOV R8,R12
1481d7579 LEA RDX,[0x14cf7cbe0]
1481d7580 LEA RCX,[0x14eab53c8]
1481d7587 CALL 0x140f24ba0
1481d758c XOR BL,BL
1481d758e LEA RCX,[RBP + 0x70]
1481d7592 CALL 0x148141b60
1481d7597 MOVZX EAX,BL
1481d759a MOV RBX,qword ptr [RSP + 0x218]
1481d75a2 ADD RSP,0x1d0
1481d75a9 POP R15
1481d75ab POP R14
1481d75ad POP R13
1481d75af POP R12
1481d75b1 POP RDI
1481d75b2 POP RSI
1481d75b3 POP RBP
1481d75b4 RET
*/

/* 1481d57b0 IsPackUnlocked */

ulonglong IsPackUnlocked(longlong param_1,undefined8 *param_2)

{
  int iVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  byte bVar5;
  char cVar6;
  ulonglong in_RAX;
  ulonglong uVar7;
  undefined8 uVar8;
  ulonglong uVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined8 *puVar13;
  undefined8 *puVar14;
  undefined *puVar15;
  undefined8 *puVar16;
  undefined *puVar17;
  byte bVar18;
  undefined8 unaff_retaddr;
  undefined1 auStackX_8 [8];
  undefined8 *puStackX_10;
  ulonglong uStackX_18;
  ulonglong uStackX_20;
  ulonglong in_stack_fffffffffffffef0;
  longlong lStack_e8;
  longlong lStack_e0;
  undefined4 uStack_d8;
  undefined2 uStack_d4;
  undefined1 uStack_d2;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined *puStack_b8;
  int iStack_b0;
  undefined *puStack_a8;
  int iStack_a0;
  undefined *puStack_98;
  int iStack_90;
  undefined *puStack_88;
  int iStack_80;
  ulonglong uStack_78;
  ulonglong uStack_70;
  ulonglong uStack_68;
  ulonglong uStack_60;
  ulonglong uStack_58;
  
  uVar7 = 0;
  puStackX_10 = param_2;
  if (*(longlong *)(param_1 + 0x38) == 0) {
    if (DAT_14eab53c8 < 2) goto LAB_1481d58af;
    puVar11 = &UNK_14cf7d2b0;
  }
  else {
    lVar2 = *(longlong *)(*(longlong *)(param_1 + 0x38) + 0x10);
    in_RAX = func_0x0001411a7b80(&uStackX_20,L"UnlockedPacks",0);
    uStack_78 = uStackX_20;
    uStack_70 = uStackX_20;
    if (uStackX_20 != 0) {
      if (lVar2 == 0) {
        lStack_e0 = 0;
      }
      else {
        lStack_e0 = *(longlong *)(lVar2 + 0x50);
      }
      uStack_d8 = 0xffffffff;
      uStack_d4 = 0x101;
      uStack_d2 = 0;
      lStack_e8 = lVar2;
      in_RAX = func_0x0001469a93b0(&lStack_e8);
      if (lStack_e0 != 0) {
        uStack_68 = uStackX_20;
        do {
          lVar2 = lStack_e0;
          in_RAX = *(ulonglong *)(lStack_e0 + 0x20);
          uStack_58 = uStackX_20;
          uStackX_18 = in_RAX;
          uStack_60 = in_RAX;
          if (in_RAX == uStackX_20) {
            if (lStack_e0 != 0) {
              lVar3 = *(longlong *)(param_1 + 0x38);
              if ((*(int *)(lStack_e0 + 0x30) < 1) &&
                 (cVar6 = func_0x000140f8dfd0(&UNK_14be5bfd0,
                                              "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                              ,0x26f,unaff_retaddr,&UNK_14be5bf60,
                                              in_stack_fffffffffffffef0 & 0xffffffff00000000,
                                              *(int *)(lStack_e0 + 0x30)), cVar6 != '\0')) {
                pcVar4 = (code *)swi(3);
                uVar7 = (*pcVar4)();
                return uVar7;
              }
              puVar11 = &UNK_14bce4e94;
              if ((lVar3 == 0) &&
                 (cVar6 = func_0x000140f8dfd0(&UNK_14be5c000,
                                              "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                              ,0x270,unaff_retaddr,&UNK_14bce4e94), cVar6 != '\0'))
              {
                pcVar4 = (code *)swi(3);
                uVar7 = (*pcVar4)();
                return uVar7;
              }
              cVar6 = func_0x0001418b7d40(lVar3);
              if ((cVar6 == '\0') &&
                 (cVar6 = func_0x000140f8dfd0(&UNK_14be86ec0,
                                              "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                              ,0x274,unaff_retaddr,&UNK_14bce4e94), cVar6 != '\0'))
              {
                pcVar4 = (code *)swi(3);
                uVar7 = (*pcVar4)();
                return uVar7;
              }
              if ((*(longlong *)(lVar3 + 0x10) == 0) &&
                 (cVar6 = func_0x000140f8dfd0(&UNK_14be86ef0,
                                              "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                              ,0x275,unaff_retaddr,&UNK_14bce4e94), cVar6 != '\0'))
              {
                pcVar4 = (code *)swi(3);
                uVar7 = (*pcVar4)();
                return uVar7;
              }
              uVar8 = func_0x0001416099b0();
              cVar6 = func_0x00014169bf20(lVar2 + 0x10,uVar8);
              if (((cVar6 == '\0') || ((*(ulonglong *)(lVar2 + 0x10) & 0xfffffffffffffffe) == 0)) &&
                 (cVar6 = func_0x000140f8dfd0(&UNK_14be86f20,
                                              "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                              ,0x276,unaff_retaddr,&UNK_14bce4e94), cVar6 != '\0'))
              {
                pcVar4 = (code *)swi(3);
                uVar7 = (*pcVar4)();
                return uVar7;
              }
              uVar8 = func_0x0001416099b0();
              cVar6 = func_0x00014169bf20(lVar2 + 0x10,uVar8);
              uVar9 = uVar7;
              if (cVar6 != '\0') {
                uVar9 = *(ulonglong *)(lVar2 + 0x10) & 0xfffffffffffffffe;
              }
              if ((*(int *)(*(longlong *)(lVar3 + 0x10) + 0x38) < *(int *)(uVar9 + 0x38)) ||
                 (*(longlong *)
                   (*(longlong *)(*(longlong *)(lVar3 + 0x10) + 0x30) +
                   (longlong)*(int *)(uVar9 + 0x38) * 8) != uVar9 + 0x30)) {
                uVar8 = func_0x0001416099b0();
                cVar6 = func_0x00014169bf20(lVar2 + 0x10,uVar8);
                if (cVar6 != '\0') {
                  uVar7 = *(ulonglong *)(lVar2 + 0x10) & 0xfffffffffffffffe;
                }
                uStack_d0 = *(undefined8 *)(uVar7 + 0x18);
                func_0x0001411de0e0(&uStack_d0,&puStack_88);
                puVar17 = &UNK_14bce4e94;
                if (iStack_80 != 0) {
                  puVar17 = puStack_88;
                }
                func_0x0001411de0e0(lVar2 + 0x20,&puStack_98);
                puVar15 = &UNK_14bce4e94;
                if (iStack_90 != 0) {
                  puVar15 = puStack_98;
                }
                uStack_c8 = *(undefined8 *)(*(longlong *)(lVar3 + 0x10) + 0x18);
                func_0x0001411de0e0(&uStack_c8,&puStack_a8);
                puVar12 = &UNK_14bce4e94;
                if (iStack_a0 != 0) {
                  puVar12 = puStack_a8;
                }
                uStack_c0 = *(undefined8 *)(lVar3 + 0x18);
                func_0x0001411de0e0(&uStack_c0,&puStack_b8);
                puVar10 = &UNK_14bce4e94;
                if (iStack_b0 != 0) {
                  puVar10 = puStack_b8;
                }
                cVar6 = func_0x000140f8dfd0(&UNK_14be86fc8,
                                            "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\CoreUObject\\Public\\UObject\\UnrealType.h"
                                            ,0x27d,unaff_retaddr,&UNK_14be86f40,puVar10,puVar12,
                                            puVar15,puVar17);
                if (puStack_b8 != (undefined *)0x0) {
                  func_0x000140e282f0();
                }
                if (puStack_a8 != (undefined *)0x0) {
                  func_0x000140e282f0();
                }
                if (puStack_98 != (undefined *)0x0) {
                  func_0x000140e282f0();
                }
                if (puStack_88 != (undefined *)0x0) {
                  func_0x000140e282f0();
                }
                if (cVar6 != '\0') {
                  pcVar4 = (code *)swi(3);
                  uVar7 = (*pcVar4)();
                  return uVar7;
                }
              }
              puVar16 = (undefined8 *)(*(int *)(lVar2 + 0x44) + lVar3);
              if ((puVar16 == (undefined8 *)0x0) ||
                 (cVar6 = func_0x000140e6d810(puVar16,param_2), cVar6 == '\0')) {
                bVar18 = 0;
                bVar5 = 0;
                if (puVar16 == (undefined8 *)0x0) {
                  if (1 < DAT_14eab53c8) {
                    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7d460);
                  }
                  goto LAB_1481d5c20;
                }
              }
              else {
                bVar5 = 1;
              }
              bVar18 = bVar5;
              if (2 < DAT_14eab53c8) {
                func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7d3b0,*(undefined4 *)(puVar16 + 1));
              }
              puVar13 = (undefined8 *)*puVar16;
              iVar1 = *(int *)(puVar16 + 1);
              puVar14 = puVar13 + (longlong)iVar1 * 2;
              while( true ) {
                if (*(int *)(puVar16 + 1) != iVar1) {
                  auStackX_8[0] = 0;
                  cVar6 = func_0x00014bae4170(auStackX_8);
                  if (cVar6 != '\0') {
                    pcVar4 = (code *)swi(3);
                    uVar7 = (*pcVar4)();
                    return uVar7;
                  }
                }
                param_2 = puStackX_10;
                if (puVar13 == puVar14) break;
                if (2 < DAT_14eab53c8) {
                  if (*(int *)(puVar13 + 1) == 0) {
                    puVar17 = &UNK_14bce4e94;
                  }
                  else {
                    puVar17 = (undefined *)*puVar13;
                  }
                  func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7d440,puVar17);
                }
                puVar13 = puVar13 + 2;
              }
LAB_1481d5c20:
              if (2 < DAT_14eab53c8) {
                if (*(int *)(param_2 + 1) != 0) {
                  puVar11 = (undefined *)*param_2;
                }
                puVar17 = &UNK_14ca022f0;
                if (bVar18 != 0) {
                  puVar17 = &UNK_14ca022e8;
                }
                func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7d4d8,puVar11,puVar17);
              }
              return (ulonglong)bVar18;
            }
            break;
          }
          lStack_e0 = *(longlong *)(lStack_e0 + 0x18);
          in_RAX = func_0x0001469a93b0(&lStack_e8);
        } while (lStack_e0 != 0);
      }
    }
    if (DAT_14eab53c8 < 2) goto LAB_1481d58af;
    puVar11 = &UNK_14cf7d328;
  }
  in_RAX = func_0x000140f24ba0(&DAT_14eab53c8,puVar11);
LAB_1481d58af:
  return in_RAX & 0xffffffffffffff00;
}


/* Instruction evidence:
1481d57b0 MOV qword ptr [RSP + 0x10],RDX
1481d57b5 PUSH RBP
1481d57b6 PUSH RBX
1481d57b7 PUSH RSI
1481d57b8 PUSH RDI
1481d57b9 PUSH R12
1481d57bb PUSH R13
1481d57bd PUSH R14
1481d57bf PUSH R15
1481d57c1 LEA RBP,[RSP + -0x1f]
1481d57c6 SUB RSP,0xf8
1481d57cd MOV R12,RDX
1481d57d0 MOV R13,RCX
1481d57d3 XOR EBX,EBX
1481d57d5 MOV RSI,qword ptr [RCX + 0x38]
1481d57d9 TEST RSI,RSI
1481d57dc JNZ 0x1481d57f7
1481d57de CMP byte ptr [0x14eab53c8],0x2
1481d57e5 JC 0x1481d58af
1481d57eb LEA RDX,[0x14cf7d2b0]
1481d57f2 JMP 0x1481d58a3
1481d57f7 MOV RSI,qword ptr [RSI + 0x10]
1481d57fb XOR R8D,R8D
1481d57fe LEA RDX,[0x14cf7d260]
1481d5805 LEA RCX,[RBP + 0x7f]
1481d5809 CALL 0x1411a7b80
1481d580e MOV RDI,qword ptr [RBP + 0x7f]
1481d5812 MOV qword ptr [RBP + -0x19],RDI
1481d5816 MOV qword ptr [RBP + -0x11],RDI
1481d581a TEST RDI,RDI
1481d581d JZ 0x1481d5893
1481d581f MOV qword ptr [RSP + 0x50],RSI
1481d5824 TEST RSI,RSI
1481d5827 JZ 0x1481d5834
1481d5829 MOV RAX,qword ptr [RSI + 0x50]
1481d582d MOV qword ptr [RSP + 0x58],RAX
1481d5832 JMP 0x1481d5839
1481d5834 MOV qword ptr [RSP + 0x58],RBX
1481d5839 MOV dword ptr [RBP + -0x79],0xffffffff
1481d5840 MOV word ptr [RBP + -0x75],0x101
1481d5846 MOV byte ptr [RBP + -0x73],BL
1481d5849 LEA RCX,[RSP + 0x50]
1481d584e CALL 0x1469a93b0
1481d5853 MOV R14,qword ptr [RSP + 0x58]
1481d5858 TEST R14,R14
1481d585b JZ 0x1481d5893
1481d585d MOV qword ptr [RBP + -0x9],RDI
1481d5861 MOV RAX,qword ptr [R14 + 0x20]
1481d5865 MOV qword ptr [RBP + 0x77],RAX
1481d5869 MOV qword ptr [RBP + -0x1],RAX
1481d586d MOV qword ptr [RBP + 0x7],RDI
1481d5871 CMP RAX,RDI
1481d5874 JZ 0x1481d58c5
1481d5876 MOV RAX,qword ptr [R14 + 0x18]
1481d587a MOV qword ptr [RSP + 0x58],RAX
1481d587f LEA RCX,[RSP + 0x50]
1481d5884 CALL 0x1469a93b0
1481d5889 MOV R14,qword ptr [RSP + 0x58]
1481d588e TEST R14,R14
1481d5891 JNZ 0x1481d5861
1481d5893 CMP byte ptr [0x14eab53c8],0x2
1481d589a JC 0x1481d58af
1481d589c LEA RDX,[0x14cf7d328]
1481d58a3 LEA RCX,[0x14eab53c8]
1481d58aa CALL 0x140f24ba0
1481d58af XOR AL,AL
1481d58b1 ADD RSP,0xf8
1481d58b8 POP R15
1481d58ba POP R14
1481d58bc POP R13
1481d58be POP R12
1481d58c0 POP RDI
1481d58c1 POP RSI
1481d58c2 POP RBX
1481d58c3 POP RBP
1481d58c4 RET
1481d58c5 TEST R14,R14
1481d58c8 JZ 0x1481d5893
1481d58ca MOV R13,qword ptr [R13 + 0x38]
1481d58ce MOV EAX,dword ptr [R14 + 0x30]
1481d58d2 TEST EAX,EAX
1481d58d4 JG 0x1481d590d
1481d58d6 MOV R9,qword ptr [RBP + 0x5f]
1481d58da MOV dword ptr [RSP + 0x30],EAX
1481d58de MOV dword ptr [RSP + 0x28],EBX
1481d58e2 LEA RAX,[0x14be5bf60]
1481d58e9 MOV qword ptr [RSP + 0x20],RAX
1481d58ee MOV R8D,0x26f
1481d58f4 LEA RDX,[0x14cf63d80]
1481d58fb LEA RCX,[0x14be5bfd0]
1481d5902 CALL 0x140f8dfd0
1481d5907 TEST AL,AL
1481d5909 JZ 0x1481d590d
1481d590b NOP
1481d590c INT3
1481d590d LEA R15,[0x14bce4e94]
1481d5914 TEST R13,R13
1481d5917 JNZ 0x1481d5941
1481d5919 MOV R9,qword ptr [RBP + 0x5f]
1481d591d MOV qword ptr [RSP + 0x20],R15
1481d5922 MOV R8D,0x270
1481d5928 LEA RDX,[0x14cf63d80]
1481d592f LEA RCX,[0x14be5c000]
1481d5936 CALL 0x140f8dfd0
1481d593b TEST AL,AL
1481d593d JZ 0x1481d5941
1481d593f NOP
1481d5940 INT3
1481d5941 MOV RCX,R13
1481d5944 CALL 0x1418b7d40
1481d5949 TEST AL,AL
1481d594b JNZ 0x1481d5975
1481d594d MOV R9,qword ptr [RBP + 0x5f]
1481d5951 MOV qword ptr [RSP + 0x20],R15
1481d5956 MOV R8D,0x274
1481d595c LEA RDX,[0x14cf63d80]
1481d5963 LEA RCX,[0x14be86ec0]
1481d596a CALL 0x140f8dfd0
1481d596f TEST AL,AL
1481d5971 JZ 0x1481d5975
1481d5973 NOP
1481d5974 INT3
1481d5975 CMP qword ptr [R13 + 0x10],RBX
1481d5979 JNZ 0x1481d59a3
1481d597b MOV R9,qword ptr [RBP + 0x5f]
1481d597f MOV qword ptr [RSP + 0x20],R15
1481d5984 MOV R8D,0x275
1481d598a LEA RDX,[0x14cf63d80]
1481d5991 LEA RCX,[0x14be86ef0]
1481d5998 CALL 0x140f8dfd0
1481d599d TEST AL,AL
1481d599f JZ 0x1481d59a3
1481d59a1 NOP
1481d59a2 INT3
1481d59a3 CALL 0x1416099b0
1481d59a8 MOV RDX,RAX
1481d59ab LEA RCX,[R14 + 0x10]
1481d59af CALL 0x14169bf20
1481d59b4 TEST AL,AL
1481d59b6 JZ 0x1481d59c2
1481d59b8 TEST qword ptr [R14 + 0x10],-0x2
1481d59c0 JNZ 0x1481d59ea
1481d59c2 MOV R9,qword ptr [RBP + 0x5f]
1481d59c6 MOV qword ptr [RSP + 0x20],R15
1481d59cb MOV R8D,0x276
1481d59d1 LEA RDX,[0x14cf63d80]
1481d59d8 LEA RCX,[0x14be86f20]
1481d59df CALL 0x140f8dfd0
1481d59e4 TEST AL,AL
1481d59e6 JZ 0x1481d59ea
1481d59e8 NOP
1481d59e9 INT3
1481d59ea CALL 0x1416099b0
1481d59ef MOV RDX,RAX
1481d59f2 LEA RCX,[R14 + 0x10]
1481d59f6 CALL 0x14169bf20
1481d59fb TEST AL,AL
1481d59fd JZ 0x1481d5a09
1481d59ff MOV RAX,qword ptr [R14 + 0x10]
1481d5a03 AND RAX,-0x2
1481d5a07 JMP 0x1481d5a0c
1481d5a09 MOV RAX,RBX
1481d5a0c MOV RDX,qword ptr [R13 + 0x10]
1481d5a10 LEA R8,[RAX + 0x30]
1481d5a14 MOVSXD RAX,dword ptr [R8 + 0x8]
1481d5a18 CMP EAX,dword ptr [RDX + 0x38]
1481d5a1b JG 0x1481d5a2e
1481d5a1d MOV RCX,RAX
1481d5a20 MOV RAX,qword ptr [RDX + 0x30]
1481d5a24 CMP qword ptr [RAX + RCX*0x8],R8
1481d5a28 JZ 0x1481d5b51
1481d5a2e CALL 0x1416099b0
1481d5a33 MOV RDX,RAX
1481d5a36 LEA RCX,[R14 + 0x10]
1481d5a3a CALL 0x14169bf20
1481d5a3f TEST AL,AL
1481d5a41 JZ 0x1481d5a4b
1481d5a43 MOV RBX,qword ptr [R14 + 0x10]
1481d5a47 AND RBX,-0x2
1481d5a4b MOV RAX,qword ptr [RBX + 0x18]
1481d5a4f MOV qword ptr [RBP + -0x71],RAX
1481d5a53 LEA RDX,[RBP + -0x29]
1481d5a57 LEA RCX,[RBP + -0x71]
1481d5a5b CALL 0x1411de0e0
1481d5a60 NOP
1481d5a61 MOV RSI,R15
1481d5a64 CMP dword ptr [RBP + -0x21],0x0
1481d5a68 CMOVNZ RSI,qword ptr [RBP + -0x29]
1481d5a6d LEA RCX,[R14 + 0x20]
1481d5a71 LEA RDX,[RBP + -0x39]
1481d5a75 CALL 0x1411de0e0
1481d5a7a NOP
1481d5a7b MOV RDI,R15
1481d5a7e CMP dword ptr [RBP + -0x31],0x0
1481d5a82 CMOVNZ RDI,qword ptr [RBP + -0x39]
1481d5a87 MOV RAX,qword ptr [R13 + 0x10]
1481d5a8b MOV RCX,qword ptr [RAX + 0x18]
1481d5a8f MOV qword ptr [RBP + -0x69],RCX
1481d5a93 LEA RDX,[RBP + -0x49]
1481d5a97 LEA RCX,[RBP + -0x69]
1481d5a9b CALL 0x1411de0e0
1481d5aa0 NOP
1481d5aa1 MOV RBX,R15
1481d5aa4 CMP dword ptr [RBP + -0x41],0x0
1481d5aa8 CMOVNZ RBX,qword ptr [RBP + -0x49]
1481d5aad MOV RAX,qword ptr [R13 + 0x18]
1481d5ab1 MOV qword ptr [RBP + -0x61],RAX
1481d5ab5 LEA RDX,[RBP + -0x59]
1481d5ab9 LEA RCX,[RBP + -0x61]
1481d5abd CALL 0x1411de0e0
1481d5ac2 NOP
1481d5ac3 MOV RAX,R15
1481d5ac6 CMP dword ptr [RBP + -0x51],0x0
1481d5aca CMOVNZ RAX,qword ptr [RBP + -0x59]
1481d5acf MOV R9,qword ptr [RBP + 0x5f]
1481d5ad3 MOV qword ptr [RSP + 0x40],RSI
1481d5ad8 MOV qword ptr [RSP + 0x38],RDI
1481d5add MOV qword ptr [RSP + 0x30],RBX
1481d5ae2 MOV qword ptr [RSP + 0x28],RAX
1481d5ae7 LEA RAX,[0x14be86f40]
1481d5aee MOV qword ptr [RSP + 0x20],RAX
1481d5af3 MOV R8D,0x27d
1481d5af9 LEA RDX,[0x14cf63d80]
1481d5b00 LEA RCX,[0x14be86fc8]
1481d5b07 CALL 0x140f8dfd0
1481d5b0c MOVZX EBX,AL
1481d5b0f MOV RCX,qword ptr [RBP + -0x59]
1481d5b13 TEST RCX,RCX
1481d5b16 JZ 0x1481d5b1e
1481d5b18 CALL 0x140e282f0
1481d5b1d NOP
1481d5b1e MOV RCX,qword ptr [RBP + -0x49]
1481d5b22 TEST RCX,RCX
1481d5b25 JZ 0x1481d5b2d
1481d5b27 CALL 0x140e282f0
1481d5b2c NOP
1481d5b2d MOV RCX,qword ptr [RBP + -0x39]
1481d5b31 TEST RCX,RCX
1481d5b34 JZ 0x1481d5b3c
1481d5b36 CALL 0x140e282f0
1481d5b3b NOP
1481d5b3c MOV RCX,qword ptr [RBP + -0x29]
1481d5b40 TEST RCX,RCX
1481d5b43 JZ 0x1481d5b4b
1481d5b45 CALL 0x140e282f0
1481d5b4a NOP
1481d5b4b TEST BL,BL
1481d5b4d JZ 0x1481d5b51
1481d5b4f NOP
1481d5b50 INT3
1481d5b51 MOVSXD RDI,dword ptr [R14 + 0x44]
1481d5b55 ADD RDI,R13
1481d5b58 JZ 0x1481d5b6e
1481d5b5a MOV RDX,R12
1481d5b5d MOV RCX,RDI
1481d5b60 CALL 0x140e6d810
1481d5b65 TEST AL,AL
1481d5b67 JZ 0x1481d5b6e
1481d5b69 MOV R14B,0x1
1481d5b6c JMP 0x1481d5b7a
1481d5b6e XOR R14B,R14B
1481d5b71 TEST RDI,RDI
1481d5b74 JZ 0x1481d5bfe
1481d5b7a CMP byte ptr [0x14eab53c8],0x3
1481d5b81 JC 0x1481d5b9a
1481d5b83 MOV R8D,dword ptr [RDI + 0x8]
1481d5b87 LEA RDX,[0x14cf7d3b0]
1481d5b8e LEA RCX,[0x14eab53c8]
1481d5b95 CALL 0x140f24ba0
1481d5b9a MOV RBX,qword ptr [RDI]
1481d5b9d MOVSXD R12,dword ptr [RDI + 0x8]
1481d5ba1 MOV RSI,R12
1481d5ba4 SHL RSI,0x4
1481d5ba8 ADD RSI,RBX
1481d5bab NOP dword ptr [RAX + RAX*0x1]
1481d5bb0 CMP dword ptr [RDI + 0x8],R12D
1481d5bb4 JZ 0x1481d5bc9
1481d5bb6 MOV byte ptr [RBP + 0x67],0x0
1481d5bba LEA RCX,[RBP + 0x67]
1481d5bbe CALL 0x14bae4170
1481d5bc3 TEST AL,AL
1481d5bc5 JZ 0x1481d5bc9
1481d5bc7 NOP
1481d5bc8 INT3
1481d5bc9 CMP RBX,RSI
1481d5bcc JZ 0x1481d5c1c
1481d5bce CMP byte ptr [0x14eab53c8],0x3
1481d5bd5 JC 0x1481d5bf8
1481d5bd7 CMP dword ptr [RBX + 0x8],0x0
1481d5bdb JZ 0x1481d5be2
1481d5bdd MOV R8,qword ptr [RBX]
1481d5be0 JMP 0x1481d5be5
1481d5be2 MOV R8,R15
1481d5be5 LEA RDX,[0x14cf7d440]
1481d5bec LEA RCX,[0x14eab53c8]
1481d5bf3 CALL 0x140f24ba0
1481d5bf8 ADD RBX,0x10
1481d5bfc JMP 0x1481d5bb0
1481d5bfe CMP byte ptr [0x14eab53c8],0x2
1481d5c05 JC 0x1481d5c20
1481d5c07 LEA RDX,[0x14cf7d460]
1481d5c0e LEA RCX,[0x14eab53c8]
1481d5c15 CALL 0x140f24ba0
1481d5c1a JMP 0x1481d5c20
1481d5c1c MOV R12,qword ptr [RBP + 0x6f]
1481d5c20 CMP byte ptr [0x14eab53c8],0x3
1481d5c27 JC 0x1481d5c60
1481d5c29 CMP dword ptr [R12 + 0x8],0x0
1481d5c2f JZ 0x1481d5c35
1481d5c31 MOV R15,qword ptr [R12]
1481d5c35 LEA RAX,[0x14ca022e8]
1481d5c3c LEA R9,[0x14ca022f0]
1481d5c43 TEST R14B,R14B
1481d5c46 CMOVNZ R9,RAX
1481d5c4a MOV R8,R15
1481d5c4d LEA RDX,[0x14cf7d4d8]
1481d5c54 LEA RCX,[0x14eab53c8]
1481d5c5b CALL 0x140f24ba0
1481d5c60 MOVZX EAX,R14B
1481d5c64 JMP 0x1481d58b1
*/
