
/* 1481b4920 AreAllRequirementsMet */

undefined8 AreAllRequirementsMet(undefined8 param_1,longlong param_2)

{
  int iVar1;
  code *pcVar2;
  char cVar3;
  undefined8 uVar4;
  longlong lVar5;
  longlong lVar6;
  bool bVar7;
  undefined1 auStackX_10 [8];
  
  iVar1 = *(int *)(param_2 + 0x10);
  lVar5 = *(longlong *)(param_2 + 8);
  lVar6 = (longlong)iVar1 * 0x10 + lVar5;
  while( true ) {
    if (*(int *)(param_2 + 0x10) != iVar1) {
      auStackX_10[0] = 0;
      cVar3 = func_0x00014bc1d030(auStackX_10);
      if (cVar3 != '\0') {
        pcVar2 = (code *)swi(3);
        uVar4 = (*pcVar2)();
        return uVar4;
      }
    }
    if (lVar5 == lVar6) {
      return 1;
    }
    cVar3 = *(char *)(lVar5 + 8);
    if (cVar3 == '\0') {
      bVar7 = *(int *)(lVar5 + 4) <= *(int *)(lVar5 + 0xc);
    }
    else if (cVar3 == '\x01') {
      bVar7 = *(int *)(lVar5 + 0xc) <= *(int *)(lVar5 + 4);
    }
    else if (cVar3 == '\x02') {
      bVar7 = *(int *)(lVar5 + 0xc) == *(int *)(lVar5 + 4);
    }
    else if (cVar3 == '\x03') {
      bVar7 = *(int *)(lVar5 + 4) < *(int *)(lVar5 + 0xc);
    }
    else {
      if (cVar3 != '\x04') {
        return 0;
      }
      bVar7 = *(int *)(lVar5 + 0xc) < *(int *)(lVar5 + 4);
    }
    if (!bVar7) break;
    lVar5 = lVar5 + 0x10;
  }
  return 0;
}


/* Instruction evidence:
1481b4920 MOV qword ptr [RSP + 0x8],RBX
1481b4925 MOV qword ptr [RSP + 0x18],RBP
1481b492a MOV qword ptr [RSP + 0x20],RSI
1481b492f PUSH RDI
1481b4930 SUB RSP,0x20
1481b4934 MOVSXD RBP,dword ptr [RDX + 0x10]
1481b4938 MOV RSI,RDX
1481b493b MOV RBX,qword ptr [RDX + 0x8]
1481b493f MOV RDI,RBP
1481b4942 SHL RDI,0x4
1481b4946 ADD RDI,RBX
1481b4949 NOP dword ptr [RAX]
1481b4950 CMP dword ptr [RSI + 0x10],EBP
1481b4953 JZ 0x1481b496a
1481b4955 LEA RCX,[RSP + 0x38]
1481b495a MOV byte ptr [RSP + 0x38],0x0
1481b495f CALL 0x14bc1d030
1481b4964 TEST AL,AL
1481b4966 JZ 0x1481b496a
1481b4968 NOP
1481b4969 INT3
1481b496a CMP RBX,RDI
1481b496d JZ 0x1481b49ce
1481b496f MOVZX ECX,byte ptr [RBX + 0x8]
1481b4973 TEST ECX,ECX
1481b4975 JZ 0x1481b49b7
1481b4977 SUB ECX,0x1
1481b497a JZ 0x1481b49ac
1481b497c SUB ECX,0x1
1481b497f JZ 0x1481b49a1
1481b4981 SUB ECX,0x1
1481b4984 JZ 0x1481b4996
1481b4986 CMP ECX,0x1
1481b4989 JNZ 0x1481b49ca
1481b498b MOV EAX,dword ptr [RBX + 0x4]
1481b498e CMP dword ptr [RBX + 0xc],EAX
1481b4991 SETL AL
1481b4994 JMP 0x1481b49c0
1481b4996 MOV EAX,dword ptr [RBX + 0x4]
1481b4999 CMP dword ptr [RBX + 0xc],EAX
1481b499c SETG AL
1481b499f JMP 0x1481b49c0
1481b49a1 MOV EAX,dword ptr [RBX + 0x4]
1481b49a4 CMP dword ptr [RBX + 0xc],EAX
1481b49a7 SETZ AL
1481b49aa JMP 0x1481b49c0
1481b49ac MOV EAX,dword ptr [RBX + 0x4]
1481b49af CMP dword ptr [RBX + 0xc],EAX
1481b49b2 SETLE AL
1481b49b5 JMP 0x1481b49c0
1481b49b7 MOV EAX,dword ptr [RBX + 0x4]
1481b49ba CMP dword ptr [RBX + 0xc],EAX
1481b49bd SETGE AL
1481b49c0 TEST AL,AL
1481b49c2 JZ 0x1481b49ca
1481b49c4 ADD RBX,0x10
1481b49c8 JMP 0x1481b4950
1481b49ca XOR AL,AL
1481b49cc JMP 0x1481b49d0
1481b49ce MOV AL,0x1
1481b49d0 MOV RBX,qword ptr [RSP + 0x30]
1481b49d5 MOV RBP,qword ptr [RSP + 0x40]
1481b49da MOV RSI,qword ptr [RSP + 0x48]
1481b49df ADD RSP,0x20
1481b49e3 POP RDI
1481b49e4 RET
*/

/* 1481b4d80 CheckChallengeConditions */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 CheckChallengeConditions(longlong param_1,longlong param_2)

{
  int iVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined *puVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  bool bVar13;
  bool bVar14;
  undefined1 auStackX_10 [16];
  undefined1 auStackX_20 [8];
  
  iVar1 = *(int *)(param_2 + 0x78);
  puVar11 = *(undefined8 **)(param_2 + 0x70);
  puVar12 = puVar11 + (longlong)iVar1 * 4;
  do {
    if (*(int *)(param_2 + 0x78) != iVar1) {
      auStackX_10[0] = 0;
      cVar3 = func_0x00014bc1cfe0(auStackX_10);
      if (cVar3 != '\0') {
        pcVar2 = (code *)swi(3);
        uVar7 = (*pcVar2)();
        return uVar7;
      }
    }
    if (puVar11 == puVar12) {
      return 1;
    }
    if (*(int *)(puVar11 + 1) == 0) {
      puVar8 = &UNK_14bce4e94;
    }
    else {
      puVar8 = (undefined *)*puVar11;
    }
    iVar4 = func_0x000140d807c0(puVar8,"modifier");
    if (iVar4 == 0) {
      iVar4 = *(int *)(param_1 + 0x278);
      puVar9 = *(undefined8 **)(param_1 + 0x270);
      puVar10 = puVar9 + (longlong)iVar4 * 2;
      do {
        if (*(int *)(param_1 + 0x278) != iVar4) {
          auStackX_20[0] = 0;
          cVar3 = func_0x00014bae4c30(auStackX_20);
          if (cVar3 != '\0') {
            pcVar2 = (code *)swi(3);
            uVar7 = (*pcVar2)();
            return uVar7;
          }
        }
        if (puVar9 == puVar10) {
          return 0;
        }
        iVar5 = *(int *)(puVar9 + 1);
        if (iVar5 == *(int *)(puVar11 + 3)) {
          if (iVar5 < 2) goto LAB_1481b4ed8;
          iVar5 = func_0x000140d80770(*puVar9,puVar11[2]);
          bVar13 = iVar5 == 0;
        }
        else {
          bVar13 = iVar5 + *(int *)(puVar11 + 3) == 1;
        }
        if (bVar13) goto LAB_1481b4ed8;
        puVar9 = puVar9 + 2;
      } while( true );
    }
    if (*(int *)(puVar11 + 1) == 0) {
      puVar8 = &UNK_14bce4e94;
    }
    else {
      puVar8 = (undefined *)*puVar11;
    }
    iVar4 = func_0x000140d807c0(puVar8,"no_items");
    if (iVar4 == 0) {
      iVar4 = *(int *)(param_1 + 0x24c);
      bVar14 = false;
      bVar13 = iVar4 == 0;
LAB_1481b4ed6:
      if (!bVar13 && bVar14 == iVar4 < 0) {
        return 0;
      }
    }
    else {
      if (*(int *)(puVar11 + 1) == 0) {
        puVar8 = &UNK_14bce4e94;
      }
      else {
        puVar8 = (undefined *)*puVar11;
      }
      iVar4 = func_0x000140d807c0(puVar8,"max_time");
      if (iVar4 == 0) {
        if (*(int *)(puVar11 + 3) == 0) {
          puVar8 = &UNK_14bce4e94;
        }
        else {
          puVar8 = (undefined *)puVar11[2];
        }
        iVar6 = (*_DAT_14bcacaf8)(puVar8);
        iVar5 = *(int *)(param_1 + 600);
        bVar14 = SBORROW4(iVar5,iVar6);
        iVar4 = iVar5 - iVar6;
        bVar13 = iVar5 == iVar6;
        goto LAB_1481b4ed6;
      }
    }
LAB_1481b4ed8:
    puVar11 = puVar11 + 4;
  } while( true );
}


/* Instruction evidence:
1481b4d80 MOV qword ptr [RSP + 0x8],RBX
1481b4d85 PUSH RBP
1481b4d86 PUSH RSI
1481b4d87 PUSH RDI
1481b4d88 PUSH R12
1481b4d8a PUSH R13
1481b4d8c PUSH R14
1481b4d8e PUSH R15
1481b4d90 SUB RSP,0x20
1481b4d94 MOVSXD R12,dword ptr [RDX + 0x78]
1481b4d98 MOV R13,RDX
1481b4d9b MOV RDI,qword ptr [RDX + 0x70]
1481b4d9f MOV R15,R12
1481b4da2 SHL R15,0x5
1481b4da6 MOV RBP,RCX
1481b4da9 ADD R15,RDI
1481b4dac NOP dword ptr [RAX]
1481b4db0 CMP dword ptr [R13 + 0x78],R12D
1481b4db4 JZ 0x1481b4dcb
1481b4db6 LEA RCX,[RSP + 0x68]
1481b4dbb MOV byte ptr [RSP + 0x68],0x0
1481b4dc0 CALL 0x14bc1cfe0
1481b4dc5 TEST AL,AL
1481b4dc7 JZ 0x1481b4dcb
1481b4dc9 NOP
1481b4dca INT3
1481b4dcb CMP RDI,R15
1481b4dce JZ 0x1481b4ee5
1481b4dd4 CMP dword ptr [RDI + 0x8],0x0
1481b4dd8 JZ 0x1481b4ddf
1481b4dda MOV RCX,qword ptr [RDI]
1481b4ddd JMP 0x1481b4de6
1481b4ddf LEA RCX,[0x14bce4e94]
1481b4de6 LEA RDX,[0x14cf719e8]
1481b4ded CALL 0x140d807c0
1481b4df2 TEST EAX,EAX
1481b4df4 JNZ 0x1481b4e6c
1481b4df6 MOVSXD R14,dword ptr [RBP + 0x278]
1481b4dfd MOV RBX,qword ptr [RBP + 0x270]
1481b4e04 MOV RSI,R14
1481b4e07 SHL RSI,0x4
1481b4e0b ADD RSI,RBX
1481b4e0e NOP
1481b4e10 CMP dword ptr [RBP + 0x278],R14D
1481b4e17 JZ 0x1481b4e2e
1481b4e19 LEA RCX,[RSP + 0x78]
1481b4e1e MOV byte ptr [RSP + 0x78],0x0
1481b4e23 CALL 0x14bae4c30
1481b4e28 TEST AL,AL
1481b4e2a JZ 0x1481b4e2e
1481b4e2c NOP
1481b4e2d INT3
1481b4e2e CMP RBX,RSI
1481b4e31 JZ 0x1481b4ee1
1481b4e37 MOV EAX,dword ptr [RBX + 0x8]
1481b4e3a MOV ECX,dword ptr [RDI + 0x18]
1481b4e3d CMP EAX,ECX
1481b4e3f JZ 0x1481b4e48
1481b4e41 ADD EAX,ECX
1481b4e43 CMP EAX,0x1
1481b4e46 JMP 0x1481b4e5f
1481b4e48 CMP EAX,0x1
1481b4e4b JLE 0x1481b4ed8
1481b4e51 MOV RDX,qword ptr [RDI + 0x10]
1481b4e55 MOV RCX,qword ptr [RBX]
1481b4e58 CALL 0x140d80770
1481b4e5d TEST EAX,EAX
1481b4e5f SETZ AL
1481b4e62 TEST AL,AL
1481b4e64 JNZ 0x1481b4ed8
1481b4e66 ADD RBX,0x10
1481b4e6a JMP 0x1481b4e10
1481b4e6c CMP dword ptr [RDI + 0x8],0x0
1481b4e70 JZ 0x1481b4e77
1481b4e72 MOV RCX,qword ptr [RDI]
1481b4e75 JMP 0x1481b4e7e
1481b4e77 LEA RCX,[0x14bce4e94]
1481b4e7e LEA RDX,[0x14cf719f8]
1481b4e85 CALL 0x140d807c0
1481b4e8a TEST EAX,EAX
1481b4e8c JNZ 0x1481b4e96
1481b4e8e CMP dword ptr [RBP + 0x24c],EAX
1481b4e94 JMP 0x1481b4ed6
1481b4e96 CMP dword ptr [RDI + 0x8],0x0
1481b4e9a JZ 0x1481b4ea1
1481b4e9c MOV RCX,qword ptr [RDI]
1481b4e9f JMP 0x1481b4ea8
1481b4ea1 LEA RCX,[0x14bce4e94]
1481b4ea8 LEA RDX,[0x14cf71a08]
1481b4eaf CALL 0x140d807c0
1481b4eb4 TEST EAX,EAX
1481b4eb6 JNZ 0x1481b4ed8
1481b4eb8 CMP dword ptr [RDI + 0x18],EAX
1481b4ebb JZ 0x1481b4ec3
1481b4ebd MOV RCX,qword ptr [RDI + 0x10]
1481b4ec1 JMP 0x1481b4eca
1481b4ec3 LEA RCX,[0x14bce4e94]
1481b4eca CALL qword ptr [0x14bcacaf8]
1481b4ed0 CMP dword ptr [RBP + 0x258],EAX
1481b4ed6 JG 0x1481b4ee1
1481b4ed8 ADD RDI,0x20
1481b4edc JMP 0x1481b4db0
1481b4ee1 XOR AL,AL
1481b4ee3 JMP 0x1481b4ee7
1481b4ee5 MOV AL,0x1
1481b4ee7 MOV RBX,qword ptr [RSP + 0x60]
1481b4eec ADD RSP,0x20
1481b4ef0 POP R15
1481b4ef2 POP R14
1481b4ef4 POP R13
1481b4ef6 POP R12
1481b4ef8 POP RDI
1481b4ef9 POP RSI
1481b4efa POP RBP
1481b4efb RET
*/

/* 1481c23f0 GetRequirementProgressPercent */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void GetRequirementProgressPercent(longlong param_1,ulonglong param_2,uint param_3)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  uint uVar6;
  undefined8 unaff_retaddr;
  int iStackX_14;
  
  iVar3 = func_0x0001411c2eb0(param_2 & 0xffffffff);
  iStackX_14 = (int)(param_2 >> 0x20);
  if (*(int *)(param_1 + 0xa8) != *(int *)(param_1 + 0xd4)) {
    lVar5 = param_1 + 0xd8;
    if (*(longlong *)(param_1 + 0xe0) != 0) {
      lVar5 = *(longlong *)(param_1 + 0xe0);
    }
    iVar3 = *(int *)(lVar5 + (ulonglong)(*(int *)(param_1 + 0xe8) - 1U & iVar3 + iStackX_14) * 4);
    if (iVar3 != -1) {
      do {
        if (*(ulonglong *)((longlong)iVar3 * 0x40 + *(longlong *)(param_1 + 0xa0)) == param_2) {
          iVar3 = func_0x0001411c2eb0(param_2 & 0xffffffff);
          if (*(int *)(param_1 + 0xa8) == *(int *)(param_1 + 0xd4)) goto LAB_1481c255a;
          lVar5 = param_1 + 0xd8;
          if (*(longlong *)(param_1 + 0xe0) != 0) {
            lVar5 = *(longlong *)(param_1 + 0xe0);
          }
          iVar3 = *(int *)(lVar5 + (ulonglong)(*(int *)(param_1 + 0xe8) - 1U & iVar3 + iStackX_14) *
                                   4);
          if (iVar3 == -1) goto LAB_1481c255a;
          lVar5 = *(longlong *)(param_1 + 0xa0);
          goto LAB_1481c2540;
        }
        iVar3 = *(int *)((longlong)iVar3 * 0x40 + 0x38 + *(longlong *)(param_1 + 0xa0));
      } while (iVar3 != -1);
    }
  }
  iVar3 = func_0x0001411c2eb0(param_2 & 0xffffffff);
  if (*(int *)(param_1 + 0xf8) == *(int *)(param_1 + 0x124)) {
    return;
  }
  lVar5 = param_1 + 0x128;
  if (*(longlong *)(param_1 + 0x130) != 0) {
    lVar5 = *(longlong *)(param_1 + 0x130);
  }
  iVar3 = *(int *)(lVar5 + (ulonglong)(*(int *)(param_1 + 0x138) - 1U & iVar3 + iStackX_14) * 4);
  if (iVar3 == -1) {
    return;
  }
  while (*(ulonglong *)((longlong)iVar3 * 0x40 + *(longlong *)(param_1 + 0xf0)) != param_2) {
    iVar3 = *(int *)((longlong)iVar3 * 0x40 + 0x38 + *(longlong *)(param_1 + 0xf0));
    if (iVar3 == -1) {
      return;
    }
  }
  iVar3 = func_0x0001411c2eb0(param_2 & 0xffffffff);
  if (*(int *)(param_1 + 0xf8) != *(int *)(param_1 + 0x124)) {
    lVar5 = param_1 + 0x128;
    if (*(longlong *)(param_1 + 0x130) != 0) {
      lVar5 = *(longlong *)(param_1 + 0x130);
    }
    iVar3 = *(int *)(lVar5 + (ulonglong)(*(int *)(param_1 + 0x138) - 1U & iVar3 + iStackX_14) * 4);
    if (iVar3 != -1) {
      lVar5 = *(longlong *)(param_1 + 0xf0);
      do {
        lVar4 = (longlong)iVar3 * 0x40;
        if (*(ulonglong *)(lVar4 + lVar5) == param_2) goto LAB_1481c265b;
        iVar3 = *(int *)(lVar4 + 0x38 + lVar5);
      } while (iVar3 != -1);
    }
  }
LAB_1481c255a:
  lVar5 = 0;
LAB_1481c255d:
  lVar4 = lVar5 + 8;
  if (lVar5 == 0) {
    lVar4 = 0;
  }
  if ((lVar4 != 0) && ((int)param_3 < *(int *)(lVar4 + 0x10))) {
    uVar6 = 0;
    if ((int)param_3 < *(int *)(lVar4 + 0x10)) {
      uVar6 = ~param_3 >> 0x1f;
    }
    if ((uVar6 == 0) &&
       (cVar2 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,&UNK_14bce6ef0
                                    ,(longlong)(int)param_3,(longlong)*(int *)(lVar4 + 0x10)),
       cVar2 != '\0')) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  return;
  while (iVar3 = *(int *)(lVar5 + 0x38 + lVar4), iVar3 != -1) {
LAB_1481c2540:
    lVar4 = (longlong)iVar3 * 0x40;
    if (*(ulonglong *)(lVar5 + lVar4) == param_2) goto LAB_1481c265b;
  }
  goto LAB_1481c255a;
LAB_1481c265b:
  lVar5 = lVar5 + lVar4;
  goto LAB_1481c255d;
}


