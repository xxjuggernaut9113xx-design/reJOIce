
/* 1481ce220 UpdateMetric */

void UpdateMetric(void)

{
  UpdateMetricWithConditions();
  return;
}


/* Instruction evidence:
1481ce220 SUB RSP,0x38
1481ce224 XOR EAX,EAX
1481ce226 MOV qword ptr [RSP + 0x20],RAX
1481ce22b MOV qword ptr [RSP + 0x28],RAX
1481ce230 LEA R9,[RSP + 0x20]
1481ce235 CALL 0x1481ce250
1481ce23a NOP
1481ce23b ADD RSP,0x38
1481ce23f RET
*/

/* 1481ce250 UpdateMetricWithConditions */

void UpdateMetricWithConditions
               (longlong param_1,undefined1 param_2,undefined4 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  longlong lVar2;
  code *pcVar3;
  longlong *plVar4;
  int iVar5;
  uint uVar6;
  char cVar7;
  longlong lVar8;
  ulonglong uVar9;
  undefined8 *puVar10;
  longlong *plVar11;
  undefined1 auStackX_8 [8];
  undefined1 uStackX_10;
  undefined4 uStackX_18;
  undefined8 uStackX_20;
  undefined1 auStack_78 [8];
  longlong *plStack_70;
  longlong *plStack_68;
  undefined8 uStack_60;
  undefined8 *puStack_58;
  uint uStack_50;
  
  uStackX_10 = param_2;
  uStackX_18 = param_3;
  uStackX_20 = param_4;
  func_0x0001481c8fd0();
  plStack_68 = (longlong *)0x0;
  uStack_60 = 0;
  func_0x0001481b2b20(param_1 + 0x1e0,param_2,&plStack_68,0);
  iVar5 = (int)uStack_60;
  plStack_70 = plStack_68 + (int)uStack_60;
  plVar11 = plStack_68;
LAB_1481ce2b0:
  do {
    plVar4 = plStack_70;
    if ((int)uStack_60 != iVar5) {
      auStackX_8[0] = 0;
      cVar7 = func_0x00014bae9430(auStackX_8);
      if (cVar7 != '\0') {
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
    }
    if (plVar11 == plVar4) {
      if (plStack_68 != (longlong *)0x0) {
        func_0x000140e282f0();
      }
      return;
    }
    lVar2 = *plVar11;
    if (*(longlong *)(param_1 + 0x60) != 0) {
      func_0x0001468fb0a0(*(longlong *)(param_1 + 0x60),&puStack_58);
      uVar6 = uStack_50;
      uVar9 = (ulonglong)(int)uStack_50;
      puVar1 = puStack_58 + uVar9;
      puVar10 = puStack_58;
      while( true ) {
        if ((uint)uVar9 != uVar6) {
          auStack_78[0] = 0;
          cVar7 = func_0x00014bae9430(auStack_78);
          if (cVar7 != '\0') {
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
        }
        if (puVar10 == puVar1) {
          if (puStack_58 != (undefined8 *)0x0) {
            func_0x000140e282f0();
          }
          goto LAB_1481ce3b4;
        }
        lVar8 = func_0x0001481b11d0(*(undefined8 *)(param_1 + 0x60),*puVar10,&UNK_14bce4e94,1);
        if ((lVar8 != 0) && (*(longlong *)(lVar8 + 8) == lVar2)) break;
        puVar10 = puVar10 + 1;
        uVar9 = (ulonglong)uStack_50;
      }
      if (puStack_58 != (undefined8 *)0x0) {
        func_0x000140e282f0();
      }
      cVar7 = func_0x0001481b4d80(param_1,lVar8,uStackX_20);
      if (cVar7 != '\0') {
        func_0x0001481cd9b0(param_1,*plVar11,uStackX_10,uStackX_18);
        plVar11 = plVar11 + 1;
        goto LAB_1481ce2b0;
      }
    }
LAB_1481ce3b4:
    plVar11 = plVar11 + 1;
  } while( true );
}


/* Instruction evidence:
1481ce250 MOV qword ptr [RSP + 0x20],R9
1481ce255 MOV dword ptr [RSP + 0x18],R8D
1481ce25a MOV byte ptr [RSP + 0x10],DL
1481ce25e PUSH RBX
1481ce25f PUSH RBP
1481ce260 PUSH RSI
1481ce261 PUSH RDI
1481ce262 PUSH R12
1481ce264 PUSH R13
1481ce266 PUSH R14
1481ce268 PUSH R15
1481ce26a SUB RSP,0x58
1481ce26e MOVZX EBX,DL
1481ce271 MOV R13,RCX
1481ce274 CALL 0x1481c8fd0
1481ce279 XOR EAX,EAX
1481ce27b MOV qword ptr [RSP + 0x30],RAX
1481ce280 MOV qword ptr [RSP + 0x38],RAX
1481ce285 LEA RCX,[R13 + 0x1e0]
1481ce28c XOR R9D,R9D
1481ce28f LEA R8,[RSP + 0x30]
1481ce294 MOVZX EDX,BL
1481ce297 CALL 0x1481b2b20
1481ce29c MOV R14,qword ptr [RSP + 0x30]
1481ce2a1 MOVSXD R12,dword ptr [RSP + 0x38]
1481ce2a6 LEA RBX,[R14 + R12*0x8]
1481ce2aa MOV qword ptr [RSP + 0x28],RBX
1481ce2af NOP
1481ce2b0 CMP dword ptr [RSP + 0x38],R12D
1481ce2b5 JZ 0x1481ce2d2
1481ce2b7 MOV byte ptr [RSP + 0xa0],0x0
1481ce2bf LEA RCX,[RSP + 0xa0]
1481ce2c7 CALL 0x14bae9430
1481ce2cc TEST AL,AL
1481ce2ce JZ 0x1481ce2d2
1481ce2d0 NOP
1481ce2d1 INT3
1481ce2d2 CMP R14,RBX
1481ce2d5 JZ 0x1481ce3c2
1481ce2db MOV RBX,qword ptr [R14]
1481ce2de MOV RCX,qword ptr [R13 + 0x60]
1481ce2e2 TEST RCX,RCX
1481ce2e5 JZ 0x1481ce3b4
1481ce2eb LEA RDX,[RSP + 0x40]
1481ce2f0 CALL 0x1468fb0a0
1481ce2f5 NOP
1481ce2f6 MOV RDI,qword ptr [RSP + 0x40]
1481ce2fb MOVSXD RCX,dword ptr [RSP + 0x48]
1481ce300 MOV RBP,RCX
1481ce303 LEA R15,[RDI + RCX*0x8]
1481ce307 CMP ECX,EBP
1481ce309 JZ 0x1481ce320
1481ce30b MOV byte ptr [RSP + 0x20],0x0
1481ce310 LEA RCX,[RSP + 0x20]
1481ce315 CALL 0x14bae9430
1481ce31a TEST AL,AL
1481ce31c JZ 0x1481ce320
1481ce31e NOP
1481ce31f INT3
1481ce320 CMP RDI,R15
1481ce323 JZ 0x1481ce3a4
1481ce325 MOV R9B,0x1
1481ce328 LEA R8,[0x14bce4e94]
1481ce32f MOV RDX,qword ptr [RDI]
1481ce332 MOV RCX,qword ptr [R13 + 0x60]
1481ce336 CALL 0x1481b11d0
1481ce33b MOV RSI,RAX
1481ce33e TEST RAX,RAX
1481ce341 JZ 0x1481ce349
1481ce343 CMP qword ptr [RAX + 0x8],RBX
1481ce347 JZ 0x1481ce353
1481ce349 ADD RDI,0x8
1481ce34d MOV ECX,dword ptr [RSP + 0x48]
1481ce351 JMP 0x1481ce307
1481ce353 MOV RCX,qword ptr [RSP + 0x40]
1481ce358 TEST RCX,RCX
1481ce35b JZ 0x1481ce363
1481ce35d CALL 0x140e282f0
1481ce362 NOP
1481ce363 MOV R8,qword ptr [RSP + 0xb8]
1481ce36b MOV RDX,RSI
1481ce36e MOV RCX,R13
1481ce371 CALL 0x1481b4d80
1481ce376 TEST AL,AL
1481ce378 JZ 0x1481ce3b4
1481ce37a MOV R9D,dword ptr [RSP + 0xb0]
1481ce382 MOVZX R8D,byte ptr [RSP + 0xa8]
1481ce38b MOV RDX,qword ptr [R14]
1481ce38e MOV RCX,R13
1481ce391 CALL 0x1481cd9b0
1481ce396 ADD R14,0x8
1481ce39a MOV RBX,qword ptr [RSP + 0x28]
1481ce39f JMP 0x1481ce2b0
1481ce3a4 MOV RCX,qword ptr [RSP + 0x40]
1481ce3a9 TEST RCX,RCX
1481ce3ac JZ 0x1481ce3b4
1481ce3ae CALL 0x140e282f0
1481ce3b3 NOP
1481ce3b4 ADD R14,0x8
1481ce3b8 MOV RBX,qword ptr [RSP + 0x28]
1481ce3bd JMP 0x1481ce2b0
1481ce3c2 MOV RCX,qword ptr [RSP + 0x30]
1481ce3c7 TEST RCX,RCX
1481ce3ca JZ 0x1481ce3d2
1481ce3cc CALL 0x140e282f0
1481ce3d1 NOP
1481ce3d2 ADD RSP,0x58
1481ce3d6 POP R15
1481ce3d8 POP R14
1481ce3da POP R13
1481ce3dc POP R12
1481ce3de POP RDI
1481ce3df POP RSI
1481ce3e0 POP RBP
1481ce3e1 POP RBX
1481ce3e2 RET
*/

/* 1481cc110 StartNewSession */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void StartNewSession(longlong *param_1)

{
  ulonglong uVar1;
  uint uVar2;
  uint uVar3;
  code *pcVar4;
  int iVar5;
  longlong *plVar6;
  char cVar7;
  longlong lVar8;
  undefined8 uVar9;
  byte bVar10;
  undefined **ppuVar11;
  longlong *plVar12;
  longlong lVar13;
  uint *puVar14;
  longlong lVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  uint *puVar19;
  undefined8 unaff_retaddr;
  undefined1 auStack_2a8 [32];
  undefined *puStack_288;
  undefined4 uStack_280;
  undefined1 uStack_278;
  undefined1 auStack_277 [7];
  int iStack_270;
  uint uStack_26c;
  uint *puStack_268;
  uint uStack_260;
  int iStack_25c;
  int iStack_258;
  undefined4 uStack_254;
  int iStack_250;
  uint uStack_24c;
  uint *puStack_248;
  uint uStack_240;
  uint uStack_23c;
  uint uStack_238;
  undefined4 uStack_234;
  longlong *plStack_230;
  longlong *plStack_228;
  undefined8 uStack_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  int iStack_200;
  undefined4 uStack_1fc;
  int iStack_1f8;
  longlong *plStack_1f0;
  undefined8 uStack_1e8;
  undefined4 uStack_1e0;
  undefined4 uStack_1dc;
  uint uStack_1d8;
  int iStack_1d4;
  int iStack_1d0;
  undefined4 uStack_1cc;
  int iStack_1c8;
  undefined4 uStack_1c4;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  longlong *plStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  longlong *plStack_140;
  undefined8 uStack_138;
  uint *puStack_130;
  undefined8 uStack_128;
  uint uStack_120;
  undefined4 uStack_11c;
  int iStack_118;
  undefined4 uStack_114;
  undefined8 *puStack_108;
  int iStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  longlong alStack_d8 [2];
  undefined **ppuStack_c8;
  undefined *puStack_b8;
  longlong *plStack_b0;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined *puStack_98;
  longlong **pplStack_90;
  longlong lStack_88;
  undefined **ppuStack_78;
  undefined *puStack_68;
  longlong *plStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined *puStack_48;
  longlong **pplStack_40;
  ulonglong uStack_38;
  
  uStack_38 = _DAT_14ea60b28 ^ (ulonglong)auStack_2a8;
  uStack_1c0 = 0;
  uStack_1b8 = 0;
  uStack_1b0 = 0;
  uStack_1a8 = 0;
  uStack_1a0 = 0;
  uStack_198 = 0;
  uStack_190 = 0;
  uStack_188 = 0;
  plStack_180 = (longlong *)0x0;
  uStack_178 = 0;
  uStack_170 = 0;
  uStack_168 = 0;
  uStack_160 = 0;
  uStack_158 = 0;
  uStack_150 = 0;
  uStack_148 = 0;
  func_0x0001481537f0(param_1 + 0x46,&uStack_1c0);
  plVar6 = plStack_180;
  plVar12 = plStack_180;
  for (iVar16 = (int)uStack_178; iVar16 != 0; iVar16 = iVar16 + -1) {
    if (*plVar12 != 0) {
      func_0x000140e282f0();
    }
    plVar12 = plVar12 + 2;
  }
  if (plVar6 != (longlong *)0x0) {
    func_0x000140e282f0(plVar6);
  }
  lVar8 = (**(code **)(*param_1 + 0x188))(param_1);
  *(float *)(param_1 + 0x66) = (float)*(double *)(lVar8 + 0x740);
  param_1[0x13] = 0;
  *(undefined4 *)((longlong)param_1 + 0x94) = 0;
  iStack_270 = 0;
  uStack_26c = 1;
  puVar14 = (uint *)(param_1 + 0x20);
  uStack_260 = 0xffffffff;
  iStack_25c = 0;
  iStack_258 = 0;
  puStack_268 = puVar14;
  if ((int)param_1[0x23] < 0) {
    puStack_288 = &UNK_14bce4e94;
    cVar7 = func_0x000140f8dfd0(&UNK_14bcf2f60,&UNK_14cf28330,0x70b,unaff_retaddr);
    if (cVar7 != '\0') {
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
  }
  plStack_228 = param_1 + 0x1e;
  iVar16 = (int)param_1[0x23];
  if (iVar16 != 0) {
    puVar19 = puVar14;
    if ((uint *)param_1[0x22] != (uint *)0x0) {
      puVar19 = (uint *)param_1[0x22];
    }
    uVar2 = *puVar19;
    iStack_25c = 0;
    iVar5 = 0;
    while (uVar2 == 0) {
      iStack_270 = iVar5 + 1;
      iStack_258 = iStack_25c + 0x20;
      if ((int)((iVar16 + -1 >> 0x1f & 0x1fU) + iVar16 + -1) >> 5 < iStack_270) goto LAB_1481cc32d;
      uVar2 = puVar19[iStack_270];
      uStack_260 = 0xffffffff;
      iStack_25c = iStack_258;
      iVar5 = iStack_270;
    }
    uStack_26c = uVar2 - 1 & uVar2 ^ uVar2;
    uVar1 = (ulonglong)uStack_26c * 2 + 1;
    lVar8 = 0x3f;
    if (uVar1 != 0) {
      for (; uVar1 >> lVar8 == 0; lVar8 = lVar8 + -1) {
      }
    }
    iStack_1f8 = (int)lVar8;
    iStack_25c = iStack_1f8 + -1 + iStack_25c;
    if (iVar16 < iStack_25c) {
LAB_1481cc32d:
      iStack_25c = iVar16;
    }
  }
  uStack_220 = CONCAT44(uStack_26c,iStack_270);
  uStack_218 = puStack_268;
  puVar19 = uStack_218;
  uStack_210 = CONCAT44(iStack_25c,uStack_260);
  uStack_208 = CONCAT44(uStack_254,iStack_258);
  iStack_200 = (int)param_1[0x1f] - *(int *)((longlong)param_1 + 0x124);
  uStack_218._0_4_ = SUB84(puStack_268,0);
  uStack_218._4_4_ = (undefined4)((ulonglong)puStack_268 >> 0x20);
  uStack_1e0 = (undefined4)uStack_218;
  uStack_1dc = uStack_218._4_4_;
  uStack_1d8 = uStack_260;
  iStack_1d4 = iStack_25c;
  iStack_1d0 = iStack_258;
  uStack_1cc = uStack_254;
  uStack_1c4 = uStack_1fc;
  uVar2 = *(uint *)(param_1 + 0x23);
  iVar16 = (int)uVar2 >> 5;
  bVar10 = (byte)uVar2 & 0x1f;
  uStack_24c = 1 << bVar10;
  uVar18 = -1 << bVar10;
  uVar17 = uVar2 & 0xffffffe0;
  iStack_250 = iVar16;
  puStack_248 = puVar14;
  uStack_240 = uVar18;
  uStack_23c = uVar2;
  uStack_238 = uVar17;
  plStack_1f0 = plStack_228;
  uStack_1e8 = uStack_220;
  iStack_1c8 = iStack_200;
  if ((int)uVar2 < 0) {
    puStack_288 = &UNK_14bce4e94;
    uStack_218 = puVar19;
    cVar7 = func_0x000140f8dfd0(&UNK_14bcf2f60,&UNK_14cf28330,0x70b,unaff_retaddr);
    if (cVar7 != '\0') {
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
  }
  plStack_228 = param_1 + 0x1e;
  uVar3 = *(uint *)(param_1 + 0x23);
  if (uVar2 != uVar3) {
    if ((uint *)param_1[0x22] != (uint *)0x0) {
      puVar14 = (uint *)param_1[0x22];
    }
    uVar18 = puVar14[iVar16] & uVar18;
    while (uVar18 == 0) {
      iStack_250 = iVar16 + 1;
      uStack_238 = uVar17 + 0x20;
      if ((int)(((int)(uVar3 - 1) >> 0x1f & 0x1fU) + (uVar3 - 1)) >> 5 < iStack_250)
      goto LAB_1481cc47d;
      uVar18 = puVar14[iStack_250];
      uStack_240 = 0xffffffff;
      iVar16 = iStack_250;
      uVar17 = uStack_238;
    }
    uStack_24c = uVar18 - 1 & uVar18 ^ uVar18;
    uVar1 = (ulonglong)uStack_24c * 2 + 1;
    lVar8 = 0x3f;
    if (uVar1 != 0) {
      for (; uVar1 >> lVar8 == 0; lVar8 = lVar8 + -1) {
      }
    }
    plStack_230 = (longlong *)CONCAT44(plStack_230._4_4_,(int)lVar8);
    uStack_23c = (int)lVar8 + -1 + uVar17;
    if ((int)uVar3 < (int)uStack_23c) {
LAB_1481cc47d:
      uStack_23c = uVar3;
    }
  }
  uStack_220 = CONCAT44(uStack_24c,iStack_250);
  uStack_218 = puStack_248;
  uStack_210 = CONCAT44(uStack_23c,uStack_240);
  uStack_208 = CONCAT44(uStack_234,uStack_238);
  iStack_200 = (int)param_1[0x1f] - *(int *)((longlong)param_1 + 0x124);
  puStack_130 = puStack_248;
  uStack_120 = uStack_238;
  uStack_11c = uStack_234;
  uStack_114 = uStack_1fc;
  plStack_140 = plStack_228;
  uStack_138 = uStack_220;
  uStack_128 = uStack_210;
  iStack_118 = iStack_200;
  while( true ) {
    plVar12 = plStack_1f0;
    if ((int)plStack_1f0[1] - *(int *)((longlong)plStack_1f0 + 0x34) != iStack_1c8) {
      uStack_278 = 0;
      cVar7 = func_0x00014bc1d2b0(&uStack_278);
      if (cVar7 != '\0') {
        pcVar4 = (code *)swi(3);
        (*pcVar4)();
        return;
      }
    }
    if (((iStack_1d4 == uStack_128._4_4_) &&
        ((uint *)CONCAT44(uStack_1dc,uStack_1e0) == puStack_130)) && (plVar12 == plStack_140))
    break;
    lVar8 = (longlong)iStack_1d4 * 0x40 + *plVar12;
    if (*(char *)(lVar8 + 0x20) == '\0') {
      *(undefined1 *)(lVar8 + 0x20) = 0;
      lVar13 = *(longlong *)(lVar8 + 0x10);
      iVar16 = *(int *)(lVar8 + 0x18);
      lVar15 = (longlong)iVar16 * 0x10 + lVar13;
      while( true ) {
        if (*(int *)(lVar8 + 0x18) != iVar16) {
          auStack_277[0] = 0;
          cVar7 = func_0x00014bc1d120(auStack_277);
          if (cVar7 != '\0') {
            pcVar4 = (code *)swi(3);
            (*pcVar4)();
            return;
          }
        }
        if (lVar13 == lVar15) break;
        *(undefined4 *)(lVar13 + 0xc) = 0;
        lVar13 = lVar13 + 0x10;
      }
    }
    uStack_1d8 = uStack_1d8 & ~uStack_1e8._4_4_;
    func_0x000140d10990(&uStack_1e8);
  }
  uVar9 = (**(code **)(*param_1 + 0x188))(param_1);
  uVar9 = func_0x000147a1e670(uVar9);
  puStack_68 = &UNK_14cf77840;
  lStack_88 = 0x1481b4ba0;
  puStack_48 = &UNK_14cf777f8;
  pplStack_90 = &plStack_60;
  puStack_108 = (undefined8 *)0x0;
  iStack_100 = 0;
  uStack_f8 = 0;
  uStack_f0 = 0;
  uStack_e8 = 0;
  plStack_230 = alStack_d8;
  alStack_d8[0] = 0x1481b4ba0;
  ppuStack_c8 = (undefined **)0x0;
  ppuStack_78 = (undefined **)0x0;
  puStack_b8 = &UNK_14cf77840;
  uStack_a8 = uStack_58;
  uStack_a4 = uStack_54;
  uStack_a0 = uStack_50;
  uStack_9c = uStack_4c;
  puStack_98 = &UNK_14cf777f8;
  plStack_b0 = param_1;
  plStack_60 = param_1;
  pplStack_40 = pplStack_90;
  pplStack_90 = (longlong **)(*_DAT_14cf77848)(&puStack_b8);
  lStack_88 = 0;
  uStack_280 = _DAT_14bd17874;
  puStack_288 = (undefined *)CONCAT71(puStack_288._1_7_,1);
  func_0x0001478cf760(uVar9,param_1 + 9,&puStack_108,_DAT_14bcef9ec);
  if (alStack_d8[0] != 0) {
    ppuVar11 = &puStack_b8;
    if (ppuStack_c8 != (undefined **)0x0) {
      ppuVar11 = ppuStack_c8;
    }
    (**(code **)(*ppuVar11 + 0x10))();
  }
  puStack_98 = &UNK_14d3ac0f0;
  func_0x000140c70210(&uStack_f8);
  if ((iStack_100 != 0) && (puStack_108 != (undefined8 *)0x0)) {
    (**(code **)*puStack_108)(puStack_108,0);
    func_0x000140d20c70(&puStack_108,0,0,0x10);
    iStack_100 = 0;
  }
  if (puStack_108 != (undefined8 *)0x0) {
    func_0x000140e282f0();
  }
  if (lStack_88 != 0) {
    ppuVar11 = &puStack_68;
    if (ppuStack_78 != (undefined **)0x0) {
      ppuVar11 = ppuStack_78;
    }
    (**(code **)(*ppuVar11 + 0x10))();
  }
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71b28);
  }
  func_0x00014b880380(uStack_38 ^ (ulonglong)auStack_2a8);
  return;
}


/* Instruction evidence:
1481cc110 MOV qword ptr [RSP + 0x10],RBX
1481cc115 MOV qword ptr [RSP + 0x18],RSI
1481cc11a MOV qword ptr [RSP + 0x20],RDI
1481cc11f PUSH RBP
1481cc120 PUSH R12
1481cc122 PUSH R13
1481cc124 PUSH R14
1481cc126 PUSH R15
1481cc128 LEA RBP,[RSP + -0x180]
1481cc130 SUB RSP,0x280
1481cc137 MOV RAX,qword ptr [0x14ea60b28]
1481cc13e XOR RAX,RSP
1481cc141 MOV qword ptr [RBP + 0x170],RAX
1481cc148 MOV R15,RCX
1481cc14b XORPS XMM0,XMM0
1481cc14e MOVUPS xmmword ptr [RBP + 0x8],XMM0
1481cc152 MOVUPS xmmword ptr [RBP + 0x18],XMM0
1481cc156 MOVUPS xmmword ptr [RBP + 0x28],XMM0
1481cc15a MOVUPS xmmword ptr [RBP + 0x38],XMM0
1481cc15e MOVUPS xmmword ptr [RBP + 0x48],XMM0
1481cc162 MOVUPS xmmword ptr [RBP + 0x58],XMM0
1481cc166 MOVDQU xmmword ptr [RBP + -0x18],XMM0
1481cc16b XORPS XMM1,XMM1
1481cc16e MOVDQU xmmword ptr [RBP + -0x8],XMM1
1481cc173 XOR R14D,R14D
1481cc176 MOV qword ptr [RBP + 0x8],R14
1481cc17a MOV dword ptr [RBP + 0x10],R14D
1481cc17e MOV word ptr [RBP + 0x14],R14W
1481cc183 MOV qword ptr [RBP + 0x18],R14
1481cc187 MOV dword ptr [RBP + 0x20],R14D
1481cc18b MOV qword ptr [RBP + 0x28],R14
1481cc18f MOVDQU xmmword ptr [RBP + 0x30],XMM0
1481cc194 MOVDQU xmmword ptr [RBP + 0x40],XMM1
1481cc199 MOVDQU xmmword ptr [RBP + 0x50],XMM0
1481cc19e MOV dword ptr [RBP + 0x60],R14D
1481cc1a2 ADD RCX,0x230
1481cc1a9 LEA RDX,[RBP + -0x18]
1481cc1ad CALL 0x1481537f0
1481cc1b2 NOP
1481cc1b3 MOV EDI,dword ptr [RBP + 0x30]
1481cc1b6 MOV RSI,qword ptr [RBP + 0x28]
1481cc1ba MOV RBX,RSI
1481cc1bd TEST EDI,EDI
1481cc1bf JZ 0x1481cc1d8
1481cc1c1 MOV RCX,qword ptr [RBX]
1481cc1c4 TEST RCX,RCX
1481cc1c7 JZ 0x1481cc1cf
1481cc1c9 CALL 0x140e282f0
1481cc1ce NOP
1481cc1cf ADD RBX,0x10
1481cc1d3 SUB EDI,0x1
1481cc1d6 JNZ 0x1481cc1c1
1481cc1d8 TEST RSI,RSI
1481cc1db JZ 0x1481cc1e6
1481cc1dd MOV RCX,RSI
1481cc1e0 CALL 0x140e282f0
1481cc1e5 NOP
1481cc1e6 MOV RAX,qword ptr [R15]
1481cc1e9 MOV RCX,R15
1481cc1ec CALL qword ptr [RAX + 0x188]
1481cc1f2 MOVSD XMM0,qword ptr [RAX + 0x740]
1481cc1fa CVTPD2PS XMM0,XMM0
1481cc1fe MOVSS dword ptr [R15 + 0x330],XMM0
1481cc207 MOV qword ptr [R15 + 0x98],R14
1481cc20e MOV dword ptr [R15 + 0x94],R14D
1481cc215 LEA R10,[R15 + 0xf0]
1481cc21c MOV EBX,R14D
1481cc21f MOV dword ptr [RSP + 0x38],EBX
1481cc223 MOV R13D,0x1
1481cc229 MOV dword ptr [RSP + 0x3c],R13D
1481cc22e LEA RSI,[R15 + 0x100]
1481cc235 MOV R14,RSI
1481cc238 MOV qword ptr [RSP + 0x40],RSI
1481cc23d MOV R12D,0xffffffff
1481cc243 MOV dword ptr [RSP + 0x48],R12D
1481cc248 MOV qword ptr [RSP + 0x4c],RBX
1481cc24d XOR EDI,EDI
1481cc24f LEA R11,[0x14bce4e94]
1481cc256 CMP dword ptr [R15 + 0x118],EBX
1481cc25d JGE 0x1481cc2aa
1481cc25f MOV R9,qword ptr [RBP + 0x1a8]
1481cc266 MOV qword ptr [RSP + 0x20],R11
1481cc26b MOV R8D,0x70b
1481cc271 LEA RDX,[0x14cf28330]
1481cc278 LEA RCX,[0x14bcf2f60]
1481cc27f CALL 0x140f8dfd0
1481cc284 TEST AL,AL
1481cc286 JZ 0x1481cc29c
1481cc288 NOP
1481cc289 INT3
1481cc29c LEA R11,[0x14bce4e94]
1481cc2a3 LEA R10,[R15 + 0xf0]
1481cc2aa MOV R9D,dword ptr [R14 + 0x18]
1481cc2ae TEST R9D,R9D
1481cc2b1 JZ 0x1481cc332
1481cc2b3 MOV RAX,qword ptr [R14 + 0x10]
1481cc2b7 TEST RAX,RAX
1481cc2ba CMOVNZ R14,RAX
1481cc2be LEA EAX,[R9 + -0x1]
1481cc2c2 CDQ
1481cc2c3 AND EDX,0x1f
1481cc2c6 LEA R8D,[RDX + RAX*0x1]
1481cc2ca SAR R8D,0x5
1481cc2ce MOVSXD RCX,EBX
1481cc2d1 MOV EDX,dword ptr [R14 + RCX*0x4]
1481cc2d5 AND EDX,R12D
1481cc2d8 JNZ 0x1481cc305
1481cc2da NOP word ptr [RAX + RAX*0x1]
1481cc2e0 INC EBX
1481cc2e2 MOV dword ptr [RSP + 0x38],EBX
1481cc2e6 ADD EDI,0x20
1481cc2e9 MOV dword ptr [RSP + 0x50],EDI
1481cc2ed CMP EBX,R8D
1481cc2f0 JG 0x1481cc32d
1481cc2f2 MOVSXD RAX,EBX
1481cc2f5 MOV EDX,dword ptr [R14 + RAX*0x4]
1481cc2f9 MOV dword ptr [RSP + 0x48],0xffffffff
1481cc301 TEST EDX,EDX
1481cc303 JZ 0x1481cc2e0
1481cc305 LEA EAX,[RDX + -0x1]
1481cc308 AND EAX,EDX
1481cc30a XOR EAX,EDX
1481cc30c MOV dword ptr [RSP + 0x3c],EAX
1481cc310 LEA RAX,[0x1 + RAX*0x2]
1481cc318 BSR RCX,RAX
1481cc31c MOV dword ptr [RBP + -0x50],ECX
1481cc31f LEA EAX,[RCX + -0x1]
1481cc322 ADD EAX,EDI
1481cc324 MOV dword ptr [RSP + 0x4c],EAX
1481cc328 CMP EAX,R9D
1481cc32b JLE 0x1481cc332
1481cc32d MOV dword ptr [RSP + 0x4c],R9D
1481cc332 MOV qword ptr [RBP + -0x80],R10
1481cc336 MOVUPS XMM0,xmmword ptr [RSP + 0x38]
1481cc33b MOVUPS xmmword ptr [RBP + -0x78],XMM0
1481cc33f MOVUPS XMM1,xmmword ptr [RSP + 0x48]
1481cc344 MOVUPS xmmword ptr [RBP + -0x68],XMM1
1481cc348 MOV EAX,dword ptr [R15 + 0xf8]
1481cc34f SUB EAX,dword ptr [R15 + 0x124]
1481cc356 MOV dword ptr [RBP + -0x58],EAX
1481cc359 MOVUPS XMM0,xmmword ptr [RBP + -0x80]
1481cc35d MOVUPS xmmword ptr [RBP + -0x48],XMM0
1481cc361 MOVUPS XMM1,xmmword ptr [RBP + -0x70]
1481cc365 MOVUPS xmmword ptr [RBP + -0x38],XMM1
1481cc369 MOVUPS XMM0,xmmword ptr [RBP + -0x60]
1481cc36d MOVUPS xmmword ptr [RBP + -0x28],XMM0
1481cc371 MOV R12D,dword ptr [R15 + 0x118]
1481cc378 MOV EBX,R12D
1481cc37b SAR EBX,0x5
1481cc37e MOV dword ptr [RSP + 0x58],EBX
1481cc382 MOV ECX,R12D
1481cc385 AND ECX,0x1f
1481cc388 SHL R13D,CL
1481cc38b MOV dword ptr [RSP + 0x5c],R13D
1481cc390 MOV qword ptr [RSP + 0x60],RSI
1481cc395 MOV R14D,0xffffffff
1481cc39b SHL R14D,CL
1481cc39e MOV dword ptr [RSP + 0x68],R14D
1481cc3a3 MOV dword ptr [RSP + 0x6c],R12D
1481cc3a8 MOV EDI,R12D
1481cc3ab AND EDI,0xffffffe0
1481cc3ae MOV dword ptr [RSP + 0x70],EDI
1481cc3b2 TEST R12D,R12D
1481cc3b5 JNS 0x1481cc3fb
1481cc3b7 MOV R9,qword ptr [RBP + 0x1a8]
1481cc3be MOV qword ptr [RSP + 0x20],R11
1481cc3c3 MOV R8D,0x70b
1481cc3c9 LEA RDX,[0x14cf28330]
1481cc3d0 LEA RCX,[0x14bcf2f60]
1481cc3d7 CALL 0x140f8dfd0
1481cc3dc TEST AL,AL
1481cc3de JZ 0x1481cc3f4
1481cc3e0 NOP
1481cc3e1 INT3
1481cc3f4 LEA R10,[R15 + 0xf0]
1481cc3fb MOV R8D,dword ptr [RSI + 0x18]
1481cc3ff CMP R12D,R8D
1481cc402 JZ 0x1481cc482
1481cc404 MOV RAX,qword ptr [RSI + 0x10]
1481cc408 TEST RAX,RAX
1481cc40b CMOVNZ RSI,RAX
1481cc40f LEA EAX,[R8 + -0x1]
1481cc413 CDQ
1481cc414 AND EDX,0x1f
1481cc417 LEA R9D,[RDX + RAX*0x1]
1481cc41b SAR R9D,0x5
1481cc41f MOVSXD RCX,EBX
1481cc422 MOV EDX,dword ptr [RSI + RCX*0x4]
1481cc425 AND EDX,R14D
1481cc428 JNZ 0x1481cc454
1481cc42a NOP word ptr [RAX + RAX*0x1]
1481cc430 INC EBX
1481cc432 MOV dword ptr [RSP + 0x58],EBX
1481cc436 ADD EDI,0x20
1481cc439 MOV dword ptr [RSP + 0x70],EDI
1481cc43d CMP EBX,R9D
1481cc440 JG 0x1481cc47d
1481cc442 MOVSXD RAX,EBX
1481cc445 MOV EDX,dword ptr [RSI + RAX*0x4]
1481cc448 MOV dword ptr [RSP + 0x68],0xffffffff
1481cc450 TEST EDX,EDX
1481cc452 JZ 0x1481cc430
1481cc454 LEA EAX,[RDX + -0x1]
1481cc457 AND EAX,EDX
1481cc459 XOR EAX,EDX
1481cc45b MOV dword ptr [RSP + 0x5c],EAX
1481cc45f LEA RAX,[0x1 + RAX*0x2]
1481cc467 BSR RCX,RAX
1481cc46b MOV dword ptr [RSP + 0x78],ECX
1481cc46f LEA EAX,[RCX + -0x1]
1481cc472 ADD EAX,EDI
1481cc474 MOV dword ptr [RSP + 0x6c],EAX
1481cc478 CMP EAX,R8D
1481cc47b JLE 0x1481cc482
1481cc47d MOV dword ptr [RSP + 0x6c],R8D
1481cc482 MOV qword ptr [RBP + -0x80],R10
1481cc486 MOVUPS XMM0,xmmword ptr [RSP + 0x58]
1481cc48b MOVUPS xmmword ptr [RBP + -0x78],XMM0
1481cc48f MOVUPS XMM1,xmmword ptr [RSP + 0x68]
1481cc494 MOVUPS xmmword ptr [RBP + -0x68],XMM1
1481cc498 MOV EAX,dword ptr [R15 + 0xf8]
1481cc49f SUB EAX,dword ptr [R15 + 0x124]
1481cc4a6 MOV dword ptr [RBP + -0x58],EAX
1481cc4a9 MOVUPS XMM0,xmmword ptr [RBP + -0x80]
1481cc4ad MOVUPS xmmword ptr [RBP + 0x68],XMM0
1481cc4b1 MOVUPS XMM1,xmmword ptr [RBP + -0x70]
1481cc4b5 MOVUPS xmmword ptr [RBP + 0x78],XMM1
1481cc4b9 MOVUPS XMM0,xmmword ptr [RBP + -0x60]
1481cc4bd MOVUPS xmmword ptr [RBP + 0x88],XMM0
1481cc4c4 XOR R12D,R12D
1481cc4c7 NOP word ptr [RAX + RAX*0x1]
1481cc4d0 MOV RBX,qword ptr [RBP + -0x48]
1481cc4d4 MOV EAX,dword ptr [RBX + 0x8]
1481cc4d7 SUB EAX,dword ptr [RBX + 0x34]
1481cc4da CMP EAX,dword ptr [RBP + -0x20]
1481cc4dd JZ 0x1481cc4f8
1481cc4df MOV byte ptr [RSP + 0x30],R12B
1481cc4e4 LEA RCX,[RSP + 0x30]
1481cc4e9 CALL 0x14bc1d2b0
1481cc4ee TEST AL,AL
1481cc4f0 JZ 0x1481cc4f8
1481cc4f2 NOP
1481cc4f3 INT3
1481cc4f8 MOVSXD RCX,dword ptr [RBP + -0x2c]
1481cc4fc CMP ECX,dword ptr [RBP + 0x84]
1481cc502 JNZ 0x1481cc514
1481cc504 MOV RAX,qword ptr [RBP + 0x78]
1481cc508 CMP qword ptr [RBP + -0x38],RAX
1481cc50c JNZ 0x1481cc514
1481cc50e CMP RBX,qword ptr [RBP + 0x68]
1481cc512 JZ 0x1481cc580
1481cc514 MOV RDI,RCX
1481cc517 SHL RDI,0x6
1481cc51b ADD RDI,qword ptr [RBX]
1481cc51e CMP byte ptr [RDI + 0x20],R12B
1481cc522 JNZ 0x1481cc56a
1481cc524 MOV byte ptr [RDI + 0x20],R12B
1481cc528 MOV RBX,qword ptr [RDI + 0x10]
1481cc52c MOVSXD R14,dword ptr [RDI + 0x18]
1481cc530 MOV RSI,R14
1481cc533 SHL RSI,0x4
1481cc537 ADD RSI,RBX
1481cc53a NOP word ptr [RAX + RAX*0x1]
1481cc540 CMP dword ptr [RDI + 0x18],R14D
1481cc544 JZ 0x1481cc55b
1481cc546 MOV byte ptr [RSP + 0x31],R12B
1481cc54b LEA RCX,[RSP + 0x31]
1481cc550 CALL 0x14bc1d120
1481cc555 TEST AL,AL
1481cc557 JZ 0x1481cc55b
1481cc559 NOP
1481cc55a INT3
1481cc55b CMP RBX,RSI
1481cc55e JZ 0x1481cc56a
1481cc560 MOV dword ptr [RBX + 0xc],R12D
1481cc564 ADD RBX,0x10
1481cc568 JMP 0x1481cc540
1481cc56a MOV EAX,dword ptr [RBP + -0x3c]
1481cc56d NOT EAX
1481cc56f AND dword ptr [RBP + -0x30],EAX
1481cc572 LEA RCX,[RBP + -0x40]
1481cc576 CALL 0x140d10990
1481cc57b JMP 0x1481cc4d0
1481cc580 MOV RAX,qword ptr [R15]
1481cc583 MOV RCX,R15
1481cc586 CALL qword ptr [RAX + 0x188]
1481cc58c MOV RCX,RAX
1481cc58f CALL 0x147a1e670
1481cc594 MOV RBX,RAX
1481cc597 MOV qword ptr [RBP + 0x148],R15
1481cc59e LEA RAX,[0x14cf77840]
1481cc5a5 MOV qword ptr [RBP + 0x140],RAX
1481cc5ac LEA RCX,[0x1481b4ba0]
1481cc5b3 MOV qword ptr [RBP + 0x120],RCX
1481cc5ba LEA RAX,[0x14cf777f8]
1481cc5c1 MOV qword ptr [RBP + 0x160],RAX
1481cc5c8 LEA RAX,[RBP + 0x148]
1481cc5cf MOV qword ptr [RBP + 0x168],RAX
1481cc5d6 XOR EDI,EDI
1481cc5d8 MOV qword ptr [RBP + 0xa0],RDI
1481cc5df MOV dword ptr [RBP + 0xa8],EDI
1481cc5e5 LEA RAX,[RBP + 0xb0]
1481cc5ec MOV qword ptr [RSP + 0x78],RAX
1481cc5f1 MOV qword ptr [RBP + 0xb0],RDI
1481cc5f8 MOV qword ptr [RBP + 0xb8],RDI
1481cc5ff MOV qword ptr [RBP + 0xc0],RDI
1481cc606 LEA RAX,[RBP + 0xd0]
1481cc60d MOV qword ptr [RSP + 0x78],RAX
1481cc612 MOV qword ptr [RBP + 0xd0],RCX
1481cc619 MOV qword ptr [RBP + 0xe0],RDI
1481cc620 MOV qword ptr [RBP + 0x130],RDI
1481cc627 LEA RCX,[RBP + 0xf0]
1481cc62e MOVAPS XMM0,xmmword ptr [RBP + 0x140]
1481cc635 MOVAPS xmmword ptr [RBP + 0xf0],XMM0
1481cc63c MOVAPS XMM1,xmmword ptr [RBP + 0x150]
1481cc643 MOVAPS xmmword ptr [RBP + 0x100],XMM1
1481cc64a MOVAPS XMM0,xmmword ptr [RBP + 0x160]
1481cc651 MOVDQA xmmword ptr [RBP + 0x110],XMM0
1481cc659 MOV RAX,qword ptr [0x14cf77848]
1481cc660 CALL RAX
1481cc662 MOV qword ptr [RBP + 0x118],RAX
1481cc669 MOV qword ptr [RBP + 0x120],RDI
1481cc670 LEA RDX,[R15 + 0x48]
1481cc674 MOVSS XMM0,dword ptr [0x14bd17874]
1481cc67c MOVSS dword ptr [RSP + 0x28],XMM0
1481cc682 MOV byte ptr [RSP + 0x20],0x1
1481cc687 MOVSS XMM3,dword ptr [0x14bcef9ec]
1481cc68f LEA R8,[RBP + 0xa0]
1481cc696 MOV RCX,RBX
1481cc699 CALL 0x1478cf760
1481cc69e NOP
1481cc69f CMP qword ptr [RBP + 0xd0],RDI
1481cc6a6 JZ 0x1481cc6c3
1481cc6a8 MOV RAX,qword ptr [RBP + 0xe0]
1481cc6af LEA RCX,[RBP + 0xf0]
1481cc6b6 TEST RAX,RAX
1481cc6b9 CMOVNZ RCX,RAX
1481cc6bd MOV RAX,qword ptr [RCX]
1481cc6c0 CALL qword ptr [RAX + 0x10]
1481cc6c3 LEA RAX,[0x14d3ac0f0]
1481cc6ca MOV qword ptr [RBP + 0x110],RAX
1481cc6d1 LEA RCX,[RBP + 0xb0]
1481cc6d8 CALL 0x140c70210
1481cc6dd NOP
1481cc6de MOV RCX,qword ptr [RBP + 0xa0]
1481cc6e5 CMP dword ptr [RBP + 0xa8],0x0
1481cc6ec JZ 0x1481cc71e
1481cc6ee TEST RCX,RCX
1481cc6f1 JZ 0x1481cc71e
1481cc6f3 MOV RAX,qword ptr [RCX]
1481cc6f6 XOR EDX,EDX
1481cc6f8 CALL qword ptr [RAX]
1481cc6fa MOV R9D,0x10
1481cc700 XOR R8D,R8D
1481cc703 XOR EDX,EDX
1481cc705 LEA RCX,[RBP + 0xa0]
1481cc70c CALL 0x140d20c70
1481cc711 MOV dword ptr [RBP + 0xa8],EDI
1481cc717 MOV RCX,qword ptr [RBP + 0xa0]
1481cc71e TEST RCX,RCX
1481cc721 JZ 0x1481cc729
1481cc723 CALL 0x140e282f0
1481cc728 NOP
1481cc729 CMP qword ptr [RBP + 0x120],0x0
1481cc731 JZ 0x1481cc74f
1481cc733 MOV RAX,qword ptr [RBP + 0x130]
1481cc73a LEA RCX,[RBP + 0x140]
1481cc741 TEST RAX,RAX
1481cc744 CMOVNZ RCX,RAX
1481cc748 MOV RAX,qword ptr [RCX]
1481cc74b CALL qword ptr [RAX + 0x10]
1481cc74e NOP
1481cc74f CMP byte ptr [0x14eab53c8],0x3
1481cc756 JC 0x1481cc76b
1481cc758 LEA RDX,[0x14cf71b28]
1481cc75f LEA RCX,[0x14eab53c8]
1481cc766 CALL 0x140f24ba0
1481cc76b MOV RCX,qword ptr [RBP + 0x170]
1481cc772 XOR RCX,RSP
1481cc775 CALL 0x14b880380
1481cc77a LEA R11,[RSP + 0x280]
1481cc782 MOV RBX,qword ptr [R11 + 0x38]
1481cc786 MOV RSI,qword ptr [R11 + 0x40]
1481cc78a MOV RDI,qword ptr [R11 + 0x48]
1481cc78e MOV RSP,R11
1481cc791 POP R15
1481cc793 POP R14
1481cc795 POP R13
1481cc797 POP R12
1481cc799 POP RBP
1481cc79a RET
*/

/* 1481b6d20 EndSession */

void EndSession(longlong *param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  undefined8 uVar6;
  longlong lVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  ulonglong *puVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  undefined8 *puVar14;
  longlong *plVar15;
  ulonglong *puVar16;
  longlong lVar17;
  ulonglong *puVar18;
  undefined8 unaff_retaddr;
  longlong *plStackX_8;
  undefined1 auStackX_18 [8];
  int iStackX_20;
  longlong lStack_e8;
  int iStack_e0;
  undefined4 uStack_dc;
  uint uStack_d8;
  ulonglong *puStack_d0;
  undefined8 uStack_c8;
  ulonglong *puStack_c0;
  ulonglong *puStack_b8;
  undefined8 *puStack_b0;
  uint uStack_a8;
  ulonglong *puStack_a0;
  ulonglong *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  longlong lStack_80;
  ulonglong uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  uVar6 = (**(code **)(*param_1 + 0x188))();
  uVar6 = func_0x000147a1e670(uVar6);
  lVar7 = func_0x00014789e110(uVar6,param_1 + 9);
  if (lVar7 != 0) {
    func_0x0001478cf210(uVar6,param_1[9]);
  }
  param_1[9] = 0;
  func_0x0001481538d0(param_1 + 0x46,param_2);
  lVar7 = (**(code **)(*param_1 + 0x188))(param_1);
  *(int *)(param_1 + 0x4b) = (int)(*(double *)(lVar7 + 0x740) - (double)*(float *)(param_1 + 0x66));
  iVar4 = func_0x0001481b49f0(param_1,param_1 + 0x46);
  func_0x000140cf7080(&lStack_80,"Session Complete");
  lVar7 = lStack_80;
  if (0 < iVar4) {
    *(int *)(param_1 + 8) = (int)param_1[8] + iVar4;
    *(int *)((longlong)param_1 + 0x54) = *(int *)((longlong)param_1 + 0x54) + iVar4;
    plStackX_8 = &lStack_e8;
    lStack_e8 = 0;
    iVar13 = (int)uStack_78;
    iStack_e0 = iVar13;
    if (iVar13 == 0) {
      uStack_dc = 0;
    }
    else {
      func_0x000140ca39a0(&lStack_e8,uStack_78 & 0xffffffff,0);
      func_0x00014b89502e(lStack_e8,lVar7,(longlong)iVar13 * 2);
    }
    plStackX_8 = &lStack_e8;
    func_0x000148155e80(param_1 + 0x6f,iVar4,&lStack_e8);
    if (lStack_e8 != 0) {
      func_0x000140e282f0();
    }
    func_0x0001481b4f10(param_1);
    uStack_90 = 0;
    uStack_88 = 0;
    UpdateMetricWithConditions(param_1,0xf,iVar4,&uStack_90);
  }
  if (lStack_80 != 0) {
    func_0x000140e282f0();
  }
  func_0x0001481ce070(param_1,0,(int)param_1[0x46]);
  func_0x0001481ce070(param_1,1,*(undefined4 *)((longlong)param_1 + 0x234));
  func_0x0001481ce070(param_1,2,(int)param_1[0x47]);
  func_0x0001481ce070(param_1,3,*(undefined4 *)((longlong)param_1 + 0x23c));
  func_0x0001481ce070(param_1,4,(int)param_1[0x48]);
  func_0x0001481ce070(param_1,0x11,(int)param_1[0x50]);
  func_0x0001481ce070(param_1,0x12,*(undefined4 *)((longlong)param_1 + 0x284));
  func_0x0001481ce070(param_1,0xc,(int)param_1[0x4b]);
  func_0x0001481ce070(param_1,6,*(undefined4 *)((longlong)param_1 + 0x244));
  func_0x0001481ce070(param_1,8,*(undefined4 *)((longlong)param_1 + 0x24c));
  func_0x0001481ce070(param_1,10,(int)param_1[0x4a]);
  func_0x0001481ce070(param_1,0x17,(int)param_1[0x51]);
  func_0x0001481ce070(param_1,0x13,(int)param_1[0x52]);
  func_0x0001481ce070(param_1,0x10,*(undefined4 *)((longlong)param_1 + 0x294));
  func_0x0001481ce070(param_1,0x18,*(undefined4 *)((longlong)param_1 + 0x28c));
  func_0x0001481ce070(param_1,0x1a,*(undefined4 *)((longlong)param_1 + 0x29c));
  func_0x0001481ce070(param_1,0x1b,(int)param_1[0x54]);
  func_0x0001481ce070(param_1,0x1c,*(undefined4 *)((longlong)param_1 + 0x2a4));
  func_0x0001481ce070(param_1,0x1d,(int)param_1[0x55]);
  *(int *)(param_1 + 0x56) = (int)param_1[0x56] + (int)param_1[0x46];
  *(int *)((longlong)param_1 + 0x2b4) =
       *(int *)((longlong)param_1 + 0x2b4) + *(int *)((longlong)param_1 + 0x234);
  *(int *)(param_1 + 0x57) = (int)param_1[0x57] + (int)param_1[0x47];
  *(int *)((longlong)param_1 + 700) =
       *(int *)((longlong)param_1 + 700) + *(int *)((longlong)param_1 + 0x23c);
  *(int *)(param_1 + 0x5b) = (int)param_1[0x5b] + (int)param_1[0x4b];
  *(int *)((longlong)param_1 + 0x2c4) =
       *(int *)((longlong)param_1 + 0x2c4) + *(int *)((longlong)param_1 + 0x244);
  *(int *)((longlong)param_1 + 0x2cc) =
       *(int *)((longlong)param_1 + 0x2cc) + *(int *)((longlong)param_1 + 0x24c);
  *(int *)(param_1 + 0x59) = (int)param_1[0x59] + (int)param_1[0x49];
  *(int *)(param_1 + 0x5a) = (int)param_1[0x5a] + (int)param_1[0x4a];
  *(int *)((longlong)param_1 + 0x2d4) =
       *(int *)((longlong)param_1 + 0x2d4) + *(int *)((longlong)param_1 + 0x254);
  *(int *)(param_1 + 0x61) = (int)param_1[0x61] + (int)param_1[0x51];
  *(int *)(param_1 + 0x62) = (int)param_1[0x62] + (int)param_1[0x52];
  *(int *)((longlong)param_1 + 0x314) =
       *(int *)((longlong)param_1 + 0x314) + *(int *)((longlong)param_1 + 0x294);
  *(int *)(param_1 + 99) = (int)param_1[99] + (int)param_1[0x53];
  *(int *)((longlong)param_1 + 0x31c) =
       *(int *)((longlong)param_1 + 0x31c) + *(int *)((longlong)param_1 + 0x29c);
  *(int *)(param_1 + 100) = (int)param_1[100] + (int)param_1[0x54];
  *(int *)((longlong)param_1 + 0x324) =
       *(int *)((longlong)param_1 + 0x324) + *(int *)((longlong)param_1 + 0x2a4);
  *(int *)(param_1 + 0x65) = (int)param_1[0x65] + (int)param_1[0x55];
  *(int *)((longlong)param_1 + 0x2e4) = *(int *)((longlong)param_1 + 0x2e4) + 1;
  if ((int)param_1[0x58] < (int)param_1[0x48]) {
    *(int *)(param_1 + 0x58) = (int)param_1[0x48];
  }
  if ((int)param_1[0x60] < (int)param_1[0x50]) {
    *(int *)(param_1 + 0x60) = (int)param_1[0x50];
  }
  if (*(int *)((longlong)param_1 + 0x304) < *(int *)((longlong)param_1 + 0x284)) {
    *(int *)((longlong)param_1 + 0x304) = *(int *)((longlong)param_1 + 0x284);
  }
  if ((int)param_1[0x4c] < 1) {
    uStack_60 = 0;
    uStack_58 = 0;
    UpdateMetricWithConditions(param_1,0x15,1,&uStack_60);
  }
  else {
    *(int *)(param_1 + 0x5c) = (int)param_1[0x5c] + 1;
    uStack_70 = 0;
    uStack_68 = 0;
    UpdateMetricWithConditions(param_1,0xe,1,&uStack_70);
  }
  if (0 < (int)param_1[0x4d]) {
    *(int *)(param_1 + 0x5d) = (int)param_1[0x5d] + (int)param_1[0x4d];
  }
  uStack_50 = 0;
  uStack_48 = 0;
  UpdateMetricWithConditions(param_1,0xd,1,&uStack_50);
  puStack_d0 = (ulonglong *)0x0;
  uStack_c8 = 0;
  func_0x0001481b2b20(param_1 + 0x3c,0x10,&puStack_d0,0);
  uVar8 = (ulonglong)(int)(uint)uStack_c8;
  uStack_d8 = (uint)uStack_c8;
  puStack_98 = puStack_d0 + uVar8;
  puVar16 = puStack_d0;
LAB_1481b71cd:
  puVar10 = puStack_98;
  puStack_b8 = puVar16;
  if ((uint)uStack_c8 != (int)uVar8) {
    plStackX_8 = (longlong *)((ulonglong)plStackX_8 & 0xffffffffffffff00);
    cVar3 = func_0x00014bae9430(&plStackX_8);
    if (cVar3 != '\0') {
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
  }
  if (puVar16 == puVar10) {
    func_0x0001481cad00(param_1);
    if (2 < DAT_14eab53c8) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf71c18);
    }
    if (puStack_d0 != (ulonglong *)0x0) {
      func_0x000140e282f0();
    }
    return;
  }
  uVar8 = *puVar16;
  if (param_1[0xc] != 0) {
    func_0x0001468fb0a0(param_1[0xc],&puStack_b0);
    uVar11 = uStack_a8;
    uVar9 = (ulonglong)(int)uStack_a8;
    puVar1 = puStack_b0 + uVar9;
    puVar14 = puStack_b0;
    while( true ) {
      if ((uint)uVar9 != uVar11) {
        auStackX_18[0] = 0;
        cVar3 = func_0x00014bae9430(auStackX_18);
        if (cVar3 != '\0') {
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
      }
      if (puVar14 == puVar1) {
        if (puStack_b0 != (undefined8 *)0x0) {
          func_0x000140e282f0();
        }
        goto LAB_1481b74be;
      }
      lVar7 = func_0x0001481b11d0(param_1[0xc],*puVar14,&UNK_14bce4e94,1);
      if ((lVar7 != 0) && (*(ulonglong *)(lVar7 + 8) == uVar8)) break;
      puVar14 = puVar14 + 1;
      uVar9 = (ulonglong)uStack_a8;
    }
    if (puStack_b0 != (undefined8 *)0x0) {
      func_0x000140e282f0();
    }
    if (*(char *)(lVar7 + 0x68) == '\0') {
      uVar8 = *puVar16;
      iVar4 = func_0x0001411c2eb0(uVar8 & 0xffffffff);
      if ((int)param_1[0x1f] != *(int *)((longlong)param_1 + 0x124)) {
        plVar15 = param_1 + 0x25;
        if ((longlong *)param_1[0x26] != (longlong *)0x0) {
          plVar15 = (longlong *)param_1[0x26];
        }
        iVar4 = *(int *)((longlong)plVar15 +
                        (ulonglong)((int)param_1[0x27] - 1U & iVar4 + (int)(uVar8 >> 0x20)) * 4);
        if (iVar4 != -1) {
          while (puVar10 = (ulonglong *)((longlong)iVar4 * 0x40 + param_1[0x1e]), *puVar10 != uVar8)
          {
            iVar4 = (int)puVar10[7];
            if (iVar4 == -1) goto code_r0x0001481b72f8;
          }
          puVar18 = puVar10 + 1;
          if (puVar10 == (ulonglong *)0x0) {
            puVar18 = (ulonglong *)0x0;
          }
          if (puVar18 == (ulonglong *)0x0) goto LAB_1481b74be;
          uVar11 = 0;
          puStack_a0 = puVar18 + 2;
          if ((int)*puStack_a0 < 1) goto LAB_1481b74be;
          puStack_c0 = puVar18 + 1;
          lVar7 = 0;
          lVar17 = 0;
          do {
            uVar12 = ~uVar11 >> 0x1f;
            uVar5 = 0;
            if ((int)uVar11 < (int)puStack_c0[1]) {
              uVar5 = uVar12;
            }
            if ((uVar5 == 0) &&
               (cVar3 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                            &UNK_14bce6ef0,(longlong)(int)uVar11,
                                            (longlong)(int)puStack_c0[1]), cVar3 != '\0')) {
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
            if (((*(char *)(*puStack_c0 + lVar17) == '\x10') && (-1 < (int)uVar11)) &&
               ((int)uVar11 < (int)puVar18[5])) {
              uVar5 = 0;
              if ((int)uVar11 < (int)puVar18[5]) {
                uVar5 = uVar12;
              }
              if ((uVar5 == 0) &&
                 (cVar3 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                              &UNK_14bce6ef0,(longlong)(int)uVar11,
                                              (longlong)(int)puVar18[5]), cVar3 != '\0')) {
                pcVar2 = (code *)swi(3);
                (*pcVar2)();
                return;
              }
              iStackX_20 = *(int *)((longlong)param_1 + 0x294);
              if (*(int *)(lVar7 + puVar18[4]) < iStackX_20) {
                uVar5 = 0;
                if ((int)uVar11 < (int)puVar18[5]) {
                  uVar5 = uVar12;
                }
                if ((uVar5 == 0) &&
                   (cVar3 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr,
                                                &UNK_14bce6ef0,(longlong)(int)uVar11,
                                                (longlong)(int)puVar18[5]), cVar3 != '\0')) {
                  pcVar2 = (code *)swi(3);
                  (*pcVar2)();
                  return;
                }
                *(int *)(lVar7 + puVar18[4]) = iStackX_20;
              }
            }
            uVar11 = uVar11 + 1;
            lVar17 = lVar17 + 0x10;
            lVar7 = lVar7 + 4;
          } while ((int)uVar11 < (int)*puStack_a0);
          puVar16 = puStack_b8 + 1;
          uVar8 = (ulonglong)uStack_d8;
          goto LAB_1481b71cd;
        }
      }
    }
  }
LAB_1481b74be:
  puVar16 = puVar16 + 1;
  uVar8 = (ulonglong)uStack_d8;
  goto LAB_1481b71cd;
code_r0x0001481b72f8:
  puVar16 = puVar16 + 1;
  uVar8 = (ulonglong)uStack_d8;
  goto LAB_1481b71cd;
}


