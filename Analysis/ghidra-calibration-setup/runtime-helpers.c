
/* 1481a0010 LatencyManagerConstructor */

undefined8 * LatencyManagerConstructor(undefined8 *param_1)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  undefined8 *puVar5;
  int *piVar6;
  char *pcVar7;
  char *pcVar8;
  undefined8 unaff_retaddr;
  undefined8 *puStackX_10;
  undefined1 auStackX_18 [8];
  undefined1 auStackX_20 [8];
  undefined1 auStack_108 [4];
  undefined8 uStack_104;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined8 uStack_f4;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined8 uStack_e4;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined8 uStack_d4;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined1 auStack_c4 [4];
  undefined1 auStack_c0 [4];
  undefined1 auStack_bc [4];
  undefined1 auStack_b8 [8];
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined4 uStack_a0;
  longlong alStack_98 [3];
  undefined1 uStack_80;
  undefined8 **ppuStack_78;
  undefined8 *puStack_70;
  undefined1 *puStack_68;
  undefined8 *puStack_60;
  undefined1 *puStack_58;
  undefined8 *puStack_50;
  undefined1 *puStack_48;
  undefined8 *puStack_40;
  undefined1 auStack_38 [8];
  undefined1 auStack_30 [8];
  
  func_0x0001461645c0();
  *param_1 = &UNK_14cf3d9e0;
  pcVar8 = (char *)0x0;
  param_1[0x55] = 0;
  param_1[0x56] = 0;
  param_1[0x57] = 0;
  param_1[0x58] = 0;
  param_1[0x59] = 0;
  param_1[0x5a] = 0;
  param_1[0x5b] = 0;
  param_1[0x5c] = 0;
  param_1[0x5d] = 0;
  param_1[0x5e] = 0;
  param_1[0x5f] = 0;
  param_1[0x60] = 0;
  param_1[0x61] = 0;
  param_1[0x62] = 0;
  param_1[99] = 0;
  puStackX_10 = param_1 + 100;
  param_1[0x67] = 0;
  param_1[0x68] = 0;
  param_1[0x69] = 0;
  *puStackX_10 = 0;
  param_1[0x65] = 0;
  *(undefined4 *)(param_1 + 0x66) = 0x42700000;
  func_0x000140cf9360(param_1 + 0x67,&UNK_14bd095a0);
  puVar5 = (undefined8 *)func_0x000141014800(auStack_38);
  param_1[0x69] = *puVar5;
  *(undefined1 *)(param_1 + 0x6a) = 0;
  param_1[0x6d] = 0;
  plVar1 = param_1 + 0x6e;
  *plVar1 = 0;
  param_1[0x6f] = 0;
  param_1[0x72] = 0;
  *(undefined4 *)(param_1 + 0x73) = 0;
  *(undefined4 *)((longlong)param_1 + 0x39c) = 0x80;
  *(undefined4 *)(param_1 + 0x74) = 0xffffffff;
  *(undefined4 *)((longlong)param_1 + 0x3a4) = 0;
  param_1[0x76] = 0;
  *(undefined4 *)(param_1 + 0x77) = 0;
  param_1[0x78] = 0;
  param_1[0x79] = 0;
  param_1[0x7a] = 0;
  param_1[0x7b] = 0;
  param_1[0x80] = 0;
  param_1[0x81] = 0;
  *(byte *)((longlong)param_1 + 0x32) = *(byte *)((longlong)param_1 + 0x32) & 0xfd;
  *(undefined1 *)(param_1 + 0x6b) = 0;
  *(undefined4 *)((longlong)param_1 + 0x35c) = 0x42f00000;
  *(undefined4 *)(param_1 + 0x6c) = 0x10;
  *(undefined4 *)((longlong)param_1 + 0x364) = 0x20;
  param_1[0x7c] = 0;
  *(undefined4 *)(param_1 + 0x7d) = 0;
  param_1[0x7e] = 0;
  *(undefined2 *)(param_1 + 0x7f) = 0;
  *(undefined4 *)((longlong)param_1 + 0x3fc) = 0;
  uStack_104 = 0;
  uStack_fc = 0;
  uStack_f8 = 0x42700000;
  puStackX_10 = (undefined8 *)((ulonglong)puStackX_10 & 0xffffffffffffff00);
  ppuStack_78 = &puStackX_10;
  puStack_70 = &uStack_104;
  func_0x00014819fcb0(plVar1,auStack_c4,&ppuStack_78,0);
  uStack_f4 = 0;
  uStack_ec = 0;
  uStack_e8 = 0x42700000;
  auStackX_18[0] = 1;
  puStack_68 = auStackX_18;
  puStack_60 = &uStack_f4;
  func_0x00014819fcb0(plVar1,auStack_c0,&puStack_68,0);
  uStack_e4 = 0;
  uStack_dc = 0;
  uStack_d8 = 0x42700000;
  auStackX_20[0] = 2;
  puStack_58 = auStackX_20;
  puStack_50 = &uStack_e4;
  func_0x00014819fcb0(plVar1,auStack_bc,&puStack_58,0);
  uStack_d4 = 0;
  uStack_cc = 0;
  uStack_c8 = 0x42700000;
  auStack_108[0] = 3;
  puStack_48 = auStack_108;
  puStack_40 = &uStack_d4;
  func_0x00014819fcb0(plVar1,auStack_b8,&puStack_48,0);
  pcVar7 = pcVar8;
  if (*(int *)(param_1 + 0x6f) != *(int *)((longlong)param_1 + 0x3a4)) {
    piVar6 = (int *)(param_1 + 0x75);
    if ((int *)param_1[0x76] != (int *)0x0) {
      piVar6 = (int *)param_1[0x76];
    }
    iVar4 = *piVar6;
    if (iVar4 != -1) {
      do {
        pcVar7 = (char *)((longlong)iVar4 * 0x1c + *plVar1);
        if (*pcVar7 == '\0') {
          if (pcVar7 != (char *)0x0) goto LAB_1481a02f5;
          break;
        }
        iVar4 = *(int *)(pcVar7 + 0x14);
        pcVar7 = pcVar8;
      } while (iVar4 != -1);
    }
  }
  cVar3 = func_0x000140f8dfd0(&UNK_14bcf2cd8,
                              "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Map.h"
                              ,0x29f,unaff_retaddr,&UNK_14bce4e94);
  if (cVar3 != '\0') {
    pcVar2 = (code *)swi(3);
    puVar5 = (undefined8 *)(*pcVar2)();
    return puVar5;
  }
