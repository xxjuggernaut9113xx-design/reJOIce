
/* 1481a0db0 AnalyzeCalibrationResults */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void AnalyzeCalibrationResults(longlong param_1)

{
  float *pfVar1;
  float fVar2;
  code *pcVar3;
  uint uVar4;
  int iVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;
  float *pfVar9;
  longlong lVar10;
  ulonglong uVar11;
  ulonglong uVar12;
  ulonglong uVar13;
  ulonglong uVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  undefined8 unaff_retaddr;
  undefined1 auStackX_8 [8];
  uint uStackX_10;
  float afStack_b8 [2];
  float *pfStack_b0;
  undefined8 uStack_a8;
  
  if (*(int *)(param_1 + 0x3c8) < *(int *)(param_1 + 0x360)) {
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65888);
    }
  }
  else {
    uVar14 = 0;
    pfStack_b0 = (float *)0x0;
    uStack_a8 = 0;
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65938);
    }
    uVar4 = _DAT_14bd17880;
    fVar19 = _DAT_14bd17870;
    uStackX_10 = 0;
    uVar13 = uVar14;
    uVar11 = uVar14;
    if (0 < *(int *)(param_1 + 0x3c8)) {
      do {
        uVar8 = (uint)uVar11;
        uVar7 = 0;
        if ((int)uVar8 < *(int *)(param_1 + 0x3c8)) {
          uVar7 = ~uVar8 >> 0x1f;
        }
        if ((uVar7 == 0) &&
           (cVar6 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                        &UNK_14bce6ef0,(longlong)(int)uVar8,
                                        (longlong)*(int *)(param_1 + 0x3c8)), cVar6 != '\0')) {
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        fVar2 = *(float *)(uVar13 + *(longlong *)(param_1 + 0x3c0));
        if ((*(int *)(param_1 + 0x3d8) < 1) &&
           (cVar6 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                        &UNK_14bce6ef0,0,(longlong)*(int *)(param_1 + 0x3d8)),
           cVar6 != '\0')) {
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        fVar20 = (float)**(double **)(param_1 + 0x3d0);
        uVar8 = 1;
        uVar7 = 0;
        if (1 < *(int *)(param_1 + 0x3d8)) {
          lVar10 = 8;
          uVar11 = uVar14;
          fVar18 = (float)((uint)(fVar2 - fVar20) & uVar4);
          do {
            uVar7 = 0;
            if ((int)uVar8 < *(int *)(param_1 + 0x3d8)) {
              uVar7 = ~uVar8 >> 0x1f;
            }
            if ((uVar7 == 0) &&
               (cVar6 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                            &UNK_14bce6ef0,(longlong)(int)uVar8,
                                            (longlong)*(int *)(param_1 + 0x3d8)), cVar6 != '\0')) {
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            fVar16 = (float)*(double *)(*(longlong *)(param_1 + 0x3d0) + lVar10);
            fVar15 = (float)((uint)(fVar2 - fVar16) & uVar4);
            fVar17 = fVar18;
            if (fVar15 < fVar18) {
              fVar17 = fVar15;
              fVar20 = fVar16;
            }
            uVar12 = (ulonglong)uVar8;
            if (fVar18 <= fVar15) {
              uVar12 = uVar11;
            }
            uVar7 = (uint)uVar12;
            uVar8 = uVar8 + 1;
            lVar10 = lVar10 + 8;
            uVar11 = uVar12;
            fVar18 = fVar17;
          } while ((int)uVar8 < *(int *)(param_1 + 0x3d8));
          uVar11 = (ulonglong)uStackX_10;
        }
        fVar18 = (fVar2 - fVar20) * fVar19;
        afStack_b8[0] = fVar18;
        if (pfStack_b0 <= afStack_b8) {
          if (afStack_b8 < pfStack_b0 + (int)uStack_a8._4_4_) {
            cVar6 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                        &UNK_14bce6d80,afStack_b8,pfStack_b0,
                                        (longlong)(int)uStack_a8._4_4_,(longlong)(int)uStack_a8,4);
            if (cVar6 != '\0') {
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
          }
        }
        uVar12 = uStack_a8;
        lVar10 = (longlong)(int)uStack_a8;
        uVar8 = (int)uStack_a8 + 1;
        uStack_a8 = CONCAT44(uStack_a8._4_4_,uVar8);
        if (uStack_a8._4_4_ < uVar8) {
          func_0x000140d215e0(&pfStack_b0,uVar12 & 0xffffffff);
        }
        pfStack_b0[lVar10] = afStack_b8[0];
        if (1 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf659a8,uVar11,(double)fVar2,uVar7,
                              (double)fVar20,(double)fVar18);
        }
        uStackX_10 = (int)uVar11 + 1;
        uVar13 = uVar13 + 4;
        uVar11 = (ulonglong)uStackX_10;
      } while ((int)uStackX_10 < *(int *)(param_1 + 0x3c8));
    }
    fVar19 = 0.0;
    iVar5 = (int)uStack_a8;
    pfVar1 = pfStack_b0 + (int)uStack_a8;
    pfVar9 = pfStack_b0;
    while( true ) {
      if ((int)uStack_a8 != iVar5) {
        auStackX_8[0] = 0;
        cVar6 = func_0x00014bb28c50(auStackX_8);
        if (cVar6 != '\0') {
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
      }
      if (pfVar9 == pfVar1) break;
      fVar19 = fVar19 + *pfVar9;
      pfVar9 = pfVar9 + 1;
    }
    *(float *)(param_1 + 0x328) = fVar19 / (float)(int)uStack_a8;
    if (2 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65a20,(double)(fVar19 / (float)(int)uStack_a8));
    }
    if (pfStack_b0 != (float *)0x0) {
      func_0x000140e282f0();
    }
  }
  return;
}


