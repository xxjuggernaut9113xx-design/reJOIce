
/* 1481cf860 ApplySpeedModifier */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Possible PIC construction at 0x0001481cf8ed: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0001481d1d2a: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0001481d1ea7: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0001481d1f32: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0001481d20dc: Changing call to branch */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ApplySpeedModifier(longlong param_1,float param_2)

{
  undefined8 *puVar1;
  uint uVar2;
  double *pdVar3;
  ulonglong uVar4;
  code *pcVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  char cVar9;
  int iVar10;
  uint uVar11;
  ulonglong uVar12;
  int iVar13;
  longlong lVar14;
  uint uVar15;
  int iVar16;
  ulonglong *puVar17;
  undefined8 unaff_retaddr;
  double dStack_b8;
  double dStack_b0;
  uint uStack_a8;
  undefined4 uStack_a4;
  double dStack_a0;
  int iStack_98;
  uint uStack_94;
  undefined8 uStack_60;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  if (((*(char *)(param_1 + 0x108) == '\0') || (iVar16 = *(int *)(param_1 + 0xf0), iVar16 == 0)) ||
     (iVar16 <= *(int *)(param_1 + 0x110))) {
    if (2 < DAT_14eab53c8) {
      halt_baddata();
    }
  }
  else {
    if ((*(int *)(param_1 + 0x170) != 0) &&
       (uVar15 = iVar16 - *(int *)(param_1 + 0x110), 0 < (int)uVar15)) {
      if (2 < DAT_14eab53c8) {
        _uStack_30 = CONCAT44(uStack_2c,*(undefined4 *)(param_1 + 0x118));
        _uStack_38 = CONCAT44(uStack_34,*(undefined4 *)(param_1 + 0x104));
        uStack_60 = 0x1481cf949;
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf7b7f8,(double)param_2,uVar15);
      }
      uVar12 = (ulonglong)uVar15;
      if (((*(char *)(param_1 + 0x108) == '\0') || (*(int *)(param_1 + 0xf0) == 0)) ||
         (*(int *)(param_1 + 0x170) == 0)) {
        if (DAT_14eab53c8 < 3) {
          return;
        }
      }
      else if (DAT_14eab53c8 < 3) {
        dVar7 = (double)func_0x0001481d12e0(param_1);
        uVar2 = *(uint *)(param_1 + 0x110);
        uVar11 = 0;
        if ((-1 < (int)uVar2) && ((int)uVar2 < *(int *)(param_1 + 0xf0))) {
          uVar11 = 0;
          if ((int)uVar2 < *(int *)(param_1 + 0xf0)) {
            uVar11 = ~uVar2 >> 0x1f;
          }
          if ((uVar11 == 0) &&
             (cVar9 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                          &UNK_14bce6ef0,(longlong)(int)uVar2,
                                          (longlong)*(int *)(param_1 + 0xf0)), cVar9 != '\0')) {
            pcVar5 = (code *)swi(3);
            (*pcVar5)();
            return;
          }
          uVar11 = *(uint *)(*(longlong *)(param_1 + 0xe8) + 0x10 + (longlong)(int)uVar2 * 0x28);
        }
        puVar17 = (ulonglong *)(param_1 + 0xe8);
        iVar16 = *(int *)(param_1 + 0x110);
        iVar13 = *(int *)(param_1 + 0xf0) - iVar16;
        if (iVar13 != 0) {
          iVar10 = (*(int *)(param_1 + 0xf0) - iVar16) - iVar13;
          if (iVar10 != 0) {
            func_0x00014b89503a(*puVar17 + (longlong)iVar16 * 0x28,
                                *puVar17 + (longlong)*(int *)(param_1 + 0xf0) * 0x28,
                                (longlong)iVar10 * 0x28);
          }
          *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) - iVar13;
          func_0x0001481d21b0(puVar17);
        }
        uVar2 = _DAT_14bd17880;
        iVar16 = *(int *)(param_1 + 0x110);
        iVar13 = *(int *)(param_1 + 0x170);
        dVar7 = dVar7 + _DAT_14bd774b8;
        if (0 < (int)uVar15) {
          dVar8 = _DAT_14bce5180 / (double)param_2;
          do {
            iVar16 = iVar16 + 1;
            if (((int)uVar11 < 0) || (*(int *)(param_1 + 0x170) <= (int)uVar11)) {
              if (1 < DAT_14eab53c8) {
                halt_baddata();
              }
              uVar11 = 0;
            }
            uVar15 = 0;
            if ((int)uVar11 < *(int *)(param_1 + 0x170)) {
              uVar15 = ~uVar11 >> 0x1f;
            }
            if ((uVar15 == 0) &&
               (cVar9 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                            &UNK_14bce6ef0,(longlong)(int)uVar11,
                                            (longlong)*(int *)(param_1 + 0x170)), cVar9 != '\0')) {
              pcVar5 = (code *)swi(3);
              (*pcVar5)();
              return;
            }
            uStack_94 = *(uint *)(*(longlong *)(param_1 + 0x168) + (longlong)(int)uVar11 * 4);
            if (1 < DAT_14eab53c8) {
              halt_baddata();
            }
            pdVar3 = (double *)*puVar17;
            dStack_b0 = dVar7 + *(double *)(param_1 + 0x150);
            dVar6 = (double)(float)(uStack_94 & uVar2) * *(double *)(param_1 + 0x1a0) * dVar8;
            if (dVar6 <= *(double *)(param_1 + 0xe0)) {
              dVar6 = *(double *)(param_1 + 0xe0);
            }
            dStack_b8 = dVar7;
            uStack_a8 = uVar11;
            dStack_a0 = dVar6;
            iStack_98 = iVar16;
            if (((pdVar3 <= &dStack_b8) &&
                (&dStack_b8 < pdVar3 + (longlong)*(int *)(param_1 + 0xf4) * 5)) &&
               (cVar9 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                            &UNK_14bce6d80,&dStack_b8,pdVar3,
                                            (longlong)*(int *)(param_1 + 0xf4),
                                            (longlong)*(int *)(param_1 + 0xf0),0x28), cVar9 != '\0')
               ) {
              pcVar5 = (code *)swi(3);
              (*pcVar5)();
              return;
            }
            iVar10 = *(int *)(param_1 + 0xf0);
            lVar14 = (longlong)iVar10;
            *(uint *)(param_1 + 0xf0) = iVar10 + 1U;
            if (*(uint *)(param_1 + 0xf4) < iVar10 + 1U) {
              func_0x0001481d2100(puVar17,iVar10);
            }
            uVar4 = *puVar17;
            dVar7 = dVar7 + dVar6;
            pdVar3 = (double *)(uVar4 + lVar14 * 0x28);
            *pdVar3 = dStack_b8;
            pdVar3[1] = dStack_b0;
            puVar1 = (undefined8 *)(uVar4 + 0x10 + lVar14 * 0x28);
            *puVar1 = CONCAT44(uStack_a4,uStack_a8);
            puVar1[1] = dStack_a0;
            *(ulonglong *)(uVar4 + 0x20 + lVar14 * 0x28) = CONCAT44(uStack_94,iStack_98);
            uVar11 = (int)(uVar11 + 1) % iVar13;
            uVar12 = uVar12 - 1;
          } while (uVar12 != 0);
        }
        *(float *)(param_1 + 0x10c) = param_2;
        return;
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (1 < DAT_14eab53c8) {
      halt_baddata();
    }
  }
  return;
}