/* Instruction evidence:
1481c23f0 MOV qword ptr [RSP + 0x8],RBX
1481c23f5 MOV qword ptr [RSP + 0x18],RBP
1481c23fa MOV qword ptr [RSP + 0x10],RDX
1481c23ff PUSH RSI
1481c2400 PUSH RDI
1481c2401 PUSH R14
1481c2403 SUB RSP,0x40
1481c2407 MOV RDI,RCX
1481c240a MOVSXD RBP,R8D
1481c240d MOV ECX,EDX
1481c240f MOV RBX,RDX
1481c2412 CALL 0x1411c2eb0
1481c2417 MOV R14D,dword ptr [RSP + 0x6c]
1481c241c LEA R8D,[RAX + R14*0x1]
1481c2420 MOV EAX,dword ptr [RDI + 0xa8]
1481c2426 CMP EAX,dword ptr [RDI + 0xd4]
1481c242c JZ 0x1481c247a
1481c242e MOV ECX,dword ptr [RDI + 0xe8]
1481c2434 LEA RSI,[RDI + 0xd8]
1481c243b MOV RDX,qword ptr [RSI + 0x8]
1481c243f DEC ECX
1481c2441 MOV EAX,R8D
1481c2444 AND RCX,RAX
1481c2447 MOV RAX,RSI
1481c244a TEST RDX,RDX
1481c244d CMOVNZ RAX,RDX
1481c2451 MOV EDX,dword ptr [RAX + RCX*0x4]
1481c2454 CMP EDX,-0x1
1481c2457 JZ 0x1481c247a
1481c2459 MOV RCX,qword ptr [RDI + 0xa0]
1481c2460 MOVSXD RAX,EDX
1481c2463 SHL RAX,0x6
1481c2467 CMP qword ptr [RAX + RCX*0x1],RBX
1481c246b JZ 0x1481c24f5
1481c2471 MOV EDX,dword ptr [RAX + RCX*0x1 + 0x38]
1481c2475 CMP EDX,-0x1
1481c2478 JNZ 0x1481c2460
1481c247a MOV ECX,EBX
1481c247c CALL 0x1411c2eb0
1481c2481 LEA R8D,[RAX + R14*0x1]
1481c2485 MOV EAX,dword ptr [RDI + 0xf8]
1481c248b CMP EAX,dword ptr [RDI + 0x124]
1481c2491 JZ 0x1481c24df
1481c2493 MOV ECX,dword ptr [RDI + 0x138]
1481c2499 LEA RSI,[RDI + 0x128]
1481c24a0 MOV RDX,qword ptr [RSI + 0x8]
1481c24a4 DEC ECX
1481c24a6 MOV EAX,R8D
1481c24a9 AND RCX,RAX
1481c24ac MOV RAX,RSI
1481c24af TEST RDX,RDX
1481c24b2 CMOVNZ RAX,RDX
1481c24b6 MOV EDX,dword ptr [RAX + RCX*0x4]
1481c24b9 CMP EDX,-0x1
1481c24bc JZ 0x1481c24df
1481c24be MOV RCX,qword ptr [RDI + 0xf0]
1481c24c5 MOVSXD RAX,EDX
1481c24c8 SHL RAX,0x6
1481c24cc CMP qword ptr [RAX + RCX*0x1],RBX
1481c24d0 JZ 0x1481c25ef
1481c24d6 MOV EDX,dword ptr [RAX + RCX*0x1 + 0x38]
1481c24da CMP EDX,-0x1
1481c24dd JNZ 0x1481c24c5
1481c24df XORPS XMM0,XMM0
1481c24e2 MOV RBX,qword ptr [RSP + 0x60]
1481c24e7 MOV RBP,qword ptr [RSP + 0x70]
1481c24ec ADD RSP,0x40
1481c24f0 POP R14
1481c24f2 POP RDI
1481c24f3 POP RSI
1481c24f4 RET
1481c24f5 MOV ECX,EBX
1481c24f7 CALL 0x1411c2eb0
1481c24fc XOR R8D,R8D
1481c24ff LEA R9D,[RAX + R14*0x1]
1481c2503 MOV EAX,dword ptr [RDI + 0xa8]
1481c2509 CMP EAX,dword ptr [RDI + 0xd4]
1481c250f JZ 0x1481c255a
1481c2511 MOV ECX,dword ptr [RDI + 0xe8]
1481c2517 MOV RDX,qword ptr [RSI + 0x8]
1481c251b DEC ECX
1481c251d MOV EAX,R9D
1481c2520 AND RCX,RAX
1481c2523 TEST RDX,RDX
1481c2526 CMOVNZ RSI,RDX
1481c252a MOV EAX,dword ptr [RSI + RCX*0x4]
1481c252d CMP EAX,-0x1
1481c2530 JZ 0x1481c255a
1481c2532 MOV RDX,qword ptr [RDI + 0xa0]
1481c2539 NOP dword ptr [RAX]
1481c2540 MOVSXD RCX,EAX
1481c2543 SHL RCX,0x6
1481c2547 CMP qword ptr [RDX + RCX*0x1],RBX
1481c254b JZ 0x1481c265b
1481c2551 MOV EAX,dword ptr [RDX + RCX*0x1 + 0x38]
1481c2555 CMP EAX,-0x1
1481c2558 JNZ 0x1481c2540
1481c255a MOV RDX,R8
1481c255d TEST RDX,RDX
1481c2560 LEA RBX,[RDX + 0x8]
1481c2564 CMOVZ RBX,R8
1481c2568 TEST RBX,RBX
1481c256b JZ 0x1481c24df
1481c2571 CMP EBP,dword ptr [RBX + 0x10]
1481c2574 JGE 0x1481c24df
1481c257a MOVSXD RCX,dword ptr [RBX + 0x10]
1481c257e MOV EAX,EBP
1481c2580 NOT EAX
1481c2582 SHR EAX,0x1f
1481c2585 CMP EBP,ECX
1481c2587 CMOVL R8D,EAX
1481c258b TEST R8D,R8D
1481c258e JNZ 0x1481c25ca
1481c2590 MOV R9,qword ptr [RSP + 0x58]
1481c2595 LEA RAX,[0x14bce6ef0]
1481c259c MOV qword ptr [RSP + 0x30],RCX
1481c25a1 LEA RDX,[0x14cf27ac0]
1481c25a8 MOV qword ptr [RSP + 0x28],RBP
1481c25ad LEA RCX,[0x14bce6f68]
1481c25b4 MOV R8D,0x303
1481c25ba MOV qword ptr [RSP + 0x20],RAX
1481c25bf CALL 0x140f8dfd0
1481c25c4 TEST AL,AL
1481c25c6 JZ 0x1481c25ca
1481c25c8 NOP
1481c25c9 INT3
1481c25ca MOV RDX,RBP
1481c25cd SHL RDX,0x4
1481c25d1 ADD RDX,qword ptr [RBX + 0x8]
1481c25d5 MOV R8D,dword ptr [RDX + 0x4]
1481c25d9 TEST R8D,R8D
1481c25dc JG 0x1481c2663
1481c25e2 MOVSS XMM0,dword ptr [0x14bcef9ec]
1481c25ea JMP 0x1481c24e2
1481c25ef MOV ECX,EBX
1481c25f1 CALL 0x1411c2eb0
1481c25f6 XOR R8D,R8D
1481c25f9 LEA R9D,[RAX + R14*0x1]
1481c25fd MOV EAX,dword ptr [RDI + 0xf8]
1481c2603 CMP EAX,dword ptr [RDI + 0x124]
1481c2609 JZ 0x1481c255a
1481c260f MOV ECX,dword ptr [RDI + 0x138]
1481c2615 MOV RDX,qword ptr [RSI + 0x8]
1481c2619 DEC ECX
1481c261b MOV EAX,R9D
1481c261e AND RCX,RAX
1481c2621 TEST RDX,RDX
1481c2624 CMOVNZ RSI,RDX
1481c2628 MOV EAX,dword ptr [RSI + RCX*0x4]
1481c262b CMP EAX,-0x1
1481c262e JZ 0x1481c255a
1481c2634 MOV RDX,qword ptr [RDI + 0xf0]
1481c263b NOP dword ptr [RAX + RAX*0x1]
1481c2640 MOVSXD RCX,EAX
1481c2643 SHL RCX,0x6
1481c2647 CMP qword ptr [RCX + RDX*0x1],RBX
1481c264b JZ 0x1481c265b
1481c264d MOV EAX,dword ptr [RCX + RDX*0x1 + 0x38]
1481c2651 CMP EAX,-0x1
1481c2654 JNZ 0x1481c2640
1481c2656 JMP 0x1481c255a
1481c265b ADD RDX,RCX
1481c265e JMP 0x1481c255d
1481c2663 MOVZX ECX,byte ptr [RDX + 0x8]
1481c2667 XORPS XMM2,XMM2
1481c266a MOVSS XMM3,dword ptr [0x14bcef9ec]
1481c2672 XORPS XMM0,XMM0
1481c2675 TEST ECX,ECX
1481c2677 JZ 0x1481c26b5
1481c2679 SUB ECX,0x1
1481c267c JZ 0x1481c268d
1481c267e SUB ECX,0x1
1481c2681 JZ 0x1481c26b5
1481c2683 SUB ECX,0x1
1481c2686 JZ 0x1481c26b5
1481c2688 CMP ECX,0x1
1481c268b JNZ 0x1481c26c9
1481c268d MOVD XMM1,dword ptr [RDX + 0xc]
1481c2692 MOVD XMM0,R8D
1481c2697 CVTDQ2PS XMM0,XMM0
1481c269a CVTDQ2PS XMM1,XMM1
1481c269d DIVSS XMM1,XMM0
1481c26a1 MOVAPS XMM0,XMM3
1481c26a4 SUBSS XMM0,XMM1
1481c26a8 MINSS XMM0,XMM3
1481c26ac MAXSS XMM0,XMM2
1481c26b0 JMP 0x1481c24e2
1481c26b5 MOVD XMM0,dword ptr [RDX + 0xc]
1481c26ba MOVD XMM1,R8D
1481c26bf CVTDQ2PS XMM0,XMM0
1481c26c2 CVTDQ2PS XMM1,XMM1
1481c26c5 DIVSS XMM0,XMM1
1481c26c9 MINSS XMM0,XMM3
1481c26cd MAXSS XMM0,XMM2
1481c26d1 JMP 0x1481c24e2
*/

/* 1481cd9b0 UpdateChallengeProgress */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void UpdateChallengeProgress(longlong *param_1,ulonglong param_2,char param_3,int param_4)

{
  int *piVar1;
  longlong lVar2;
  code *pcVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  double dVar7;
  float fVar8;
  float fVar9;
  char cVar10;
  char cVar11;
  int iVar12;
  uint uVar13;
  longlong lVar14;
  longlong lVar15;
  uint uVar16;
  ulonglong uVar17;
  ulonglong uVar18;
  longlong *plVar19;
  uint uVar20;
  ulonglong uVar21;
  ulonglong uVar22;
  float fVar23;
  double dVar24;
  undefined8 unaff_retaddr;
  int iStackX_14;
  
  lVar14 = func_0x0001481ba790();
  if (lVar14 != 0) {
    uVar17 = 0;
    iStackX_14 = (int)(param_2 >> 0x20);
    if (*(char *)(lVar14 + 0x68) == '\0') {
      iVar12 = func_0x0001411c2eb0(param_2 & 0xffffffff);
      if ((int)param_1[0x1f] != *(int *)((longlong)param_1 + 0x124)) {
        plVar19 = param_1 + 0x25;
        if ((longlong *)param_1[0x26] != (longlong *)0x0) {
          plVar19 = (longlong *)param_1[0x26];
        }
        iVar12 = *(int *)((longlong)plVar19 +
                         (ulonglong)((int)param_1[0x27] - 1U & iStackX_14 + iVar12) * 4);
        if (iVar12 != -1) {
          lVar2 = param_1[0x1e];
          do {
            lVar15 = (longlong)iVar12 * 0x40;
            if (*(ulonglong *)(lVar2 + lVar15) == param_2) {
              uVar18 = lVar2 + lVar15 + 8;
              if (lVar2 + lVar15 == 0) {
                uVar18 = uVar17;
              }
              goto LAB_1481cdb1b;
            }
            iVar12 = *(int *)(lVar2 + 0x38 + lVar15);
          } while (iVar12 != -1);
        }
      }
      uVar18 = 0;
LAB_1481cdb1b:
      fVar9 = _DAT_14bd1786c;
      fVar8 = _DAT_14bcfdb28;
      dVar7 = _DAT_14bcefa00;
      if (uVar18 != 0) {
        cVar11 = *(char *)(uVar18 + 0x18);
        bVar4 = false;
        bVar6 = false;
        bVar5 = false;
        uVar21 = uVar17;
        uVar22 = uVar17;
        if (0 < *(int *)(uVar18 + 0x10)) {
          do {
            uVar16 = (uint)uVar17;
            uVar20 = ~uVar16 >> 0x1f;
            uVar13 = 0;
            if ((int)uVar16 < *(int *)(uVar18 + 0x10)) {
              uVar13 = uVar20;
            }
            if ((uVar13 == 0) &&
               (cVar10 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                             &UNK_14bce6ef0,(longlong)(int)uVar16,
                                             (longlong)*(int *)(uVar18 + 0x10)), bVar4 = bVar5,
               cVar10 != '\0')) {
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            lVar2 = *(longlong *)(uVar18 + 8);
            if (*(char *)(uVar22 + lVar2) == param_3) {
              if (*(char *)(lVar14 + 0x68) == '\0') {
                switch(param_3) {
                case '\0':
                  *(int *)(uVar22 + 0xc + lVar2) = (int)param_1[0x46];
                  break;
                case '\x01':
                  *(undefined4 *)(uVar22 + 0xc + lVar2) = *(undefined4 *)((longlong)param_1 + 0x234)
                  ;
                  break;
                case '\x02':
                  *(int *)(uVar22 + 0xc + lVar2) = (int)param_1[0x47];
                  break;
                case '\x03':
                  *(undefined4 *)(uVar22 + 0xc + lVar2) = *(undefined4 *)((longlong)param_1 + 0x23c)
                  ;
                  break;
                case '\x04':
                  *(int *)(uVar22 + 0xc + lVar2) = (int)param_1[0x48];
                  break;
                default:
                  *(int *)(uVar22 + 0xc + lVar2) = *(int *)(uVar22 + 0xc + lVar2) + param_4;
                  break;
                case '\x06':
                  *(undefined4 *)(uVar22 + 0xc + lVar2) = *(undefined4 *)((longlong)param_1 + 0x244)
                  ;
                  break;
                case '\a':
                  *(int *)(uVar22 + 0xc + lVar2) = (int)param_1[0x49];
                  break;
                case '\b':
                  *(undefined4 *)(uVar22 + 0xc + lVar2) = *(undefined4 *)((longlong)param_1 + 0x24c)
                  ;
                  break;
                case '\n':
                  *(int *)(uVar22 + 0xc + lVar2) = (int)param_1[0x4a];
                  break;
                case '\v':
                  *(undefined4 *)(uVar22 + 0xc + lVar2) = *(undefined4 *)((longlong)param_1 + 0x254)
                  ;
                  break;
                case '\f':
                  lVar15 = (**(code **)(*param_1 + 0x188))(param_1);
                  dVar24 = *(double *)(lVar15 + 0x740) - (double)*(float *)(param_1 + 0x66);
                  *(int *)(uVar22 + 0xc + lVar2) =
                       (int)((longlong)ROUND((dVar24 + dVar24) - dVar7) >> 1);
                  break;
                case '\x10':
                  *(undefined4 *)(uVar22 + 0xc + lVar2) = *(undefined4 *)((longlong)param_1 + 0x294)
                  ;
                  break;
                case '\x11':
                  *(int *)(uVar22 + 0xc + lVar2) = (int)param_1[0x50];
                  break;
                case '\x12':
                  *(undefined4 *)(uVar22 + 0xc + lVar2) = *(undefined4 *)((longlong)param_1 + 0x284)
                  ;
                  break;
                case '\x13':
                  *(int *)(uVar22 + 0xc + lVar2) = (int)param_1[0x52];
                  break;
                case '\x17':
                  *(int *)(uVar22 + 0xc + lVar2) = (int)param_1[0x51];
                  break;
                case '\x18':
                  lVar15 = (**(code **)(*param_1 + 0x188))(param_1);
                  dVar24 = *(double *)(lVar15 + 0x740) - (double)*(float *)(param_1 + 0x66);
                  iVar12 = (int)((longlong)ROUND((dVar24 + dVar24) - dVar7) >> 1);
                  if (iVar12 < 1) {
                    *(undefined4 *)(uVar22 + 0xc + lVar2) = 0;
                  }
                  else {
                    fVar23 = ((float)(int)param_1[0x51] / (float)iVar12) * fVar9;
                    *(int *)(uVar22 + 0xc + lVar2) = (int)ROUND((fVar23 + fVar23) - fVar8) >> 1;
                  }
                  break;
                case '\x19':
                  *(int *)(uVar22 + 0xc + lVar2) = (int)param_1[0x53];
                  break;
                case '\x1a':
                  *(undefined4 *)(uVar22 + 0xc + lVar2) = *(undefined4 *)((longlong)param_1 + 0x29c)
                  ;
                  break;
                case '\x1b':
                  *(int *)(uVar22 + 0xc + lVar2) = (int)param_1[0x54];
                  break;
                case '\x1c':
                  *(undefined4 *)(uVar22 + 0xc + lVar2) = *(undefined4 *)((longlong)param_1 + 0x2a4)
                  ;
                  break;
                case '\x1d':
                  *(int *)(uVar22 + 0xc + lVar2) = (int)param_1[0x55];
                }
              }
              else {
                piVar1 = (int *)(uVar22 + 0xc + lVar2);
                *piVar1 = *piVar1 + param_4;
              }
              bVar6 = true;
              bVar4 = bVar5;
              if ((-1 < (int)uVar16) && ((int)uVar16 < *(int *)(uVar18 + 0x28))) {
                uVar13 = 0;
                if ((int)uVar16 < *(int *)(uVar18 + 0x28)) {
                  uVar13 = uVar20;
                }
                if ((uVar13 == 0) &&
                   (cVar10 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                                 &UNK_14bce6ef0,(longlong)(int)uVar16,
                                                 (longlong)*(int *)(uVar18 + 0x28)), cVar10 != '\0')
                   ) {
                  pcVar3 = (code *)swi(3);
                  (*pcVar3)();
                  return;
                }
                iVar12 = *(int *)(uVar22 + 0xc + lVar2);
                if (*(int *)(*(longlong *)(uVar18 + 0x20) + uVar21) < iVar12) {
                  uVar13 = 0;
                  if ((int)uVar16 < *(int *)(uVar18 + 0x28)) {
                    uVar13 = uVar20;
                  }
                  if ((uVar13 == 0) &&
                     (cVar10 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr
                                                   ,&UNK_14bce6ef0,(longlong)(int)uVar16,
                                                   (longlong)*(int *)(uVar18 + 0x28)),
                     cVar10 != '\0')) {
                    pcVar3 = (code *)swi(3);
                    (*pcVar3)();
                    return;
                  }
                  bVar5 = true;
                  *(int *)(*(longlong *)(uVar18 + 0x20) + uVar21) = iVar12;
                  bVar4 = true;
                }
              }
            }
            uVar17 = (ulonglong)(uVar16 + 1);
            uVar21 = uVar21 + 4;
            uVar22 = uVar22 + 0x10;
          } while ((int)(uVar16 + 1) < *(int *)(uVar18 + 0x10));
          if (bVar4) {
            func_0x0001481cad00(param_1);
          }
          if (((bVar6) && (cVar11 == '\0')) &&
             (cVar11 = AreAllRequirementsMet(param_1,uVar18), cVar11 != '\0')) {
            CompleteChallenge(param_1,param_2);
          }
        }
        func_0x000148155da0(param_1 + 5,param_2);
      }
    }
    else {
      iVar12 = func_0x0001411c2eb0(param_2 & 0xffffffff);
      if ((int)param_1[0x15] != *(int *)((longlong)param_1 + 0xd4)) {
        plVar19 = param_1 + 0x1b;
        if ((longlong *)param_1[0x1c] != (longlong *)0x0) {
          plVar19 = (longlong *)param_1[0x1c];
        }
        iVar12 = *(int *)((longlong)plVar19 +
                         (ulonglong)((int)param_1[0x1d] - 1U & iStackX_14 + iVar12) * 4);
        if (iVar12 != -1) {
          lVar2 = param_1[0x14];
          do {
            lVar15 = (longlong)iVar12 * 0x40;
            if (*(ulonglong *)(lVar15 + lVar2) == param_2) {
              if (lVar2 + lVar15 == 0) {
                return;
              }
              uVar18 = lVar2 + lVar15 + 8;
              goto LAB_1481cdb1b;
            }
            iVar12 = *(int *)(lVar15 + 0x38 + lVar2);
          } while (iVar12 != -1);
        }
      }
    }
  }
  return;
}