/* Instruction evidence:
1481a0db0 MOV RAX,RSP
1481a0db3 MOV qword ptr [RAX + 0x18],RBX
1481a0db7 PUSH RBP
1481a0db8 PUSH RSI
1481a0db9 PUSH RDI
1481a0dba PUSH R12
1481a0dbc PUSH R13
1481a0dbe PUSH R14
1481a0dc0 PUSH R15
1481a0dc2 SUB RSP,0xd0
1481a0dc9 MOVAPS xmmword ptr [RAX + -0x48],XMM6
1481a0dcd MOVAPS xmmword ptr [RAX + -0x58],XMM7
1481a0dd1 MOVAPS xmmword ptr [RAX + -0x68],XMM8
1481a0dd6 MOVAPS xmmword ptr [RAX + -0x78],XMM9
1481a0ddb MOVAPS xmmword ptr [RAX + -0x88],XMM10
1481a0de3 MOVAPS xmmword ptr [RSP + 0x70],XMM11
1481a0de9 MOV RSI,RCX
1481a0dec MOV R8D,dword ptr [RCX + 0x3c8]
1481a0df3 CMP R8D,dword ptr [RCX + 0x360]
1481a0dfa JGE 0x1481a0e21
1481a0dfc CMP byte ptr [0x14eab53c8],0x2
1481a0e03 JC 0x1481a11df
1481a0e09 LEA RDX,[0x14cf65888]
1481a0e10 LEA RCX,[0x14eab53c8]
1481a0e17 CALL 0x140f24ba0
1481a0e1c JMP 0x1481a11df
1481a0e21 XOR R13D,R13D
1481a0e24 MOV qword ptr [RSP + 0x58],R13
1481a0e29 MOV qword ptr [RSP + 0x60],R13
1481a0e2e CMP byte ptr [0x14eab53c8],0x2
1481a0e35 JC 0x1481a0e4a
1481a0e37 LEA RDX,[0x14cf65938]
1481a0e3e LEA RCX,[0x14eab53c8]
1481a0e45 CALL 0x140f24ba0
1481a0e4a MOV R15D,R13D
1481a0e4d MOV dword ptr [RSP + 0x118],R13D
1481a0e55 CMP dword ptr [RSI + 0x3c8],R13D
1481a0e5c JLE 0x1481a1150
1481a0e62 MOV R12,R13
1481a0e65 LEA R8,[0x14bce6ef0]
1481a0e6c LEA RBP,[0x14bce6d80]
1481a0e73 MOVSS XMM10,dword ptr [0x14bd17880]
1481a0e7c MOVSS XMM11,dword ptr [0x14bd17870]
1481a0e85 NOP word ptr [RAX + RAX*0x1]
1481a0e90 MOVSXD RDX,dword ptr [RSI + 0x3c8]
1481a0e97 MOV ECX,R15D
1481a0e9a NOT ECX
1481a0e9c SHR ECX,0x1f
1481a0e9f MOV EAX,R13D
1481a0ea2 CMP R15D,EDX
1481a0ea5 CMOVL EAX,ECX
1481a0ea8 TEST EAX,EAX
1481a0eaa JNZ 0x1481a0eec
1481a0eac MOVSXD RCX,R15D
1481a0eaf MOV R9,qword ptr [RSP + 0x108]
1481a0eb7 MOV qword ptr [RSP + 0x30],RDX
1481a0ebc MOV qword ptr [RSP + 0x28],RCX
1481a0ec1 MOV qword ptr [RSP + 0x20],R8
1481a0ec6 MOV R8D,0x303
1481a0ecc LEA RDX,[0x14cf27ac0]
1481a0ed3 LEA RCX,[0x14bce6f68]
1481a0eda CALL 0x140f8dfd0
1481a0edf TEST AL,AL
1481a0ee1 JZ 0x1481a0ee5
1481a0ee3 NOP
1481a0ee4 INT3
1481a0ee5 LEA R8,[0x14bce6ef0]
1481a0eec MOV RAX,qword ptr [RSI + 0x3c0]
1481a0ef3 MOVSS XMM9,dword ptr [R12 + RAX*0x1]
1481a0ef9 MOVSXD RAX,dword ptr [RSI + 0x3d8]
1481a0f00 TEST EAX,EAX
1481a0f02 JG 0x1481a0f3a
1481a0f04 MOV R9,qword ptr [RSP + 0x108]
1481a0f0c MOV qword ptr [RSP + 0x30],RAX
1481a0f11 MOV qword ptr [RSP + 0x28],R13
1481a0f16 MOV qword ptr [RSP + 0x20],R8
1481a0f1b MOV R8D,0x303
1481a0f21 LEA RDX,[0x14cf27ac0]
1481a0f28 LEA RCX,[0x14bce6f68]
1481a0f2f CALL 0x140f8dfd0
1481a0f34 TEST AL,AL
1481a0f36 JZ 0x1481a0f3a
1481a0f38 NOP
1481a0f39 INT3
1481a0f3a MOV RAX,qword ptr [RSI + 0x3d0]
1481a0f41 MOVSD XMM8,qword ptr [RAX]
1481a0f46 CVTPD2PS XMM8,XMM8
1481a0f4b MOVAPS XMM6,XMM9
1481a0f4f SUBSS XMM6,XMM8
1481a0f54 ANDPS XMM6,XMM10
1481a0f58 MOV EDI,R13D
1481a0f5b MOV EBX,0x1
1481a0f60 CMP dword ptr [RSI + 0x3d8],EBX
1481a0f66 JLE 0x1481a102b
1481a0f6c LEA EBP,[RBX + 0x7]
1481a0f6f LEA R15,[0x14bce6ef0]
1481a0f76 NOP dword ptr [RAX + RAX*0x1]
1481a0f80 MOV R14D,EDI
1481a0f83 MOVAPS XMM7,XMM6
1481a0f86 MOVSXD RDX,dword ptr [RSI + 0x3d8]
1481a0f8d MOV ECX,EBX
1481a0f8f NOT ECX
1481a0f91 SHR ECX,0x1f
1481a0f94 MOV EAX,R13D
1481a0f97 CMP EBX,EDX
1481a0f99 CMOVL EAX,ECX
1481a0f9c TEST EAX,EAX
1481a0f9e JNZ 0x1481a0fd9
1481a0fa0 MOVSXD RCX,EBX
1481a0fa3 MOV R9,qword ptr [RSP + 0x108]
1481a0fab MOV qword ptr [RSP + 0x30],RDX
1481a0fb0 MOV qword ptr [RSP + 0x28],RCX
1481a0fb5 MOV qword ptr [RSP + 0x20],R15
1481a0fba MOV R8D,0x303
1481a0fc0 LEA RDX,[0x14cf27ac0]
1481a0fc7 LEA RCX,[0x14bce6f68]
1481a0fce CALL 0x140f8dfd0
1481a0fd3 TEST AL,AL
1481a0fd5 JZ 0x1481a0fd9
1481a0fd7 NOP
1481a0fd8 INT3
1481a0fd9 MOV RAX,qword ptr [RSI + 0x3d0]
1481a0fe0 MOVSD XMM1,qword ptr [RAX + RBP*0x1]
1481a0fe5 CVTPD2PS XMM1,XMM1
1481a0fe9 MOVAPS XMM0,XMM9
1481a0fed SUBSS XMM0,XMM1
1481a0ff1 ANDPS XMM0,XMM10
1481a0ff5 COMISS XMM0,XMM6
1481a0ff8 JNC 0x1481a1001
1481a0ffa MOVAPS XMM6,XMM0
1481a0ffd MOVAPS XMM8,XMM1
1481a1001 MOV EDI,EBX
1481a1003 COMISS XMM7,XMM0
1481a1006 CMOVBE EDI,R14D
1481a100a INC EBX
1481a100c ADD RBP,0x8
1481a1010 CMP EBX,dword ptr [RSI + 0x3d8]
1481a1016 JL 0x1481a0f80
1481a101c MOV R15D,dword ptr [RSP + 0x118]
1481a1024 LEA RBP,[0x14bce6d80]
1481a102b MOVAPS XMM6,XMM9
1481a102f SUBSS XMM6,XMM8
1481a1034 MULSS XMM6,XMM11
1481a1039 MOVSS dword ptr [RSP + 0x50],XMM6
1481a103f LEA RAX,[RSP + 0x50]
1481a1044 MOV RCX,qword ptr [RSP + 0x58]
1481a1049 CMP RAX,RCX
1481a104c JC 0x1481a10b4
1481a104e MOVSXD RDX,dword ptr [RSP + 0x64]
1481a1053 LEA RAX,[RCX + RDX*0x4]
1481a1057 LEA R8,[RSP + 0x50]
1481a105c CMP R8,RAX
1481a105f JNC 0x1481a10b4
1481a1061 MOVSXD RAX,dword ptr [RSP + 0x60]
1481a1066 MOV R9,qword ptr [RSP + 0x108]
1481a106e MOV qword ptr [RSP + 0x48],0x4
1481a1077 MOV qword ptr [RSP + 0x40],RAX
1481a107c MOV qword ptr [RSP + 0x38],RDX
1481a1081 MOV qword ptr [RSP + 0x30],RCX
1481a1086 LEA RAX,[RSP + 0x50]
1481a108b MOV qword ptr [RSP + 0x28],RAX
1481a1090 MOV qword ptr [RSP + 0x20],RBP
1481a1095 MOV R8D,0x63e
1481a109b LEA RDX,[0x14cf27ac0]
1481a10a2 LEA RCX,[0x14bce6eb8]
1481a10a9 CALL 0x140f8dfd0
1481a10ae TEST AL,AL
1481a10b0 JZ 0x1481a10b4
1481a10b2 NOP
1481a10b3 INT3
1481a10b4 MOVSXD RBX,dword ptr [RSP + 0x60]
1481a10b9 LEA EAX,[RBX + 0x1]
1481a10bc MOV dword ptr [RSP + 0x60],EAX
1481a10c0 CMP EAX,dword ptr [RSP + 0x64]
1481a10c4 JBE 0x1481a10d2
1481a10c6 MOV EDX,EBX
1481a10c8 LEA RCX,[RSP + 0x58]
1481a10cd CALL 0x140d215e0
1481a10d2 MOVSS XMM0,dword ptr [RSP + 0x50]
1481a10d8 MOV RAX,qword ptr [RSP + 0x58]
1481a10dd MOVSS dword ptr [RAX + RBX*0x4],XMM0
1481a10e2 CMP byte ptr [0x14eab53c8],0x2
1481a10e9 JC 0x1481a112d
1481a10eb XORPS XMM0,XMM0
1481a10ee CVTSS2SD XMM0,XMM6
1481a10f2 XORPS XMM1,XMM1
1481a10f5 CVTSS2SD XMM1,XMM8
1481a10fa XORPS XMM3,XMM3
1481a10fd CVTSS2SD XMM3,XMM9
1481a1102 MOVSD qword ptr [RSP + 0x30],XMM0
1481a1108 MOVSD qword ptr [RSP + 0x28],XMM1
1481a110e MOV dword ptr [RSP + 0x20],EDI
1481a1112 MOVQ R9,XMM3
1481a1117 MOV R8D,R15D
1481a111a LEA RDX,[0x14cf659a8]
1481a1121 LEA RCX,[0x14eab53c8]
1481a1128 CALL 0x140f24ba0
1481a112d INC R15D
1481a1130 MOV dword ptr [RSP + 0x118],R15D
1481a1138 ADD R12,0x4
1481a113c CMP R15D,dword ptr [RSI + 0x3c8]
1481a1143 LEA R8,[0x14bce6ef0]
1481a114a JL 0x1481a0e90
1481a1150 XORPS XMM6,XMM6
1481a1153 MOV RBX,qword ptr [RSP + 0x58]
1481a1158 MOVSXD RDI,dword ptr [RSP + 0x60]
1481a115d LEA RBP,[RBX + RDI*0x4]
1481a1161 CMP dword ptr [RSP + 0x60],EDI
1481a1165 JZ 0x1481a1182
1481a1167 MOV byte ptr [RSP + 0x110],0x0
1481a116f LEA RCX,[RSP + 0x110]
1481a1177 CALL 0x14bb28c50
1481a117c TEST AL,AL
1481a117e JZ 0x1481a1182
1481a1180 NOP
1481a1181 INT3
1481a1182 CMP RBX,RBP
1481a1185 JZ 0x1481a1191
1481a1187 ADDSS XMM6,dword ptr [RBX]
1481a118b ADD RBX,0x4
1481a118f JMP 0x1481a1161
1481a1191 MOVD XMM0,dword ptr [RSP + 0x60]
1481a1197 CVTDQ2PS XMM0,XMM0
1481a119a DIVSS XMM6,XMM0
1481a119e MOVSS dword ptr [RSI + 0x328],XMM6
1481a11a6 CMP byte ptr [0x14eab53c8],0x3
1481a11ad JC 0x1481a11cf
1481a11af XORPS XMM2,XMM2
1481a11b2 CVTSS2SD XMM2,XMM6
1481a11b6 MOVQ R8,XMM2
1481a11bb LEA RDX,[0x14cf65a20]
1481a11c2 LEA RCX,[0x14eab53c8]
1481a11c9 CALL 0x140f24ba0
1481a11ce NOP
1481a11cf MOV RCX,qword ptr [RSP + 0x58]
1481a11d4 TEST RCX,RCX
1481a11d7 JZ 0x1481a11df
1481a11d9 CALL 0x140e282f0
1481a11de NOP
1481a11df LEA R11,[RSP + 0xd0]
1481a11e7 MOV RBX,qword ptr [R11 + 0x50]
1481a11eb MOVAPS XMM6,xmmword ptr [R11 + -0x10]
1481a11f0 MOVAPS XMM7,xmmword ptr [R11 + -0x20]
1481a11f5 MOVAPS XMM8,xmmword ptr [R11 + -0x30]
1481a11fa MOVAPS XMM9,xmmword ptr [R11 + -0x40]
1481a11ff MOVAPS XMM10,xmmword ptr [R11 + -0x50]
1481a1204 MOVAPS XMM11,xmmword ptr [R11 + -0x60]
1481a1209 MOV RSP,R11
1481a120c POP R15
1481a120e POP R14
1481a1210 POP R13
1481a1212 POP R12
1481a1214 POP RDI
1481a1215 POP RSI
1481a1216 POP RBP
1481a1217 RET
*/

/* 1481a2200 RegisterBeatTap */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void RegisterBeatTap(longlong param_1,float param_2)