LAB_1481a02f5:
  pcVar7[4] = '\0';
  pcVar7[5] = '\0';
  pcVar7[6] = '\0';
  pcVar7[7] = 'A';
  pcVar7 = pcVar8;
  if (*(int *)(param_1 + 0x6f) != *(int *)((longlong)param_1 + 0x3a4)) {
    piVar6 = (int *)(param_1 + 0x75);
    if ((int *)param_1[0x76] != (int *)0x0) {
      piVar6 = (int *)param_1[0x76];
    }
    iVar4 = *piVar6;
    if (iVar4 != -1) {
      do {
        pcVar7 = (char *)((longlong)iVar4 * 0x1c + param_1[0x6e]);
        if (*pcVar7 == '\0') {
          if (pcVar7 != (char *)0x0) goto LAB_1481a0375;
          break;
        }
        iVar4 = *(int *)(pcVar7 + 0x14);
        pcVar7 = pcVar8;
      } while (iVar4 != -1);
    }
  }
  cVar3 = func_0x000140f8dfd0(&UNK_14bcf2cd8,
                              "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Map.h"
                              ,0x29f,unaff_retaddr,&UNK_14bce4e94);
  if (cVar3 != '\0') {
    pcVar2 = (code *)swi(3);
    puVar5 = (undefined8 *)(*pcVar2)();
    return puVar5;
  }
LAB_1481a0375:
  pcVar7[0x10] = '\0';
  pcVar7[0x11] = '\0';
  pcVar7[0x12] = 'H';
  pcVar7[0x13] = 'B';
  pcVar7 = pcVar8;
  if (*(int *)(param_1 + 0x6f) != *(int *)((longlong)param_1 + 0x3a4)) {
    puVar5 = param_1 + 0x75;
    if ((undefined8 *)param_1[0x76] != (undefined8 *)0x0) {
      puVar5 = (undefined8 *)param_1[0x76];
    }
    iVar4 = *(int *)((longlong)puVar5 + (ulonglong)(*(int *)(param_1 + 0x77) - 1U & 1) * 4);
    if (iVar4 != -1) {
      do {
        pcVar7 = (char *)((longlong)iVar4 * 0x1c + param_1[0x6e]);
        if (*pcVar7 == '\x01') {
          if (pcVar7 != (char *)0x0) goto LAB_1481a0406;
          break;
        }
        iVar4 = *(int *)(pcVar7 + 0x14);
        pcVar7 = pcVar8;
      } while (iVar4 != -1);
    }
  }
  cVar3 = func_0x000140f8dfd0(&UNK_14bcf2cd8,
                              "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Map.h"
                              ,0x29f,unaff_retaddr,&UNK_14bce4e94);
  if (cVar3 != '\0') {
    pcVar2 = (code *)swi(3);
    puVar5 = (undefined8 *)(*pcVar2)();
    return puVar5;
  }
LAB_1481a0406:
  pcVar7[4] = '\0';
  pcVar7[5] = '\0';
  pcVar7[6] = 'p';
  pcVar7[7] = 'A';
  pcVar7 = pcVar8;
  if (*(int *)(param_1 + 0x6f) != *(int *)((longlong)param_1 + 0x3a4)) {
    puVar5 = param_1 + 0x75;
    if ((undefined8 *)param_1[0x76] != (undefined8 *)0x0) {
      puVar5 = (undefined8 *)param_1[0x76];
    }
    iVar4 = *(int *)((longlong)puVar5 + (ulonglong)(*(int *)(param_1 + 0x77) - 1U & 1) * 4);
    if (iVar4 != -1) {
      do {
        pcVar7 = (char *)((longlong)iVar4 * 0x1c + param_1[0x6e]);
        if (*pcVar7 == '\x01') {
          if (pcVar7 != (char *)0x0) goto LAB_1481a0496;
          break;
        }
        iVar4 = *(int *)(pcVar7 + 0x14);
        pcVar7 = pcVar8;
      } while (iVar4 != -1);
    }
  }
  cVar3 = func_0x000140f8dfd0(&UNK_14bcf2cd8,
                              "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Map.h"
                              ,0x29f,unaff_retaddr,&UNK_14bce4e94);
  if (cVar3 != '\0') {
    pcVar2 = (code *)swi(3);
    puVar5 = (undefined8 *)(*pcVar2)();
    return puVar5;
  }
LAB_1481a0496:
  pcVar7[0x10] = '\0';
  pcVar7[0x11] = '\0';
  pcVar7[0x12] = -0x74;
  pcVar7[0x13] = 'B';
  pcVar7 = pcVar8;
  if (*(int *)(param_1 + 0x6f) != *(int *)((longlong)param_1 + 0x3a4)) {
    puVar5 = param_1 + 0x75;
    if ((undefined8 *)param_1[0x76] != (undefined8 *)0x0) {
      puVar5 = (undefined8 *)param_1[0x76];
    }
    iVar4 = *(int *)((longlong)puVar5 + (ulonglong)(*(int *)(param_1 + 0x77) - 1U & 2) * 4);
    if (iVar4 != -1) {
      do {
        pcVar7 = (char *)((longlong)iVar4 * 0x1c + param_1[0x6e]);
        if (*pcVar7 == '\x02') {
          if (pcVar7 != (char *)0x0) goto LAB_1481a0526;
          break;
        }
        iVar4 = *(int *)(pcVar7 + 0x14);
        pcVar7 = pcVar8;
      } while (iVar4 != -1);
    }
  }
  cVar3 = func_0x000140f8dfd0(&UNK_14bcf2cd8,
                              "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Map.h"
                              ,0x29f,unaff_retaddr,&UNK_14bce4e94);
  if (cVar3 != '\0') {
    pcVar2 = (code *)swi(3);
    puVar5 = (undefined8 *)(*pcVar2)();
    return puVar5;
  }