/* Instruction evidence:
1481cd9b0 MOV dword ptr [RSP + 0x20],R9D
1481cd9b5 MOV byte ptr [RSP + 0x18],R8B
1481cd9ba MOV qword ptr [RSP + 0x10],RDX
1481cd9bf PUSH RBX
1481cd9c0 PUSH RDI
1481cd9c1 SUB RSP,0xb8
1481cd9c8 MOV RBX,RDX
1481cd9cb MOV qword ptr [RSP + 0x50],RDX
1481cd9d0 MOV RDI,RCX
1481cd9d3 CALL 0x1481ba790
1481cd9d8 MOV qword ptr [RSP + 0x48],RAX
1481cd9dd TEST RAX,RAX
1481cd9e0 JZ 0x1481cdfdd
1481cd9e6 MOV qword ptr [RSP + 0x90],R15
1481cd9ee MOV ECX,EBX
1481cd9f0 XOR R15D,R15D
1481cd9f3 MOV qword ptr [RSP + 0xb0],RSI
1481cd9fb CMP byte ptr [RAX + 0x68],R15B
1481cd9ff JNZ 0x1481cda8f
1481cda05 CALL 0x1411c2eb0
1481cda0a MOV R9D,dword ptr [RSP + 0xdc]
1481cda12 ADD R9D,EAX
1481cda15 MOV EAX,dword ptr [RDI + 0xf8]
1481cda1b CMP EAX,dword ptr [RDI + 0x124]
1481cda21 JZ 0x1481cda69
1481cda23 MOV ECX,dword ptr [RDI + 0x138]
1481cda29 LEA R8,[RDI + 0x128]
1481cda30 MOV RDX,qword ptr [R8 + 0x8]
1481cda34 DEC ECX
1481cda36 MOV EAX,R9D
1481cda39 AND RCX,RAX
1481cda3c TEST RDX,RDX
1481cda3f CMOVNZ R8,RDX
1481cda43 MOV EAX,dword ptr [R8 + RCX*0x4]
1481cda47 CMP EAX,-0x1
1481cda4a JZ 0x1481cda69
1481cda4c MOV RDX,qword ptr [RDI + 0xf0]
1481cda53 MOVSXD RCX,EAX
1481cda56 SHL RCX,0x6
1481cda5a CMP qword ptr [RDX + RCX*0x1],RBX
1481cda5e JZ 0x1481cda7c
1481cda60 MOV EAX,dword ptr [RDX + RCX*0x1 + 0x38]
1481cda64 CMP EAX,-0x1
1481cda67 JNZ 0x1481cda53
1481cda69 MOV RDX,R15
1481cda6c TEST RDX,RDX
1481cda6f LEA RSI,[RDX + 0x8]
1481cda73 CMOVZ RSI,R15
1481cda77 JMP 0x1481cdb1b
1481cda7c ADD RDX,RCX
1481cda7f TEST RDX,RDX
1481cda82 LEA RSI,[RDX + 0x8]
1481cda86 CMOVZ RSI,R15
1481cda8a JMP 0x1481cdb1b
1481cda8f CALL 0x1411c2eb0
1481cda94 MOV R9D,dword ptr [RSP + 0xdc]
1481cda9c ADD R9D,EAX
1481cda9f MOV EAX,dword ptr [RDI + 0xa8]
1481cdaa5 CMP EAX,dword ptr [RDI + 0xd4]
1481cdaab JZ 0x1481cdfcd
1481cdab1 MOV ECX,dword ptr [RDI + 0xe8]
1481cdab7 LEA R8,[RDI + 0xd8]
1481cdabe MOV RDX,qword ptr [R8 + 0x8]
1481cdac2 DEC ECX
1481cdac4 MOV EAX,R9D
1481cdac7 AND RCX,RAX
1481cdaca TEST RDX,RDX
1481cdacd CMOVNZ R8,RDX
1481cdad1 MOV EAX,dword ptr [R8 + RCX*0x4]
1481cdad5 CMP EAX,-0x1
1481cdad8 JZ 0x1481cdfcd
1481cdade MOV RDX,qword ptr [RDI + 0xa0]
1481cdae5 NOP word ptr [RAX + RAX*0x1]
1481cdaf0 MOVSXD RCX,EAX
1481cdaf3 SHL RCX,0x6
1481cdaf7 CMP qword ptr [RCX + RDX*0x1],RBX
1481cdafb JZ 0x1481cdb0b
1481cdafd MOV EAX,dword ptr [RCX + RDX*0x1 + 0x38]
1481cdb01 CMP EAX,-0x1
1481cdb04 JNZ 0x1481cdaf0
1481cdb06 JMP 0x1481cdfcd
1481cdb0b MOV RSI,RDX
1481cdb0e ADD RSI,RCX
1481cdb11 JZ 0x1481cdfcd
1481cdb17 ADD RSI,0x8
1481cdb1b TEST RSI,RSI
1481cdb1e JZ 0x1481cdfcd
1481cdb24 MOVZX EAX,byte ptr [RSI + 0x18]
1481cdb28 XOR DL,DL
1481cdb2a MOV byte ptr [RSP + 0x42],AL
1481cdb2e XOR AL,AL
1481cdb30 MOV qword ptr [RSP + 0xd0],RBP
1481cdb38 MOV EBP,R15D
1481cdb3b MOV byte ptr [RSP + 0x41],AL
1481cdb3f MOV byte ptr [RSP + 0x40],DL
1481cdb43 CMP dword ptr [RSI + 0x10],R15D
1481cdb47 JLE 0x1481cdfb9
1481cdb4d MOV EBX,dword ptr [RSP + 0xe8]
1481cdb54 LEA R8,[0x14bce6ef0]
1481cdb5b MOV qword ptr [RSP + 0xa8],R12
1481cdb63 LEA R9,[0x140000000]
1481cdb6a MOV qword ptr [RSP + 0xa0],R13
1481cdb72 MOV R13,R15
1481cdb75 MOV qword ptr [RSP + 0x98],R14
1481cdb7d MOV R14,R15
1481cdb80 MOVAPS xmmword ptr [RSP + 0x80],XMM6
1481cdb88 MOVSD XMM6,qword ptr [0x14bcefa00]
1481cdb90 MOVAPS xmmword ptr [RSP + 0x70],XMM7
1481cdb95 MOVSS XMM7,dword ptr [0x14bd1786c]
1481cdb9d MOVAPS xmmword ptr [RSP + 0x60],XMM8
1481cdba3 MOVSS XMM8,dword ptr [0x14bcfdb28]
1481cdbac NOP dword ptr [RAX]
1481cdbb0 MOVSXD RCX,dword ptr [RSI + 0x10]
1481cdbb4 MOV R12D,EBP
1481cdbb7 NOT R12D
1481cdbba MOV EAX,R15D
1481cdbbd SHR R12D,0x1f
1481cdbc1 CMP EBP,ECX
1481cdbc3 CMOVL EAX,R12D
1481cdbc7 TEST EAX,EAX
1481cdbc9 JNZ 0x1481cdc13
1481cdbcb MOV R9,qword ptr [RSP + 0xc8]
1481cdbd3 LEA RDX,[0x14cf27ac0]
1481cdbda MOV RAX,RCX
1481cdbdd MOVSXD RCX,EBP
1481cdbe0 MOV qword ptr [RSP + 0x30],RAX
1481cdbe5 MOV qword ptr [RSP + 0x28],RCX
1481cdbea LEA RCX,[0x14bce6f68]
1481cdbf1 MOV qword ptr [RSP + 0x20],R8
1481cdbf6 MOV R8D,0x303
1481cdbfc CALL 0x140f8dfd0
1481cdc01 TEST AL,AL
1481cdc03 JZ 0x1481cdc07
1481cdc05 NOP
1481cdc06 INT3
1481cdc07 MOVZX EDX,byte ptr [RSP + 0x40]
1481cdc0c LEA R9,[0x140000000]
1481cdc13 MOV R15,qword ptr [RSI + 0x8]
1481cdc17 MOVZX EAX,byte ptr [RSP + 0xe0]
1481cdc1f CMP byte ptr [R14 + R15*0x1],AL
1481cdc23 JNZ 0x1481cdf2e
1481cdc29 MOV RCX,qword ptr [RSP + 0x48]
1481cdc2e CMP byte ptr [RCX + 0x68],0x0
1481cdc32 JNZ 0x1481cde49
1481cdc38 CMP EAX,0x1d
1481cdc3b JA 0x1481cde3b
1481cdc41 MOV ECX,dword ptr [R9 + RAX*0x4 + 0x81cdfe8]
1481cdc49 ADD RCX,R9
1481cdc4c JMP RCX
1481cde3b MOV EAX,dword ptr [R14 + R15*0x1 + 0xc]
1481cde40 ADD EAX,EBX
1481cde42 MOV dword ptr [R14 + R15*0x1 + 0xc],EAX
1481cde47 JMP 0x1481cde4e
1481cde49 ADD dword ptr [R14 + R15*0x1 + 0xc],EBX
1481cde4e MOV byte ptr [RSP + 0x41],0x1
1481cde53 TEST EBP,EBP
1481cde55 JS 0x1481cdf29
1481cde5b CMP EBP,dword ptr [RSI + 0x28]
1481cde5e JGE 0x1481cdf29
1481cde64 MOVSXD RCX,dword ptr [RSI + 0x28]
1481cde68 XOR EAX,EAX
1481cde6a CMP EBP,ECX
1481cde6c CMOVL EAX,R12D
1481cde70 TEST EAX,EAX
1481cde72 JNZ 0x1481cdeb7
1481cde74 MOV R9,qword ptr [RSP + 0xc8]
1481cde7c LEA RDX,[0x14cf27ac0]
1481cde83 MOV RAX,RCX
1481cde86 MOV R8D,0x303
1481cde8c MOV qword ptr [RSP + 0x30],RAX
1481cde91 LEA RAX,[0x14bce6ef0]
1481cde98 MOVSXD RCX,EBP
1481cde9b MOV qword ptr [RSP + 0x28],RCX
1481cdea0 LEA RCX,[0x14bce6f68]
1481cdea7 MOV qword ptr [RSP + 0x20],RAX
1481cdeac CALL 0x140f8dfd0
1481cdeb1 TEST AL,AL
1481cdeb3 JZ 0x1481cdeb7
1481cdeb5 NOP
1481cdeb6 INT3
1481cdeb7 MOV RAX,qword ptr [RSI + 0x20]
1481cdebb MOV R15D,dword ptr [R14 + R15*0x1 + 0xc]
1481cdec0 CMP R15D,dword ptr [RAX + R13*0x1]
1481cdec4 JLE 0x1481cdf29
1481cdec6 MOVSXD RCX,dword ptr [RSI + 0x28]
1481cdeca XOR EAX,EAX
1481cdecc CMP EBP,ECX
1481cdece CMOVL EAX,R12D
1481cded2 TEST EAX,EAX
1481cded4 JNZ 0x1481cdf19
1481cded6 MOV R9,qword ptr [RSP + 0xc8]
1481cdede LEA RDX,[0x14cf27ac0]
1481cdee5 MOV RAX,RCX
1481cdee8 MOV R8D,0x303
1481cdeee MOV qword ptr [RSP + 0x30],RAX
1481cdef3 LEA RAX,[0x14bce6ef0]
1481cdefa MOVSXD RCX,EBP
1481cdefd MOV qword ptr [RSP + 0x28],RCX
1481cdf02 LEA RCX,[0x14bce6f68]
1481cdf09 MOV qword ptr [RSP + 0x20],RAX
1481cdf0e CALL 0x140f8dfd0
1481cdf13 TEST AL,AL
1481cdf15 JZ 0x1481cdf19
1481cdf17 NOP
1481cdf18 INT3
1481cdf19 MOV RAX,qword ptr [RSI + 0x20]
1481cdf1d MOV DL,0x1
1481cdf1f MOV byte ptr [RSP + 0x40],DL
1481cdf23 MOV dword ptr [RAX + R13*0x1],R15D
1481cdf27 JMP 0x1481cdf2e
1481cdf29 MOVZX EDX,byte ptr [RSP + 0x40]
1481cdf2e INC EBP
1481cdf30 LEA R8,[0x14bce6ef0]
1481cdf37 ADD R14,0x10
1481cdf3b LEA R9,[0x140000000]
1481cdf42 ADD R13,0x4
1481cdf46 MOV R15D,0x0
1481cdf4c CMP EBP,dword ptr [RSI + 0x10]
1481cdf4f JL 0x1481cdbb0
1481cdf55 MOVAPS XMM8,xmmword ptr [RSP + 0x60]
1481cdf5b MOVAPS XMM7,xmmword ptr [RSP + 0x70]
1481cdf60 MOVAPS XMM6,xmmword ptr [RSP + 0x80]
1481cdf68 MOV R14,qword ptr [RSP + 0x98]
1481cdf70 MOV R13,qword ptr [RSP + 0xa0]
1481cdf78 MOV R12,qword ptr [RSP + 0xa8]
1481cdf80 MOV RBX,qword ptr [RSP + 0x50]
1481cdf85 TEST DL,DL
1481cdf87 JZ 0x1481cdf91
1481cdf89 MOV RCX,RDI
1481cdf8c CALL 0x1481cad00
1481cdf91 CMP byte ptr [RSP + 0x41],R15B
1481cdf96 JZ 0x1481cdfb9
1481cdf98 CMP byte ptr [RSP + 0x42],R15B
1481cdf9d JNZ 0x1481cdfb9
1481cdf9f MOV RDX,RSI
1481cdfa2 MOV RCX,RDI
1481cdfa5 CALL 0x1481b4920
1481cdfaa TEST AL,AL
1481cdfac JZ 0x1481cdfb9
1481cdfae MOV RDX,RBX
1481cdfb1 MOV RCX,RDI
1481cdfb4 CALL 0x1481b5dc0
1481cdfb9 LEA RCX,[RDI + 0x28]
1481cdfbd MOV RDX,RBX
1481cdfc0 CALL 0x148155da0
1481cdfc5 MOV RBP,qword ptr [RSP + 0xd0]
1481cdfcd MOV RSI,qword ptr [RSP + 0xb0]
1481cdfd5 MOV R15,qword ptr [RSP + 0x90]
1481cdfdd ADD RSP,0xb8
1481cdfe4 POP RDI
1481cdfe5 POP RBX
1481cdfe6 RET
*/

/* 1481c4080 InitializeChallenges */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void InitializeChallenges(longlong param_1)

{
  ulonglong *puVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  bool bVar4;
  code *pcVar5;
  char cVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined8 *puVar10;
  longlong lVar11;
  longlong lVar12;
  ulonglong *puVar13;
  ulonglong *puVar14;
  longlong lVar15;
  ulonglong uVar16;
  undefined1 *puVar17;
  ulonglong uVar18;
  longlong *plVar19;
  int iVar20;
  uint uVar21;
  longlong lVar22;
  undefined *puVar23;
  ulonglong **ppuVar24;
  int iVar25;
  undefined8 unaff_retaddr;
  undefined1 auStack_228 [32];
  undefined *puStack_208;
  longlong lStack_200;
  longlong lStack_1f8;
  undefined1 uStack_1e8;
  undefined1 auStack_1e7 [7];
  ulonglong uStack_1e0;
  longlong lStack_1d8;
  ulonglong uStack_1d0;
  undefined2 uStack_1c8;
  undefined4 uStack_1c4;
  ulonglong uStack_1c0;
  undefined8 uStack_1b8;
  uint uStack_1b0;
  longlong lStack_1a8;
  undefined8 *puStack_1a0;
  uint uStack_198;
  longlong *plStack_190;
  longlong lStack_188;
  int iStack_180;
  undefined8 *apuStack_178 [2];
  undefined1 auStack_168 [4];
  undefined1 auStack_164 [4];
  undefined1 auStack_160 [4];
  undefined8 uStack_15c;
  undefined8 uStack_154;
  undefined *puStack_148;
  int iStack_140;
  undefined *puStack_138;
  int iStack_130;
  ulonglong *puStack_128;
  ulonglong *puStack_120;
  ulonglong *puStack_118;
  ulonglong *puStack_110;
  longlong lStack_108;
  ulonglong *puStack_100;
  longlong alStack_f8 [2];
  longlong alStack_e8 [2];
  longlong lStack_d8;
  undefined8 uStack_d0;
  longlong lStack_b8;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  int iStack_a4;
  undefined1 auStack_a0 [8];
  undefined1 *puStack_98;
  int iStack_90;
  longlong lStack_88;
  undefined8 uStack_80;
  longlong lStack_68;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  int iStack_54;
  undefined1 auStack_50 [8];
  undefined1 *puStack_48;
  int iStack_40;
  ulonglong uStack_38;
  
  uStack_38 = _DAT_14ea60b28 ^ (ulonglong)auStack_228;
  uVar16 = 0;
  uStack_1b0 = 0;
  lStack_1a8 = param_1;
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf714a0);
  }
  if (*(longlong *)(param_1 + 0x60) == 0) {
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71508);
    }
  }
  else {
    uVar18 = uVar16;
    if (2 < DAT_14eab53c8) {
      uStack_15c = *(undefined8 *)(*(longlong *)(param_1 + 0x60) + 0x18);
      func_0x0001411de0e0(&uStack_15c,&puStack_148);
      uVar18 = 2;
      uStack_1b0 = 2;
      puVar23 = &UNK_14bce4e94;
      if (iStack_140 != 0) {
        puVar23 = puStack_148;
      }
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71568,puVar23);
      if (puStack_148 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      if (2 < DAT_14eab53c8) {
        puVar10 = (undefined8 *)func_0x00014192e690(*(undefined8 *)(param_1 + 0x60),alStack_f8,0);
        if (*(int *)(puVar10 + 1) == 0) {
          puVar23 = &UNK_14bce4e94;
        }
        else {
          puVar23 = (undefined *)*puVar10;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf715d0,puVar23);
        if (alStack_f8[0] != 0) {
          func_0x000140e282f0();
        }
      }
    }
    func_0x0001468fb0a0(*(undefined8 *)(param_1 + 0x60),&lStack_188);
    if (2 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71610,iStack_180);
    }
    if (iStack_180 == 0) {
      if ((1 < DAT_14eab53c8) &&
         (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71670), 1 < DAT_14eab53c8)) {
        lVar11 = *(longlong *)(*(longlong *)(param_1 + 0x60) + 0x28);
        if (lVar11 == 0) {
          puVar23 = &UNK_14be6ede0;
        }
        else {
          uStack_154 = *(undefined8 *)(lVar11 + 0x18);
          func_0x0001411de0e0(&uStack_154,&puStack_138);
          uStack_1b0 = (uint)uVar18 | 5;
          uVar18 = (ulonglong)uStack_1b0;
          puVar23 = &UNK_14bce4e94;
          if (iStack_130 != 0) {
            puVar23 = puStack_138;
          }
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71720,puVar23);
        if (((uVar18 & 1) != 0) && (puStack_138 != (undefined *)0x0)) {
          func_0x000140e282f0();
        }
      }
    }
    else {
      iVar7 = iStack_180;
      if (5 < iStack_180) {
        iVar7 = 5;
      }
      uVar18 = uVar16;
      if (0 < iVar7) {
        do {
          uVar21 = (uint)uVar16;
          if (2 < DAT_14eab53c8) {
            uVar8 = 0;
            if ((int)uVar21 < iStack_180) {
              uVar8 = ~uVar21 >> 0x1f;
            }
            if (uVar8 == 0) {
              lStack_200 = (longlong)(int)uVar21;
              lStack_1f8 = (longlong)iStack_180;
              puStack_208 = &UNK_14bce6ef0;
              cVar6 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr);
              if (cVar6 != '\0') {
                pcVar5 = (code *)swi(3);
                (*pcVar5)();
                return;
              }
            }
            puVar10 = (undefined8 *)
                      func_0x0001411de0e0(lStack_188 + (longlong)(int)uVar21 * 8,alStack_e8);
            if (*(int *)(puVar10 + 1) == 0) {
              puVar23 = &UNK_14bce4e94;
            }
            else {
              puVar23 = (undefined *)*puVar10;
            }
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71760,uVar16,puVar23);
            if (alStack_e8[0] != 0) {
              func_0x000140e282f0();
            }
          }
          uVar3 = *(undefined8 *)(param_1 + 0x60);
          uVar8 = 0;
          if ((int)uVar21 < iStack_180) {
            uVar8 = ~uVar21 >> 0x1f;
          }
          if (uVar8 == 0) {
            lStack_1f8 = (longlong)iStack_180;
            puStack_208 = &UNK_14bce6ef0;
            lStack_200 = (longlong)(int)uVar21;
            cVar6 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr);
            if (cVar6 != '\0') {
              pcVar5 = (code *)swi(3);
              (*pcVar5)();
              return;
            }
          }
          lVar11 = func_0x0001481b11d0(uVar3,*(undefined8 *)(lStack_188 + uVar18),&UNK_14bce4e94,1);
          if (lVar11 == 0) {
            if (1 < DAT_14eab53c8) {
              func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71828);
            }
          }
          else if (2 < DAT_14eab53c8) {
            uVar2 = *(undefined4 *)(lVar11 + 0x60);
            puVar10 = (undefined8 *)func_0x000140ef8a00(lVar11 + 0x10);
            if (*(int *)(puVar10 + 1) == 0) {
              puVar23 = &UNK_14bce4e94;
            }
            else {
              puVar23 = (undefined *)*puVar10;
            }
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf717a8,puVar23,uVar2);
          }
          uVar16 = (ulonglong)(uVar21 + 1);
          iVar7 = iStack_180;
          if (5 < iStack_180) {
            iVar7 = 5;
          }
          param_1 = lStack_1a8;
          uVar18 = uVar18 + 8;
        } while ((int)(uVar21 + 1) < iVar7);
      }
      if (2 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf718b0);
      }
      plStack_190 = &lStack_88;
      lStack_88 = 0;
      uStack_80 = 0;
      lStack_68 = 0;
      uStack_60 = 0;
      uStack_5c = 0x80;
      uStack_58 = 0xffffffff;
      iStack_54 = 0;
      puStack_48 = (undefined1 *)0x0;
      iStack_40 = 0;
      lVar11 = param_1 + 0xa0;
      func_0x0001481b3950(&lStack_88,lVar11);
      plStack_190 = &lStack_d8;
      lStack_d8 = 0;
      uStack_d0 = 0;
      lStack_b8 = 0;
      uStack_b0 = 0;
      uStack_ac = 0x80;
      uStack_a8 = 0xffffffff;
      iStack_a4 = 0;
      puStack_98 = (undefined1 *)0x0;
      iStack_90 = 0;
      lVar12 = param_1 + 0xf0;
      func_0x0001481b3950(&lStack_d8,lVar12);
      if (*(int *)(param_1 + 0xe8) < 2) {
        func_0x0001481cca20(lVar11);
        func_0x000148155670(lVar11,0);
      }
      else {
        func_0x000148155670(lVar11,0);
        *(undefined4 *)(param_1 + 0xe8) = 1;
        func_0x0001481c9190(lVar11);
      }
      if (*(int *)(param_1 + 0x138) < 2) {
        func_0x0001481cca20(lVar12);
        func_0x000148155670(lVar12,0);
      }
      else {
        func_0x000148155670(lVar12,0);
        *(undefined4 *)(param_1 + 0x138) = 1;
        func_0x0001481c9190(lVar12);
      }
      lVar11 = param_1 + 0x1e0;
      bVar4 = *(int *)(param_1 + 0x228) < 2;
      if (bVar4) {
        func_0x0001481cd0e0(lVar11);
      }
      *(undefined4 *)(param_1 + 0x1e8) = 0;
      if (*(int *)(param_1 + 0x1ec) != 0) {
        func_0x000140d78450(lVar11,0);
      }
      *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x214) = 0;
      *(undefined4 *)(param_1 + 0x208) = 0;
      if (0x80 < *(uint *)(param_1 + 0x20c)) {
        *(undefined4 *)(param_1 + 0x20c) = 0x80;
        func_0x000140d182e0(param_1 + 0x1f0,0);
      }
      if (!bVar4) {
        *(undefined4 *)(param_1 + 0x228) = 1;
        func_0x0001481c9670(lVar11);
      }
      func_0x0001468fb0a0(*(undefined8 *)(param_1 + 0x60),apuStack_178);
      uStack_198 = (uint)apuStack_178[1];
      uVar16 = (ulonglong)(int)uStack_198;
      plVar19 = apuStack_178[0] + uVar16;
      puVar10 = apuStack_178[0];
      plStack_190 = plVar19;
      while( true ) {
        puStack_1a0 = puVar10;
        if ((int)apuStack_178[1] != (int)uVar16) {
          uStack_1e8 = 0;
          cVar6 = func_0x00014bae9430(&uStack_1e8);
          if (cVar6 != '\0') {
            pcVar5 = (code *)swi(3);
            (*pcVar5)();
            return;
          }
        }
        if (puVar10 == plVar19) break;
        lVar12 = func_0x0001481b11d0(*(undefined8 *)(param_1 + 0x60),*puVar10,&UNK_14bce4e94);
        if (lVar12 != 0) {
          puVar1 = (ulonglong *)(lVar12 + 8);
          uVar16 = *puVar1;
          iVar7 = (int)(uVar16 >> 0x20);
          if (*(char *)(lVar12 + 0x68) == '\0') {
            iVar9 = func_0x0001411c2eb0(uVar16 & 0xffffffff);
            if ((int)uStack_d0 != iStack_a4) {
              puVar17 = auStack_a0;
              if (puStack_98 != (undefined1 *)0x0) {
                puVar17 = puStack_98;
              }
              iVar7 = *(int *)(puVar17 + (ulonglong)(iStack_90 - 1U & iVar9 + iVar7) * 4);
              while (iVar7 != -1) {
                puVar13 = (ulonglong *)((longlong)iVar7 * 0x40 + lStack_d8);
                if (*puVar13 == uVar16) {
                  puVar14 = puVar13 + 1;
                  if (puVar13 == (ulonglong *)0x0) {
                    puVar14 = (ulonglong *)0x0;
                  }
                  goto LAB_1481c475f;
                }
                iVar7 = (int)puVar13[7];
              }
            }
            puVar14 = (ulonglong *)0x0;
          }
          else {
            iVar9 = func_0x0001411c2eb0(uVar16 & 0xffffffff);
            if ((int)uStack_80 != iStack_54) {
              puVar17 = auStack_50;
              if (puStack_48 != (undefined1 *)0x0) {
                puVar17 = puStack_48;
              }
              iVar7 = *(int *)(puVar17 + (ulonglong)(iStack_40 - 1U & iVar9 + iVar7) * 4);
              while (iVar7 != -1) {
                puVar14 = (ulonglong *)((longlong)iVar7 * 0x40 + lStack_88);
                if (*puVar14 == uVar16) {
                  if (puVar14 != (ulonglong *)0x0) {
                    puVar14 = puVar14 + 1;
                    goto LAB_1481c475f;
                  }
                  break;
                }
                iVar7 = (int)puVar14[7];
              }
            }
            puVar14 = (ulonglong *)0x0;
          }
LAB_1481c475f:
          uVar16 = 0;
          lStack_1d8 = 0;
          uStack_1d0 = 0;
          uStack_1c8 = 0;
          uStack_1c4 = 0;
          uStack_1c0 = 0;
          uStack_1b8 = 0;
          if (puVar14 == (ulonglong *)0x0) {
            uStack_1e0 = *puVar1;
            if (&lStack_1d8 != (longlong *)(lVar12 + 0x58)) {
              uVar21 = *(uint *)(lVar12 + 0x60);
              lVar15 = *(longlong *)(lVar12 + 0x58);
              uStack_1d0 = (ulonglong)uVar21;
              if (uVar21 == 0) {
                uStack_1d0 = 0;
              }
              else {
                func_0x000148157ec0(&lStack_1d8,uVar21,0);
                func_0x00014b89502e(lStack_1d8,lVar15,(longlong)(int)uVar21 << 4);
                uVar16 = uStack_1b8 & 0xffffffff;
              }
            }
            uStack_1c8 = 0;
            iVar7 = *(int *)(lVar12 + 0x60);
            iVar9 = (int)uVar16;
            if (iVar9 < iVar7) {
              uVar21 = iVar7 - iVar9;
              uStack_1b8 = CONCAT44(uStack_1b8._4_4_,iVar9 + uVar21);
              if ((uint)(uStack_1b8._4_4_ - iVar9) < uVar21) {
                func_0x000140d21490(&uStack_1c0,uVar16);
              }
              func_0x00014b895046(uStack_1c0 + (longlong)iVar9 * 4,0,(longlong)(int)uVar21 << 2);
            }
            else {
              if (iVar7 < 0) {
                func_0x000140d14f00(iVar7);
                pcVar5 = (code *)swi(3);
                (*pcVar5)();
                return;
              }
              puVar10 = puStack_1a0;
              if ((iVar9 <= iVar7) || (iVar20 = iVar9 - iVar7, iVar20 == 0)) goto LAB_1481c495a;
              iVar25 = (iVar9 - iVar20) - iVar7;
              if (iVar25 != 0) {
                func_0x00014b89503a(uStack_1c0 + (longlong)iVar7 * 4,
                                    uStack_1c0 + (longlong)(iVar20 + iVar7) * 4,
                                    (longlong)iVar25 << 2);
                iVar9 = (int)uStack_1b8;
              }
              uStack_1b8 = CONCAT44(uStack_1b8._4_4_,iVar9 - iVar20);
              func_0x000140d22fa0(&uStack_1c0);
            }
            uVar16 = uStack_1b8 & 0xffffffff;
            puVar10 = puStack_1a0;
          }
          else {
            uStack_1e0 = *puVar14;
            func_0x000148152d60(&lStack_1d8,puVar14 + 1);
            uStack_1c8 = (undefined2)puVar14[3];
            uStack_1c4 = *(undefined4 *)((longlong)puVar14 + 0x1c);
            if (&uStack_1c0 != puVar14 + 4) {
              iVar7 = (int)puVar14[5];
              uVar16 = puVar14[4];
              uStack_1b8 = CONCAT44(uStack_1b8._4_4_,iVar7);
              if ((iVar7 == 0) && (uStack_1b8._4_4_ == 0)) {
                uStack_1b8 = 0;
                uVar16 = 0;
                goto LAB_1481c495a;
              }
              func_0x000140d20ea0(&uStack_1c0,iVar7);
              if (iVar7 != 0) {
                func_0x00014b89502e(uStack_1c0,uVar16,(longlong)iVar7 << 2);
              }
            }
            uVar16 = uStack_1b8 & 0xffffffff;
          }
LAB_1481c495a:
          iVar7 = *(int *)(lVar12 + 0x60);
          iVar9 = (int)uVar16;
          if (iVar9 != iVar7) {
            if (iVar9 < iVar7) {
              uVar21 = iVar7 - iVar9;
              uStack_1b8 = CONCAT44(uStack_1b8._4_4_,iVar9 + uVar21);
              if ((uint)(uStack_1b8._4_4_ - iVar9) < uVar21) {
                func_0x000140d21490(&uStack_1c0,uVar16);
              }
              func_0x00014b895046(uStack_1c0 + (longlong)iVar9 * 4,0,(longlong)(int)uVar21 << 2);
            }
            else {
              if (iVar7 < 0) {
                func_0x000140d14f00(iVar7);
                pcVar5 = (code *)swi(3);
                (*pcVar5)();
                return;
              }
              if ((iVar7 < iVar9) && (iVar20 = iVar9 - iVar7, iVar20 != 0)) {
                iVar25 = (iVar9 - iVar20) - iVar7;
                if (iVar25 != 0) {
                  func_0x00014b89503a(uStack_1c0 + (longlong)iVar7 * 4,
                                      uStack_1c0 + (longlong)(iVar20 + iVar7) * 4,
                                      (longlong)iVar25 << 2);
                  iVar9 = (int)uStack_1b8;
                }
                uStack_1b8 = CONCAT44(uStack_1b8._4_4_,iVar9 - iVar20);
                func_0x000140d22fa0(&uStack_1c0);
              }
            }
          }
          if (*(char *)(lVar12 + 0x68) == '\0') {
            puVar17 = auStack_168;
            lVar15 = lStack_1a8 + 0xf0;
            ppuVar24 = &puStack_128;
            puStack_128 = puVar1;
            puStack_120 = &uStack_1e0;
          }
          else {
            ppuVar24 = &puStack_118;
            puVar17 = auStack_164;
            lVar15 = lStack_1a8 + 0xa0;
            puStack_118 = puVar1;
            puStack_110 = &uStack_1e0;
          }
          func_0x0001481b0870(lVar15,puVar17,ppuVar24);
          lVar15 = *(longlong *)(lVar12 + 0x58);
          iVar7 = *(int *)(lVar12 + 0x60);
          lVar22 = (longlong)iVar7 * 0x10 + lVar15;
          while( true ) {
            if (*(int *)(lVar12 + 0x60) != iVar7) {
              auStack_1e7[0] = 0;
              cVar6 = func_0x00014bc1d120(auStack_1e7);
              if (cVar6 != '\0') {
                pcVar5 = (code *)swi(3);
                (*pcVar5)();
                return;
              }
            }
            if (lVar15 == lVar22) break;
            lStack_108 = lVar15;
            puStack_100 = puVar1;
            func_0x0001481b0d30(lVar11,auStack_160,&lStack_108,0);
            lVar15 = lVar15 + 0x10;
          }
          if (uStack_1c0 != 0) {
            func_0x000140e282f0();
          }
          plVar19 = plStack_190;
          param_1 = lStack_1a8;
          if (lStack_1d8 != 0) {
            func_0x000140e282f0();
            plVar19 = plStack_190;
            param_1 = lStack_1a8;
          }
        }
        puVar10 = puVar10 + 1;
        uVar16 = (ulonglong)uStack_198;
      }
      if (2 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71958,
                            *(int *)(param_1 + 0xa8) - *(int *)(param_1 + 0xd4),
                            *(int *)(param_1 + 0xf8) - *(int *)(param_1 + 0x124));
      }
      if (apuStack_178[0] != (undefined8 *)0x0) {
        func_0x000140e282f0();
      }
      iStack_90 = 0;
      if (puStack_98 != (undefined1 *)0x0) {
        func_0x000140e282f0();
      }
      func_0x000148155670(&lStack_d8,0);
      if (lStack_b8 != 0) {
        func_0x000140e282f0();
      }
      if (lStack_d8 != 0) {
        func_0x000140e282f0();
      }
      iStack_40 = 0;
      if (puStack_48 != (undefined1 *)0x0) {
        func_0x000140e282f0();
      }
      func_0x000148155670(&lStack_88,0);
      if (lStack_68 != 0) {
        func_0x000140e282f0();
      }
      if (lStack_88 != 0) {
        func_0x000140e282f0();
      }
    }
    if (lStack_188 != 0) {
      func_0x000140e282f0();
    }
  }
  func_0x00014b880380(uStack_38 ^ (ulonglong)auStack_228);
  return;
}