{
  ulonglong *puVar1;
  int iVar2;
  float *pfVar3;
  code *pcVar4;
  char cVar5;
  longlong lVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined8 unaff_retaddr;
  float afStackX_10 [2];
  
  if (*(char *)(param_1 + 0x358) == '\x02') {
    afStackX_10[0] = param_2;
    lVar6 = func_0x00014618b360();
    if (lVar6 == 0) {
      if (1 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65ab0);
      }
      uVar7 = 0;
      uVar8 = 0;
    }
    else {
      uVar7 = (undefined4)*(undefined8 *)(lVar6 + 0x740);
      uVar8 = (undefined4)((ulonglong)*(undefined8 *)(lVar6 + 0x740) >> 0x20);
    }
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65338);
      if (1 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65380,(double)afStackX_10[0]);
        if (1 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf653d0,CONCAT44(uVar8,uVar7));
          if (1 < DAT_14eab53c8) {
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65410,
                                (double)afStackX_10[0] - (double)CONCAT44(uVar8,uVar7));
            if (1 < DAT_14eab53c8) {
              func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65470,
                                  ((double)afStackX_10[0] - (double)CONCAT44(uVar8,uVar7)) *
                                  _DAT_14bcefa10);
            }
          }
        }
      }
    }
    puVar1 = (ulonglong *)(param_1 + 0x3c0);
    pfVar3 = (float *)*puVar1;
    if ((pfVar3 <= afStackX_10) && (afStackX_10 < pfVar3 + *(int *)(param_1 + 0x3cc))) {
      cVar5 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  afStackX_10,pfVar3,(longlong)*(int *)(param_1 + 0x3cc),
                                  (longlong)*(int *)(param_1 + 0x3c8),4);
      if (cVar5 != '\0') {
        pcVar4 = (code *)swi(3);
        (*pcVar4)();
        return;
      }
    }
    iVar2 = *(int *)(param_1 + 0x3c8);
    *(uint *)(param_1 + 0x3c8) = iVar2 + 1U;
    if (*(uint *)(param_1 + 0x3cc) < iVar2 + 1U) {
      func_0x000140d215e0(puVar1,iVar2);
    }
    *(float *)(*puVar1 + (longlong)iVar2 * 4) = afStackX_10[0];
    func_0x000148149ef0(param_1 + 0x2c0,*(undefined1 *)(param_1 + 0x358),
                        (float)*(int *)(param_1 + 0x3c8) / (float)*(int *)(param_1 + 0x360));
    if (*(int *)(param_1 + 0x360) <= *(int *)(param_1 + 0x3c8)) {
      AnalyzeCalibrationResults(param_1);
      if (*(char *)(param_1 + 0x3f9) != '\0') {
        func_0x0001481a2cc0();
        return;
      }
      func_0x0001481a1610(param_1);
    }
  }
  return;
}


/* Instruction evidence:
1481a2200 MOV RAX,RSP
1481a2203 MOVSS dword ptr [RAX + 0x10],XMM1
1481a2208 PUSH RBX
1481a2209 SUB RSP,0x60
1481a220d CMP byte ptr [RCX + 0x358],0x2
1481a2214 MOV RBX,RCX
1481a2217 JNZ 0x1481a2446
1481a221d MOV qword ptr [RAX + 0x8],RSI
1481a2221 MOV qword ptr [RAX + 0x18],RDI
1481a2225 MOVAPS xmmword ptr [RAX + -0x18],XMM6
1481a2229 CALL 0x14618b360
1481a222e TEST RAX,RAX
1481a2231 JZ 0x1481a223d
1481a2233 MOVSD XMM6,qword ptr [RAX + 0x740]
1481a223b JMP 0x1481a225c
1481a223d CMP byte ptr [0x14eab53c8],0x2
1481a2244 JC 0x1481a2259
1481a2246 LEA RDX,[0x14cf65ab0]
1481a224d LEA RCX,[0x14eab53c8]
1481a2254 CALL 0x140f24ba0
1481a2259 XORPS XMM6,XMM6
1481a225c CMP byte ptr [0x14eab53c8],0x2
1481a2263 JC 0x1481a2332
1481a2269 LEA RDX,[0x14cf65338]
1481a2270 LEA RCX,[0x14eab53c8]
1481a2277 CALL 0x140f24ba0
1481a227c CMP byte ptr [0x14eab53c8],0x2
1481a2283 JC 0x1481a2332
1481a2289 MOVSS XMM2,dword ptr [RSP + 0x78]
1481a228f LEA RDX,[0x14cf65380]
1481a2296 CVTPS2PD XMM2,XMM2
1481a2299 LEA RCX,[0x14eab53c8]
1481a22a0 MOVQ R8,XMM2
1481a22a5 CALL 0x140f24ba0
1481a22aa CMP byte ptr [0x14eab53c8],0x2
1481a22b1 JC 0x1481a2332
1481a22b3 MOVAPS XMM2,XMM6
1481a22b6 LEA RDX,[0x14cf653d0]
1481a22bd MOVQ R8,XMM6
1481a22c2 LEA RCX,[0x14eab53c8]
1481a22c9 CALL 0x140f24ba0
1481a22ce CMP byte ptr [0x14eab53c8],0x2
1481a22d5 JC 0x1481a2332
1481a22d7 MOVSS XMM2,dword ptr [RSP + 0x78]
1481a22dd LEA RDX,[0x14cf65410]
1481a22e4 CVTPS2PD XMM2,XMM2
1481a22e7 LEA RCX,[0x14eab53c8]
1481a22ee SUBSD XMM2,XMM6
1481a22f2 MOVQ R8,XMM2
1481a22f7 CALL 0x140f24ba0
1481a22fc CMP byte ptr [0x14eab53c8],0x2
1481a2303 JC 0x1481a2332
1481a2305 MOVSS XMM2,dword ptr [RSP + 0x78]
1481a230b LEA RDX,[0x14cf65470]
1481a2312 CVTPS2PD XMM2,XMM2
1481a2315 LEA RCX,[0x14eab53c8]
1481a231c SUBSD XMM2,XMM6
1481a2320 MULSD XMM2,qword ptr [0x14bcefa10]
1481a2328 MOVQ R8,XMM2
1481a232d CALL 0x140f24ba0
1481a2332 MOVAPS XMM6,xmmword ptr [RSP + 0x50]
1481a2337 LEA RDI,[RBX + 0x3c0]
1481a233e MOV RCX,qword ptr [RDI]
1481a2341 LEA RAX,[RSP + 0x78]
1481a2346 CMP RAX,RCX
1481a2349 JC 0x1481a23b3
1481a234b MOVSXD RDX,dword ptr [RDI + 0xc]
1481a234f LEA R8,[RSP + 0x78]
1481a2354 LEA RAX,[RCX + RDX*0x4]
1481a2358 CMP R8,RAX
1481a235b JNC 0x1481a23b3
1481a235d MOVSXD RAX,dword ptr [RDI + 0x8]
1481a2361 MOV R8D,0x63e
1481a2367 MOV R9,qword ptr [RSP + 0x68]
1481a236c MOV qword ptr [RSP + 0x48],0x4
1481a2375 MOV qword ptr [RSP + 0x40],RAX
1481a237a LEA RAX,[RSP + 0x78]
1481a237f MOV qword ptr [RSP + 0x38],RDX
1481a2384 LEA RDX,[0x14cf27ac0]
1481a238b MOV qword ptr [RSP + 0x30],RCX
1481a2390 LEA RCX,[0x14bce6eb8]
1481a2397 MOV qword ptr [RSP + 0x28],RAX
1481a239c LEA RAX,[0x14bce6d80]
1481a23a3 MOV qword ptr [RSP + 0x20],RAX
1481a23a8 CALL 0x140f8dfd0
1481a23ad TEST AL,AL
1481a23af JZ 0x1481a23b3
1481a23b1 NOP
1481a23b2 INT3
1481a23b3 MOVSXD RSI,dword ptr [RDI + 0x8]
1481a23b7 LEA EAX,[RSI + 0x1]
1481a23ba MOV dword ptr [RDI + 0x8],EAX
1481a23bd CMP EAX,dword ptr [RDI + 0xc]
1481a23c0 JBE 0x1481a23cc
1481a23c2 MOV EDX,ESI
1481a23c4 MOV RCX,RDI
1481a23c7 CALL 0x140d215e0
1481a23cc MOVSS XMM0,dword ptr [RSP + 0x78]
1481a23d2 LEA RCX,[RBX + 0x2c0]
1481a23d9 MOV RAX,qword ptr [RDI]
1481a23dc MOVSS dword ptr [RAX + RSI*0x4],XMM0
1481a23e1 MOVD XMM2,dword ptr [RBX + 0x3c8]
1481a23e9 MOVD XMM0,dword ptr [RBX + 0x360]
1481a23f1 MOVZX EDX,byte ptr [RBX + 0x358]
1481a23f8 CVTDQ2PS XMM2,XMM2
1481a23fb CVTDQ2PS XMM0,XMM0
1481a23fe DIVSS XMM2,XMM0
1481a2402 CALL 0x148149ef0
1481a2407 MOV EAX,dword ptr [RBX + 0x360]
1481a240d MOV RDI,qword ptr [RSP + 0x80]
1481a2415 MOV RSI,qword ptr [RSP + 0x70]
1481a241a CMP dword ptr [RBX + 0x3c8],EAX
1481a2420 JL 0x1481a2446
1481a2422 MOV RCX,RBX
1481a2425 CALL 0x1481a0db0
1481a242a CMP byte ptr [RBX + 0x3f9],0x0
1481a2431 MOV RCX,RBX
1481a2434 JZ 0x1481a2441
1481a2436 CALL 0x1481a2cc0
1481a243b ADD RSP,0x60
1481a243f POP RBX
1481a2440 RET
1481a2441 CALL 0x1481a1610
1481a2446 ADD RSP,0x60
1481a244a POP RBX
1481a244b RET
*/

/* 1481a2a90 RunManualCalibrationStep */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void RunManualCalibrationStep(longlong param_1)