/* Instruction evidence:
1481cf860 PUSH RBX
1481cf862 SUB RSP,0x50
1481cf866 CMP byte ptr [RCX + 0x108],0x0
1481cf86d MOV RBX,RCX
1481cf870 MOVAPS xmmword ptr [RSP + 0x40],XMM6
1481cf875 MOVAPS XMM6,XMM1
1481cf878 JZ 0x1481cf96d
1481cf87e MOV EAX,dword ptr [RCX + 0xf0]
1481cf884 TEST EAX,EAX
1481cf886 JZ 0x1481cf96d
1481cf88c MOV ECX,dword ptr [RCX + 0x110]
1481cf892 CMP ECX,EAX
1481cf894 JGE 0x1481cf96d
1481cf89a CMP dword ptr [RBX + 0x170],0x0
1481cf8a1 JNZ 0x1481cf8c9
1481cf8a3 CMP byte ptr [0x14eab53c8],0x2
1481cf8aa JC 0x1481cf8f7
1481cf8ac LEA RDX,[0x14cf7b698]
1481cf8b3 LEA RCX,[0x14eab53c8]
1481cf8ba MOVAPS XMM6,xmmword ptr [RSP + 0x40]
1481cf8bf ADD RSP,0x50
1481cf8c3 POP RBX
1481cf8c4 JMP 0x140f24ba0
1481cf8c9 MOV qword ptr [RSP + 0x60],RDI
1481cf8ce MOV EDI,EAX
1481cf8d0 SUB EDI,ECX
1481cf8d2 TEST EDI,EDI
1481cf8d4 JG 0x1481cf902
1481cf8d6 CMP byte ptr [0x14eab53c8],0x2
1481cf8dd JC 0x1481cf8f2
1481cf8df LEA RDX,[0x14cf7b750]
1481cf8e6 LEA RCX,[0x14eab53c8]
1481cf8ed CALL 0x140f24ba0
1481cf8f2 MOV RDI,qword ptr [RSP + 0x60]
1481cf8f7 MOVAPS XMM6,xmmword ptr [RSP + 0x40]
1481cf8fc ADD RSP,0x50
1481cf900 POP RBX
1481cf901 RET
1481cf902 CMP byte ptr [0x14eab53c8],0x3
1481cf909 JC 0x1481cf949
1481cf90b MOV dword ptr [RSP + 0x38],ECX
1481cf90f LEA RDX,[0x14cf7b7f8]
1481cf916 MOV dword ptr [RSP + 0x30],EAX
1481cf91a LEA RCX,[0x14eab53c8]
1481cf921 MOV EAX,dword ptr [RBX + 0x118]
1481cf927 XORPS XMM2,XMM2
1481cf92a MOV dword ptr [RSP + 0x28],EAX
1481cf92e MOV R9D,EDI
1481cf931 MOV EAX,dword ptr [RBX + 0x104]
1481cf937 CVTSS2SD XMM2,XMM6
1481cf93b MOV dword ptr [RSP + 0x20],EAX
1481cf93f MOVQ R8,XMM2
1481cf944 CALL 0x140f24ba0
1481cf949 LEA RDX,[RBX + 0x158]
1481cf950 MOV R9D,EDI
1481cf953 MOVAPS XMM2,XMM6
1481cf956 MOV RCX,RBX
1481cf959 MOV RDI,qword ptr [RSP + 0x60]
1481cf95e MOVAPS XMM6,xmmword ptr [RSP + 0x40]
1481cf963 ADD RSP,0x50
1481cf967 POP RBX
1481cf968 JMP 0x1481d1c90
1481cf96d CMP byte ptr [0x14eab53c8],0x3
1481cf974 JC 0x1481cf8f7
1481cf976 LEA RDX,[0x14cf7b5d8]
1481cf97d LEA RCX,[0x14eab53c8]
1481cf984 MOVAPS XMM6,xmmword ptr [RSP + 0x40]
1481cf989 ADD RSP,0x50
1481cf98d POP RBX
1481cf98e JMP 0x140f24ba0
*/

/* 1481cf9a0 ApplyStrokeCountModifier */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ApplyStrokeCountModifier(longlong param_1,int param_2)

{
  ulonglong *puVar1;
  undefined8 *puVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  double *pdVar8;
  ulonglong uVar9;
  code *pcVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  ulonglong uVar15;
  char cVar16;
  uint uVar17;
  longlong *plVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  uint uVar23;
  longlong lVar24;
  uint uVar25;
  undefined8 unaff_retaddr;
  ulonglong uStackX_20;
  undefined8 in_stack_fffffffffffffec8;
  undefined4 uVar26;
  undefined8 in_stack_fffffffffffffed0;
  undefined4 uVar27;
  undefined8 in_stack_fffffffffffffed8;
  undefined4 uVar28;
  double dStack_108;
  double dStack_100;
  uint uStack_f8;
  undefined4 uStack_f4;
  double dStack_f0;
  int iStack_e8;
  float fStack_e4;
  longlong lStack_d8;
  undefined8 uStack_d0;
  longlong lStack_c8;
  ulonglong uStack_c0;
  longlong *plStack_b8;
  undefined8 uStack_b0;
  longlong lStack_a8;
  undefined8 uStack_a0;
  
  uVar26 = (undefined4)((ulonglong)in_stack_fffffffffffffec8 >> 0x20);
  uVar27 = (undefined4)((ulonglong)in_stack_fffffffffffffed0 >> 0x20);
  uVar28 = (undefined4)((ulonglong)in_stack_fffffffffffffed8 >> 0x20);
  if ((((*(char *)(param_1 + 0x108) == '\0') || (param_2 < 1)) ||
      (iVar20 = *(int *)(param_1 + 0xf0), iVar20 == 0)) ||
     (iVar19 = *(int *)(param_1 + 0x110), iVar20 <= iVar19)) {
    if (DAT_14eab53c8 < 3) {
      return;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78f10);
    return;
  }
  iVar21 = *(int *)(param_1 + 0x118);
  iVar22 = iVar19 - iVar21;
  iVar5 = *(int *)(param_1 + 0x104);
  iVar20 = iVar20 - iVar19;
  if ((((1 < DAT_14eab53c8) &&
       (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf78fc0), 1 < DAT_14eab53c8)) &&
      ((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79028,iVar19), 1 < DAT_14eab53c8 &&
       ((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf790a8,iVar21), 1 < DAT_14eab53c8 &&
        (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79130,iVar22), 1 < DAT_14eab53c8)))))) &&
     (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf791a0,iVar5 - iVar21), 1 < DAT_14eab53c8)) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79218,iVar20);
  }
  uVar23 = iVar20 * param_2;
  uVar6 = *(undefined4 *)(param_1 + 0x104);
  iVar19 = iVar19 + uVar23;
  if ((((1 < DAT_14eab53c8) &&
       (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79290), 1 < DAT_14eab53c8)) &&
      (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf792f8,uVar6), 1 < DAT_14eab53c8)) &&
     ((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79350,param_2,iVar20), 1 < DAT_14eab53c8 &&
      (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf793e0,iVar21,iVar22,CONCAT44(uVar26,iVar20),
                           CONCAT44(uVar27,param_2),CONCAT44(uVar28,iVar19)), 1 < DAT_14eab53c8))))
  {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79488,iVar19);
  }
  *(int *)(param_1 + 0x104) = iVar19;
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf794e0,uVar6,iVar19,iVar22);
  }
  uVar25 = 0;
  lStack_d8 = 0;
  uStack_d0 = 0;
  lStack_c8 = 0;
  uStack_c0 = 0;
  plStack_b8 = (longlong *)0x0;
  uStack_b0 = 0;
  lStack_a8 = 0;
  uStack_a0 = 0;
  if (*(int *)(param_1 + 200) < 1) {
    if (1 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79630);
    }
  }
  else {
    puVar1 = (ulonglong *)(param_1 + 0xe8);
    uVar7 = *(uint *)(param_1 + 0x110);
    uVar17 = uVar25;
    if ((int)uVar7 < *(int *)(param_1 + 0xf0)) {
      uVar17 = ~uVar7 >> 0x1f;
    }
    if ((uVar17 == 0) &&
       (cVar16 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                     &UNK_14bce6ef0,(longlong)(int)uVar7,
                                     (longlong)*(int *)(param_1 + 0xf0)), cVar16 != '\0')) {
      pcVar10 = (code *)swi(3);
      (*pcVar10)();
      return;
    }
    uVar7 = *(uint *)(*puVar1 + 0x10 + (longlong)(int)uVar7 * 0x28);
    if (((int)uVar7 < 0) || (*(int *)(param_1 + 200) <= (int)uVar7)) {
      if ((*(int *)(param_1 + 200) < 1) &&
         (cVar16 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                       &UNK_14bce6ef0,0,(longlong)*(int *)(param_1 + 200)),
         cVar16 != '\0')) {
        pcVar10 = (code *)swi(3);
        (*pcVar10)();
        return;
      }
      func_0x0001481cf600(&lStack_d8,*(undefined8 *)(param_1 + 0xc0));
      if (2 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79598);
      }
    }
    else {
      uVar17 = uVar25;
      if ((int)uVar7 < *(int *)(param_1 + 200)) {
        uVar17 = ~uVar7 >> 0x1f;
      }
      if ((uVar17 == 0) &&
         (cVar16 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                       &UNK_14bce6ef0,(longlong)(int)uVar7,
                                       (longlong)*(int *)(param_1 + 200)), cVar16 != '\0')) {
        pcVar10 = (code *)swi(3);
        (*pcVar10)();
        return;
      }
      func_0x0001481cf600(&lStack_d8,(longlong)(int)uVar7 * 0x40 + *(longlong *)(param_1 + 0xc0));
    }
    fVar3 = *(float *)(param_1 + 0x10c);
    if (((*(char *)(param_1 + 0x108) == '\0') || (*(int *)(param_1 + 0xf0) == 0)) ||
       ((int)uStack_c0 == 0)) {
      if (DAT_14eab53c8 < 3) goto LAB_1481d01d7;
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf798f8);
    }
    else {
      if (2 < DAT_14eab53c8) {
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf799a0,*(undefined4 *)(param_1 + 0x110),uVar23,
                            (double)fVar3,*(undefined8 *)(param_1 + 0x1a0));
      }
      dVar12 = (double)func_0x0001481d12e0(param_1);
      uVar7 = *(uint *)(param_1 + 0x110);
      if ((-1 < (int)uVar7) && ((int)uVar7 < *(int *)(param_1 + 0xf0))) {
        if ((int)uVar7 < *(int *)(param_1 + 0xf0)) {
          uVar25 = ~uVar7 >> 0x1f;
        }
        if ((uVar25 == 0) &&
           (cVar16 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                         &UNK_14bce6ef0,(longlong)(int)uVar7,
                                         (longlong)*(int *)(param_1 + 0xf0)), cVar16 != '\0')) {
          pcVar10 = (code *)swi(3);
          (*pcVar10)();
          return;
        }
        uVar25 = *(uint *)(*puVar1 + 0x10 + (longlong)(int)uVar7 * 0x28);
      }
      iVar20 = *(int *)(param_1 + 0x110);
      iVar19 = *(int *)(param_1 + 0xf0) - iVar20;
      if (iVar19 != 0) {
        iVar21 = (*(int *)(param_1 + 0xf0) - iVar20) - iVar19;
        if (iVar21 != 0) {
          func_0x00014b89503a(*puVar1 + (longlong)iVar20 * 0x28,
                              *puVar1 + (longlong)*(int *)(param_1 + 0xf0) * 0x28,
                              (longlong)iVar21 * 0x28);
        }
        *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) - iVar19;
        func_0x0001481d21b0(puVar1);
      }
      uVar15 = uStack_c0;
      uVar7 = _DAT_14bd17880;
      dVar12 = dVar12 + _DAT_14bd774b8;
      iVar19 = (int)uStack_c0;
      iVar20 = *(int *)(param_1 + 0x110);
      if (0 < (int)uVar23) {
        dVar13 = _DAT_14bce5180 / (double)fVar3;
        uStackX_20 = (ulonglong)uVar23;
        while( true ) {
          iVar20 = iVar20 + 1;
          iVar21 = (int)uStack_c0;
          if (((int)uVar25 < 0) || ((int)uStack_c0 <= (int)uVar25)) {
            if (1 < DAT_14eab53c8) {
              func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79aa8,uVar25,uVar15 & 0xffffffff);
              iVar21 = (int)uStack_c0;
            }
            uVar25 = 0;
          }
          uVar17 = 0;
          if ((int)uVar25 < iVar21) {
            uVar17 = ~uVar25 >> 0x1f;
          }
          if ((uVar17 == 0) &&
             (cVar16 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                           &UNK_14bce6ef0,(longlong)(int)uVar25,(longlong)iVar21),
             cVar16 != '\0')) {
            pcVar10 = (code *)swi(3);
            (*pcVar10)();
            return;
          }
          fVar4 = *(float *)(lStack_c8 + (longlong)(int)uVar25 * 4);
          if (1 < DAT_14eab53c8) {
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79b58,(double)fVar4,uVar25);
          }
          dVar11 = (double)(float)((uint)fVar4 & uVar7) * *(double *)(param_1 + 0x1a0) * dVar13;
          dVar14 = *(double *)(param_1 + 0xe0);
          if (*(double *)(param_1 + 0xe0) <= dVar11) {
            dVar14 = dVar11;
          }
          dStack_100 = dVar12 + *(double *)(param_1 + 0x150);
          pdVar8 = (double *)*puVar1;
          dStack_108 = dVar12;
          uStack_f8 = uVar25;
          dStack_f0 = dVar14;
          iStack_e8 = iVar20;
          fStack_e4 = fVar4;
          if (((pdVar8 <= &dStack_108) &&
              (&dStack_108 < pdVar8 + (longlong)*(int *)(param_1 + 0xf4) * 5)) &&
             (cVar16 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                           &UNK_14bce6d80,&dStack_108,pdVar8,
                                           (longlong)*(int *)(param_1 + 0xf4),
                                           (longlong)*(int *)(param_1 + 0xf0),0x28), cVar16 != '\0')
             ) {
            pcVar10 = (code *)swi(3);
            (*pcVar10)();
            return;
          }
          iVar21 = *(int *)(param_1 + 0xf0);
          lVar24 = (longlong)iVar21;
          *(uint *)(param_1 + 0xf0) = iVar21 + 1U;
          if (*(uint *)(param_1 + 0xf4) < iVar21 + 1U) {
            func_0x0001481d2100(puVar1,iVar21);
          }
          uVar9 = *puVar1;
          pdVar8 = (double *)(uVar9 + lVar24 * 0x28);
          *pdVar8 = dStack_108;
          pdVar8[1] = dStack_100;
          puVar2 = (undefined8 *)(uVar9 + 0x10 + lVar24 * 0x28);
          *puVar2 = CONCAT44(uStack_f4,uStack_f8);
          puVar2[1] = dStack_f0;
          *(ulonglong *)(uVar9 + 0x20 + lVar24 * 0x28) = CONCAT44(fStack_e4,iStack_e8);
          dVar12 = dVar12 + dVar14;
          uVar25 = (int)(uVar25 + 1) % iVar19;
          uStackX_20 = uStackX_20 - 1;
          if (uStackX_20 == 0) break;
        }
      }
      *(float *)(param_1 + 0x10c) = fVar3;
    }
    if (((2 < DAT_14eab53c8) &&
        (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf796b8), 2 < DAT_14eab53c8)) &&
       ((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79728,iVar22), 2 < DAT_14eab53c8 &&
        ((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79798,uVar23), 2 < DAT_14eab53c8 &&
         (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79808,*(undefined4 *)(param_1 + 0x104)),
         2 < DAT_14eab53c8)))))) {
      iVar20 = *(int *)(param_1 + 0x104) - *(int *)(param_1 + 0x118);
      if (iVar20 < 0) {
        iVar20 = 0;
      }
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79888,iVar20);
    }
  }