/* Instruction evidence:
1481c4080 MOV qword ptr [RSP + 0x10],RBX
1481c4085 MOV qword ptr [RSP + 0x18],RSI
1481c408a MOV qword ptr [RSP + 0x20],RDI
1481c408f PUSH RBP
1481c4090 PUSH R12
1481c4092 PUSH R13
1481c4094 PUSH R14
1481c4096 PUSH R15
1481c4098 LEA RBP,[RSP + -0x100]
1481c40a0 SUB RSP,0x200
1481c40a7 MOV RAX,qword ptr [0x14ea60b28]
1481c40ae XOR RAX,RSP
1481c40b1 MOV qword ptr [RBP + 0xf0],RAX
1481c40b8 MOV RSI,RCX
1481c40bb MOV qword ptr [RBP + -0x80],RCX
1481c40bf XOR R12D,R12D
1481c40c2 MOV EBX,R12D
1481c40c5 MOV dword ptr [RSP + 0x78],EBX
1481c40c9 MOVZX EAX,byte ptr [0x14eab53c8]
1481c40d0 CMP AL,0x3
1481c40d2 JC 0x1481c40ee
1481c40d4 LEA RDX,[0x14cf714a0]
1481c40db LEA RCX,[0x14eab53c8]
1481c40e2 CALL 0x140f24ba0
1481c40e7 MOVZX EAX,byte ptr [0x14eab53c8]
1481c40ee MOV RDX,qword ptr [RSI + 0x60]
1481c40f2 TEST RDX,RDX
1481c40f5 JNZ 0x1481c4117
1481c40f7 CMP AL,0x2
1481c40f9 JC 0x1481c4bb1
1481c40ff LEA RDX,[0x14cf71508]
1481c4106 LEA RCX,[0x14eab53c8]
1481c410d CALL 0x140f24ba0
1481c4112 JMP 0x1481c4bb1
1481c4117 LEA R15,[0x14bce4e94]
1481c411e CMP AL,0x3
1481c4120 JC 0x1481c41be
1481c4126 MOV RAX,qword ptr [RDX + 0x18]
1481c412a MOV qword ptr [RBP + -0x34],RAX
1481c412e LEA RDX,[RBP + -0x20]
1481c4132 LEA RCX,[RBP + -0x34]
1481c4136 CALL 0x1411de0e0
1481c413b MOV EBX,0x2
1481c4140 MOV dword ptr [RSP + 0x78],EBX
1481c4144 MOV R8,R15
1481c4147 CMP dword ptr [RBP + -0x18],0x0
1481c414b CMOVNZ R8,qword ptr [RBP + -0x20]
1481c4150 LEA RDX,[0x14cf71568]
1481c4157 LEA RCX,[0x14eab53c8]
1481c415e CALL 0x140f24ba0
1481c4163 NOP
1481c4164 MOV RCX,qword ptr [RBP + -0x20]
1481c4168 TEST RCX,RCX
1481c416b JZ 0x1481c4173
1481c416d CALL 0x140e282f0
1481c4172 NOP
1481c4173 CMP byte ptr [0x14eab53c8],0x3
1481c417a JC 0x1481c41be
1481c417c XOR R8D,R8D
1481c417f LEA RDX,[RBP + 0x30]
1481c4183 MOV RCX,qword ptr [RSI + 0x60]
1481c4187 CALL 0x14192e690
1481c418c NOP
1481c418d CMP dword ptr [RAX + 0x8],0x0
1481c4191 JZ 0x1481c4198
1481c4193 MOV R8,qword ptr [RAX]
1481c4196 JMP 0x1481c419b
1481c4198 MOV R8,R15
1481c419b LEA RDX,[0x14cf715d0]
1481c41a2 LEA RCX,[0x14eab53c8]
1481c41a9 CALL 0x140f24ba0
1481c41ae NOP
1481c41af MOV RCX,qword ptr [RBP + 0x30]
1481c41b3 TEST RCX,RCX
1481c41b6 JZ 0x1481c41be
1481c41b8 CALL 0x140e282f0
1481c41bd NOP
1481c41be LEA RDX,[RBP + -0x60]
1481c41c2 MOV RCX,qword ptr [RSI + 0x60]
1481c41c6 CALL 0x1468fb0a0
1481c41cb NOP
1481c41cc CMP byte ptr [0x14eab53c8],0x3
1481c41d3 JC 0x1481c41ec
1481c41d5 MOV R8D,dword ptr [RBP + -0x58]
1481c41d9 LEA RDX,[0x14cf71610]
1481c41e0 LEA RCX,[0x14eab53c8]
1481c41e7 CALL 0x140f24ba0
1481c41ec MOV EDX,dword ptr [RBP + -0x58]
1481c41ef TEST EDX,EDX
1481c41f1 JNZ 0x1481c4296
1481c41f7 CMP byte ptr [0x14eab53c8],0x2
1481c41fe JC 0x1481c4ba2
1481c4204 LEA RDX,[0x14cf71670]
1481c420b LEA RCX,[0x14eab53c8]
1481c4212 CALL 0x140f24ba0
1481c4217 CMP byte ptr [0x14eab53c8],0x2
1481c421e JC 0x1481c4ba2
1481c4224 MOV RAX,qword ptr [RSI + 0x60]
1481c4228 MOV RAX,qword ptr [RAX + 0x28]
1481c422c TEST RAX,RAX
1481c422f JZ 0x1481c425b
1481c4231 MOV RAX,qword ptr [RAX + 0x18]
1481c4235 MOV qword ptr [RBP + -0x2c],RAX
1481c4239 LEA RDX,[RBP + -0x10]
1481c423d LEA RCX,[RBP + -0x2c]
1481c4241 CALL 0x1411de0e0
1481c4246 OR EBX,0x4
1481c4249 OR EBX,0x1
1481c424c MOV dword ptr [RSP + 0x78],EBX
1481c4250 CMP dword ptr [RBP + -0x8],0x0
1481c4254 CMOVNZ R15,qword ptr [RBP + -0x10]
1481c4259 JMP 0x1481c4262
1481c425b LEA R15,[0x14be6ede0]
1481c4262 MOV R8,R15
1481c4265 LEA RDX,[0x14cf71720]
1481c426c LEA RCX,[0x14eab53c8]
1481c4273 CALL 0x140f24ba0
1481c4278 NOP
1481c4279 TEST BL,0x1
1481c427c JZ 0x1481c4ba2
1481c4282 MOV RCX,qword ptr [RBP + -0x10]
1481c4286 TEST RCX,RCX
1481c4289 JZ 0x1481c4291
1481c428b CALL 0x140e282f0
1481c4290 NOP
1481c4291 JMP 0x1481c4ba2
1481c4296 MOV EBX,R12D
1481c4299 MOV EAX,EDX
1481c429b MOV R13D,0x5
1481c42a1 CMP EDX,R13D
1481c42a4 CMOVG EAX,R13D
1481c42a8 TEST EAX,EAX
1481c42aa JLE 0x1481c4459
1481c42b0 MOV R14,R12
1481c42b3 LEA R8,[0x14bce6ef0]
1481c42ba NOP word ptr [RAX + RAX*0x1]
1481c42c0 CMP byte ptr [0x14eab53c8],0x3
1481c42c7 JC 0x1481c4370
1481c42cd MOV ECX,EBX
1481c42cf NOT ECX
1481c42d1 SHR ECX,0x1f
1481c42d4 MOV EAX,R12D
1481c42d7 CMP EBX,EDX
1481c42d9 CMOVL EAX,ECX
1481c42dc TEST EAX,EAX
1481c42de JNZ 0x1481c431b
1481c42e0 MOVSXD RCX,EBX
1481c42e3 MOVSXD RAX,EDX
1481c42e6 MOV R9,qword ptr [RBP + 0x128]
1481c42ed MOV qword ptr [RSP + 0x30],RAX
1481c42f2 MOV qword ptr [RSP + 0x28],RCX
1481c42f7 MOV qword ptr [RSP + 0x20],R8
1481c42fc MOV R8D,0x303
1481c4302 LEA RDX,[0x14cf27ac0]
1481c4309 LEA RCX,[0x14bce6f68]
1481c4310 CALL 0x140f8dfd0
1481c4315 TEST AL,AL
1481c4317 JZ 0x1481c431b
1481c4319 NOP
1481c431a INT3
1481c431b MOVSXD RDI,EBX
1481c431e MOV RAX,qword ptr [RBP + -0x60]
1481c4322 LEA RCX,[RAX + RDI*0x8]
1481c4326 LEA RDX,[RBP + 0x40]
1481c432a CALL 0x1411de0e0
1481c432f NOP
1481c4330 CMP dword ptr [RAX + 0x8],0x0
1481c4334 JZ 0x1481c433b
1481c4336 MOV R9,qword ptr [RAX]
1481c4339 JMP 0x1481c433e
1481c433b MOV R9,R15
1481c433e MOV R8D,EBX
1481c4341 LEA RDX,[0x14cf71760]
1481c4348 LEA RCX,[0x14eab53c8]
1481c434f CALL 0x140f24ba0
1481c4354 NOP
1481c4355 MOV RCX,qword ptr [RBP + 0x40]
1481c4359 TEST RCX,RCX
1481c435c JZ 0x1481c4364
1481c435e CALL 0x140e282f0
1481c4363 NOP
1481c4364 MOV EDX,dword ptr [RBP + -0x58]
1481c4367 LEA R8,[0x14bce6ef0]
1481c436e JMP 0x1481c4373
1481c4370 MOVSXD RDI,EBX
1481c4373 MOV RSI,qword ptr [RSI + 0x60]
1481c4377 MOV ECX,EBX
1481c4379 NOT ECX
1481c437b SHR ECX,0x1f
1481c437e MOV EAX,R12D
1481c4381 CMP EBX,EDX
1481c4383 CMOVL EAX,ECX
1481c4386 TEST EAX,EAX
1481c4388 JNZ 0x1481c43c2
1481c438a MOVSXD RAX,EDX
1481c438d MOV R9,qword ptr [RBP + 0x128]
1481c4394 MOV qword ptr [RSP + 0x30],RAX
1481c4399 MOV qword ptr [RSP + 0x28],RDI
1481c439e MOV qword ptr [RSP + 0x20],R8
1481c43a3 MOV R8D,0x303
1481c43a9 LEA RDX,[0x14cf27ac0]
1481c43b0 LEA RCX,[0x14bce6f68]
1481c43b7 CALL 0x140f8dfd0
1481c43bc TEST AL,AL
1481c43be JZ 0x1481c43c2
1481c43c0 NOP
1481c43c1 INT3
1481c43c2 MOV RDX,qword ptr [RBP + -0x60]
1481c43c6 MOV R9B,0x1
1481c43c9 MOV R8,R15
1481c43cc MOV RDX,qword ptr [RDX + R14*0x1]
1481c43d0 MOV RCX,RSI
1481c43d3 CALL 0x1481b11d0
1481c43d8 TEST RAX,RAX
1481c43db JZ 0x1481c4418
1481c43dd CMP byte ptr [0x14eab53c8],0x3
1481c43e4 JC 0x1481c4434
1481c43e6 MOV EDI,dword ptr [RAX + 0x60]
1481c43e9 LEA RCX,[RAX + 0x10]
1481c43ed CALL 0x140ef8a00
1481c43f2 CMP dword ptr [RAX + 0x8],0x0
1481c43f6 JZ 0x1481c43fd
1481c43f8 MOV R8,qword ptr [RAX]
1481c43fb JMP 0x1481c4400
1481c43fd MOV R8,R15
1481c4400 MOV R9D,EDI
1481c4403 LEA RDX,[0x14cf717a8]
1481c440a LEA RCX,[0x14eab53c8]
1481c4411 CALL 0x140f24ba0
1481c4416 JMP 0x1481c4434
1481c4418 CMP byte ptr [0x14eab53c8],0x2
1481c441f JC 0x1481c4434
1481c4421 LEA RDX,[0x14cf71828]
1481c4428 LEA RCX,[0x14eab53c8]
1481c442f CALL 0x140f24ba0
1481c4434 INC EBX
1481c4436 ADD R14,0x8
1481c443a MOV EDX,dword ptr [RBP + -0x58]
1481c443d MOV EAX,EDX
1481c443f CMP EDX,0x5
1481c4442 CMOVG EAX,R13D
1481c4446 CMP EBX,EAX
1481c4448 MOV RSI,qword ptr [RBP + -0x80]
1481c444c LEA R8,[0x14bce6ef0]
1481c4453 JL 0x1481c42c0
1481c4459 CMP byte ptr [0x14eab53c8],0x3
1481c4460 JC 0x1481c4475
1481c4462 LEA RDX,[0x14cf718b0]
1481c4469 LEA RCX,[0x14eab53c8]
1481c4470 CALL 0x140f24ba0
1481c4475 LEA RAX,[RBP + 0xa0]
1481c447c MOV qword ptr [RBP + -0x68],RAX
1481c4480 MOV qword ptr [RBP + 0xa0],R12
1481c4487 MOV qword ptr [RBP + 0xa8],R12
1481c448e MOV qword ptr [RBP + 0xc0],R12
1481c4495 MOV dword ptr [RBP + 0xc8],R12D
1481c449c MOV dword ptr [RBP + 0xcc],0x80
1481c44a6 MOV dword ptr [RBP + 0xd0],0xffffffff
1481c44b0 MOV dword ptr [RBP + 0xd4],R12D
1481c44b7 MOV qword ptr [RBP + 0xe0],R12
1481c44be MOV dword ptr [RBP + 0xe8],R12D
1481c44c5 LEA RDI,[RSI + 0xa0]
1481c44cc MOV RDX,RDI
1481c44cf LEA RCX,[RBP + 0xa0]
1481c44d6 CALL 0x1481b3950
1481c44db NOP
1481c44dc LEA RAX,[RBP + 0x50]
1481c44e0 MOV qword ptr [RBP + -0x68],RAX
1481c44e4 MOV qword ptr [RBP + 0x50],R12
1481c44e8 MOV qword ptr [RBP + 0x58],R12
1481c44ec MOV qword ptr [RBP + 0x70],R12
1481c44f0 MOV dword ptr [RBP + 0x78],R12D
1481c44f4 MOV dword ptr [RBP + 0x7c],0x80
1481c44fb MOV dword ptr [RBP + 0x80],0xffffffff
1481c4505 MOV dword ptr [RBP + 0x84],R12D
1481c450c MOV qword ptr [RBP + 0x90],R12
1481c4513 MOV dword ptr [RBP + 0x98],R12D
1481c451a LEA RBX,[RSI + 0xf0]
1481c4521 MOV RDX,RBX
1481c4524 LEA RCX,[RBP + 0x50]
1481c4528 CALL 0x1481b3950
1481c452d NOP
1481c452e MOV RCX,RDI
1481c4531 CMP dword ptr [RDI + 0x48],0x1
1481c4535 JLE 0x1481c454f
1481c4537 XOR EDX,EDX
1481c4539 CALL 0x148155670
1481c453e MOV dword ptr [RDI + 0x48],0x1
1481c4545 MOV RCX,RDI
1481c4548 CALL 0x1481c9190
1481c454d JMP 0x1481c455e
1481c454f CALL 0x1481cca20
1481c4554 XOR EDX,EDX
1481c4556 MOV RCX,RDI
1481c4559 CALL 0x148155670
1481c455e MOV RCX,RBX
1481c4561 CMP dword ptr [RBX + 0x48],0x1
1481c4565 JLE 0x1481c457f
1481c4567 XOR EDX,EDX
1481c4569 CALL 0x148155670
1481c456e MOV dword ptr [RBX + 0x48],0x1
1481c4575 MOV RCX,RBX
1481c4578 CALL 0x1481c9190
1481c457d JMP 0x1481c458e
1481c457f CALL 0x1481cca20
1481c4584 XOR EDX,EDX
1481c4586 MOV RCX,RBX
1481c4589 CALL 0x148155670
1481c458e LEA R13,[RSI + 0x1e0]
1481c4595 CMP dword ptr [R13 + 0x48],0x1
1481c459a JLE 0x1481c45a0
1481c459c MOV BL,0x1
1481c459e JMP 0x1481c45aa
1481c45a0 XOR BL,BL
1481c45a2 MOV RCX,R13
1481c45a5 CALL 0x1481cd0e0
1481c45aa MOV dword ptr [R13 + 0x8],R12D
1481c45ae CMP dword ptr [R13 + 0xc],0x0
1481c45b3 JZ 0x1481c45bf
1481c45b5 XOR EDX,EDX
1481c45b7 MOV RCX,R13
1481c45ba CALL 0x140d78450
1481c45bf MOV dword ptr [R13 + 0x30],0xffffffff
1481c45c7 MOV dword ptr [R13 + 0x34],R12D
1481c45cb LEA RCX,[R13 + 0x10]
1481c45cf MOV dword ptr [RCX + 0x18],R12D
1481c45d3 CMP dword ptr [RCX + 0x1c],0x80
1481c45da JBE 0x1481c45ea
1481c45dc MOV dword ptr [RCX + 0x1c],0x80
1481c45e3 XOR EDX,EDX
1481c45e5 CALL 0x140d182e0
1481c45ea TEST BL,BL
1481c45ec JZ 0x1481c45fe
1481c45ee MOV dword ptr [R13 + 0x48],0x1
1481c45f6 MOV RCX,R13
1481c45f9 CALL 0x1481c9670
1481c45fe LEA RDX,[RBP + -0x50]
1481c4602 MOV RCX,qword ptr [RSI + 0x60]
1481c4606 CALL 0x1468fb0a0
1481c460b NOP
1481c460c MOV R14,qword ptr [RBP + -0x50]
1481c4610 MOV RCX,qword ptr [RBP + -0x48]
1481c4614 MOVSXD RDX,ECX
1481c4617 MOV dword ptr [RBP + -0x70],EDX
1481c461a LEA RBX,[R14 + RDX*0x8]
1481c461e MOV qword ptr [RBP + -0x68],RBX
1481c4622 MOV qword ptr [RBP + -0x78],R14
1481c4626 CMP ECX,EDX
1481c4628 JZ 0x1481c463f
1481c462a MOV byte ptr [RSP + 0x40],0x0
1481c462f LEA RCX,[RSP + 0x40]
1481c4634 CALL 0x14bae9430
1481c4639 TEST AL,AL
1481c463b JZ 0x1481c463f
1481c463d NOP
1481c463e INT3
1481c463f CMP R14,RBX
1481c4642 JZ 0x1481c4ac8
1481c4648 MOV R9B,0x1
1481c464b MOV R8,R15
1481c464e MOV RDX,qword ptr [R14]
1481c4651 MOV RCX,qword ptr [RSI + 0x60]
1481c4655 CALL 0x1481b11d0
1481c465a MOV R15,RAX
1481c465d TEST RAX,RAX
1481c4660 JZ 0x1481c4ab1
1481c4666 LEA R12,[RAX + 0x8]
1481c466a MOV RBX,qword ptr [R12]
1481c466e MOV RDI,RBX
1481c4671 SHR RDI,0x20
1481c4675 MOV ECX,EBX
1481c4677 CMP byte ptr [RAX + 0x68],0x0
1481c467b JNZ 0x1481c46f7
1481c467d CALL 0x1411c2eb0
1481c4682 ADD EAX,EDI
1481c4684 MOV ECX,dword ptr [RBP + 0x58]
1481c4687 CMP ECX,dword ptr [RBP + 0x84]
1481c468d JZ 0x1481c46d7
1481c468f LEA R8,[RBP + 0x88]
1481c4696 MOV RCX,qword ptr [RBP + 0x90]
1481c469d TEST RCX,RCX
1481c46a0 CMOVNZ R8,RCX
1481c46a4 MOV EDX,dword ptr [RBP + 0x98]
1481c46aa DEC EDX
1481c46ac AND RDX,RAX
1481c46af MOV EAX,dword ptr [R8 + RDX*0x4]
1481c46b3 CMP EAX,-0x1
1481c46b6 JZ 0x1481c46d7
1481c46b8 MOV RDX,qword ptr [RBP + 0x50]
1481c46bc NOP dword ptr [RAX]
1481c46c0 MOVSXD RCX,EAX
1481c46c3 SHL RCX,0x6
1481c46c7 ADD RCX,RDX
1481c46ca CMP qword ptr [RCX],RBX
1481c46cd JZ 0x1481c46e8
1481c46cf MOV EAX,dword ptr [RCX + 0x38]
1481c46d2 CMP EAX,-0x1
1481c46d5 JNZ 0x1481c46c0
1481c46d7 XOR EDX,EDX
1481c46d9 MOV ECX,EDX
1481c46db LEA RDI,[RDX + 0x8]
1481c46df TEST RDX,RDX
1481c46e2 CMOVZ RDI,RDX
1481c46e6 JMP 0x1481c475f
1481c46e8 XOR EDX,EDX
1481c46ea LEA RDI,[RCX + 0x8]
1481c46ee TEST RCX,RCX
1481c46f1 CMOVZ RDI,RDX
1481c46f5 JMP 0x1481c475f
1481c46f7 CALL 0x1411c2eb0
1481c46fc ADD EAX,EDI
1481c46fe MOV ECX,dword ptr [RBP + 0xa8]
1481c4704 CMP ECX,dword ptr [RBP + 0xd4]
1481c470a JZ 0x1481c475b
1481c470c LEA R8,[RBP + 0xd8]
1481c4713 MOV RCX,qword ptr [RBP + 0xe0]
1481c471a TEST RCX,RCX
1481c471d CMOVNZ R8,RCX
1481c4721 MOV EDX,dword ptr [RBP + 0xe8]
1481c4727 DEC EDX
1481c4729 AND RDX,RAX
1481c472c MOV EAX,dword ptr [R8 + RDX*0x4]
1481c4730 CMP EAX,-0x1
1481c4733 JZ 0x1481c475b
1481c4735 MOV RDX,qword ptr [RBP + 0xa0]
1481c473c NOP dword ptr [RAX]
1481c4740 MOVSXD RCX,EAX
1481c4743 SHL RCX,0x6
1481c4747 ADD RCX,RDX
1481c474a CMP qword ptr [RCX],RBX
1481c474d JZ 0x1481c480c
1481c4753 MOV EAX,dword ptr [RCX + 0x38]
1481c4756 CMP EAX,-0x1
1481c4759 JNZ 0x1481c4740
1481c475b XOR EDX,EDX
1481c475d MOV EDI,EDX
1481c475f MOV qword ptr [RSP + 0x48],0x0
1481c4768 MOV qword ptr [RSP + 0x50],RDX
1481c476d MOV qword ptr [RSP + 0x58],0x0
1481c4776 MOV word ptr [RSP + 0x60],0x0
1481c477d MOV dword ptr [RSP + 0x64],0x0
1481c4785 MOV R8,RDX
1481c4788 MOV qword ptr [RSP + 0x68],RDX
1481c478d MOV EBX,EDX
1481c478f MOV qword ptr [RSP + 0x70],0x0
1481c4798 LEA RCX,[RSP + 0x50]
1481c479d TEST RDI,RDI
1481c47a0 JZ 0x1481c4856
1481c47a6 MOV RAX,qword ptr [RDI]
1481c47a9 MOV qword ptr [RSP + 0x48],RAX
1481c47ae LEA RDX,[RDI + 0x8]
1481c47b2 CALL 0x148152d60
1481c47b7 MOVZX EAX,byte ptr [RDI + 0x18]
1481c47bb MOV byte ptr [RSP + 0x60],AL
1481c47bf MOVZX EAX,byte ptr [RDI + 0x19]
1481c47c3 MOV byte ptr [RSP + 0x61],AL
1481c47c7 MOVSS XMM0,dword ptr [RDI + 0x1c]
1481c47cc MOVSS dword ptr [RSP + 0x64],XMM0
1481c47d2 ADD RDI,0x20
1481c47d6 LEA RAX,[RSP + 0x68]
1481c47db CMP RAX,RDI
1481c47de JZ 0x1481c4844
1481c47e0 MOVSXD RBX,dword ptr [RDI + 0x8]
1481c47e4 MOV RDI,qword ptr [RDI]
1481c47e7 MOV dword ptr [RSP + 0x70],EBX
1481c47eb MOV R8D,dword ptr [RSP + 0x74]
1481c47f0 TEST EBX,EBX
1481c47f2 JNZ 0x1481c4820
1481c47f4 TEST R8D,R8D
1481c47f7 JNZ 0x1481c4820
1481c47f9 MOV dword ptr [RSP + 0x74],R8D
1481c47fe LEA RAX,[R15 + 0x60]
1481c4802 MOV R8,qword ptr [RSP + 0x68]
1481c4807 JMP 0x1481c495a
1481c480c TEST RCX,RCX
1481c480f JZ 0x1481c475b
1481c4815 LEA RDI,[RCX + 0x8]
1481c4819 XOR EDX,EDX
1481c481b JMP 0x1481c475f
1481c4820 MOV EDX,EBX
1481c4822 LEA RCX,[RSP + 0x68]
1481c4827 CALL 0x140d20ea0
1481c482c TEST EBX,EBX
1481c482e JZ 0x1481c4844
1481c4830 MOV R8,RBX
1481c4833 SHL R8,0x2
1481c4837 MOV RDX,RDI
1481c483a MOV RCX,qword ptr [RSP + 0x68]
1481c483f CALL 0x14b89502e
1481c4844 MOV EBX,dword ptr [RSP + 0x70]
1481c4848 LEA RAX,[R15 + 0x60]
1481c484c MOV R8,qword ptr [RSP + 0x68]
1481c4851 JMP 0x1481c495a
1481c4856 MOV RAX,qword ptr [R12]
1481c485a MOV qword ptr [RSP + 0x48],RAX
1481c485f LEA RAX,[R15 + 0x58]
1481c4863 CMP RCX,RAX
1481c4866 JZ 0x1481c48a9
1481c4868 MOVSXD RDI,dword ptr [RAX + 0x8]
1481c486c MOV RSI,qword ptr [RAX]
1481c486f MOV dword ptr [RSP + 0x58],EDI
1481c4873 TEST EDI,EDI
1481c4875 JNZ 0x1481c487d
1481c4877 MOV dword ptr [RSP + 0x5c],EDX
1481c487b JMP 0x1481c48a9
1481c487d XOR R8D,R8D
1481c4880 MOV EDX,EDI
1481c4882 LEA RCX,[RSP + 0x50]
1481c4887 CALL 0x148157ec0
1481c488c MOV R8,RDI
1481c488f SHL R8,0x4
1481c4893 MOV RDX,RSI
1481c4896 MOV RCX,qword ptr [RSP + 0x50]
1481c489b CALL 0x14b89502e
1481c48a0 MOV EBX,dword ptr [RSP + 0x70]
1481c48a4 MOV R8,qword ptr [RSP + 0x68]
1481c48a9 MOV word ptr [RSP + 0x60],0x0
1481c48b0 MOV EDI,dword ptr [R15 + 0x60]
1481c48b4 CMP EDI,EBX
1481c48b6 JLE 0x1481c48f3
1481c48b8 SUB EDI,EBX
1481c48ba LEA EAX,[RBX + RDI*0x1]
1481c48bd MOV dword ptr [RSP + 0x70],EAX
1481c48c1 MOV EAX,dword ptr [RSP + 0x74]
1481c48c5 SUB EAX,EBX
1481c48c7 CMP EDI,EAX
1481c48c9 JBE 0x1481c48dc
1481c48cb MOV EDX,EBX
1481c48cd LEA RCX,[RSP + 0x68]
1481c48d2 CALL 0x140d21490
1481c48d7 MOV R8,qword ptr [RSP + 0x68]
1481c48dc MOVSXD RAX,EBX
1481c48df LEA RCX,[R8 + RAX*0x4]
1481c48e3 MOVSXD R8,EDI
1481c48e6 SHL R8,0x2
1481c48ea XOR EDX,EDX
1481c48ec CALL 0x14b895046
1481c48f1 JMP 0x1481c4949
1481c48f3 TEST EDI,EDI
1481c48f5 JS 0x1481c4be1
1481c48fb LEA RAX,[R15 + 0x60]
1481c48ff CMP EDI,EBX
1481c4901 JGE 0x1481c4956
1481c4903 MOV ESI,EBX
1481c4905 SUB ESI,EDI
1481c4907 LEA RAX,[R15 + 0x60]
1481c490b JZ 0x1481c4956
1481c490d MOV R9D,EBX
1481c4910 SUB R9D,ESI
1481c4913 SUB R9D,EDI
1481c4916 JZ 0x1481c4939
1481c4918 LEA EAX,[RSI + RDI*0x1]
1481c491b MOVSXD RCX,EAX
1481c491e LEA RDX,[R8 + RCX*0x4]
1481c4922 MOVSXD RAX,EDI
1481c4925 LEA RCX,[R8 + RAX*0x4]
1481c4929 MOVSXD R8,R9D
1481c492c SHL R8,0x2
1481c4930 CALL 0x14b89503a
1481c4935 MOV EBX,dword ptr [RSP + 0x70]
1481c4939 SUB EBX,ESI
1481c493b MOV dword ptr [RSP + 0x70],EBX
1481c493f LEA RCX,[RSP + 0x68]
1481c4944 CALL 0x140d22fa0
1481c4949 MOV R8,qword ptr [RSP + 0x68]
1481c494e MOV EBX,dword ptr [RSP + 0x70]
1481c4952 LEA RAX,[R15 + 0x60]
1481c4956 MOV R14,qword ptr [RBP + -0x78]
1481c495a MOV EDI,dword ptr [RAX]
1481c495c CMP EBX,EDI
1481c495e JZ 0x1481c49ef
1481c4964 JGE 0x1481c49a1
1481c4966 SUB EDI,EBX
1481c4968 LEA EAX,[RBX + RDI*0x1]
1481c496b MOV dword ptr [RSP + 0x70],EAX
1481c496f MOV EAX,dword ptr [RSP + 0x74]
1481c4973 SUB EAX,EBX
1481c4975 CMP EDI,EAX
1481c4977 JBE 0x1481c498a
1481c4979 MOV EDX,EBX
1481c497b LEA RCX,[RSP + 0x68]
1481c4980 CALL 0x140d21490
1481c4985 MOV R8,qword ptr [RSP + 0x68]
1481c498a MOVSXD RAX,EBX
1481c498d LEA RCX,[R8 + RAX*0x4]
1481c4991 MOVSXD R8,EDI
1481c4994 SHL R8,0x2
1481c4998 XOR EDX,EDX
1481c499a CALL 0x14b895046
1481c499f JMP 0x1481c49ef
1481c49a1 TEST EDI,EDI
1481c49a3 JS 0x1481c4bea
1481c49a9 CMP EDI,EBX
1481c49ab JGE 0x1481c49ef
1481c49ad MOV ESI,EBX
1481c49af SUB ESI,EDI
1481c49b1 JZ 0x1481c49ef
1481c49b3 MOV R9D,EBX
1481c49b6 SUB R9D,ESI
1481c49b9 SUB R9D,EDI
1481c49bc JZ 0x1481c49df
1481c49be LEA EAX,[RSI + RDI*0x1]
1481c49c1 MOVSXD RCX,EAX
1481c49c4 LEA RDX,[R8 + RCX*0x4]
1481c49c8 MOVSXD RAX,EDI
1481c49cb LEA RCX,[R8 + RAX*0x4]
1481c49cf MOVSXD R8,R9D
1481c49d2 SHL R8,0x2
1481c49d6 CALL 0x14b89503a
1481c49db MOV EBX,dword ptr [RSP + 0x70]
1481c49df SUB EBX,ESI
1481c49e1 MOV dword ptr [RSP + 0x70],EBX
1481c49e5 LEA RCX,[RSP + 0x68]
1481c49ea CALL 0x140d22fa0
1481c49ef LEA RAX,[RSP + 0x48]
1481c49f4 XOR R9D,R9D
1481c49f7 MOV RCX,qword ptr [RBP + -0x80]
1481c49fb CMP byte ptr [R15 + 0x68],R9B
1481c49ff JNZ 0x1481c4a1a
1481c4a01 MOV qword ptr [RBP],R12
1481c4a05 MOV qword ptr [RBP + 0x8],RAX
1481c4a09 LEA R8,[RBP]
1481c4a0d LEA RDX,[RBP + -0x40]
1481c4a11 ADD RCX,0xf0
1481c4a18 JMP 0x1481c4a31
1481c4a1a MOV qword ptr [RBP + 0x10],R12
1481c4a1e MOV qword ptr [RBP + 0x18],RAX
1481c4a22 LEA R8,[RBP + 0x10]
1481c4a26 LEA RDX,[RBP + -0x3c]
1481c4a2a ADD RCX,0xa0
1481c4a31 CALL 0x1481b0870
1481c4a36 MOV RBX,qword ptr [R15 + 0x58]
1481c4a3a MOVSXD RSI,dword ptr [R15 + 0x60]
1481c4a3e MOV RDI,RSI
1481c4a41 SHL RDI,0x4
1481c4a45 ADD RDI,RBX
1481c4a48 CMP dword ptr [R15 + 0x60],ESI
1481c4a4c JZ 0x1481c4a63
1481c4a4e MOV byte ptr [RSP + 0x41],0x0
1481c4a53 LEA RCX,[RSP + 0x41]
1481c4a58 CALL 0x14bc1d120
1481c4a5d TEST AL,AL
1481c4a5f JZ 0x1481c4a63
1481c4a61 NOP
1481c4a62 INT3
1481c4a63 CMP RBX,RDI
1481c4a66 JZ 0x1481c4a89
1481c4a68 MOV qword ptr [RBP + 0x20],RBX
1481c4a6c MOV qword ptr [RBP + 0x28],R12
1481c4a70 XOR R9D,R9D
1481c4a73 LEA R8,[RBP + 0x20]
1481c4a77 LEA RDX,[RBP + -0x38]
1481c4a7b MOV RCX,R13
1481c4a7e CALL 0x1481b0d30
1481c4a83 ADD RBX,0x10
1481c4a87 JMP 0x1481c4a48
1481c4a89 MOV RCX,qword ptr [RSP + 0x68]
1481c4a8e TEST RCX,RCX
1481c4a91 JZ 0x1481c4a99
1481c4a93 CALL 0x140e282f0
1481c4a98 NOP
1481c4a99 MOV RCX,qword ptr [RSP + 0x50]
1481c4a9e TEST RCX,RCX
1481c4aa1 JZ 0x1481c4aa9
1481c4aa3 CALL 0x140e282f0
1481c4aa8 NOP
1481c4aa9 MOV RBX,qword ptr [RBP + -0x68]
1481c4aad MOV RSI,qword ptr [RBP + -0x80]
1481c4ab1 ADD R14,0x8
1481c4ab5 MOV RCX,qword ptr [RBP + -0x48]
1481c4ab9 MOV EDX,dword ptr [RBP + -0x70]
1481c4abc LEA R15,[0x14bce4e94]
1481c4ac3 JMP 0x1481c4622
1481c4ac8 CMP byte ptr [0x14eab53c8],0x3
1481c4acf JC 0x1481c4b01
1481c4ad1 MOV R9D,dword ptr [RSI + 0xf8]
1481c4ad8 SUB R9D,dword ptr [RSI + 0x124]
1481c4adf MOV R8D,dword ptr [RSI + 0xa8]
1481c4ae6 SUB R8D,dword ptr [RSI + 0xd4]
1481c4aed LEA RDX,[0x14cf71958]
1481c4af4 LEA RCX,[0x14eab53c8]
1481c4afb CALL 0x140f24ba0
1481c4b00 NOP
1481c4b01 MOV RCX,qword ptr [RBP + -0x50]
1481c4b05 TEST RCX,RCX
1481c4b08 JZ 0x1481c4b10
1481c4b0a CALL 0x140e282f0
1481c4b0f NOP
1481c4b10 XOR R12D,R12D
1481c4b13 MOV dword ptr [RBP + 0x98],R12D
1481c4b1a MOV RCX,qword ptr [RBP + 0x90]
1481c4b21 TEST RCX,RCX
1481c4b24 JZ 0x1481c4b2c
1481c4b26 CALL 0x140e282f0
1481c4b2b NOP
1481c4b2c XOR EDX,EDX
1481c4b2e LEA RCX,[RBP + 0x50]
1481c4b32 CALL 0x148155670
1481c4b37 NOP
1481c4b38 MOV RCX,qword ptr [RBP + 0x70]
1481c4b3c TEST RCX,RCX
1481c4b3f JZ 0x1481c4b47
1481c4b41 CALL 0x140e282f0
1481c4b46 NOP
1481c4b47 MOV RCX,qword ptr [RBP + 0x50]
1481c4b4b TEST RCX,RCX
1481c4b4e JZ 0x1481c4b56
1481c4b50 CALL 0x140e282f0
1481c4b55 NOP
1481c4b56 MOV dword ptr [RBP + 0xe8],R12D
1481c4b5d MOV RCX,qword ptr [RBP + 0xe0]
1481c4b64 TEST RCX,RCX
1481c4b67 JZ 0x1481c4b6f
1481c4b69 CALL 0x140e282f0
1481c4b6e NOP
1481c4b6f XOR EDX,EDX
1481c4b71 LEA RCX,[RBP + 0xa0]
1481c4b78 CALL 0x148155670
1481c4b7d NOP
1481c4b7e MOV RCX,qword ptr [RBP + 0xc0]
1481c4b85 TEST RCX,RCX
1481c4b88 JZ 0x1481c4b90
1481c4b8a CALL 0x140e282f0
1481c4b8f NOP
1481c4b90 MOV RCX,qword ptr [RBP + 0xa0]
1481c4b97 TEST RCX,RCX
1481c4b9a JZ 0x1481c4ba2
1481c4b9c CALL 0x140e282f0
1481c4ba1 NOP
1481c4ba2 MOV RCX,qword ptr [RBP + -0x60]
1481c4ba6 TEST RCX,RCX
1481c4ba9 JZ 0x1481c4bb1
1481c4bab CALL 0x140e282f0
1481c4bb0 NOP
1481c4bb1 MOV RCX,qword ptr [RBP + 0xf0]
1481c4bb8 XOR RCX,RSP
1481c4bbb CALL 0x14b880380
1481c4bc0 LEA R11,[RSP + 0x200]
1481c4bc8 MOV RBX,qword ptr [R11 + 0x38]
1481c4bcc MOV RSI,qword ptr [R11 + 0x40]
1481c4bd0 MOV RDI,qword ptr [R11 + 0x48]
1481c4bd4 MOV RSP,R11
1481c4bd7 POP R15
1481c4bd9 POP R14
1481c4bdb POP R13
1481c4bdd POP R12
1481c4bdf POP RBP
1481c4be0 RET
1481c4be1 MOV RCX,RDI
1481c4be4 CALL 0x140d14f00
1481c4be9 INT3
1481c4bea MOV RCX,RDI
1481c4bed CALL 0x140d14f00
1481c4bf2 INT3
*/