{
  double dVar1;
  undefined8 uVar2;
  undefined **ppuVar3;
  undefined1 auStack_138 [32];
  undefined1 uStack_118;
  undefined4 uStack_110;
  longlong *plStack_108;
  undefined8 *puStack_f8;
  int iStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  longlong alStack_c8 [2];
  undefined **ppuStack_b8;
  undefined *puStack_a8;
  longlong lStack_a0;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined *puStack_88;
  longlong *plStack_80;
  longlong lStack_78;
  undefined **ppuStack_68;
  undefined *puStack_58;
  longlong lStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined *puStack_38;
  longlong *plStack_30;
  ulonglong uStack_28;
  
  uStack_28 = _DAT_14ea60b28 ^ (ulonglong)auStack_138;
  if (*(char *)(param_1 + 0x358) == '\x02') {
    if (*(int *)(param_1 + 1000) < *(int *)(param_1 + 0x364)) {
      PlayCalibrationBeat();
      *(int *)(param_1 + 1000) = *(int *)(param_1 + 1000) + 1;
      dVar1 = _DAT_14bd17840 / (double)*(float *)(param_1 + 0x35c);
      uVar2 = func_0x00014618b360(param_1);
      uVar2 = func_0x000147a1e670(uVar2);
      puStack_58 = &UNK_14cf65bd0;
      lStack_78 = 0x1481a1270;
      puStack_38 = &UNK_14cf65b20;
      plStack_80 = &lStack_50;
      puStack_f8 = (undefined8 *)0x0;
      iStack_f0 = 0;
      uStack_e8 = 0;
      uStack_e0 = 0;
      uStack_d8 = 0;
      plStack_108 = alStack_c8;
      alStack_c8[0] = 0x1481a1270;
      ppuStack_b8 = (undefined **)0x0;
      ppuStack_68 = (undefined **)0x0;
      puStack_a8 = &UNK_14cf65bd0;
      uStack_98 = uStack_48;
      uStack_94 = uStack_44;
      uStack_90 = uStack_40;
      uStack_8c = uStack_3c;
      puStack_88 = &UNK_14cf65b20;
      lStack_a0 = param_1;
      lStack_50 = param_1;
      plStack_30 = plStack_80;
      plStack_80 = (longlong *)(*_DAT_14cf65bd8)(&puStack_a8);
      lStack_78 = 0;
      uStack_110 = _DAT_14bd17874;
      uStack_118 = 0;
      func_0x0001478cf760(uVar2,param_1 + 0x408,&puStack_f8,(float)dVar1);
      if (alStack_c8[0] != 0) {
        ppuVar3 = &puStack_a8;
        if (ppuStack_b8 != (undefined **)0x0) {
          ppuVar3 = ppuStack_b8;
        }
        (**(code **)(*ppuVar3 + 0x10))();
      }
      puStack_88 = &UNK_14d3ac0f0;
      func_0x000140c70210(&uStack_e8);
      if ((iStack_f0 != 0) && (puStack_f8 != (undefined8 *)0x0)) {
        (**(code **)*puStack_f8)(puStack_f8,0);
        func_0x000140d20c70(&puStack_f8,0,0,0x10);
        iStack_f0 = 0;
      }
      if (puStack_f8 != (undefined8 *)0x0) {
        func_0x000140e282f0();
      }
      if (lStack_78 != 0) {
        ppuVar3 = &puStack_58;
        if (ppuStack_68 != (undefined **)0x0) {
          ppuVar3 = ppuStack_68;
        }
        (**(code **)(*ppuVar3 + 0x10))();
      }
    }
    else {
      AnalyzeCalibrationResults();
      if (*(char *)(param_1 + 0x3f9) == '\0') {
        func_0x0001481a1610(param_1);
      }
      else {
        func_0x0001481a2cc0();
      }
    }
  }
  func_0x00014b880380(uStack_28 ^ (ulonglong)auStack_138);
  return;
}


/* Instruction evidence:
1481a2a90 MOV RAX,RSP
1481a2a93 MOV qword ptr [RAX + 0x10],RBX
1481a2a97 MOV qword ptr [RAX + 0x18],RSI
1481a2a9b MOV qword ptr [RAX + 0x20],RDI
1481a2a9f PUSH RBP
1481a2aa0 LEA RBP,[RAX + -0x38]
1481a2aa4 SUB RSP,0x130
1481a2aab MOVAPS xmmword ptr [RAX + -0x18],XMM6
1481a2aaf MOV RAX,qword ptr [0x14ea60b28]
1481a2ab6 XOR RAX,RSP
1481a2ab9 MOV qword ptr [RBP + 0x10],RAX
1481a2abd MOV RDI,RCX
1481a2ac0 CMP byte ptr [RCX + 0x358],0x2
1481a2ac7 JNZ 0x1481a2c87
1481a2acd MOV EAX,dword ptr [RCX + 0x364]
1481a2ad3 CMP dword ptr [RCX + 0x3e8],EAX
1481a2ad9 JL 0x1481a2b00
1481a2adb CALL 0x1481a0db0
1481a2ae0 MOV RCX,RDI
1481a2ae3 CMP byte ptr [RDI + 0x3f9],0x0
1481a2aea JZ 0x1481a2af6
1481a2aec CALL 0x1481a2cc0
1481a2af1 JMP 0x1481a2c87
1481a2af6 CALL 0x1481a1610
1481a2afb JMP 0x1481a2c87
1481a2b00 CALL 0x1481a1db0
1481a2b05 INC dword ptr [RDI + 0x3e8]
1481a2b0b MOVSS XMM0,dword ptr [RDI + 0x35c]
1481a2b13 CVTPS2PD XMM0,XMM0
1481a2b16 MOVSD XMM6,qword ptr [0x14bd17840]
1481a2b1e DIVSD XMM6,XMM0
1481a2b22 MOV RCX,RDI
1481a2b25 CALL 0x14618b360
1481a2b2a MOV RCX,RAX
1481a2b2d CALL 0x147a1e670
1481a2b32 MOV RBX,RAX
1481a2b35 MOV qword ptr [RBP + -0x18],RDI
1481a2b39 LEA RAX,[0x14cf65bd0]
1481a2b40 MOV qword ptr [RBP + -0x20],RAX
1481a2b44 LEA RCX,[0x1481a1270]
1481a2b4b MOV qword ptr [RBP + -0x40],RCX
1481a2b4f LEA RAX,[0x14cf65b20]
1481a2b56 MOV qword ptr [RBP],RAX
1481a2b5a LEA RAX,[RBP + -0x18]
1481a2b5e MOV qword ptr [RBP + 0x8],RAX
1481a2b62 XOR ESI,ESI
1481a2b64 MOV qword ptr [RSP + 0x40],RSI
1481a2b69 MOV dword ptr [RSP + 0x48],ESI
1481a2b6d LEA RAX,[RSP + 0x50]
1481a2b72 MOV qword ptr [RSP + 0x30],RAX
1481a2b77 MOV qword ptr [RSP + 0x50],RSI
1481a2b7c MOV qword ptr [RSP + 0x58],RSI
1481a2b81 MOV qword ptr [RSP + 0x60],RSI
1481a2b86 LEA RAX,[RSP + 0x70]
1481a2b8b MOV qword ptr [RSP + 0x30],RAX
1481a2b90 MOV qword ptr [RSP + 0x70],RCX
1481a2b95 MOV qword ptr [RBP + -0x80],RSI
1481a2b99 MOV qword ptr [RBP + -0x30],RSI
1481a2b9d LEA RCX,[RBP + -0x70]
1481a2ba1 MOVAPS XMM0,xmmword ptr [RBP + -0x20]
1481a2ba5 MOVAPS xmmword ptr [RBP + -0x70],XMM0
1481a2ba9 MOVAPS XMM1,xmmword ptr [RBP + -0x10]
1481a2bad MOVAPS xmmword ptr [RBP + -0x60],XMM1
1481a2bb1 MOVAPS XMM0,xmmword ptr [RBP]
1481a2bb5 MOVDQA xmmword ptr [RBP + -0x50],XMM0
1481a2bba MOV RAX,qword ptr [0x14cf65bd8]
1481a2bc1 CALL RAX
1481a2bc3 MOV qword ptr [RBP + -0x48],RAX
1481a2bc7 MOV qword ptr [RBP + -0x40],RSI
1481a2bcb CVTPD2PS XMM3,XMM6
1481a2bcf LEA RDX,[RDI + 0x408]
1481a2bd6 MOVSS XMM0,dword ptr [0x14bd17874]
1481a2bde MOVSS dword ptr [RSP + 0x28],XMM0
1481a2be4 MOV byte ptr [RSP + 0x20],SIL
1481a2be9 LEA R8,[RSP + 0x40]
1481a2bee MOV RCX,RBX
1481a2bf1 CALL 0x1478cf760
1481a2bf6 NOP
1481a2bf7 CMP qword ptr [RSP + 0x70],RSI
1481a2bfc JZ 0x1481a2c13
1481a2bfe MOV RAX,qword ptr [RBP + -0x80]
1481a2c02 LEA RCX,[RBP + -0x70]
1481a2c06 TEST RAX,RAX
1481a2c09 CMOVNZ RCX,RAX
1481a2c0d MOV RAX,qword ptr [RCX]
1481a2c10 CALL qword ptr [RAX + 0x10]
1481a2c13 LEA RAX,[0x14d3ac0f0]
1481a2c1a MOV qword ptr [RBP + -0x50],RAX
1481a2c1e LEA RCX,[RSP + 0x50]
1481a2c23 CALL 0x140c70210
1481a2c28 NOP
1481a2c29 MOV RCX,qword ptr [RSP + 0x40]
1481a2c2e CMP dword ptr [RSP + 0x48],0x0
1481a2c33 JZ 0x1481a2c5f
1481a2c35 TEST RCX,RCX
1481a2c38 JZ 0x1481a2c5f
1481a2c3a MOV RAX,qword ptr [RCX]
1481a2c3d XOR EDX,EDX
1481a2c3f CALL qword ptr [RAX]
1481a2c41 MOV R9D,0x10
1481a2c47 XOR R8D,R8D
1481a2c4a XOR EDX,EDX
1481a2c4c LEA RCX,[RSP + 0x40]
1481a2c51 CALL 0x140d20c70
1481a2c56 MOV dword ptr [RSP + 0x48],ESI
1481a2c5a MOV RCX,qword ptr [RSP + 0x40]
1481a2c5f TEST RCX,RCX
1481a2c62 JZ 0x1481a2c6a
1481a2c64 CALL 0x140e282f0
1481a2c69 NOP
1481a2c6a CMP qword ptr [RBP + -0x40],0x0
1481a2c6f JZ 0x1481a2c87
1481a2c71 MOV RAX,qword ptr [RBP + -0x30]
1481a2c75 LEA RCX,[RBP + -0x20]
1481a2c79 TEST RAX,RAX
1481a2c7c CMOVNZ RCX,RAX
1481a2c80 MOV RAX,qword ptr [RCX]
1481a2c83 CALL qword ptr [RAX + 0x10]
1481a2c86 NOP
1481a2c87 MOV RCX,qword ptr [RBP + 0x10]
1481a2c8b XOR RCX,RSP
1481a2c8e CALL 0x14b880380
1481a2c93 LEA R11,[RSP + 0x130]
1481a2c9b MOV RBX,qword ptr [R11 + 0x18]
1481a2c9f MOV RSI,qword ptr [R11 + 0x20]
1481a2ca3 MOV RDI,qword ptr [R11 + 0x28]
1481a2ca7 MOVAPS XMM6,xmmword ptr [R11 + -0x10]
1481a2cac MOV RSP,R11
1481a2caf POP RBP
1481a2cb0 RET
*/

/* 1481a1db0 PlayCalibrationBeat */

void PlayCalibrationBeat(longlong param_1)