LAB_1481d01d7:
  if (lStack_a8 != 0) {
    func_0x000140e282f0();
  }
  plVar18 = plStack_b8;
  for (iVar20 = (int)uStack_b0; iVar20 != 0; iVar20 = iVar20 + -1) {
    if (*plVar18 != 0) {
      func_0x000140e282f0();
    }
    plVar18 = plVar18 + 2;
  }
  if (plStack_b8 != (longlong *)0x0) {
    func_0x000140e282f0();
  }
  if (lStack_c8 != 0) {
    func_0x000140e282f0();
  }
  if (lStack_d8 != 0) {
    func_0x000140e282f0();
  }
  return;
}


/* Instruction evidence:
1481cf9a0 MOV RAX,RSP
1481cf9a3 MOV qword ptr [RAX + 0x10],RBX
1481cf9a7 PUSH RBP
1481cf9a8 PUSH RSI
1481cf9a9 PUSH RDI
1481cf9aa PUSH R12
1481cf9ac PUSH R13
1481cf9ae PUSH R14
1481cf9b0 PUSH R15
1481cf9b2 LEA RBP,[RAX + -0x58]
1481cf9b6 SUB RSP,0x120
1481cf9bd MOVAPS xmmword ptr [RAX + -0x48],XMM6
1481cf9c1 MOVAPS xmmword ptr [RAX + -0x58],XMM7
1481cf9c5 MOVAPS xmmword ptr [RAX + -0x68],XMM8
1481cf9ca MOVAPS xmmword ptr [RAX + -0x78],XMM9
1481cf9cf MOVAPS xmmword ptr [RAX + -0x88],XMM10
1481cf9d7 MOVAPS xmmword ptr [RAX + -0x98],XMM11
1481cf9df MOV R14D,EDX
1481cf9e2 MOV RBX,RCX
1481cf9e5 CMP byte ptr [RCX + 0x108],0x0
1481cf9ec JZ 0x1481d0237
1481cf9f2 TEST EDX,EDX
1481cf9f4 JLE 0x1481d0237
1481cf9fa MOV EDI,dword ptr [RCX + 0xf0]
1481cfa00 TEST EDI,EDI
1481cfa02 JZ 0x1481d0237
1481cfa08 MOV ESI,dword ptr [RCX + 0x110]
1481cfa0e CMP ESI,EDI
1481cfa10 JGE 0x1481d0237
1481cfa16 MOV R15D,dword ptr [RCX + 0x118]
1481cfa1d MOV R13D,ESI
1481cfa20 SUB R13D,R15D
1481cfa23 MOV dword ptr [RBP + 0x60],R13D
1481cfa27 MOV R12D,dword ptr [RCX + 0x104]
1481cfa2e SUB R12D,R15D
1481cfa31 SUB EDI,ESI
1481cfa33 MOVZX EAX,byte ptr [0x14eab53c8]
1481cfa3a CMP AL,0x2
1481cfa3c JC 0x1481cfb09
1481cfa42 LEA RDX,[0x14cf78fc0]
1481cfa49 LEA RCX,[0x14eab53c8]
1481cfa50 CALL 0x140f24ba0
1481cfa55 MOVZX EAX,byte ptr [0x14eab53c8]
1481cfa5c CMP AL,0x2
1481cfa5e JC 0x1481cfb09
1481cfa64 MOV R8D,ESI
1481cfa67 LEA RDX,[0x14cf79028]
1481cfa6e LEA RCX,[0x14eab53c8]
1481cfa75 CALL 0x140f24ba0
1481cfa7a MOVZX EAX,byte ptr [0x14eab53c8]
1481cfa81 CMP AL,0x2
1481cfa83 JC 0x1481cfb09
1481cfa89 MOV R8D,R15D
1481cfa8c LEA RDX,[0x14cf790a8]
1481cfa93 LEA RCX,[0x14eab53c8]
1481cfa9a CALL 0x140f24ba0
1481cfa9f MOVZX EAX,byte ptr [0x14eab53c8]
1481cfaa6 CMP AL,0x2
1481cfaa8 JC 0x1481cfb09
1481cfaaa MOV R8D,R13D
1481cfaad LEA RDX,[0x14cf79130]
1481cfab4 LEA RCX,[0x14eab53c8]
1481cfabb CALL 0x140f24ba0
1481cfac0 MOVZX EAX,byte ptr [0x14eab53c8]
1481cfac7 CMP AL,0x2
1481cfac9 JC 0x1481cfb09
1481cfacb MOV R8D,R12D
1481cface LEA RDX,[0x14cf791a0]
1481cfad5 LEA RCX,[0x14eab53c8]
1481cfadc CALL 0x140f24ba0
1481cfae1 MOVZX EAX,byte ptr [0x14eab53c8]
1481cfae8 CMP AL,0x2
1481cfaea JC 0x1481cfb09
1481cfaec MOV R8D,EDI
1481cfaef LEA RDX,[0x14cf79218]
1481cfaf6 LEA RCX,[0x14eab53c8]
1481cfafd CALL 0x140f24ba0
1481cfb02 MOVZX EAX,byte ptr [0x14eab53c8]
1481cfb09 MOV R13D,EDI
1481cfb0c IMUL R13D,R14D
1481cfb10 MOV dword ptr [RBP + 0x70],R13D
1481cfb14 MOV R12D,dword ptr [RBX + 0x104]
1481cfb1b ADD ESI,R13D
1481cfb1e CMP AL,0x2
1481cfb20 JC 0x1481cfbd1
1481cfb26 LEA RDX,[0x14cf79290]
1481cfb2d LEA RCX,[0x14eab53c8]
1481cfb34 CALL 0x140f24ba0
1481cfb39 CMP byte ptr [0x14eab53c8],0x2
1481cfb40 JC 0x1481cfbd1
1481cfb46 MOV R8D,R12D
1481cfb49 LEA RDX,[0x14cf792f8]
1481cfb50 LEA RCX,[0x14eab53c8]
1481cfb57 CALL 0x140f24ba0
1481cfb5c CMP byte ptr [0x14eab53c8],0x2
1481cfb63 JC 0x1481cfbd1
1481cfb65 MOV R9D,EDI
1481cfb68 MOV R8D,R14D
1481cfb6b LEA RDX,[0x14cf79350]
1481cfb72 LEA RCX,[0x14eab53c8]
1481cfb79 CALL 0x140f24ba0
1481cfb7e CMP byte ptr [0x14eab53c8],0x2
1481cfb85 JC 0x1481cfbd1
1481cfb87 MOV dword ptr [RSP + 0x30],ESI
1481cfb8b MOV dword ptr [RSP + 0x28],R14D
1481cfb90 MOV dword ptr [RSP + 0x20],EDI
1481cfb94 MOV EDI,dword ptr [RBP + 0x60]
1481cfb97 MOV R9D,EDI
1481cfb9a MOV R8D,R15D
1481cfb9d LEA RDX,[0x14cf793e0]
1481cfba4 LEA RCX,[0x14eab53c8]
1481cfbab CALL 0x140f24ba0
1481cfbb0 CMP byte ptr [0x14eab53c8],0x2
1481cfbb7 JC 0x1481cfbd4
1481cfbb9 MOV R8D,ESI
1481cfbbc LEA RDX,[0x14cf79488]
1481cfbc3 LEA RCX,[0x14eab53c8]
1481cfbca CALL 0x140f24ba0
1481cfbcf JMP 0x1481cfbd4
1481cfbd1 MOV EDI,dword ptr [RBP + 0x60]
1481cfbd4 MOV dword ptr [RBX + 0x104],ESI
1481cfbda MOVZX EAX,byte ptr [0x14eab53c8]
1481cfbe1 CMP AL,0x3
1481cfbe3 JC 0x1481cfc09
1481cfbe5 MOV dword ptr [RSP + 0x20],EDI
1481cfbe9 MOV R9D,ESI
1481cfbec MOV R8D,R12D
1481cfbef LEA RDX,[0x14cf794e0]
1481cfbf6 LEA RCX,[0x14eab53c8]
1481cfbfd CALL 0x140f24ba0
1481cfc02 MOVZX EAX,byte ptr [0x14eab53c8]
1481cfc09 XOR R15D,R15D
1481cfc0c MOV qword ptr [RBP + -0x80],R15
1481cfc10 MOV qword ptr [RBP + -0x78],R15
1481cfc14 MOV qword ptr [RBP + -0x70],R15
1481cfc18 MOV qword ptr [RBP + -0x68],R15
1481cfc1c MOV qword ptr [RBP + -0x60],R15
1481cfc20 MOV qword ptr [RBP + -0x58],R15
1481cfc24 MOV qword ptr [RBP + -0x50],R15
1481cfc28 MOV qword ptr [RBP + -0x48],R15
1481cfc2c CMP dword ptr [RBX + 0xc8],R15D
1481cfc33 JLE 0x1481d01bf
1481cfc39 LEA RSI,[RBX + 0xe8]
1481cfc40 MOVSXD RDI,dword ptr [RBX + 0x110]
1481cfc47 MOVSXD RDX,dword ptr [RSI + 0x8]
1481cfc4b MOV EAX,EDI
1481cfc4d NOT EAX
1481cfc4f SHR EAX,0x1f
1481cfc52 MOV ECX,R15D
1481cfc55 CMP EDI,EDX
1481cfc57 CMOVL ECX,EAX
1481cfc5a LEA R12,[0x14bce6ef0]
1481cfc61 TEST ECX,ECX
1481cfc63 JNZ 0x1481cfc97
1481cfc65 MOV R9,qword ptr [RBP + 0x58]
1481cfc69 MOV qword ptr [RSP + 0x30],RDX
1481cfc6e MOV qword ptr [RSP + 0x28],RDI
1481cfc73 MOV qword ptr [RSP + 0x20],R12
1481cfc78 MOV R8D,0x303
1481cfc7e LEA RDX,[0x14cf27ac0]
1481cfc85 LEA RCX,[0x14bce6f68]
1481cfc8c CALL 0x140f8dfd0
1481cfc91 TEST AL,AL
1481cfc93 JZ 0x1481cfc97
1481cfc95 NOP
1481cfc96 INT3
1481cfc97 LEA RCX,[RDI + RDI*0x4]
1481cfc9b MOV RAX,qword ptr [RSI]
1481cfc9e MOVSXD RDI,dword ptr [RAX + RCX*0x8 + 0x10]
1481cfca3 TEST EDI,EDI
1481cfca5 JS 0x1481cfd14
1481cfca7 CMP EDI,dword ptr [RBX + 0xc8]
1481cfcad JGE 0x1481cfd14
1481cfcaf MOVSXD RDX,dword ptr [RBX + 0xc8]
1481cfcb6 MOV ECX,EDI
1481cfcb8 NOT ECX
1481cfcba SHR ECX,0x1f
1481cfcbd MOV EAX,R15D
1481cfcc0 CMP EDI,EDX
1481cfcc2 CMOVL EAX,ECX
1481cfcc5 TEST EAX,EAX
1481cfcc7 JNZ 0x1481cfcfb
1481cfcc9 MOV R9,qword ptr [RBP + 0x58]
1481cfccd MOV qword ptr [RSP + 0x30],RDX
1481cfcd2 MOV qword ptr [RSP + 0x28],RDI
1481cfcd7 MOV qword ptr [RSP + 0x20],R12
1481cfcdc MOV R8D,0x303
1481cfce2 LEA RDX,[0x14cf27ac0]
1481cfce9 LEA RCX,[0x14bce6f68]
1481cfcf0 CALL 0x140f8dfd0
1481cfcf5 TEST AL,AL
1481cfcf7 JZ 0x1481cfcfb
1481cfcf9 NOP
1481cfcfa INT3
1481cfcfb MOV RDX,RDI
1481cfcfe SHL RDX,0x6
1481cfd02 ADD RDX,qword ptr [RBX + 0xc0]
1481cfd09 LEA RCX,[RBP + -0x80]
1481cfd0d CALL 0x1481cf600
1481cfd12 JMP 0x1481cfd7f
1481cfd14 MOVSXD RAX,dword ptr [RBX + 0xc8]
1481cfd1b TEST EAX,EAX
1481cfd1d JG 0x1481cfd51
1481cfd1f MOV R9,qword ptr [RBP + 0x58]
1481cfd23 MOV qword ptr [RSP + 0x30],RAX
1481cfd28 MOV qword ptr [RSP + 0x28],R15
1481cfd2d MOV qword ptr [RSP + 0x20],R12
1481cfd32 MOV R8D,0x303
1481cfd38 LEA RDX,[0x14cf27ac0]
1481cfd3f LEA RCX,[0x14bce6f68]
1481cfd46 CALL 0x140f8dfd0
1481cfd4b TEST AL,AL
1481cfd4d JZ 0x1481cfd51
1481cfd4f NOP
1481cfd50 INT3
1481cfd51 MOV RDX,qword ptr [RBX + 0xc0]
1481cfd58 LEA RCX,[RBP + -0x80]
1481cfd5c CALL 0x1481cf600
1481cfd61 MOVZX EAX,byte ptr [0x14eab53c8]
1481cfd68 CMP AL,0x3
1481cfd6a JC 0x1481cfd86
1481cfd6c LEA RDX,[0x14cf79598]
1481cfd73 LEA RCX,[0x14eab53c8]
1481cfd7a CALL 0x140f24ba0
1481cfd7f MOVZX EAX,byte ptr [0x14eab53c8]
1481cfd86 MOVSS XMM10,dword ptr [RBX + 0x10c]
1481cfd8f CMP byte ptr [RBX + 0x108],0x0
1481cfd96 JZ 0x1481d00ea
1481cfd9c CMP dword ptr [RBX + 0xf0],0x0
1481cfda3 JZ 0x1481d00ea
1481cfda9 CMP dword ptr [RBP + -0x68],0x0
1481cfdad JZ 0x1481d00ea
1481cfdb3 CMP AL,0x3
1481cfdb5 JC 0x1481cfdec
1481cfdb7 CVTPS2PD XMM1,XMM10
1481cfdbb MOVSD XMM0,qword ptr [RBX + 0x1a0]
1481cfdc3 MOVSD qword ptr [RSP + 0x28],XMM0
1481cfdc9 MOVSD qword ptr [RSP + 0x20],XMM1
1481cfdcf MOV R9D,R13D
1481cfdd2 MOV R8D,dword ptr [RBX + 0x110]
1481cfdd9 LEA RDX,[0x14cf799a0]
1481cfde0 LEA RCX,[0x14eab53c8]
1481cfde7 CALL 0x140f24ba0
1481cfdec MOV RCX,RBX
1481cfdef CALL 0x1481d12e0
1481cfdf4 MOVAPS XMM8,XMM0
1481cfdf8 MOV EDI,R15D
1481cfdfb MOVSXD R14,dword ptr [RBX + 0x110]
1481cfe02 TEST R14D,R14D
1481cfe05 JS 0x1481cfe66
1481cfe07 CMP R14D,dword ptr [RBX + 0xf0]
1481cfe0e JGE 0x1481cfe66
1481cfe10 MOVSXD RDX,dword ptr [RSI + 0x8]
1481cfe14 MOV ECX,R14D
1481cfe17 NOT ECX
1481cfe19 SHR ECX,0x1f
1481cfe1c MOV EAX,R15D
1481cfe1f CMP R14D,EDX
1481cfe22 CMOVL EAX,ECX
1481cfe25 TEST EAX,EAX
1481cfe27 JNZ 0x1481cfe5b
1481cfe29 MOV R9,qword ptr [RBP + 0x58]
1481cfe2d MOV qword ptr [RSP + 0x30],RDX
1481cfe32 MOV qword ptr [RSP + 0x28],R14
1481cfe37 MOV qword ptr [RSP + 0x20],R12
1481cfe3c MOV R8D,0x303
1481cfe42 LEA RDX,[0x14cf27ac0]
1481cfe49 LEA RCX,[0x14bce6f68]
1481cfe50 CALL 0x140f8dfd0
1481cfe55 TEST AL,AL
1481cfe57 JZ 0x1481cfe5b
1481cfe59 NOP
1481cfe5a INT3
1481cfe5b LEA RCX,[R14 + R14*0x4]
1481cfe5f MOV RAX,qword ptr [RSI]
1481cfe62 MOV EDI,dword ptr [RAX + RCX*0x8 + 0x10]
1481cfe66 MOVSXD RAX,dword ptr [RBX + 0xf0]
1481cfe6d MOVSXD R10,dword ptr [RBX + 0x110]
1481cfe74 MOV R14D,EAX
1481cfe77 SUB R14D,R10D
1481cfe7a JZ 0x1481cfeb7
1481cfe7c MOV R9D,dword ptr [RSI + 0x8]
1481cfe80 SUB R9D,R10D
1481cfe83 SUB R9D,R14D
1481cfe86 JZ 0x1481cfeab
1481cfe88 MOV R8,qword ptr [RSI]
1481cfe8b LEA RCX,[RAX + RAX*0x4]
1481cfe8f LEA RDX,[R8 + RCX*0x8]
1481cfe93 LEA RCX,[R10 + R10*0x4]
1481cfe97 LEA RCX,[R8 + RCX*0x8]
1481cfe9b MOVSXD RAX,R9D
1481cfe9e LEA R8,[RAX + RAX*0x4]
1481cfea2 SHL R8,0x3
1481cfea6 CALL 0x14b89503a
1481cfeab SUB dword ptr [RSI + 0x8],R14D
1481cfeaf MOV RCX,RSI
1481cfeb2 CALL 0x1481d21b0
1481cfeb7 ADDSD XMM8,qword ptr [0x14bd774b8]
1481cfec0 MOV EDX,dword ptr [RBP + -0x68]
1481cfec3 MOV R12D,EDX
1481cfec6 MOV R15D,dword ptr [RBX + 0x110]
1481cfecd INC R15D
1481cfed0 TEST R13D,R13D
1481cfed3 JLE 0x1481d00dc
1481cfed9 CVTPS2PD XMM0,XMM10
1481cfedd MOVSD XMM9,qword ptr [0x14bce5180]
1481cfee6 DIVSD XMM9,XMM0
1481cfeeb MOV EAX,R13D
1481cfeee MOV qword ptr [RBP + 0x78],RAX
1481cfef2 MOVSS XMM11,dword ptr [0x14bd17880]
1481cfefb LEA R13,[0x14bce6ef0]
1481cff02 LEA R14,[0x14bce6d80]
1481cff09 TEST EDI,EDI
1481cff0b JS 0x1481cff11
1481cff0d CMP EDI,EDX
1481cff0f JL 0x1481cff38
1481cff11 CMP byte ptr [0x14eab53c8],0x2
1481cff18 JC 0x1481cff36
1481cff1a MOV R9D,R12D
1481cff1d MOV R8D,EDI
1481cff20 LEA RDX,[0x14cf79aa8]
1481cff27 LEA RCX,[0x14eab53c8]
1481cff2e CALL 0x140f24ba0
1481cff33 MOV EDX,dword ptr [RBP + -0x68]
1481cff36 XOR EDI,EDI
1481cff38 MOV ECX,EDI
1481cff3a NOT ECX
1481cff3c SHR ECX,0x1f
1481cff3f XOR EAX,EAX
1481cff41 CMP EDI,EDX
1481cff43 CMOVL EAX,ECX
1481cff46 TEST EAX,EAX
1481cff48 JNZ 0x1481cff82
1481cff4a MOVSXD RAX,EDX
1481cff4d MOVSXD RCX,EDI
1481cff50 MOV R9,qword ptr [RBP + 0x58]
1481cff54 MOV qword ptr [RSP + 0x30],RAX
1481cff59 MOV qword ptr [RSP + 0x28],RCX
1481cff5e MOV qword ptr [RSP + 0x20],R13
1481cff63 MOV R8D,0x303
1481cff69 LEA RDX,[0x14cf27ac0]
1481cff70 LEA RCX,[0x14bce6f68]
1481cff77 CALL 0x140f8dfd0
1481cff7c TEST AL,AL
1481cff7e JZ 0x1481cff82
1481cff80 NOP
1481cff81 INT3
1481cff82 MOVSXD RCX,EDI
1481cff85 MOV RAX,qword ptr [RBP + -0x70]
1481cff89 MOVSS XMM6,dword ptr [RAX + RCX*0x4]
1481cff8e CMP byte ptr [0x14eab53c8],0x2
1481cff95 JC 0x1481cffb5
1481cff97 CVTPS2PD XMM2,XMM6
1481cff9a MOV R9D,EDI
1481cff9d MOVQ R8,XMM2
1481cffa2 LEA RDX,[0x14cf79b58]
1481cffa9 LEA RCX,[0x14eab53c8]
1481cffb0 CALL 0x140f24ba0
1481cffb5 MOVSD XMM7,qword ptr [RBX + 0xe0]
1481cffbd MOVAPS XMM0,XMM6
1481cffc0 ANDPS XMM0,XMM11
1481cffc4 CVTPS2PD XMM1,XMM0
1481cffc7 MULSD XMM1,qword ptr [RBX + 0x1a0]
1481cffcf MULSD XMM1,XMM9
1481cffd4 MAXSD XMM7,XMM1
1481cffd8 MOVAPS XMM0,XMM8
1481cffdc ADDSD XMM0,qword ptr [RBX + 0x150]
1481cffe4 MOVSD qword ptr [RSP + 0x50],XMM8
1481cffeb MOV dword ptr [RSP + 0x60],EDI
1481cffef MOVSD qword ptr [RSP + 0x68],XMM7
1481cfff5 MOV dword ptr [RSP + 0x70],R15D
1481cfffa INC R15D
1481cfffd MOVSS dword ptr [RSP + 0x74],XMM6
1481d0003 MOVSD qword ptr [RSP + 0x58],XMM0
1481d0009 MOV R8,qword ptr [RSI]
1481d000c LEA RAX,[RSP + 0x50]
1481d0011 CMP RAX,R8
1481d0014 JC 0x1481d007a
1481d0016 MOVSXD RDX,dword ptr [RSI + 0xc]
1481d001a LEA RAX,[RDX + RDX*0x4]
1481d001e LEA RCX,[R8 + RAX*0x8]
1481d0022 LEA RAX,[RSP + 0x50]
1481d0027 CMP RAX,RCX
1481d002a JNC 0x1481d007a
1481d002c MOVSXD RAX,dword ptr [RSI + 0x8]
1481d0030 MOV R9,qword ptr [RBP + 0x58]
1481d0034 MOV qword ptr [RSP + 0x48],0x28
1481d003d MOV qword ptr [RSP + 0x40],RAX
1481d0042 MOV qword ptr [RSP + 0x38],RDX
1481d0047 MOV qword ptr [RSP + 0x30],R8
1481d004c LEA RAX,[RSP + 0x50]
1481d0051 MOV qword ptr [RSP + 0x28],RAX
1481d0056 MOV qword ptr [RSP + 0x20],R14
1481d005b MOV R8D,0x63e
1481d0061 LEA RDX,[0x14cf27ac0]
1481d0068 LEA RCX,[0x14bce6eb8]
1481d006f CALL 0x140f8dfd0
1481d0074 TEST AL,AL
1481d0076 JZ 0x1481d007a
1481d0078 NOP
1481d0079 INT3
1481d007a MOVSXD R14,dword ptr [RSI + 0x8]
1481d007e LEA EAX,[R14 + 0x1]
1481d0082 MOV dword ptr [RSI + 0x8],EAX
1481d0085 CMP EAX,dword ptr [RSI + 0xc]
1481d0088 JBE 0x1481d0095
1481d008a MOV EDX,R14D
1481d008d MOV RCX,RSI
1481d0090 CALL 0x1481d2100
1481d0095 LEA RCX,[R14 + R14*0x4]
1481d0099 MOV RAX,qword ptr [RSI]
1481d009c MOVUPS XMM0,xmmword ptr [RSP + 0x50]
1481d00a1 MOVUPS xmmword ptr [RAX + RCX*0x8],XMM0
1481d00a5 MOVUPS XMM1,xmmword ptr [RSP + 0x60]
1481d00aa MOVUPS xmmword ptr [RAX + RCX*0x8 + 0x10],XMM1
1481d00af MOVSD XMM0,qword ptr [RSP + 0x70]
1481d00b5 MOVSD qword ptr [RAX + RCX*0x8 + 0x20],XMM0
1481d00bb ADDSD XMM8,XMM7
1481d00c0 LEA EAX,[RDI + 0x1]
1481d00c3 CDQ
1481d00c4 IDIV R12D
1481d00c7 MOV EDI,EDX
1481d00c9 SUB qword ptr [RBP + 0x78],0x1
1481d00ce JZ 0x1481d00d8
1481d00d0 MOV EDX,dword ptr [RBP + -0x68]
1481d00d3 JMP 0x1481cff02
1481d00d8 MOV R13D,dword ptr [RBP + 0x70]
1481d00dc MOVSS dword ptr [RBX + 0x10c],XMM10
1481d00e5 XOR R15D,R15D
1481d00e8 JMP 0x1481d0105
1481d00ea CMP AL,0x3
1481d00ec JC 0x1481d01d7
1481d00f2 LEA RDX,[0x14cf798f8]
1481d00f9 LEA RCX,[0x14eab53c8]
1481d0100 CALL 0x140f24ba0
1481d0105 CMP byte ptr [0x14eab53c8],0x3
1481d010c JC 0x1481d01d7
1481d0112 LEA RDX,[0x14cf796b8]
1481d0119 LEA RCX,[0x14eab53c8]
1481d0120 CALL 0x140f24ba0
1481d0125 CMP byte ptr [0x14eab53c8],0x3
1481d012c JC 0x1481d01d7
1481d0132 MOV R8D,dword ptr [RBP + 0x60]
1481d0136 LEA RDX,[0x14cf79728]
1481d013d LEA RCX,[0x14eab53c8]
1481d0144 CALL 0x140f24ba0
1481d0149 CMP byte ptr [0x14eab53c8],0x3
1481d0150 JC 0x1481d01d7
1481d0156 MOV R8D,R13D
1481d0159 LEA RDX,[0x14cf79798]
1481d0160 LEA RCX,[0x14eab53c8]
1481d0167 CALL 0x140f24ba0
1481d016c CMP byte ptr [0x14eab53c8],0x3
1481d0173 JC 0x1481d01d7
1481d0175 MOV R8D,dword ptr [RBX + 0x104]
1481d017c LEA RDX,[0x14cf79808]
1481d0183 LEA RCX,[0x14eab53c8]
1481d018a CALL 0x140f24ba0
1481d018f CMP byte ptr [0x14eab53c8],0x3
1481d0196 JC 0x1481d01d7
1481d0198 MOV R8D,dword ptr [RBX + 0x104]
1481d019f SUB R8D,dword ptr [RBX + 0x118]
1481d01a6 CMOVS R8D,R15D
1481d01aa LEA RDX,[0x14cf79888]
1481d01b1 LEA RCX,[0x14eab53c8]
1481d01b8 CALL 0x140f24ba0
1481d01bd JMP 0x1481d01d7
1481d01bf CMP AL,0x2
1481d01c1 JC 0x1481d01d7
1481d01c3 LEA RDX,[0x14cf79630]
1481d01ca LEA RCX,[0x14eab53c8]
1481d01d1 CALL 0x140f24ba0
1481d01d6 NOP
1481d01d7 MOV RCX,qword ptr [RBP + -0x50]
1481d01db TEST RCX,RCX
1481d01de JZ 0x1481d01e6
1481d01e0 CALL 0x140e282f0
1481d01e5 NOP
1481d01e6 MOV EDI,dword ptr [RBP + -0x58]
1481d01e9 MOV RBX,qword ptr [RBP + -0x60]
1481d01ed TEST EDI,EDI
1481d01ef JZ 0x1481d0208
1481d01f1 MOV RCX,qword ptr [RBX]
1481d01f4 TEST RCX,RCX
1481d01f7 JZ 0x1481d01ff
1481d01f9 CALL 0x140e282f0
1481d01fe NOP
1481d01ff ADD RBX,0x10
1481d0203 SUB EDI,0x1
1481d0206 JNZ 0x1481d01f1
1481d0208 MOV RCX,qword ptr [RBP + -0x60]
1481d020c TEST RCX,RCX
1481d020f JZ 0x1481d0217
1481d0211 CALL 0x140e282f0
1481d0216 NOP
1481d0217 MOV RCX,qword ptr [RBP + -0x70]
1481d021b TEST RCX,RCX
1481d021e JZ 0x1481d0226
1481d0220 CALL 0x140e282f0
1481d0225 NOP
1481d0226 MOV RCX,qword ptr [RBP + -0x80]
1481d022a TEST RCX,RCX
1481d022d JZ 0x1481d0235
1481d022f CALL 0x140e282f0
1481d0234 NOP
1481d0235 JMP 0x1481d0253
1481d0237 CMP byte ptr [0x14eab53c8],0x3
1481d023e JC 0x1481d0253
1481d0240 LEA RDX,[0x14cf78f10]
1481d0247 LEA RCX,[0x14eab53c8]
1481d024e CALL 0x140f24ba0
1481d0253 LEA R11,[RSP + 0x120]
1481d025b MOV RBX,qword ptr [R11 + 0x48]
1481d025f MOVAPS XMM6,xmmword ptr [R11 + -0x10]
1481d0264 MOVAPS XMM7,xmmword ptr [R11 + -0x20]
1481d0269 MOVAPS XMM8,xmmword ptr [R11 + -0x30]
1481d026e MOVAPS XMM9,xmmword ptr [R11 + -0x40]
1481d0273 MOVAPS XMM10,xmmword ptr [R11 + -0x50]
1481d0278 MOVAPS XMM11,xmmword ptr [R11 + -0x60]
1481d027d MOV RSP,R11
1481d0280 POP R15
1481d0282 POP R14
1481d0284 POP R13
1481d0286 POP R12
1481d0288 POP RDI
1481d0289 POP RSI
1481d028a POP RBP
1481d028b RET
*/