LAB_1481a0526:
  pcVar7[4] = '\0';
  pcVar7[5] = '\0';
  pcVar7[6] = -0x38;
  pcVar7[7] = 'A';
  pcVar7 = pcVar8;
  if (*(int *)(param_1 + 0x6f) != *(int *)((longlong)param_1 + 0x3a4)) {
    puVar5 = param_1 + 0x75;
    if ((undefined8 *)param_1[0x76] != (undefined8 *)0x0) {
      puVar5 = (undefined8 *)param_1[0x76];
    }
    iVar4 = *(int *)((longlong)puVar5 + (ulonglong)(*(int *)(param_1 + 0x77) - 1U & 2) * 4);
    if (iVar4 != -1) {
      do {
        pcVar7 = (char *)((longlong)iVar4 * 0x1c + param_1[0x6e]);
        if (*pcVar7 == '\x02') {
          if (pcVar7 != (char *)0x0) goto LAB_1481a05b6;
          break;
        }
        iVar4 = *(int *)(pcVar7 + 0x14);
        pcVar7 = pcVar8;
      } while (iVar4 != -1);
    }
  }
  cVar3 = func_0x000140f8dfd0(&UNK_14bcf2cd8,
                              "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Map.h"
                              ,0x29f,unaff_retaddr,&UNK_14bce4e94);
  if (cVar3 != '\0') {
    pcVar2 = (code *)swi(3);
    puVar5 = (undefined8 *)(*pcVar2)();
    return puVar5;
  }
LAB_1481a05b6:
  pcVar7[0x10] = '\0';
  pcVar7[0x11] = '\0';
  pcVar7[0x12] = -0x4c;
  pcVar7[0x13] = 'B';
  alStack_98[0] = 0;
  alStack_98[1] = 0;
  alStack_98[2] = 0;
  uStack_b0 = 0;
  uStack_a8 = 0;
  uStack_a0 = 0x42700000;
  func_0x000140cf9360(alStack_98,&UNK_14bd095a0);
  puVar5 = (undefined8 *)func_0x000141014800(auStack_30);
  alStack_98[2] = *puVar5;
  uStack_80 = 0;
  func_0x000148149860(param_1 + 100,&uStack_b0);
  if (alStack_98[0] != 0) {
    func_0x000140e282f0();
  }
  *(undefined4 *)(param_1 + 0x66) = 0x42700000;
  return param_1;
}