{
  ulonglong *puVar1;
  uint uVar2;
  int iVar3;
  double *pdVar4;
  code *pcVar5;
  char cVar6;
  uint uVar7;
  longlong lVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined8 unaff_retaddr;
  double adStack_28 [4];
  
  lVar8 = func_0x00014618b360();
  if (lVar8 == 0) {
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65ab0);
    }
    uVar9 = 0;
    uVar10 = 0;
  }
  else {
    uVar9 = (undefined4)*(undefined8 *)(lVar8 + 0x740);
    uVar10 = (undefined4)((ulonglong)*(undefined8 *)(lVar8 + 0x740) >> 0x20);
  }
  uVar2 = *(uint *)(param_1 + 1000);
  puVar1 = (ulonglong *)(param_1 + 0x3d0);
  adStack_28[0] = (double)CONCAT44(uVar10,uVar9);
  if ((int)uVar2 < *(int *)(param_1 + 0x3d8)) {
    uVar7 = 0;
    if ((int)uVar2 < *(int *)(param_1 + 0x3d8)) {
      uVar7 = ~uVar2 >> 0x1f;
    }
    if (uVar7 == 0) {
      cVar6 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,&UNK_14bce6ef0,
                                  (longlong)(int)uVar2,(longlong)*(int *)(param_1 + 0x3d8));
      if (cVar6 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    *(ulonglong *)(*puVar1 + (longlong)(int)uVar2 * 8) = CONCAT44(uVar10,uVar9);
  }
  else {
    pdVar4 = (double *)*puVar1;
    if ((pdVar4 <= adStack_28) && (adStack_28 < pdVar4 + *(int *)(param_1 + 0x3dc))) {
      cVar6 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,&UNK_14bce6d80,
                                  adStack_28,pdVar4,(longlong)*(int *)(param_1 + 0x3dc),
                                  (longlong)*(int *)(param_1 + 0x3d8),8);
      if (cVar6 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar3 = *(int *)(param_1 + 0x3d8);
    *(uint *)(param_1 + 0x3d8) = iVar3 + 1U;
    if (*(uint *)(param_1 + 0x3dc) < iVar3 + 1U) {
      func_0x0001410e9010(puVar1,iVar3);
    }
    *(double *)(*puVar1 + (longlong)iVar3 * 8) = adStack_28[0];
  }
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65820,*(undefined4 *)(param_1 + 1000),adStack_28[0])
    ;
  }
  func_0x000148149f40(param_1 + 0x2f0);
  func_0x000148149f20(param_1 + 0x2d8,(float)adStack_28[0]);
  return;
}


/* Instruction evidence:
1481a1db0 MOV qword ptr [RSP + 0x8],RBX
1481a1db5 MOV qword ptr [RSP + 0x10],RSI
1481a1dba PUSH RDI
1481a1dbb SUB RSP,0x70
1481a1dbf MOVAPS xmmword ptr [RSP + 0x60],XMM6
1481a1dc4 MOV RDI,RCX
1481a1dc7 CALL 0x14618b360
1481a1dcc TEST RAX,RAX
1481a1dcf JZ 0x1481a1ddb
1481a1dd1 MOVSD XMM6,qword ptr [RAX + 0x740]
1481a1dd9 JMP 0x1481a1dfa
1481a1ddb CMP byte ptr [0x14eab53c8],0x2
1481a1de2 JC 0x1481a1df7
1481a1de4 LEA RDX,[0x14cf65ab0]
1481a1deb LEA RCX,[0x14eab53c8]
1481a1df2 CALL 0x140f24ba0
1481a1df7 XORPS XMM6,XMM6
1481a1dfa MOVSXD RSI,dword ptr [RDI + 0x3e8]
1481a1e01 LEA RBX,[RDI + 0x3d0]
1481a1e08 MOVSD qword ptr [RSP + 0x50],XMM6
1481a1e0e CMP dword ptr [RDI + 0x3d8],ESI
1481a1e14 JG 0x1481a1eb8
1481a1e1a MOV RCX,qword ptr [RBX]
1481a1e1d LEA RAX,[RSP + 0x50]
1481a1e22 CMP RAX,RCX
1481a1e25 JC 0x1481a1e8f
1481a1e27 MOVSXD RDX,dword ptr [RBX + 0xc]
1481a1e2b LEA R8,[RSP + 0x50]
1481a1e30 LEA RAX,[RCX + RDX*0x8]
1481a1e34 CMP R8,RAX
1481a1e37 JNC 0x1481a1e8f
1481a1e39 MOVSXD RAX,dword ptr [RBX + 0x8]
1481a1e3d MOV R8D,0x63e
1481a1e43 MOV R9,qword ptr [RSP + 0x78]
1481a1e48 MOV qword ptr [RSP + 0x48],0x8
1481a1e51 MOV qword ptr [RSP + 0x40],RAX
1481a1e56 LEA RAX,[RSP + 0x50]
1481a1e5b MOV qword ptr [RSP + 0x38],RDX
1481a1e60 LEA RDX,[0x14cf27ac0]
1481a1e67 MOV qword ptr [RSP + 0x30],RCX
1481a1e6c LEA RCX,[0x14bce6eb8]
1481a1e73 MOV qword ptr [RSP + 0x28],RAX
1481a1e78 LEA RAX,[0x14bce6d80]
1481a1e7f MOV qword ptr [RSP + 0x20],RAX
1481a1e84 CALL 0x140f8dfd0
1481a1e89 TEST AL,AL
1481a1e8b JZ 0x1481a1e8f
1481a1e8d NOP
1481a1e8e INT3
1481a1e8f MOVSXD RSI,dword ptr [RBX + 0x8]
1481a1e93 LEA EAX,[RSI + 0x1]
1481a1e96 MOV dword ptr [RBX + 0x8],EAX
1481a1e99 CMP EAX,dword ptr [RBX + 0xc]
1481a1e9c JBE 0x1481a1ea8
1481a1e9e MOV EDX,ESI
1481a1ea0 MOV RCX,RBX
1481a1ea3 CALL 0x1410e9010
1481a1ea8 MOV RAX,qword ptr [RBX]
1481a1eab MOVSD XMM0,qword ptr [RSP + 0x50]
1481a1eb1 MOVSD qword ptr [RAX + RSI*0x8],XMM0
1481a1eb6 JMP 0x1481a1f10
1481a1eb8 MOVSXD RDX,dword ptr [RBX + 0x8]
1481a1ebc XOR EAX,EAX
1481a1ebe MOV ECX,ESI
1481a1ec0 NOT ECX
1481a1ec2 SHR ECX,0x1f
1481a1ec5 CMP ESI,EDX
1481a1ec7 CMOVL EAX,ECX
1481a1eca TEST EAX,EAX
1481a1ecc JNZ 0x1481a1f08
1481a1ece MOV R9,qword ptr [RSP + 0x78]
1481a1ed3 LEA RAX,[0x14bce6ef0]
1481a1eda MOV qword ptr [RSP + 0x30],RDX
1481a1edf LEA RCX,[0x14bce6f68]
1481a1ee6 MOV qword ptr [RSP + 0x28],RSI
1481a1eeb LEA RDX,[0x14cf27ac0]
1481a1ef2 MOV R8D,0x303
1481a1ef8 MOV qword ptr [RSP + 0x20],RAX
1481a1efd CALL 0x140f8dfd0
1481a1f02 TEST AL,AL
1481a1f04 JZ 0x1481a1f08
1481a1f06 NOP
1481a1f07 INT3
1481a1f08 MOV RAX,qword ptr [RBX]
1481a1f0b MOVSD qword ptr [RAX + RSI*0x8],XMM6
1481a1f10 CMP byte ptr [0x14eab53c8],0x3
1481a1f17 JC 0x1481a1f3e
1481a1f19 MOVSD XMM3,qword ptr [RSP + 0x50]
1481a1f1f LEA RDX,[0x14cf65820]
1481a1f26 MOV R8D,dword ptr [RDI + 0x3e8]
1481a1f2d LEA RCX,[0x14eab53c8]
1481a1f34 MOVQ R9,XMM3
1481a1f39 CALL 0x140f24ba0
1481a1f3e LEA RCX,[RDI + 0x2f0]
1481a1f45 CALL 0x148149f40
1481a1f4a MOVSD XMM1,qword ptr [RSP + 0x50]
1481a1f50 LEA RCX,[RDI + 0x2d8]
1481a1f57 CVTPD2PS XMM1,XMM1
1481a1f5b CALL 0x148149f20
1481a1f60 MOVAPS XMM6,xmmword ptr [RSP + 0x60]
1481a1f65 LEA R11,[RSP + 0x70]
1481a1f6a MOV RBX,qword ptr [R11 + 0x10]
1481a1f6e MOV RSI,qword ptr [R11 + 0x18]
1481a1f72 MOV RSP,R11
1481a1f75 POP RDI
1481a1f76 RET
*/

/* 1481a3160 StartManualCalibration */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void StartManualCalibration(longlong param_1)

