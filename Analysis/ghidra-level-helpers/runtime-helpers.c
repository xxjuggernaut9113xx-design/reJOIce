
/* 1481b41f0 AddUnlockPoints */

void AddUnlockPoints(longlong param_1,int param_2)

{
  *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + param_2;
  return;
}


/* Instruction evidence:
1481b41f0 ADD dword ptr [RCX + 0x58],EDX
1481b41f3 RET
*/

/* 1481b4200 AddXP */

void AddXP(longlong param_1,int param_2,undefined8 param_3)

{
  longlong *plVar1;
  undefined8 uStack_18;
  undefined8 uStack_10;
  
  if (0 < param_2) {
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + param_2;
    *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) + param_2;
    plVar1 = (longlong *)func_0x000140cf6c30(&uStack_18,param_3);
    func_0x000148155e80(param_1 + 0x378,param_2,plVar1);
    if (*plVar1 != 0) {
      func_0x000140e282f0();
    }
    CheckLevelUp(param_1);
    uStack_18 = 0;
    uStack_10 = 0;
    func_0x0001481ce250(param_1,0xf,param_2,&uStack_18);
  }
  return;
}


/* Instruction evidence:
1481b4200 TEST EDX,EDX
1481b4202 JLE 0x1481b4297
1481b4208 MOV qword ptr [RSP + 0x8],RBX
1481b420d MOV qword ptr [RSP + 0x10],RBP
1481b4212 MOV qword ptr [RSP + 0x18],RSI
1481b4217 PUSH RDI
1481b4218 SUB RSP,0x30
1481b421c MOV EBP,EDX
1481b421e MOV RSI,RCX
1481b4221 ADD dword ptr [RCX + 0x40],EDX
1481b4224 ADD dword ptr [RCX + 0x54],EDX
1481b4227 MOV RDX,R8
1481b422a LEA RCX,[RSP + 0x20]
1481b422f CALL 0x140cf6c30
1481b4234 MOV RBX,RAX
1481b4237 MOV qword ptr [RSP + 0x58],RAX
1481b423c MOV R8,RAX
1481b423f MOV EDX,EBP
1481b4241 LEA RCX,[RSI + 0x378]
1481b4248 CALL 0x148155e80
1481b424d NOP
1481b424e MOV RCX,qword ptr [RBX]
1481b4251 TEST RCX,RCX
1481b4254 JZ 0x1481b425c
1481b4256 CALL 0x140e282f0
1481b425b NOP
1481b425c MOV RCX,RSI
1481b425f CALL 0x1481b4f10
1481b4264 XOR EAX,EAX
1481b4266 MOV qword ptr [RSP + 0x20],RAX
1481b426b MOV qword ptr [RSP + 0x28],RAX
1481b4270 LEA R9,[RSP + 0x20]
1481b4275 MOV R8D,EBP
1481b4278 MOV DL,0xf
1481b427a MOV RCX,RSI
1481b427d CALL 0x1481ce250
1481b4282 NOP
1481b4283 MOV RBX,qword ptr [RSP + 0x40]
1481b4288 MOV RBP,qword ptr [RSP + 0x48]
1481b428d MOV RSI,qword ptr [RSP + 0x50]
1481b4292 ADD RSP,0x30
1481b4296 POP RDI
1481b4297 RET
*/

/* 1481b4f10 CheckLevelUp */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void CheckLevelUp(longlong param_1)