/* 1481d1c90 RebuildQueueFromCurrentState */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void RebuildQueueFromCurrentState(longlong param_1,longlong param_2,float param_3,uint param_4)

{
  undefined8 *puVar1;
  float fVar2;
  uint uVar3;
  double *pdVar4;
  ulonglong uVar5;
  code *pcVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  char cVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  ulonglong uVar14;
  int iVar15;
  longlong lVar16;
  int iVar17;
  ulonglong *puVar18;
  undefined8 unaff_retaddr;
  double dStack_b8;
  double dStack_b0;
  uint uStack_a8;
  undefined4 uStack_a4;
  double dStack_a0;
  int iStack_98;
  float fStack_94;
  
  uVar14 = (ulonglong)param_4;
  if (((*(char *)(param_1 + 0x108) == '\0') || (*(int *)(param_1 + 0xf0) == 0)) ||
     (*(int *)(param_2 + 0x18) == 0)) {
    if (2 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf798f8);
    }
  }
  else {
    if (2 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf799a0,*(undefined4 *)(param_1 + 0x110),uVar14,
                          (double)param_3,*(undefined8 *)(param_1 + 0x1a0));
    }
    dVar8 = (double)func_0x0001481d12e0(param_1);
    uVar3 = *(uint *)(param_1 + 0x110);
    uVar13 = 0;
    if ((-1 < (int)uVar3) && ((int)uVar3 < *(int *)(param_1 + 0xf0))) {
      uVar13 = 0;
      if ((int)uVar3 < *(int *)(param_1 + 0xf0)) {
        uVar13 = ~uVar3 >> 0x1f;
      }
      if ((uVar13 == 0) &&
         (cVar10 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                       &UNK_14bce6ef0,(longlong)(int)uVar3,
                                       (longlong)*(int *)(param_1 + 0xf0)), cVar10 != '\0')) {
        pcVar6 = (code *)swi(3);
        (*pcVar6)();
        return;
      }
      uVar13 = *(uint *)(*(longlong *)(param_1 + 0xe8) + 0x10 + (longlong)(int)uVar3 * 0x28);
    }
    puVar18 = (ulonglong *)(param_1 + 0xe8);
    iVar17 = *(int *)(param_1 + 0x110);
    iVar15 = *(int *)(param_1 + 0xf0) - iVar17;
    if (iVar15 != 0) {
      iVar11 = (*(int *)(param_1 + 0xf0) - iVar17) - iVar15;
      if (iVar11 != 0) {
        func_0x00014b89503a(*puVar18 + (longlong)iVar17 * 0x28,
                            *puVar18 + (longlong)*(int *)(param_1 + 0xf0) * 0x28,
                            (longlong)iVar11 * 0x28);
      }
      *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) - iVar15;
      func_0x0001481d21b0(puVar18);
    }
    uVar3 = _DAT_14bd17880;
    iVar17 = *(int *)(param_1 + 0x110);
    iVar15 = *(int *)(param_2 + 0x18);
    dVar8 = dVar8 + _DAT_14bd774b8;
    if (0 < (int)param_4) {
      dVar9 = _DAT_14bce5180 / (double)param_3;
      do {
        iVar17 = iVar17 + 1;
        if (((int)uVar13 < 0) || (*(int *)(param_2 + 0x18) <= (int)uVar13)) {
          if (1 < DAT_14eab53c8) {
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79aa8,uVar13,iVar15);
          }
          uVar13 = 0;
        }
        uVar12 = 0;
        if ((int)uVar13 < *(int *)(param_2 + 0x18)) {
          uVar12 = ~uVar13 >> 0x1f;
        }
        if ((uVar12 == 0) &&
           (cVar10 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                         &UNK_14bce6ef0,(longlong)(int)uVar13,
                                         (longlong)*(int *)(param_2 + 0x18)), cVar10 != '\0')) {
          pcVar6 = (code *)swi(3);
          (*pcVar6)();
          return;
        }
        fVar2 = *(float *)(*(longlong *)(param_2 + 0x10) + (longlong)(int)uVar13 * 4);
        if (1 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf79b58,(double)fVar2,uVar13);
        }
        pdVar4 = (double *)*puVar18;
        dStack_b0 = dVar8 + *(double *)(param_1 + 0x150);
        dVar7 = (double)(float)((uint)fVar2 & uVar3) * *(double *)(param_1 + 0x1a0) * dVar9;
        if (dVar7 <= *(double *)(param_1 + 0xe0)) {
          dVar7 = *(double *)(param_1 + 0xe0);
        }
        dStack_b8 = dVar8;
        uStack_a8 = uVar13;
        dStack_a0 = dVar7;
        iStack_98 = iVar17;
        fStack_94 = fVar2;
        if (((pdVar4 <= &dStack_b8) &&
            (&dStack_b8 < pdVar4 + (longlong)*(int *)(param_1 + 0xf4) * 5)) &&
           (cVar10 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                         &UNK_14bce6d80,&dStack_b8,pdVar4,
                                         (longlong)*(int *)(param_1 + 0xf4),
                                         (longlong)*(int *)(param_1 + 0xf0),0x28), cVar10 != '\0'))
        {
          pcVar6 = (code *)swi(3);
          (*pcVar6)();
          return;
        }
        iVar11 = *(int *)(param_1 + 0xf0);
        lVar16 = (longlong)iVar11;
        *(uint *)(param_1 + 0xf0) = iVar11 + 1U;
        if (*(uint *)(param_1 + 0xf4) < iVar11 + 1U) {
          func_0x0001481d2100(puVar18,iVar11);
        }
        uVar5 = *puVar18;
        dVar8 = dVar8 + dVar7;
        pdVar4 = (double *)(uVar5 + lVar16 * 0x28);
        *pdVar4 = dStack_b8;
        pdVar4[1] = dStack_b0;
        puVar1 = (undefined8 *)(uVar5 + 0x10 + lVar16 * 0x28);
        *puVar1 = CONCAT44(uStack_a4,uStack_a8);
        puVar1[1] = dStack_a0;
        *(ulonglong *)(uVar5 + 0x20 + lVar16 * 0x28) = CONCAT44(fStack_94,iStack_98);
        uVar13 = (int)(uVar13 + 1) % iVar15;
        uVar14 = uVar14 - 1;
      } while (uVar14 != 0);
    }
    *(float *)(param_1 + 0x10c) = param_3;
  }
  return;
}