{
  double dVar1;
  undefined8 uVar2;
  longlong lVar3;
  undefined **ppuVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 auStack_138 [32];
  undefined1 uStack_118;
  undefined4 uStack_110;
  longlong *plStack_108;
  undefined8 *puStack_f8;
  int iStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  longlong alStack_c8 [2];
  undefined **ppuStack_b8;
  undefined *puStack_a8;
  longlong lStack_a0;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined *puStack_88;
  longlong *plStack_80;
  longlong lStack_78;
  undefined **ppuStack_68;
  undefined *puStack_58;
  longlong lStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined *puStack_38;
  longlong *plStack_30;
  ulonglong uStack_28;
  
  if (2 < DAT_14eab53c8) {
    plStack_30 = (longlong *)0x1481a3185;
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf652a8);
  }
  *(undefined1 *)(param_1 + 0x358) = 2;
  *(undefined4 *)(param_1 + 0x3c8) = 0;
  if (*(int *)(param_1 + 0x3cc) != 0) {
    plStack_30 = (longlong *)0x1481a31a7;
    func_0x000141095ac0(param_1 + 0x3c0,0);
  }
  *(undefined4 *)(param_1 + 0x3d8) = 0;
  if (*(int *)(param_1 + 0x3dc) != 0) {
    plStack_30 = (longlong *)0x1481a31c2;
    func_0x0001420ccc70(param_1 + 0x3d0,0);
  }
  *(undefined4 *)(param_1 + 1000) = 0;
  plStack_30 = (longlong *)0x1481a31d4;
  lVar3 = func_0x00014618b360(param_1);
  if (lVar3 == 0) {
    if (1 < DAT_14eab53c8) {
      plStack_30 = (longlong *)0x1481a31ff;
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65ab0);
    }
    uVar5 = 0;
    uVar6 = 0;
  }
  else {
    uVar5 = (undefined4)*(undefined8 *)(lVar3 + 0x740);
    uVar6 = (undefined4)((ulonglong)*(undefined8 *)(lVar3 + 0x740) >> 0x20);
  }
  *(ulonglong *)(param_1 + 0x3e0) = CONCAT44(uVar6,uVar5);
  plStack_30 = (longlong *)0x1481a3220;
  func_0x000148149ef0(param_1 + 0x2c0,*(undefined1 *)(param_1 + 0x358),0);
  uStack_28 = _DAT_14ea60b28 ^ (ulonglong)auStack_138;
  if (*(char *)(param_1 + 0x358) == '\x02') {
    if (*(int *)(param_1 + 1000) < *(int *)(param_1 + 0x364)) {
      PlayCalibrationBeat();
      *(int *)(param_1 + 1000) = *(int *)(param_1 + 1000) + 1;
      dVar1 = _DAT_14bd17840 / (double)*(float *)(param_1 + 0x35c);
      uVar2 = func_0x00014618b360(param_1);
      uVar2 = func_0x000147a1e670(uVar2);
      puStack_58 = &UNK_14cf65bd0;
      lStack_78 = 0x1481a1270;
      puStack_38 = &UNK_14cf65b20;
      plStack_80 = &lStack_50;
      puStack_f8 = (undefined8 *)0x0;
      iStack_f0 = 0;
      uStack_e8 = 0;
      uStack_e0 = 0;
      uStack_d8 = 0;
      plStack_108 = alStack_c8;
      alStack_c8[0] = 0x1481a1270;
      ppuStack_b8 = (undefined **)0x0;
      ppuStack_68 = (undefined **)0x0;
      puStack_a8 = &UNK_14cf65bd0;
      uStack_98 = uStack_48;
      uStack_94 = uStack_44;
      uStack_90 = uStack_40;
      uStack_8c = uStack_3c;
      puStack_88 = &UNK_14cf65b20;
      lStack_a0 = param_1;
      lStack_50 = param_1;
      plStack_30 = plStack_80;
      plStack_80 = (longlong *)(*_DAT_14cf65bd8)(&puStack_a8);
      lStack_78 = 0;
      uStack_110 = _DAT_14bd17874;
      uStack_118 = 0;
      func_0x0001478cf760(uVar2,param_1 + 0x408,&puStack_f8,(float)dVar1);
      if (alStack_c8[0] != 0) {
        ppuVar4 = &puStack_a8;
        if (ppuStack_b8 != (undefined **)0x0) {
          ppuVar4 = ppuStack_b8;
        }
        (**(code **)(*ppuVar4 + 0x10))();
      }
      puStack_88 = &UNK_14d3ac0f0;
      func_0x000140c70210(&uStack_e8);
      if ((iStack_f0 != 0) && (puStack_f8 != (undefined8 *)0x0)) {
        (**(code **)*puStack_f8)(puStack_f8,0);
        func_0x000140d20c70(&puStack_f8,0,0,0x10);
        iStack_f0 = 0;
      }
      if (puStack_f8 != (undefined8 *)0x0) {
        func_0x000140e282f0();
      }
      if (lStack_78 != 0) {
        ppuVar4 = &puStack_58;
        if (ppuStack_68 != (undefined **)0x0) {
          ppuVar4 = ppuStack_68;
        }
        (**(code **)(*ppuVar4 + 0x10))();
      }
    }
    else {
      AnalyzeCalibrationResults();
      if (*(char *)(param_1 + 0x3f9) == '\0') {
        func_0x0001481a1610(param_1);
      }
      else {
        func_0x0001481a2cc0();
      }
    }
  }
  func_0x00014b880380(uStack_28 ^ (ulonglong)auStack_138);
  return;
}


/* Instruction evidence:
1481a3160 PUSH RBX
1481a3162 SUB RSP,0x20
1481a3166 CMP byte ptr [0x14eab53c8],0x3
1481a316d MOV RBX,RCX
1481a3170 JC 0x1481a3185
1481a3172 LEA RDX,[0x14cf652a8]
1481a3179 LEA RCX,[0x14eab53c8]
1481a3180 CALL 0x140f24ba0
1481a3185 LEA RCX,[RBX + 0x3c0]
1481a318c MOV byte ptr [RBX + 0x358],0x2
1481a3193 CMP dword ptr [RCX + 0xc],0x0
1481a3197 MOV dword ptr [RCX + 0x8],0x0
1481a319e JZ 0x1481a31a7
1481a31a0 XOR EDX,EDX
1481a31a2 CALL 0x141095ac0
1481a31a7 LEA RCX,[RBX + 0x3d0]
1481a31ae CMP dword ptr [RCX + 0xc],0x0
1481a31b2 MOV dword ptr [RCX + 0x8],0x0
1481a31b9 JZ 0x1481a31c2
1481a31bb XOR EDX,EDX
1481a31bd CALL 0x1420ccc70
1481a31c2 MOV RCX,RBX
1481a31c5 MOV dword ptr [RBX + 0x3e8],0x0
1481a31cf CALL 0x14618b360
1481a31d4 TEST RAX,RAX
1481a31d7 JZ 0x1481a31e3
1481a31d9 MOVSD XMM0,qword ptr [RAX + 0x740]
1481a31e1 JMP 0x1481a3202
1481a31e3 CMP byte ptr [0x14eab53c8],0x2
1481a31ea JC 0x1481a31ff
1481a31ec LEA RDX,[0x14cf65ab0]
1481a31f3 LEA RCX,[0x14eab53c8]
1481a31fa CALL 0x140f24ba0
1481a31ff XORPS XMM0,XMM0
1481a3202 MOVZX EDX,byte ptr [RBX + 0x358]
1481a3209 LEA RCX,[RBX + 0x2c0]
1481a3210 XORPS XMM2,XMM2
1481a3213 MOVSD qword ptr [RBX + 0x3e0],XMM0
1481a321b CALL 0x148149ef0
1481a3220 MOV RCX,RBX
1481a3223 ADD RSP,0x20
1481a3227 POP RBX
1481a3228 JMP 0x1481a2a90
*/

/* 1481a1420 CompleteManualCalibration */