{
  longlong *plVar1;
  longlong lVar2;
  ulonglong uVar3;
  code *pcVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  ulonglong *puVar8;
  undefined8 *puVar9;
  longlong lVar10;
  longlong *plVar11;
  ulonglong *puVar12;
  longlong *plVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined8 unaff_retaddr;
  ulonglong uStackX_8;
  undefined8 uStackX_10;
  undefined1 auStackX_18 [8];
  undefined *puStack_88;
  int iStack_80;
  longlong alStack_78 [2];
  longlong alStack_68 [2];
  longlong alStack_58 [2];
  longlong alStack_48 [2];
  longlong alStack_38 [2];
  
  if (*(int *)(param_1 + 0x50) < 0x14) {
    iVar6 = func_0x0001481c32e0();
    iVar7 = *(int *)(param_1 + 0x40);
    if (iVar6 <= iVar7) {
      do {
        if (0x13 < *(int *)(param_1 + 0x50)) break;
        *(int *)(param_1 + 0x40) = iVar7 - iVar6;
        *(int *)(param_1 + 0x50) = *(int *)(param_1 + 0x50) + 1;
        if (*(longlong *)(param_1 + 0x68) != 0) {
          func_0x000140d169d0(&puStack_88,L"Level_%d");
          plVar1 = *(longlong **)(param_1 + 0x68);
          puVar14 = &UNK_14bce4e94;
          if (iStack_80 != 0) {
            puVar14 = puStack_88;
          }
          puVar8 = (ulonglong *)func_0x0001411a7b80(auStackX_18,puVar14,1);
          uStackX_8 = *puVar8;
          lVar2 = plVar1[5];
          if (lVar2 == 0) {
            if (1 < DAT_14ed60660) {
              puVar9 = (undefined8 *)func_0x00014192e690(plVar1,alStack_78,0);
              if (*(int *)(puVar9 + 1) == 0) {
                puVar14 = &UNK_14bce4e94;
              }
              else {
                puVar14 = (undefined *)*puVar9;
              }
              func_0x000140f24ba0(&DAT_14ed60660,&UNK_14cf775f8,&UNK_14bce4e94,puVar14);
              if (alStack_78[0] != 0) {
                func_0x000140e282f0();
              }
            }
          }
          else {
            lVar10 = func_0x0001481502d0();
            if (lVar10 != 0) {
              if ((*(int *)(lVar10 + 0x38) <= *(int *)(lVar2 + 0x38)) &&
                 (*(longlong *)(*(longlong *)(lVar2 + 0x30) + (longlong)*(int *)(lVar10 + 0x38) * 8)
                  == lVar10 + 0x30)) {
                if (uStackX_8 == 0) {
                  if (2 < DAT_14ed60660) {
                    puVar9 = (undefined8 *)func_0x00014192e690(plVar1,alStack_68,0);
                    if (*(int *)(puVar9 + 1) == 0) {
                      puVar14 = &UNK_14bce4e94;
                    }
                    else {
                      puVar14 = (undefined *)*puVar9;
                    }
                    func_0x000140f24ba0(&DAT_14ed60660,&UNK_14cf77638,&UNK_14bce4e94,puVar14);
                    if (alStack_68[0] != 0) {
                      func_0x000140e282f0();
                    }
                  }
                }
                else {
                  plVar11 = (longlong *)(**(code **)(*plVar1 + 0x2d8))(plVar1);
                  uVar3 = uStackX_8;
                  uStackX_10 = uStackX_8;
                  iVar7 = func_0x0001411c2eb0(uStackX_8 & 0xffffffff);
                  if ((int)plVar11[1] != *(int *)((longlong)plVar11 + 0x34)) {
                    plVar13 = plVar11 + 7;
                    if ((longlong *)plVar11[8] != (longlong *)0x0) {
                      plVar13 = (longlong *)plVar11[8];
                    }
                    iVar7 = *(int *)((longlong)plVar13 +
                                    (ulonglong)((int)plVar11[9] - 1U & uStackX_10._4_4_ + iVar7) * 4
                                    );
                    if (iVar7 != -1) {
                      do {
                        puVar8 = (ulonglong *)(*plVar11 + (longlong)iVar7 * 0x18);
                        if (*puVar8 == uVar3) {
                          puVar12 = puVar8 + 1;
                          if (puVar8 == (ulonglong *)0x0) {
                            puVar12 = (ulonglong *)0x0;
                          }
                          if (puVar12 != (ulonglong *)0x0) {
                            uVar3 = *puVar12;
                            if (uVar3 == 0) {
                              cVar5 = func_0x000140f8dfd0(&UNK_14c7689a0,&UNK_14cf2d4f0,0xf5,
                                                          unaff_retaddr,&UNK_14bce4e94);
                              if (cVar5 != '\0') {
                                pcVar4 = (code *)swi(3);
                                (*pcVar4)();
                                return;
                              }
                            }
                            else {
                              *(int *)(param_1 + 0x58) =
                                   *(int *)(param_1 + 0x58) + *(int *)(uVar3 + 0x10);
                              func_0x000148155dc0(param_1 + 0x348,*(undefined4 *)(param_1 + 0x50),
                                                  *(undefined4 *)(uVar3 + 0x10),uVar3 + 0x18);
                            }
                            goto LAB_1481b5276;
                          }
                          break;
                        }
                        iVar7 = (int)puVar8[2];
                      } while (iVar7 != -1);
                    }
                  }
                  if (2 < DAT_14ed60660) {
                    puVar9 = (undefined8 *)func_0x00014192e690(plVar1,alStack_48,0);
                    if (*(int *)(puVar9 + 1) == 0) {
                      puVar14 = &UNK_14bce4e94;
                    }
                    else {
                      puVar14 = (undefined *)*puVar9;
                    }
                    puVar9 = (undefined8 *)func_0x0001411de0e0(&uStackX_8,alStack_58);
                    if (*(int *)(puVar9 + 1) == 0) {
                      puVar15 = &UNK_14bce4e94;
                    }
                    else {
                      puVar15 = (undefined *)*puVar9;
                    }
                    func_0x000140f24ba0(&DAT_14ed60660,&UNK_14cf77658,&UNK_14bce4e94,puVar15,puVar14
                                       );
                    if (alStack_58[0] != 0) {
                      func_0x000140e282f0();
                    }
                    if (alStack_48[0] != 0) {
                      func_0x000140e282f0();
                    }
                  }
                }
                goto LAB_1481b5276;
              }
            }
            if (1 < DAT_14ed60660) {
              puVar9 = (undefined8 *)func_0x00014192e690(plVar1,alStack_38,0);
              if (*(int *)(puVar9 + 1) == 0) {
                puVar14 = &UNK_14bce4e94;
              }
              else {
                puVar14 = (undefined *)*puVar9;
              }
              func_0x000140f24ba0(&DAT_14ed60660,&UNK_14cf77618,&UNK_14bce4e94,puVar14);
              if (alStack_38[0] != 0) {
                func_0x000140e282f0();
              }
            }
          }
LAB_1481b5276:
          if (puStack_88 != (undefined *)0x0) {
            func_0x000140e282f0();
          }
        }
        iVar6 = func_0x0001481c32e0(param_1);
        iVar7 = *(int *)(param_1 + 0x40);
      } while (iVar6 <= iVar7);
    }
    func_0x0001481c32e0(param_1);
    func_0x000148155e60(param_1 + 0x390);
  }
  return;
}


