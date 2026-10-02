
/* 1481c3cd0 GrantUnlockPackReward */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Possible PIC construction at 0x0001481c3dc6: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0001481c3e5b: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0001481c3eb8: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0001481c3e61) */
/* WARNING: Removing unreachable block (ram,0x0001481c3e6b) */
/* WARNING: Removing unreachable block (ram,0x0001481c3e71) */
/* WARNING: Removing unreachable block (ram,0x0001481c3dcc) */
/* WARNING: Removing unreachable block (ram,0x0001481c3dd6) */
/* WARNING: Removing unreachable block (ram,0x0001481c3ddc) */
/* WARNING: Removing unreachable block (ram,0x0001481c3ebe) */
/* WARNING: Removing unreachable block (ram,0x0001481c3ec8) */

void GrantUnlockPackReward(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  char cVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  longlong alStack_18 [2];
  
  if ((*param_2 == 0) || (lVar1 = *(longlong *)(param_1 + 0x70), lVar1 == 0)) {
    if (DAT_14eab53c8 < 2) {
      return;
    }
  }
  else {
    uVar3 = func_0x0001411de0e0(param_2,alStack_18);
    cVar2 = func_0x0001481d6810(lVar1,uVar3);
    if (alStack_18[0] != 0) {
      func_0x000140e282f0();
    }
    if (cVar2 == '\0') {
      uVar3 = *(undefined8 *)(param_1 + 0x70);
      uVar4 = func_0x0001411de0e0(param_2,alStack_18);
      cVar2 = func_0x0001481d57b0(uVar3,uVar4);
      if (alStack_18[0] != 0) {
        func_0x000140e282f0();
      }
      if (cVar2 == '\0') {
        if (DAT_14eab53c8 < 2) {
          return;
        }
        func_0x0001411de0e0(param_2,alStack_18);
      }
      else {
        if (DAT_14eab53c8 < 3) {
          return;
        }
        func_0x0001411de0e0(param_2,alStack_18);
      }
    }
    else {
      if (DAT_14eab53c8 < 3) {
        return;
      }
      func_0x0001411de0e0(param_2,alStack_18);
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* Instruction evidence:
1481c3cd0 MOV qword ptr [RSP + 0x8],RBX
1481c3cd5 MOV qword ptr [RSP + 0x18],RSI
1481c3cda PUSH RDI
1481c3cdb SUB RSP,0x30
1481c3cdf MOV RDI,RDX
1481c3ce2 MOV RSI,RCX
1481c3ce5 MOV RAX,qword ptr [RDX]
1481c3ce8 XOR ECX,ECX
1481c3cea MOV qword ptr [RSP + 0x48],RCX
1481c3cef CMP RAX,RCX
1481c3cf2 JNZ 0x1481c3d23
1481c3cf4 CMP byte ptr [0x14eab53c8],0x2
1481c3cfb JC 0x1481c3ece
1481c3d01 LEA RDX,[0x14cf748a0]
1481c3d08 LEA RCX,[0x14eab53c8]
1481c3d0f MOV RBX,qword ptr [RSP + 0x40]
1481c3d14 MOV RSI,qword ptr [RSP + 0x50]
1481c3d19 ADD RSP,0x30
1481c3d1d POP RDI
1481c3d1e JMP 0x140f24ba0
1481c3d23 MOV RBX,qword ptr [RSI + 0x70]
1481c3d27 TEST RBX,RBX
1481c3d2a JNZ 0x1481c3d5b
1481c3d2c CMP byte ptr [0x14eab53c8],0x2
1481c3d33 JC 0x1481c3ece
1481c3d39 LEA RDX,[0x14cf74918]
1481c3d40 LEA RCX,[0x14eab53c8]
1481c3d47 MOV RBX,qword ptr [RSP + 0x40]
1481c3d4c MOV RSI,qword ptr [RSP + 0x50]
1481c3d51 ADD RSP,0x30
1481c3d55 POP RDI
1481c3d56 JMP 0x140f24ba0
1481c3d5b LEA RDX,[RSP + 0x20]
1481c3d60 MOV RCX,RDI
1481c3d63 CALL 0x1411de0e0
1481c3d68 NOP
1481c3d69 MOV RDX,RAX
1481c3d6c MOV RCX,RBX
1481c3d6f CALL 0x1481d6810
1481c3d74 MOVZX EBX,AL
1481c3d77 MOV RCX,qword ptr [RSP + 0x20]
1481c3d7c TEST RCX,RCX
1481c3d7f JZ 0x1481c3d87
1481c3d81 CALL 0x140e282f0
1481c3d86 NOP
1481c3d87 TEST BL,BL
1481c3d89 JZ 0x1481c3dec
1481c3d8b CMP byte ptr [0x14eab53c8],0x3
1481c3d92 JC 0x1481c3ece
1481c3d98 LEA RDX,[RSP + 0x20]
1481c3d9d MOV RCX,RDI
1481c3da0 CALL 0x1411de0e0
1481c3da5 NOP
1481c3da6 CMP dword ptr [RAX + 0x8],0x0
1481c3daa JZ 0x1481c3db1
1481c3dac MOV R8,qword ptr [RAX]
1481c3daf JMP 0x1481c3db8
1481c3db1 LEA R8,[0x14bce4e94]
1481c3db8 LEA RDX,[0x14cf749b0]
1481c3dbf LEA RCX,[0x14eab53c8]
1481c3dc6 CALL 0x140f24ba0
1481c3dcb NOP
1481c3dcc MOV RCX,qword ptr [RSP + 0x20]
1481c3dd1 TEST RCX,RCX
1481c3dd4 JZ 0x1481c3ddc
1481c3dd6 CALL 0x140e282f0
1481c3ddb NOP
1481c3ddc MOV RBX,qword ptr [RSP + 0x40]
1481c3de1 MOV RSI,qword ptr [RSP + 0x50]
1481c3de6 ADD RSP,0x30
1481c3dea POP RDI
1481c3deb RET
1481c3dec MOV RBX,qword ptr [RSI + 0x70]
1481c3df0 LEA RDX,[RSP + 0x20]
1481c3df5 MOV RCX,RDI
1481c3df8 CALL 0x1411de0e0
1481c3dfd NOP
1481c3dfe MOV RDX,RAX
1481c3e01 MOV RCX,RBX
1481c3e04 CALL 0x1481d57b0
1481c3e09 MOVZX EBX,AL
1481c3e0c MOV RCX,qword ptr [RSP + 0x20]
1481c3e11 TEST RCX,RCX
1481c3e14 JZ 0x1481c3e1c
1481c3e16 CALL 0x140e282f0
1481c3e1b NOP
1481c3e1c TEST BL,BL
1481c3e1e JZ 0x1481c3e81
1481c3e20 CMP byte ptr [0x14eab53c8],0x3
1481c3e27 JC 0x1481c3ece
1481c3e2d LEA RDX,[RSP + 0x20]
1481c3e32 MOV RCX,RDI
1481c3e35 CALL 0x1411de0e0
1481c3e3a NOP
1481c3e3b CMP dword ptr [RAX + 0x8],0x0
1481c3e3f JZ 0x1481c3e46
1481c3e41 MOV R8,qword ptr [RAX]
1481c3e44 JMP 0x1481c3e4d
1481c3e46 LEA R8,[0x14bce4e94]
1481c3e4d LEA RDX,[0x14cf74a08]
1481c3e54 LEA RCX,[0x14eab53c8]
1481c3e5b CALL 0x140f24ba0
1481c3e60 NOP
1481c3e61 MOV RCX,qword ptr [RSP + 0x20]
1481c3e66 TEST RCX,RCX
1481c3e69 JZ 0x1481c3e71
1481c3e6b CALL 0x140e282f0
1481c3e70 NOP
1481c3e71 MOV RBX,qword ptr [RSP + 0x40]
1481c3e76 MOV RSI,qword ptr [RSP + 0x50]
1481c3e7b ADD RSP,0x30
1481c3e7f POP RDI
1481c3e80 RET
1481c3e81 CMP byte ptr [0x14eab53c8],0x2
1481c3e88 JC 0x1481c3ece
1481c3e8a LEA RDX,[RSP + 0x20]
1481c3e8f MOV RCX,RDI
1481c3e92 CALL 0x1411de0e0
1481c3e97 NOP
1481c3e98 CMP dword ptr [RAX + 0x8],0x0
1481c3e9c JZ 0x1481c3ea3
1481c3e9e MOV R8,qword ptr [RAX]
1481c3ea1 JMP 0x1481c3eaa
1481c3ea3 LEA R8,[0x14bce4e94]
1481c3eaa LEA RDX,[0x14cf74a78]
1481c3eb1 LEA RCX,[0x14eab53c8]
1481c3eb8 CALL 0x140f24ba0
1481c3ebd NOP
1481c3ebe MOV RCX,qword ptr [RSP + 0x20]
1481c3ec3 TEST RCX,RCX
1481c3ec6 JZ 0x1481c3ece
1481c3ec8 CALL 0x140e282f0
1481c3ecd NOP
1481c3ece MOV RBX,qword ptr [RSP + 0x40]
1481c3ed3 MOV RSI,qword ptr [RSP + 0x50]
1481c3ed8 ADD RSP,0x30
1481c3edc POP RDI
1481c3edd RET
*/

/* 1481cd680 UnlockPlayerCard */

ulonglong UnlockPlayerCard(longlong param_1,ulonglong param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  ulonglong in_RAX;
  ulonglong uVar4;
  longlong lVar5;
  undefined8 *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  ulonglong uStackX_10;
  undefined8 uStackX_18;
  undefined8 uStackX_20;
  longlong alStack_88 [2];
  longlong alStack_78 [2];
  undefined1 auStack_68 [8];
  longlong lStack_60;
  undefined1 auStack_58 [8];
  longlong *plStack_50;
  
  uStackX_20 = 0;
  uStackX_10 = param_2;
  if (param_2 == 0) {
    if (DAT_14eab53c8 < 3) {
LAB_1481cd7ed:
      uVar4 = in_RAX & 0xffffffffffffff00;
    }
    else {
      uVar4 = func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf754d8);
      uVar4 = uVar4 & 0xffffffffffffff00;
    }
  }
  else {
    uStackX_18 = param_2;
    iVar3 = func_0x0001411c2eb0(param_2 & 0xffffffff);
    if (*(int *)(param_1 + 0x408) != *(int *)(param_1 + 0x434)) {
      lVar5 = param_1 + 0x438;
      if (*(longlong *)(param_1 + 0x440) != 0) {
        lVar5 = *(longlong *)(param_1 + 0x440);
      }
      iVar3 = *(int *)(lVar5 + (ulonglong)
                               (*(int *)(param_1 + 0x448) - 1U & uStackX_18._4_4_ + iVar3) * 4);
      if (iVar3 != -1) {
        do {
          lVar5 = (longlong)iVar3;
          in_RAX = lVar5 * 2;
          if (*(ulonglong *)(*(longlong *)(param_1 + 0x400) + lVar5 * 0x10) == param_2) {
            if (2 < DAT_14eab53c8) {
              puVar6 = (undefined8 *)func_0x0001411de0e0(&uStackX_10,alStack_88);
              if (*(int *)(puVar6 + 1) == 0) {
                puVar7 = &UNK_14bce4e94;
              }
              else {
                puVar7 = (undefined *)*puVar6;
              }
              in_RAX = func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf75560,puVar7);
              if (alStack_88[0] != 0) {
                in_RAX = func_0x000140e282f0();
              }
            }
            goto LAB_1481cd7ed;
          }
          iVar3 = *(int *)(*(longlong *)(param_1 + 0x400) + 8 + lVar5 * 0x10);
        } while (iVar3 != -1);
      }
    }
    func_0x0001481c1a60(param_1,auStack_68,uStackX_10);
    alStack_88[0] = 0;
    if (lStack_60 == 0) {
      if (1 < DAT_14eab53c8) {
        puVar6 = (undefined8 *)func_0x0001411de0e0(&uStackX_10,alStack_78);
        if (*(int *)(puVar6 + 1) == 0) {
          puVar7 = &UNK_14bce4e94;
        }
        else {
          puVar7 = (undefined *)*puVar6;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf755d0,puVar7);
        if (alStack_78[0] != 0) {
          func_0x000140e282f0();
        }
      }
      uVar4 = 0;
    }
    else {
      func_0x000140cd7960(param_1 + 0x400,&uStackX_18,&uStackX_10,0);
      func_0x0001481cad00(param_1);
      if (2 < DAT_14eab53c8) {
        puVar6 = (undefined8 *)func_0x000140ef8a00(auStack_58);
        puVar7 = &UNK_14bce4e94;
        if (*(int *)(puVar6 + 1) == 0) {
          puVar8 = &UNK_14bce4e94;
        }
        else {
          puVar8 = (undefined *)*puVar6;
        }
        puVar6 = (undefined8 *)func_0x0001411de0e0(&uStackX_10,alStack_78);
        if (*(int *)(puVar6 + 1) != 0) {
          puVar7 = (undefined *)*puVar6;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf75650,puVar7,puVar8);
        if (alStack_78[0] != 0) {
          func_0x000140e282f0();
        }
      }
      uVar4 = 1;
    }
    if (plStack_50 != (longlong *)0x0) {
      LOCK();
      plVar1 = plStack_50 + 1;
      lVar5 = *plVar1;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)lVar5 == 1) {
        (**(code **)*plStack_50)(plStack_50);
        LOCK();
        piVar2 = (int *)((longlong)plStack_50 + 0xc);
        iVar3 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar3 == 1) {
          (**(code **)(*plStack_50 + 8))(plStack_50,1);
        }
      }
    }
  }
  return uVar4;
}