/* 1481b5dc0 CompleteChallenge */

void CompleteChallenge(longlong *param_1,ulonglong param_2)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  int iVar3;
  longlong lVar4;
  undefined8 *puVar5;
  longlong lVar6;
  ulonglong *puVar7;
  longlong *plVar8;
  longlong lVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined8 uStackX_8;
  ulonglong uStackX_10;
  longlong alStack_18 [2];
  
  uStackX_8 = param_2;
  uStackX_10 = param_2;
  iVar3 = func_0x0001411c2eb0(param_2 & 0xffffffff);
  uVar2 = uStackX_10;
  if ((int)param_1[0x1f] != *(int *)((longlong)param_1 + 0x124)) {
    plVar8 = param_1 + 0x25;
    if ((longlong *)param_1[0x26] != (longlong *)0x0) {
      plVar8 = (longlong *)param_1[0x26];
    }
    iVar3 = *(int *)((longlong)plVar8 +
                    (ulonglong)((int)param_1[0x27] - 1U & uStackX_8._4_4_ + iVar3) * 4);
    if (iVar3 != -1) {
      lVar4 = param_1[0x1e];
      do {
        lVar6 = (longlong)iVar3 * 0x40;
        if (*(ulonglong *)(lVar6 + lVar4) == param_2) {
          lVar9 = lVar6 + lVar4 + 8;
          if (lVar6 + lVar4 == 0) {
            lVar9 = 0;
          }
          if (lVar9 != 0) goto LAB_1481b5eff;
          break;
        }
        iVar3 = *(int *)(lVar6 + 0x38 + lVar4);
      } while (iVar3 != -1);
    }
  }
  uStackX_8 = uStackX_10;
  iVar3 = func_0x0001411c2eb0(uStackX_10 & 0xffffffff);
  if ((int)param_1[0x15] != *(int *)((longlong)param_1 + 0xd4)) {
    plVar8 = param_1 + 0x1b;
    if ((longlong *)param_1[0x1c] != (longlong *)0x0) {
      plVar8 = (longlong *)param_1[0x1c];
    }
    iVar3 = *(int *)((longlong)plVar8 +
                    (ulonglong)((int)param_1[0x1d] - 1U & uStackX_8._4_4_ + iVar3) * 4);
    if (iVar3 != -1) {
      lVar4 = param_1[0x14];
      while (lVar6 = (longlong)iVar3 * 0x40, *(ulonglong *)(lVar4 + lVar6) != uVar2) {
        iVar3 = *(int *)(lVar4 + 0x38 + lVar6);
        if (iVar3 == -1) {
          return;
        }
      }
      if ((lVar4 + lVar6 != 0) && (lVar9 = lVar4 + lVar6 + 8, lVar9 != 0)) {
LAB_1481b5eff:
        *(undefined2 *)(lVar9 + 0x18) = 1;
        lVar4 = (**(code **)(*param_1 + 0x188))(param_1);
        *(float *)(lVar9 + 0x1c) = (float)*(double *)(lVar4 + 0x740);
        func_0x000140cd7960(param_1 + 0x28,&uStackX_8,&uStackX_10,0);
        puVar7 = (ulonglong *)param_1[0x67];
        puVar1 = puVar7 + (int)param_1[0x68];
        puVar10 = &UNK_14bce4e94;
        for (; puVar7 != puVar1; puVar7 = puVar7 + 1) {
          if (*puVar7 == uStackX_10) {
            func_0x00014101d060(param_1 + 0x67,&uStackX_10);
            if (2 < DAT_14eab53c8) {
              puVar5 = (undefined8 *)func_0x0001411de0e0(&uStackX_10,alStack_18);
              if (*(int *)(puVar5 + 1) == 0) {
                puVar11 = &UNK_14bce4e94;
              }
              else {
                puVar11 = (undefined *)*puVar5;
              }
              func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71a18,puVar11);
              if (alStack_18[0] != 0) {
                func_0x000140e282f0();
              }
            }
            break;
          }
        }
        lVar4 = func_0x0001481ba790(param_1,uStackX_10);
        if ((lVar4 != 0) && (func_0x000148155d70(param_1 + 0x6c,uStackX_10,0), 2 < DAT_14eab53c8)) {
          puVar5 = (undefined8 *)func_0x000140ef8a00(lVar4 + 0x10);
          if (*(int *)(puVar5 + 1) != 0) {
            puVar10 = (undefined *)*puVar5;
          }
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71aa8,puVar10);
        }
        func_0x0001481cad00(param_1);
        func_0x0001481b5300(param_1);
      }
    }
  }
  return;
}