/* Instruction evidence:
1481b6d20 MOV qword ptr [RSP + 0x10],RBX
1481b6d25 PUSH RBP
1481b6d26 PUSH RSI
1481b6d27 PUSH RDI
1481b6d28 PUSH R12
1481b6d2a PUSH R13
1481b6d2c PUSH R14
1481b6d2e PUSH R15
1481b6d30 LEA RBP,[RSP + -0x27]
1481b6d35 SUB RSP,0xf0
1481b6d3c MOV R14,RDX
1481b6d3f MOV R15,RCX
1481b6d42 MOV RAX,qword ptr [RCX]
1481b6d45 CALL qword ptr [RAX + 0x188]
1481b6d4b MOV RCX,RAX
1481b6d4e CALL 0x147a1e670
1481b6d53 MOV RDI,RAX
1481b6d56 LEA RDX,[R15 + 0x48]
1481b6d5a MOV RCX,RAX
1481b6d5d CALL 0x14789e110
1481b6d62 TEST RAX,RAX
1481b6d65 JZ 0x1481b6d73
1481b6d67 MOV RDX,qword ptr [R15 + 0x48]
1481b6d6b MOV RCX,RDI
1481b6d6e CALL 0x1478cf210
1481b6d73 XOR R13D,R13D
1481b6d76 MOV qword ptr [R15 + 0x48],R13
1481b6d7a MOV RDX,R14
1481b6d7d LEA RCX,[R15 + 0x230]
1481b6d84 CALL 0x1481538d0
1481b6d89 MOV RAX,qword ptr [R15]
1481b6d8c MOV RCX,R15
1481b6d8f CALL qword ptr [RAX + 0x188]
1481b6d95 MOVSS XMM0,dword ptr [R15 + 0x330]
1481b6d9e CVTPS2PD XMM0,XMM0
1481b6da1 MOVSD XMM1,qword ptr [RAX + 0x740]
1481b6da9 SUBSD XMM1,XMM0
1481b6dad CVTTSD2SI EAX,XMM1
1481b6db1 MOV dword ptr [R15 + 0x258],EAX
1481b6db8 LEA RDX,[R15 + 0x230]
1481b6dbf MOV RCX,R15
1481b6dc2 CALL 0x1481b49f0
1481b6dc7 MOV EBX,EAX
1481b6dc9 LEA RDX,[0x14cf71c90]
1481b6dd0 LEA RCX,[RBP + -0x21]
1481b6dd4 CALL 0x140cf7080
1481b6dd9 NOP
1481b6dda TEST EBX,EBX
1481b6ddc JLE 0x1481b6e80
1481b6de2 ADD dword ptr [R15 + 0x40],EBX
1481b6de6 ADD dword ptr [R15 + 0x54],EBX
1481b6dea LEA RAX,[RSP + 0x40]
1481b6def MOV qword ptr [RBP + 0x67],RAX
1481b6df3 MOV qword ptr [RSP + 0x40],R13
1481b6df8 MOV RDI,qword ptr [RBP + -0x19]
1481b6dfc MOV R12,qword ptr [RBP + -0x21]
1481b6e00 MOV dword ptr [RSP + 0x48],EDI
1481b6e04 TEST EDI,EDI
1481b6e06 JNZ 0x1481b6e0e
1481b6e08 MOV dword ptr [RBP + -0x7d],R13D
1481b6e0c JMP 0x1481b6e31
1481b6e0e XOR R8D,R8D
1481b6e11 MOV EDX,EDI
1481b6e13 LEA RCX,[RSP + 0x40]
1481b6e18 CALL 0x140ca39a0
1481b6e1d MOVSXD R8,EDI
1481b6e20 ADD R8,R8
1481b6e23 MOV RDX,R12
1481b6e26 MOV RCX,qword ptr [RSP + 0x40]
1481b6e2b CALL 0x14b89502e
1481b6e30 NOP
1481b6e31 LEA RAX,[RSP + 0x40]
1481b6e36 MOV qword ptr [RBP + 0x67],RAX
1481b6e3a LEA R8,[RSP + 0x40]
1481b6e3f MOV EDX,EBX
1481b6e41 LEA RCX,[R15 + 0x378]
1481b6e48 CALL 0x148155e80
1481b6e4d NOP
1481b6e4e MOV RCX,qword ptr [RSP + 0x40]
1481b6e53 TEST RCX,RCX
1481b6e56 JZ 0x1481b6e5e
1481b6e58 CALL 0x140e282f0
1481b6e5d NOP
1481b6e5e MOV RCX,R15
1481b6e61 CALL 0x1481b4f10
1481b6e66 MOV qword ptr [RBP + -0x31],R13
1481b6e6a MOV qword ptr [RBP + -0x29],R13
1481b6e6e LEA R9,[RBP + -0x31]
1481b6e72 MOV R8D,EBX
1481b6e75 MOV DL,0xf
1481b6e77 MOV RCX,R15
1481b6e7a CALL 0x1481ce250
1481b6e7f NOP
1481b6e80 MOV RCX,qword ptr [RBP + -0x21]
1481b6e84 TEST RCX,RCX
1481b6e87 JZ 0x1481b6e8f
1481b6e89 CALL 0x140e282f0
1481b6e8e NOP
1481b6e8f MOV R8D,dword ptr [R15 + 0x230]
1481b6e96 XOR EDX,EDX
1481b6e98 MOV RCX,R15
1481b6e9b CALL 0x1481ce070
1481b6ea0 MOV R8D,dword ptr [R15 + 0x234]
1481b6ea7 MOV DL,0x1
1481b6ea9 MOV RCX,R15
1481b6eac CALL 0x1481ce070
1481b6eb1 MOV R8D,dword ptr [R15 + 0x238]
1481b6eb8 MOV DL,0x2
1481b6eba MOV RCX,R15
1481b6ebd CALL 0x1481ce070
1481b6ec2 MOV R8D,dword ptr [R15 + 0x23c]
1481b6ec9 MOV DL,0x3
1481b6ecb MOV RCX,R15
1481b6ece CALL 0x1481ce070
1481b6ed3 MOV R8D,dword ptr [R15 + 0x240]
1481b6eda MOV DL,0x4
1481b6edc MOV RCX,R15
1481b6edf CALL 0x1481ce070
1481b6ee4 MOV R8D,dword ptr [R15 + 0x280]
1481b6eeb MOV DL,0x11
1481b6eed MOV RCX,R15
1481b6ef0 CALL 0x1481ce070
1481b6ef5 MOV R8D,dword ptr [R15 + 0x284]
1481b6efc MOV DL,0x12
1481b6efe MOV RCX,R15
1481b6f01 CALL 0x1481ce070
1481b6f06 MOV R8D,dword ptr [R15 + 0x258]
1481b6f0d MOV DL,0xc
1481b6f0f MOV RCX,R15
1481b6f12 CALL 0x1481ce070
1481b6f17 MOV R8D,dword ptr [R15 + 0x244]
1481b6f1e MOV DL,0x6
1481b6f20 MOV RCX,R15
1481b6f23 CALL 0x1481ce070
1481b6f28 MOV R8D,dword ptr [R15 + 0x24c]
1481b6f2f MOV DL,0x8
1481b6f31 MOV RCX,R15
1481b6f34 CALL 0x1481ce070
1481b6f39 MOV R8D,dword ptr [R15 + 0x250]
1481b6f40 MOV DL,0xa
1481b6f42 MOV RCX,R15
1481b6f45 CALL 0x1481ce070
1481b6f4a MOV R8D,dword ptr [R15 + 0x288]
1481b6f51 MOV DL,0x17
1481b6f53 MOV RCX,R15
1481b6f56 CALL 0x1481ce070
1481b6f5b MOV R8D,dword ptr [R15 + 0x290]
1481b6f62 MOV DL,0x13
1481b6f64 MOV RCX,R15
1481b6f67 CALL 0x1481ce070
1481b6f6c MOV R8D,dword ptr [R15 + 0x294]
1481b6f73 MOV DL,0x10
1481b6f75 MOV RCX,R15
1481b6f78 CALL 0x1481ce070
1481b6f7d MOV R8D,dword ptr [R15 + 0x28c]
1481b6f84 MOV DL,0x18
1481b6f86 MOV RCX,R15
1481b6f89 CALL 0x1481ce070
1481b6f8e MOV R8D,dword ptr [R15 + 0x29c]
1481b6f95 MOV DL,0x1a
1481b6f97 MOV RCX,R15
1481b6f9a CALL 0x1481ce070
1481b6f9f MOV R8D,dword ptr [R15 + 0x2a0]
1481b6fa6 MOV DL,0x1b
1481b6fa8 MOV RCX,R15
1481b6fab CALL 0x1481ce070
1481b6fb0 MOV R8D,dword ptr [R15 + 0x2a4]
1481b6fb7 MOV DL,0x1c
1481b6fb9 MOV RCX,R15
1481b6fbc CALL 0x1481ce070
1481b6fc1 MOV R8D,dword ptr [R15 + 0x2a8]
1481b6fc8 MOV DL,0x1d
1481b6fca MOV RCX,R15
1481b6fcd CALL 0x1481ce070
1481b6fd2 MOV EAX,dword ptr [R15 + 0x230]
1481b6fd9 ADD dword ptr [R15 + 0x2b0],EAX
1481b6fe0 MOV EAX,dword ptr [R15 + 0x234]
1481b6fe7 ADD dword ptr [R15 + 0x2b4],EAX
1481b6fee MOV EAX,dword ptr [R15 + 0x238]
1481b6ff5 ADD dword ptr [R15 + 0x2b8],EAX
1481b6ffc MOV EAX,dword ptr [R15 + 0x23c]
1481b7003 ADD dword ptr [R15 + 0x2bc],EAX
1481b700a MOV EAX,dword ptr [R15 + 0x258]
1481b7011 ADD dword ptr [R15 + 0x2d8],EAX
1481b7018 MOV EAX,dword ptr [R15 + 0x244]
1481b701f ADD dword ptr [R15 + 0x2c4],EAX
1481b7026 MOV EAX,dword ptr [R15 + 0x24c]
1481b702d ADD dword ptr [R15 + 0x2cc],EAX
1481b7034 MOV EAX,dword ptr [R15 + 0x248]
1481b703b ADD dword ptr [R15 + 0x2c8],EAX
1481b7042 MOV EAX,dword ptr [R15 + 0x250]
1481b7049 ADD dword ptr [R15 + 0x2d0],EAX
1481b7050 MOV EAX,dword ptr [R15 + 0x254]
1481b7057 ADD dword ptr [R15 + 0x2d4],EAX
1481b705e MOV EAX,dword ptr [R15 + 0x288]
1481b7065 ADD dword ptr [R15 + 0x308],EAX
1481b706c MOV EAX,dword ptr [R15 + 0x290]
1481b7073 ADD dword ptr [R15 + 0x310],EAX
1481b707a MOV EAX,dword ptr [R15 + 0x294]
1481b7081 ADD dword ptr [R15 + 0x314],EAX
1481b7088 MOV EAX,dword ptr [R15 + 0x298]
1481b708f ADD dword ptr [R15 + 0x318],EAX
1481b7096 MOV EAX,dword ptr [R15 + 0x29c]
1481b709d ADD dword ptr [R15 + 0x31c],EAX
1481b70a4 MOV EAX,dword ptr [R15 + 0x2a0]
1481b70ab ADD dword ptr [R15 + 0x320],EAX
1481b70b2 MOV EAX,dword ptr [R15 + 0x2a4]
1481b70b9 ADD dword ptr [R15 + 0x324],EAX
1481b70c0 MOV EAX,dword ptr [R15 + 0x2a8]
1481b70c7 ADD dword ptr [R15 + 0x328],EAX
1481b70ce INC dword ptr [R15 + 0x2e4]
1481b70d5 MOV EAX,dword ptr [R15 + 0x240]
1481b70dc CMP EAX,dword ptr [R15 + 0x2c0]
1481b70e3 JLE 0x1481b70ec
1481b70e5 MOV dword ptr [R15 + 0x2c0],EAX
1481b70ec MOV EAX,dword ptr [R15 + 0x280]
1481b70f3 CMP EAX,dword ptr [R15 + 0x300]
1481b70fa JLE 0x1481b7103
1481b70fc MOV dword ptr [R15 + 0x300],EAX
1481b7103 MOV EAX,dword ptr [R15 + 0x284]
1481b710a CMP EAX,dword ptr [R15 + 0x304]
1481b7111 JLE 0x1481b711a
1481b7113 MOV dword ptr [R15 + 0x304],EAX
1481b711a CMP dword ptr [R15 + 0x260],0x0
1481b7122 JLE 0x1481b714a
1481b7124 INC dword ptr [R15 + 0x2e0]
1481b712b MOV qword ptr [RBP + -0x11],R13
1481b712f MOV qword ptr [RBP + -0x9],R13
1481b7133 LEA R9,[RBP + -0x11]
1481b7137 MOV R8D,0x1
1481b713d MOV DL,0xe
1481b713f MOV RCX,R15
1481b7142 CALL 0x1481ce250
1481b7147 NOP
1481b7148 JMP 0x1481b7167
1481b714a MOV qword ptr [RBP + -0x1],R13
1481b714e MOV qword ptr [RBP + 0x7],R13
1481b7152 LEA R9,[RBP + -0x1]
1481b7156 MOV R8D,0x1
1481b715c MOV DL,0x15
1481b715e MOV RCX,R15
1481b7161 CALL 0x1481ce250
1481b7166 NOP
1481b7167 MOV EAX,dword ptr [R15 + 0x268]
1481b716e TEST EAX,EAX
1481b7170 JLE 0x1481b7179
1481b7172 ADD dword ptr [R15 + 0x2e8],EAX
1481b7179 MOV qword ptr [RBP + 0xf],R13
1481b717d MOV qword ptr [RBP + 0x17],R13
1481b7181 LEA R9,[RBP + 0xf]
1481b7185 MOV R8D,0x1
1481b718b MOV DL,0xd
1481b718d MOV RCX,R15
1481b7190 CALL 0x1481ce250
1481b7195 NOP
1481b7196 MOV qword ptr [RBP + -0x71],R13
1481b719a MOV qword ptr [RBP + -0x69],R13
1481b719e LEA RCX,[R15 + 0x1e0]
1481b71a5 XOR R9D,R9D
1481b71a8 LEA R8,[RBP + -0x71]
1481b71ac MOV DL,0x10
1481b71ae CALL 0x1481b2b20
1481b71b3 MOV R13,qword ptr [RBP + -0x71]
1481b71b7 MOVSXD RCX,dword ptr [RBP + -0x69]
1481b71bb MOV dword ptr [RBP + -0x79],ECX
1481b71be LEA RBX,[RCX*0x8]
1481b71c6 ADD RBX,R13
1481b71c9 MOV qword ptr [RBP + -0x39],RBX
1481b71cd MOV qword ptr [RBP + -0x59],R13
1481b71d1 CMP dword ptr [RBP + -0x69],ECX
1481b71d4 JZ 0x1481b71e9
1481b71d6 MOV byte ptr [RBP + 0x67],0x0
1481b71da LEA RCX,[RBP + 0x67]
1481b71de CALL 0x14bae9430
1481b71e3 TEST AL,AL
1481b71e5 JZ 0x1481b71e9
1481b71e7 NOP
1481b71e8 INT3
1481b71e9 CMP R13,RBX
1481b71ec JZ 0x1481b74ce
1481b71f2 MOV RBX,qword ptr [R13]
1481b71f6 MOV RCX,qword ptr [R15 + 0x60]
1481b71fa TEST RCX,RCX
1481b71fd JZ 0x1481b74be
1481b7203 LEA RDX,[RBP + -0x51]
1481b7207 CALL 0x1468fb0a0
1481b720c NOP
1481b720d MOV RDI,qword ptr [RBP + -0x51]
1481b7211 MOVSXD RCX,dword ptr [RBP + -0x49]
1481b7215 MOV R14,RCX
1481b7218 LEA R12,[RDI + RCX*0x8]
1481b721c NOP dword ptr [RAX]
1481b7220 CMP ECX,R14D
1481b7223 JZ 0x1481b7238
1481b7225 MOV byte ptr [RBP + 0x77],0x0
1481b7229 LEA RCX,[RBP + 0x77]
1481b722d CALL 0x14bae9430
1481b7232 TEST AL,AL
1481b7234 JZ 0x1481b7238
1481b7236 NOP
1481b7237 INT3
1481b7238 CMP RDI,R12
1481b723b JZ 0x1481b74af
1481b7241 MOV R9B,0x1
1481b7244 LEA R8,[0x14bce4e94]
1481b724b MOV RDX,qword ptr [RDI]
1481b724e MOV RCX,qword ptr [R15 + 0x60]
1481b7252 CALL 0x1481b11d0
1481b7257 MOV RSI,RAX
1481b725a TEST RAX,RAX
1481b725d JZ 0x1481b7265
1481b725f CMP qword ptr [RAX + 0x8],RBX
1481b7263 JZ 0x1481b726e
1481b7265 ADD RDI,0x8
1481b7269 MOV ECX,dword ptr [RBP + -0x49]
1481b726c JMP 0x1481b7220
1481b726e MOV RCX,qword ptr [RBP + -0x51]
1481b7272 TEST RCX,RCX
1481b7275 JZ 0x1481b727d
1481b7277 CALL 0x140e282f0
1481b727c NOP
1481b727d CMP byte ptr [RSI + 0x68],0x0
1481b7281 JNZ 0x1481b74be
1481b7287 MOV RBX,qword ptr [R13]
1481b728b MOV ECX,EBX
1481b728d CALL 0x1411c2eb0
1481b7292 MOV RCX,RBX
1481b7295 SHR RCX,0x20
1481b7299 ADD EAX,ECX
1481b729b MOV ECX,dword ptr [R15 + 0xf8]
1481b72a2 CMP ECX,dword ptr [R15 + 0x124]
1481b72a9 JZ 0x1481b74be
1481b72af LEA R9,[R15 + 0x128]
1481b72b6 MOV R8,qword ptr [R9 + 0x8]
1481b72ba MOV EDX,dword ptr [R15 + 0x138]
1481b72c1 DEC EDX
1481b72c3 AND RDX,RAX
1481b72c6 TEST R8,R8
1481b72c9 CMOVNZ R9,R8
1481b72cd MOV EAX,dword ptr [R9 + RDX*0x4]
1481b72d1 CMP EAX,-0x1
1481b72d4 JZ 0x1481b74be
1481b72da MOV RDX,qword ptr [R15 + 0xf0]
1481b72e1 MOVSXD RCX,EAX
1481b72e4 SHL RCX,0x6
1481b72e8 ADD RCX,RDX
1481b72eb CMP qword ptr [RCX],RBX
1481b72ee JZ 0x1481b7308
1481b72f0 MOV EAX,dword ptr [RCX + 0x38]
1481b72f3 CMP EAX,-0x1
1481b72f6 JNZ 0x1481b72e1
1481b72f8 ADD R13,0x8
1481b72fc MOV ECX,dword ptr [RBP + -0x79]
1481b72ff MOV RBX,qword ptr [RBP + -0x39]
1481b7303 JMP 0x1481b71cd
1481b7308 LEA R14,[RCX + 0x8]
1481b730c TEST RCX,RCX
1481b730f MOV EDX,0x0
1481b7314 CMOVZ R14,RDX
1481b7318 TEST R14,R14
1481b731b JZ 0x1481b74be
1481b7321 MOV EBX,EDX
1481b7323 LEA RAX,[R14 + 0x10]
1481b7327 MOV qword ptr [RBP + -0x41],RAX
1481b732b CMP dword ptr [RAX],EDX
1481b732d JLE 0x1481b74be
1481b7333 LEA RAX,[R14 + 0x8]
1481b7337 MOV qword ptr [RBP + -0x61],RAX
1481b733b MOV R12D,EDX
1481b733e MOV R13D,EDX
1481b7341 MOVSXD RCX,dword ptr [RAX + 0x8]
1481b7345 MOV ESI,EBX
1481b7347 NOT ESI
1481b7349 SHR ESI,0x1f
1481b734c MOV EAX,EDX
1481b734e CMP EBX,ECX
1481b7350 CMOVL EAX,ESI
1481b7353 TEST EAX,EAX
1481b7355 JNZ 0x1481b7398
1481b7357 MOV RAX,RCX
1481b735a MOVSXD RCX,EBX
1481b735d MOV R9,qword ptr [RBP + 0x5f]
1481b7361 MOV qword ptr [RSP + 0x30],RAX
1481b7366 MOV qword ptr [RSP + 0x28],RCX
1481b736b LEA RAX,[0x14bce6ef0]
1481b7372 MOV qword ptr [RSP + 0x20],RAX
1481b7377 MOV R8D,0x303
1481b737d LEA RDX,[0x14cf27ac0]
1481b7384 LEA RCX,[0x14bce6f68]
1481b738b CALL 0x140f8dfd0
1481b7390 TEST AL,AL
1481b7392 JZ 0x1481b7396
1481b7394 NOP
1481b7395 INT3
1481b7396 XOR EDX,EDX
1481b7398 MOV RDI,R14
1481b739b MOV RAX,qword ptr [RBP + -0x61]
1481b739f MOV RAX,qword ptr [RAX]
1481b73a2 CMP byte ptr [RAX + R13*0x1],0x10
1481b73a7 JNZ 0x1481b7481
1481b73ad TEST EBX,EBX
1481b73af JS 0x1481b7481
1481b73b5 CMP EBX,dword ptr [R14 + 0x28]
1481b73b9 JGE 0x1481b7481
1481b73bf MOVSXD RCX,dword ptr [R14 + 0x28]
1481b73c3 MOV EAX,EDX
1481b73c5 CMP EBX,ECX
1481b73c7 CMOVL EAX,ESI
1481b73ca TEST EAX,EAX
1481b73cc JNZ 0x1481b740f
1481b73ce MOV RAX,RCX
1481b73d1 MOVSXD RCX,EBX
1481b73d4 MOV R9,qword ptr [RBP + 0x5f]
1481b73d8 MOV qword ptr [RSP + 0x30],RAX
1481b73dd MOV qword ptr [RSP + 0x28],RCX
1481b73e2 LEA RAX,[0x14bce6ef0]
1481b73e9 MOV qword ptr [RSP + 0x20],RAX
1481b73ee MOV R8D,0x303
1481b73f4 LEA RDX,[0x14cf27ac0]
1481b73fb LEA RCX,[0x14bce6f68]
1481b7402 CALL 0x140f8dfd0
1481b7407 TEST AL,AL
1481b7409 JZ 0x1481b740d
1481b740b NOP
1481b740c INT3
1481b740d XOR EDX,EDX
1481b740f MOV EAX,dword ptr [R15 + 0x294]
1481b7416 MOV dword ptr [RBP + 0x7f],EAX
1481b7419 MOV RAX,qword ptr [RDI + 0x20]
1481b741d MOV ECX,dword ptr [RBP + 0x7f]
1481b7420 CMP ECX,dword ptr [R12 + RAX*0x1]
1481b7424 JLE 0x1481b7481
1481b7426 MOVSXD RCX,dword ptr [RDI + 0x28]
1481b742a MOV EAX,EDX
1481b742c CMP EBX,ECX
1481b742e CMOVL EAX,ESI
1481b7431 TEST EAX,EAX
1481b7433 JNZ 0x1481b7476
1481b7435 MOV RAX,RCX
1481b7438 MOVSXD RCX,EBX
1481b743b MOV R9,qword ptr [RBP + 0x5f]
1481b743f MOV qword ptr [RSP + 0x30],RAX
1481b7444 MOV qword ptr [RSP + 0x28],RCX
1481b7449 LEA RAX,[0x14bce6ef0]
1481b7450 MOV qword ptr [RSP + 0x20],RAX
1481b7455 MOV R8D,0x303
1481b745b LEA RDX,[0x14cf27ac0]
1481b7462 LEA RCX,[0x14bce6f68]
1481b7469 CALL 0x140f8dfd0
1481b746e TEST AL,AL
1481b7470 JZ 0x1481b7474
1481b7472 NOP
1481b7473 INT3
1481b7474 XOR EDX,EDX
1481b7476 MOV RAX,qword ptr [RDI + 0x20]
1481b747a MOV EDI,dword ptr [RBP + 0x7f]
1481b747d MOV dword ptr [R12 + RAX*0x1],EDI
1481b7481 INC EBX
1481b7483 ADD R13,0x10
1481b7487 ADD R12,0x4
1481b748b MOV RAX,qword ptr [RBP + -0x41]
1481b748f CMP EBX,dword ptr [RAX]
1481b7491 MOV RAX,qword ptr [RBP + -0x61]
1481b7495 JL 0x1481b7341
1481b749b MOV R13,qword ptr [RBP + -0x59]
1481b749f ADD R13,0x8
1481b74a3 MOV ECX,dword ptr [RBP + -0x79]
1481b74a6 MOV RBX,qword ptr [RBP + -0x39]
1481b74aa JMP 0x1481b71cd
1481b74af MOV RCX,qword ptr [RBP + -0x51]
1481b74b3 TEST RCX,RCX
1481b74b6 JZ 0x1481b74be
1481b74b8 CALL 0x140e282f0
1481b74bd NOP
1481b74be ADD R13,0x8
1481b74c2 MOV ECX,dword ptr [RBP + -0x79]
1481b74c5 MOV RBX,qword ptr [RBP + -0x39]
1481b74c9 JMP 0x1481b71cd
1481b74ce MOV RCX,R15
1481b74d1 CALL 0x1481cad00
1481b74d6 CMP byte ptr [0x14eab53c8],0x3
1481b74dd JC 0x1481b74f3
1481b74df LEA RDX,[0x14cf71c18]
1481b74e6 LEA RCX,[0x14eab53c8]
1481b74ed CALL 0x140f24ba0
1481b74f2 NOP
1481b74f3 MOV RCX,qword ptr [RBP + -0x71]
1481b74f7 TEST RCX,RCX
1481b74fa JZ 0x1481b7502
1481b74fc CALL 0x140e282f0
1481b7501 NOP
1481b7502 MOV RBX,qword ptr [RSP + 0x138]
1481b750a ADD RSP,0xf0
1481b7511 POP R15
1481b7513 POP R14
1481b7515 POP R13
1481b7517 POP R12
1481b7519 POP RDI
1481b751a POP RSI
1481b751b POP RBP
1481b751c RET
*/