/* WARNING: Possible PIC construction at 0x0001481a2d22: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0001481a2edf: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0001481a2d27) */
/* WARNING: Removing unreachable block (ram,0x0001481a2d55) */
/* WARNING: Removing unreachable block (ram,0x0001481a2d36) */
/* WARNING: Removing unreachable block (ram,0x0001481a2d3b) */
/* WARNING: Removing unreachable block (ram,0x0001481a2d49) */
/* WARNING: Removing unreachable block (ram,0x0001481a2d40) */
/* WARNING: Removing unreachable block (ram,0x0001481a2d5f) */
/* WARNING: Removing unreachable block (ram,0x0001481a2e3f) */
/* WARNING: Removing unreachable block (ram,0x0001481a2e4a) */
/* WARNING: Removing unreachable block (ram,0x0001481a2e4e) */
/* WARNING: Removing unreachable block (ram,0x0001481a2e54) */
/* WARNING: Removing unreachable block (ram,0x0001481a2e76) */
/* WARNING: Removing unreachable block (ram,0x0001481a2e7b) */
/* WARNING: Removing unreachable block (ram,0x0001481a2ea1) */
/* WARNING: Removing unreachable block (ram,0x0001481a2ea6) */
/* WARNING: Removing unreachable block (ram,0x0001481a2eac) */
/* WARNING: Removing unreachable block (ram,0x0001481a2eb3) */
/* WARNING: Removing unreachable block (ram,0x0001481a2ebe) */
/* WARNING: Removing unreachable block (ram,0x0001481a2ec2) */
/* WARNING: Removing unreachable block (ram,0x0001481a2ec9) */
/* WARNING: Removing unreachable block (ram,0x0001481a2ee4) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void CompleteManualCalibration(longlong param_1)

{
  undefined8 *puVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  undefined1 auStackX_8 [16];
  undefined8 uStack_140;
  undefined1 auStack_138 [24];
  undefined1 auStack_120 [240];
  undefined8 uStack_30;
  ulonglong uStack_28;
  
  uStack_30 = 0x1481a142e;
  AnalyzeCalibrationResults();
  if (*(char *)(param_1 + 0x3f9) == '\0') {
    *(undefined1 *)(param_1 + 0x358) = 4;
    *(undefined1 *)(param_1 + 0x350) = 1;
    uStack_30 = 0x1481a1635;
    puVar1 = (undefined8 *)func_0x000141014800(auStackX_8);
    *(undefined8 *)(param_1 + 0x348) = *puVar1;
    if (2 < DAT_14eab53c8) {
      uStack_30 = 0x1481a165f;
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf655e8);
      if (2 < DAT_14eab53c8) {
        uStack_30 = 0x1481a1692;
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65668,(double)*(float *)(param_1 + 800));
        if (2 < DAT_14eab53c8) {
          uStack_30 = 0x1481a16c2;
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf656b8,(double)*(float *)(param_1 + 0x324));
          if (2 < DAT_14eab53c8) {
            uStack_30 = 0x1481a16f2;
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf656f8,(double)*(float *)(param_1 + 0x328));
            if (2 < DAT_14eab53c8) {
              uStack_30 = 0x1481a1722;
              func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65750,(double)*(float *)(param_1 + 0x32c))
              ;
              if (2 < DAT_14eab53c8) {
                uStack_30 = 0x1481a174e;
                func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65790,
                                    (double)*(float *)(param_1 + 0x330));
                if (2 < DAT_14eab53c8) {
                  uStack_30 = 0x1481a178e;
                  func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf657e0,
                                      (double)(*(float *)(param_1 + 0x330) +
                                               *(float *)(param_1 + 0x32c) +
                                               *(float *)(param_1 + 0x328) +
                                              *(float *)(param_1 + 0x324) +
                                              *(float *)(param_1 + 800)));
                }
              }
            }
          }
        }
      }
    }
    uStack_30 = 0x1481a17a6;
    func_0x000148149e50(param_1 + 0x2a8,param_1 + 800);
    uVar2 = *(undefined1 *)(param_1 + 0x358);
    uVar3 = _DAT_14bcef9ec;
  }
  else {
    uStack_28 = _DAT_14ea60b28 ^ (ulonglong)auStack_138;
    if (2 < DAT_14eab53c8) {
      uStack_140 = 0x1481a2d0f;
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65548,*(undefined1 *)(param_1 + 0x3f9));
    }
    *(undefined1 *)(param_1 + 0x358) = 3;
    uVar2 = 3;
    register0x00000020 = (BADSPACEBASE *)&uStack_140;
    uStack_140 = 0x1481a2d27;
    uVar3 = 0;
  }
  *(undefined1 *)((longlong)register0x00000020 + 0x20) = uVar2;
  *(undefined4 *)((longlong)register0x00000020 + 0x24) = uVar3;
  *(undefined8 *)((longlong)register0x00000020 + -0x30) = 0x148149f08;
  func_0x000141894210(param_1 + 0x2c0,(undefined1 *)((longlong)register0x00000020 + 0x20));
  return;
}


/* Instruction evidence:
148149ef0 SUB RSP,0x28
148149ef4 MOV byte ptr [RSP + 0x48],DL
148149ef8 LEA RDX,[RSP + 0x48]
148149efd MOVSS dword ptr [RSP + 0x4c],XMM2
148149f03 CALL 0x141894210
148149f08 ADD RSP,0x28
148149f0c RET
1481a1420 PUSH RBX
1481a1422 SUB RSP,0x20
1481a1426 MOV RBX,RCX
1481a1429 CALL 0x1481a0db0
1481a142e CMP byte ptr [RBX + 0x3f9],0x0
1481a1435 MOV RCX,RBX
1481a1438 JZ 0x1481a1444
1481a143a ADD RSP,0x20
1481a143e POP RBX
1481a143f JMP 0x1481a2cc0
1481a1444 ADD RSP,0x20
1481a1448 POP RBX
1481a1449 JMP 0x1481a1610
1481a1610 MOV qword ptr [RSP + 0x10],RBX
1481a1615 PUSH RDI
1481a1616 SUB RSP,0x20
1481a161a MOV RBX,RCX
1481a161d MOV byte ptr [RCX + 0x358],0x4
1481a1624 MOV byte ptr [RCX + 0x350],0x1
1481a162b LEA RCX,[RSP + 0x30]
1481a1630 CALL 0x141014800
1481a1635 MOV RDX,qword ptr [RAX]
1481a1638 MOV qword ptr [RBX + 0x348],RDX
1481a163f CMP byte ptr [0x14eab53c8],0x3
1481a1646 JC 0x1481a1790
1481a164c LEA RDX,[0x14cf655e8]
1481a1653 LEA RCX,[0x14eab53c8]
1481a165a CALL 0x140f24ba0
1481a165f CMP byte ptr [0x14eab53c8],0x3
1481a1666 JC 0x1481a1790
1481a166c LEA RDI,[RBX + 0x320]
1481a1673 MOVSS XMM2,dword ptr [RDI]
1481a1677 LEA RDX,[0x14cf65668]
1481a167e CVTPS2PD XMM2,XMM2
1481a1681 LEA RCX,[0x14eab53c8]
1481a1688 MOVQ R8,XMM2
1481a168d CALL 0x140f24ba0
1481a1692 CMP byte ptr [0x14eab53c8],0x3
1481a1699 JC 0x1481a1790
1481a169f MOVSS XMM2,dword ptr [RBX + 0x324]
1481a16a7 LEA RDX,[0x14cf656b8]
1481a16ae CVTPS2PD XMM2,XMM2
1481a16b1 LEA RCX,[0x14eab53c8]
1481a16b8 MOVQ R8,XMM2
1481a16bd CALL 0x140f24ba0
1481a16c2 CMP byte ptr [0x14eab53c8],0x3
1481a16c9 JC 0x1481a1790
1481a16cf MOVSS XMM2,dword ptr [RBX + 0x328]
1481a16d7 LEA RDX,[0x14cf656f8]
1481a16de CVTPS2PD XMM2,XMM2
1481a16e1 LEA RCX,[0x14eab53c8]
1481a16e8 MOVQ R8,XMM2
1481a16ed CALL 0x140f24ba0
1481a16f2 CMP byte ptr [0x14eab53c8],0x3
1481a16f9 JC 0x1481a1790
1481a16ff MOVSS XMM2,dword ptr [RBX + 0x32c]
1481a1707 LEA RDX,[0x14cf65750]
1481a170e CVTPS2PD XMM2,XMM2
1481a1711 LEA RCX,[0x14eab53c8]
1481a1718 MOVQ R8,XMM2
1481a171d CALL 0x140f24ba0
1481a1722 CMP byte ptr [0x14eab53c8],0x3
1481a1729 JC 0x1481a1790
1481a172b MOVSS XMM2,dword ptr [RBX + 0x330]
1481a1733 LEA RDX,[0x14cf65790]
1481a173a CVTPS2PD XMM2,XMM2
1481a173d LEA RCX,[0x14eab53c8]
1481a1744 MOVQ R8,XMM2
1481a1749 CALL 0x140f24ba0
1481a174e CMP byte ptr [0x14eab53c8],0x3
1481a1755 JC 0x1481a1790
1481a1757 MOVSS XMM1,dword ptr [RDI + 0x10]
1481a175c LEA RDX,[0x14cf657e0]
1481a1763 ADDSS XMM1,dword ptr [RDI + 0xc]
1481a1768 MOVSS XMM0,dword ptr [RDI + 0x4]
1481a176d LEA RCX,[0x14eab53c8]
1481a1774 ADDSS XMM0,dword ptr [RDI]
1481a1778 ADDSS XMM1,dword ptr [RDI + 0x8]
1481a177d ADDSS XMM1,XMM0
1481a1781 CVTPS2PD XMM2,XMM1
1481a1784 MOVQ R8,XMM2
1481a1789 CALL 0x140f24ba0
1481a178e JMP 0x1481a1797
1481a1790 LEA RDI,[RBX + 0x320]
1481a1797 LEA RCX,[RBX + 0x2a8]
1481a179e MOV RDX,RDI
1481a17a1 CALL 0x148149e50
1481a17a6 MOVSS XMM2,dword ptr [0x14bcef9ec]
1481a17ae LEA RCX,[RBX + 0x2c0]
1481a17b5 MOVZX EDX,byte ptr [RBX + 0x358]
1481a17bc MOV RBX,qword ptr [RSP + 0x38]
1481a17c1 ADD RSP,0x20
1481a17c5 POP RDI
1481a17c6 JMP 0x148149ef0
1481a2cc0 MOV qword ptr [RSP + 0x10],RBX
1481a2cc5 MOV qword ptr [RSP + 0x18],RSI
1481a2cca PUSH RBP
1481a2ccb PUSH RDI
1481a2ccc PUSH R14
1481a2cce LEA RBP,[RSP + -0x20]
1481a2cd3 SUB RSP,0x120
1481a2cda MOV RAX,qword ptr [0x14ea60b28]
1481a2ce1 XOR RAX,RSP
1481a2ce4 MOV qword ptr [RBP + 0x10],RAX
1481a2ce8 MOV RDI,RCX
1481a2ceb CMP byte ptr [0x14eab53c8],0x3
1481a2cf2 JC 0x1481a2d0f
1481a2cf4 MOVZX R8D,byte ptr [RCX + 0x3f9]
1481a2cfc LEA RDX,[0x14cf65548]
1481a2d03 LEA RCX,[0x14eab53c8]
1481a2d0a CALL 0x140f24ba0
1481a2d0f MOV byte ptr [RDI + 0x358],0x3
1481a2d16 XORPS XMM2,XMM2
1481a2d19 MOV DL,0x3
1481a2d1b LEA RCX,[RDI + 0x2c0]
1481a2d22 CALL 0x148149ef0
1481a2d27 MOVZX ECX,byte ptr [RDI + 0x3f9]
1481a2d2e XOR R14D,R14D
1481a2d31 SUB ECX,0x1
1481a2d34 JZ 0x1481a2d55
1481a2d36 SUB ECX,0x1
1481a2d39 JZ 0x1481a2d49
1481a2d3b CMP ECX,0x1
1481a2d3e JZ 0x1481a2d49
1481a2d40 MOV dword ptr [RDI + 0x32c],R14D
1481a2d47 JMP 0x1481a2d5f
1481a2d49 MOV dword ptr [RDI + 0x32c],0x42f00000
1481a2d53 JMP 0x1481a2d5f
1481a2d55 MOV dword ptr [RDI + 0x32c],0x42a00000
1481a2d5f MOV RCX,RDI
1481a2d62 CALL 0x14618b360
1481a2d67 MOV RCX,RAX
1481a2d6a CALL 0x147a1e670
1481a2d6f MOV RBX,RAX
1481a2d72 MOV qword ptr [RBP + -0x18],RDI
1481a2d76 LEA RAX,[0x14cf65c30]
1481a2d7d MOV qword ptr [RBP + -0x20],RAX
1481a2d81 LEA RCX,[0x1481a1280]
1481a2d88 MOV qword ptr [RBP + -0x40],RCX
1481a2d8c LEA RAX,[0x14cf65b28]
1481a2d93 MOV qword ptr [RBP],RAX
1481a2d97 LEA RAX,[RBP + -0x18]
1481a2d9b MOV qword ptr [RBP + 0x8],RAX
1481a2d9f MOV qword ptr [RSP + 0x40],R14
1481a2da4 MOV dword ptr [RSP + 0x48],R14D
1481a2da9 LEA RAX,[RSP + 0x50]
1481a2dae MOV qword ptr [RSP + 0x30],RAX
1481a2db3 MOV qword ptr [RSP + 0x50],R14
1481a2db8 MOV qword ptr [RSP + 0x58],R14
1481a2dbd MOV qword ptr [RSP + 0x60],R14
1481a2dc2 LEA RAX,[RSP + 0x70]
1481a2dc7 MOV qword ptr [RSP + 0x30],RAX
1481a2dcc MOV qword ptr [RSP + 0x70],RCX
1481a2dd1 MOV qword ptr [RBP + -0x80],R14
1481a2dd5 MOV qword ptr [RBP + -0x30],R14
1481a2dd9 LEA RCX,[RBP + -0x70]
1481a2ddd MOVAPS XMM0,xmmword ptr [RBP + -0x20]
1481a2de1 MOVAPS xmmword ptr [RBP + -0x70],XMM0
1481a2de5 MOVAPS XMM1,xmmword ptr [RBP + -0x10]
1481a2de9 MOVAPS xmmword ptr [RBP + -0x60],XMM1
1481a2ded MOVAPS XMM0,xmmword ptr [RBP]
1481a2df1 MOVDQA xmmword ptr [RBP + -0x50],XMM0
1481a2df6 MOV RAX,qword ptr [0x14cf65c38]
1481a2dfd CALL RAX
1481a2dff MOV qword ptr [RBP + -0x48],RAX
1481a2e03 MOV qword ptr [RBP + -0x40],R14
1481a2e07 LEA RDX,[RDI + 0x400]
1481a2e0e MOVSS XMM0,dword ptr [0x14bd17874]
1481a2e16 MOVSS dword ptr [RSP + 0x28],XMM0
1481a2e1c MOV byte ptr [RSP + 0x20],0x0
1481a2e21 MOVSS XMM3,dword ptr [0x14bd17824]
1481a2e29 LEA R8,[RSP + 0x40]
1481a2e2e MOV RCX,RBX
1481a2e31 CALL 0x1478cf760
1481a2e36 NOP
1481a2e37 CMP qword ptr [RSP + 0x70],0x0
1481a2e3d JZ 0x1481a2e54
1481a2e3f MOV RAX,qword ptr [RBP + -0x80]
1481a2e43 LEA RCX,[RBP + -0x70]
1481a2e47 TEST RAX,RAX
1481a2e4a CMOVNZ RCX,RAX
1481a2e4e MOV RAX,qword ptr [RCX]
1481a2e51 CALL qword ptr [RAX + 0x10]
1481a2e54 LEA RAX,[0x14d3ac0f0]
1481a2e5b MOV qword ptr [RBP + -0x50],RAX
1481a2e5f LEA RCX,[RSP + 0x50]
1481a2e64 CALL 0x140c70210
1481a2e69 NOP
1481a2e6a MOV RCX,qword ptr [RSP + 0x40]
1481a2e6f CMP dword ptr [RSP + 0x48],0x0
1481a2e74 JZ 0x1481a2ea1
1481a2e76 TEST RCX,RCX
1481a2e79 JZ 0x1481a2ea1
1481a2e7b MOV RAX,qword ptr [RCX]
1481a2e7e XOR EDX,EDX
1481a2e80 CALL qword ptr [RAX]
1481a2e82 MOV R9D,0x10
1481a2e88 XOR R8D,R8D
1481a2e8b XOR EDX,EDX
1481a2e8d LEA RCX,[RSP + 0x40]
1481a2e92 CALL 0x140d20c70
1481a2e97 MOV dword ptr [RSP + 0x48],R14D
1481a2e9c MOV RCX,qword ptr [RSP + 0x40]
1481a2ea1 TEST RCX,RCX
1481a2ea4 JZ 0x1481a2eac
1481a2ea6 CALL 0x140e282f0
1481a2eab NOP
1481a2eac CMP qword ptr [RBP + -0x40],0x0
1481a2eb1 JZ 0x1481a2ec9
1481a2eb3 MOV RAX,qword ptr [RBP + -0x30]
1481a2eb7 LEA RCX,[RBP + -0x20]
1481a2ebb TEST RAX,RAX
1481a2ebe CMOVNZ RCX,RAX
1481a2ec2 MOV RAX,qword ptr [RCX]
1481a2ec5 CALL qword ptr [RAX + 0x10]
1481a2ec8 NOP
1481a2ec9 MOVSS XMM2,dword ptr [0x14bcef9ec]
1481a2ed1 MOVZX EDX,byte ptr [RDI + 0x358]
1481a2ed8 LEA RCX,[RDI + 0x2c0]
1481a2edf CALL 0x148149ef0
1481a2ee4 MOV RCX,qword ptr [RBP + 0x10]
1481a2ee8 XOR RCX,RSP
1481a2eeb CALL 0x14b880380
1481a2ef0 LEA R11,[RSP + 0x120]
1481a2ef8 MOV RBX,qword ptr [R11 + 0x28]
1481a2efc MOV RSI,qword ptr [R11 + 0x30]
1481a2f00 MOV RSP,R11
1481a2f03 POP R14
1481a2f05 POP RDI
1481a2f06 POP RBP
1481a2f07 RET
*/