/* Instruction evidence:
1481cd680 MOV qword ptr [RSP + 0x8],RBX
1481cd685 MOV qword ptr [RSP + 0x10],RDX
1481cd68a PUSH RBP
1481cd68b PUSH RSI
1481cd68c PUSH RDI
1481cd68d SUB RSP,0x90
1481cd694 MOV RBX,RDX
1481cd697 MOV RDI,RCX
1481cd69a XOR EBP,EBP
1481cd69c MOV qword ptr [RSP + 0xc8],RBP
1481cd6a4 CMP RDX,RBP
1481cd6a7 JNZ 0x1481cd6d0
1481cd6a9 CMP byte ptr [0x14eab53c8],0x3
1481cd6b0 JC 0x1481cd7ed
1481cd6b6 LEA RDX,[0x14cf754d8]
1481cd6bd LEA RCX,[0x14eab53c8]
1481cd6c4 CALL 0x140f24ba0
1481cd6c9 XOR AL,AL
1481cd6cb JMP 0x1481cd903
1481cd6d0 MOV qword ptr [RSP + 0xc0],RBX
1481cd6d8 MOV ECX,EBX
1481cd6da CALL 0x1411c2eb0
1481cd6df MOV R8D,dword ptr [RSP + 0xc4]
1481cd6e7 ADD R8D,EAX
1481cd6ea MOV EAX,dword ptr [RDI + 0x408]
1481cd6f0 CMP EAX,dword ptr [RDI + 0x434]
1481cd6f6 JZ 0x1481cd744
1481cd6f8 LEA RDX,[RDI + 0x438]
1481cd6ff MOV RAX,qword ptr [RDX + 0x8]
1481cd703 TEST RAX,RAX
1481cd706 CMOVNZ RDX,RAX
1481cd70a MOV ECX,dword ptr [RDI + 0x448]
1481cd710 DEC ECX
1481cd712 MOV EAX,R8D
1481cd715 AND RCX,RAX
1481cd718 MOV EAX,dword ptr [RDX + RCX*0x4]
1481cd71b CMP EAX,-0x1
1481cd71e JZ 0x1481cd744
1481cd720 MOV RCX,qword ptr [RDI + 0x400]
1481cd727 NOP word ptr [RAX + RAX*0x1]
1481cd730 CDQE
1481cd732 ADD RAX,RAX
1481cd735 CMP qword ptr [RCX + RAX*0x8],RBX
1481cd739 JZ 0x1481cd798
1481cd73b MOV EAX,dword ptr [RCX + RAX*0x8 + 0x8]
1481cd73f CMP EAX,-0x1
1481cd742 JNZ 0x1481cd730
1481cd744 MOV R8,qword ptr [RSP + 0xb8]
1481cd74c LEA RDX,[RSP + 0x40]
1481cd751 MOV RCX,RDI
1481cd754 CALL 0x1481c1a60
1481cd759 NOP
1481cd75a MOV qword ptr [RSP + 0x20],RBP
1481cd75f MOV RAX,RBP
1481cd762 CMP qword ptr [RSP + 0x48],RAX
1481cd767 JNZ 0x1481cd82a
1481cd76d CMP byte ptr [0x14eab53c8],0x2
1481cd774 JC 0x1481cd822
1481cd77a LEA RDX,[RSP + 0x30]
1481cd77f LEA RCX,[RSP + 0xb8]
1481cd787 CALL 0x1411de0e0
1481cd78c NOP
1481cd78d CMP dword ptr [RAX + 0x8],0x0
1481cd791 JZ 0x1481cd7f4
1481cd793 MOV RBX,qword ptr [RAX]
1481cd796 JMP 0x1481cd7fb
1481cd798 CMP byte ptr [0x14eab53c8],0x3
1481cd79f JC 0x1481cd7ed
1481cd7a1 LEA RDX,[RSP + 0x20]
1481cd7a6 LEA RCX,[RSP + 0xb8]
1481cd7ae CALL 0x1411de0e0
1481cd7b3 NOP
1481cd7b4 CMP dword ptr [RAX + 0x8],0x0
1481cd7b8 JZ 0x1481cd7bf
1481cd7ba MOV RBX,qword ptr [RAX]
1481cd7bd JMP 0x1481cd7c6
1481cd7bf LEA RBX,[0x14bce4e94]
1481cd7c6 MOV R8,RBX
1481cd7c9 LEA RDX,[0x14cf75560]
1481cd7d0 LEA RCX,[0x14eab53c8]
1481cd7d7 CALL 0x140f24ba0
1481cd7dc NOP
1481cd7dd MOV RCX,qword ptr [RSP + 0x20]
1481cd7e2 TEST RCX,RCX
1481cd7e5 JZ 0x1481cd7ed
1481cd7e7 CALL 0x140e282f0
1481cd7ec NOP
1481cd7ed XOR AL,AL
1481cd7ef JMP 0x1481cd903
1481cd7f4 LEA RBX,[0x14bce4e94]
1481cd7fb MOV R8,RBX
1481cd7fe LEA RDX,[0x14cf755d0]
1481cd805 LEA RCX,[0x14eab53c8]
1481cd80c CALL 0x140f24ba0
1481cd811 NOP
1481cd812 MOV RCX,qword ptr [RSP + 0x30]
1481cd817 TEST RCX,RCX
1481cd81a JZ 0x1481cd822
1481cd81c CALL 0x140e282f0
1481cd821 NOP
1481cd822 XOR SIL,SIL
1481cd825 JMP 0x1481cd8c2
1481cd82a XOR R9D,R9D
1481cd82d LEA R8,[RSP + 0xb8]
1481cd835 LEA RDX,[RSP + 0xc0]
1481cd83d LEA RCX,[RDI + 0x400]
1481cd844 CALL 0x140cd7960
1481cd849 MOV RCX,RDI
1481cd84c CALL 0x1481cad00
1481cd851 CMP byte ptr [0x14eab53c8],0x3
1481cd858 JC 0x1481cd8bf
1481cd85a LEA RCX,[RSP + 0x50]
1481cd85f CALL 0x140ef8a00
1481cd864 LEA RBX,[0x14bce4e94]
1481cd86b CMP dword ptr [RAX + 0x8],0x0
1481cd86f JZ 0x1481cd876
1481cd871 MOV RDI,qword ptr [RAX]
1481cd874 JMP 0x1481cd879
1481cd876 MOV RDI,RBX
1481cd879 LEA RDX,[RSP + 0x30]
1481cd87e LEA RCX,[RSP + 0xb8]
1481cd886 CALL 0x1411de0e0
1481cd88b NOP
1481cd88c CMP dword ptr [RAX + 0x8],0x0
1481cd890 JZ 0x1481cd895
1481cd892 MOV RBX,qword ptr [RAX]
1481cd895 MOV R9,RDI
1481cd898 MOV R8,RBX
1481cd89b LEA RDX,[0x14cf75650]
1481cd8a2 LEA RCX,[0x14eab53c8]
1481cd8a9 CALL 0x140f24ba0
1481cd8ae NOP
1481cd8af MOV RCX,qword ptr [RSP + 0x30]
1481cd8b4 TEST RCX,RCX
1481cd8b7 JZ 0x1481cd8bf
1481cd8b9 CALL 0x140e282f0
1481cd8be NOP
1481cd8bf MOV SIL,0x1
1481cd8c2 MOV RBX,qword ptr [RSP + 0x58]
1481cd8c7 TEST RBX,RBX
1481cd8ca JZ 0x1481cd8ff
1481cd8cc MOV EDI,0xffffffff
1481cd8d1 MOV EAX,EDI
1481cd8d3 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481cd8d8 CMP EAX,0x1
1481cd8db JNZ 0x1481cd8ff
1481cd8dd MOV RAX,qword ptr [RBX]
1481cd8e0 MOV RCX,RBX
1481cd8e3 CALL qword ptr [RAX]
1481cd8e5 XADD.LOCK dword ptr [RBX + 0xc],EDI
1481cd8ea CMP EDI,0x1
1481cd8ed JNZ 0x1481cd8ff
1481cd8ef MOV RDX,qword ptr [RBX]
1481cd8f2 MOV R8,qword ptr [RDX + 0x8]
1481cd8f6 MOV EDX,EDI
1481cd8f8 MOV RCX,RBX
1481cd8fb CALL R8
1481cd8fe NOP
1481cd8ff MOVZX EAX,SIL
1481cd903 MOV RBX,qword ptr [RSP + 0xb0]
1481cd90b ADD RSP,0x90
1481cd912 POP RDI
1481cd913 POP RSI
1481cd914 POP RBP
1481cd915 RET
*/