/* 1481ba790 GetChallengeDataPtr */

longlong GetChallengeDataPtr(longlong param_1,longlong param_2)

{
  undefined8 *puVar1;
  code *pcVar2;
  char cVar3;
  longlong lVar4;
  int iVar5;
  undefined8 *puVar6;
  undefined1 auStackX_8 [8];
  undefined8 *apuStack_28 [2];
  
  if (*(longlong *)(param_1 + 0x60) == 0) {
    lVar4 = 0;
  }
  else {
    func_0x0001468fb0a0(*(longlong *)(param_1 + 0x60),apuStack_28);
    iVar5 = (int)apuStack_28[1];
    puVar1 = apuStack_28[0] + iVar5;
    puVar6 = apuStack_28[0];
    while( true ) {
      if ((int)apuStack_28[1] != iVar5) {
        auStackX_8[0] = 0;
        cVar3 = func_0x00014bae9430(auStackX_8);
        if (cVar3 != '\0') {
          pcVar2 = (code *)swi(3);
          lVar4 = (*pcVar2)();
          return lVar4;
        }
      }
      if (puVar6 == puVar1) break;
      lVar4 = func_0x0001481b11d0(*(undefined8 *)(param_1 + 0x60),*puVar6,&UNK_14bce4e94,1);
      if ((lVar4 != 0) && (*(longlong *)(lVar4 + 8) == param_2)) goto LAB_1481ba826;
      puVar6 = puVar6 + 1;
    }
    lVar4 = 0;
LAB_1481ba826:
    if (apuStack_28[0] != (undefined8 *)0x0) {
      func_0x000140e282f0();
    }
  }
  return lVar4;
}