/* Instruction evidence:
1481b4f10 MOV qword ptr [RSP + 0x20],RBX
1481b4f15 PUSH RBP
1481b4f16 PUSH RSI
1481b4f17 PUSH RDI
1481b4f18 PUSH R14
1481b4f1a PUSH R15
1481b4f1c SUB RSP,0x90
1481b4f23 MOV RSI,RCX
1481b4f26 XOR R15D,R15D
1481b4f29 CMP dword ptr [RCX + 0x50],0x14
1481b4f2d JGE 0x1481b52dd
1481b4f33 CALL 0x1481c32e0
1481b4f38 MOV EDX,dword ptr [RSI + 0x40]
1481b4f3b CMP EDX,EAX
1481b4f3d JL 0x1481b5299
1481b4f43 LEA RBP,[0x14bce4e94]
1481b4f4a NOP word ptr [RAX + RAX*0x1]
1481b4f50 MOV ECX,dword ptr [RSI + 0x50]
1481b4f53 CMP ECX,0x14
1481b4f56 JGE 0x1481b5299
1481b4f5c SUB EDX,EAX
1481b4f5e MOV dword ptr [RSI + 0x40],EDX
1481b4f61 LEA R8D,[RCX + 0x1]
1481b4f65 MOV dword ptr [RSI + 0x50],R8D
1481b4f69 CMP qword ptr [RSI + 0x68],0x0
1481b4f6e JZ 0x1481b5286
1481b4f74 LEA RDX,[0x14cf71488]
1481b4f7b LEA RCX,[RSP + 0x30]
1481b4f80 CALL 0x140d169d0
1481b4f85 NOP
1481b4f86 MOV R14,qword ptr [RSI + 0x68]
1481b4f8a MOV RDX,RBP
1481b4f8d CMP dword ptr [RSP + 0x38],0x0
1481b4f92 CMOVNZ RDX,qword ptr [RSP + 0x30]
1481b4f98 MOV R8D,0x1
1481b4f9e LEA RCX,[RSP + 0xd0]
1481b4fa6 CALL 0x1411a7b80
1481b4fab MOV RDX,qword ptr [RAX]
1481b4fae MOV qword ptr [RSP + 0xc0],RDX
1481b4fb6 MOV RBX,qword ptr [R14 + 0x28]
1481b4fba TEST RBX,RBX
1481b4fbd JNZ 0x1481b5016
1481b4fbf CMP byte ptr [0x14ed60660],0x2
1481b4fc6 JC 0x1481b5276
1481b4fcc XOR R8D,R8D
1481b4fcf LEA RDX,[RSP + 0x40]
1481b4fd4 MOV RCX,R14
1481b4fd7 CALL 0x14192e690
1481b4fdc NOP
1481b4fdd CMP dword ptr [RAX + 0x8],EBX
1481b4fe0 JZ 0x1481b4fe7
1481b4fe2 MOV R9,qword ptr [RAX]
1481b4fe5 JMP 0x1481b4fea
1481b4fe7 MOV R9,RBP
1481b4fea MOV R8,RBP
1481b4fed LEA RDX,[0x14cf775f8]
1481b4ff4 LEA RCX,[0x14ed60660]
1481b4ffb CALL 0x140f24ba0
1481b5000 NOP
1481b5001 MOV RCX,qword ptr [RSP + 0x40]
1481b5006 TEST RCX,RCX
1481b5009 JZ 0x1481b5011
1481b500b CALL 0x140e282f0
1481b5010 NOP
1481b5011 JMP 0x1481b5276
1481b5016 CALL 0x1481502d0
1481b501b TEST RAX,RAX
1481b501e JZ 0x1481b5221
1481b5024 LEA RDX,[RAX + 0x30]
1481b5028 MOVSXD RAX,dword ptr [RDX + 0x8]
1481b502c CMP EAX,dword ptr [RBX + 0x38]
1481b502f JG 0x1481b5221
1481b5035 MOV RCX,RAX
1481b5038 MOV RAX,qword ptr [RBX + 0x30]
1481b503c CMP qword ptr [RAX + RCX*0x8],RDX
1481b5040 JNZ 0x1481b5221
1481b5046 CMP qword ptr [RSP + 0xc0],0x0
1481b504f JNZ 0x1481b50a9
1481b5051 CMP byte ptr [0x14ed60660],0x3
1481b5058 JC 0x1481b5276
1481b505e XOR R8D,R8D
1481b5061 LEA RDX,[RSP + 0x50]
1481b5066 MOV RCX,R14
1481b5069 CALL 0x14192e690
1481b506e NOP
1481b506f CMP dword ptr [RAX + 0x8],0x0
1481b5073 JZ 0x1481b507a
1481b5075 MOV R9,qword ptr [RAX]
1481b5078 JMP 0x1481b507d
1481b507a MOV R9,RBP
1481b507d MOV R8,RBP
1481b5080 LEA RDX,[0x14cf77638]
1481b5087 LEA RCX,[0x14ed60660]
1481b508e CALL 0x140f24ba0
1481b5093 NOP
1481b5094 MOV RCX,qword ptr [RSP + 0x50]
1481b5099 TEST RCX,RCX
1481b509c JZ 0x1481b50a4
1481b509e CALL 0x140e282f0
1481b50a3 NOP
1481b50a4 JMP 0x1481b5276
1481b50a9 MOV RAX,qword ptr [R14]
1481b50ac MOV RCX,R14
1481b50af CALL qword ptr [RAX + 0x2d8]
1481b50b5 MOV RDI,RAX
1481b50b8 MOV RBX,qword ptr [RSP + 0xc0]
1481b50c0 MOV qword ptr [RSP + 0xc8],RBX
1481b50c8 MOV ECX,EBX
1481b50ca CALL 0x1411c2eb0
1481b50cf MOV R8D,dword ptr [RSP + 0xcc]
1481b50d7 ADD R8D,EAX
1481b50da MOV ECX,dword ptr [RDI + 0x8]
1481b50dd CMP ECX,dword ptr [RDI + 0x34]
1481b50e0 JZ 0x1481b5127
1481b50e2 LEA RDX,[RDI + 0x38]
1481b50e6 MOV RAX,qword ptr [RDX + 0x8]
1481b50ea TEST RAX,RAX
1481b50ed CMOVNZ RDX,RAX
1481b50f1 MOV ECX,dword ptr [RDI + 0x48]
1481b50f4 DEC ECX
1481b50f6 MOV EAX,R8D
1481b50f9 AND RCX,RAX
1481b50fc MOV EAX,dword ptr [RDX + RCX*0x4]
1481b50ff CMP EAX,-0x1
1481b5102 JZ 0x1481b5127
1481b5104 MOV RDX,qword ptr [RDI]
1481b5107 NOP word ptr [RAX + RAX*0x1]
1481b5110 CDQE
1481b5112 LEA RCX,[RAX + RAX*0x2]
1481b5116 LEA RAX,[RDX + RCX*0x8]
1481b511a CMP qword ptr [RAX],RBX
1481b511d JZ 0x1481b5150
1481b511f MOV EAX,dword ptr [RAX + 0x10]
1481b5122 CMP EAX,-0x1
1481b5125 JNZ 0x1481b5110
1481b5127 CMP byte ptr [0x14ed60660],0x3
1481b512e JC 0x1481b5276
1481b5134 XOR R8D,R8D
1481b5137 LEA RDX,[RSP + 0x70]
1481b513c MOV RCX,R14
1481b513f CALL 0x14192e690
1481b5144 NOP
1481b5145 CMP dword ptr [RAX + 0x8],0x0
1481b5149 JZ 0x1481b51bf
1481b514b MOV RBX,qword ptr [RAX]
1481b514e JMP 0x1481b51c2
1481b5150 LEA RCX,[RAX + 0x8]
1481b5154 TEST RAX,RAX
1481b5157 CMOVZ RCX,R15
1481b515b TEST RCX,RCX
1481b515e JZ 0x1481b5127
1481b5160 MOV RDX,qword ptr [RCX]
1481b5163 TEST RDX,RDX
1481b5166 JNZ 0x1481b519d
1481b5168 MOV R9,qword ptr [RSP + 0xb8]
1481b5170 MOV qword ptr [RSP + 0x20],RBP
1481b5175 MOV R8D,0xf5
1481b517b LEA RDX,[0x14cf2d4f0]
1481b5182 LEA RCX,[0x14c7689a0]
1481b5189 CALL 0x140f8dfd0
1481b518e TEST AL,AL
1481b5190 JZ 0x1481b5276
1481b5196 NOP
1481b5197 INT3
1481b519d MOV EAX,dword ptr [RDX + 0x10]
1481b51a0 ADD dword ptr [RSI + 0x58],EAX
1481b51a3 LEA RCX,[RSI + 0x348]
1481b51aa LEA R9,[RDX + 0x18]
1481b51ae MOV R8D,dword ptr [RDX + 0x10]
1481b51b2 MOV EDX,dword ptr [RSI + 0x50]
1481b51b5 CALL 0x148155dc0
1481b51ba JMP 0x1481b5276
1481b51bf MOV RBX,RBP
1481b51c2 LEA RDX,[RSP + 0x60]
1481b51c7 LEA RCX,[RSP + 0xc0]
1481b51cf CALL 0x1411de0e0
1481b51d4 NOP
1481b51d5 CMP dword ptr [RAX + 0x8],0x0
1481b51d9 JZ 0x1481b51e0
1481b51db MOV R9,qword ptr [RAX]
1481b51de JMP 0x1481b51e3
1481b51e0 MOV R9,RBP
1481b51e3 MOV qword ptr [RSP + 0x20],RBX
1481b51e8 MOV R8,RBP
1481b51eb LEA RDX,[0x14cf77658]
1481b51f2 LEA RCX,[0x14ed60660]
1481b51f9 CALL 0x140f24ba0
1481b51fe NOP
1481b51ff MOV RCX,qword ptr [RSP + 0x60]
1481b5204 TEST RCX,RCX
1481b5207 JZ 0x1481b520f
1481b5209 CALL 0x140e282f0
1481b520e NOP
1481b520f MOV RCX,qword ptr [RSP + 0x70]
1481b5214 TEST RCX,RCX
1481b5217 JZ 0x1481b521f
1481b5219 CALL 0x140e282f0
1481b521e NOP
1481b521f JMP 0x1481b5276
1481b5221 CMP byte ptr [0x14ed60660],0x2
1481b5228 JC 0x1481b5276
1481b522a XOR R8D,R8D
1481b522d LEA RDX,[RSP + 0x80]
1481b5235 MOV RCX,R14
1481b5238 CALL 0x14192e690
1481b523d NOP
1481b523e CMP dword ptr [RAX + 0x8],0x0
1481b5242 JZ 0x1481b5249
1481b5244 MOV R9,qword ptr [RAX]
1481b5247 JMP 0x1481b524c
1481b5249 MOV R9,RBP
1481b524c MOV R8,RBP
1481b524f LEA RDX,[0x14cf77618]
1481b5256 LEA RCX,[0x14ed60660]
1481b525d CALL 0x140f24ba0
1481b5262 NOP
1481b5263 MOV RCX,qword ptr [RSP + 0x80]
1481b526b TEST RCX,RCX
1481b526e JZ 0x1481b5276
1481b5270 CALL 0x140e282f0
1481b5275 NOP
1481b5276 MOV RCX,qword ptr [RSP + 0x30]
1481b527b TEST RCX,RCX
1481b527e JZ 0x1481b5286
1481b5280 CALL 0x140e282f0
1481b5285 NOP
1481b5286 MOV RCX,RSI
1481b5289 CALL 0x1481c32e0
1481b528e MOV EDX,dword ptr [RSI + 0x40]
1481b5291 CMP EDX,EAX
1481b5293 JGE 0x1481b4f50
1481b5299 MOV RCX,RSI
1481b529c CALL 0x1481c32e0
1481b52a1 TEST EAX,EAX
1481b52a3 JG 0x1481b52af
1481b52a5 MOVSS XMM1,dword ptr [0x14bcef9ec]
1481b52ad JMP 0x1481b52d1
1481b52af MOVD XMM1,dword ptr [RSI + 0x40]
1481b52b4 CVTDQ2PS XMM1,XMM1
1481b52b7 MOVD XMM0,EAX
1481b52bb CVTDQ2PS XMM0,XMM0
1481b52be DIVSS XMM1,XMM0
1481b52c2 MINSS XMM1,dword ptr [0x14bcef9ec]
1481b52ca XORPS XMM0,XMM0
1481b52cd MAXSS XMM1,XMM0
1481b52d1 LEA RCX,[RSI + 0x390]
1481b52d8 CALL 0x148155e60
1481b52dd MOV RBX,qword ptr [RSP + 0xd8]
1481b52e5 ADD RSP,0x90
1481b52ec POP R15
1481b52ee POP R14
1481b52f0 POP RDI
1481b52f1 POP RSI
1481b52f2 POP RBP
1481b52f3 RET
*/