/* 1481cd440 UnlockModifier */

ulonglong UnlockModifier(longlong param_1,ulonglong param_2)

{
  char cVar1;
  int iVar2;
  ulonglong uVar3;
  longlong lVar4;
  undefined8 *puVar5;
  undefined *puVar6;
  ulonglong uStackX_10;
  undefined8 uStackX_18;
  longlong alStack_58 [2];
  undefined1 auStack_48 [8];
  undefined1 auStack_40 [56];
  
  uVar3 = 0;
  uStackX_18 = 0;
  uStackX_10 = param_2;
  if (param_2 == 0) {
    if (2 < DAT_14eab53c8) {
      uVar3 = func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf77160);
      return uVar3 & 0xffffffffffffff00;
    }
LAB_1481cd5ad:
    return uVar3 & 0xffffffffffffff00;
  }
  uStackX_18 = param_2;
  iVar2 = func_0x0001411c2eb0(param_2 & 0xffffffff);
  if (*(int *)(param_1 + 0x460) != *(int *)(param_1 + 0x48c)) {
    lVar4 = param_1 + 0x490;
    if (*(longlong *)(param_1 + 0x498) != 0) {
      lVar4 = *(longlong *)(param_1 + 0x498);
    }
    iVar2 = *(int *)(lVar4 + (ulonglong)(*(int *)(param_1 + 0x4a0) - 1U & uStackX_18._4_4_ + iVar2)
                             * 4);
    if (iVar2 != -1) {
      do {
        lVar4 = (longlong)iVar2;
        uVar3 = lVar4 * 2;
        if (*(ulonglong *)(*(longlong *)(param_1 + 0x458) + lVar4 * 0x10) == param_2) {
          if (2 < DAT_14eab53c8) {
            puVar5 = (undefined8 *)func_0x0001411de0e0(&uStackX_10,alStack_58);
            if (*(int *)(puVar5 + 1) == 0) {
              puVar6 = &UNK_14bce4e94;
            }
            else {
              puVar6 = (undefined *)*puVar5;
            }
            uVar3 = func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf771e8,puVar6);
            if (alStack_58[0] != 0) {
              uVar3 = func_0x000140e282f0();
            }
          }
          goto LAB_1481cd5ad;
        }
        iVar2 = *(int *)(*(longlong *)(param_1 + 0x458) + 8 + lVar4 * 0x10);
      } while (iVar2 != -1);
    }
  }
  func_0x0001481c1380(param_1,auStack_48,uStackX_10);
  cVar1 = func_0x000140ecdff0(auStack_40);
  if (cVar1 == '\0') {
    func_0x000140cd7960(param_1 + 0x458,&uStackX_18,&uStackX_10,0);
    func_0x0001481cad00(param_1);
    if (2 < DAT_14eab53c8) {
      puVar5 = (undefined8 *)func_0x000140ef8a00(auStack_40);
      if (*(int *)(puVar5 + 1) == 0) {
        puVar6 = &UNK_14bce4e94;
      }
      else {
        puVar6 = (undefined *)*puVar5;
      }
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf772f8,puVar6);
    }
    uVar3 = 1;
  }
  else {
    if (1 < DAT_14eab53c8) {
      puVar5 = (undefined8 *)func_0x0001411de0e0(&uStackX_10,alStack_58);
      if (*(int *)(puVar5 + 1) == 0) {
        puVar6 = &UNK_14bce4e94;
      }
      else {
        puVar6 = (undefined *)*puVar5;
      }
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf77268,puVar6);
      if (alStack_58[0] != 0) {
        func_0x000140e282f0();
      }
    }
    uVar3 = 0;
  }
  func_0x0001481520d0(auStack_48);
  return uVar3;
}