/* Instruction evidence:
1481a0010 MOV qword ptr [RSP + 0x8],RCX
1481a0015 PUSH RBP
1481a0016 PUSH RBX
1481a0017 PUSH RSI
1481a0018 PUSH RDI
1481a0019 PUSH R14
1481a001b LEA RBP,[RSP + -0x10]
1481a0020 SUB RSP,0x110
1481a0027 MOV RDI,RCX
1481a002a CALL 0x1461645c0
1481a002f NOP
1481a0030 LEA RAX,[0x14cf3d9e0]
1481a0037 MOV qword ptr [RDI],RAX
1481a003a XOR ESI,ESI
1481a003c MOV qword ptr [RDI + 0x2a8],RSI
1481a0043 MOV qword ptr [RDI + 0x2b0],RSI
1481a004a MOV qword ptr [RDI + 0x2b8],RSI
1481a0051 MOV qword ptr [RDI + 0x2c0],RSI
1481a0058 MOV qword ptr [RDI + 0x2c8],RSI
1481a005f MOV qword ptr [RDI + 0x2d0],RSI
1481a0066 MOV qword ptr [RDI + 0x2d8],RSI
1481a006d MOV qword ptr [RDI + 0x2e0],RSI
1481a0074 MOV qword ptr [RDI + 0x2e8],RSI
1481a007b MOV qword ptr [RDI + 0x2f0],RSI
1481a0082 MOV qword ptr [RDI + 0x2f8],RSI
1481a0089 MOV qword ptr [RDI + 0x300],RSI
1481a0090 MOV qword ptr [RDI + 0x308],RSI
1481a0097 MOV qword ptr [RDI + 0x310],RSI
1481a009e MOV qword ptr [RDI + 0x318],RSI
1481a00a5 LEA RBX,[RDI + 0x320]
1481a00ac MOV qword ptr [RBP + 0x48],RBX
1481a00b0 LEA RCX,[RBX + 0x18]
1481a00b4 MOV qword ptr [RCX],RSI
1481a00b7 MOV qword ptr [RCX + 0x8],RSI
1481a00bb MOV qword ptr [RBX + 0x28],RSI
1481a00bf MOV qword ptr [RBX],RSI
1481a00c2 MOV qword ptr [RBX + 0x8],RSI
1481a00c6 MOV dword ptr [RBX + 0x10],0x42700000
1481a00cd LEA RDX,[0x14bd095a0]
1481a00d4 CALL 0x140cf9360
1481a00d9 LEA RCX,[RBP]
1481a00dd CALL 0x141014800
1481a00e2 MOV RCX,qword ptr [RAX]
1481a00e5 MOV qword ptr [RBX + 0x28],RCX
1481a00e9 MOV byte ptr [RBX + 0x30],SIL
1481a00ed MOV qword ptr [RDI + 0x368],RSI
1481a00f4 LEA RBX,[RDI + 0x370]
1481a00fb MOV qword ptr [RBX],RSI
1481a00fe MOV qword ptr [RBX + 0x8],RSI
1481a0102 MOV qword ptr [RBX + 0x20],RSI
1481a0106 MOV dword ptr [RBX + 0x28],ESI
1481a0109 MOV dword ptr [RBX + 0x2c],0x80
1481a0110 MOV dword ptr [RBX + 0x30],0xffffffff
1481a0117 MOV dword ptr [RBX + 0x34],ESI
1481a011a MOV qword ptr [RBX + 0x40],RSI
1481a011e MOV dword ptr [RBX + 0x48],ESI
1481a0121 MOV qword ptr [RDI + 0x3c0],RSI
1481a0128 MOV qword ptr [RDI + 0x3c8],RSI
1481a012f MOV qword ptr [RDI + 0x3d0],RSI
1481a0136 MOV qword ptr [RDI + 0x3d8],RSI
1481a013d MOV qword ptr [RDI + 0x400],RSI
1481a0144 MOV qword ptr [RDI + 0x408],RSI
1481a014b AND byte ptr [RDI + 0x32],0xfd
1481a014f MOV byte ptr [RDI + 0x358],SIL
1481a0156 MOV dword ptr [RDI + 0x35c],0x42f00000
1481a0160 MOV dword ptr [RDI + 0x360],0x10
1481a016a MOV dword ptr [RDI + 0x364],0x20
1481a0174 MOV qword ptr [RDI + 0x3e0],RSI
1481a017b MOV dword ptr [RDI + 0x3e8],ESI
1481a0181 MOV qword ptr [RDI + 0x3f0],RSI
1481a0188 MOV word ptr [RDI + 0x3f8],SI
1481a018f MOV dword ptr [RDI + 0x3fc],ESI
1481a0195 MOV qword ptr [RSP + 0x34],RSI
1481a019a MOV dword ptr [RSP + 0x3c],ESI
1481a019e MOV dword ptr [RSP + 0x40],0x42700000
1481a01a6 MOV byte ptr [RBP + 0x48],SIL
1481a01aa LEA RAX,[RBP + 0x48]
1481a01ae MOV qword ptr [RBP + -0x40],RAX
1481a01b2 LEA RAX,[RSP + 0x34]
1481a01b7 MOV qword ptr [RBP + -0x38],RAX
1481a01bb XOR R9D,R9D
1481a01be LEA R8,[RBP + -0x40]
1481a01c2 LEA RDX,[RSP + 0x74]
1481a01c7 MOV RCX,RBX
1481a01ca CALL 0x14819fcb0
1481a01cf MOV qword ptr [RSP + 0x44],RSI
1481a01d4 MOV dword ptr [RSP + 0x4c],ESI
1481a01d8 MOV dword ptr [RSP + 0x50],0x42700000
1481a01e0 MOV byte ptr [RBP + 0x50],0x1
1481a01e4 LEA RAX,[RBP + 0x50]
1481a01e8 MOV qword ptr [RBP + -0x30],RAX
1481a01ec LEA RAX,[RSP + 0x44]
1481a01f1 MOV qword ptr [RBP + -0x28],RAX
1481a01f5 XOR R9D,R9D
1481a01f8 LEA R8,[RBP + -0x30]
1481a01fc LEA RDX,[RSP + 0x78]
1481a0201 MOV RCX,RBX
1481a0204 CALL 0x14819fcb0
1481a0209 MOV qword ptr [RSP + 0x54],RSI
1481a020e MOV dword ptr [RSP + 0x5c],ESI
1481a0212 MOV dword ptr [RSP + 0x60],0x42700000
1481a021a MOV byte ptr [RBP + 0x58],0x2
1481a021e LEA RAX,[RBP + 0x58]
1481a0222 MOV qword ptr [RBP + -0x20],RAX
1481a0226 LEA RAX,[RSP + 0x54]
1481a022b MOV qword ptr [RBP + -0x18],RAX
1481a022f XOR R9D,R9D
1481a0232 LEA R8,[RBP + -0x20]
1481a0236 LEA RDX,[RSP + 0x7c]
1481a023b MOV RCX,RBX
1481a023e CALL 0x14819fcb0
1481a0243 MOV qword ptr [RSP + 0x64],RSI
1481a0248 MOV dword ptr [RSP + 0x6c],ESI
1481a024c MOV dword ptr [RSP + 0x70],0x42700000
1481a0254 MOV byte ptr [RSP + 0x30],0x3
1481a0259 LEA RAX,[RSP + 0x30]
1481a025e MOV qword ptr [RBP + -0x10],RAX
1481a0262 LEA RAX,[RSP + 0x64]
1481a0267 MOV qword ptr [RBP + -0x8],RAX
1481a026b XOR R9D,R9D
1481a026e LEA R8,[RBP + -0x10]
1481a0272 LEA RDX,[RBP + -0x80]
1481a0276 MOV RCX,RBX
1481a0279 CALL 0x14819fcb0
1481a027e MOV EAX,dword ptr [RBX + 0x8]
1481a0281 LEA R14,[0x14bce4e94]
1481a0288 CMP EAX,dword ptr [RBX + 0x34]
1481a028b JZ 0x1481a02ca
1481a028d LEA RCX,[RBX + 0x38]
1481a0291 MOV RAX,qword ptr [RCX + 0x8]
1481a0295 TEST RAX,RAX
1481a0298 CMOVNZ RCX,RAX
1481a029c MOV EAX,dword ptr [RCX]
1481a029e CMP EAX,-0x1
1481a02a1 JZ 0x1481a02ca
1481a02a3 MOV RDX,qword ptr [RBX]
1481a02a6 NOP dword ptr [RAX + RAX*0x1]
1481a02b0 CDQE
1481a02b2 IMUL RBX,RAX,0x1c
1481a02b6 ADD RBX,RDX
1481a02b9 CMP byte ptr [RBX],0x0
1481a02bc JZ 0x1481a0636
1481a02c2 MOV EAX,dword ptr [RBX + 0x14]
1481a02c5 CMP EAX,-0x1
1481a02c8 JNZ 0x1481a02b0
1481a02ca MOV RBX,RSI
1481a02cd MOV R9,qword ptr [RBP + 0x38]
1481a02d1 MOV qword ptr [RSP + 0x20],R14
1481a02d6 MOV R8D,0x29f
1481a02dc LEA RDX,[0x14cf4deb0]
1481a02e3 LEA RCX,[0x14bcf2cd8]
1481a02ea CALL 0x140f8dfd0
1481a02ef TEST AL,AL
1481a02f1 JZ 0x1481a02f5
1481a02f3 NOP
1481a02f4 INT3
1481a02f5 MOV dword ptr [RBX + 0x4],0x41000000
1481a02fc MOV EAX,dword ptr [RDI + 0x378]
1481a0302 CMP EAX,dword ptr [RDI + 0x3a4]
1481a0308 JZ 0x1481a034a
1481a030a LEA RCX,[RDI + 0x3a8]
1481a0311 MOV RAX,qword ptr [RCX + 0x8]
1481a0315 TEST RAX,RAX
1481a0318 CMOVNZ RCX,RAX
1481a031c MOV EAX,dword ptr [RCX]
1481a031e CMP EAX,-0x1
1481a0321 JZ 0x1481a034a
1481a0323 MOV RDX,qword ptr [RDI + 0x370]
1481a032a NOP word ptr [RAX + RAX*0x1]
1481a0330 CDQE
1481a0332 IMUL RBX,RAX,0x1c
1481a0336 ADD RBX,RDX
1481a0339 CMP byte ptr [RBX],0x0
1481a033c JZ 0x1481a0644
1481a0342 MOV EAX,dword ptr [RBX + 0x14]
1481a0345 CMP EAX,-0x1
1481a0348 JNZ 0x1481a0330
1481a034a MOV RBX,RSI
1481a034d MOV R9,qword ptr [RBP + 0x38]
1481a0351 MOV qword ptr [RSP + 0x20],R14
1481a0356 MOV R8D,0x29f
1481a035c LEA RDX,[0x14cf4deb0]
1481a0363 LEA RCX,[0x14bcf2cd8]
1481a036a CALL 0x140f8dfd0
1481a036f TEST AL,AL
1481a0371 JZ 0x1481a0375
1481a0373 NOP
1481a0374 INT3
1481a0375 MOV dword ptr [RBX + 0x10],0x42480000
1481a037c MOV EAX,dword ptr [RDI + 0x378]
1481a0382 CMP EAX,dword ptr [RDI + 0x3a4]
1481a0388 JZ 0x1481a03db
1481a038a LEA RCX,[RDI + 0x3a8]
1481a0391 MOV RAX,qword ptr [RCX + 0x8]
1481a0395 TEST RAX,RAX
1481a0398 CMOVNZ RCX,RAX
1481a039c MOV EAX,dword ptr [RDI + 0x3b8]
1481a03a2 DEC EAX
1481a03a4 AND EAX,0x1
1481a03a7 MOV EDX,dword ptr [RCX + RAX*0x4]
1481a03aa CMP EDX,-0x1
1481a03ad JZ 0x1481a03db
1481a03af MOV R8,qword ptr [RDI + 0x370]
1481a03b6 NOP dword ptr [RAX + RAX*0x1]
1481a03c0 MOVSXD RAX,EDX
1481a03c3 IMUL RBX,RAX,0x1c
1481a03c7 ADD RBX,R8
1481a03ca CMP byte ptr [RBX],0x1
1481a03cd JZ 0x1481a0652
1481a03d3 MOV EDX,dword ptr [RBX + 0x14]
1481a03d6 CMP EDX,-0x1
1481a03d9 JNZ 0x1481a03c0
1481a03db MOV RBX,RSI
1481a03de MOV R9,qword ptr [RBP + 0x38]
1481a03e2 MOV qword ptr [RSP + 0x20],R14
1481a03e7 MOV R8D,0x29f
1481a03ed LEA RDX,[0x14cf4deb0]
1481a03f4 LEA RCX,[0x14bcf2cd8]
1481a03fb CALL 0x140f8dfd0
1481a0400 TEST AL,AL
1481a0402 JZ 0x1481a0406
1481a0404 NOP
1481a0405 INT3
1481a0406 MOV dword ptr [RBX + 0x4],0x41700000
1481a040d MOV EAX,dword ptr [RDI + 0x378]
1481a0413 CMP EAX,dword ptr [RDI + 0x3a4]
1481a0419 JZ 0x1481a046b
1481a041b LEA RCX,[RDI + 0x3a8]
1481a0422 MOV RAX,qword ptr [RCX + 0x8]
1481a0426 TEST RAX,RAX
1481a0429 CMOVNZ RCX,RAX
1481a042d MOV EAX,dword ptr [RDI + 0x3b8]
1481a0433 DEC EAX
1481a0435 AND EAX,0x1
1481a0438 MOV EDX,dword ptr [RCX + RAX*0x4]
1481a043b CMP EDX,-0x1
1481a043e JZ 0x1481a046b
1481a0440 MOV R8,qword ptr [RDI + 0x370]
1481a0447 NOP word ptr [RAX + RAX*0x1]
1481a0450 MOVSXD RAX,EDX
1481a0453 IMUL RBX,RAX,0x1c
1481a0457 ADD RBX,R8
1481a045a CMP byte ptr [RBX],0x1
1481a045d JZ 0x1481a0660
1481a0463 MOV EDX,dword ptr [RBX + 0x14]
1481a0466 CMP EDX,-0x1
1481a0469 JNZ 0x1481a0450
1481a046b MOV RBX,RSI
1481a046e MOV R9,qword ptr [RBP + 0x38]
1481a0472 MOV qword ptr [RSP + 0x20],R14
1481a0477 MOV R8D,0x29f
1481a047d LEA RDX,[0x14cf4deb0]
1481a0484 LEA RCX,[0x14bcf2cd8]
1481a048b CALL 0x140f8dfd0
1481a0490 TEST AL,AL
1481a0492 JZ 0x1481a0496
1481a0494 NOP
1481a0495 INT3
1481a0496 MOV dword ptr [RBX + 0x10],0x428c0000
1481a049d MOV EAX,dword ptr [RDI + 0x378]
1481a04a3 CMP EAX,dword ptr [RDI + 0x3a4]
1481a04a9 JZ 0x1481a04fb
1481a04ab LEA RCX,[RDI + 0x3a8]
1481a04b2 MOV RAX,qword ptr [RCX + 0x8]
1481a04b6 TEST RAX,RAX
1481a04b9 CMOVNZ RCX,RAX
1481a04bd MOV EAX,dword ptr [RDI + 0x3b8]
1481a04c3 DEC EAX
1481a04c5 AND EAX,0x2
1481a04c8 MOV EDX,dword ptr [RCX + RAX*0x4]
1481a04cb CMP EDX,-0x1
1481a04ce JZ 0x1481a04fb
1481a04d0 MOV R8,qword ptr [RDI + 0x370]
1481a04d7 NOP word ptr [RAX + RAX*0x1]
1481a04e0 MOVSXD RAX,EDX
1481a04e3 IMUL RBX,RAX,0x1c
1481a04e7 ADD RBX,R8
1481a04ea CMP byte ptr [RBX],0x2
1481a04ed JZ 0x1481a066e
1481a04f3 MOV EDX,dword ptr [RBX + 0x14]
1481a04f6 CMP EDX,-0x1
1481a04f9 JNZ 0x1481a04e0
1481a04fb MOV RBX,RSI
1481a04fe MOV R9,qword ptr [RBP + 0x38]
1481a0502 MOV qword ptr [RSP + 0x20],R14
1481a0507 MOV R8D,0x29f
1481a050d LEA RDX,[0x14cf4deb0]
1481a0514 LEA RCX,[0x14bcf2cd8]
1481a051b CALL 0x140f8dfd0
1481a0520 TEST AL,AL
1481a0522 JZ 0x1481a0526
1481a0524 NOP
1481a0525 INT3
1481a0526 MOV dword ptr [RBX + 0x4],0x41c80000
1481a052d MOV EAX,dword ptr [RDI + 0x378]
1481a0533 CMP EAX,dword ptr [RDI + 0x3a4]
1481a0539 JZ 0x1481a058b
1481a053b LEA RCX,[RDI + 0x3a8]
1481a0542 MOV RAX,qword ptr [RCX + 0x8]
1481a0546 TEST RAX,RAX
1481a0549 CMOVNZ RCX,RAX
1481a054d MOV EAX,dword ptr [RDI + 0x3b8]
1481a0553 DEC EAX
1481a0555 AND EAX,0x2
1481a0558 MOV EDX,dword ptr [RCX + RAX*0x4]
1481a055b CMP EDX,-0x1
1481a055e JZ 0x1481a058b
1481a0560 MOV R8,qword ptr [RDI + 0x370]
1481a0567 NOP word ptr [RAX + RAX*0x1]
1481a0570 MOVSXD RAX,EDX
1481a0573 IMUL RBX,RAX,0x1c
1481a0577 ADD RBX,R8
1481a057a CMP byte ptr [RBX],0x2
1481a057d JZ 0x1481a067c
1481a0583 MOV EDX,dword ptr [RBX + 0x14]
1481a0586 CMP EDX,-0x1
1481a0589 JNZ 0x1481a0570
1481a058b MOV RBX,RSI
1481a058e MOV R9,qword ptr [RBP + 0x38]
1481a0592 MOV qword ptr [RSP + 0x20],R14
1481a0597 MOV R8D,0x29f
1481a059d LEA RDX,[0x14cf4deb0]
1481a05a4 LEA RCX,[0x14bcf2cd8]
1481a05ab CALL 0x140f8dfd0
1481a05b0 TEST AL,AL
1481a05b2 JZ 0x1481a05b6
1481a05b4 NOP
1481a05b5 INT3
1481a05b6 MOV dword ptr [RBX + 0x10],0x42b40000
1481a05bd MOV qword ptr [RBP + -0x60],RSI
1481a05c1 MOV qword ptr [RBP + -0x58],RSI
1481a05c5 MOV qword ptr [RBP + -0x50],RSI
1481a05c9 XORPS XMM0,XMM0
1481a05cc MOVUPS xmmword ptr [RBP + -0x78],XMM0
1481a05d0 MOV dword ptr [RBP + -0x68],0x42700000
1481a05d7 LEA RDX,[0x14bd095a0]
1481a05de LEA RCX,[RBP + -0x60]
1481a05e2 CALL 0x140cf9360
1481a05e7 LEA RCX,[RBP + 0x8]
1481a05eb CALL 0x141014800
1481a05f0 MOV RCX,qword ptr [RAX]
1481a05f3 MOV qword ptr [RBP + -0x50],RCX
1481a05f7 MOV byte ptr [RBP + -0x48],0x0
1481a05fb LEA RCX,[RDI + 0x320]
1481a0602 LEA RDX,[RBP + -0x78]
1481a0606 CALL 0x148149860
1481a060b NOP
1481a060c MOV RCX,qword ptr [RBP + -0x60]
1481a0610 TEST RCX,RCX
1481a0613 JZ 0x1481a061b
1481a0615 CALL 0x140e282f0
1481a061a NOP
1481a061b MOV dword ptr [RDI + 0x330],0x42700000
1481a0625 MOV RAX,RDI
1481a0628 ADD RSP,0x110
1481a062f POP R14
1481a0631 POP RDI
1481a0632 POP RSI
1481a0633 POP RBX
1481a0634 POP RBP
1481a0635 RET
1481a0636 TEST RBX,RBX
1481a0639 JNZ 0x1481a02f5
1481a063f JMP 0x1481a02cd
1481a0644 TEST RBX,RBX
1481a0647 JNZ 0x1481a0375
1481a064d JMP 0x1481a034d
1481a0652 TEST RBX,RBX
1481a0655 JNZ 0x1481a0406
1481a065b JMP 0x1481a03de
1481a0660 TEST RBX,RBX
1481a0663 JNZ 0x1481a0496
1481a0669 JMP 0x1481a046e
1481a066e TEST RBX,RBX
1481a0671 JNZ 0x1481a0526
1481a0677 JMP 0x1481a04fe
1481a067c TEST RBX,RBX
1481a067f JNZ 0x1481a05b6
1481a0685 JMP 0x1481a058e
*/