/* Instruction evidence:
1481ba790 MOV qword ptr [RSP + 0x10],RBX
1481ba795 MOV qword ptr [RSP + 0x18],RBP
1481ba79a MOV qword ptr [RSP + 0x20],RSI
1481ba79f PUSH RDI
1481ba7a0 PUSH R14
1481ba7a2 PUSH R15
1481ba7a4 SUB RSP,0x30
1481ba7a8 MOV RBX,RDX
1481ba7ab MOV R15,RCX
1481ba7ae MOV RCX,qword ptr [RCX + 0x60]
1481ba7b2 TEST RCX,RCX
1481ba7b5 JNZ 0x1481ba7bb
1481ba7b7 XOR EAX,EAX
1481ba7b9 JMP 0x1481ba839
1481ba7bb LEA RDX,[RSP + 0x20]
1481ba7c0 CALL 0x1468fb0a0
1481ba7c5 NOP
1481ba7c6 MOV RDI,qword ptr [RSP + 0x20]
1481ba7cb MOV RCX,qword ptr [RSP + 0x28]
1481ba7d0 MOVSXD RBP,ECX
1481ba7d3 LEA R14,[RDI + RBP*0x8]
1481ba7d7 CMP ECX,EBP
1481ba7d9 JZ 0x1481ba7f0
1481ba7db MOV byte ptr [RSP + 0x50],0x0
1481ba7e0 LEA RCX,[RSP + 0x50]
1481ba7e5 CALL 0x14bae9430
1481ba7ea TEST AL,AL
1481ba7ec JZ 0x1481ba7f0
1481ba7ee NOP
1481ba7ef INT3
1481ba7f0 CMP RDI,R14
1481ba7f3 JZ 0x1481ba824
1481ba7f5 MOV R9B,0x1
1481ba7f8 LEA R8,[0x14bce4e94]
1481ba7ff MOV RDX,qword ptr [RDI]
1481ba802 MOV RCX,qword ptr [R15 + 0x60]
1481ba806 CALL 0x1481b11d0
1481ba80b MOV RSI,RAX
1481ba80e TEST RAX,RAX
1481ba811 JZ 0x1481ba819
1481ba813 CMP qword ptr [RAX + 0x8],RBX
1481ba817 JZ 0x1481ba826
1481ba819 ADD RDI,0x8
1481ba81d MOV RCX,qword ptr [RSP + 0x28]
1481ba822 JMP 0x1481ba7d7
1481ba824 XOR ESI,ESI
1481ba826 MOV RCX,qword ptr [RSP + 0x20]
1481ba82b TEST RCX,RCX
1481ba82e JZ 0x1481ba836
1481ba830 CALL 0x140e282f0
1481ba835 NOP
1481ba836 MOV RAX,RSI
1481ba839 MOV RBX,qword ptr [RSP + 0x58]
1481ba83e MOV RBP,qword ptr [RSP + 0x60]
1481ba843 MOV RSI,qword ptr [RSP + 0x68]
1481ba848 ADD RSP,0x30
1481ba84c POP R15
1481ba84e POP R14
1481ba850 POP RDI
1481ba851 RET
*/