/* Instruction evidence:
1481b5dc0 MOV qword ptr [RSP + 0x18],RBX
1481b5dc5 MOV qword ptr [RSP + 0x20],RSI
1481b5dca MOV qword ptr [RSP + 0x10],RDX
1481b5dcf PUSH RDI
1481b5dd0 SUB RSP,0x30
1481b5dd4 MOV RBX,RDX
1481b5dd7 MOV RDI,RCX
1481b5dda MOV qword ptr [RSP + 0x40],RDX
1481b5ddf MOV ECX,EDX
1481b5de1 CALL 0x1411c2eb0
1481b5de6 MOV R8D,dword ptr [RSP + 0x44]
1481b5deb ADD R8D,EAX
1481b5dee MOV EAX,dword ptr [RDI + 0xf8]
1481b5df4 CMP EAX,dword ptr [RDI + 0x124]
1481b5dfa JZ 0x1481b5e5e
1481b5dfc LEA RDX,[RDI + 0x128]
1481b5e03 MOV RAX,qword ptr [RDX + 0x8]
1481b5e07 TEST RAX,RAX
1481b5e0a CMOVNZ RDX,RAX
1481b5e0e MOV ECX,dword ptr [RDI + 0x138]
1481b5e14 DEC ECX
1481b5e16 MOV EAX,R8D
1481b5e19 AND RCX,RAX
1481b5e1c MOV EAX,dword ptr [RDX + RCX*0x4]
1481b5e1f CMP EAX,-0x1
1481b5e22 JZ 0x1481b5e5e
1481b5e24 MOV RDX,qword ptr [RDI + 0xf0]
1481b5e2b NOP dword ptr [RAX + RAX*0x1]
1481b5e30 MOVSXD RCX,EAX
1481b5e33 SHL RCX,0x6
1481b5e37 CMP qword ptr [RCX + RDX*0x1],RBX
1481b5e3b JZ 0x1481b5e48
1481b5e3d MOV EAX,dword ptr [RCX + RDX*0x1 + 0x38]
1481b5e41 CMP EAX,-0x1
1481b5e44 JNZ 0x1481b5e30
1481b5e46 JMP 0x1481b5e5e
1481b5e48 XOR EAX,EAX
1481b5e4a ADD RCX,RDX
1481b5e4d LEA RBX,[RCX + 0x8]
1481b5e51 CMOVZ RBX,RAX
1481b5e55 TEST RBX,RBX
1481b5e58 JNZ 0x1481b5eff
1481b5e5e MOV RBX,qword ptr [RSP + 0x48]
1481b5e63 MOV qword ptr [RSP + 0x40],RBX
1481b5e68 MOV ECX,EBX
1481b5e6a CALL 0x1411c2eb0
1481b5e6f MOV R8D,dword ptr [RSP + 0x44]
1481b5e74 ADD R8D,EAX
1481b5e77 MOV EAX,dword ptr [RDI + 0xa8]
1481b5e7d CMP EAX,dword ptr [RDI + 0xd4]
1481b5e83 JZ 0x1481b6036
1481b5e89 LEA RDX,[RDI + 0xd8]
1481b5e90 MOV RAX,qword ptr [RDX + 0x8]
1481b5e94 TEST RAX,RAX
1481b5e97 CMOVNZ RDX,RAX
1481b5e9b MOV ECX,dword ptr [RDI + 0xe8]
1481b5ea1 DEC ECX
1481b5ea3 MOV EAX,R8D
1481b5ea6 AND RCX,RAX
1481b5ea9 MOV EAX,dword ptr [RDX + RCX*0x4]
1481b5eac CMP EAX,-0x1
1481b5eaf JZ 0x1481b6036
1481b5eb5 MOV RDX,qword ptr [RDI + 0xa0]
1481b5ebc NOP dword ptr [RAX]
1481b5ec0 MOVSXD RCX,EAX
1481b5ec3 SHL RCX,0x6
1481b5ec7 CMP qword ptr [RDX + RCX*0x1],RBX
1481b5ecb JZ 0x1481b5ee6
1481b5ecd MOV EAX,dword ptr [RDX + RCX*0x1 + 0x38]
1481b5ed1 CMP EAX,-0x1
1481b5ed4 JNZ 0x1481b5ec0
1481b5ed6 MOV RBX,qword ptr [RSP + 0x50]
1481b5edb MOV RSI,qword ptr [RSP + 0x58]
1481b5ee0 ADD RSP,0x30
1481b5ee4 POP RDI
1481b5ee5 RET
1481b5ee6 MOV RBX,RDX
1481b5ee9 ADD RBX,RCX
1481b5eec JZ 0x1481b6036
1481b5ef2 ADD RBX,0x8
1481b5ef6 TEST RBX,RBX
1481b5ef9 JZ 0x1481b6036
1481b5eff MOV word ptr [RBX + 0x18],0x1
1481b5f05 MOV RAX,qword ptr [RDI]
1481b5f08 MOV RCX,RDI
1481b5f0b CALL qword ptr [RAX + 0x188]
1481b5f11 MOVSD XMM0,qword ptr [RAX + 0x740]
1481b5f19 CVTPD2PS XMM0,XMM0
1481b5f1d MOVSS dword ptr [RBX + 0x1c],XMM0
1481b5f22 LEA RCX,[RDI + 0x140]
1481b5f29 XOR R9D,R9D
1481b5f2c LEA R8,[RSP + 0x48]
1481b5f31 LEA RDX,[RSP + 0x40]
1481b5f36 CALL 0x140cd7960
1481b5f3b MOV RCX,qword ptr [RDI + 0x338]
1481b5f42 MOVSXD RAX,dword ptr [RDI + 0x340]
1481b5f49 LEA R8,[RCX + RAX*0x8]
1481b5f4d LEA RSI,[0x14bce4e94]
1481b5f54 CMP RCX,R8
1481b5f57 JZ 0x1481b5fcc
1481b5f59 MOV RDX,qword ptr [RSP + 0x48]
1481b5f5e NOP
1481b5f60 CMP qword ptr [RCX],RDX
1481b5f63 JZ 0x1481b5f70
1481b5f65 ADD RCX,0x8
1481b5f69 CMP RCX,R8
1481b5f6c JNZ 0x1481b5f60
1481b5f6e JMP 0x1481b5fd1
1481b5f70 LEA RDX,[RSP + 0x48]
1481b5f75 LEA RCX,[RDI + 0x338]
1481b5f7c CALL 0x14101d060
1481b5f81 CMP byte ptr [0x14eab53c8],0x3
1481b5f88 JC 0x1481b5fcc
1481b5f8a LEA RDX,[RSP + 0x20]
1481b5f8f LEA RCX,[RSP + 0x48]
1481b5f94 CALL 0x1411de0e0
1481b5f99 NOP
1481b5f9a CMP dword ptr [RAX + 0x8],0x0
1481b5f9e JZ 0x1481b5fa5
1481b5fa0 MOV R8,qword ptr [RAX]
1481b5fa3 JMP 0x1481b5fa8
1481b5fa5 MOV R8,RSI
1481b5fa8 LEA RDX,[0x14cf71a18]
1481b5faf LEA RCX,[0x14eab53c8]
1481b5fb6 CALL 0x140f24ba0
1481b5fbb NOP
1481b5fbc MOV RCX,qword ptr [RSP + 0x20]
1481b5fc1 TEST RCX,RCX
1481b5fc4 JZ 0x1481b5fcc
1481b5fc6 CALL 0x140e282f0
1481b5fcb NOP
1481b5fcc MOV RDX,qword ptr [RSP + 0x48]
1481b5fd1 MOV RCX,RDI
1481b5fd4 CALL 0x1481ba790
1481b5fd9 MOV RBX,RAX
1481b5fdc TEST RAX,RAX
1481b5fdf JZ 0x1481b6026
1481b5fe1 LEA RCX,[RDI + 0x360]
1481b5fe8 XOR R8D,R8D
1481b5feb MOV RDX,qword ptr [RSP + 0x48]
1481b5ff0 CALL 0x148155d70
1481b5ff5 CMP byte ptr [0x14eab53c8],0x3
1481b5ffc JC 0x1481b6026
1481b5ffe LEA RCX,[RBX + 0x10]
1481b6002 CALL 0x140ef8a00
1481b6007 CMP dword ptr [RAX + 0x8],0x0
1481b600b JZ 0x1481b6010
1481b600d MOV RSI,qword ptr [RAX]
1481b6010 MOV R8,RSI
1481b6013 LEA RDX,[0x14cf71aa8]
1481b601a LEA RCX,[0x14eab53c8]
1481b6021 CALL 0x140f24ba0
1481b6026 MOV RCX,RDI
1481b6029 CALL 0x1481cad00
1481b602e MOV RCX,RDI
1481b6031 CALL 0x1481b5300
1481b6036 MOV RBX,qword ptr [RSP + 0x50]
1481b603b MOV RSI,qword ptr [RSP + 0x58]
1481b6040 ADD RSP,0x30
1481b6044 POP RDI
1481b6045 RET
*/

/* 1481b5720 ClaimChallengeRewards */

ulonglong * ClaimChallengeRewards(longlong param_1,ulonglong *param_2,ulonglong param_3)

{
  uint uVar1;
  ulonglong uVar2;
  code *pcVar3;
  ulonglong uVar4;
  char cVar5;
  int iVar6;
  undefined8 *puVar7;
  longlong lVar8;
  ulonglong *puVar9;
  uint *puVar10;
  undefined4 *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  longlong lVar14;
  longlong lVar15;
  longlong lVar16;
  undefined8 unaff_retaddr;
  ulonglong uStackX_18;
  undefined8 uStackX_20;
  uint uStack_c8;
  uint uStack_c4;
  undefined8 uStack_c0;
  undefined4 uStack_b8;
  int iStack_b4;
  undefined8 uStack_b0;
  longlong alStack_a8 [2];
  longlong alStack_98 [2];
  longlong alStack_88 [2];
  longlong alStack_78 [2];
  longlong alStack_68 [2];
  longlong alStack_58 [3];
  
  lVar15 = 0;
  *param_2 = 0;
  param_2[1] = 0;
  uStackX_18 = param_3;
  uStackX_20 = param_3;
  iVar6 = func_0x0001411c2eb0(param_3 & 0xffffffff);
  if (*(int *)(param_1 + 0x148) != *(int *)(param_1 + 0x174)) {
    lVar8 = param_1 + 0x178;
    if (*(longlong *)(param_1 + 0x180) != 0) {
      lVar8 = *(longlong *)(param_1 + 0x180);
    }
    iVar6 = *(int *)(lVar8 + (ulonglong)(*(int *)(param_1 + 0x188) - 1U & uStackX_20._4_4_ + iVar6)
                             * 4);
    if (iVar6 != -1) {
      do {
        if (*(ulonglong *)(*(longlong *)(param_1 + 0x140) + (longlong)iVar6 * 0x10) == param_3) {
          lVar8 = func_0x0001481ba790(param_1,uStackX_18);
          uVar2 = uStackX_18;
          if (lVar8 == 0) {
            if (DAT_14eab53c8 < 2) {
              return param_2;
            }
            puVar7 = (undefined8 *)func_0x0001411de0e0(&uStackX_18,alStack_a8);
            if (*(int *)(puVar7 + 1) == 0) {
              puVar12 = &UNK_14bce4e94;
            }
            else {
              puVar12 = (undefined *)*puVar7;
            }
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf74478,puVar12);
            if (alStack_a8[0] == 0) {
              return param_2;
            }
            func_0x000140e282f0();
            return param_2;
          }
          uStackX_20 = uStackX_18;
          iVar6 = func_0x0001411c2eb0(uStackX_18 & 0xffffffff);
          uVar4 = uStackX_18;
          if (*(int *)(param_1 + 0xa8) == *(int *)(param_1 + 0xd4)) goto LAB_1481b5901;
          lVar16 = param_1 + 0xd8;
          if (*(longlong *)(param_1 + 0xe0) != 0) {
            lVar16 = *(longlong *)(param_1 + 0xe0);
          }
          iVar6 = *(int *)(lVar16 + (ulonglong)
                                    (*(int *)(param_1 + 0xe8) - 1U & uStackX_20._4_4_ + iVar6) * 4);
          if (iVar6 == -1) goto LAB_1481b5901;
          goto LAB_1481b58d0;
        }
        iVar6 = *(int *)(*(longlong *)(param_1 + 0x140) + 8 + (longlong)iVar6 * 0x10);
      } while (iVar6 != -1);
    }
  }
  if (DAT_14eab53c8 < 3) {
    return param_2;
  }
  puVar7 = (undefined8 *)func_0x0001411de0e0(&uStackX_18,alStack_58);
  if (*(int *)(puVar7 + 1) == 0) {
    puVar12 = &UNK_14bce4e94;
  }
  else {
    puVar12 = (undefined *)*puVar7;
  }
  func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf743e0,puVar12);
  if (alStack_58[0] == 0) {
    return param_2;
  }
  func_0x000140e282f0();
  return param_2;
  while (iVar6 = (int)puVar9[7], iVar6 != -1) {
LAB_1481b58d0:
    puVar9 = (ulonglong *)(*(longlong *)(param_1 + 0xa0) + (longlong)iVar6 * 0x40);
    if (*puVar9 == uVar2) {
      lVar14 = *(longlong *)(param_1 + 0xa0) + (longlong)iVar6 * 0x40;
      lVar16 = lVar14 + 8;
      if (lVar14 == 0) {
        lVar16 = lVar15;
      }
      if (lVar16 != 0) goto LAB_1481b59d3;
      break;
    }
  }
LAB_1481b5901:
  uStackX_20 = uStackX_18;
  iVar6 = func_0x0001411c2eb0(uStackX_18 & 0xffffffff);
  if (*(int *)(param_1 + 0xf8) != *(int *)(param_1 + 0x124)) {
    lVar16 = param_1 + 0x128;
    if (*(longlong *)(param_1 + 0x130) != 0) {
      lVar16 = *(longlong *)(param_1 + 0x130);
    }
    iVar6 = *(int *)(lVar16 + (ulonglong)(*(int *)(param_1 + 0x138) - 1U & uStackX_20._4_4_ + iVar6)
                              * 4);
    if (iVar6 != -1) {
      do {
        puVar9 = (ulonglong *)(*(longlong *)(param_1 + 0xf0) + (longlong)iVar6 * 0x40);
        if (*puVar9 == uVar4) {
          lVar16 = *(longlong *)(param_1 + 0xf0) + (longlong)iVar6 * 0x40;
          if ((lVar16 != 0) && (lVar16 = lVar16 + 8, lVar15 = lVar16, lVar16 != 0)) {
LAB_1481b59d3:
            lVar15 = lVar16;
            if (*(char *)(lVar16 + 0x19) != '\0') {
              if (DAT_14eab53c8 < 3) {
                return param_2;
              }
              puVar7 = (undefined8 *)func_0x0001411de0e0(&uStackX_18,alStack_98);
              if (*(int *)(puVar7 + 1) == 0) {
                puVar12 = &UNK_14bce4e94;
              }
              else {
                puVar12 = (undefined *)*puVar7;
              }
              func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf74500,puVar12);
              if (alStack_98[0] == 0) {
                return param_2;
              }
              func_0x000140e282f0();
              return param_2;
            }
          }
          break;
        }
        iVar6 = (int)puVar9[7];
      } while (iVar6 != -1);
    }
  }
  puVar12 = &UNK_14bce4e94;
  if (*(int *)(lVar8 + 0x88) < 1) {
    uVar1 = *(uint *)(lVar8 + 0x90);
    if (0 < (int)uVar1) {
      uStack_c0 = 0;
      uStack_c8 = uStack_c8 & 0xffffff00;
      puVar10 = (uint *)*param_2;
      uStack_c4 = uVar1;
      if (((puVar10 <= &uStack_c8) &&
          (&uStack_c8 < puVar10 + (longlong)*(int *)((longlong)param_2 + 0xc) * 4)) &&
         (cVar5 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                      &UNK_14bce6d80,&uStack_c8,puVar10,
                                      (longlong)*(int *)((longlong)param_2 + 0xc),
                                      (longlong)(int)param_2[1],0x10), cVar5 != '\0')) {
        pcVar3 = (code *)swi(3);
        puVar9 = (ulonglong *)(*pcVar3)();
        return puVar9;
      }
      iVar6 = (int)param_2[1];
      *(uint *)(param_2 + 1) = iVar6 + 1U;
      if (*(uint *)((longlong)param_2 + 0xc) < iVar6 + 1U) {
        func_0x0001481ca690(param_2,iVar6);
      }
      puVar10 = (uint *)((longlong)iVar6 * 0x10 + *param_2);
      *puVar10 = uStack_c8;
      puVar10[1] = uStack_c4;
      puVar10[2] = (uint)uStack_c0;
      puVar10[3] = uStack_c0._4_4_;
    }
    iVar6 = *(int *)(lVar8 + 0x94);
    if (0 < iVar6) {
      uStack_b0 = 0;
      uStack_b8 = CONCAT31(uStack_b8._1_3_,1);
      puVar11 = (undefined4 *)*param_2;
      iStack_b4 = iVar6;
      if (((puVar11 <= &uStack_b8) &&
          (&uStack_b8 < puVar11 + (longlong)*(int *)((longlong)param_2 + 0xc) * 4)) &&
         (cVar5 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                      &UNK_14bce6d80,&uStack_b8,puVar11,
                                      (longlong)*(int *)((longlong)param_2 + 0xc),
                                      (longlong)(int)param_2[1],0x10), cVar5 != '\0')) {
        pcVar3 = (code *)swi(3);
        puVar9 = (ulonglong *)(*pcVar3)();
        return puVar9;
      }
      iVar6 = (int)param_2[1];
      *(uint *)(param_2 + 1) = iVar6 + 1U;
      if (*(uint *)((longlong)param_2 + 0xc) < iVar6 + 1U) {
        func_0x0001481ca690(param_2,iVar6);
      }
      puVar11 = (undefined4 *)((longlong)iVar6 * 0x10 + *param_2);
      *puVar11 = uStack_b8;
      puVar11[1] = iStack_b4;
      puVar11[2] = (undefined4)uStack_b0;
      puVar11[3] = uStack_b0._4_4_;
    }
    if (2 < DAT_14eab53c8) {
      puVar7 = (undefined8 *)func_0x0001411de0e0(&uStackX_18,alStack_78);
      if (*(int *)(puVar7 + 1) == 0) {
        puVar13 = &UNK_14bce4e94;
      }
      else {
        puVar13 = (undefined *)*puVar7;
      }
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf74610,puVar13);
      if (alStack_78[0] != 0) {
        func_0x000140e282f0();
      }
    }
  }
  else {
    if (param_2 != (ulonglong *)(lVar8 + 0x80)) {
      iVar6 = *(int *)(lVar8 + 0x88);
      uVar2 = *(ulonglong *)(lVar8 + 0x80);
      *(int *)(param_2 + 1) = iVar6;
      if ((iVar6 == 0) && (*(int *)((longlong)param_2 + 0xc) == 0)) {
        *(undefined4 *)((longlong)param_2 + 0xc) = 0;
      }
      else {
        func_0x000148157da0(param_2,iVar6);
        if (iVar6 != 0) {
          func_0x00014b89502e(*param_2,uVar2,(longlong)iVar6 << 4);
        }
      }
    }
    if (2 < DAT_14eab53c8) {
      puVar7 = (undefined8 *)func_0x0001411de0e0(&uStackX_18,alStack_88);
      if (*(int *)(puVar7 + 1) == 0) {
        puVar13 = &UNK_14bce4e94;
      }
      else {
        puVar13 = (undefined *)*puVar7;
      }
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf74588,(int)param_2[1],puVar13);
      if (alStack_88[0] != 0) {
        func_0x000140e282f0();
      }
    }
  }
  GrantRewards(param_1,param_2);
  if (lVar15 != 0) {
    *(undefined1 *)(lVar15 + 0x19) = 1;
    func_0x0001481cad00(param_1);
  }
  if (2 < DAT_14eab53c8) {
    puVar7 = (undefined8 *)func_0x0001411de0e0(&uStackX_18,alStack_68);
    if (*(int *)(puVar7 + 1) != 0) {
      puVar12 = (undefined *)*puVar7;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf74698,puVar12);
    if (alStack_68[0] != 0) {
      func_0x000140e282f0();
    }
  }
  return param_2;
}