/* 1481a1610 FinalizeCalibration */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FinalizeCalibration(longlong param_1)

{
  undefined8 *puVar1;
  undefined1 auStackX_8 [8];
  undefined1 auStackX_20 [4];
  undefined4 uStackX_24;
  
  *(undefined1 *)(param_1 + 0x358) = 4;
  *(undefined1 *)(param_1 + 0x350) = 1;
  puVar1 = (undefined8 *)func_0x000141014800(auStackX_8);
  *(undefined8 *)(param_1 + 0x348) = *puVar1;
  if ((2 < DAT_14eab53c8) && (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf655e8), 2 < DAT_14eab53c8)
     ) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65668,(double)*(float *)(param_1 + 800));
    if (((2 < DAT_14eab53c8) &&
        (((func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf656b8,(double)*(float *)(param_1 + 0x324)),
          2 < DAT_14eab53c8 &&
          (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf656f8,(double)*(float *)(param_1 + 0x328)),
          2 < DAT_14eab53c8)) &&
         (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65750,(double)*(float *)(param_1 + 0x32c)),
         2 < DAT_14eab53c8)))) &&
       (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf65790,(double)*(float *)(param_1 + 0x330)),
       2 < DAT_14eab53c8)) {
      func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf657e0,
                          (double)(*(float *)(param_1 + 0x330) + *(float *)(param_1 + 0x32c) +
                                   *(float *)(param_1 + 0x328) +
                                  *(float *)(param_1 + 0x324) + *(float *)(param_1 + 800)));
    }
  }
  func_0x000148149e50(param_1 + 0x2a8,param_1 + 800);
  auStackX_20[0] = *(undefined1 *)(param_1 + 0x358);
  uStackX_24 = _DAT_14bcef9ec;
  func_0x000141894210(param_1 + 0x2c0,auStackX_20);
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
*/