/* Instruction evidence:
1481cd440 MOV qword ptr [RSP + 0x8],RBX
1481cd445 MOV qword ptr [RSP + 0x20],RSI
1481cd44a MOV qword ptr [RSP + 0x10],RDX
1481cd44f PUSH RDI
1481cd450 SUB RSP,0x70
1481cd454 MOV RBX,RDX
1481cd457 MOV RDI,RCX
1481cd45a XOR EAX,EAX
1481cd45c MOV qword ptr [RSP + 0x90],RAX
1481cd464 CMP RDX,RAX
1481cd467 JNZ 0x1481cd49d
1481cd469 CMP byte ptr [0x14eab53c8],0x3
1481cd470 JC 0x1481cd5ad
1481cd476 LEA RDX,[0x14cf77160]
1481cd47d LEA RCX,[0x14eab53c8]
1481cd484 CALL 0x140f24ba0
1481cd489 XOR AL,AL
1481cd48b LEA R11,[RSP + 0x70]
1481cd490 MOV RBX,qword ptr [R11 + 0x10]
1481cd494 MOV RSI,qword ptr [R11 + 0x28]
1481cd498 MOV RSP,R11
1481cd49b POP RDI
1481cd49c RET
1481cd49d MOV qword ptr [RSP + 0x90],RBX
1481cd4a5 MOV ECX,EBX
1481cd4a7 CALL 0x1411c2eb0
1481cd4ac MOV R8D,dword ptr [RSP + 0x94]
1481cd4b4 ADD R8D,EAX
1481cd4b7 MOV EAX,dword ptr [RDI + 0x460]
1481cd4bd CMP EAX,dword ptr [RDI + 0x48c]
1481cd4c3 JZ 0x1481cd508
1481cd4c5 LEA RDX,[RDI + 0x490]
1481cd4cc MOV RAX,qword ptr [RDX + 0x8]
1481cd4d0 TEST RAX,RAX
1481cd4d3 CMOVNZ RDX,RAX
1481cd4d7 MOV ECX,dword ptr [RDI + 0x4a0]
1481cd4dd DEC ECX
1481cd4df MOV EAX,R8D
1481cd4e2 AND RCX,RAX
1481cd4e5 MOV EAX,dword ptr [RDX + RCX*0x4]
1481cd4e8 CMP EAX,-0x1
1481cd4eb JZ 0x1481cd508
1481cd4ed MOV RCX,qword ptr [RDI + 0x458]
1481cd4f4 CDQE
1481cd4f6 ADD RAX,RAX
1481cd4f9 CMP qword ptr [RCX + RAX*0x8],RBX
1481cd4fd JZ 0x1481cd55b
1481cd4ff MOV EAX,dword ptr [RCX + RAX*0x8 + 0x8]
1481cd503 CMP EAX,-0x1
1481cd506 JNZ 0x1481cd4f4
1481cd508 MOV R8,qword ptr [RSP + 0x88]
1481cd510 LEA RDX,[RSP + 0x30]
1481cd515 MOV RCX,RDI
1481cd518 CALL 0x1481c1380
1481cd51d NOP
1481cd51e LEA RCX,[RSP + 0x38]
1481cd523 CALL 0x140ecdff0
1481cd528 TEST AL,AL
1481cd52a JZ 0x1481cd5f0
1481cd530 CMP byte ptr [0x14eab53c8],0x2
1481cd537 JC 0x1481cd5ec
1481cd53d LEA RDX,[RSP + 0x20]
1481cd542 LEA RCX,[RSP + 0x88]
1481cd54a CALL 0x1411de0e0
1481cd54f NOP
1481cd550 CMP dword ptr [RAX + 0x8],0x0
1481cd554 JZ 0x1481cd5c1
1481cd556 MOV R8,qword ptr [RAX]
1481cd559 JMP 0x1481cd5c8
1481cd55b CMP byte ptr [0x14eab53c8],0x3
1481cd562 JC 0x1481cd5ad
1481cd564 LEA RDX,[RSP + 0x20]
1481cd569 LEA RCX,[RSP + 0x88]
1481cd571 CALL 0x1411de0e0
1481cd576 NOP
1481cd577 CMP dword ptr [RAX + 0x8],0x0
1481cd57b JZ 0x1481cd582
1481cd57d MOV R8,qword ptr [RAX]
1481cd580 JMP 0x1481cd589
1481cd582 LEA R8,[0x14bce4e94]
1481cd589 LEA RDX,[0x14cf771e8]
1481cd590 LEA RCX,[0x14eab53c8]
1481cd597 CALL 0x140f24ba0
1481cd59c NOP
1481cd59d MOV RCX,qword ptr [RSP + 0x20]
1481cd5a2 TEST RCX,RCX
1481cd5a5 JZ 0x1481cd5ad
1481cd5a7 CALL 0x140e282f0
1481cd5ac NOP
1481cd5ad XOR AL,AL
1481cd5af LEA R11,[RSP + 0x70]
1481cd5b4 MOV RBX,qword ptr [R11 + 0x10]
1481cd5b8 MOV RSI,qword ptr [R11 + 0x28]
1481cd5bc MOV RSP,R11
1481cd5bf POP RDI
1481cd5c0 RET
1481cd5c1 LEA R8,[0x14bce4e94]
1481cd5c8 LEA RDX,[0x14cf77268]
1481cd5cf LEA RCX,[0x14eab53c8]
1481cd5d6 CALL 0x140f24ba0
1481cd5db NOP
1481cd5dc MOV RCX,qword ptr [RSP + 0x20]
1481cd5e1 TEST RCX,RCX
1481cd5e4 JZ 0x1481cd5ec
1481cd5e6 CALL 0x140e282f0
1481cd5eb NOP
1481cd5ec XOR BL,BL
1481cd5ee JMP 0x1481cd651
1481cd5f0 XOR R9D,R9D
1481cd5f3 LEA R8,[RSP + 0x88]
1481cd5fb LEA RDX,[RSP + 0x90]
1481cd603 LEA RCX,[RDI + 0x458]
1481cd60a CALL 0x140cd7960
1481cd60f MOV RCX,RDI
1481cd612 CALL 0x1481cad00
1481cd617 CMP byte ptr [0x14eab53c8],0x3
1481cd61e JC 0x1481cd64f
1481cd620 LEA RCX,[RSP + 0x38]
1481cd625 CALL 0x140ef8a00
1481cd62a CMP dword ptr [RAX + 0x8],0x0
1481cd62e JZ 0x1481cd635
1481cd630 MOV R8,qword ptr [RAX]
1481cd633 JMP 0x1481cd63c
1481cd635 LEA R8,[0x14bce4e94]
1481cd63c LEA RDX,[0x14cf772f8]
1481cd643 LEA RCX,[0x14eab53c8]
1481cd64a CALL 0x140f24ba0
1481cd64f MOV BL,0x1
1481cd651 LEA RCX,[RSP + 0x30]
1481cd656 CALL 0x1481520d0
1481cd65b MOVZX EAX,BL
1481cd65e LEA R11,[RSP + 0x70]
1481cd663 MOV RBX,qword ptr [R11 + 0x10]
1481cd667 MOV RSI,qword ptr [R11 + 0x28]
1481cd66b MOV RSP,R11
1481cd66e POP RDI
1481cd66f RET
*/