/* 1481a1a50 GetPreciseTime */

undefined8 GetPreciseTime(void)

{
  longlong lVar1;
  
  lVar1 = func_0x00014618b360();
  if (lVar1 != 0) {
    return *(undefined8 *)(lVar1 + 0x740);
  }
  if (1 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65ab0);
  }
  return 0;
}


/* Instruction evidence:
1481a1a50 SUB RSP,0x28
1481a1a54 CALL 0x14618b360
1481a1a59 TEST RAX,RAX
1481a1a5c JZ 0x1481a1a6b
1481a1a5e MOVSD XMM0,qword ptr [RAX + 0x740]
1481a1a66 ADD RSP,0x28
1481a1a6a RET
1481a1a6b CMP byte ptr [0x14eab53c8],0x2
1481a1a72 JC 0x1481a1a87
1481a1a74 LEA RDX,[0x14cf65ab0]
1481a1a7b LEA RCX,[0x14eab53c8]
1481a1a82 CALL 0x140f24ba0
1481a1a87 XORPS XMM0,XMM0
1481a1a8a ADD RSP,0x28
1481a1a8e RET
*/

/* 1481a1910 GetCompensatedTimelineOffset */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

double GetCompensatedTimelineOffset(longlong param_1)

{
  return (double)(*(float *)(param_1 + 0x330) + *(float *)(param_1 + 0x32c) +
                  *(float *)(param_1 + 0x328) +
                 *(float *)(param_1 + 0x324) + *(float *)(param_1 + 800)) * _DAT_14bcfdb30;
}


/* Instruction evidence:
1481a1910 MOVSS XMM1,dword ptr [RCX + 0x330]
1481a1918 ADDSS XMM1,dword ptr [RCX + 0x32c]
1481a1920 MOVSS XMM0,dword ptr [RCX + 0x324]
1481a1928 ADDSS XMM0,dword ptr [RCX + 0x320]
1481a1930 ADDSS XMM1,dword ptr [RCX + 0x328]
1481a1938 ADDSS XMM1,XMM0
1481a193c CVTPS2PD XMM0,XMM1
1481a193f MULSD XMM0,qword ptr [0x14bcfdb30]
1481a1947 RET
*/

/* 1481a1b70 GetProfileTotalLatency */

float GetProfileTotalLatency(undefined8 param_1,float *param_2)

{
  return param_2[4] + param_2[3] + param_2[2] + param_2[1] + *param_2;
}


/* Instruction evidence:
1481a1b70 MOVSS XMM0,dword ptr [RDX + 0x10]
1481a1b75 ADDSS XMM0,dword ptr [RDX + 0xc]
1481a1b7a MOVSS XMM1,dword ptr [RDX + 0x4]
1481a1b7f ADDSS XMM1,dword ptr [RDX]
1481a1b83 ADDSS XMM0,dword ptr [RDX + 0x8]
1481a1b88 ADDSS XMM0,XMM1
1481a1b8c RET
*/

/* 1481a1810 GetCalibrationProgress */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float GetCalibrationProgress(longlong param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x358);
  if (cVar1 == '\0') {
    return 0.0;
  }
  if (cVar1 != '\x01') {
    if (cVar1 != '\x02') {
      if (cVar1 == '\x03') {
        return _DAT_14bf058f0;
      }
      if (cVar1 != '\x04') {
        return 0.0;
      }
      return _DAT_14bcef9ec;
    }
    if (0 < *(int *)(param_1 + 0x360)) {
      return ((float)*(int *)(param_1 + 0x3c8) * _DAT_14bcfdb28) / (float)*(int *)(param_1 + 0x360)
             + _DAT_14bd4dca0;
    }
  }
  return _DAT_14bd4dca0;
}


/* Instruction evidence:
1481a1810 MOVZX EDX,byte ptr [RCX + 0x358]
1481a1817 TEST EDX,EDX
1481a1819 JZ 0x1481a187b
1481a181b SUB EDX,0x1
1481a181e JZ 0x1481a1872
1481a1820 SUB EDX,0x1
1481a1823 JZ 0x1481a1841
1481a1825 SUB EDX,0x1
1481a1828 JZ 0x1481a1838
1481a182a CMP EDX,0x1
1481a182d JNZ 0x1481a187b
1481a182f MOVSS XMM0,dword ptr [0x14bcef9ec]
1481a1837 RET
1481a1838 MOVSS XMM0,dword ptr [0x14bf058f0]
1481a1840 RET
1481a1841 MOV EAX,dword ptr [RCX + 0x360]
1481a1847 TEST EAX,EAX
1481a1849 JLE 0x1481a1872
1481a184b MOVD XMM0,dword ptr [RCX + 0x3c8]
1481a1853 CVTDQ2PS XMM0,XMM0
1481a1856 MOVD XMM1,EAX
1481a185a MULSS XMM0,dword ptr [0x14bcfdb28]
1481a1862 CVTDQ2PS XMM1,XMM1
1481a1865 DIVSS XMM0,XMM1
1481a1869 ADDSS XMM0,dword ptr [0x14bd4dca0]
1481a1871 RET
1481a1872 MOVSS XMM0,dword ptr [0x14bd4dca0]
1481a187a RET
1481a187b XORPS XMM0,XMM0
1481a187e RET
*/

/* 1481a1ba0 GetRequiredTapsRemaining */

int GetRequiredTapsRemaining(longlong param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x358) == '\x02') {
    iVar1 = *(int *)(param_1 + 0x360) - *(int *)(param_1 + 0x3c8);
    if (iVar1 < 0) {
      iVar1 = 0;
    }
    return iVar1;
  }
  return 0;
}


/* Instruction evidence:
1481a1ba0 CMP byte ptr [RCX + 0x358],0x2
1481a1ba7 JNZ 0x1481a1bbe
1481a1ba9 MOV EAX,dword ptr [RCX + 0x360]
1481a1baf SUB EAX,dword ptr [RCX + 0x3c8]
1481a1bb5 MOV ECX,0x0
1481a1bba CMOVS EAX,ECX
1481a1bbd RET
1481a1bbe XOR EAX,EAX
1481a1bc0 RET
*/

/* 1481a1cc0 IsProfileValid */

undefined1 IsProfileValid(undefined8 param_1,float *param_2)

{
  if ((*(char *)(param_2 + 0xc) != '\0') &&
     (0.0 < param_2[4] + param_2[3] + param_2[2] + param_2[1] + *param_2)) {
    return 1;
  }
  return 0;
}


/* Instruction evidence:
1481a1cc0 CMP byte ptr [RDX + 0x30],0x0
1481a1cc4 JZ 0x1481a1ced
1481a1cc6 MOVSS XMM0,dword ptr [RDX + 0x4]
1481a1ccb ADDSS XMM0,dword ptr [RDX]
1481a1ccf MOVSS XMM1,dword ptr [RDX + 0x10]
1481a1cd4 ADDSS XMM1,dword ptr [RDX + 0xc]
1481a1cd9 ADDSS XMM1,dword ptr [RDX + 0x8]
1481a1cde ADDSS XMM1,XMM0
1481a1ce2 XORPS XMM0,XMM0
1481a1ce5 COMISS XMM1,XMM0
1481a1ce8 JBE 0x1481a1ced
1481a1cea MOV AL,0x1
1481a1cec RET
1481a1ced XOR AL,AL
1481a1cef RET
*/