/* 1481a2880 RunAudioVideoTest */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void RunAudioVideoTest(longlong param_1)

{
  undefined8 uVar1;
  undefined **ppuVar2;
  undefined1 auStack_128 [32];
  undefined1 uStack_108;
  undefined4 uStack_100;
  longlong *plStack_f8;
  undefined8 *puStack_e8;
  int iStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  longlong alStack_b8 [2];
  undefined **ppuStack_a8;
  undefined *puStack_98;
  longlong lStack_90;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined *puStack_78;
  longlong *plStack_70;
  longlong lStack_68;
  undefined **ppuStack_58;
  undefined *puStack_48;
  longlong lStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined *puStack_28;
  longlong *plStack_20;
  ulonglong uStack_18;
  
  uStack_18 = _DAT_14ea60b28 ^ (ulonglong)auStack_128;
  if (2 < DAT_14eab53c8) {
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf654c0);
  }
  *(undefined4 *)(param_1 + 0x324) = 0x42340000;
  uVar1 = func_0x00014618b360(param_1);
  uVar1 = func_0x000147a1e670(uVar1);
  puStack_48 = &UNK_14cf65b70;
  lStack_68 = 0x1481a1260;
  puStack_28 = &UNK_14cf65b18;
  plStack_70 = &lStack_40;
  puStack_e8 = (undefined8 *)0x0;
  iStack_e0 = 0;
  uStack_d8 = 0;
  uStack_d0 = 0;
  uStack_c8 = 0;
  plStack_f8 = alStack_b8;
  alStack_b8[0] = 0x1481a1260;
  ppuStack_a8 = (undefined **)0x0;
  ppuStack_58 = (undefined **)0x0;
  puStack_98 = &UNK_14cf65b70;
  uStack_88 = uStack_38;
  uStack_84 = uStack_34;
  uStack_80 = uStack_30;
  uStack_7c = uStack_2c;
  puStack_78 = &UNK_14cf65b18;
  lStack_90 = param_1;
  lStack_40 = param_1;
  plStack_20 = plStack_70;
  plStack_70 = (longlong *)(*_DAT_14cf65b78)(&puStack_98);
  lStack_68 = 0;
  uStack_100 = _DAT_14bd17874;
  uStack_108 = 0;
  func_0x0001478cf760(uVar1,param_1 + 0x400,&puStack_e8,_DAT_14bcef9ec);
  if (alStack_b8[0] != 0) {
    ppuVar2 = &puStack_98;
    if (ppuStack_a8 != (undefined **)0x0) {
      ppuVar2 = ppuStack_a8;
    }
    (**(code **)(*ppuVar2 + 0x10))();
  }
  puStack_78 = &UNK_14d3ac0f0;
  func_0x000140c70210(&uStack_d8);
  if ((iStack_e0 != 0) && (puStack_e8 != (undefined8 *)0x0)) {
    (**(code **)*puStack_e8)(puStack_e8,0);
    func_0x000140d20c70(&puStack_e8,0,0,0x10);
    iStack_e0 = 0;
  }
  if (puStack_e8 != (undefined8 *)0x0) {
    func_0x000140e282f0();
  }
  if (lStack_68 != 0) {
    ppuVar2 = &puStack_48;
    if (ppuStack_58 != (undefined **)0x0) {
      ppuVar2 = ppuStack_58;
    }
    (**(code **)(*ppuVar2 + 0x10))();
  }
  func_0x000148149ef0(param_1 + 0x2c0,*(undefined1 *)(param_1 + 0x358),_DAT_14bcef9ec);
  func_0x00014b880380(uStack_18 ^ (ulonglong)auStack_128);
  return;
}