/* 1481ca280 ResetProgress */

void ResetProgress(longlong param_1)

{
  longlong lVar1;
  bool bVar2;
  longlong *plVar3;
  int iVar4;
  longlong *plVar5;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  longlong *plStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x50) = 1;
  *(undefined4 *)(param_1 + 0x58) = 0;
  lVar1 = param_1 + 0xa0;
  if (*(int *)(param_1 + 0xe8) < 2) {
    func_0x0001481cca20(lVar1);
    func_0x000148155670(lVar1,0);
  }
  else {
    func_0x000148155670(lVar1,0);
    *(undefined4 *)(param_1 + 0xe8) = 1;
    func_0x0001481c9190(lVar1);
  }
  lVar1 = param_1 + 0xf0;
  if (*(int *)(param_1 + 0x138) < 2) {
    func_0x0001481cca20(lVar1);
    func_0x000148155670(lVar1,0);
  }
  else {
    func_0x000148155670(lVar1,0);
    *(undefined4 *)(param_1 + 0x138) = 1;
    func_0x0001481c9190(lVar1);
  }
  lVar1 = param_1 + 0x140;
  bVar2 = *(int *)(param_1 + 0x188) < 2;
  if (bVar2) {
    func_0x000140fc6930(lVar1);
  }
  *(undefined4 *)(param_1 + 0x148) = 0;
  if (*(int *)(param_1 + 0x14c) != 0) {
    func_0x000140d239b0(lVar1,0);
  }
  *(undefined4 *)(param_1 + 0x170) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x174) = 0;
  *(undefined4 *)(param_1 + 0x168) = 0;
  if (0x80 < *(uint *)(param_1 + 0x16c)) {
    *(undefined4 *)(param_1 + 0x16c) = 0x80;
    func_0x000140d182e0(param_1 + 0x150,0);
  }
  if (!bVar2) {
    *(undefined4 *)(param_1 + 0x188) = 1;
    func_0x000140d1afe0(lVar1);
  }
  uStack_98 = 0;
  uStack_90 = 0;
  uStack_88 = 0;
  uStack_80 = 0;
  uStack_78 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_60 = 0;
  plStack_58 = (longlong *)0x0;
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_40 = 0;
  uStack_38 = 0;
  uStack_30 = 0;
  uStack_28 = 0;
  uStack_20 = 0;
  func_0x0001481537f0(param_1 + 0x2b0,&uStack_98);
  plVar3 = plStack_58;
  plVar5 = plStack_58;
  for (iVar4 = (int)uStack_50; iVar4 != 0; iVar4 = iVar4 + -1) {
    if (*plVar5 != 0) {
      func_0x000140e282f0();
    }
    plVar5 = plVar5 + 2;
  }
  if (plVar3 != (longlong *)0x0) {
    func_0x000140e282f0(plVar3);
  }
  uStack_98 = 0;
  uStack_90 = 0;
  uStack_88 = 0;
  uStack_80 = 0;
  uStack_78 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_60 = 0;
  plStack_58 = (longlong *)0x0;
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_40 = 0;
  uStack_38 = 0;
  uStack_30 = 0;
  uStack_28 = 0;
  uStack_20 = 0;
  func_0x0001481537f0(param_1 + 0x230,&uStack_98);
  plVar3 = plStack_58;
  plVar5 = plStack_58;
  for (iVar4 = (int)uStack_50; iVar4 != 0; iVar4 = iVar4 + -1) {
    if (*plVar5 != 0) {
      func_0x000140e282f0();
    }
    plVar5 = plVar5 + 2;
  }
  if (plVar3 != (longlong *)0x0) {
    func_0x000140e282f0(plVar3);
  }
  lVar1 = param_1 + 400;
  bVar2 = *(int *)(param_1 + 0x1d8) < 2;
  if (bVar2) {
    func_0x0001481ccd80(lVar1);
  }
  *(undefined4 *)(param_1 + 0x198) = 0;
  if (*(int *)(param_1 + 0x19c) != 0) {
    func_0x000140d239b0(lVar1,0);
  }
  *(undefined4 *)(param_1 + 0x1c0) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1c4) = 0;
  *(undefined4 *)(param_1 + 0x1b8) = 0;
  if (0x80 < *(uint *)(param_1 + 0x1bc)) {
    *(undefined4 *)(param_1 + 0x1bc) = 0x80;
    func_0x000140d182e0(param_1 + 0x1a0,0);
  }
  if (!bVar2) {
    *(undefined4 *)(param_1 + 0x1d8) = 1;
    func_0x0001481c9400(lVar1);
  }
  *(undefined4 *)(param_1 + 0x340) = 0;
  if (*(int *)(param_1 + 0x344) != 0) {
    func_0x000140d24320(param_1 + 0x338,0);
  }
  lVar1 = param_1 + 0x400;
  bVar2 = *(int *)(param_1 + 0x448) < 2;
  if (bVar2) {
    func_0x000140fc6930(lVar1);
  }
  *(undefined4 *)(param_1 + 0x408) = 0;
  if (*(int *)(param_1 + 0x40c) != 0) {
    func_0x000140d239b0(lVar1,0);
  }
  *(undefined4 *)(param_1 + 0x430) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x434) = 0;
  *(undefined4 *)(param_1 + 0x428) = 0;
  if (0x80 < *(uint *)(param_1 + 0x42c)) {
    *(undefined4 *)(param_1 + 0x42c) = 0x80;
    func_0x000140d182e0(param_1 + 0x410,0);
  }
  if (!bVar2) {
    *(undefined4 *)(param_1 + 0x448) = 1;
    func_0x000140d1afe0(lVar1);
  }
  *(undefined8 *)(param_1 + 0x4a8) = 0;
  lVar1 = param_1 + 0x458;
  bVar2 = *(int *)(param_1 + 0x4a0) < 2;
  if (bVar2) {
    func_0x000140fc6930(lVar1);
  }
  *(undefined4 *)(param_1 + 0x460) = 0;
  if (*(int *)(param_1 + 0x464) != 0) {
    func_0x000140d239b0(lVar1,0);
  }
  *(undefined4 *)(param_1 + 0x488) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x48c) = 0;
  *(undefined4 *)(param_1 + 0x480) = 0;
  if (0x80 < *(uint *)(param_1 + 0x484)) {
    *(undefined4 *)(param_1 + 0x484) = 0x80;
    func_0x000140d182e0(param_1 + 0x468,0);
  }
  if (!bVar2) {
    *(undefined4 *)(param_1 + 0x4a0) = 1;
    func_0x000140d1afe0(lVar1);
  }
  func_0x0001481c4080(param_1);
  func_0x0001481cad00(param_1);
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71fa8);
  }
  return;
}