/* Instruction evidence:
1481b5720 MOV qword ptr [RSP + 0x18],R8
1481b5725 MOV qword ptr [RSP + 0x10],RDX
1481b572a PUSH RBP
1481b572b PUSH RBX
1481b572c PUSH RSI
1481b572d PUSH RDI
1481b572e PUSH R12
1481b5730 PUSH R13
1481b5732 PUSH R14
1481b5734 PUSH R15
1481b5736 LEA RBP,[RSP + -0x1f]
1481b573b SUB RSP,0xd8
1481b5742 MOV RBX,R8
1481b5745 MOV RDI,RDX
1481b5748 MOV RSI,RCX
1481b574b MOV dword ptr [RBP + 0x67],0x1
1481b5752 XOR R15D,R15D
1481b5755 MOV qword ptr [RDX],R15
1481b5758 MOV qword ptr [RDX + 0x8],R15
1481b575c MOV dword ptr [RBP + 0x67],0x1
1481b5763 MOV qword ptr [RBP + 0x7f],RBX
1481b5767 MOV ECX,R8D
1481b576a CALL 0x1411c2eb0
1481b576f MOV R8D,dword ptr [RBP + 0x83]
1481b5776 ADD R8D,EAX
1481b5779 MOV EAX,dword ptr [RSI + 0x148]
1481b577f CMP EAX,dword ptr [RSI + 0x174]
1481b5785 JZ 0x1481b57d4
1481b5787 LEA RDX,[RSI + 0x178]
1481b578e MOV RAX,qword ptr [RDX + 0x8]
1481b5792 TEST RAX,RAX
1481b5795 CMOVNZ RDX,RAX
1481b5799 MOV ECX,dword ptr [RSI + 0x188]
1481b579f DEC ECX
1481b57a1 MOV EAX,R8D
1481b57a4 AND RCX,RAX
1481b57a7 MOV EAX,dword ptr [RDX + RCX*0x4]
1481b57aa CMP EAX,-0x1
1481b57ad JZ 0x1481b57d4
1481b57af MOV RCX,qword ptr [RSI + 0x140]
1481b57b6 NOP dword ptr [RAX + RAX*0x1]
1481b57c0 CDQE
1481b57c2 ADD RAX,RAX
1481b57c5 CMP qword ptr [RCX + RAX*0x8],RBX
1481b57c9 JZ 0x1481b5801
1481b57cb MOV EAX,dword ptr [RCX + RAX*0x8 + 0x8]
1481b57cf CMP EAX,-0x1
1481b57d2 JNZ 0x1481b57c0
1481b57d4 CMP byte ptr [0x14eab53c8],0x3
1481b57db JC 0x1481b5cfa
1481b57e1 LEA RDX,[RBP + 0x7]
1481b57e5 LEA RCX,[RBP + 0x77]
1481b57e9 CALL 0x1411de0e0
1481b57ee NOP
1481b57ef CMP dword ptr [RAX + 0x8],0x0
1481b57f3 JZ 0x1481b5ccd
1481b57f9 MOV RBX,qword ptr [RAX]
1481b57fc JMP 0x1481b5cd4
1481b5801 MOV RDX,qword ptr [RBP + 0x77]
1481b5805 MOV RCX,RSI
1481b5808 CALL 0x1481ba790
1481b580d MOV R13,RAX
1481b5810 TEST RAX,RAX
1481b5813 JNZ 0x1481b586d
1481b5815 CMP byte ptr [0x14eab53c8],0x2
1481b581c JC 0x1481b5cfa
1481b5822 LEA RDX,[RBP + -0x49]
1481b5826 LEA RCX,[RBP + 0x77]
1481b582a CALL 0x1411de0e0
1481b582f NOP
1481b5830 CMP dword ptr [RAX + 0x8],R13D
1481b5834 JZ 0x1481b583b
1481b5836 MOV RBX,qword ptr [RAX]
1481b5839 JMP 0x1481b5842
1481b583b LEA RBX,[0x14bce4e94]
1481b5842 MOV R8,RBX
1481b5845 LEA RDX,[0x14cf74478]
1481b584c LEA RCX,[0x14eab53c8]
1481b5853 CALL 0x140f24ba0
1481b5858 NOP
1481b5859 MOV RCX,qword ptr [RBP + -0x49]
1481b585d TEST RCX,RCX
1481b5860 JZ 0x1481b5868
1481b5862 CALL 0x140e282f0
1481b5867 NOP
1481b5868 JMP 0x1481b5cfa
1481b586d MOV RBX,qword ptr [RBP + 0x77]
1481b5871 MOV qword ptr [RBP + 0x7f],RBX
1481b5875 MOV ECX,EBX
1481b5877 CALL 0x1411c2eb0
1481b587c MOV R8D,dword ptr [RBP + 0x83]
1481b5883 ADD R8D,EAX
1481b5886 MOV EAX,dword ptr [RSI + 0xa8]
1481b588c CMP EAX,dword ptr [RSI + 0xd4]
1481b5892 JZ 0x1481b5901
1481b5894 LEA RDX,[RSI + 0xd8]
1481b589b MOV RAX,qword ptr [RDX + 0x8]
1481b589f TEST RAX,RAX
1481b58a2 CMOVNZ RDX,RAX
1481b58a6 MOV ECX,dword ptr [RSI + 0xe8]
1481b58ac DEC ECX
1481b58ae MOV EAX,R8D
1481b58b1 AND RCX,RAX
1481b58b4 MOV EAX,dword ptr [RDX + RCX*0x4]
1481b58b7 CMP EAX,-0x1
1481b58ba JZ 0x1481b5901
1481b58bc MOV RDX,qword ptr [RSI + 0xa0]
1481b58c3 NOP dword ptr [RAX]
1481b58c7 NOP word ptr [RAX + RAX*0x1]
1481b58d0 MOVSXD RCX,EAX
1481b58d3 SHL RCX,0x6
1481b58d7 LEA RAX,[RDX + RCX*0x1]
1481b58db CMP qword ptr [RAX],RBX
1481b58de JZ 0x1481b58ea
1481b58e0 MOV EAX,dword ptr [RAX + 0x38]
1481b58e3 CMP EAX,-0x1
1481b58e6 JNZ 0x1481b58d0
1481b58e8 JMP 0x1481b5901
1481b58ea MOV R14,RDX
1481b58ed ADD R14,RCX
1481b58f0 LEA R14,[R14 + 0x8]
1481b58f4 CMOVZ R14,R15
1481b58f8 TEST R14,R14
1481b58fb JNZ 0x1481b59d3
1481b5901 MOV RBX,qword ptr [RBP + 0x77]
1481b5905 MOV qword ptr [RBP + 0x7f],RBX
1481b5909 MOV ECX,EBX
1481b590b CALL 0x1411c2eb0
1481b5910 MOV R8D,dword ptr [RBP + 0x83]
1481b5917 ADD R8D,EAX
1481b591a MOV EAX,dword ptr [RSI + 0xf8]
1481b5920 CMP EAX,dword ptr [RSI + 0x124]
1481b5926 JZ 0x1481b5978
1481b5928 LEA RDX,[RSI + 0x128]
1481b592f MOV RAX,qword ptr [RDX + 0x8]
1481b5933 TEST RAX,RAX
1481b5936 CMOVNZ RDX,RAX
1481b593a MOV ECX,dword ptr [RSI + 0x138]
1481b5940 DEC ECX
1481b5942 MOV EAX,R8D
1481b5945 AND RCX,RAX
1481b5948 MOV EAX,dword ptr [RDX + RCX*0x4]
1481b594b CMP EAX,-0x1
1481b594e JZ 0x1481b5978
1481b5950 MOV RDX,qword ptr [RSI + 0xf0]
1481b5957 NOP word ptr [RAX + RAX*0x1]
1481b5960 MOVSXD RCX,EAX
1481b5963 SHL RCX,0x6
1481b5967 LEA RAX,[RDX + RCX*0x1]
1481b596b CMP qword ptr [RAX],RBX
1481b596e JZ 0x1481b59c2
1481b5970 MOV EAX,dword ptr [RAX + 0x38]
1481b5973 CMP EAX,-0x1
1481b5976 JNZ 0x1481b5960
1481b5978 MOV R14,R15
1481b597b LEA RBX,[0x14bce4e94]
1481b5982 CMP dword ptr [R13 + 0x88],0x0
1481b598a JLE 0x1481b5aa9
1481b5990 LEA RAX,[R13 + 0x80]
1481b5997 CMP RDI,RAX
1481b599a JZ 0x1481b5a54
1481b59a0 MOV R8D,dword ptr [RDI + 0xc]
1481b59a4 MOVSXD R15,dword ptr [RAX + 0x8]
1481b59a8 MOV R12,qword ptr [RAX]
1481b59ab MOV dword ptr [RDI + 0x8],R15D
1481b59af TEST R15D,R15D
1481b59b2 JNZ 0x1481b5a32
1481b59b4 TEST R8D,R8D
1481b59b7 JNZ 0x1481b5a32
1481b59b9 MOV dword ptr [RDI + 0xc],R15D
1481b59bd JMP 0x1481b5a54
1481b59c2 MOV R14,RDX
1481b59c5 ADD R14,RCX
1481b59c8 JZ 0x1481b5978
1481b59ca ADD R14,0x8
1481b59ce TEST R14,R14
1481b59d1 JZ 0x1481b597b
1481b59d3 CMP byte ptr [R14 + 0x19],0x0
1481b59d8 JZ 0x1481b597b
1481b59da CMP byte ptr [0x14eab53c8],0x3
1481b59e1 JC 0x1481b5cfa
1481b59e7 LEA RDX,[RBP + -0x39]
1481b59eb LEA RCX,[RBP + 0x77]
1481b59ef CALL 0x1411de0e0
1481b59f4 NOP
1481b59f5 CMP dword ptr [RAX + 0x8],0x0
1481b59f9 JZ 0x1481b5a00
1481b59fb MOV RBX,qword ptr [RAX]
1481b59fe JMP 0x1481b5a07
1481b5a00 LEA RBX,[0x14bce4e94]
1481b5a07 MOV R8,RBX
1481b5a0a LEA RDX,[0x14cf74500]
1481b5a11 LEA RCX,[0x14eab53c8]
1481b5a18 CALL 0x140f24ba0
1481b5a1d NOP
1481b5a1e MOV RCX,qword ptr [RBP + -0x39]
1481b5a22 TEST RCX,RCX
1481b5a25 JZ 0x1481b5a2d
1481b5a27 CALL 0x140e282f0
1481b5a2c NOP
1481b5a2d JMP 0x1481b5cfa
1481b5a32 MOV EDX,R15D
1481b5a35 MOV RCX,RDI
1481b5a38 CALL 0x148157da0
1481b5a3d TEST R15D,R15D
1481b5a40 JZ 0x1481b5a54
1481b5a42 MOV R8,R15
1481b5a45 SHL R8,0x4
1481b5a49 MOV RDX,R12
1481b5a4c MOV RCX,qword ptr [RDI]
1481b5a4f CALL 0x14b89502e
1481b5a54 CMP byte ptr [0x14eab53c8],0x3
1481b5a5b JC 0x1481b5c68
1481b5a61 LEA RDX,[RBP + -0x29]
1481b5a65 LEA RCX,[RBP + 0x77]
1481b5a69 CALL 0x1411de0e0
1481b5a6e NOP
1481b5a6f CMP dword ptr [RAX + 0x8],0x0
1481b5a73 JZ 0x1481b5a7a
1481b5a75 MOV R9,qword ptr [RAX]
1481b5a78 JMP 0x1481b5a7d
1481b5a7a MOV R9,RBX
1481b5a7d MOV R8D,dword ptr [RDI + 0x8]
1481b5a81 LEA RDX,[0x14cf74588]
1481b5a88 LEA RCX,[0x14eab53c8]
1481b5a8f CALL 0x140f24ba0
1481b5a94 NOP
1481b5a95 MOV RCX,qword ptr [RBP + -0x29]
1481b5a99 TEST RCX,RCX
1481b5a9c JZ 0x1481b5aa4
1481b5a9e CALL 0x140e282f0
1481b5aa3 NOP
1481b5aa4 JMP 0x1481b5c68
1481b5aa9 MOV EAX,dword ptr [R13 + 0x90]
1481b5ab0 LEA R12,[0x14bce6d80]
1481b5ab7 TEST EAX,EAX
1481b5ab9 JLE 0x1481b5b66
1481b5abf MOV qword ptr [RBP + -0x61],R15
1481b5ac3 MOV byte ptr [RBP + -0x69],0x0
1481b5ac7 MOV dword ptr [RBP + -0x65],EAX
1481b5aca MOV RCX,qword ptr [RDI]
1481b5acd LEA RAX,[RBP + -0x69]
1481b5ad1 CMP RAX,RCX
1481b5ad4 JC 0x1481b5b3a
1481b5ad6 MOVSXD RDX,dword ptr [RDI + 0xc]
1481b5ada MOV RAX,RDX
1481b5add SHL RAX,0x4
1481b5ae1 ADD RAX,RCX
1481b5ae4 LEA R8,[RBP + -0x69]
1481b5ae8 CMP R8,RAX
1481b5aeb JNC 0x1481b5b3a
1481b5aed MOVSXD RAX,dword ptr [RDI + 0x8]
1481b5af1 MOV R9,qword ptr [RBP + 0x5f]
1481b5af5 MOV qword ptr [RSP + 0x48],0x10
1481b5afe MOV qword ptr [RSP + 0x40],RAX
1481b5b03 MOV qword ptr [RSP + 0x38],RDX
1481b5b08 MOV qword ptr [RSP + 0x30],RCX
1481b5b0d LEA RAX,[RBP + -0x69]
1481b5b11 MOV qword ptr [RSP + 0x28],RAX
1481b5b16 MOV qword ptr [RSP + 0x20],R12
1481b5b1b MOV R8D,0x63e
1481b5b21 LEA RDX,[0x14cf27ac0]
1481b5b28 LEA RCX,[0x14bce6eb8]
1481b5b2f CALL 0x140f8dfd0
1481b5b34 TEST AL,AL
1481b5b36 JZ 0x1481b5b3a
1481b5b38 NOP
1481b5b39 INT3
1481b5b3a MOVSXD R15,dword ptr [RDI + 0x8]
1481b5b3e LEA EAX,[R15 + 0x1]
1481b5b42 MOV dword ptr [RDI + 0x8],EAX
1481b5b45 CMP EAX,dword ptr [RDI + 0xc]
1481b5b48 JBE 0x1481b5b55
1481b5b4a MOV EDX,R15D
1481b5b4d MOV RCX,RDI
1481b5b50 CALL 0x1481ca690
1481b5b55 MOV RAX,R15
1481b5b58 SHL RAX,0x4
1481b5b5c ADD RAX,qword ptr [RDI]
1481b5b5f MOVUPS XMM0,xmmword ptr [RBP + -0x69]
1481b5b63 MOVUPS xmmword ptr [RAX],XMM0
1481b5b66 MOV EAX,dword ptr [R13 + 0x94]
1481b5b6d TEST EAX,EAX
1481b5b6f JLE 0x1481b5c20
1481b5b75 MOV qword ptr [RBP + -0x51],0x0
1481b5b7d MOV byte ptr [RBP + -0x59],0x1
1481b5b81 MOV dword ptr [RBP + -0x55],EAX
1481b5b84 MOV R10,qword ptr [RDI]
1481b5b87 LEA RAX,[RBP + -0x59]
1481b5b8b CMP RAX,R10
1481b5b8e JC 0x1481b5bf4
1481b5b90 MOVSXD R11,dword ptr [RDI + 0xc]
1481b5b94 MOV RAX,R11
1481b5b97 SHL RAX,0x4
1481b5b9b ADD RAX,R10
1481b5b9e LEA RCX,[RBP + -0x59]
1481b5ba2 CMP RCX,RAX
1481b5ba5 JNC 0x1481b5bf4
1481b5ba7 MOVSXD RAX,dword ptr [RDI + 0x8]
1481b5bab MOV R9,qword ptr [RBP + 0x5f]
1481b5baf MOV qword ptr [RSP + 0x48],0x10
1481b5bb8 MOV qword ptr [RSP + 0x40],RAX
1481b5bbd MOV qword ptr [RSP + 0x38],R11
1481b5bc2 MOV qword ptr [RSP + 0x30],R10
1481b5bc7 LEA RAX,[RBP + -0x59]
1481b5bcb MOV qword ptr [RSP + 0x28],RAX
1481b5bd0 MOV qword ptr [RSP + 0x20],R12
1481b5bd5 MOV R8D,0x63e
1481b5bdb LEA RDX,[0x14cf27ac0]
1481b5be2 LEA RCX,[0x14bce6eb8]
1481b5be9 CALL 0x140f8dfd0
1481b5bee TEST AL,AL
1481b5bf0 JZ 0x1481b5bf4
1481b5bf2 NOP
1481b5bf3 INT3
1481b5bf4 MOVSXD R15,dword ptr [RDI + 0x8]
1481b5bf8 LEA EAX,[R15 + 0x1]
1481b5bfc MOV dword ptr [RDI + 0x8],EAX
1481b5bff CMP EAX,dword ptr [RDI + 0xc]
1481b5c02 JBE 0x1481b5c0f
1481b5c04 MOV EDX,R15D
1481b5c07 MOV RCX,RDI
1481b5c0a CALL 0x1481ca690
1481b5c0f MOV RAX,R15
1481b5c12 SHL RAX,0x4
1481b5c16 ADD RAX,qword ptr [RDI]
1481b5c19 MOVUPS XMM0,xmmword ptr [RBP + -0x59]
1481b5c1d MOVUPS xmmword ptr [RAX],XMM0
1481b5c20 CMP byte ptr [0x14eab53c8],0x3
1481b5c27 JC 0x1481b5c68
1481b5c29 LEA RDX,[RBP + -0x19]
1481b5c2d LEA RCX,[RBP + 0x77]
1481b5c31 CALL 0x1411de0e0
1481b5c36 NOP
1481b5c37 CMP dword ptr [RAX + 0x8],0x0
1481b5c3b JZ 0x1481b5c42
1481b5c3d MOV R8,qword ptr [RAX]
1481b5c40 JMP 0x1481b5c45
1481b5c42 MOV R8,RBX
1481b5c45 LEA RDX,[0x14cf74610]
1481b5c4c LEA RCX,[0x14eab53c8]
1481b5c53 CALL 0x140f24ba0
1481b5c58 NOP
1481b5c59 MOV RCX,qword ptr [RBP + -0x19]
1481b5c5d TEST RCX,RCX
1481b5c60 JZ 0x1481b5c68
1481b5c62 CALL 0x140e282f0
1481b5c67 NOP
1481b5c68 MOV RDX,RDI
1481b5c6b MOV RCX,RSI
1481b5c6e CALL 0x1481c3870
1481b5c73 TEST R14,R14
1481b5c76 JZ 0x1481b5c85
1481b5c78 MOV byte ptr [R14 + 0x19],0x1
1481b5c7d MOV RCX,RSI
1481b5c80 CALL 0x1481cad00
1481b5c85 CMP byte ptr [0x14eab53c8],0x3
1481b5c8c JC 0x1481b5cfa
1481b5c8e LEA RDX,[RBP + -0x9]
1481b5c92 LEA RCX,[RBP + 0x77]
1481b5c96 CALL 0x1411de0e0
1481b5c9b NOP
1481b5c9c CMP dword ptr [RAX + 0x8],0x0
1481b5ca0 JZ 0x1481b5ca5
1481b5ca2 MOV RBX,qword ptr [RAX]
1481b5ca5 MOV R8,RBX
1481b5ca8 LEA RDX,[0x14cf74698]
1481b5caf LEA RCX,[0x14eab53c8]
1481b5cb6 CALL 0x140f24ba0
1481b5cbb NOP
1481b5cbc MOV RCX,qword ptr [RBP + -0x9]
1481b5cc0 TEST RCX,RCX
1481b5cc3 JZ 0x1481b5ccb
1481b5cc5 CALL 0x140e282f0
1481b5cca NOP
1481b5ccb JMP 0x1481b5cfa
1481b5ccd LEA RBX,[0x14bce4e94]
1481b5cd4 MOV R8,RBX
1481b5cd7 LEA RDX,[0x14cf743e0]
1481b5cde LEA RCX,[0x14eab53c8]
1481b5ce5 CALL 0x140f24ba0
1481b5cea NOP
1481b5ceb MOV RCX,qword ptr [RBP + 0x7]
1481b5cef TEST RCX,RCX
1481b5cf2 JZ 0x1481b5cfa
1481b5cf4 CALL 0x140e282f0
1481b5cf9 NOP
1481b5cfa MOV RAX,RDI
1481b5cfd ADD RSP,0xd8
1481b5d04 POP R15
1481b5d06 POP R14
1481b5d08 POP R13
1481b5d0a POP R12
1481b5d0c POP RDI
1481b5d0d POP RSI
1481b5d0e POP RBX
1481b5d0f POP RBP
1481b5d10 RET
*/