/* Instruction evidence:
1481a2880 MOV qword ptr [RSP + 0x10],RBX
1481a2885 MOV qword ptr [RSP + 0x18],RSI
1481a288a MOV qword ptr [RSP + 0x20],RDI
1481a288f PUSH RBP
1481a2890 LEA RBP,[RSP + -0x20]
1481a2895 SUB RSP,0x120
1481a289c MOV RAX,qword ptr [0x14ea60b28]
1481a28a3 XOR RAX,RSP
1481a28a6 MOV qword ptr [RBP + 0x10],RAX
1481a28aa MOV RDI,RCX
1481a28ad CMP byte ptr [0x14eab53c8],0x3
1481a28b4 JC 0x1481a28c9
1481a28b6 LEA RDX,[0x14cf654c0]
1481a28bd LEA RCX,[0x14eab53c8]
1481a28c4 CALL 0x140f24ba0
1481a28c9 MOV dword ptr [RDI + 0x324],0x42340000
1481a28d3 MOV RCX,RDI
1481a28d6 CALL 0x14618b360
1481a28db MOV RCX,RAX
1481a28de CALL 0x147a1e670
1481a28e3 MOV RBX,RAX
1481a28e6 MOV qword ptr [RBP + -0x18],RDI
1481a28ea LEA RAX,[0x14cf65b70]
1481a28f1 MOV qword ptr [RBP + -0x20],RAX
1481a28f5 LEA RCX,[0x1481a1260]
1481a28fc MOV qword ptr [RBP + -0x40],RCX
1481a2900 LEA RAX,[0x14cf65b18]
1481a2907 MOV qword ptr [RBP],RAX
1481a290b LEA RAX,[RBP + -0x18]
1481a290f MOV qword ptr [RBP + 0x8],RAX
1481a2913 XOR ESI,ESI
1481a2915 MOV qword ptr [RSP + 0x40],RSI
1481a291a MOV dword ptr [RSP + 0x48],ESI
1481a291e LEA RAX,[RSP + 0x50]
1481a2923 MOV qword ptr [RSP + 0x30],RAX
1481a2928 MOV qword ptr [RSP + 0x50],RSI
1481a292d MOV qword ptr [RSP + 0x58],RSI
1481a2932 MOV qword ptr [RSP + 0x60],RSI
1481a2937 LEA RAX,[RSP + 0x70]
1481a293c MOV qword ptr [RSP + 0x30],RAX
1481a2941 MOV qword ptr [RSP + 0x70],RCX
1481a2946 MOV qword ptr [RBP + -0x80],RSI
1481a294a MOV qword ptr [RBP + -0x30],RSI
1481a294e LEA RCX,[RBP + -0x70]
1481a2952 MOVAPS XMM0,xmmword ptr [RBP + -0x20]
1481a2956 MOVAPS xmmword ptr [RBP + -0x70],XMM0
1481a295a MOVAPS XMM1,xmmword ptr [RBP + -0x10]
1481a295e MOVAPS xmmword ptr [RBP + -0x60],XMM1
1481a2962 MOVAPS XMM0,xmmword ptr [RBP]
1481a2966 MOVDQA xmmword ptr [RBP + -0x50],XMM0
1481a296b MOV RAX,qword ptr [0x14cf65b78]
1481a2972 CALL RAX
1481a2974 MOV qword ptr [RBP + -0x48],RAX
1481a2978 MOV qword ptr [RBP + -0x40],RSI
1481a297c LEA RDX,[RDI + 0x400]
1481a2983 MOVSS XMM0,dword ptr [0x14bd17874]
1481a298b MOVSS dword ptr [RSP + 0x28],XMM0
1481a2991 MOV byte ptr [RSP + 0x20],SIL
1481a2996 MOVSS XMM3,dword ptr [0x14bcef9ec]
1481a299e LEA R8,[RSP + 0x40]
1481a29a3 MOV RCX,RBX
1481a29a6 CALL 0x1478cf760
1481a29ab NOP
1481a29ac CMP qword ptr [RSP + 0x70],RSI
1481a29b1 JZ 0x1481a29c8
1481a29b3 MOV RAX,qword ptr [RBP + -0x80]
1481a29b7 LEA RCX,[RBP + -0x70]
1481a29bb TEST RAX,RAX
1481a29be CMOVNZ RCX,RAX
1481a29c2 MOV RAX,qword ptr [RCX]
1481a29c5 CALL qword ptr [RAX + 0x10]
1481a29c8 LEA RAX,[0x14d3ac0f0]
1481a29cf MOV qword ptr [RBP + -0x50],RAX
1481a29d3 LEA RCX,[RSP + 0x50]
1481a29d8 CALL 0x140c70210
1481a29dd NOP
1481a29de MOV RCX,qword ptr [RSP + 0x40]
1481a29e3 CMP dword ptr [RSP + 0x48],0x0
1481a29e8 JZ 0x1481a2a14
1481a29ea TEST RCX,RCX
1481a29ed JZ 0x1481a2a14
1481a29ef MOV RAX,qword ptr [RCX]
1481a29f2 XOR EDX,EDX
1481a29f4 CALL qword ptr [RAX]
1481a29f6 MOV R9D,0x10
1481a29fc XOR R8D,R8D
1481a29ff XOR EDX,EDX
1481a2a01 LEA RCX,[RSP + 0x40]
1481a2a06 CALL 0x140d20c70
1481a2a0b MOV dword ptr [RSP + 0x48],ESI
1481a2a0f MOV RCX,qword ptr [RSP + 0x40]
1481a2a14 TEST RCX,RCX
1481a2a17 JZ 0x1481a2a1f
1481a2a19 CALL 0x140e282f0
1481a2a1e NOP
1481a2a1f CMP qword ptr [RBP + -0x40],0x0
1481a2a24 JZ 0x1481a2a3c
1481a2a26 MOV RAX,qword ptr [RBP + -0x30]
1481a2a2a LEA RCX,[RBP + -0x20]
1481a2a2e TEST RAX,RAX
1481a2a31 CMOVNZ RCX,RAX
1481a2a35 MOV RAX,qword ptr [RCX]
1481a2a38 CALL qword ptr [RAX + 0x10]
1481a2a3b NOP
1481a2a3c LEA RCX,[RDI + 0x2c0]
1481a2a43 MOVSS XMM2,dword ptr [0x14bcef9ec]
1481a2a4b MOVZX EDX,byte ptr [RDI + 0x358]
1481a2a52 CALL 0x148149ef0
1481a2a57 MOV RCX,qword ptr [RBP + 0x10]
1481a2a5b XOR RCX,RSP
1481a2a5e CALL 0x14b880380
1481a2a63 LEA R11,[RSP + 0x120]
1481a2a6b MOV RBX,qword ptr [R11 + 0x18]
1481a2a6f MOV RSI,qword ptr [R11 + 0x20]
1481a2a73 MOV RDI,qword ptr [R11 + 0x28]
1481a2a77 MOV RSP,R11
1481a2a7a POP RBP
1481a2a7b RET
*/