/* Instruction evidence:
1481d1c90 MOV RAX,RSP
1481d1c93 PUSH RBP
1481d1c94 PUSH RDI
1481d1c95 PUSH R13
1481d1c97 SUB RSP,0xf0
1481d1c9e CMP byte ptr [RCX + 0x108],0x0
1481d1ca5 MOV R13,RDX
1481d1ca8 MOVAPS xmmword ptr [RAX + -0x78],XMM10
1481d1cad MOV RDI,RCX
1481d1cb0 MOVAPS XMM10,XMM2
1481d1cb4 MOV EBP,R9D
1481d1cb7 JZ 0x1481d20c5
1481d1cbd CMP dword ptr [RCX + 0xf0],0x0
1481d1cc4 JZ 0x1481d20c5
1481d1cca CMP dword ptr [RDX + 0x18],0x0
1481d1cce JZ 0x1481d20c5
1481d1cd4 CMP byte ptr [0x14eab53c8],0x3
1481d1cdb MOV qword ptr [RAX + 0x10],RBX
1481d1cdf MOV qword ptr [RAX + 0x18],RSI
1481d1ce3 MOV qword ptr [RAX + 0x20],R12
1481d1ce7 MOV qword ptr [RAX + -0x20],R14
1481d1ceb MOV qword ptr [RAX + -0x28],R15
1481d1cef MOVAPS xmmword ptr [RAX + -0x58],XMM8
1481d1cf4 JC 0x1481d1d2f
1481d1cf6 MOVSD XMM0,qword ptr [RCX + 0x1a0]
1481d1cfe LEA RDX,[0x14cf799a0]
1481d1d05 MOV R8D,dword ptr [RCX + 0x110]
1481d1d0c XORPS XMM1,XMM1
1481d1d0f CVTSS2SD XMM1,XMM10
1481d1d14 LEA RCX,[0x14eab53c8]
1481d1d1b MOV R9D,EBP
1481d1d1e MOVSD qword ptr [RSP + 0x28],XMM0
1481d1d24 MOVSD qword ptr [RSP + 0x20],XMM1
1481d1d2a CALL 0x140f24ba0
1481d1d2f MOV RCX,RDI
1481d1d32 CALL 0x1481d12e0
1481d1d37 MOVSXD RSI,dword ptr [RDI + 0x110]
1481d1d3e LEA R8,[0x14bce6ef0]
1481d1d45 XOR EBX,EBX
1481d1d47 MOVAPS XMM8,XMM0
1481d1d4b TEST ESI,ESI
1481d1d4d JS 0x1481d1db7
1481d1d4f CMP ESI,dword ptr [RDI + 0xf0]
1481d1d55 JGE 0x1481d1db7
1481d1d57 XOR EAX,EAX
1481d1d59 LEA R14,[RDI + 0xe8]
1481d1d60 MOVSXD RDX,dword ptr [R14 + 0x8]
1481d1d64 MOV ECX,ESI
1481d1d66 NOT ECX
1481d1d68 SHR ECX,0x1f
1481d1d6b CMP ESI,EDX
1481d1d6d CMOVL EAX,ECX
1481d1d70 TEST EAX,EAX
1481d1d72 JNZ 0x1481d1daa
1481d1d74 MOV R9,qword ptr [RSP + 0x108]
1481d1d7c LEA RCX,[0x14bce6f68]
1481d1d83 MOV qword ptr [RSP + 0x30],RDX
1481d1d88 LEA RDX,[0x14cf27ac0]
1481d1d8f MOV qword ptr [RSP + 0x28],RSI
1481d1d94 MOV qword ptr [RSP + 0x20],R8
1481d1d99 MOV R8D,0x303
1481d1d9f CALL 0x140f8dfd0
1481d1da4 TEST AL,AL
1481d1da6 JZ 0x1481d1daa
1481d1da8 NOP
1481d1da9 INT3
1481d1daa MOV RAX,qword ptr [R14]
1481d1dad LEA RCX,[RSI + RSI*0x4]
1481d1db1 MOV EBX,dword ptr [RAX + RCX*0x8 + 0x10]
1481d1db5 JMP 0x1481d1dbe
1481d1db7 LEA R14,[RDI + 0xe8]
1481d1dbe MOVSXD RCX,dword ptr [RDI + 0xf0]
1481d1dc5 MOVSXD R10,dword ptr [RDI + 0x110]
1481d1dcc MOV ESI,ECX
1481d1dce SUB ESI,R10D
1481d1dd1 JZ 0x1481d1e0c
1481d1dd3 MOV EAX,dword ptr [R14 + 0x8]
1481d1dd7 SUB EAX,R10D
1481d1dda SUB EAX,ESI
1481d1ddc JZ 0x1481d1e00
1481d1dde MOV R9,qword ptr [R14]
1481d1de1 LEA RCX,[RCX + RCX*0x4]
1481d1de5 CDQE
1481d1de7 LEA RDX,[R9 + RCX*0x8]
1481d1deb LEA RCX,[R10 + R10*0x4]
1481d1def LEA R8,[RAX + RAX*0x4]
1481d1df3 LEA RCX,[R9 + RCX*0x8]
1481d1df7 SHL R8,0x3
1481d1dfb CALL 0x14b89503a
1481d1e00 SUB dword ptr [R14 + 0x8],ESI
1481d1e04 MOV RCX,R14
1481d1e07 CALL 0x1481d21b0
1481d1e0c MOV R12D,dword ptr [RDI + 0x110]
1481d1e13 MOV EAX,dword ptr [R13 + 0x18]
1481d1e17 INC R12D
1481d1e1a MOV dword ptr [RSP + 0x110],EAX
1481d1e21 ADDSD XMM8,qword ptr [0x14bd774b8]
1481d1e2a TEST EBP,EBP
1481d1e2c JLE 0x1481d2089
1481d1e32 MOVAPS xmmword ptr [RSP + 0xd0],XMM6
1481d1e3a LEA RSI,[0x14bce6d80]
1481d1e41 MOVAPS xmmword ptr [RSP + 0xc0],XMM7
1481d1e49 XORPS XMM0,XMM0
1481d1e4c MOVAPS xmmword ptr [RSP + 0xa0],XMM9
1481d1e55 MOVSD XMM9,qword ptr [0x14bce5180]
1481d1e5e CVTSS2SD XMM0,XMM10
1481d1e63 MOVAPS xmmword ptr [RSP + 0x80],XMM11
1481d1e6c MOVSS XMM11,dword ptr [0x14bd17880]
1481d1e75 DIVSD XMM9,XMM0
1481d1e7a NOP word ptr [RAX + RAX*0x1]
1481d1e80 TEST EBX,EBX
1481d1e82 JS 0x1481d1e8a
1481d1e84 CMP EBX,dword ptr [R13 + 0x18]
1481d1e88 JL 0x1481d1eae
1481d1e8a CMP byte ptr [0x14eab53c8],0x2
1481d1e91 JC 0x1481d1eac
1481d1e93 MOV R9D,EAX
1481d1e96 LEA RDX,[0x14cf79aa8]
1481d1e9d MOV R8D,EBX
1481d1ea0 LEA RCX,[0x14eab53c8]
1481d1ea7 CALL 0x140f24ba0
1481d1eac XOR EBX,EBX
1481d1eae MOVSXD RDX,dword ptr [R13 + 0x18]
1481d1eb2 XOR EAX,EAX
1481d1eb4 MOV ECX,EBX
1481d1eb6 NOT ECX
1481d1eb8 SHR ECX,0x1f
1481d1ebb CMP EBX,EDX
1481d1ebd CMOVL EAX,ECX
1481d1ec0 TEST EAX,EAX
1481d1ec2 JNZ 0x1481d1f04
1481d1ec4 MOV R9,qword ptr [RSP + 0x108]
1481d1ecc LEA RAX,[0x14bce6ef0]
1481d1ed3 MOV qword ptr [RSP + 0x30],RDX
1481d1ed8 MOV R8D,0x303
1481d1ede MOVSXD RCX,EBX
1481d1ee1 LEA RDX,[0x14cf27ac0]
1481d1ee8 MOV qword ptr [RSP + 0x28],RCX
1481d1eed LEA RCX,[0x14bce6f68]
1481d1ef4 MOV qword ptr [RSP + 0x20],RAX
1481d1ef9 CALL 0x140f8dfd0
1481d1efe TEST AL,AL
1481d1f00 JZ 0x1481d1f04
1481d1f02 NOP
1481d1f03 INT3
1481d1f04 CMP byte ptr [0x14eab53c8],0x2
1481d1f0b MOV RAX,qword ptr [R13 + 0x10]
1481d1f0f MOVSXD RCX,EBX
1481d1f12 MOVSS XMM7,dword ptr [RAX + RCX*0x4]
1481d1f17 JC 0x1481d1f37
1481d1f19 CVTPS2PD XMM2,XMM7
1481d1f1c MOV R9D,EBX
1481d1f1f LEA RDX,[0x14cf79b58]
1481d1f26 LEA RCX,[0x14eab53c8]
1481d1f2d MOVQ R8,XMM2
1481d1f32 CALL 0x140f24ba0
1481d1f37 MOV R8,qword ptr [R14]
1481d1f3a LEA RAX,[RSP + 0x50]
1481d1f3f MOVAPS XMM0,XMM7
1481d1f42 MOV dword ptr [RSP + 0x70],R12D
1481d1f47 ANDPS XMM0,XMM11
1481d1f4b MOVSD qword ptr [RSP + 0x50],XMM8
1481d1f52 CVTPS2PD XMM6,XMM0
1481d1f55 INC R12D
1481d1f58 MOV dword ptr [RSP + 0x60],EBX
1481d1f5c MOVAPS XMM0,XMM8
1481d1f60 MOVSS dword ptr [RSP + 0x74],XMM7
1481d1f66 MULSD XMM6,qword ptr [RDI + 0x1a0]
1481d1f6e ADDSD XMM0,qword ptr [RDI + 0x150]
1481d1f76 MULSD XMM6,XMM9
1481d1f7b MOVSD qword ptr [RSP + 0x58],XMM0
1481d1f81 MAXSD XMM6,qword ptr [RDI + 0xe0]
1481d1f89 MOVSD qword ptr [RSP + 0x68],XMM6
1481d1f8f CMP RAX,R8
1481d1f92 JC 0x1481d1ffc
1481d1f94 MOVSXD RDX,dword ptr [R14 + 0xc]
1481d1f98 LEA RAX,[RDX + RDX*0x4]
1481d1f9c LEA RCX,[R8 + RAX*0x8]
1481d1fa0 LEA RAX,[RSP + 0x50]
1481d1fa5 CMP RAX,RCX
1481d1fa8 JNC 0x1481d1ffc
1481d1faa MOVSXD RAX,dword ptr [R14 + 0x8]
1481d1fae LEA RCX,[0x14bce6eb8]
1481d1fb5 MOV R9,qword ptr [RSP + 0x108]
1481d1fbd MOV qword ptr [RSP + 0x48],0x28
1481d1fc6 MOV qword ptr [RSP + 0x40],RAX
1481d1fcb LEA RAX,[RSP + 0x50]
1481d1fd0 MOV qword ptr [RSP + 0x38],RDX
1481d1fd5 LEA RDX,[0x14cf27ac0]
1481d1fdc MOV qword ptr [RSP + 0x30],R8
1481d1fe1 MOV R8D,0x63e
1481d1fe7 MOV qword ptr [RSP + 0x28],RAX
1481d1fec MOV qword ptr [RSP + 0x20],RSI
1481d1ff1 CALL 0x140f8dfd0
1481d1ff6 TEST AL,AL
1481d1ff8 JZ 0x1481d1ffc
1481d1ffa NOP
1481d1ffb INT3
1481d1ffc MOVSXD RSI,dword ptr [R14 + 0x8]
1481d2000 LEA EAX,[RSI + 0x1]
1481d2003 MOV dword ptr [R14 + 0x8],EAX
1481d2007 CMP EAX,dword ptr [R14 + 0xc]
1481d200b JBE 0x1481d2017
1481d200d MOV EDX,ESI
1481d200f MOV RCX,R14
1481d2012 CALL 0x1481d2100
1481d2017 MOV RAX,qword ptr [R14]
1481d201a LEA RCX,[RSI + RSI*0x4]
1481d201e MOVUPS XMM0,xmmword ptr [RSP + 0x50]
1481d2023 LEA RSI,[0x14bce6d80]
1481d202a ADDSD XMM8,XMM6
1481d202f MOVUPS xmmword ptr [RAX + RCX*0x8],XMM0
1481d2033 MOVUPS XMM1,xmmword ptr [RSP + 0x60]
1481d2038 MOVUPS xmmword ptr [RAX + RCX*0x8 + 0x10],XMM1
1481d203d MOVSD XMM0,qword ptr [RSP + 0x70]
1481d2043 MOVSD qword ptr [RAX + RCX*0x8 + 0x20],XMM0
1481d2049 LEA EAX,[RBX + 0x1]
1481d204c CDQ
1481d204d IDIV dword ptr [RSP + 0x110]
1481d2054 MOV EAX,dword ptr [RSP + 0x110]
1481d205b MOV EBX,EDX
1481d205d SUB RBP,0x1
1481d2061 JNZ 0x1481d1e80
1481d2067 MOVAPS XMM11,xmmword ptr [RSP + 0x80]
1481d2070 MOVAPS XMM9,xmmword ptr [RSP + 0xa0]
1481d2079 MOVAPS XMM7,xmmword ptr [RSP + 0xc0]
1481d2081 MOVAPS XMM6,xmmword ptr [RSP + 0xd0]
1481d2089 MOVAPS XMM8,xmmword ptr [RSP + 0xb0]
1481d2092 MOV R15,qword ptr [RSP + 0xe0]
1481d209a MOV R14,qword ptr [RSP + 0xe8]
1481d20a2 MOV R12,qword ptr [RSP + 0x128]
1481d20aa MOV RSI,qword ptr [RSP + 0x120]
1481d20b2 MOV RBX,qword ptr [RSP + 0x118]
1481d20ba MOVSS dword ptr [RDI + 0x10c],XMM10
1481d20c3 JMP 0x1481d20e1
1481d20c5 CMP byte ptr [0x14eab53c8],0x3
1481d20cc JC 0x1481d20e1
1481d20ce LEA RDX,[0x14cf798f8]
1481d20d5 LEA RCX,[0x14eab53c8]
1481d20dc CALL 0x140f24ba0
1481d20e1 MOVAPS XMM10,xmmword ptr [RSP + 0x90]
1481d20ea ADD RSP,0xf0
1481d20f1 POP R13
1481d20f3 POP RDI
1481d20f4 POP RBP
1481d20f5 RET
*/