/* 1481c3870 GrantRewards */

void GrantRewards(longlong param_1,undefined8 *param_2)

{
  int iVar1;
  code *pcVar2;
  longlong lVar3;
  char cVar4;
  ulonglong uVar5;
  undefined *puVar6;
  char *pcVar7;
  longlong lVar8;
  longlong *plVar9;
  char *pcVar10;
  longlong *plStackX_18;
  uint uStackX_20;
  longlong lStack_c0;
  int iStack_b8;
  undefined4 uStack_b4;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  longlong lStack_90;
  int iStack_88;
  longlong alStack_80 [2];
  longlong alStack_70 [2];
  longlong alStack_60 [2];
  longlong alStack_50 [3];
  
  pcVar10 = (char *)*param_2;
  uStackX_20 = *(uint *)(param_2 + 1);
  uVar5 = (ulonglong)(int)uStackX_20;
  pcVar7 = pcVar10 + uVar5 * 0x10;
  plVar9 = (longlong *)(pcVar10 + 8);
LAB_1481c38b6:
  if (*(int *)(param_2 + 1) != (int)uVar5) {
    plStackX_18 = (longlong *)((ulonglong)plStackX_18 & 0xffffffffffffff00);
    cVar4 = func_0x00014bc1cf90(&plStackX_18);
    if (cVar4 != '\0') {
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
  }
  if (pcVar10 == pcVar7) {
    return;
  }
  cVar4 = *pcVar10;
  if (cVar4 == '\0') {
    iVar1 = *(int *)((longlong)plVar9 + -4);
    if (0 < iVar1) {
      func_0x000140cf7750(&lStack_90,&UNK_14cad0ba0);
      lVar3 = lStack_90;
      *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + iVar1;
      *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) + iVar1;
      plStackX_18 = &lStack_c0;
      lStack_c0 = 0;
      lVar8 = (longlong)iStack_88;
      iStack_b8 = iStack_88;
      if (iStack_88 == 0) {
        uStack_b4 = 0;
      }
      else {
        func_0x000140ca39a0(&lStack_c0,iStack_88,0);
        func_0x00014b89502e(lStack_c0,lVar3,lVar8 * 2);
      }
      plStackX_18 = &lStack_c0;
      func_0x000148155e80(param_1 + 0x378,iVar1,&lStack_c0);
      if (lStack_c0 != 0) {
        func_0x000140e282f0();
      }
      func_0x0001481b4f10(param_1);
      uStack_a0 = 0;
      uStack_98 = 0;
      func_0x0001481ce250(param_1,0xf,iVar1,&uStack_a0);
      if (lStack_90 != 0) {
        func_0x000140e282f0();
      }
      if (2 < DAT_14eab53c8) {
        puVar6 = &UNK_14cf74738;
        goto LAB_1481c3c83;
      }
    }
  }
  else {
    if (cVar4 == '\x01') {
      iVar1 = *(int *)((longlong)plVar9 + -4);
      if (0 < iVar1) {
        *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + iVar1;
        if (*(longlong *)(param_1 + 0x70) == 0) {
          if (2 < DAT_14eab53c8) {
            puVar6 = &UNK_14cf747f8;
            goto LAB_1481c3c83;
          }
        }
        else {
          func_0x0001481d3580(*(longlong *)(param_1 + 0x70),iVar1);
          if (2 < DAT_14eab53c8) {
            puVar6 = &UNK_14cf74788;
LAB_1481c3c83:
            func_0x000140f24ba0(&DAT_14eab53c8,puVar6);
          }
        }
      }
      goto LAB_1481c3c96;
    }
    if (cVar4 == '\x02') {
      func_0x0001481c3cd0(param_1,plVar9);
      pcVar10 = pcVar10 + 0x10;
      plVar9 = plVar9 + 2;
      uVar5 = (ulonglong)uStackX_20;
      goto LAB_1481c38b6;
    }
    if (cVar4 == '\x03') {
      uStack_a8 = 0;
      if (*plVar9 == 0) {
        if (1 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf74ae8);
          pcVar10 = pcVar10 + 0x10;
          plVar9 = plVar9 + 2;
          uVar5 = (ulonglong)uStackX_20;
          goto LAB_1481c38b6;
        }
      }
      else {
        cVar4 = func_0x0001481cd680(param_1,*plVar9);
        if (cVar4 == '\0') {
          if (2 < DAT_14eab53c8) {
            func_0x0001411de0e0(plVar9,alStack_50);
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf74bd8);
            if (alStack_50[0] != 0) {
              func_0x000140e282f0();
            }
            pcVar10 = pcVar10 + 0x10;
            plVar9 = plVar9 + 2;
            uVar5 = (ulonglong)uStackX_20;
            goto LAB_1481c38b6;
          }
        }
        else if (2 < DAT_14eab53c8) {
          func_0x0001411de0e0(plVar9,alStack_60);
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf74b68);
          if (alStack_60[0] != 0) {
            func_0x000140e282f0();
          }
          pcVar10 = pcVar10 + 0x10;
          plVar9 = plVar9 + 2;
          uVar5 = (ulonglong)uStackX_20;
          goto LAB_1481c38b6;
        }
      }
    }
    else if (cVar4 == '\x04') {
      uStack_b0 = 0;
      if (*plVar9 == 0) {
        if (1 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf77490);
          pcVar10 = pcVar10 + 0x10;
          plVar9 = plVar9 + 2;
          uVar5 = (ulonglong)uStackX_20;
          goto LAB_1481c38b6;
        }
      }
      else {
        cVar4 = func_0x0001481cd440(param_1,*plVar9);
        if (cVar4 != '\0') {
          if (DAT_14eab53c8 < 3) goto LAB_1481c3c96;
          func_0x0001411de0e0(plVar9,alStack_80);
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf77510);
          if (alStack_80[0] != 0) {
            func_0x000140e282f0();
          }
          pcVar10 = pcVar10 + 0x10;
          plVar9 = plVar9 + 2;
          uVar5 = (ulonglong)uStackX_20;
          goto LAB_1481c38b6;
        }
        if (2 < DAT_14eab53c8) {
          func_0x0001411de0e0(plVar9,alStack_70);
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf77570);
          if (alStack_70[0] != 0) {
            func_0x000140e282f0();
          }
          pcVar10 = pcVar10 + 0x10;
          plVar9 = plVar9 + 2;
          uVar5 = (ulonglong)uStackX_20;
          goto LAB_1481c38b6;
        }
      }
    }
  }
LAB_1481c3c96:
  pcVar10 = pcVar10 + 0x10;
  plVar9 = plVar9 + 2;
  uVar5 = (ulonglong)uStackX_20;
  goto LAB_1481c38b6;
}


/* Instruction evidence:
1481c3870 MOV qword ptr [RSP + 0x8],RBX
1481c3875 MOV qword ptr [RSP + 0x10],RDX
1481c387a PUSH RBP
1481c387b PUSH RSI
1481c387c PUSH RDI
1481c387d PUSH R12
1481c387f PUSH R13
1481c3881 PUSH R14
1481c3883 PUSH R15
1481c3885 LEA RBP,[RSP + -0x27]
1481c388a SUB RSP,0xb0
1481c3891 MOV RAX,RDX
1481c3894 MOV R13,RCX
1481c3897 MOV R12,qword ptr [RDX]
1481c389a MOVSXD RCX,dword ptr [RDX + 0x8]
1481c389e MOV dword ptr [RBP + 0x7f],ECX
1481c38a1 MOV RBX,RCX
1481c38a4 SHL RBX,0x4
1481c38a8 ADD RBX,R12
1481c38ab MOV qword ptr [RBP + -0x69],RBX
1481c38af LEA RDI,[R12 + 0x8]
1481c38b4 XOR ESI,ESI
1481c38b6 CMP dword ptr [RAX + 0x8],ECX
1481c38b9 JZ 0x1481c38ce
1481c38bb MOV byte ptr [RBP + 0x77],0x0
1481c38bf LEA RCX,[RBP + 0x77]
1481c38c3 CALL 0x14bc1cf90
1481c38c8 TEST AL,AL
1481c38ca JZ 0x1481c38ce
1481c38cc NOP
1481c38cd INT3
1481c38ce CMP R12,RBX
1481c38d1 JZ 0x1481c3caa
1481c38d7 MOVZX ECX,byte ptr [R12]
1481c38dc TEST ECX,ECX
1481c38de JZ 0x1481c3bac
1481c38e4 SUB ECX,0x1
1481c38e7 JZ 0x1481c3b5b
1481c38ed SUB ECX,0x1
1481c38f0 JZ 0x1481c3b3c
1481c38f6 SUB ECX,0x1
1481c38f9 JZ 0x1481c3a22
1481c38ff CMP ECX,0x1
1481c3902 JNZ 0x1481c3c96
1481c3908 MOV RAX,qword ptr [RDI]
1481c390b MOV qword ptr [RBP + -0x51],0x0
1481c3913 CMP RAX,qword ptr [RBP + -0x51]
1481c3917 JNZ 0x1481c394d
1481c3919 CMP byte ptr [0x14eab53c8],0x2
1481c3920 JC 0x1481c3c96
1481c3926 LEA RDX,[0x14cf77490]
1481c392d LEA RCX,[0x14eab53c8]
1481c3934 CALL 0x140f24ba0
1481c3939 ADD R12,0x10
1481c393d ADD RDI,0x10
1481c3941 MOV RAX,qword ptr [RBP + 0x6f]
1481c3945 MOV ECX,dword ptr [RBP + 0x7f]
1481c3948 JMP 0x1481c38b6
1481c394d MOV RDX,RAX
1481c3950 MOV RCX,R13
1481c3953 CALL 0x1481cd440
1481c3958 TEST AL,AL
1481c395a JZ 0x1481c39bf
1481c395c CMP byte ptr [0x14eab53c8],0x3
1481c3963 JC 0x1481c3c96
1481c3969 LEA RDX,[RBP + -0x21]
1481c396d MOV RCX,RDI
1481c3970 CALL 0x1411de0e0
1481c3975 NOP
1481c3976 CMP dword ptr [RAX + 0x8],0x0
1481c397a JZ 0x1481c3981
1481c397c MOV R8,qword ptr [RAX]
1481c397f JMP 0x1481c3988
1481c3981 LEA R8,[0x14bce4e94]
1481c3988 LEA RDX,[0x14cf77510]
1481c398f LEA RCX,[0x14eab53c8]
1481c3996 CALL 0x140f24ba0
1481c399b NOP
1481c399c MOV RCX,qword ptr [RBP + -0x21]
1481c39a0 TEST RCX,RCX
1481c39a3 JZ 0x1481c39ab
1481c39a5 CALL 0x140e282f0
1481c39aa NOP
1481c39ab ADD R12,0x10
1481c39af ADD RDI,0x10
1481c39b3 MOV RAX,qword ptr [RBP + 0x6f]
1481c39b7 MOV ECX,dword ptr [RBP + 0x7f]
1481c39ba JMP 0x1481c38b6
1481c39bf CMP byte ptr [0x14eab53c8],0x3
1481c39c6 JC 0x1481c3c96
1481c39cc LEA RDX,[RBP + -0x11]
1481c39d0 MOV RCX,RDI
1481c39d3 CALL 0x1411de0e0
1481c39d8 NOP
1481c39d9 CMP dword ptr [RAX + 0x8],0x0
1481c39dd JZ 0x1481c39e4
1481c39df MOV R8,qword ptr [RAX]
1481c39e2 JMP 0x1481c39eb
1481c39e4 LEA R8,[0x14bce4e94]
1481c39eb LEA RDX,[0x14cf77570]
1481c39f2 LEA RCX,[0x14eab53c8]
1481c39f9 CALL 0x140f24ba0
1481c39fe NOP
1481c39ff MOV RCX,qword ptr [RBP + -0x11]
1481c3a03 TEST RCX,RCX
1481c3a06 JZ 0x1481c3a0e
1481c3a08 CALL 0x140e282f0
1481c3a0d NOP
1481c3a0e ADD R12,0x10
1481c3a12 ADD RDI,0x10
1481c3a16 MOV RAX,qword ptr [RBP + 0x6f]
1481c3a1a MOV ECX,dword ptr [RBP + 0x7f]
1481c3a1d JMP 0x1481c38b6
1481c3a22 MOV RAX,qword ptr [RDI]
1481c3a25 MOV qword ptr [RBP + -0x49],0x0
1481c3a2d CMP RAX,qword ptr [RBP + -0x49]
1481c3a31 JNZ 0x1481c3a67
1481c3a33 CMP byte ptr [0x14eab53c8],0x2
1481c3a3a JC 0x1481c3c96
1481c3a40 LEA RDX,[0x14cf74ae8]
1481c3a47 LEA RCX,[0x14eab53c8]
1481c3a4e CALL 0x140f24ba0
1481c3a53 ADD R12,0x10
1481c3a57 ADD RDI,0x10
1481c3a5b MOV RAX,qword ptr [RBP + 0x6f]
1481c3a5f MOV ECX,dword ptr [RBP + 0x7f]
1481c3a62 JMP 0x1481c38b6
1481c3a67 MOV RDX,RAX
1481c3a6a MOV RCX,R13
1481c3a6d CALL 0x1481cd680
1481c3a72 TEST AL,AL
1481c3a74 JZ 0x1481c3ad9
1481c3a76 CMP byte ptr [0x14eab53c8],0x3
1481c3a7d JC 0x1481c3c96
1481c3a83 LEA RDX,[RBP + -0x1]
1481c3a87 MOV RCX,RDI
1481c3a8a CALL 0x1411de0e0
1481c3a8f NOP
1481c3a90 CMP dword ptr [RAX + 0x8],0x0
1481c3a94 JZ 0x1481c3a9b
1481c3a96 MOV R8,qword ptr [RAX]
1481c3a99 JMP 0x1481c3aa2
1481c3a9b LEA R8,[0x14bce4e94]
1481c3aa2 LEA RDX,[0x14cf74b68]
1481c3aa9 LEA RCX,[0x14eab53c8]
1481c3ab0 CALL 0x140f24ba0
1481c3ab5 NOP
1481c3ab6 MOV RCX,qword ptr [RBP + -0x1]
1481c3aba TEST RCX,RCX
1481c3abd JZ 0x1481c3ac5
1481c3abf CALL 0x140e282f0
1481c3ac4 NOP
1481c3ac5 ADD R12,0x10
1481c3ac9 ADD RDI,0x10
1481c3acd MOV RAX,qword ptr [RBP + 0x6f]
1481c3ad1 MOV ECX,dword ptr [RBP + 0x7f]
1481c3ad4 JMP 0x1481c38b6
1481c3ad9 CMP byte ptr [0x14eab53c8],0x3
1481c3ae0 JC 0x1481c3c96
1481c3ae6 LEA RDX,[RBP + 0xf]
1481c3aea MOV RCX,RDI
1481c3aed CALL 0x1411de0e0
1481c3af2 NOP
1481c3af3 CMP dword ptr [RAX + 0x8],0x0
1481c3af7 JZ 0x1481c3afe
1481c3af9 MOV R8,qword ptr [RAX]
1481c3afc JMP 0x1481c3b05
1481c3afe LEA R8,[0x14bce4e94]
1481c3b05 LEA RDX,[0x14cf74bd8]
1481c3b0c LEA RCX,[0x14eab53c8]
1481c3b13 CALL 0x140f24ba0
1481c3b18 NOP
1481c3b19 MOV RCX,qword ptr [RBP + 0xf]
1481c3b1d TEST RCX,RCX
1481c3b20 JZ 0x1481c3b28
1481c3b22 CALL 0x140e282f0
1481c3b27 NOP
1481c3b28 ADD R12,0x10
1481c3b2c ADD RDI,0x10
1481c3b30 MOV RAX,qword ptr [RBP + 0x6f]
1481c3b34 MOV ECX,dword ptr [RBP + 0x7f]
1481c3b37 JMP 0x1481c38b6
1481c3b3c MOV RDX,RDI
1481c3b3f MOV RCX,R13
1481c3b42 CALL 0x1481c3cd0
1481c3b47 ADD R12,0x10
1481c3b4b ADD RDI,0x10
1481c3b4f MOV RAX,qword ptr [RBP + 0x6f]
1481c3b53 MOV ECX,dword ptr [RBP + 0x7f]
1481c3b56 JMP 0x1481c38b6
1481c3b5b MOV EBX,dword ptr [RDI + -0x4]
1481c3b5e TEST EBX,EBX
1481c3b60 JLE 0x1481c3c92
1481c3b66 ADD dword ptr [R13 + 0x58],EBX
1481c3b6a MOV RCX,qword ptr [R13 + 0x70]
1481c3b6e TEST RCX,RCX
1481c3b71 JZ 0x1481c3b93
1481c3b73 MOV EDX,EBX
1481c3b75 CALL 0x1481d3580
1481c3b7a CMP byte ptr [0x14eab53c8],0x3
1481c3b81 JC 0x1481c3c92
1481c3b87 LEA RDX,[0x14cf74788]
1481c3b8e JMP 0x1481c3c83
1481c3b93 CMP byte ptr [0x14eab53c8],0x3
1481c3b9a JC 0x1481c3c92
1481c3ba0 LEA RDX,[0x14cf747f8]
1481c3ba7 JMP 0x1481c3c83
1481c3bac MOV EBX,dword ptr [RDI + -0x4]
1481c3baf TEST EBX,EBX
1481c3bb1 JLE 0x1481c3c92
1481c3bb7 LEA RDX,[0x14cad0ba0]
1481c3bbe LEA RCX,[RBP + -0x31]
1481c3bc2 CALL 0x140cf7750
1481c3bc7 NOP
1481c3bc8 ADD dword ptr [R13 + 0x40],EBX
1481c3bcc ADD dword ptr [R13 + 0x54],EBX
1481c3bd0 LEA RAX,[RBP + -0x61]
1481c3bd4 MOV qword ptr [RBP + 0x77],RAX
1481c3bd8 MOV qword ptr [RBP + -0x61],RSI
1481c3bdc MOVSXD RSI,dword ptr [RBP + -0x29]
1481c3be0 MOV R14,qword ptr [RBP + -0x31]
1481c3be4 MOV dword ptr [RBP + -0x59],ESI
1481c3be7 TEST ESI,ESI
1481c3be9 JNZ 0x1481c3bf2
1481c3beb XOR ESI,ESI
1481c3bed MOV dword ptr [RBP + -0x55],ESI
1481c3bf0 JMP 0x1481c3c14
1481c3bf2 XOR R8D,R8D
1481c3bf5 MOV EDX,ESI
1481c3bf7 LEA RCX,[RBP + -0x61]
1481c3bfb CALL 0x140ca39a0
1481c3c00 MOV R8,RSI
1481c3c03 ADD R8,R8
1481c3c06 MOV RDX,R14
1481c3c09 MOV RCX,qword ptr [RBP + -0x61]
1481c3c0d CALL 0x14b89502e
1481c3c12 XOR ESI,ESI
1481c3c14 LEA RAX,[RBP + -0x61]
1481c3c18 MOV qword ptr [RBP + 0x77],RAX
1481c3c1c LEA R8,[RBP + -0x61]
1481c3c20 MOV EDX,EBX
1481c3c22 LEA RCX,[R13 + 0x378]
1481c3c29 CALL 0x148155e80
1481c3c2e NOP
1481c3c2f MOV RCX,qword ptr [RBP + -0x61]
1481c3c33 TEST RCX,RCX
1481c3c36 JZ 0x1481c3c3e
1481c3c38 CALL 0x140e282f0
1481c3c3d NOP
1481c3c3e MOV RCX,R13
1481c3c41 CALL 0x1481b4f10
1481c3c46 MOV qword ptr [RBP + -0x41],RSI
1481c3c4a MOV qword ptr [RBP + -0x39],0x0
1481c3c52 LEA R9,[RBP + -0x41]
1481c3c56 MOV R8D,EBX
1481c3c59 MOV DL,0xf
1481c3c5b MOV RCX,R13
1481c3c5e CALL 0x1481ce250
1481c3c63 NOP
1481c3c64 MOV RCX,qword ptr [RBP + -0x31]
1481c3c68 TEST RCX,RCX
1481c3c6b JZ 0x1481c3c73
1481c3c6d CALL 0x140e282f0
1481c3c72 NOP
1481c3c73 CMP byte ptr [0x14eab53c8],0x3
1481c3c7a JC 0x1481c3c92
1481c3c7c LEA RDX,[0x14cf74738]
1481c3c83 MOV R8D,EBX
1481c3c86 LEA RCX,[0x14eab53c8]
1481c3c8d CALL 0x140f24ba0
1481c3c92 MOV RBX,qword ptr [RBP + -0x69]
1481c3c96 ADD R12,0x10
1481c3c9a ADD RDI,0x10
1481c3c9e MOV RAX,qword ptr [RBP + 0x6f]
1481c3ca2 MOV ECX,dword ptr [RBP + 0x7f]
1481c3ca5 JMP 0x1481c38b6
1481c3caa MOV RBX,qword ptr [RSP + 0xf0]
1481c3cb2 ADD RSP,0xb0
1481c3cb9 POP R15
1481c3cbb POP R14
1481c3cbd POP R13
1481c3cbf POP R12
1481c3cc1 POP RDI
1481c3cc2 POP RSI
1481c3cc3 POP RBP
1481c3cc4 RET
*/