/* Instruction evidence:
1481ca280 MOV qword ptr [RSP + 0x10],RBX
1481ca285 MOV qword ptr [RSP + 0x18],RSI
1481ca28a MOV qword ptr [RSP + 0x20],RDI
1481ca28f PUSH RBP
1481ca290 PUSH R14
1481ca292 PUSH R15
1481ca294 LEA RBP,[RSP + -0x47]
1481ca299 SUB RSP,0xa0
1481ca2a0 MOV RBX,RCX
1481ca2a3 XOR R15D,R15D
1481ca2a6 MOV dword ptr [RCX + 0x40],R15D
1481ca2aa MOV qword ptr [RCX + 0x50],0x1
1481ca2b2 MOV dword ptr [RCX + 0x58],R15D
1481ca2b6 LEA RDI,[RCX + 0xa0]
1481ca2bd MOV RCX,RDI
1481ca2c0 CMP dword ptr [RDI + 0x48],0x1
1481ca2c4 JLE 0x1481ca2de
1481ca2c6 XOR EDX,EDX
1481ca2c8 CALL 0x148155670
1481ca2cd MOV dword ptr [RDI + 0x48],0x1
1481ca2d4 MOV RCX,RDI
1481ca2d7 CALL 0x1481c9190
1481ca2dc JMP 0x1481ca2ed
1481ca2de CALL 0x1481cca20
1481ca2e3 XOR EDX,EDX
1481ca2e5 MOV RCX,RDI
1481ca2e8 CALL 0x148155670
1481ca2ed LEA RDI,[RBX + 0xf0]
1481ca2f4 MOV RCX,RDI
1481ca2f7 CMP dword ptr [RDI + 0x48],0x1
1481ca2fb JLE 0x1481ca315
1481ca2fd XOR EDX,EDX
1481ca2ff CALL 0x148155670
1481ca304 MOV dword ptr [RDI + 0x48],0x1
1481ca30b MOV RCX,RDI
1481ca30e CALL 0x1481c9190
1481ca313 JMP 0x1481ca324
1481ca315 CALL 0x1481cca20
1481ca31a XOR EDX,EDX
1481ca31c MOV RCX,RDI
1481ca31f CALL 0x148155670
1481ca324 LEA RDI,[RBX + 0x140]
1481ca32b CMP dword ptr [RDI + 0x48],0x1
1481ca32f JLE 0x1481ca336
1481ca331 MOV SIL,0x1
1481ca334 JMP 0x1481ca341
1481ca336 XOR SIL,SIL
1481ca339 MOV RCX,RDI
1481ca33c CALL 0x140fc6930
1481ca341 MOV dword ptr [RDI + 0x8],R15D
1481ca345 CMP dword ptr [RDI + 0xc],R15D
1481ca349 JZ 0x1481ca355
1481ca34b XOR EDX,EDX
1481ca34d MOV RCX,RDI
1481ca350 CALL 0x140d239b0
1481ca355 MOV dword ptr [RDI + 0x30],0xffffffff
1481ca35c MOV dword ptr [RDI + 0x34],R15D
1481ca360 LEA RCX,[RDI + 0x10]
1481ca364 MOV dword ptr [RCX + 0x18],R15D
1481ca368 CMP dword ptr [RCX + 0x1c],0x80
1481ca36f JBE 0x1481ca37f
1481ca371 MOV dword ptr [RCX + 0x1c],0x80
1481ca378 XOR EDX,EDX
1481ca37a CALL 0x140d182e0
1481ca37f TEST SIL,SIL
1481ca382 JZ 0x1481ca393
1481ca384 MOV dword ptr [RDI + 0x48],0x1
1481ca38b MOV RCX,RDI
1481ca38e CALL 0x140d1afe0
1481ca393 XORPS XMM0,XMM0
1481ca396 MOVUPS xmmword ptr [RBP + -0x19],XMM0
1481ca39a MOVUPS xmmword ptr [RBP + -0x9],XMM0
1481ca39e MOVUPS xmmword ptr [RBP + 0x7],XMM0
1481ca3a2 MOVUPS xmmword ptr [RBP + 0x17],XMM0
1481ca3a6 MOVUPS xmmword ptr [RBP + 0x27],XMM0
1481ca3aa MOVUPS xmmword ptr [RBP + 0x37],XMM0
1481ca3ae MOVDQU xmmword ptr [RBP + -0x39],XMM0
1481ca3b3 XORPS XMM1,XMM1
1481ca3b6 MOVDQU xmmword ptr [RBP + -0x29],XMM1
1481ca3bb MOV qword ptr [RBP + -0x19],R15
1481ca3bf MOV dword ptr [RBP + -0x11],R15D
1481ca3c3 MOV word ptr [RBP + -0xd],R15W
1481ca3c8 MOV qword ptr [RBP + -0x9],R15
1481ca3cc MOV dword ptr [RBP + -0x1],R15D
1481ca3d0 MOV qword ptr [RBP + 0x7],R15
1481ca3d4 MOVDQU xmmword ptr [RBP + 0xf],XMM0
1481ca3d9 MOVDQU xmmword ptr [RBP + 0x1f],XMM1
1481ca3de MOVDQU xmmword ptr [RBP + 0x2f],XMM0
1481ca3e3 MOV dword ptr [RBP + 0x3f],R15D
1481ca3e7 LEA RCX,[RBX + 0x2b0]
1481ca3ee LEA RDX,[RBP + -0x39]
1481ca3f2 CALL 0x1481537f0
1481ca3f7 NOP
1481ca3f8 MOV ESI,dword ptr [RBP + 0xf]
1481ca3fb MOV R14,qword ptr [RBP + 0x7]
1481ca3ff MOV RDI,R14
1481ca402 TEST ESI,ESI
1481ca404 JZ 0x1481ca41d
1481ca406 MOV RCX,qword ptr [RDI]
1481ca409 TEST RCX,RCX
1481ca40c JZ 0x1481ca414
1481ca40e CALL 0x140e282f0
1481ca413 NOP
1481ca414 ADD RDI,0x10
1481ca418 SUB ESI,0x1
1481ca41b JNZ 0x1481ca406
1481ca41d TEST R14,R14
1481ca420 JZ 0x1481ca42b
1481ca422 MOV RCX,R14
1481ca425 CALL 0x140e282f0
1481ca42a NOP
1481ca42b XORPS XMM0,XMM0
1481ca42e MOVUPS xmmword ptr [RBP + -0x19],XMM0
1481ca432 MOVUPS xmmword ptr [RBP + -0x9],XMM0
1481ca436 MOVUPS xmmword ptr [RBP + 0x7],XMM0
1481ca43a MOVUPS xmmword ptr [RBP + 0x17],XMM0
1481ca43e MOVUPS xmmword ptr [RBP + 0x27],XMM0
1481ca442 MOVUPS xmmword ptr [RBP + 0x37],XMM0
1481ca446 MOVDQU xmmword ptr [RBP + -0x39],XMM0
1481ca44b XORPS XMM1,XMM1
1481ca44e MOVDQU xmmword ptr [RBP + -0x29],XMM1
1481ca453 MOV qword ptr [RBP + -0x19],R15
1481ca457 MOV dword ptr [RBP + -0x11],R15D
1481ca45b MOV word ptr [RBP + -0xd],0x0
1481ca461 MOV qword ptr [RBP + -0x9],R15
1481ca465 MOV dword ptr [RBP + -0x1],R15D
1481ca469 MOV qword ptr [RBP + 0x7],R15
1481ca46d MOVDQU xmmword ptr [RBP + 0xf],XMM0
1481ca472 MOVDQU xmmword ptr [RBP + 0x1f],XMM1
1481ca477 MOVDQU xmmword ptr [RBP + 0x2f],XMM0
1481ca47c MOV dword ptr [RBP + 0x3f],R15D
1481ca480 LEA RCX,[RBX + 0x230]
1481ca487 LEA RDX,[RBP + -0x39]
1481ca48b CALL 0x1481537f0
1481ca490 NOP
1481ca491 MOV ESI,dword ptr [RBP + 0xf]
1481ca494 MOV R14,qword ptr [RBP + 0x7]
1481ca498 MOV RDI,R14
1481ca49b TEST ESI,ESI
1481ca49d JZ 0x1481ca4b7
1481ca49f NOP
1481ca4a0 MOV RCX,qword ptr [RDI]
1481ca4a3 TEST RCX,RCX
1481ca4a6 JZ 0x1481ca4ae
1481ca4a8 CALL 0x140e282f0
1481ca4ad NOP
1481ca4ae ADD RDI,0x10
1481ca4b2 SUB ESI,0x1
1481ca4b5 JNZ 0x1481ca4a0
1481ca4b7 TEST R14,R14
1481ca4ba JZ 0x1481ca4c5
1481ca4bc MOV RCX,R14
1481ca4bf CALL 0x140e282f0
1481ca4c4 NOP
1481ca4c5 LEA RDI,[RBX + 0x190]
1481ca4cc CMP dword ptr [RDI + 0x48],0x1
1481ca4d0 JLE 0x1481ca4d7
1481ca4d2 MOV SIL,0x1
1481ca4d5 JMP 0x1481ca4e2
1481ca4d7 XOR SIL,SIL
1481ca4da MOV RCX,RDI
1481ca4dd CALL 0x1481ccd80
1481ca4e2 MOV dword ptr [RDI + 0x8],R15D
1481ca4e6 CMP dword ptr [RDI + 0xc],0x0
1481ca4ea JZ 0x1481ca4f6
1481ca4ec XOR EDX,EDX
1481ca4ee MOV RCX,RDI
1481ca4f1 CALL 0x140d239b0
1481ca4f6 MOV dword ptr [RDI + 0x30],0xffffffff
1481ca4fd MOV dword ptr [RDI + 0x34],R15D
1481ca501 LEA RCX,[RDI + 0x10]
1481ca505 MOV dword ptr [RCX + 0x18],R15D
1481ca509 CMP dword ptr [RCX + 0x1c],0x80
1481ca510 JBE 0x1481ca520
1481ca512 MOV dword ptr [RCX + 0x1c],0x80
1481ca519 XOR EDX,EDX
1481ca51b CALL 0x140d182e0
1481ca520 TEST SIL,SIL
1481ca523 JZ 0x1481ca534
1481ca525 MOV dword ptr [RDI + 0x48],0x1
1481ca52c MOV RCX,RDI
1481ca52f CALL 0x1481c9400
1481ca534 LEA RCX,[RBX + 0x338]
1481ca53b MOV dword ptr [RCX + 0x8],R15D
1481ca53f CMP dword ptr [RCX + 0xc],0x0
1481ca543 JZ 0x1481ca54c
1481ca545 XOR EDX,EDX
1481ca547 CALL 0x140d24320
1481ca54c LEA RDI,[RBX + 0x400]
1481ca553 CMP dword ptr [RDI + 0x48],0x1
1481ca557 JLE 0x1481ca55e
1481ca559 MOV SIL,0x1
1481ca55c JMP 0x1481ca569
1481ca55e XOR SIL,SIL
1481ca561 MOV RCX,RDI
1481ca564 CALL 0x140fc6930
1481ca569 MOV dword ptr [RDI + 0x8],R15D
1481ca56d CMP dword ptr [RDI + 0xc],0x0
1481ca571 JZ 0x1481ca57d
1481ca573 XOR EDX,EDX
1481ca575 MOV RCX,RDI
1481ca578 CALL 0x140d239b0
1481ca57d MOV dword ptr [RDI + 0x30],0xffffffff
1481ca584 MOV dword ptr [RDI + 0x34],R15D
1481ca588 LEA RCX,[RDI + 0x10]
1481ca58c MOV dword ptr [RCX + 0x18],R15D
1481ca590 CMP dword ptr [RCX + 0x1c],0x80
1481ca597 JBE 0x1481ca5a7
1481ca599 MOV dword ptr [RCX + 0x1c],0x80
1481ca5a0 XOR EDX,EDX
1481ca5a2 CALL 0x140d182e0
1481ca5a7 TEST SIL,SIL
1481ca5aa JZ 0x1481ca5bb
1481ca5ac MOV dword ptr [RDI + 0x48],0x1
1481ca5b3 MOV RCX,RDI
1481ca5b6 CALL 0x140d1afe0
1481ca5bb MOV qword ptr [RBP + 0x67],R15
1481ca5bf MOV RAX,R15
1481ca5c2 MOV qword ptr [RBX + 0x4a8],RAX
1481ca5c9 LEA RDI,[RBX + 0x458]
1481ca5d0 CMP dword ptr [RDI + 0x48],0x1
1481ca5d4 JLE 0x1481ca5db
1481ca5d6 MOV SIL,0x1
1481ca5d9 JMP 0x1481ca5e6
1481ca5db XOR SIL,SIL
1481ca5de MOV RCX,RDI
1481ca5e1 CALL 0x140fc6930
1481ca5e6 MOV dword ptr [RDI + 0x8],R15D
1481ca5ea CMP dword ptr [RDI + 0xc],0x0
1481ca5ee JZ 0x1481ca5fa
1481ca5f0 XOR EDX,EDX
1481ca5f2 MOV RCX,RDI
1481ca5f5 CALL 0x140d239b0
1481ca5fa MOV dword ptr [RDI + 0x30],0xffffffff
1481ca601 MOV dword ptr [RDI + 0x34],R15D
1481ca605 LEA RCX,[RDI + 0x10]
1481ca609 MOV dword ptr [RCX + 0x18],R15D
1481ca60d CMP dword ptr [RCX + 0x1c],0x80
1481ca614 JBE 0x1481ca624
1481ca616 MOV dword ptr [RCX + 0x1c],0x80
1481ca61d XOR EDX,EDX
1481ca61f CALL 0x140d182e0
1481ca624 TEST SIL,SIL
1481ca627 JZ 0x1481ca638
1481ca629 MOV dword ptr [RDI + 0x48],0x1
1481ca630 MOV RCX,RDI
1481ca633 CALL 0x140d1afe0
1481ca638 MOV RCX,RBX
1481ca63b CALL 0x1481c4080
1481ca640 MOV RCX,RBX
1481ca643 CALL 0x1481cad00
1481ca648 CMP byte ptr [0x14eab53c8],0x3
1481ca64f JC 0x1481ca664
1481ca651 LEA RDX,[0x14cf71fa8]
1481ca658 LEA RCX,[0x14eab53c8]
1481ca65f CALL 0x140f24ba0
1481ca664 LEA R11,[RSP + 0xa0]
1481ca66c MOV RBX,qword ptr [R11 + 0x28]
1481ca670 MOV RSI,qword ptr [R11 + 0x30]
1481ca674 MOV RDI,qword ptr [R11 + 0x38]
1481ca678 MOV RSP,R11
1481ca67b POP R15
1481ca67d POP R14
1481ca67f POP RBP
1481ca680 RET
*/
