
/* 1481b3090 ProgressionConstructor */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * ProgressionConstructor(undefined8 *param_1)

{
  longlong lVar1;
  undefined *puVar2;
  longlong unaff_GS_OFFSET;
  longlong alStack_28 [2];
  
  func_0x00014190cc60();
  *param_1 = &UNK_14cf49998;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  param_1[9] = 0;
  param_1[10] = 1;
  *(undefined4 *)(param_1 + 0xb) = 0;
  param_1[0xe] = 0;
  *(undefined4 *)(param_1 + 0xf) = 0x41200000;
  *(undefined4 *)((longlong)param_1 + 0x7c) = 0x3e3851ec;
  *(undefined4 *)(param_1 + 0x10) = 0x3f800000;
  *(undefined4 *)((longlong)param_1 + 0x84) = 0x41700000;
  *(undefined4 *)(param_1 + 0x11) = 0x42700000;
  *(undefined4 *)((longlong)param_1 + 0x8c) = 0x168;
  param_1[0x12] = 0x3c;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x18] = 0;
  *(undefined4 *)(param_1 + 0x19) = 0;
  *(undefined4 *)((longlong)param_1 + 0xcc) = 0x80;
  *(undefined4 *)(param_1 + 0x1a) = 0xffffffff;
  *(undefined4 *)((longlong)param_1 + 0xd4) = 0;
  param_1[0x1c] = 0;
  *(undefined4 *)(param_1 + 0x1d) = 0;
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  param_1[0x22] = 0;
  *(undefined4 *)(param_1 + 0x23) = 0;
  *(undefined4 *)((longlong)param_1 + 0x11c) = 0x80;
  *(undefined4 *)(param_1 + 0x24) = 0xffffffff;
  *(undefined4 *)((longlong)param_1 + 0x124) = 0;
  param_1[0x26] = 0;
  *(undefined4 *)(param_1 + 0x27) = 0;
  param_1[0x28] = 0;
  param_1[0x29] = 0;
  param_1[0x2c] = 0;
  *(undefined4 *)(param_1 + 0x2d) = 0;
  *(undefined4 *)((longlong)param_1 + 0x16c) = 0x80;
  *(undefined4 *)(param_1 + 0x2e) = 0xffffffff;
  *(undefined4 *)((longlong)param_1 + 0x174) = 0;
  param_1[0x30] = 0;
  *(undefined4 *)(param_1 + 0x31) = 0;
  param_1[0x32] = 0;
  param_1[0x33] = 0;
  param_1[0x36] = 0;
  *(undefined4 *)(param_1 + 0x37) = 0;
  *(undefined4 *)((longlong)param_1 + 0x1bc) = 0x80;
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  *(undefined4 *)((longlong)param_1 + 0x1c4) = 0;
  param_1[0x3a] = 0;
  *(undefined4 *)(param_1 + 0x3b) = 0;
  param_1[0x3c] = 0;
  param_1[0x3d] = 0;
  param_1[0x40] = 0;
  *(undefined4 *)(param_1 + 0x41) = 0;
  *(undefined4 *)((longlong)param_1 + 0x20c) = 0x80;
  *(undefined4 *)(param_1 + 0x42) = 0xffffffff;
  *(undefined4 *)((longlong)param_1 + 0x214) = 0;
  param_1[0x44] = 0;
  *(undefined4 *)(param_1 + 0x45) = 0;
  param_1[0x46] = 0;
  param_1[0x47] = 0;
  param_1[0x48] = 0;
  param_1[0x49] = 0;
  param_1[0x4a] = 0;
  *(undefined4 *)(param_1 + 0x4b) = 0;
  *(undefined2 *)((longlong)param_1 + 0x25c) = 0;
  param_1[0x4c] = 0;
  *(undefined4 *)(param_1 + 0x4d) = 0;
  param_1[0x4e] = 0;
  param_1[0x4f] = 0;
  param_1[0x50] = 0;
  param_1[0x51] = 0;
  param_1[0x52] = 0;
  param_1[0x53] = 0;
  param_1[0x54] = 0;
  *(undefined4 *)(param_1 + 0x55) = 0;
  param_1[0x56] = 0;
  param_1[0x57] = 0;
  param_1[0x58] = 0;
  param_1[0x59] = 0;
  param_1[0x5a] = 0;
  *(undefined4 *)(param_1 + 0x5b) = 0;
  *(undefined2 *)((longlong)param_1 + 0x2dc) = 0;
  param_1[0x5c] = 0;
  *(undefined4 *)(param_1 + 0x5d) = 0;
  param_1[0x5e] = 0;
  param_1[0x5f] = 0;
  param_1[0x60] = 0;
  param_1[0x61] = 0;
  param_1[0x62] = 0;
  param_1[99] = 0;
  param_1[100] = 0;
  *(undefined4 *)(param_1 + 0x65) = 0;
  *(undefined4 *)(param_1 + 0x66) = 0;
  param_1[0x67] = 0;
  param_1[0x68] = 0;
  param_1[0x69] = 0;
  param_1[0x6a] = 0;
  param_1[0x6b] = 0;
  param_1[0x6c] = 0;
  param_1[0x6d] = 0;
  param_1[0x6e] = 0;
  param_1[0x6f] = 0;
  param_1[0x70] = 0;
  param_1[0x71] = 0;
  param_1[0x72] = 0;
  param_1[0x73] = 0;
  param_1[0x74] = 0;
  param_1[0x75] = 0;
  param_1[0x76] = 0;
  param_1[0x79] = 0;
  *(undefined4 *)(param_1 + 0x7a) = 0;
  *(undefined4 *)((longlong)param_1 + 0x3d4) = 0x80;
  *(undefined4 *)(param_1 + 0x7b) = 0xffffffff;
  *(undefined4 *)((longlong)param_1 + 0x3dc) = 0;
  param_1[0x7d] = 0;
  *(undefined4 *)(param_1 + 0x7e) = 0;
  param_1[0x80] = 0;
  param_1[0x81] = 0;
  param_1[0x84] = 0;
  *(undefined4 *)(param_1 + 0x85) = 0;
  *(undefined4 *)((longlong)param_1 + 0x42c) = 0x80;
  *(undefined4 *)(param_1 + 0x86) = 0xffffffff;
  *(undefined4 *)((longlong)param_1 + 0x434) = 0;
  param_1[0x88] = 0;
  *(undefined4 *)(param_1 + 0x89) = 0;
  param_1[0x8b] = 0;
  param_1[0x8c] = 0;
  param_1[0x8f] = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(undefined4 *)((longlong)param_1 + 0x484) = 0x80;
  *(undefined4 *)(param_1 + 0x91) = 0xffffffff;
  *(undefined4 *)((longlong)param_1 + 0x48c) = 0;
  param_1[0x93] = 0;
  *(undefined4 *)(param_1 + 0x94) = 0;
  param_1[0x95] = 0;
  lVar1 = *(longlong *)(*(longlong *)(unaff_GS_OFFSET + 0x58) + (ulonglong)_DAT_14ee952f8 * 8);
  if ((*(int *)(lVar1 + 0x908c) < _DAT_14edbfe9c) &&
     (func_0x00014b87ff78(&DAT_14edbfe9c), _DAT_14edbfe9c == -1)) {
    func_0x00014151ad40(&DAT_14e9f11e0);
    _DAT_14e9f11e0 = &UNK_14cf70e80;
    _DAT_14e9f11f0 = 0;
    func_0x00014191aaf0(L"/Game/Data/Progression/DT_Challenges.DT_Challenges");
    func_0x000140cf7750(alStack_28,L"/Game/Data/Progression/DT_Challenges.DT_Challenges");
    func_0x000141958ae0(alStack_28,1);
    _DAT_14e9f11f0 = func_0x0001481b0ef0(alStack_28,0);
    if (_DAT_14e9f11f0 == 0) {
      func_0x000141924bb0(L"/Game/Data/Progression/DT_Challenges.DT_Challenges");
    }
    if (alStack_28[0] != 0) {
      func_0x000140e282f0();
    }
    func_0x00014b87fc50(0x14ba6bcf0);
    func_0x00014b87ff10(&DAT_14edbfe9c);
  }
  if (_DAT_14e9f11f0 == 0) {
    if (DAT_14eab53c8 < 2) goto LAB_1481b34fb;
    puVar2 = &UNK_14cf70f48;
  }
  else {
    param_1[0xc] = _DAT_14e9f11f0;
    if (DAT_14eab53c8 < 3) goto LAB_1481b34fb;
    puVar2 = &UNK_14cf70ea0;
  }
  func_0x000140f24ba0(&DAT_14eab53c8,puVar2);
LAB_1481b34fb:
  if ((*(int *)(lVar1 + 0x908c) < _DAT_14edbfea4) &&
     (func_0x00014b87ff78(&DAT_14edbfea4), _DAT_14edbfea4 == -1)) {
    func_0x00014151ad40(&DAT_14e9f11f8);
    _DAT_14e9f11f8 = &UNK_14cf70e80;
    _DAT_14e9f1208 = 0;
    func_0x00014191aaf0(L"/Game/Data/Progression/DT_LevelData.DT_LevelData");
    func_0x000140cf7750(alStack_28,L"/Game/Data/Progression/DT_LevelData.DT_LevelData");
    func_0x000141958ae0(alStack_28,1);
    _DAT_14e9f1208 = func_0x0001481b0ef0(alStack_28,0);
    if (_DAT_14e9f1208 == 0) {
      func_0x000141924bb0(L"/Game/Data/Progression/DT_LevelData.DT_LevelData");
    }
    if (alStack_28[0] != 0) {
      func_0x000140e282f0();
    }
    func_0x00014b87fc50(0x14ba6bd20);
    func_0x00014b87ff10(&DAT_14edbfea4);
  }
  if (_DAT_14e9f1208 == 0) {
    if (DAT_14eab53c8 < 2) {
      return param_1;
    }
    puVar2 = &UNK_14cf71038;
  }
  else {
    param_1[0xd] = _DAT_14e9f1208;
    if (DAT_14eab53c8 < 3) {
      return param_1;
    }
    puVar2 = &UNK_14cf70fc8;
  }
  func_0x000140f24ba0(&DAT_14eab53c8,puVar2);
  return param_1;
}


/* Instruction evidence:
1481b3090 MOV qword ptr [RSP + 0x10],RBX
1481b3095 MOV qword ptr [RSP + 0x18],RBP
1481b309a MOV qword ptr [RSP + 0x8],RCX
1481b309f PUSH RSI
1481b30a0 PUSH RDI
1481b30a1 PUSH R14
1481b30a3 SUB RSP,0x30
1481b30a7 MOV RBX,RCX
1481b30aa CALL 0x14190cc60
1481b30af NOP
1481b30b0 LEA RAX,[0x14cf49998]
1481b30b7 MOV qword ptr [RBX],RAX
1481b30ba XOR ESI,ESI
1481b30bc MOV qword ptr [RBX + 0x28],RSI
1481b30c0 MOV qword ptr [RBX + 0x30],RSI
1481b30c4 MOV qword ptr [RBX + 0x38],RSI
1481b30c8 MOV dword ptr [RBX + 0x40],ESI
1481b30cb MOV qword ptr [RBX + 0x48],RSI
1481b30cf MOV qword ptr [RBX + 0x50],0x1
1481b30d7 MOV dword ptr [RBX + 0x58],ESI
1481b30da MOV qword ptr [RBX + 0x70],RSI
1481b30de MOV dword ptr [RBX + 0x78],0x41200000
1481b30e5 MOV dword ptr [RBX + 0x7c],0x3e3851ec
1481b30ec MOV dword ptr [RBX + 0x80],0x3f800000
1481b30f6 MOV dword ptr [RBX + 0x84],0x41700000
1481b3100 MOV dword ptr [RBX + 0x88],0x42700000
1481b310a MOV dword ptr [RBX + 0x8c],0x168
1481b3114 MOV qword ptr [RBX + 0x90],0x3c
1481b311f MOV qword ptr [RBX + 0x98],RSI
1481b3126 MOV qword ptr [RBX + 0xa0],RSI
1481b312d MOV qword ptr [RBX + 0xa8],RSI
1481b3134 MOV qword ptr [RBX + 0xc0],RSI
1481b313b MOV dword ptr [RBX + 0xc8],ESI
1481b3141 MOV dword ptr [RBX + 0xcc],0x80
1481b314b MOV dword ptr [RBX + 0xd0],0xffffffff
1481b3155 MOV dword ptr [RBX + 0xd4],ESI
1481b315b MOV qword ptr [RBX + 0xe0],RSI
1481b3162 MOV dword ptr [RBX + 0xe8],ESI
1481b3168 MOV qword ptr [RBX + 0xf0],RSI
1481b316f MOV qword ptr [RBX + 0xf8],RSI
1481b3176 MOV qword ptr [RBX + 0x110],RSI
1481b317d MOV dword ptr [RBX + 0x118],ESI
1481b3183 MOV dword ptr [RBX + 0x11c],0x80
1481b318d MOV dword ptr [RBX + 0x120],0xffffffff
1481b3197 MOV dword ptr [RBX + 0x124],ESI
1481b319d MOV qword ptr [RBX + 0x130],RSI
1481b31a4 MOV dword ptr [RBX + 0x138],ESI
1481b31aa MOV qword ptr [RBX + 0x140],RSI
1481b31b1 MOV qword ptr [RBX + 0x148],RSI
1481b31b8 MOV qword ptr [RBX + 0x160],RSI
1481b31bf MOV dword ptr [RBX + 0x168],ESI
1481b31c5 MOV dword ptr [RBX + 0x16c],0x80
1481b31cf MOV dword ptr [RBX + 0x170],0xffffffff
1481b31d9 MOV dword ptr [RBX + 0x174],ESI
1481b31df MOV qword ptr [RBX + 0x180],RSI
1481b31e6 MOV dword ptr [RBX + 0x188],ESI
1481b31ec MOV qword ptr [RBX + 0x190],RSI
1481b31f3 MOV qword ptr [RBX + 0x198],RSI
1481b31fa MOV qword ptr [RBX + 0x1b0],RSI
1481b3201 MOV dword ptr [RBX + 0x1b8],ESI
1481b3207 MOV dword ptr [RBX + 0x1bc],0x80
1481b3211 MOV dword ptr [RBX + 0x1c0],0xffffffff
1481b321b MOV dword ptr [RBX + 0x1c4],ESI
1481b3221 MOV qword ptr [RBX + 0x1d0],RSI
1481b3228 MOV dword ptr [RBX + 0x1d8],ESI
1481b322e MOV qword ptr [RBX + 0x1e0],RSI
1481b3235 MOV qword ptr [RBX + 0x1e8],RSI
1481b323c MOV qword ptr [RBX + 0x200],RSI
1481b3243 MOV dword ptr [RBX + 0x208],ESI
1481b3249 MOV dword ptr [RBX + 0x20c],0x80
1481b3253 MOV dword ptr [RBX + 0x210],0xffffffff
1481b325d MOV dword ptr [RBX + 0x214],ESI
1481b3263 MOV qword ptr [RBX + 0x220],RSI
1481b326a MOV dword ptr [RBX + 0x228],ESI
1481b3270 MOV qword ptr [RBX + 0x230],RSI
1481b3277 MOV qword ptr [RBX + 0x238],RSI
1481b327e MOV qword ptr [RBX + 0x240],RSI
1481b3285 MOV qword ptr [RBX + 0x248],RSI
1481b328c MOV qword ptr [RBX + 0x250],RSI
1481b3293 MOV dword ptr [RBX + 0x258],ESI
1481b3299 MOV word ptr [RBX + 0x25c],SI
1481b32a0 MOV qword ptr [RBX + 0x260],RSI
1481b32a7 MOV dword ptr [RBX + 0x268],ESI
1481b32ad MOV qword ptr [RBX + 0x270],RSI
1481b32b4 MOV qword ptr [RBX + 0x278],RSI
1481b32bb MOV qword ptr [RBX + 0x280],RSI
1481b32c2 MOV qword ptr [RBX + 0x288],RSI
1481b32c9 MOV qword ptr [RBX + 0x290],RSI
1481b32d0 MOV qword ptr [RBX + 0x298],RSI
1481b32d7 MOV qword ptr [RBX + 0x2a0],RSI
1481b32de MOV dword ptr [RBX + 0x2a8],ESI
1481b32e4 MOV qword ptr [RBX + 0x2b0],RSI
1481b32eb MOV qword ptr [RBX + 0x2b8],RSI
1481b32f2 MOV qword ptr [RBX + 0x2c0],RSI
1481b32f9 MOV qword ptr [RBX + 0x2c8],RSI
1481b3300 MOV qword ptr [RBX + 0x2d0],RSI
1481b3307 MOV dword ptr [RBX + 0x2d8],ESI
1481b330d MOV word ptr [RBX + 0x2dc],SI
1481b3314 MOV qword ptr [RBX + 0x2e0],RSI
1481b331b MOV dword ptr [RBX + 0x2e8],ESI
1481b3321 MOV qword ptr [RBX + 0x2f0],RSI
1481b3328 MOV qword ptr [RBX + 0x2f8],RSI
1481b332f MOV qword ptr [RBX + 0x300],RSI
1481b3336 MOV qword ptr [RBX + 0x308],RSI
1481b333d MOV qword ptr [RBX + 0x310],RSI
1481b3344 MOV qword ptr [RBX + 0x318],RSI
1481b334b MOV qword ptr [RBX + 0x320],RSI
1481b3352 MOV dword ptr [RBX + 0x328],ESI
1481b3358 MOV dword ptr [RBX + 0x330],ESI
1481b335e MOV qword ptr [RBX + 0x338],RSI
1481b3365 MOV qword ptr [RBX + 0x340],RSI
1481b336c MOV qword ptr [RBX + 0x348],RSI
1481b3373 MOV qword ptr [RBX + 0x350],RSI
1481b337a MOV qword ptr [RBX + 0x358],RSI
1481b3381 MOV qword ptr [RBX + 0x360],RSI
1481b3388 MOV qword ptr [RBX + 0x368],RSI
1481b338f MOV qword ptr [RBX + 0x370],RSI
1481b3396 MOV qword ptr [RBX + 0x378],RSI
1481b339d MOV qword ptr [RBX + 0x380],RSI
1481b33a4 MOV qword ptr [RBX + 0x388],RSI
1481b33ab MOV qword ptr [RBX + 0x390],RSI
1481b33b2 MOV qword ptr [RBX + 0x398],RSI
1481b33b9 MOV qword ptr [RBX + 0x3a0],RSI
1481b33c0 MOV qword ptr [RBX + 0x3a8],RSI
1481b33c7 MOV qword ptr [RBX + 0x3b0],RSI
1481b33ce MOV qword ptr [RBX + 0x3c8],RSI
1481b33d5 MOV dword ptr [RBX + 0x3d0],ESI
1481b33db MOV dword ptr [RBX + 0x3d4],0x80
1481b33e5 MOV dword ptr [RBX + 0x3d8],0xffffffff
1481b33ef MOV dword ptr [RBX + 0x3dc],ESI
1481b33f5 MOV qword ptr [RBX + 0x3e8],RSI
1481b33fc MOV dword ptr [RBX + 0x3f0],ESI
1481b3402 MOV qword ptr [RBX + 0x400],RSI
1481b3409 MOV qword ptr [RBX + 0x408],RSI
1481b3410 MOV qword ptr [RBX + 0x420],RSI
1481b3417 MOV dword ptr [RBX + 0x428],ESI
1481b341d MOV dword ptr [RBX + 0x42c],0x80
1481b3427 MOV dword ptr [RBX + 0x430],0xffffffff
1481b3431 MOV dword ptr [RBX + 0x434],ESI
1481b3437 MOV qword ptr [RBX + 0x440],RSI
1481b343e MOV dword ptr [RBX + 0x448],ESI
1481b3444 MOV qword ptr [RBX + 0x458],RSI
1481b344b MOV qword ptr [RBX + 0x460],RSI
1481b3452 MOV qword ptr [RBX + 0x478],RSI
1481b3459 MOV dword ptr [RBX + 0x480],ESI
1481b345f MOV dword ptr [RBX + 0x484],0x80
1481b3469 MOV dword ptr [RBX + 0x488],0xffffffff
1481b3473 MOV dword ptr [RBX + 0x48c],ESI
1481b3479 MOV qword ptr [RBX + 0x498],RSI
1481b3480 MOV dword ptr [RBX + 0x4a0],ESI
1481b3486 MOV qword ptr [RBX + 0x4a8],RSI
1481b348d MOV ECX,dword ptr [0x14ee952f8]
1481b3493 MOV RAX,qword ptr GS:[0x58]
1481b349c MOV R14D,0x908c
1481b34a2 MOV RDI,qword ptr [RAX + RCX*0x8]
1481b34a6 LEA RBP,[0x14cf70e80]
1481b34ad MOV EAX,dword ptr [RDI + R14*0x1]
1481b34b1 CMP dword ptr [0x14edbfe9c],EAX
1481b34b7 JG 0x1481b357b
1481b34bd MOV RAX,qword ptr [0x14e9f11f0]
1481b34c4 TEST RAX,RAX
1481b34c7 JZ 0x1481b34df
1481b34c9 MOV qword ptr [RBX + 0x60],RAX
1481b34cd CMP byte ptr [0x14eab53c8],0x3
1481b34d4 JC 0x1481b34fb
1481b34d6 LEA RDX,[0x14cf70ea0]
1481b34dd JMP 0x1481b34ef
1481b34df CMP byte ptr [0x14eab53c8],0x2
1481b34e6 JC 0x1481b34fb
1481b34e8 LEA RDX,[0x14cf70f48]
1481b34ef LEA RCX,[0x14eab53c8]
1481b34f6 CALL 0x140f24ba0
1481b34fb MOV EAX,dword ptr [RDI + R14*0x1]
1481b34ff CMP dword ptr [0x14edbfea4],EAX
1481b3505 JG 0x1481b362c
1481b350b MOV RAX,qword ptr [0x14e9f1208]
1481b3512 TEST RAX,RAX
1481b3515 JZ 0x1481b352d
1481b3517 MOV qword ptr [RBX + 0x68],RAX
1481b351b CMP byte ptr [0x14eab53c8],0x3
1481b3522 JC 0x1481b354a
1481b3524 LEA RDX,[0x14cf70fc8]
1481b352b JMP 0x1481b353d
1481b352d CMP byte ptr [0x14eab53c8],0x2
1481b3534 JC 0x1481b354a
1481b3536 LEA RDX,[0x14cf71038]
1481b353d LEA RCX,[0x14eab53c8]
1481b3544 CALL 0x140f24ba0
1481b3549 NOP
1481b354a MOV RAX,RBX
1481b354d MOV RBX,qword ptr [RSP + 0x58]
1481b3552 MOV RBP,qword ptr [RSP + 0x60]
1481b3557 ADD RSP,0x30
1481b355b POP R14
1481b355d POP RDI
1481b355e POP RSI
1481b355f RET
1481b3560 LEA RCX,[0x14ba6bd20]
1481b3567 CALL 0x14b87fc50
1481b356c NOP
1481b356d LEA RCX,[0x14edbfea4]
1481b3574 CALL 0x14b87ff10
1481b3579 JMP 0x1481b350b
1481b357b LEA RCX,[0x14edbfe9c]
1481b3582 CALL 0x14b87ff78
1481b3587 CMP dword ptr [0x14edbfe9c],-0x1
1481b358e JNZ 0x1481b34bd
1481b3594 LEA RCX,[0x14e9f11e0]
1481b359b CALL 0x14151ad40
1481b35a0 NOP
1481b35a1 MOV qword ptr [0x14e9f11e0],RBP
1481b35a8 MOV qword ptr [0x14e9f11f0],RSI
1481b35af LEA RCX,[0x14cf710c0]
1481b35b6 CALL 0x14191aaf0
1481b35bb LEA RDX,[0x14cf710c0]
1481b35c2 LEA RCX,[RSP + 0x20]
1481b35c7 CALL 0x140cf7750
1481b35cc NOP
1481b35cd MOV DL,0x1
1481b35cf LEA RCX,[RSP + 0x20]
1481b35d4 CALL 0x141958ae0
1481b35d9 XOR EDX,EDX
1481b35db LEA RCX,[RSP + 0x20]
1481b35e0 CALL 0x1481b0ef0
1481b35e5 MOV qword ptr [0x14e9f11f0],RAX
1481b35ec TEST RAX,RAX
1481b35ef JNZ 0x1481b35fe
1481b35f1 LEA RCX,[0x14cf710c0]
1481b35f8 CALL 0x141924bb0
1481b35fd NOP
1481b35fe MOV RCX,qword ptr [RSP + 0x20]
1481b3603 TEST RCX,RCX
1481b3606 JZ 0x1481b360e
1481b3608 CALL 0x140e282f0
1481b360d NOP
1481b360e LEA RCX,[0x14ba6bcf0]
1481b3615 CALL 0x14b87fc50
1481b361a NOP
1481b361b LEA RCX,[0x14edbfe9c]
1481b3622 CALL 0x14b87ff10
1481b3627 JMP 0x1481b34bd
1481b362c LEA RCX,[0x14edbfea4]
1481b3633 CALL 0x14b87ff78
1481b3638 CMP dword ptr [0x14edbfea4],-0x1
1481b363f JNZ 0x1481b350b
1481b3645 LEA RCX,[0x14e9f11f8]
1481b364c CALL 0x14151ad40
1481b3651 NOP
1481b3652 MOV qword ptr [0x14e9f11f8],RBP
1481b3659 MOV qword ptr [0x14e9f1208],RSI
1481b3660 LEA RCX,[0x14cf71130]
1481b3667 CALL 0x14191aaf0
1481b366c LEA RDX,[0x14cf71130]
1481b3673 LEA RCX,[RSP + 0x20]
1481b3678 CALL 0x140cf7750
1481b367d NOP
1481b367e MOV DL,0x1
1481b3680 LEA RCX,[RSP + 0x20]
1481b3685 CALL 0x141958ae0
1481b368a XOR EDX,EDX
1481b368c LEA RCX,[RSP + 0x20]
1481b3691 CALL 0x1481b0ef0
1481b3696 MOV qword ptr [0x14e9f1208],RAX
1481b369d TEST RAX,RAX
1481b36a0 JNZ 0x1481b36af
1481b36a2 LEA RCX,[0x14cf71130]
1481b36a9 CALL 0x141924bb0
1481b36ae NOP
1481b36af MOV RCX,qword ptr [RSP + 0x20]
1481b36b4 TEST RCX,RCX
1481b36b7 JZ 0x1481b3560
1481b36bd CALL 0x140e282f0
1481b36c2 NOP
1481b36c3 JMP 0x1481b3560
*/

/* 1481b49f0 CalculateSessionXP */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int CalculateSessionXP(longlong param_1,int *param_2)

{
  float fVar1;
  int iVar2;
  undefined *puVar3;
  undefined8 *puVar4;
  int iVar5;
  undefined8 *puVar6;
  float fVar7;
  
  fVar1 = _DAT_14bcef9ec;
  fVar7 = (float)*param_2 * *(float *)(param_1 + 0x7c);
  iVar2 = (int)ROUND((fVar7 + fVar7) - _DAT_14bcfdb28) >> 1;
  fVar7 = (float)param_2[10] * _DAT_14bcfdb20 * *(float *)(param_1 + 0x78);
  iVar5 = *(int *)(param_1 + 0x8c);
  if (iVar2 < *(int *)(param_1 + 0x8c)) {
    iVar5 = iVar2;
  }
  iVar2 = *(int *)(param_1 + 0x90);
  if (param_2[3] + param_2[2] < *(int *)(param_1 + 0x90)) {
    iVar2 = param_2[3] + param_2[2];
  }
  iVar5 = (int)((float)(((int)ROUND((fVar7 + fVar7) - _DAT_14bcfdb28) >> 1) + iVar5 + iVar2) +
               (float)param_2[1] * *(float *)(param_1 + 0x84));
  if ((char)param_2[0xb] != '\0') {
    iVar5 = (int)((float)iVar5 + *(float *)(param_1 + 0x88));
  }
  puVar4 = *(undefined8 **)(param_2 + 0x10);
  puVar6 = puVar4 + (longlong)param_2[0x12] * 2;
  for (; fVar7 = fVar1, puVar4 != puVar6; puVar4 = puVar4 + 2) {
    if (*(int *)(puVar4 + 1) == 0) {
      puVar3 = &UNK_14bce4e94;
    }
    else {
      puVar3 = (undefined *)*puVar4;
    }
    iVar2 = func_0x000140d807c0(puVar3,"ironman");
    fVar7 = _DAT_14bd17818;
    if (iVar2 == 0) break;
  }
  puVar4 = *(undefined8 **)(param_2 + 0x10);
  puVar6 = puVar4 + (longlong)param_2[0x12] * 2;
  do {
    if (puVar4 == puVar6) {
LAB_1481b4b55:
      return (int)ROUND(((float)iVar5 * fVar7 + (float)iVar5 * fVar7) - _DAT_14bcfdb28) >> 1;
    }
    if (*(int *)(puVar4 + 1) == 0) {
      puVar3 = &UNK_14bce4e94;
    }
    else {
      puVar3 = (undefined *)*puVar4;
    }
    iVar2 = func_0x000140d807c0(puVar3,"hardcore");
    if (iVar2 == 0) {
      fVar7 = fVar7 + _DAT_14bd774a8;
      goto LAB_1481b4b55;
    }
    puVar4 = puVar4 + 2;
  } while( true );
}


/* Instruction evidence:
1481b49f0 MOV qword ptr [RSP + 0x8],RBX
1481b49f5 MOV qword ptr [RSP + 0x10],RBP
1481b49fa MOV qword ptr [RSP + 0x18],RSI
1481b49ff PUSH RDI
1481b4a00 SUB RSP,0x30
1481b4a04 MOV R9D,dword ptr [RCX + 0x8c]
1481b4a0b MOV RSI,RDX
1481b4a0e MOVD XMM1,dword ptr [RDX]
1481b4a12 MOV R10,RCX
1481b4a15 MOV EDX,dword ptr [RDX + 0xc]
1481b4a18 CVTDQ2PS XMM1,XMM1
1481b4a1b ADD EDX,dword ptr [RSI + 0x8]
1481b4a1e MOV R8D,dword ptr [R10 + 0x90]
1481b4a25 MOVD XMM0,dword ptr [RSI + 0x4]
1481b4a2a MULSS XMM1,dword ptr [RCX + 0x7c]
1481b4a2f CVTDQ2PS XMM0,XMM0
1481b4a32 ADDSS XMM1,XMM1
1481b4a36 MOVAPS xmmword ptr [RSP + 0x20],XMM6
1481b4a3b MULSS XMM0,dword ptr [R10 + 0x84]
1481b4a44 SUBSS XMM1,dword ptr [0x14bcfdb28]
1481b4a4c CVTSS2SI ECX,XMM1
1481b4a50 MOVD XMM1,dword ptr [RSI + 0x28]
1481b4a55 CVTDQ2PS XMM1,XMM1
1481b4a58 SAR ECX,0x1
1481b4a5a MULSS XMM1,dword ptr [0x14bcfdb20]
1481b4a62 MULSS XMM1,dword ptr [R10 + 0x78]
1481b4a68 ADDSS XMM1,XMM1
1481b4a6c SUBSS XMM1,dword ptr [0x14bcfdb28]
1481b4a74 CVTSS2SI EAX,XMM1
1481b4a78 SAR EAX,0x1
1481b4a7a CMP ECX,R9D
1481b4a7d CMOVL R9D,ECX
1481b4a81 ADD EAX,R9D
1481b4a84 CMP EDX,R8D
1481b4a87 CMOVL R8D,EDX
1481b4a8b ADD EAX,R8D
1481b4a8e CMP byte ptr [RSI + 0x2c],0x0
1481b4a92 MOVD XMM1,EAX
1481b4a96 CVTDQ2PS XMM1,XMM1
1481b4a99 ADDSS XMM1,XMM0
1481b4a9d CVTTSS2SI EBP,XMM1
1481b4aa1 JZ 0x1481b4ab7
1481b4aa3 MOVD XMM0,EBP
1481b4aa7 CVTDQ2PS XMM0,XMM0
1481b4aaa ADDSS XMM0,dword ptr [R10 + 0x88]
1481b4ab3 CVTTSS2SI EBP,XMM0
1481b4ab7 MOV RBX,qword ptr [RSI + 0x40]
1481b4abb MOVSXD RDI,dword ptr [RSI + 0x48]
1481b4abf MOVSS XMM6,dword ptr [0x14bcef9ec]
1481b4ac7 SHL RDI,0x4
1481b4acb ADD RDI,RBX
1481b4ace CMP RBX,RDI
1481b4ad1 JZ 0x1481b4b08
1481b4ad3 CMP dword ptr [RBX + 0x8],0x0
1481b4ad7 JZ 0x1481b4ade
1481b4ad9 MOV RCX,qword ptr [RBX]
1481b4adc JMP 0x1481b4ae5
1481b4ade LEA RCX,[0x14bce4e94]
1481b4ae5 LEA RDX,[0x14cf71470]
1481b4aec CALL 0x140d807c0
1481b4af1 TEST EAX,EAX
1481b4af3 JZ 0x1481b4b00
1481b4af5 ADD RBX,0x10
1481b4af9 CMP RBX,RDI
1481b4afc JNZ 0x1481b4ad3
1481b4afe JMP 0x1481b4b08
1481b4b00 MOVSS XMM6,dword ptr [0x14bd17818]
1481b4b08 MOV RBX,qword ptr [RSI + 0x40]
1481b4b0c MOVSXD RDI,dword ptr [RSI + 0x48]
1481b4b10 SHL RDI,0x4
1481b4b14 ADD RDI,RBX
1481b4b17 CMP RBX,RDI
1481b4b1a JZ 0x1481b4b55
1481b4b1c NOP dword ptr [RAX]
1481b4b20 CMP dword ptr [RBX + 0x8],0x0
1481b4b24 JZ 0x1481b4b2b
1481b4b26 MOV RCX,qword ptr [RBX]
1481b4b29 JMP 0x1481b4b32
1481b4b2b LEA RCX,[0x14bce4e94]
1481b4b32 LEA RDX,[0x14cf71478]
1481b4b39 CALL 0x140d807c0
1481b4b3e TEST EAX,EAX
1481b4b40 JZ 0x1481b4b4d
1481b4b42 ADD RBX,0x10
1481b4b46 CMP RBX,RDI
1481b4b49 JNZ 0x1481b4b20
1481b4b4b JMP 0x1481b4b55
1481b4b4d ADDSS XMM6,dword ptr [0x14bd774a8]
1481b4b55 MOV RBX,qword ptr [RSP + 0x40]
1481b4b5a MOV RSI,qword ptr [RSP + 0x50]
1481b4b5f MOVD XMM1,EBP
1481b4b63 MOV RBP,qword ptr [RSP + 0x48]
1481b4b68 CVTDQ2PS XMM1,XMM1
1481b4b6b MULSS XMM1,XMM6
1481b4b6f MOVAPS XMM6,xmmword ptr [RSP + 0x20]
1481b4b74 ADDSS XMM1,XMM1
1481b4b78 SUBSS XMM1,dword ptr [0x14bcfdb28]
1481b4b80 CVTSS2SI EAX,XMM1
1481b4b84 SAR EAX,0x1
1481b4b86 ADD RSP,0x30
1481b4b8a POP RDI
1481b4b8b RET
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
  iVar4 = CalculateSessionXP(param_1,param_1 + 0x46);
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
    func_0x0001481ce250(param_1,0xf,iVar4,&uStack_90);
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
    func_0x0001481ce250(param_1,0x15,1,&uStack_60);
  }
  else {
    *(int *)(param_1 + 0x5c) = (int)param_1[0x5c] + 1;
    uStack_70 = 0;
    uStack_68 = 0;
    func_0x0001481ce250(param_1,0xe,1,&uStack_70);
  }
  if (0 < (int)param_1[0x4d]) {
    *(int *)(param_1 + 0x5d) = (int)param_1[0x5d] + (int)param_1[0x4d];
  }
  uStack_50 = 0;
  uStack_48 = 0;
  func_0x0001481ce250(param_1,0xd,1,&uStack_50);
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

/* 1481c6a00 PrepareSessionRewards */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void PrepareSessionRewards(longlong param_1,undefined4 *param_2,int *param_3)

{
  longlong *plVar1;
  int iVar2;
  int *piVar3;
  undefined8 uVar4;
  code *pcVar5;
  undefined8 uVar6;
  longlong *plVar7;
  undefined1 auVar8 [16];
  float fVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  char cVar18;
  undefined4 uVar19;
  uint uVar20;
  undefined8 *puVar21;
  undefined1 (*pauVar22) [16];
  undefined *puVar23;
  int iVar24;
  uint uVar25;
  longlong lVar26;
  uint uVar27;
  longlong lVar28;
  undefined8 *puVar29;
  int iVar30;
  int iVar31;
  longlong unaff_GS_OFFSET;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  undefined8 unaff_retaddr;
  undefined1 auStack_9c8 [32];
  undefined *puStack_9a8;
  int *piStack_9a0;
  int *piStack_998;
  longlong lStack_990;
  longlong lStack_988;
  undefined *puStack_980;
  uint uStack_978;
  undefined1 auStack_974 [4];
  int iStack_970;
  int iStack_968;
  undefined4 uStack_964;
  undefined4 uStack_960;
  undefined4 uStack_95c;
  int iStack_958;
  int iStack_950;
  undefined8 uStack_948;
  longlong *plStack_940;
  undefined4 uStack_938;
  undefined4 uStack_930;
  undefined8 uStack_928;
  longlong *plStack_920;
  undefined4 uStack_918;
  undefined1 uStack_910;
  undefined8 uStack_908;
  longlong *plStack_900;
  undefined4 uStack_8f8;
  int iStack_8f0;
  undefined8 uStack_8e8;
  longlong *plStack_8e0;
  undefined4 uStack_8d8;
  undefined1 uStack_8d0;
  undefined8 uStack_8c8;
  longlong *plStack_8c0;
  undefined4 uStack_8b8;
  int iStack_8b0;
  undefined8 uStack_8a8;
  longlong *plStack_8a0;
  undefined4 uStack_898;
  undefined1 uStack_890;
  undefined8 uStack_888;
  undefined8 uStack_880;
  undefined4 uStack_878;
  int iStack_870;
  undefined8 uStack_868;
  undefined8 uStack_860;
  undefined4 uStack_858;
  undefined8 uStack_850;
  undefined8 uStack_848;
  undefined4 uStack_840;
  int iStack_838;
  undefined8 uStack_830;
  undefined8 uStack_828;
  undefined4 uStack_820;
  undefined8 uStack_818;
  undefined8 uStack_810;
  undefined4 uStack_808;
  int iStack_800;
  undefined8 uStack_7f8;
  undefined8 uStack_7f0;
  undefined4 uStack_7e8;
  undefined1 uStack_7e0;
  undefined8 uStack_7d8;
  undefined8 uStack_7d0;
  undefined4 uStack_7c8;
  int iStack_7c0;
  undefined8 uStack_7b8;
  undefined8 uStack_7b0;
  undefined4 uStack_7a8;
  undefined8 uStack_7a0;
  undefined8 uStack_798;
  undefined4 uStack_790;
  int iStack_788;
  undefined8 uStack_780;
  undefined8 uStack_778;
  undefined4 uStack_770;
  undefined8 uStack_768;
  undefined8 uStack_760;
  undefined4 uStack_758;
  int iStack_750;
  undefined8 uStack_748;
  undefined8 uStack_740;
  undefined4 uStack_738;
  undefined8 uStack_730;
  undefined8 uStack_728;
  undefined4 uStack_720;
  int iStack_718;
  undefined8 uStack_710;
  undefined8 uStack_708;
  undefined4 uStack_700;
  undefined8 uStack_6f8;
  undefined8 uStack_6f0;
  undefined4 uStack_6e8;
  int iStack_6e0;
  undefined8 uStack_6d8;
  undefined8 uStack_6d0;
  undefined4 uStack_6c8;
  undefined1 uStack_6c0;
  undefined8 uStack_6b8;
  undefined8 uStack_6b0;
  undefined4 uStack_6a8;
  int iStack_6a0;
  undefined8 uStack_698;
  undefined8 uStack_690;
  undefined4 uStack_688;
  undefined1 uStack_680;
  undefined8 uStack_678;
  undefined8 uStack_670;
  undefined4 uStack_668;
  int iStack_660;
  undefined8 uStack_658;
  undefined8 uStack_650;
  undefined4 uStack_648;
  undefined1 uStack_640;
  undefined8 uStack_638;
  undefined8 uStack_630;
  undefined4 uStack_628;
  undefined4 uStack_620;
  undefined8 uStack_618;
  undefined8 uStack_610;
  undefined4 uStack_608;
  undefined1 uStack_600;
  longlong lStack_5f8;
  int *piStack_5f0;
  undefined *puStack_5e8;
  int iStack_5e0;
  longlong alStack_5d8 [2];
  longlong alStack_5c8 [2];
  longlong alStack_5b8 [2];
  longlong alStack_5a8 [2];
  longlong alStack_598 [2];
  longlong alStack_588 [2];
  longlong alStack_578 [2];
  longlong alStack_568 [2];
  longlong alStack_558 [2];
  longlong alStack_548 [2];
  longlong alStack_538 [2];
  longlong alStack_528 [2];
  longlong alStack_518 [2];
  longlong alStack_508 [2];
  longlong alStack_4f8 [2];
  longlong alStack_4e8 [2];
  longlong alStack_4d8 [2];
  longlong alStack_4c8 [2];
  longlong alStack_4b8 [2];
  longlong alStack_4a8 [2];
  longlong alStack_498 [2];
  longlong alStack_488 [2];
  longlong alStack_478 [2];
  longlong alStack_468 [2];
  longlong alStack_458 [2];
  longlong alStack_448 [2];
  longlong alStack_438 [2];
  longlong alStack_428 [2];
  longlong alStack_418 [2];
  longlong alStack_408 [2];
  undefined4 *puStack_3f8;
  undefined1 auStack_3f0 [8];
  undefined1 auStack_3e8 [8];
  undefined1 auStack_3e0 [8];
  longlong *plStack_3d8;
  undefined1 auStack_3c8 [8];
  longlong *plStack_3c0;
  undefined1 auStack_3b0 [24];
  undefined1 auStack_398 [8];
  longlong *plStack_390;
  undefined1 auStack_380 [8];
  longlong *plStack_378;
  undefined1 auStack_368 [8];
  longlong *plStack_360;
  undefined1 auStack_350 [8];
  longlong *plStack_348;
  undefined1 auStack_338 [8];
  longlong *plStack_330;
  undefined1 auStack_320 [8];
  longlong *plStack_318;
  undefined1 auStack_308 [8];
  longlong *plStack_300;
  undefined1 auStack_2f0 [24];
  undefined1 auStack_2d8 [24];
  undefined1 auStack_2c0 [24];
  undefined1 auStack_2a8 [24];
  undefined1 auStack_290 [24];
  undefined1 auStack_278 [24];
  undefined1 auStack_260 [24];
  undefined1 auStack_248 [24];
  undefined1 auStack_230 [24];
  undefined1 auStack_218 [24];
  undefined1 auStack_200 [24];
  undefined1 auStack_1e8 [24];
  undefined1 auStack_1d0 [24];
  undefined1 auStack_1b8 [24];
  undefined1 auStack_1a0 [24];
  undefined1 auStack_188 [24];
  undefined1 auStack_170 [24];
  undefined1 auStack_158 [24];
  undefined1 auStack_140 [24];
  undefined1 auStack_128 [32];
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  ulonglong uStack_b8;
  
  uStack_b8 = _DAT_14ea60b28 ^ (ulonglong)auStack_9c8;
  *param_2 = 0;
  param_2[1] = 1;
  param_2[2] = 100;
  *(undefined8 *)(param_2 + 4) = 0;
  *(undefined8 *)(param_2 + 6) = 0;
  param_2[8] = 0;
  *(undefined8 *)(param_2 + 10) = 0;
  *(undefined8 *)(param_2 + 0xc) = 0;
  *(undefined8 *)(param_2 + 0xe) = 0;
  *(undefined8 *)(param_2 + 0x10) = 0;
  *(undefined8 *)(param_2 + 0x12) = 0;
  *(undefined8 *)(param_2 + 0x14) = 0;
  *(undefined8 *)(param_2 + 0x16) = 0;
  *(undefined8 *)(param_2 + 0x18) = 0;
  *(undefined8 *)(param_2 + 0x1a) = 0;
  *(undefined8 *)(param_2 + 0x1c) = 0;
  param_2[0x1e] = 0;
  *(undefined2 *)(param_2 + 0x1f) = 0;
  *(undefined8 *)(param_2 + 0x20) = 0;
  param_2[0x22] = 0;
  *(undefined8 *)(param_2 + 0x24) = 0;
  *(undefined8 *)(param_2 + 0x26) = 0;
  *(undefined8 *)(param_2 + 0x28) = 0;
  *(undefined8 *)(param_2 + 0x2a) = 0;
  *(undefined8 *)(param_2 + 0x2c) = 0;
  *(undefined8 *)(param_2 + 0x2e) = 0;
  *(undefined8 *)(param_2 + 0x30) = 0;
  param_2[0x32] = 0;
  *(undefined1 *)(param_2 + 0x34) = 0;
  param_2[0x35] = 0;
  param_2[0x36] = 1;
  uVar27 = 1;
  uStack_978 = 1;
  *param_2 = *(undefined4 *)(param_1 + 0x40);
  param_2[1] = *(undefined4 *)(param_1 + 0x50);
  lStack_5f8 = param_1;
  piStack_5f0 = param_3;
  puStack_3f8 = param_2;
  uVar19 = func_0x0001481c32e0();
  param_2[2] = uVar19;
  param_2[0xe] = *(undefined4 *)(param_1 + 0x58);
  func_0x0001481538d0(param_2 + 0x14,param_3);
  *(bool *)(param_2 + 0x34) = 0 < param_3[0xc];
  fVar9 = _DAT_14bcfdb28;
  fVar34 = _DAT_14bcef9ec;
  fVar35 = _DAT_14bcfdb28;
  if (0 < param_3[0xc]) {
    fVar35 = _DAT_14bcef9ec;
  }
  iVar30 = (int)ROUND(((float)param_3[10] * _DAT_14bcfdb20 + (float)param_3[10] * _DAT_14bcfdb20) -
                      _DAT_14bcfdb28) >> 1;
  fVar32 = (float)iVar30 * *(float *)(param_1 + 0x78) * fVar35;
  iVar24 = (int)ROUND((fVar32 + fVar32) - _DAT_14bcfdb28) >> 1;
  iStack_950 = iVar30;
  if (0 < iVar24) {
    func_0x000140e820a0(&uStack_7a0);
    iStack_788 = 0;
    func_0x000140e820a0(&uStack_780);
    func_0x000140cf7750(alStack_4b8,L"TIME PLAYED");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_2f0,alStack_4b8);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_7a0;
    puVar21[1] = uStack_798;
    uStack_790 = *(undefined4 *)(puVar21 + 2);
    uStack_7a0 = uVar4;
    uStack_798 = uVar6;
    func_0x000140e86d70(auStack_2f0);
    if (alStack_4b8[0] != 0) {
      func_0x000140e282f0();
    }
    iStack_788 = iVar24;
    func_0x000140d169d0(alStack_4a8,L"%d MIN",iVar30);
    uVar27 = 0x201;
    uStack_978 = 0x201;
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_260,alStack_4a8);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_780;
    puVar21[1] = uStack_778;
    uStack_770 = *(undefined4 *)(puVar21 + 2);
    uStack_780 = uVar4;
    uStack_778 = uVar6;
    func_0x000140e86d70(auStack_260);
    if (alStack_4a8[0] != 0) {
      func_0x000140e282f0();
    }
    piVar3 = *(int **)(param_2 + 4);
    if ((piVar3 <= &uStack_7a0) && (&uStack_7a0 < piVar3 + (longlong)(int)param_2[7] * 0xe)) {
      lStack_988 = (longlong)(int)param_2[6];
      puStack_980 = (undefined *)0x38;
      piStack_9a0 = (int *)&uStack_7a0;
      puStack_9a8 = &UNK_14bce6d80;
      piStack_998 = piVar3;
      lStack_990 = (longlong)(int)param_2[7];
      cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar24 = param_2[6];
    param_2[6] = iVar24 + 1U;
    if ((uint)param_2[7] < iVar24 + 1U) {
      func_0x0001481cab30(param_2 + 4,iVar24);
    }
    func_0x0001481b3040((longlong)iVar24 * 0x38 + *(longlong *)(param_2 + 4),&uStack_7a0);
    func_0x000148152600(&uStack_7a0);
  }
  fVar32 = (float)*param_3 * *(float *)(param_1 + 0x7c);
  if ((float)*(int *)(param_1 + 0x8c) <= fVar32) {
    fVar32 = (float)*(int *)(param_1 + 0x8c);
  }
  iVar24 = (int)ROUND((fVar32 * fVar35 + fVar32 * fVar35) - fVar9) >> 1;
  if (0 < iVar24) {
    func_0x000140e820a0(&uStack_888);
    iStack_870 = 0;
    func_0x000140e820a0(&uStack_868);
    func_0x000140cf7750(alStack_588,L"STROKES");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_248,alStack_588);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_888;
    puVar21[1] = uStack_880;
    uStack_878 = *(undefined4 *)(puVar21 + 2);
    uStack_888 = uVar4;
    uStack_880 = uVar6;
    func_0x000140e86d70(auStack_248);
    if (alStack_588[0] != 0) {
      func_0x000140e282f0();
    }
    iStack_870 = iVar24;
    if ((float)*param_3 * *(float *)(param_1 + 0x7c) < (float)*(int *)(param_1 + 0x8c)) {
      func_0x000140d169d0(alStack_488,L"%d STROKES");
      uVar27 = uVar27 | 0x1000;
      uStack_978 = uVar27;
      puVar21 = (undefined8 *)func_0x000140ebb430(auStack_218,alStack_488);
      uVar4 = *puVar21;
      uVar6 = puVar21[1];
      *puVar21 = uStack_868;
      puVar21[1] = uStack_860;
      uStack_858 = *(undefined4 *)(puVar21 + 2);
      uStack_868 = uVar4;
      uStack_860 = uVar6;
      func_0x000140e86d70(auStack_218);
      alStack_498[0] = alStack_488[0];
    }
    else {
      func_0x000140d169d0(alStack_498,L"%d STROKES (MAX)");
      uVar27 = uVar27 | 0x2000;
      uStack_978 = uVar27;
      puVar21 = (undefined8 *)func_0x000140ebb430(auStack_230,alStack_498);
      uVar4 = *puVar21;
      uVar6 = puVar21[1];
      *puVar21 = uStack_868;
      puVar21[1] = uStack_860;
      uStack_858 = *(undefined4 *)(puVar21 + 2);
      uStack_868 = uVar4;
      uStack_860 = uVar6;
      func_0x000140e86d70(auStack_230);
    }
    if (alStack_498[0] != 0) {
      func_0x000140e282f0();
    }
    piVar3 = *(int **)(param_2 + 4);
    if ((piVar3 <= &uStack_888) && (&uStack_888 < piVar3 + (longlong)(int)param_2[7] * 0xe)) {
      lStack_988 = (longlong)(int)param_2[6];
      puStack_980 = (undefined *)0x38;
      piStack_9a0 = (int *)&uStack_888;
      puStack_9a8 = &UNK_14bce6d80;
      piStack_998 = piVar3;
      lStack_990 = (longlong)(int)param_2[7];
      cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar24 = param_2[6];
    param_2[6] = iVar24 + 1U;
    if ((uint)param_2[7] < iVar24 + 1U) {
      func_0x0001481cab30(param_2 + 4,iVar24);
    }
    func_0x0001481b3040((longlong)iVar24 * 0x38 + *(longlong *)(param_2 + 4),&uStack_888);
    func_0x000148152600(&uStack_888);
  }
  iVar31 = 0;
  iVar30 = param_3[3] + param_3[2];
  iVar24 = *(int *)(param_1 + 0x90);
  if (iVar30 < *(int *)(param_1 + 0x90)) {
    iVar24 = iVar30;
  }
  iVar24 = (int)ROUND(((float)iVar24 * fVar35 + (float)iVar24 * fVar35) - fVar9) >> 1;
  if (0 < iVar24) {
    func_0x000140e820a0(&uStack_850);
    iStack_838 = 0;
    func_0x000140e820a0(&uStack_830);
    func_0x000140cf7750(alStack_478,L"ENEMIES");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_1e8,alStack_478);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_850;
    puVar21[1] = uStack_848;
    uStack_840 = *(undefined4 *)(puVar21 + 2);
    uStack_850 = uVar4;
    uStack_848 = uVar6;
    func_0x000140e86d70(auStack_1e8);
    if (alStack_478[0] != 0) {
      func_0x000140e282f0();
    }
    iStack_838 = iVar24;
    if (iVar30 < *(int *)(param_1 + 0x90)) {
      func_0x000140d169d0(alStack_448,L"%d DEFEATED",iVar30);
      uVar27 = uVar27 | 0x4000;
      uStack_978 = uVar27;
      puVar21 = (undefined8 *)func_0x000140ebb430(auStack_1b8,alStack_448);
      uVar4 = *puVar21;
      uVar6 = puVar21[1];
      *puVar21 = uStack_830;
      puVar21[1] = uStack_828;
      uStack_820 = *(undefined4 *)(puVar21 + 2);
      uStack_830 = uVar4;
      uStack_828 = uVar6;
      func_0x000140e86d70(auStack_1b8);
      alStack_458[0] = alStack_448[0];
    }
    else {
      func_0x000140d169d0(alStack_458,L"%d DEFEATED (MAX)",iVar30);
      uVar27 = uVar27 | 0x800;
      uStack_978 = uVar27;
      puVar21 = (undefined8 *)func_0x000140ebb430(auStack_1d0,alStack_458);
      uVar4 = *puVar21;
      uVar6 = puVar21[1];
      *puVar21 = uStack_830;
      puVar21[1] = uStack_828;
      uStack_820 = *(undefined4 *)(puVar21 + 2);
      uStack_830 = uVar4;
      uStack_828 = uVar6;
      func_0x000140e86d70(auStack_1d0);
    }
    if (alStack_458[0] != 0) {
      func_0x000140e282f0();
    }
    piVar3 = *(int **)(param_2 + 4);
    if ((piVar3 <= &uStack_850) && (&uStack_850 < piVar3 + (longlong)(int)param_2[7] * 0xe)) {
      lStack_988 = (longlong)(int)param_2[6];
      puStack_980 = (undefined *)0x38;
      piStack_9a0 = (int *)&uStack_850;
      puStack_9a8 = &UNK_14bce6d80;
      piStack_998 = piVar3;
      lStack_990 = (longlong)(int)param_2[7];
      cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar24 = param_2[6];
    param_2[6] = iVar24 + 1U;
    if ((uint)param_2[7] < iVar24 + 1U) {
      func_0x0001481cab30(param_2 + 4,iVar24);
    }
    func_0x0001481b3040((longlong)iVar24 * 0x38 + *(longlong *)(param_2 + 4),&uStack_850);
    func_0x000148152600(&uStack_850);
  }
  fVar32 = (float)param_3[1] * *(float *)(param_1 + 0x84) * fVar35;
  iVar24 = (int)ROUND((fVar32 + fVar32) - fVar9) >> 1;
  if (0 < iVar24) {
    func_0x000140e820a0(&uStack_768);
    iStack_750 = 0;
    func_0x000140e820a0(&uStack_748);
    func_0x000140cf7750(alStack_438,L"EDGES");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_1a0,alStack_438);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_768;
    puVar21[1] = uStack_760;
    uStack_758 = *(undefined4 *)(puVar21 + 2);
    uStack_768 = uVar4;
    uStack_760 = uVar6;
    func_0x000140e86d70(auStack_1a0);
    if (alStack_438[0] != 0) {
      func_0x000140e282f0();
    }
    iStack_750 = iVar24;
    func_0x000140d169d0(alStack_428,L"%d EDGES",param_3[1]);
    uStack_978 = uVar27 | 0x400;
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_188,alStack_428);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_748;
    puVar21[1] = uStack_740;
    uStack_738 = *(undefined4 *)(puVar21 + 2);
    uStack_748 = uVar4;
    uStack_740 = uVar6;
    func_0x000140e86d70(auStack_188);
    if (alStack_428[0] != 0) {
      func_0x000140e282f0();
    }
    piVar3 = *(int **)(param_2 + 4);
    if ((piVar3 <= &uStack_768) && (&uStack_768 < piVar3 + (longlong)(int)param_2[7] * 0xe)) {
      lStack_988 = (longlong)(int)param_2[6];
      puStack_980 = (undefined *)0x38;
      piStack_9a0 = (int *)&uStack_768;
      puStack_9a8 = &UNK_14bce6d80;
      piStack_998 = piVar3;
      lStack_990 = (longlong)(int)param_2[7];
      cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar24 = param_2[6];
    param_2[6] = iVar24 + 1U;
    if ((uint)param_2[7] < iVar24 + 1U) {
      func_0x0001481cab30(param_2 + 4,iVar24);
    }
    func_0x0001481b3040((longlong)iVar24 * 0x38 + *(longlong *)(param_2 + 4),&uStack_768);
    func_0x000148152600(&uStack_768);
  }
  if (0 < param_3[0xc]) {
    func_0x000140e820a0(&uStack_7d8);
    iStack_7c0 = 0;
    func_0x000140e820a0(&uStack_7b8);
    func_0x000140cf7750(alStack_418,L"VICTORY BONUS");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_170,alStack_418);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_7d8;
    puVar21[1] = uStack_7d0;
    uStack_7c8 = *(undefined4 *)(puVar21 + 2);
    uStack_7d8 = uVar4;
    uStack_7d0 = uVar6;
    func_0x000140e86d70(auStack_170);
    if (alStack_418[0] != 0) {
      func_0x000140e282f0();
    }
    iStack_7c0 = (int)*(float *)(param_1 + 0x88);
    func_0x000140cf7750(alStack_408,&UNK_14cf76c80);
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_158,alStack_408);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_7b8;
    puVar21[1] = uStack_7b0;
    uStack_7a8 = *(undefined4 *)(puVar21 + 2);
    uStack_7b8 = uVar4;
    uStack_7b0 = uVar6;
    func_0x000140e86d70(auStack_158);
    if (alStack_408[0] != 0) {
      func_0x000140e282f0();
    }
    piVar3 = *(int **)(param_2 + 4);
    if ((piVar3 <= &uStack_7d8) && (&uStack_7d8 < piVar3 + (longlong)(int)param_2[7] * 0xe)) {
      lStack_988 = (longlong)(int)param_2[6];
      puStack_980 = (undefined *)0x38;
      piStack_9a0 = (int *)&uStack_7d8;
      puStack_9a8 = &UNK_14bce6d80;
      piStack_998 = piVar3;
      lStack_990 = (longlong)(int)param_2[7];
      cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar24 = param_2[6];
    param_2[6] = iVar24 + 1U;
    if ((uint)param_2[7] < iVar24 + 1U) {
      func_0x0001481cab30(param_2 + 4,iVar24);
    }
    func_0x0001481b3040((longlong)iVar24 * 0x38 + *(longlong *)(param_2 + 4),&uStack_7d8);
    func_0x000148152600(&uStack_7d8);
  }
  lVar26 = *(longlong *)(param_2 + 4);
  iVar24 = param_2[6];
  lVar28 = (longlong)iVar24 * 0x38 + lVar26;
  while( true ) {
    if (param_2[6] != iVar24) {
      auStack_974[0] = 0;
      cVar18 = func_0x00014bc1d170(auStack_974);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    if (lVar26 == lVar28) break;
    iVar31 = iVar31 + *(int *)(lVar26 + 0x18);
    lVar26 = lVar26 + 0x38;
  }
  puVar21 = *(undefined8 **)(param_3 + 0x10);
  puVar29 = puVar21 + (longlong)param_3[0x12] * 2;
  for (; fVar32 = fVar34, puVar21 != puVar29; puVar21 = puVar21 + 2) {
    if (*(int *)(puVar21 + 1) == 0) {
      puVar23 = &UNK_14bce4e94;
    }
    else {
      puVar23 = (undefined *)*puVar21;
    }
    iVar24 = func_0x000140d80770(puVar23,L"ironman");
    fVar32 = _DAT_14bd17818;
    if (iVar24 == 0) break;
  }
  puVar21 = *(undefined8 **)(param_3 + 0x10);
  puVar29 = puVar21 + (longlong)param_3[0x12] * 2;
  for (; puVar21 != puVar29; puVar21 = puVar21 + 2) {
    if (*(int *)(puVar21 + 1) == 0) {
      puVar23 = &UNK_14bce4e94;
    }
    else {
      puVar23 = (undefined *)*puVar21;
    }
    iVar24 = func_0x000140d80770(puVar23,L"hardcore");
    if (iVar24 == 0) {
      fVar32 = fVar32 + _DAT_14bd774a8;
      break;
    }
  }
  if (fVar34 < fVar32) {
    fVar33 = (float)iVar31 * (fVar32 - fVar34);
    iVar24 = (int)ROUND((fVar33 + fVar33) - fVar9) >> 1;
    if (0 < iVar24) {
      func_0x000140e820a0(&uStack_730);
      iStack_718 = 0;
      func_0x000140e820a0(&uStack_710);
      func_0x000140cf7750(alStack_5d8,L"MODIFIER BONUS");
      puVar21 = (undefined8 *)func_0x000140ebb430(auStack_140,alStack_5d8);
      uVar4 = *puVar21;
      uVar6 = puVar21[1];
      *puVar21 = uStack_730;
      puVar21[1] = uStack_728;
      uStack_720 = *(undefined4 *)(puVar21 + 2);
      uStack_730 = uVar4;
      uStack_728 = uVar6;
      func_0x000140e86d70(auStack_140);
      if (alStack_5d8[0] != 0) {
        func_0x000140e282f0();
      }
      fVar34 = (fVar32 - fVar34) * _DAT_14bd1786c;
      iStack_718 = iVar24;
      func_0x000140d169d0(alStack_5c8,L"+%d%%",(int)ROUND((fVar34 + fVar34) - fVar9) >> 1);
      uStack_978 = uStack_978 | 0x100;
      puVar21 = (undefined8 *)func_0x000140ebb430(auStack_128,alStack_5c8);
      uVar4 = *puVar21;
      uVar6 = puVar21[1];
      *puVar21 = uStack_710;
      puVar21[1] = uStack_708;
      uStack_700 = *(undefined4 *)(puVar21 + 2);
      uStack_710 = uVar4;
      uStack_708 = uVar6;
      func_0x000140e86d70(auStack_128);
      if (alStack_5c8[0] != 0) {
        func_0x000140e282f0();
      }
      piVar3 = *(int **)(param_2 + 4);
      if ((piVar3 <= &uStack_730) && (&uStack_730 < piVar3 + (longlong)(int)param_2[7] * 0xe)) {
        lStack_988 = (longlong)(int)param_2[6];
        puStack_980 = (undefined *)0x38;
        piStack_9a0 = (int *)&uStack_730;
        puStack_9a8 = &UNK_14bce6d80;
        piStack_998 = piVar3;
        lStack_990 = (longlong)(int)param_2[7];
        cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
        if (cVar18 != '\0') {
          pcVar5 = (code *)swi(3);
          (*pcVar5)();
          return;
        }
      }
      iVar24 = param_2[6];
      param_2[6] = iVar24 + 1U;
      if ((uint)param_2[7] < iVar24 + 1U) {
        func_0x0001481cab30(param_2 + 4,iVar24);
      }
      func_0x0001481b3040((longlong)iVar24 * 0x38 + *(longlong *)(param_2 + 4),&uStack_730);
      func_0x000148152600(&uStack_730);
    }
  }
  iStack_970 = (int)ROUND(((float)iVar31 * fVar32 + (float)iVar31 * fVar32) - fVar9) >> 1;
  param_2[8] = iStack_970;
  iStack_970 = *(int *)(param_1 + 0x40) + iStack_970;
  iVar24 = *(int *)(param_1 + 0x50);
  if (iVar24 < 0x14) {
    lVar26 = *(longlong *)(unaff_GS_OFFSET + 0x58);
    uVar27 = iVar24 - 1;
    do {
      iVar30 = iStack_970;
      if ((*(int *)(*(longlong *)(lVar26 + (ulonglong)_DAT_14ee952f8 * 8) + 0x908c) < _DAT_14edbff0c
          ) && (func_0x00014b87ff78(&DAT_14edbff0c), uVar17 = _UNK_14cf778b8,
               uVar16 = _DAT_14cf778b0, uVar15 = _UNK_14cf778a8, uVar14 = _DAT_14cf778a0,
               uVar13 = _UNK_14cf77898, uVar12 = _DAT_14cf77890, uVar11 = _UNK_14cf77888,
               uVar10 = _DAT_14cf77880, uVar6 = _UNK_14cf77878, uVar4 = _DAT_14cf77870,
               _DAT_14edbff0c == -1)) {
        _DAT_14e9f1210 = (undefined8 *)0x0;
        _DAT_14e9f1218 = 0x14;
        func_0x000140d20ea0(&DAT_14e9f1210,0x14);
        puVar21 = _DAT_14e9f1210;
        uStack_108 = uVar4;
        uStack_100 = uVar6;
        *_DAT_14e9f1210 = uVar4;
        puVar21[1] = uVar6;
        uStack_f8 = uVar10;
        uStack_f0 = uVar11;
        puVar21[2] = uVar10;
        puVar21[3] = uVar11;
        uStack_e8 = uVar12;
        uStack_e0 = uVar13;
        puVar21[4] = uVar12;
        puVar21[5] = uVar13;
        uStack_d8 = uVar14;
        uStack_d0 = uVar15;
        puVar21[6] = uVar14;
        puVar21[7] = uVar15;
        uStack_c8 = uVar16;
        uStack_c0 = uVar17;
        puVar21[8] = uVar16;
        puVar21[9] = uVar17;
        func_0x00014b87fc50(0x14ba6bd50);
        func_0x00014b87ff10(&DAT_14edbff0c);
      }
      if ((iVar24 < 1) || (_DAT_14e9f1218 < iVar24)) {
        iVar31 = 999999;
      }
      else {
        uVar20 = _DAT_14e9f1218 - 1U;
        if ((int)uVar27 < (int)(_DAT_14e9f1218 - 1U)) {
          uVar20 = uVar27;
        }
        uVar25 = 0;
        if (0 < (int)uVar20) {
          uVar25 = uVar20;
        }
        uVar20 = 0;
        if ((int)uVar25 < _DAT_14e9f1218) {
          uVar20 = ~uVar25 >> 0x1f;
        }
        if (uVar20 == 0) {
          piStack_9a0 = (int *)(longlong)(int)uVar25;
          puStack_9a8 = &UNK_14bce6ef0;
          piStack_998 = (int *)(longlong)_DAT_14e9f1218;
          cVar18 = func_0x000140f8dfd0(&UNK_14bce6f68,&UNK_14cf27ac0,0x303,unaff_retaddr);
          if (cVar18 != '\0') {
            pcVar5 = (code *)swi(3);
            (*pcVar5)();
            return;
          }
        }
        iVar31 = *(int *)((longlong)_DAT_14e9f1210 + (longlong)(int)uVar25 * 4);
      }
      lVar26 = lStack_5f8;
      param_3 = piStack_5f0;
      if (iVar30 < iVar31) break;
      iStack_970 = iVar30 - iVar31;
      iVar24 = iVar24 + 1;
      uVar27 = uVar27 + 1;
      uStack_964 = 0;
      uStack_960 = 0;
      uStack_95c = 0;
      iStack_968 = iVar24;
      iStack_958 = iVar31;
      puVar21 = (undefined8 *)func_0x0001481c3000(lStack_5f8,auStack_3e8,iVar24);
      uStack_964 = (undefined4)*puVar21;
      uStack_960 = (undefined4)((ulonglong)*puVar21 >> 0x20);
      if (*(longlong *)(lVar26 + 0x68) != 0) {
        func_0x000140d169d0(&puStack_5e8,L"Level_%d",iVar24);
        uStack_978 = uStack_978 | 2;
        uVar4 = *(undefined8 *)(lVar26 + 0x68);
        puVar23 = &UNK_14bce4e94;
        if (iStack_5e0 != 0) {
          puVar23 = puStack_5e8;
        }
        puVar21 = (undefined8 *)func_0x0001411a7b80(auStack_3f0,puVar23,1);
        lVar26 = func_0x0001481b14e0(uVar4,*puVar21,&UNK_14bce4e94,1);
        if ((lVar26 != 0) &&
           (uStack_95c = *(undefined4 *)(lVar26 + 0x10), 0 < *(int *)(lVar26 + 0x10))) {
          func_0x000140e820a0(&uStack_948);
          uStack_930 = 0;
          func_0x000140e820a0(&uStack_928);
          uStack_910 = 0;
          func_0x000140cf7750(alStack_5b8,L"LEVEL UP");
          puVar21 = (undefined8 *)func_0x000140ebb430(auStack_3e0,alStack_5b8);
          plVar1 = plStack_3d8;
          uVar4 = *puVar21;
          plVar7 = (longlong *)puVar21[1];
          *puVar21 = uStack_948;
          puVar21[1] = plStack_940;
          uStack_938 = *(undefined4 *)(puVar21 + 2);
          uStack_948 = uVar4;
          plStack_940 = plVar7;
          if (plStack_3d8 != (longlong *)0x0) {
            LOCK();
            plVar7 = plStack_3d8 + 1;
            lVar28 = *plVar7;
            *(int *)plVar7 = (int)*plVar7 + -1;
            UNLOCK();
            if ((int)lVar28 == 1) {
              (**(code **)*plStack_3d8)(plStack_3d8);
              LOCK();
              piVar3 = (int *)((longlong)plVar1 + 0xc);
              iVar30 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar30 == 1) {
                (**(code **)(*plVar1 + 8))(plVar1,1);
              }
            }
          }
          if (alStack_5b8[0] != 0) {
            func_0x000140e282f0();
          }
          uStack_930 = *(undefined4 *)(lVar26 + 0x10);
          func_0x000140d169d0(alStack_5a8,L"LVL %d",iVar24);
          uStack_978 = uStack_978 | 4;
          pauVar22 = (undefined1 (*) [16])func_0x000140ebb430(auStack_3c8,alStack_5a8);
          plVar7 = plStack_3c0;
          auVar8._8_8_ = plStack_920;
          auVar8._0_8_ = uStack_928;
          uStack_928 = *(undefined8 *)*pauVar22;
          plStack_920 = *(longlong **)(*pauVar22 + 8);
          *pauVar22 = auVar8;
          uStack_918 = *(undefined4 *)pauVar22[1];
          if (plStack_3c0 != (longlong *)0x0) {
            LOCK();
            plVar1 = plStack_3c0 + 1;
            lVar28 = *plVar1;
            *(int *)plVar1 = (int)*plVar1 + -1;
            UNLOCK();
            if ((int)lVar28 == 1) {
              (**(code **)*plStack_3c0)(plStack_3c0);
              LOCK();
              piVar3 = (int *)((longlong)plVar7 + 0xc);
              iVar30 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar30 == 1) {
                (**(code **)(*plVar7 + 8))(plVar7,1);
              }
            }
          }
          if (alStack_5a8[0] != 0) {
            func_0x000140e282f0();
          }
          uStack_910 = 1;
          piVar3 = *(int **)(param_2 + 10);
          if ((piVar3 <= &uStack_948) && (&uStack_948 < piVar3 + (longlong)(int)param_2[0xd] * 0x10)
             ) {
            lStack_988 = (longlong)(int)param_2[0xc];
            puStack_980 = (undefined *)0x40;
            piStack_9a0 = (int *)&uStack_948;
            puStack_9a8 = &UNK_14bce6d80;
            piStack_998 = piVar3;
            lStack_990 = (longlong)(int)param_2[0xd];
            cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
            if (cVar18 != '\0') {
              pcVar5 = (code *)swi(3);
              (*pcVar5)();
              return;
            }
          }
          iVar30 = param_2[0xc];
          param_2[0xc] = iVar30 + 1U;
          if ((uint)param_2[0xd] < iVar30 + 1U) {
            func_0x0001481caa90(param_2 + 10,iVar30);
          }
          plVar7 = plStack_920;
          puVar21 = (undefined8 *)((longlong)iVar30 * 0x40 + *(longlong *)(param_2 + 10));
          *puVar21 = uStack_948;
          puVar21[1] = plStack_940;
          if (plStack_940 != (longlong *)0x0) {
            LOCK();
            *(int *)(plStack_940 + 1) = (int)plStack_940[1] + 1;
            UNLOCK();
          }
          *(undefined4 *)(puVar21 + 2) = uStack_938;
          *(undefined4 *)(puVar21 + 3) = uStack_930;
          puVar21[4] = uStack_928;
          puVar21[5] = plStack_920;
          if (plStack_920 != (longlong *)0x0) {
            LOCK();
            *(int *)(plStack_920 + 1) = (int)plStack_920[1] + 1;
            UNLOCK();
          }
          *(undefined4 *)(puVar21 + 6) = uStack_918;
          *(undefined1 *)(puVar21 + 7) = uStack_910;
          param_2[0xf] = param_2[0xf] + *(int *)(lVar26 + 0x10);
          if (plStack_920 != (longlong *)0x0) {
            LOCK();
            plVar1 = plStack_920 + 1;
            lVar26 = *plVar1;
            *(int *)plVar1 = (int)*plVar1 + -1;
            UNLOCK();
            if ((int)lVar26 == 1) {
              (**(code **)*plStack_920)(plStack_920);
              LOCK();
              piVar3 = (int *)((longlong)plVar7 + 0xc);
              iVar30 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar30 == 1) {
                (**(code **)(*plVar7 + 8))(plVar7,1);
              }
            }
          }
          plVar7 = plStack_940;
          if (plStack_940 != (longlong *)0x0) {
            LOCK();
            plVar1 = plStack_940 + 1;
            lVar26 = *plVar1;
            *(int *)plVar1 = (int)*plVar1 + -1;
            UNLOCK();
            if ((int)lVar26 == 1) {
              (**(code **)*plStack_940)(plStack_940);
              LOCK();
              piVar3 = (int *)((longlong)plVar7 + 0xc);
              iVar30 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar30 == 1) {
                (**(code **)(*plVar7 + 8))(plVar7,1);
              }
            }
          }
        }
        if (puStack_5e8 != (undefined *)0x0) {
          func_0x000140e282f0();
        }
      }
      piVar3 = *(int **)(param_2 + 0x10);
      if ((piVar3 <= &iStack_968) && (&iStack_968 < piVar3 + (longlong)(int)param_2[0x13] * 5)) {
        lStack_988 = (longlong)(int)param_2[0x12];
        puStack_980 = (undefined *)0x14;
        piStack_9a0 = &iStack_968;
        puStack_9a8 = &UNK_14bce6d80;
        piStack_998 = piVar3;
        lStack_990 = (longlong)(int)param_2[0x13];
        cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
        if (cVar18 != '\0') {
          pcVar5 = (code *)swi(3);
          (*pcVar5)();
          return;
        }
      }
      iVar30 = param_2[0x12];
      param_2[0x12] = iVar30 + 1U;
      if ((uint)param_2[0x13] < iVar30 + 1U) {
        func_0x0001481ca890(param_2 + 0x10,iVar30);
      }
      lVar26 = *(longlong *)(param_2 + 0x10);
      puVar21 = (undefined8 *)(lVar26 + (longlong)iVar30 * 0x14);
      *puVar21 = CONCAT44(uStack_964,iStack_968);
      puVar21[1] = CONCAT44(uStack_95c,uStack_960);
      *(int *)(lVar26 + 0x10 + (longlong)iVar30 * 0x14) = iStack_958;
      lVar26 = *(longlong *)(unaff_GS_OFFSET + 0x58);
      param_3 = piStack_5f0;
    } while ((int)uVar27 < 0x13);
  }
  fVar34 = (float)(*param_3 / 300) * fVar35;
  iVar30 = (int)ROUND((fVar34 + fVar34) - fVar9) >> 1;
  if (0 < iVar30) {
    func_0x000140e820a0(&uStack_6f8);
    iStack_6e0 = 0;
    func_0x000140e820a0(&uStack_6d8);
    uStack_6c0 = 0;
    func_0x000140cf7750(alStack_598,L"STROKES");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_3b0,alStack_598);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_6f8;
    puVar21[1] = uStack_6f0;
    uStack_6e8 = *(undefined4 *)(puVar21 + 2);
    uStack_6f8 = uVar4;
    uStack_6f0 = uVar6;
    func_0x000140e86d70(auStack_3b0);
    if (alStack_598[0] != 0) {
      func_0x000140e282f0();
    }
    iStack_6e0 = iVar30;
    func_0x000140d169d0(alStack_468,L"%d STROKES",*param_3);
    uStack_978 = uStack_978 | 0x80;
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_398,alStack_468);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_6d8;
    puVar21[1] = uStack_6d0;
    uStack_6c8 = *(undefined4 *)(puVar21 + 2);
    uStack_6d8 = uVar4;
    uStack_6d0 = uVar6;
    if (plStack_390 != (longlong *)0x0) {
      LOCK();
      plVar7 = plStack_390 + 1;
      lVar26 = *plVar7;
      *(int *)plVar7 = (int)*plVar7 + -1;
      UNLOCK();
      if ((int)lVar26 == 1) {
        (**(code **)*plStack_390)(plStack_390);
        LOCK();
        piVar3 = (int *)((longlong)plStack_390 + 0xc);
        iVar31 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar31 == 1) {
          (**(code **)(*plStack_390 + 8))(plStack_390,1);
        }
      }
    }
    if (alStack_468[0] != 0) {
      func_0x000140e282f0();
    }
    uStack_6c0 = 0;
    piVar3 = *(int **)(param_2 + 10);
    if ((piVar3 <= &uStack_6f8) && (&uStack_6f8 < piVar3 + (longlong)(int)param_2[0xd] * 0x10)) {
      lStack_988 = (longlong)(int)param_2[0xc];
      puStack_980 = (undefined *)0x40;
      piStack_9a0 = (int *)&uStack_6f8;
      puStack_9a8 = &UNK_14bce6d80;
      piStack_998 = piVar3;
      lStack_990 = (longlong)(int)param_2[0xd];
      cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar31 = param_2[0xc];
    param_2[0xc] = iVar31 + 1U;
    if ((uint)param_2[0xd] < iVar31 + 1U) {
      func_0x0001481caa90(param_2 + 10,iVar31);
    }
    func_0x0001481b2fe0((longlong)iVar31 * 0x40 + *(longlong *)(param_2 + 10),&uStack_6f8);
    param_2[0xf] = param_2[0xf] + iVar30;
    func_0x000148152560(&uStack_6f8);
  }
  fVar34 = (float)(param_3[4] / 400) * fVar35;
  iVar30 = (int)ROUND((fVar34 + fVar34) - fVar9) >> 1;
  if (0 < iVar30) {
    func_0x000140e820a0(&uStack_908);
    iStack_8f0 = 0;
    func_0x000140e820a0(&uStack_8e8);
    uStack_8d0 = 0;
    func_0x000140cf7750(alStack_578,L"MAX COMBO");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_380,alStack_578);
    uVar4 = *puVar21;
    plVar7 = (longlong *)puVar21[1];
    *puVar21 = uStack_908;
    puVar21[1] = plStack_900;
    uStack_8f8 = *(undefined4 *)(puVar21 + 2);
    uStack_908 = uVar4;
    plStack_900 = plVar7;
    if (plStack_378 != (longlong *)0x0) {
      LOCK();
      plVar7 = plStack_378 + 1;
      lVar26 = *plVar7;
      *(int *)plVar7 = (int)*plVar7 + -1;
      UNLOCK();
      if ((int)lVar26 == 1) {
        (**(code **)*plStack_378)(plStack_378);
        LOCK();
        piVar3 = (int *)((longlong)plStack_378 + 0xc);
        iVar31 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar31 == 1) {
          (**(code **)(*plStack_378 + 8))(plStack_378,1);
        }
      }
    }
    if (alStack_578[0] != 0) {
      func_0x000140e282f0();
    }
    iStack_8f0 = iVar30;
    func_0x000140d169d0(alStack_568,L"%d COMBO",param_3[4]);
    uStack_978 = uStack_978 | 8;
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_368,alStack_568);
    uVar4 = *puVar21;
    plVar7 = (longlong *)puVar21[1];
    *puVar21 = uStack_8e8;
    puVar21[1] = plStack_8e0;
    uStack_8d8 = *(undefined4 *)(puVar21 + 2);
    uStack_8e8 = uVar4;
    plStack_8e0 = plVar7;
    if (plStack_360 != (longlong *)0x0) {
      LOCK();
      plVar7 = plStack_360 + 1;
      lVar26 = *plVar7;
      *(int *)plVar7 = (int)*plVar7 + -1;
      UNLOCK();
      if ((int)lVar26 == 1) {
        (**(code **)*plStack_360)(plStack_360);
        LOCK();
        piVar3 = (int *)((longlong)plStack_360 + 0xc);
        iVar31 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar31 == 1) {
          (**(code **)(*plStack_360 + 8))(plStack_360,1);
        }
      }
    }
    if (alStack_568[0] != 0) {
      func_0x000140e282f0();
    }
    uStack_8d0 = 0;
    piVar3 = *(int **)(param_2 + 10);
    if ((piVar3 <= &uStack_908) && (&uStack_908 < piVar3 + (longlong)(int)param_2[0xd] * 0x10)) {
      lStack_988 = (longlong)(int)param_2[0xc];
      puStack_980 = (undefined *)0x40;
      piStack_9a0 = (int *)&uStack_908;
      puStack_9a8 = &UNK_14bce6d80;
      piStack_998 = piVar3;
      lStack_990 = (longlong)(int)param_2[0xd];
      cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar31 = param_2[0xc];
    param_2[0xc] = iVar31 + 1U;
    if ((uint)param_2[0xd] < iVar31 + 1U) {
      func_0x0001481caa90(param_2 + 10,iVar31);
    }
    plVar7 = plStack_8e0;
    puVar21 = (undefined8 *)((longlong)iVar31 * 0x40 + *(longlong *)(param_2 + 10));
    *puVar21 = uStack_908;
    puVar21[1] = plStack_900;
    if (plStack_900 != (longlong *)0x0) {
      LOCK();
      *(int *)(plStack_900 + 1) = (int)plStack_900[1] + 1;
      UNLOCK();
    }
    *(undefined4 *)(puVar21 + 2) = uStack_8f8;
    *(int *)(puVar21 + 3) = iStack_8f0;
    puVar21[4] = uStack_8e8;
    puVar21[5] = plStack_8e0;
    if (plStack_8e0 != (longlong *)0x0) {
      LOCK();
      *(int *)(plStack_8e0 + 1) = (int)plStack_8e0[1] + 1;
      UNLOCK();
    }
    *(undefined4 *)(puVar21 + 6) = uStack_8d8;
    *(undefined1 *)(puVar21 + 7) = uStack_8d0;
    param_2[0xf] = param_2[0xf] + iVar30;
    if (plStack_8e0 != (longlong *)0x0) {
      LOCK();
      plVar1 = plStack_8e0 + 1;
      lVar26 = *plVar1;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)lVar26 == 1) {
        (**(code **)*plStack_8e0)(plStack_8e0);
        LOCK();
        piVar3 = (int *)((longlong)plVar7 + 0xc);
        iVar30 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar30 == 1) {
          (**(code **)(*plVar7 + 8))(plVar7,1);
        }
      }
    }
    plVar7 = plStack_900;
    if (plStack_900 != (longlong *)0x0) {
      LOCK();
      plVar1 = plStack_900 + 1;
      lVar26 = *plVar1;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)lVar26 == 1) {
        (**(code **)*plStack_900)(plStack_900);
        LOCK();
        piVar3 = (int *)((longlong)plVar7 + 0xc);
        iVar30 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar30 == 1) {
          (**(code **)(*plVar7 + 8))(plVar7,1);
        }
      }
    }
  }
  fVar34 = (float)(param_3[1] / 2) * fVar35;
  iVar30 = (int)ROUND((fVar34 + fVar34) - fVar9) >> 1;
  if (0 < iVar30) {
    func_0x000140e820a0(&uStack_8c8);
    iStack_8b0 = 0;
    func_0x000140e820a0(&uStack_8a8);
    uStack_890 = 0;
    func_0x000140cf7750(alStack_558,L"EDGES");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_350,alStack_558);
    uVar4 = *puVar21;
    plVar7 = (longlong *)puVar21[1];
    *puVar21 = uStack_8c8;
    puVar21[1] = plStack_8c0;
    uStack_8b8 = *(undefined4 *)(puVar21 + 2);
    uStack_8c8 = uVar4;
    plStack_8c0 = plVar7;
    if (plStack_348 != (longlong *)0x0) {
      LOCK();
      plVar7 = plStack_348 + 1;
      lVar26 = *plVar7;
      *(int *)plVar7 = (int)*plVar7 + -1;
      UNLOCK();
      if ((int)lVar26 == 1) {
        (**(code **)*plStack_348)(plStack_348);
        LOCK();
        piVar3 = (int *)((longlong)plStack_348 + 0xc);
        iVar31 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar31 == 1) {
          (**(code **)(*plStack_348 + 8))(plStack_348,1);
        }
      }
    }
    if (alStack_558[0] != 0) {
      func_0x000140e282f0();
    }
    iStack_8b0 = iVar30;
    func_0x000140d169d0(alStack_548,L"%d EDGES",param_3[1]);
    uStack_978 = uStack_978 | 0x10;
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_338,alStack_548);
    uVar4 = *puVar21;
    plVar7 = (longlong *)puVar21[1];
    *puVar21 = uStack_8a8;
    puVar21[1] = plStack_8a0;
    uStack_898 = *(undefined4 *)(puVar21 + 2);
    uStack_8a8 = uVar4;
    plStack_8a0 = plVar7;
    if (plStack_330 != (longlong *)0x0) {
      LOCK();
      plVar7 = plStack_330 + 1;
      lVar26 = *plVar7;
      *(int *)plVar7 = (int)*plVar7 + -1;
      UNLOCK();
      if ((int)lVar26 == 1) {
        (**(code **)*plStack_330)(plStack_330);
        LOCK();
        piVar3 = (int *)((longlong)plStack_330 + 0xc);
        iVar31 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar31 == 1) {
          (**(code **)(*plStack_330 + 8))(plStack_330,1);
        }
      }
    }
    if (alStack_548[0] != 0) {
      func_0x000140e282f0();
    }
    uStack_890 = 0;
    piVar3 = *(int **)(param_2 + 10);
    if ((piVar3 <= &uStack_8c8) && (&uStack_8c8 < piVar3 + (longlong)(int)param_2[0xd] * 0x10)) {
      lStack_988 = (longlong)(int)param_2[0xc];
      puStack_980 = (undefined *)0x40;
      puStack_9a8 = &UNK_14bce6d80;
      piStack_9a0 = (int *)&uStack_8c8;
      piStack_998 = piVar3;
      lStack_990 = (longlong)(int)param_2[0xd];
      cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar31 = param_2[0xc];
    param_2[0xc] = iVar31 + 1U;
    if ((uint)param_2[0xd] < iVar31 + 1U) {
      func_0x0001481caa90(param_2 + 10,iVar31);
    }
    plVar7 = plStack_8a0;
    puVar21 = (undefined8 *)((longlong)iVar31 * 0x40 + *(longlong *)(param_2 + 10));
    *puVar21 = uStack_8c8;
    puVar21[1] = plStack_8c0;
    if (plStack_8c0 != (longlong *)0x0) {
      LOCK();
      *(int *)(plStack_8c0 + 1) = (int)plStack_8c0[1] + 1;
      UNLOCK();
    }
    *(undefined4 *)(puVar21 + 2) = uStack_8b8;
    *(int *)(puVar21 + 3) = iStack_8b0;
    puVar21[4] = uStack_8a8;
    puVar21[5] = plStack_8a0;
    if (plStack_8a0 != (longlong *)0x0) {
      LOCK();
      *(int *)(plStack_8a0 + 1) = (int)plStack_8a0[1] + 1;
      UNLOCK();
    }
    *(undefined4 *)(puVar21 + 6) = uStack_898;
    *(undefined1 *)(puVar21 + 7) = uStack_890;
    param_2[0xf] = param_2[0xf] + iVar30;
    if (plStack_8a0 != (longlong *)0x0) {
      LOCK();
      plVar1 = plStack_8a0 + 1;
      lVar26 = *plVar1;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)lVar26 == 1) {
        (**(code **)*plStack_8a0)(plStack_8a0);
        LOCK();
        piVar3 = (int *)((longlong)plVar7 + 0xc);
        iVar30 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar30 == 1) {
          (**(code **)(*plVar7 + 8))(plVar7,1);
        }
      }
    }
    plVar7 = plStack_8c0;
    if (plStack_8c0 != (longlong *)0x0) {
      LOCK();
      plVar1 = plStack_8c0 + 1;
      lVar26 = *plVar1;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)lVar26 == 1) {
        (**(code **)*plStack_8c0)(plStack_8c0);
        LOCK();
        piVar3 = (int *)((longlong)plVar7 + 0xc);
        iVar30 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar30 == 1) {
          (**(code **)(*plVar7 + 8))(plVar7,1);
        }
      }
    }
  }
  iVar30 = iStack_950;
  fVar34 = (float)(iStack_950 / 3 + (iStack_950 >> 0x1f) +
                  (int)(((longlong)iStack_950 / 3 + ((longlong)iStack_950 >> 0x3f) & 0xffffffffU) >>
                       0x1f)) * fVar35;
  iVar31 = (int)ROUND((fVar34 + fVar34) - fVar9) >> 1;
  if (0 < iVar31) {
    func_0x000140e820a0(&uStack_6b8);
    iStack_6a0 = 0;
    func_0x000140e820a0(&uStack_698);
    uStack_680 = 0;
    func_0x000140cf7750(alStack_538,L"TIME PLAYED");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_320,alStack_538);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_6b8;
    puVar21[1] = uStack_6b0;
    uStack_6a8 = *(undefined4 *)(puVar21 + 2);
    uStack_6b8 = uVar4;
    uStack_6b0 = uVar6;
    if (plStack_318 != (longlong *)0x0) {
      LOCK();
      plVar7 = plStack_318 + 1;
      lVar26 = *plVar7;
      *(int *)plVar7 = (int)*plVar7 + -1;
      UNLOCK();
      if ((int)lVar26 == 1) {
        (**(code **)*plStack_318)(plStack_318);
        LOCK();
        piVar3 = (int *)((longlong)plStack_318 + 0xc);
        iVar2 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar2 == 1) {
          (**(code **)(*plStack_318 + 8))(plStack_318,1);
        }
      }
    }
    if (alStack_538[0] != 0) {
      func_0x000140e282f0();
    }
    iStack_6a0 = iVar31;
    func_0x000140d169d0(alStack_528,L"%d MIN",iVar30);
    uStack_978 = uStack_978 | 0x20;
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_308,alStack_528);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_698;
    puVar21[1] = uStack_690;
    uStack_688 = *(undefined4 *)(puVar21 + 2);
    uStack_698 = uVar4;
    uStack_690 = uVar6;
    if (plStack_300 != (longlong *)0x0) {
      LOCK();
      plVar7 = plStack_300 + 1;
      lVar26 = *plVar7;
      *(int *)plVar7 = (int)*plVar7 + -1;
      UNLOCK();
      if ((int)lVar26 == 1) {
        (**(code **)*plStack_300)(plStack_300);
        LOCK();
        piVar3 = (int *)((longlong)plStack_300 + 0xc);
        iVar30 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar30 == 1) {
          (**(code **)(*plStack_300 + 8))(plStack_300,1);
        }
      }
    }
    if (alStack_528[0] != 0) {
      func_0x000140e282f0();
    }
    uStack_680 = 0;
    piVar3 = *(int **)(param_2 + 10);
    if ((piVar3 <= &uStack_6b8) && (&uStack_6b8 < piVar3 + (longlong)(int)param_2[0xd] * 0x10)) {
      lStack_988 = (longlong)(int)param_2[0xc];
      puStack_980 = (undefined *)0x40;
      piStack_9a0 = (int *)&uStack_6b8;
      puStack_9a8 = &UNK_14bce6d80;
      piStack_998 = piVar3;
      lStack_990 = (longlong)(int)param_2[0xd];
      cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar30 = param_2[0xc];
    param_2[0xc] = iVar30 + 1U;
    if ((uint)param_2[0xd] < iVar30 + 1U) {
      func_0x0001481caa90(param_2 + 10,iVar30);
    }
    func_0x0001481b2fe0((longlong)iVar30 * 0x40 + *(longlong *)(param_2 + 10),&uStack_6b8);
    param_2[0xf] = param_2[0xf] + iVar31;
    func_0x000148152560(&uStack_6b8);
  }
  fVar34 = (float)(param_3[8] / 10) * fVar35;
  iVar30 = (int)ROUND((fVar34 + fVar34) - fVar9) >> 1;
  if (0 < iVar30) {
    func_0x000140e820a0(&uStack_678);
    iStack_660 = 0;
    func_0x000140e820a0(&uStack_658);
    uStack_640 = 0;
    func_0x000140cf7750(alStack_518,L"MAX HEAT DRAWS");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_200,alStack_518);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_678;
    puVar21[1] = uStack_670;
    uStack_668 = *(undefined4 *)(puVar21 + 2);
    uStack_678 = uVar4;
    uStack_670 = uVar6;
    func_0x000140e86d70(auStack_200);
    if (alStack_518[0] != 0) {
      func_0x000140e282f0();
    }
    iStack_660 = iVar30;
    func_0x000140d169d0(alStack_508,L"%d DRAWS",param_3[8]);
    uStack_978 = uStack_978 | 0x40;
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_2d8,alStack_508);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_658;
    puVar21[1] = uStack_650;
    uStack_648 = *(undefined4 *)(puVar21 + 2);
    uStack_658 = uVar4;
    uStack_650 = uVar6;
    func_0x000140e86d70(auStack_2d8);
    if (alStack_508[0] != 0) {
      func_0x000140e282f0();
    }
    uStack_640 = 0;
    piVar3 = *(int **)(param_2 + 10);
    if ((piVar3 <= &uStack_678) && (&uStack_678 < piVar3 + (longlong)(int)param_2[0xd] * 0x10)) {
      lStack_988 = (longlong)(int)param_2[0xc];
      puStack_980 = (undefined *)0x40;
      piStack_9a0 = (int *)&uStack_678;
      puStack_9a8 = &UNK_14bce6d80;
      piStack_998 = piVar3;
      lStack_990 = (longlong)(int)param_2[0xd];
      cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar31 = param_2[0xc];
    param_2[0xc] = iVar31 + 1U;
    if ((uint)param_2[0xd] < iVar31 + 1U) {
      func_0x0001481caa90(param_2 + 10,iVar31);
    }
    func_0x0001481b2fe0((longlong)iVar31 * 0x40 + *(longlong *)(param_2 + 10),&uStack_678);
    param_2[0xf] = param_2[0xf] + iVar30;
    func_0x000148152560(&uStack_678);
  }
  if (0 < param_3[0xc]) {
    func_0x000140e820a0(&uStack_638);
    uStack_620 = 0;
    func_0x000140e820a0(&uStack_618);
    uStack_600 = 0;
    func_0x000140cf7750(alStack_4f8,L"VICTORY");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_2c0,alStack_4f8);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_638;
    puVar21[1] = uStack_630;
    uStack_628 = *(undefined4 *)(puVar21 + 2);
    uStack_638 = uVar4;
    uStack_630 = uVar6;
    func_0x000140e86d70(auStack_2c0);
    if (alStack_4f8[0] != 0) {
      func_0x000140e282f0();
    }
    uStack_620 = 5;
    func_0x000140cf7750(alStack_4e8,L"CAME ON TIME");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_2a8,alStack_4e8);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_618;
    puVar21[1] = uStack_610;
    uStack_608 = *(undefined4 *)(puVar21 + 2);
    uStack_618 = uVar4;
    uStack_610 = uVar6;
    func_0x000140e86d70(auStack_2a8);
    if (alStack_4e8[0] != 0) {
      func_0x000140e282f0();
    }
    uStack_600 = 0;
    piVar3 = *(int **)(param_2 + 10);
    if ((piVar3 <= &uStack_638) && (&uStack_638 < piVar3 + (longlong)(int)param_2[0xd] * 0x10)) {
      lStack_988 = (longlong)(int)param_2[0xc];
      puStack_980 = (undefined *)0x40;
      piStack_9a0 = (int *)&uStack_638;
      puStack_9a8 = &UNK_14bce6d80;
      piStack_998 = piVar3;
      lStack_990 = (longlong)(int)param_2[0xd];
      cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar30 = param_2[0xc];
    param_2[0xc] = iVar30 + 1U;
    if ((uint)param_2[0xd] < iVar30 + 1U) {
      func_0x0001481caa90(param_2 + 10,iVar30);
    }
    func_0x0001481b2fe0((longlong)iVar30 * 0x40 + *(longlong *)(param_2 + 10),&uStack_638);
    param_2[0xf] = param_2[0xf] + 5;
    func_0x000148152560(&uStack_638);
  }
  if (param_3[7] == 0) {
    func_0x000140e820a0(&uStack_818);
    iStack_800 = 0;
    func_0x000140e820a0(&uStack_7f8);
    uStack_7e0 = 0;
    func_0x000140cf7750(alStack_4d8,L"PURIST");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_290,alStack_4d8);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_818;
    puVar21[1] = uStack_810;
    uStack_808 = *(undefined4 *)(puVar21 + 2);
    uStack_818 = uVar4;
    uStack_810 = uVar6;
    func_0x000140e86d70(auStack_290);
    if (alStack_4d8[0] != 0) {
      func_0x000140e282f0();
    }
    iStack_800 = (int)ROUND((fVar35 * _DAT_14bcfdb5c + fVar35 * _DAT_14bcfdb5c) - fVar9) >> 1;
    func_0x000140cf7750(alStack_4c8,L"NO ITEMS");
    puVar21 = (undefined8 *)func_0x000140ebb430(auStack_278,alStack_4c8);
    uVar4 = *puVar21;
    uVar6 = puVar21[1];
    *puVar21 = uStack_7f8;
    puVar21[1] = uStack_7f0;
    uStack_7e8 = *(undefined4 *)(puVar21 + 2);
    uStack_7f8 = uVar4;
    uStack_7f0 = uVar6;
    func_0x000140e86d70(auStack_278);
    if (alStack_4c8[0] != 0) {
      func_0x000140e282f0();
    }
    uStack_7e0 = 0;
    piVar3 = *(int **)(param_2 + 10);
    if ((piVar3 <= &uStack_818) && (&uStack_818 < piVar3 + (longlong)(int)param_2[0xd] * 0x10)) {
      lStack_988 = (longlong)(int)param_2[0xc];
      puStack_980 = (undefined *)0x40;
      piStack_9a0 = (int *)&uStack_818;
      puStack_9a8 = &UNK_14bce6d80;
      piStack_998 = piVar3;
      lStack_990 = (longlong)(int)param_2[0xd];
      cVar18 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr);
      if (cVar18 != '\0') {
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
    }
    iVar30 = param_2[0xc];
    param_2[0xc] = iVar30 + 1U;
    if ((uint)param_2[0xd] < iVar30 + 1U) {
      func_0x0001481caa90(param_2 + 10,iVar30);
    }
    func_0x0001481b2fe0((longlong)iVar30 * 0x40 + *(longlong *)(param_2 + 10),&uStack_818);
    param_2[0xf] = param_2[0xf] + iStack_800;
    func_0x000148152560(&uStack_818);
  }
  param_2[0x35] = iStack_970;
  param_2[0x36] = iVar24;
  if (2 < DAT_14eab53c8) {
    puStack_980 = &UNK_14bd0f08c;
    if (*(char *)(param_2 + 0x34) != '\0') {
      puStack_980 = &UNK_14bd0f098;
    }
    lStack_988 = CONCAT44(lStack_988._4_4_,param_2[0x12]);
    lStack_990 = CONCAT44(lStack_990._4_4_,param_2[0xf]);
    piStack_998 = (int *)CONCAT44(piStack_998._4_4_,iStack_970);
    piStack_9a0 = (int *)CONCAT44(piStack_9a0._4_4_,iVar24);
    puStack_9a8 = (undefined *)CONCAT44(puStack_9a8._4_4_,param_2[8]);
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf76a68,param_2[1],*param_2);
  }
  func_0x00014b880380(uStack_b8 ^ (ulonglong)auStack_9c8);
  return;
}


/* Instruction evidence:
1481c6a00 MOV RAX,RSP
1481c6a03 MOV qword ptr [RAX + 0x20],RBX
1481c6a07 MOV qword ptr [RAX + 0x10],RDX
1481c6a0b PUSH RBP
1481c6a0c PUSH RSI
1481c6a0d PUSH RDI
1481c6a0e PUSH R12
1481c6a10 PUSH R13
1481c6a12 PUSH R14
1481c6a14 PUSH R15
1481c6a16 LEA RBP,[RAX + -0x8c8]
1481c6a1d SUB RSP,0x990
1481c6a24 MOVAPS xmmword ptr [RAX + -0x48],XMM6
1481c6a28 MOVAPS xmmword ptr [RAX + -0x58],XMM7
1481c6a2c MOVAPS xmmword ptr [RAX + -0x68],XMM8
1481c6a31 MOVAPS xmmword ptr [RAX + -0x78],XMM9
1481c6a36 MOVAPS xmmword ptr [RAX + -0x88],XMM10
1481c6a3e MOVAPS xmmword ptr [RAX + -0x98],XMM11
1481c6a46 MOVAPS xmmword ptr [RAX + -0xa8],XMM12
1481c6a4e MOV RAX,qword ptr [0x14ea60b28]
1481c6a55 XOR RAX,RSP
1481c6a58 MOV qword ptr [RBP + 0x810],RAX
1481c6a5f MOV R12,R8
1481c6a62 MOV qword ptr [RBP + 0x2d8],R8
1481c6a69 MOV R14,RDX
1481c6a6c MOV R13,RCX
1481c6a6f MOV qword ptr [RBP + 0x2d0],RCX
1481c6a76 MOV qword ptr [RBP + 0x4d0],RDX
1481c6a7d XOR EAX,EAX
1481c6a7f MOV dword ptr [RSP + 0x50],EAX
1481c6a83 MOV dword ptr [RDX],EAX
1481c6a85 MOV dword ptr [RDX + 0x4],0x1
1481c6a8c MOV dword ptr [RDX + 0x8],0x64
1481c6a93 MOV qword ptr [RDX + 0x10],RAX
1481c6a97 MOV qword ptr [RDX + 0x18],RAX
1481c6a9b MOV dword ptr [RDX + 0x20],EAX
1481c6a9e MOV qword ptr [RDX + 0x28],RAX
1481c6aa2 MOV qword ptr [RDX + 0x30],RAX
1481c6aa6 MOV qword ptr [RDX + 0x38],RAX
1481c6aaa MOV qword ptr [RDX + 0x40],RAX
1481c6aae MOV qword ptr [RDX + 0x48],RAX
1481c6ab2 MOV qword ptr [RDX + 0x50],RAX
1481c6ab6 MOV qword ptr [RDX + 0x58],RAX
1481c6aba MOV qword ptr [RDX + 0x60],RAX
1481c6abe MOV qword ptr [RDX + 0x68],RAX
1481c6ac2 MOV qword ptr [RDX + 0x70],RAX
1481c6ac6 MOV dword ptr [RDX + 0x78],EAX
1481c6ac9 MOV word ptr [RDX + 0x7c],AX
1481c6acd MOV qword ptr [RDX + 0x80],RAX
1481c6ad4 MOV dword ptr [RDX + 0x88],EAX
1481c6ada MOV qword ptr [RDX + 0x90],RAX
1481c6ae1 MOV qword ptr [RDX + 0x98],RAX
1481c6ae8 MOV qword ptr [RDX + 0xa0],RAX
1481c6aef MOV qword ptr [RDX + 0xa8],RAX
1481c6af6 MOV qword ptr [RDX + 0xb0],RAX
1481c6afd MOV qword ptr [RDX + 0xb8],RAX
1481c6b04 MOV qword ptr [RDX + 0xc0],RAX
1481c6b0b MOV dword ptr [RDX + 0xc8],EAX
1481c6b11 MOV byte ptr [RDX + 0xd0],AL
1481c6b17 MOV dword ptr [RDX + 0xd4],EAX
1481c6b1d MOV dword ptr [RDX + 0xd8],0x1
1481c6b27 MOV EDI,0x1
1481c6b2c MOV dword ptr [RSP + 0x50],EDI
1481c6b30 MOV EAX,dword ptr [RCX + 0x40]
1481c6b33 MOV dword ptr [RDX],EAX
1481c6b35 MOV EAX,dword ptr [RCX + 0x50]
1481c6b38 MOV dword ptr [RDX + 0x4],EAX
1481c6b3b CALL 0x1481c32e0
1481c6b40 MOV dword ptr [R14 + 0x8],EAX
1481c6b44 MOV EAX,dword ptr [R13 + 0x58]
1481c6b48 MOV dword ptr [R14 + 0x38],EAX
1481c6b4c MOV RDX,R12
1481c6b4f LEA RCX,[R14 + 0x50]
1481c6b53 CALL 0x1481538d0
1481c6b58 CMP dword ptr [R12 + 0x30],0x0
1481c6b5e SETG AL
1481c6b61 MOV byte ptr [R14 + 0xd0],AL
1481c6b68 MOVSS XMM12,dword ptr [0x14bcfdb28]
1481c6b71 MOVSS XMM8,dword ptr [0x14bcef9ec]
1481c6b7a CMP dword ptr [R12 + 0x30],0x0
1481c6b80 JLE 0x1481c6b88
1481c6b82 MOVAPS XMM11,XMM8
1481c6b86 JMP 0x1481c6b8c
1481c6b88 MOVAPS XMM11,XMM12
1481c6b8c XORPS XMM1,XMM1
1481c6b8f CVTSI2SS XMM1,dword ptr [R12 + 0x28]
1481c6b96 MULSS XMM1,dword ptr [0x14bcfdb20]
1481c6b9e ADDSS XMM1,XMM1
1481c6ba2 SUBSS XMM1,XMM12
1481c6ba7 CVTSS2SI R15D,XMM1
1481c6bac SAR R15D,0x1
1481c6baf MOV dword ptr [RSP + 0x78],R15D
1481c6bb4 XORPS XMM1,XMM1
1481c6bb7 CVTSI2SS XMM1,R15D
1481c6bbc MULSS XMM1,dword ptr [R13 + 0x78]
1481c6bc2 MULSS XMM1,XMM11
1481c6bc7 ADDSS XMM1,XMM1
1481c6bcb SUBSS XMM1,XMM12
1481c6bd0 CVTSS2SI EBX,XMM1
1481c6bd4 SAR EBX,0x1
1481c6bd6 TEST EBX,EBX
1481c6bd8 JLE 0x1481c6d9b
1481c6bde LEA RCX,[RBP + 0x128]
1481c6be5 CALL 0x140e820a0
1481c6bea NOP
1481c6beb MOV dword ptr [RBP + 0x140],0x0
1481c6bf5 LEA RCX,[RBP + 0x148]
1481c6bfc CALL 0x140e820a0
1481c6c01 NOP
1481c6c02 LEA RDX,[0x14cf76b70]
1481c6c09 LEA RCX,[RBP + 0x410]
1481c6c10 CALL 0x140cf7750
1481c6c15 NOP
1481c6c16 LEA RDX,[RBP + 0x410]
1481c6c1d LEA RCX,[RBP + 0x5d8]
1481c6c24 CALL 0x140ebb430
1481c6c29 MOVUPS XMM1,xmmword ptr [RBP + 0x128]
1481c6c30 MOVUPS XMM0,xmmword ptr [RAX]
1481c6c33 MOVUPS xmmword ptr [RBP + 0x128],XMM0
1481c6c3a MOVUPS xmmword ptr [RAX],XMM1
1481c6c3d MOV EAX,dword ptr [RAX + 0x10]
1481c6c40 MOV dword ptr [RBP + 0x138],EAX
1481c6c46 LEA RCX,[RBP + 0x5d8]
1481c6c4d CALL 0x140e86d70
1481c6c52 NOP
1481c6c53 MOV RCX,qword ptr [RBP + 0x410]
1481c6c5a TEST RCX,RCX
1481c6c5d JZ 0x1481c6c65
1481c6c5f CALL 0x140e282f0
1481c6c64 NOP
1481c6c65 MOV dword ptr [RBP + 0x140],EBX
1481c6c6b MOV R8D,R15D
1481c6c6e LEA RDX,[0x14cf76b88]
1481c6c75 LEA RCX,[RBP + 0x420]
1481c6c7c CALL 0x140d169d0
1481c6c81 MOV EDI,0x201
1481c6c86 MOV dword ptr [RSP + 0x50],EDI
1481c6c8a LEA RDX,[RBP + 0x420]
1481c6c91 LEA RCX,[RBP + 0x668]
1481c6c98 CALL 0x140ebb430
1481c6c9d MOVUPS XMM1,xmmword ptr [RBP + 0x148]
1481c6ca4 MOVUPS XMM0,xmmword ptr [RAX]
1481c6ca7 MOVUPS xmmword ptr [RBP + 0x148],XMM0
1481c6cae MOVUPS xmmword ptr [RAX],XMM1
1481c6cb1 MOV EAX,dword ptr [RAX + 0x10]
1481c6cb4 MOV dword ptr [RBP + 0x158],EAX
1481c6cba LEA RCX,[RBP + 0x668]
1481c6cc1 CALL 0x140e86d70
1481c6cc6 NOP
1481c6cc7 MOV RCX,qword ptr [RBP + 0x420]
1481c6cce TEST RCX,RCX
1481c6cd1 JZ 0x1481c6cd9
1481c6cd3 CALL 0x140e282f0
1481c6cd8 NOP
1481c6cd9 MOV RCX,qword ptr [R14 + 0x10]
1481c6cdd LEA RAX,[RBP + 0x128]
1481c6ce4 CMP RAX,RCX
1481c6ce7 JC 0x1481c6d5e
1481c6ce9 MOVSXD RDX,dword ptr [R14 + 0x1c]
1481c6ced IMUL RAX,RDX,0x38
1481c6cf1 ADD RAX,RCX
1481c6cf4 LEA R8,[RBP + 0x128]
1481c6cfb CMP R8,RAX
1481c6cfe JNC 0x1481c6d5e
1481c6d00 MOVSXD RAX,dword ptr [R14 + 0x18]
1481c6d04 MOV R9,qword ptr [RBP + 0x8c8]
1481c6d0b MOV qword ptr [RSP + 0x48],0x38
1481c6d14 MOV qword ptr [RSP + 0x40],RAX
1481c6d19 MOV qword ptr [RSP + 0x38],RDX
1481c6d1e MOV qword ptr [RSP + 0x30],RCX
1481c6d23 LEA RAX,[RBP + 0x128]
1481c6d2a MOV qword ptr [RSP + 0x28],RAX
1481c6d2f LEA RAX,[0x14bce6d80]
1481c6d36 MOV qword ptr [RSP + 0x20],RAX
1481c6d3b MOV R8D,0x63e
1481c6d41 LEA RDX,[0x14cf27ac0]
1481c6d48 LEA RCX,[0x14bce6eb8]
1481c6d4f CALL 0x140f8dfd0
1481c6d54 TEST AL,AL
1481c6d56 JZ 0x1481c6d5e
1481c6d58 NOP
1481c6d59 INT3
1481c6d5e MOVSXD RBX,dword ptr [R14 + 0x18]
1481c6d62 LEA EAX,[RBX + 0x1]
1481c6d65 MOV dword ptr [R14 + 0x18],EAX
1481c6d69 CMP EAX,dword ptr [R14 + 0x1c]
1481c6d6d JBE 0x1481c6d7a
1481c6d6f MOV EDX,EBX
1481c6d71 LEA RCX,[R14 + 0x10]
1481c6d75 CALL 0x1481cab30
1481c6d7a IMUL RCX,RBX,0x38
1481c6d7e ADD RCX,qword ptr [R14 + 0x10]
1481c6d82 LEA RDX,[RBP + 0x128]
1481c6d89 CALL 0x1481b3040
1481c6d8e NOP
1481c6d8f LEA RCX,[RBP + 0x128]
1481c6d96 CALL 0x148152600
1481c6d9b XORPS XMM0,XMM0
1481c6d9e CVTSI2SS XMM0,dword ptr [R13 + 0x8c]
1481c6da7 XORPS XMM1,XMM1
1481c6daa CVTSI2SS XMM1,dword ptr [R12]
1481c6db0 MULSS XMM1,dword ptr [R13 + 0x7c]
1481c6db6 MINSS XMM1,XMM0
1481c6dba MULSS XMM1,XMM11
1481c6dbf ADDSS XMM1,XMM1
1481c6dc3 SUBSS XMM1,XMM12
1481c6dc8 CVTSS2SI EBX,XMM1
1481c6dcc SAR EBX,0x1
1481c6dce TEST EBX,EBX
1481c6dd0 JLE 0x1481c6fdf
1481c6dd6 LEA RCX,[RBP + 0x40]
1481c6dda CALL 0x140e820a0
1481c6ddf NOP
1481c6de0 XOR R15D,R15D
1481c6de3 MOV dword ptr [RBP + 0x58],R15D
1481c6de7 LEA RCX,[RBP + 0x60]
1481c6deb CALL 0x140e820a0
1481c6df0 NOP
1481c6df1 LEA RDX,[0x14cf76b98]
1481c6df8 LEA RCX,[RBP + 0x340]
1481c6dff CALL 0x140cf7750
1481c6e04 NOP
1481c6e05 LEA RDX,[RBP + 0x340]
1481c6e0c LEA RCX,[RBP + 0x680]
1481c6e13 CALL 0x140ebb430
1481c6e18 MOVUPS XMM1,xmmword ptr [RBP + 0x40]
1481c6e1c MOVUPS XMM0,xmmword ptr [RAX]
1481c6e1f MOVUPS xmmword ptr [RBP + 0x40],XMM0
1481c6e23 MOVUPS xmmword ptr [RAX],XMM1
1481c6e26 MOV EAX,dword ptr [RAX + 0x10]
1481c6e29 MOV dword ptr [RBP + 0x50],EAX
1481c6e2c LEA RCX,[RBP + 0x680]
1481c6e33 CALL 0x140e86d70
1481c6e38 NOP
1481c6e39 MOV RCX,qword ptr [RBP + 0x340]
1481c6e40 TEST RCX,RCX
1481c6e43 JZ 0x1481c6e4b
1481c6e45 CALL 0x140e282f0
1481c6e4a NOP
1481c6e4b MOV dword ptr [RBP + 0x58],EBX
1481c6e4e MOV R8D,dword ptr [R12]
1481c6e52 MOVD XMM1,R8D
1481c6e57 CVTDQ2PS XMM1,XMM1
1481c6e5a MULSS XMM1,dword ptr [R13 + 0x7c]
1481c6e60 MOVD XMM0,dword ptr [R13 + 0x8c]
1481c6e69 CVTDQ2PS XMM0,XMM0
1481c6e6c COMISS XMM1,XMM0
1481c6e6f JC 0x1481c6ec9
1481c6e71 LEA RDX,[0x14cf76ba8]
1481c6e78 LEA RCX,[RBP + 0x430]
1481c6e7f CALL 0x140d169d0
1481c6e84 BTS EDI,0xd
1481c6e88 MOV dword ptr [RSP + 0x50],EDI
1481c6e8c LEA RDX,[RBP + 0x430]
1481c6e93 LEA RCX,[RBP + 0x698]
1481c6e9a CALL 0x140ebb430
1481c6e9f MOVUPS XMM1,xmmword ptr [RBP + 0x60]
1481c6ea3 MOVUPS XMM0,xmmword ptr [RAX]
1481c6ea6 MOVUPS xmmword ptr [RBP + 0x60],XMM0
1481c6eaa MOVUPS xmmword ptr [RAX],XMM1
1481c6ead MOV EAX,dword ptr [RAX + 0x10]
1481c6eb0 MOV dword ptr [RBP + 0x70],EAX
1481c6eb3 LEA RCX,[RBP + 0x698]
1481c6eba CALL 0x140e86d70
1481c6ebf NOP
1481c6ec0 MOV RCX,qword ptr [RBP + 0x430]
1481c6ec7 JMP 0x1481c6f1f
1481c6ec9 LEA RDX,[0x14cf76bd0]
1481c6ed0 LEA RCX,[RBP + 0x440]
1481c6ed7 CALL 0x140d169d0
1481c6edc BTS EDI,0xc
1481c6ee0 MOV dword ptr [RSP + 0x50],EDI
1481c6ee4 LEA RDX,[RBP + 0x440]
1481c6eeb LEA RCX,[RBP + 0x6b0]
1481c6ef2 CALL 0x140ebb430
1481c6ef7 MOVUPS XMM1,xmmword ptr [RBP + 0x60]
1481c6efb MOVUPS XMM0,xmmword ptr [RAX]
1481c6efe MOVUPS xmmword ptr [RBP + 0x60],XMM0
1481c6f02 MOVUPS xmmword ptr [RAX],XMM1
1481c6f05 MOV EAX,dword ptr [RAX + 0x10]
1481c6f08 MOV dword ptr [RBP + 0x70],EAX
1481c6f0b LEA RCX,[RBP + 0x6b0]
1481c6f12 CALL 0x140e86d70
1481c6f17 NOP
1481c6f18 MOV RCX,qword ptr [RBP + 0x440]
1481c6f1f TEST RCX,RCX
1481c6f22 JZ 0x1481c6f2a
1481c6f24 CALL 0x140e282f0
1481c6f29 NOP
1481c6f2a MOV RCX,qword ptr [R14 + 0x10]
1481c6f2e LEA RAX,[RBP + 0x40]
1481c6f32 CMP RAX,RCX
1481c6f35 JC 0x1481c6fa6
1481c6f37 MOVSXD RDX,dword ptr [R14 + 0x1c]
1481c6f3b IMUL RAX,RDX,0x38
1481c6f3f ADD RAX,RCX
1481c6f42 LEA R8,[RBP + 0x40]
1481c6f46 CMP R8,RAX
1481c6f49 JNC 0x1481c6fa6
1481c6f4b MOVSXD RAX,dword ptr [R14 + 0x18]
1481c6f4f MOV R9,qword ptr [RBP + 0x8c8]
1481c6f56 MOV qword ptr [RSP + 0x48],0x38
1481c6f5f MOV qword ptr [RSP + 0x40],RAX
1481c6f64 MOV qword ptr [RSP + 0x38],RDX
1481c6f69 MOV qword ptr [RSP + 0x30],RCX
1481c6f6e LEA RAX,[RBP + 0x40]
1481c6f72 MOV qword ptr [RSP + 0x28],RAX
1481c6f77 LEA RAX,[0x14bce6d80]
1481c6f7e MOV qword ptr [RSP + 0x20],RAX
1481c6f83 MOV R8D,0x63e
1481c6f89 LEA RDX,[0x14cf27ac0]
1481c6f90 LEA RCX,[0x14bce6eb8]
1481c6f97 CALL 0x140f8dfd0
1481c6f9c TEST AL,AL
1481c6f9e JZ 0x1481c6fa6
1481c6fa0 NOP
1481c6fa1 INT3
1481c6fa6 MOVSXD RSI,dword ptr [R14 + 0x18]
1481c6faa LEA EAX,[RSI + 0x1]
1481c6fad MOV dword ptr [R14 + 0x18],EAX
1481c6fb1 CMP EAX,dword ptr [R14 + 0x1c]
1481c6fb5 JBE 0x1481c6fc2
1481c6fb7 MOV EDX,ESI
1481c6fb9 LEA RCX,[R14 + 0x10]
1481c6fbd CALL 0x1481cab30
1481c6fc2 IMUL RCX,RSI,0x38
1481c6fc6 ADD RCX,qword ptr [R14 + 0x10]
1481c6fca LEA RDX,[RBP + 0x40]
1481c6fce CALL 0x1481b3040
1481c6fd3 NOP
1481c6fd4 LEA RCX,[RBP + 0x40]
1481c6fd8 CALL 0x148152600
1481c6fdd JMP 0x1481c6fe2
1481c6fdf XOR R15D,R15D
1481c6fe2 MOV EBX,dword ptr [R12 + 0xc]
1481c6fe7 ADD EBX,dword ptr [R12 + 0x8]
1481c6fec MOV EAX,dword ptr [R13 + 0x90]
1481c6ff3 CMP EBX,EAX
1481c6ff5 CMOVL EAX,EBX
1481c6ff8 MOVD XMM1,EAX
1481c6ffc CVTDQ2PS XMM1,XMM1
1481c6fff MULSS XMM1,XMM11
1481c7004 ADDSS XMM1,XMM1
1481c7008 SUBSS XMM1,XMM12
1481c700d CVTSS2SI ESI,XMM1
1481c7011 SAR ESI,0x1
1481c7013 TEST ESI,ESI
1481c7015 JLE 0x1481c7226
1481c701b LEA RCX,[RBP + 0x78]
1481c701f CALL 0x140e820a0
1481c7024 NOP
1481c7025 MOV dword ptr [RBP + 0x90],R15D
1481c702c LEA RCX,[RBP + 0x98]
1481c7033 CALL 0x140e820a0
1481c7038 NOP
1481c7039 LEA RDX,[0x14cf76be8]
1481c7040 LEA RCX,[RBP + 0x450]
1481c7047 CALL 0x140cf7750
1481c704c NOP
1481c704d LEA RDX,[RBP + 0x450]
1481c7054 LEA RCX,[RBP + 0x6e0]
1481c705b CALL 0x140ebb430
1481c7060 MOVUPS XMM1,xmmword ptr [RBP + 0x78]
1481c7064 MOVUPS XMM0,xmmword ptr [RAX]
1481c7067 MOVUPS xmmword ptr [RBP + 0x78],XMM0
1481c706b MOVUPS xmmword ptr [RAX],XMM1
1481c706e MOV EAX,dword ptr [RAX + 0x10]
1481c7071 MOV dword ptr [RBP + 0x88],EAX
1481c7077 LEA RCX,[RBP + 0x6e0]
1481c707e CALL 0x140e86d70
1481c7083 NOP
1481c7084 MOV RCX,qword ptr [RBP + 0x450]
1481c708b TEST RCX,RCX
1481c708e JZ 0x1481c7096
1481c7090 CALL 0x140e282f0
1481c7095 NOP
1481c7096 MOV dword ptr [RBP + 0x90],ESI
1481c709c MOV R8D,EBX
1481c709f CMP EBX,dword ptr [R13 + 0x90]
1481c70a6 JL 0x1481c7109
1481c70a8 LEA RDX,[0x14cf76bf8]
1481c70af LEA RCX,[RBP + 0x470]
1481c70b6 CALL 0x140d169d0
1481c70bb BTS EDI,0xb
1481c70bf MOV dword ptr [RSP + 0x50],EDI
1481c70c3 LEA RDX,[RBP + 0x470]
1481c70ca LEA RCX,[RBP + 0x6f8]
1481c70d1 CALL 0x140ebb430
1481c70d6 MOVUPS XMM1,xmmword ptr [RBP + 0x98]
1481c70dd MOVUPS XMM0,xmmword ptr [RAX]
1481c70e0 MOVUPS xmmword ptr [RBP + 0x98],XMM0
1481c70e7 MOVUPS xmmword ptr [RAX],XMM1
1481c70ea MOV EAX,dword ptr [RAX + 0x10]
1481c70ed MOV dword ptr [RBP + 0xa8],EAX
1481c70f3 LEA RCX,[RBP + 0x6f8]
1481c70fa CALL 0x140e86d70
1481c70ff NOP
1481c7100 MOV RCX,qword ptr [RBP + 0x470]
1481c7107 JMP 0x1481c7168
1481c7109 LEA RDX,[0x14cf76c20]
1481c7110 LEA RCX,[RBP + 0x480]
1481c7117 CALL 0x140d169d0
1481c711c BTS EDI,0xe
1481c7120 MOV dword ptr [RSP + 0x50],EDI
1481c7124 LEA RDX,[RBP + 0x480]
1481c712b LEA RCX,[RBP + 0x710]
1481c7132 CALL 0x140ebb430
1481c7137 MOVUPS XMM1,xmmword ptr [RBP + 0x98]
1481c713e MOVUPS XMM0,xmmword ptr [RAX]
1481c7141 MOVUPS xmmword ptr [RBP + 0x98],XMM0
1481c7148 MOVUPS xmmword ptr [RAX],XMM1
1481c714b MOV EAX,dword ptr [RAX + 0x10]
1481c714e MOV dword ptr [RBP + 0xa8],EAX
1481c7154 LEA RCX,[RBP + 0x710]
1481c715b CALL 0x140e86d70
1481c7160 NOP
1481c7161 MOV RCX,qword ptr [RBP + 0x480]
1481c7168 TEST RCX,RCX
1481c716b JZ 0x1481c7173
1481c716d CALL 0x140e282f0
1481c7172 NOP
1481c7173 MOV RCX,qword ptr [R14 + 0x10]
1481c7177 LEA RAX,[RBP + 0x78]
1481c717b CMP RAX,RCX
1481c717e JC 0x1481c71ef
1481c7180 MOVSXD RDX,dword ptr [R14 + 0x1c]
1481c7184 IMUL RAX,RDX,0x38
1481c7188 ADD RAX,RCX
1481c718b LEA R8,[RBP + 0x78]
1481c718f CMP R8,RAX
1481c7192 JNC 0x1481c71ef
1481c7194 MOVSXD RAX,dword ptr [R14 + 0x18]
1481c7198 MOV R9,qword ptr [RBP + 0x8c8]
1481c719f MOV qword ptr [RSP + 0x48],0x38
1481c71a8 MOV qword ptr [RSP + 0x40],RAX
1481c71ad MOV qword ptr [RSP + 0x38],RDX
1481c71b2 MOV qword ptr [RSP + 0x30],RCX
1481c71b7 LEA RAX,[RBP + 0x78]
1481c71bb MOV qword ptr [RSP + 0x28],RAX
1481c71c0 LEA RAX,[0x14bce6d80]
1481c71c7 MOV qword ptr [RSP + 0x20],RAX
1481c71cc MOV R8D,0x63e
1481c71d2 LEA RDX,[0x14cf27ac0]
1481c71d9 LEA RCX,[0x14bce6eb8]
1481c71e0 CALL 0x140f8dfd0
1481c71e5 TEST AL,AL
1481c71e7 JZ 0x1481c71ef
1481c71e9 NOP
1481c71ea INT3
1481c71ef MOVSXD RSI,dword ptr [R14 + 0x18]
1481c71f3 LEA EAX,[RSI + 0x1]
1481c71f6 MOV dword ptr [R14 + 0x18],EAX
1481c71fa CMP EAX,dword ptr [R14 + 0x1c]
1481c71fe JBE 0x1481c720b
1481c7200 MOV EDX,ESI
1481c7202 LEA RCX,[R14 + 0x10]
1481c7206 CALL 0x1481cab30
1481c720b IMUL RCX,RSI,0x38
1481c720f ADD RCX,qword ptr [R14 + 0x10]
1481c7213 LEA RDX,[RBP + 0x78]
1481c7217 CALL 0x1481b3040
1481c721c NOP
1481c721d LEA RCX,[RBP + 0x78]
1481c7221 CALL 0x148152600
1481c7226 MOVD XMM1,dword ptr [R12 + 0x4]
1481c722d CVTDQ2PS XMM1,XMM1
1481c7230 MULSS XMM1,dword ptr [R13 + 0x84]
1481c7239 MULSS XMM1,XMM11
1481c723e ADDSS XMM1,XMM1
1481c7242 SUBSS XMM1,XMM12
1481c7247 CVTSS2SI EBX,XMM1
1481c724b SAR EBX,0x1
1481c724d TEST EBX,EBX
1481c724f JLE 0x1481c740c
1481c7255 LEA RCX,[RBP + 0x160]
1481c725c CALL 0x140e820a0
1481c7261 NOP
1481c7262 MOV dword ptr [RBP + 0x178],R15D
1481c7269 LEA RCX,[RBP + 0x180]
1481c7270 CALL 0x140e820a0
1481c7275 NOP
1481c7276 LEA RDX,[0x14cf76c38]
1481c727d LEA RCX,[RBP + 0x490]
1481c7284 CALL 0x140cf7750
1481c7289 NOP
1481c728a LEA RDX,[RBP + 0x490]
1481c7291 LEA RCX,[RBP + 0x728]
1481c7298 CALL 0x140ebb430
1481c729d MOVUPS XMM1,xmmword ptr [RBP + 0x160]
1481c72a4 MOVUPS XMM0,xmmword ptr [RAX]
1481c72a7 MOVUPS xmmword ptr [RBP + 0x160],XMM0
1481c72ae MOVUPS xmmword ptr [RAX],XMM1
1481c72b1 MOV EAX,dword ptr [RAX + 0x10]
1481c72b4 MOV dword ptr [RBP + 0x170],EAX
1481c72ba LEA RCX,[RBP + 0x728]
1481c72c1 CALL 0x140e86d70
1481c72c6 NOP
1481c72c7 MOV RCX,qword ptr [RBP + 0x490]
1481c72ce TEST RCX,RCX
1481c72d1 JZ 0x1481c72d9
1481c72d3 CALL 0x140e282f0
1481c72d8 NOP
1481c72d9 MOV dword ptr [RBP + 0x178],EBX
1481c72df MOV R8D,dword ptr [R12 + 0x4]
1481c72e4 LEA RDX,[0x14cf76c48]
1481c72eb LEA RCX,[RBP + 0x4a0]
1481c72f2 CALL 0x140d169d0
1481c72f7 BTS EDI,0xa
1481c72fb MOV dword ptr [RSP + 0x50],EDI
1481c72ff LEA RDX,[RBP + 0x4a0]
1481c7306 LEA RCX,[RBP + 0x740]
1481c730d CALL 0x140ebb430
1481c7312 MOVUPS XMM1,xmmword ptr [RBP + 0x180]
1481c7319 MOVUPS XMM0,xmmword ptr [RAX]
1481c731c MOVUPS xmmword ptr [RBP + 0x180],XMM0
1481c7323 MOVUPS xmmword ptr [RAX],XMM1
1481c7326 MOV EAX,dword ptr [RAX + 0x10]
1481c7329 MOV dword ptr [RBP + 0x190],EAX
1481c732f LEA RCX,[RBP + 0x740]
1481c7336 CALL 0x140e86d70
1481c733b NOP
1481c733c MOV RCX,qword ptr [RBP + 0x4a0]
1481c7343 TEST RCX,RCX
1481c7346 JZ 0x1481c734e
1481c7348 CALL 0x140e282f0
1481c734d NOP
1481c734e MOV RCX,qword ptr [R14 + 0x10]
1481c7352 LEA RAX,[RBP + 0x160]
1481c7359 CMP RAX,RCX
1481c735c JC 0x1481c73cf
1481c735e MOVSXD RDX,dword ptr [R14 + 0x1c]
1481c7362 IMUL RAX,RDX,0x38
1481c7366 ADD RAX,RCX
1481c7369 LEA R8,[RBP + 0x160]
1481c7370 CMP R8,RAX
1481c7373 JNC 0x1481c73cf
1481c7375 MOVSXD RAX,dword ptr [R14 + 0x18]
1481c7379 MOV R9,qword ptr [RBP + 0x8c8]
1481c7380 MOV qword ptr [RSP + 0x48],0x38
1481c7389 MOV qword ptr [RSP + 0x40],RAX
1481c738e MOV qword ptr [RSP + 0x38],RDX
1481c7393 MOV qword ptr [RSP + 0x30],RCX
1481c7398 LEA RAX,[RBP + 0x160]
1481c739f MOV qword ptr [RSP + 0x28],RAX
1481c73a4 LEA RAX,[0x14bce6d80]
1481c73ab MOV qword ptr [RSP + 0x20],RAX
1481c73b0 MOV R8D,0x63e
1481c73b6 LEA RDX,[0x14cf27ac0]
1481c73bd LEA RCX,[0x14bce6eb8]
1481c73c4 CALL 0x140f8dfd0
1481c73c9 TEST AL,AL
1481c73cb JZ 0x1481c73cf
1481c73cd NOP
1481c73ce INT3
1481c73cf MOVSXD RDI,dword ptr [R14 + 0x18]
1481c73d3 LEA EAX,[RDI + 0x1]
1481c73d6 MOV dword ptr [R14 + 0x18],EAX
1481c73da CMP EAX,dword ptr [R14 + 0x1c]
1481c73de JBE 0x1481c73eb
1481c73e0 MOV EDX,EDI
1481c73e2 LEA RCX,[R14 + 0x10]
1481c73e6 CALL 0x1481cab30
1481c73eb IMUL RCX,RDI,0x38
1481c73ef ADD RCX,qword ptr [R14 + 0x10]
1481c73f3 LEA RDX,[RBP + 0x160]
1481c73fa CALL 0x1481b3040
1481c73ff NOP
1481c7400 LEA RCX,[RBP + 0x160]
1481c7407 CALL 0x148152600
1481c740c CMP dword ptr [R12 + 0x30],0x0
1481c7412 JLE 0x1481c75cc
1481c7418 LEA RCX,[RBP + 0xf0]
1481c741f CALL 0x140e820a0
1481c7424 NOP
1481c7425 MOV dword ptr [RBP + 0x108],R15D
1481c742c LEA RCX,[RBP + 0x110]
1481c7433 CALL 0x140e820a0
1481c7438 NOP
1481c7439 LEA RDX,[0x14cf76c60]
1481c7440 LEA RCX,[RBP + 0x4b0]
1481c7447 CALL 0x140cf7750
1481c744c NOP
1481c744d LEA RDX,[RBP + 0x4b0]
1481c7454 LEA RCX,[RBP + 0x758]
1481c745b CALL 0x140ebb430
1481c7460 MOVUPS XMM1,xmmword ptr [RBP + 0xf0]
1481c7467 MOVUPS XMM0,xmmword ptr [RAX]
1481c746a MOVUPS xmmword ptr [RBP + 0xf0],XMM0
1481c7471 MOVUPS xmmword ptr [RAX],XMM1
1481c7474 MOV EAX,dword ptr [RAX + 0x10]
1481c7477 MOV dword ptr [RBP + 0x100],EAX
1481c747d LEA RCX,[RBP + 0x758]
1481c7484 CALL 0x140e86d70
1481c7489 NOP
1481c748a MOV RCX,qword ptr [RBP + 0x4b0]
1481c7491 TEST RCX,RCX
1481c7494 JZ 0x1481c749c
1481c7496 CALL 0x140e282f0
1481c749b NOP
1481c749c CVTTSS2SI EAX,dword ptr [R13 + 0x88]
1481c74a5 MOV dword ptr [RBP + 0x108],EAX
1481c74ab LEA RDX,[0x14cf76c80]
1481c74b2 LEA RCX,[RBP + 0x4c0]
1481c74b9 CALL 0x140cf7750
1481c74be NOP
1481c74bf LEA RDX,[RBP + 0x4c0]
1481c74c6 LEA RCX,[RBP + 0x770]
1481c74cd CALL 0x140ebb430
1481c74d2 MOVUPS XMM1,xmmword ptr [RBP + 0x110]
1481c74d9 MOVUPS XMM0,xmmword ptr [RAX]
1481c74dc MOVUPS xmmword ptr [RBP + 0x110],XMM0
1481c74e3 MOVUPS xmmword ptr [RAX],XMM1
1481c74e6 MOV EAX,dword ptr [RAX + 0x10]
1481c74e9 MOV dword ptr [RBP + 0x120],EAX
1481c74ef LEA RCX,[RBP + 0x770]
1481c74f6 CALL 0x140e86d70
1481c74fb NOP
1481c74fc MOV RCX,qword ptr [RBP + 0x4c0]
1481c7503 TEST RCX,RCX
1481c7506 JZ 0x1481c750e
1481c7508 CALL 0x140e282f0
1481c750d NOP
1481c750e MOV RCX,qword ptr [R14 + 0x10]
1481c7512 LEA RAX,[RBP + 0xf0]
1481c7519 CMP RAX,RCX
1481c751c JC 0x1481c758f
1481c751e MOVSXD RDX,dword ptr [R14 + 0x1c]
1481c7522 IMUL RAX,RDX,0x38
1481c7526 ADD RAX,RCX
1481c7529 LEA R8,[RBP + 0xf0]
1481c7530 CMP R8,RAX
1481c7533 JNC 0x1481c758f
1481c7535 MOVSXD RAX,dword ptr [R14 + 0x18]
1481c7539 MOV R9,qword ptr [RBP + 0x8c8]
1481c7540 MOV qword ptr [RSP + 0x48],0x38
1481c7549 MOV qword ptr [RSP + 0x40],RAX
1481c754e MOV qword ptr [RSP + 0x38],RDX
1481c7553 MOV qword ptr [RSP + 0x30],RCX
1481c7558 LEA RAX,[RBP + 0xf0]
1481c755f MOV qword ptr [RSP + 0x28],RAX
1481c7564 LEA RAX,[0x14bce6d80]
1481c756b MOV qword ptr [RSP + 0x20],RAX
1481c7570 MOV R8D,0x63e
1481c7576 LEA RDX,[0x14cf27ac0]
1481c757d LEA RCX,[0x14bce6eb8]
1481c7584 CALL 0x140f8dfd0
1481c7589 TEST AL,AL
1481c758b JZ 0x1481c758f
1481c758d NOP
1481c758e INT3
1481c758f MOVSXD RDI,dword ptr [R14 + 0x18]
1481c7593 LEA EAX,[RDI + 0x1]
1481c7596 MOV dword ptr [R14 + 0x18],EAX
1481c759a CMP EAX,dword ptr [R14 + 0x1c]
1481c759e JBE 0x1481c75ab
1481c75a0 MOV EDX,EDI
1481c75a2 LEA RCX,[R14 + 0x10]
1481c75a6 CALL 0x1481cab30
1481c75ab IMUL RCX,RDI,0x38
1481c75af ADD RCX,qword ptr [R14 + 0x10]
1481c75b3 LEA RDX,[RBP + 0xf0]
1481c75ba CALL 0x1481b3040
1481c75bf NOP
1481c75c0 LEA RCX,[RBP + 0xf0]
1481c75c7 CALL 0x148152600
1481c75cc MOV RBX,qword ptr [R14 + 0x10]
1481c75d0 MOVSXD RSI,dword ptr [R14 + 0x18]
1481c75d4 IMUL RDI,RSI,0x38
1481c75d8 ADD RDI,RBX
1481c75db NOP dword ptr [RAX + RAX*0x1]
1481c75e0 CMP dword ptr [R14 + 0x18],ESI
1481c75e4 JZ 0x1481c75fb
1481c75e6 MOV byte ptr [RSP + 0x54],0x0
1481c75eb LEA RCX,[RSP + 0x54]
1481c75f0 CALL 0x14bc1d170
1481c75f5 TEST AL,AL
1481c75f7 JZ 0x1481c75fb
1481c75f9 NOP
1481c75fa INT3
1481c75fb CMP RBX,RDI
1481c75fe JZ 0x1481c760a
1481c7600 ADD R15D,dword ptr [RBX + 0x18]
1481c7604 ADD RBX,0x38
1481c7608 JMP 0x1481c75e0
1481c760a MOVAPS XMM7,XMM8
1481c760e MOV RBX,qword ptr [R12 + 0x40]
1481c7613 MOVSXD RDI,dword ptr [R12 + 0x48]
1481c7618 SHL RDI,0x4
1481c761c ADD RDI,RBX
1481c761f CMP RBX,RDI
1481c7622 JZ 0x1481c7659
1481c7624 CMP dword ptr [RBX + 0x8],0x0
1481c7628 JZ 0x1481c762f
1481c762a MOV RCX,qword ptr [RBX]
1481c762d JMP 0x1481c7636
1481c762f LEA RCX,[0x14bce4e94]
1481c7636 LEA RDX,[0x14cf76c88]
1481c763d CALL 0x140d80770
1481c7642 TEST EAX,EAX
1481c7644 JZ 0x1481c7651
1481c7646 ADD RBX,0x10
1481c764a CMP RBX,RDI
1481c764d JNZ 0x1481c7624
1481c764f JMP 0x1481c7659
1481c7651 MOVSS XMM7,dword ptr [0x14bd17818]
1481c7659 MOV RBX,qword ptr [R12 + 0x40]
1481c765e MOVSXD RDI,dword ptr [R12 + 0x48]
1481c7663 SHL RDI,0x4
1481c7667 ADD RDI,RBX
1481c766a CMP RBX,RDI
1481c766d JZ 0x1481c76a5
1481c766f NOP
1481c7670 CMP dword ptr [RBX + 0x8],0x0
1481c7674 JZ 0x1481c767b
1481c7676 MOV RCX,qword ptr [RBX]
1481c7679 JMP 0x1481c7682
1481c767b LEA RCX,[0x14bce4e94]
1481c7682 LEA RDX,[0x14cf76c98]
1481c7689 CALL 0x140d80770
1481c768e TEST EAX,EAX
1481c7690 JZ 0x1481c769d
1481c7692 ADD RBX,0x10
1481c7696 CMP RBX,RDI
1481c7699 JNZ 0x1481c7670
1481c769b JMP 0x1481c76a5
1481c769d ADDSS XMM7,dword ptr [0x14bd774a8]
1481c76a5 COMISS XMM7,XMM8
1481c76a9 JBE 0x1481c78a8
1481c76af MOVAPS XMM6,XMM7
1481c76b2 SUBSS XMM6,XMM8
1481c76b7 MOVD XMM1,R15D
1481c76bc CVTDQ2PS XMM1,XMM1
1481c76bf MULSS XMM1,XMM6
1481c76c3 ADDSS XMM1,XMM1
1481c76c7 SUBSS XMM1,XMM12
1481c76cc CVTSS2SI EBX,XMM1
1481c76d0 SAR EBX,0x1
1481c76d2 TEST EBX,EBX
1481c76d4 JLE 0x1481c78a8
1481c76da LEA RCX,[RBP + 0x198]
1481c76e1 CALL 0x140e820a0
1481c76e6 NOP
1481c76e7 XOR ESI,ESI
1481c76e9 MOV dword ptr [RBP + 0x1b0],ESI
1481c76ef LEA RCX,[RBP + 0x1b8]
1481c76f6 CALL 0x140e820a0
1481c76fb NOP
1481c76fc LEA RDX,[0x14cf76cb0]
1481c7703 LEA RCX,[RBP + 0x2f0]
1481c770a CALL 0x140cf7750
1481c770f NOP
1481c7710 LEA RDX,[RBP + 0x2f0]
1481c7717 LEA RCX,[RBP + 0x788]
1481c771e CALL 0x140ebb430
1481c7723 MOVUPS XMM1,xmmword ptr [RBP + 0x198]
1481c772a MOVUPS XMM0,xmmword ptr [RAX]
1481c772d MOVUPS xmmword ptr [RBP + 0x198],XMM0
1481c7734 MOVUPS xmmword ptr [RAX],XMM1
1481c7737 MOV EAX,dword ptr [RAX + 0x10]
1481c773a MOV dword ptr [RBP + 0x1a8],EAX
1481c7740 LEA RCX,[RBP + 0x788]
1481c7747 CALL 0x140e86d70
1481c774c NOP
1481c774d MOV RCX,qword ptr [RBP + 0x2f0]
1481c7754 TEST RCX,RCX
1481c7757 JZ 0x1481c775f
1481c7759 CALL 0x140e282f0
1481c775e NOP
1481c775f MOV dword ptr [RBP + 0x1b0],EBX
1481c7765 MULSS XMM6,dword ptr [0x14bd1786c]
1481c776d ADDSS XMM6,XMM6
1481c7771 SUBSS XMM6,XMM12
1481c7776 CVTSS2SI R8D,XMM6
1481c777b SAR R8D,0x1
1481c777e LEA RDX,[0x14cf76cd0]
1481c7785 LEA RCX,[RBP + 0x300]
1481c778c CALL 0x140d169d0
1481c7791 OR dword ptr [RSP + 0x50],0x100
1481c7799 LEA RDX,[RBP + 0x300]
1481c77a0 LEA RCX,[RBP + 0x7a0]
1481c77a7 CALL 0x140ebb430
1481c77ac MOVUPS XMM1,xmmword ptr [RBP + 0x1b8]
1481c77b3 MOVUPS XMM0,xmmword ptr [RAX]
1481c77b6 MOVUPS xmmword ptr [RBP + 0x1b8],XMM0
1481c77bd MOVUPS xmmword ptr [RAX],XMM1
1481c77c0 MOV EAX,dword ptr [RAX + 0x10]
1481c77c3 MOV dword ptr [RBP + 0x1c8],EAX
1481c77c9 LEA RCX,[RBP + 0x7a0]
1481c77d0 CALL 0x140e86d70
1481c77d5 NOP
1481c77d6 MOV RCX,qword ptr [RBP + 0x300]
1481c77dd TEST RCX,RCX
1481c77e0 JZ 0x1481c77e8
1481c77e2 CALL 0x140e282f0
1481c77e7 NOP
1481c77e8 MOV RCX,qword ptr [R14 + 0x10]
1481c77ec LEA RAX,[RBP + 0x198]
1481c77f3 CMP RAX,RCX
1481c77f6 JC 0x1481c7869
1481c77f8 MOVSXD RDX,dword ptr [R14 + 0x1c]
1481c77fc IMUL RAX,RDX,0x38
1481c7800 ADD RAX,RCX
1481c7803 LEA R8,[RBP + 0x198]
1481c780a CMP R8,RAX
1481c780d JNC 0x1481c7869
1481c780f MOVSXD RAX,dword ptr [R14 + 0x18]
1481c7813 MOV R9,qword ptr [RBP + 0x8c8]
1481c781a MOV qword ptr [RSP + 0x48],0x38
1481c7823 MOV qword ptr [RSP + 0x40],RAX
1481c7828 MOV qword ptr [RSP + 0x38],RDX
1481c782d MOV qword ptr [RSP + 0x30],RCX
1481c7832 LEA RAX,[RBP + 0x198]
1481c7839 MOV qword ptr [RSP + 0x28],RAX
1481c783e LEA RAX,[0x14bce6d80]
1481c7845 MOV qword ptr [RSP + 0x20],RAX
1481c784a MOV R8D,0x63e
1481c7850 LEA RDX,[0x14cf27ac0]
1481c7857 LEA RCX,[0x14bce6eb8]
1481c785e CALL 0x140f8dfd0
1481c7863 TEST AL,AL
1481c7865 JZ 0x1481c7869
1481c7867 NOP
1481c7868 INT3
1481c7869 MOVSXD RDI,dword ptr [R14 + 0x18]
1481c786d LEA EAX,[RDI + 0x1]
1481c7870 MOV dword ptr [R14 + 0x18],EAX
1481c7874 CMP EAX,dword ptr [R14 + 0x1c]
1481c7878 JBE 0x1481c7885
1481c787a MOV EDX,EDI
1481c787c LEA RCX,[R14 + 0x10]
1481c7880 CALL 0x1481cab30
1481c7885 IMUL RCX,RDI,0x38
1481c7889 ADD RCX,qword ptr [R14 + 0x10]
1481c788d LEA RDX,[RBP + 0x198]
1481c7894 CALL 0x1481b3040
1481c7899 NOP
1481c789a LEA RCX,[RBP + 0x198]
1481c78a1 CALL 0x148152600
1481c78a6 JMP 0x1481c78aa
1481c78a8 XOR ESI,ESI
1481c78aa MOVD XMM1,R15D
1481c78af CVTDQ2PS XMM1,XMM1
1481c78b2 MULSS XMM1,XMM7
1481c78b6 ADDSS XMM1,XMM1
1481c78ba SUBSS XMM1,XMM12
1481c78bf CVTSS2SI ECX,XMM1
1481c78c3 SAR ECX,0x1
1481c78c5 MOV dword ptr [R14 + 0x20],ECX
1481c78c9 MOV EDI,dword ptr [R13 + 0x40]
1481c78cd ADD EDI,ECX
1481c78cf MOV dword ptr [RSP + 0x58],EDI
1481c78d3 MOV R13D,dword ptr [R13 + 0x50]
1481c78d7 MOV R15D,0xffffffff
1481c78dd CMP R13D,0x14
1481c78e1 JGE 0x1481c7edd
1481c78e7 MOV RCX,qword ptr GS:[0x58]
1481c78f0 MOV EDX,0x908c
1481c78f5 LEA R12D,[R13 + -0x1]
1481c78f9 LEA R8,[0x14bce6ef0]
1481c7900 MOV EAX,dword ptr [0x14ee952f8]
1481c7906 MOV RCX,qword ptr [RCX + RAX*0x8]
1481c790a MOV EAX,dword ptr [RDX + RCX*0x1]
1481c790d CMP dword ptr [0x14edbff0c],EAX
1481c7913 JLE 0x1481c79e9
1481c7919 LEA RCX,[0x14edbff0c]
1481c7920 CALL 0x14b87ff78
1481c7925 CMP dword ptr [0x14edbff0c],-0x1
1481c792c JNZ 0x1481c79e2
1481c7932 MOVDQA XMM6,xmmword ptr [0x14cf77870]
1481c793a MOVDQA XMM7,xmmword ptr [0x14cf77880]
1481c7942 MOVDQA XMM8,xmmword ptr [0x14cf77890]
1481c794b MOVDQA XMM9,xmmword ptr [0x14cf778a0]
1481c7954 MOVDQA XMM10,xmmword ptr [0x14cf778b0]
1481c795d MOV qword ptr [0x14e9f1210],RSI
1481c7964 MOV dword ptr [0x14e9f1218],0x14
1481c796e XOR R8D,R8D
1481c7971 LEA EDX,[R8 + 0x14]
1481c7975 LEA RCX,[0x14e9f1210]
1481c797c CALL 0x140d20ea0
1481c7981 MOV RAX,qword ptr [0x14e9f1210]
1481c7988 MOVDQU xmmword ptr [RBP + 0x7c0],XMM6
1481c7990 MOVUPS xmmword ptr [RAX],XMM6
1481c7993 MOVDQU xmmword ptr [RBP + 0x7d0],XMM7
1481c799b MOVUPS xmmword ptr [RAX + 0x10],XMM7
1481c799f MOVDQU xmmword ptr [RBP + 0x7e0],XMM8
1481c79a8 MOVUPS xmmword ptr [RAX + 0x20],XMM8
1481c79ad MOVDQU xmmword ptr [RBP + 0x7f0],XMM9
1481c79b6 MOVUPS xmmword ptr [RAX + 0x30],XMM9
1481c79bb MOVDQU xmmword ptr [RBP + 0x800],XMM10
1481c79c4 MOVUPS xmmword ptr [RAX + 0x40],XMM10
1481c79c9 LEA RCX,[0x14ba6bd50]
1481c79d0 CALL 0x14b87fc50
1481c79d5 NOP
1481c79d6 LEA RCX,[0x14edbff0c]
1481c79dd CALL 0x14b87ff10
1481c79e2 LEA R8,[0x14bce6ef0]
1481c79e9 TEST R13D,R13D
1481c79ec JLE 0x1481c7a68
1481c79f2 MOVSXD RDX,dword ptr [0x14e9f1218]
1481c79f9 CMP R13D,EDX
1481c79fc JG 0x1481c7a68
1481c79fe LEA EAX,[RDX + -0x1]
1481c7a01 CMP R12D,EAX
1481c7a04 CMOVL EAX,R12D
1481c7a08 MOV EBX,ESI
1481c7a0a TEST EAX,EAX
1481c7a0c CMOVG EBX,EAX
1481c7a0f MOV ECX,EBX
1481c7a11 NOT ECX
1481c7a13 SHR ECX,0x1f
1481c7a16 MOV EAX,ESI
1481c7a18 CMP EBX,EDX
1481c7a1a CMOVL EAX,ECX
1481c7a1d TEST EAX,EAX
1481c7a1f JNZ 0x1481c7a59
1481c7a21 MOVSXD RCX,EBX
1481c7a24 MOV R9,qword ptr [RBP + 0x8c8]
1481c7a2b MOV qword ptr [RSP + 0x30],RDX
1481c7a30 MOV qword ptr [RSP + 0x28],RCX
1481c7a35 MOV qword ptr [RSP + 0x20],R8
1481c7a3a MOV R8D,0x303
1481c7a40 LEA RDX,[0x14cf27ac0]
1481c7a47 LEA RCX,[0x14bce6f68]
1481c7a4e CALL 0x140f8dfd0
1481c7a53 TEST AL,AL
1481c7a55 JZ 0x1481c7a59
1481c7a57 NOP
1481c7a58 INT3
1481c7a59 MOVSXD RCX,EBX
1481c7a5c MOV RAX,qword ptr [0x14e9f1210]
1481c7a63 MOV EDX,dword ptr [RAX + RCX*0x4]
1481c7a66 JMP 0x1481c7a6d
1481c7a68 MOV EDX,0xf423f
1481c7a6d CMP EDI,EDX
1481c7a6f JL 0x1481c7ed6
1481c7a75 SUB EDI,EDX
1481c7a77 MOV dword ptr [RSP + 0x58],EDI
1481c7a7b INC R13D
1481c7a7e INC R12D
1481c7a81 MOV qword ptr [RSP + 0x64],0x0
1481c7a8a MOV dword ptr [RSP + 0x6c],ESI
1481c7a8e MOV dword ptr [RSP + 0x60],R13D
1481c7a93 MOV dword ptr [RSP + 0x70],EDX
1481c7a97 MOV R8D,R13D
1481c7a9a LEA RDX,[RBP + 0x4e0]
1481c7aa1 MOV RBX,qword ptr [RBP + 0x2d0]
1481c7aa8 MOV RCX,RBX
1481c7aab CALL 0x1481c3000
1481c7ab0 MOV RCX,qword ptr [RAX]
1481c7ab3 MOV qword ptr [RSP + 0x64],RCX
1481c7ab8 CMP qword ptr [RBX + 0x68],0x0
1481c7abd JZ 0x1481c7e02
1481c7ac3 MOV R8D,R13D
1481c7ac6 LEA RDX,[0x14cf71488]
1481c7acd LEA RCX,[RBP + 0x2e0]
1481c7ad4 CALL 0x140d169d0
1481c7ad9 OR dword ptr [RSP + 0x50],0x2
1481c7ade MOV RBX,qword ptr [RBX + 0x68]
1481c7ae2 LEA RDX,[0x14bce4e94]
1481c7ae9 CMP dword ptr [RBP + 0x2e8],0x0
1481c7af0 CMOVNZ RDX,qword ptr [RBP + 0x2e0]
1481c7af8 MOV R8D,0x1
1481c7afe LEA RCX,[RBP + 0x4d8]
1481c7b05 CALL 0x1411a7b80
1481c7b0a MOV R9B,0x1
1481c7b0d LEA R8,[0x14bce4e94]
1481c7b14 MOV RDX,qword ptr [RAX]
1481c7b17 MOV RCX,RBX
1481c7b1a CALL 0x1481b14e0
1481c7b1f MOV RSI,RAX
1481c7b22 TEST RAX,RAX
1481c7b25 JZ 0x1481c7dee
1481c7b2b MOV ECX,dword ptr [RAX + 0x10]
1481c7b2e MOV dword ptr [RSP + 0x6c],ECX
1481c7b32 CMP dword ptr [RAX + 0x10],0x0
1481c7b36 JLE 0x1481c7dee
1481c7b3c LEA RCX,[RBP + -0x80]
1481c7b40 CALL 0x140e820a0
1481c7b45 NOP
1481c7b46 MOV dword ptr [RBP + -0x68],0x0
1481c7b4d LEA RCX,[RBP + -0x60]
1481c7b51 CALL 0x140e820a0
1481c7b56 MOV byte ptr [RBP + -0x48],0x0
1481c7b5a LEA RDX,[0x14cf76ce0]
1481c7b61 LEA RCX,[RBP + 0x310]
1481c7b68 CALL 0x140cf7750
1481c7b6d NOP
1481c7b6e LEA RDX,[RBP + 0x310]
1481c7b75 LEA RCX,[RBP + 0x4e8]
1481c7b7c CALL 0x140ebb430
1481c7b81 MOVUPS XMM1,xmmword ptr [RBP + -0x80]
1481c7b85 MOVUPS XMM0,xmmword ptr [RAX]
1481c7b88 MOVUPS xmmword ptr [RBP + -0x80],XMM0
1481c7b8c MOVUPS xmmword ptr [RAX],XMM1
1481c7b8f MOV EAX,dword ptr [RAX + 0x10]
1481c7b92 MOV dword ptr [RBP + -0x70],EAX
1481c7b95 MOV RBX,qword ptr [RBP + 0x4f0]
1481c7b9c TEST RBX,RBX
1481c7b9f JZ 0x1481c7bd2
1481c7ba1 MOV EAX,R15D
1481c7ba4 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c7ba9 CMP EAX,0x1
1481c7bac JNZ 0x1481c7bd2
1481c7bae MOV RAX,qword ptr [RBX]
1481c7bb1 MOV RCX,RBX
1481c7bb4 CALL qword ptr [RAX]
1481c7bb6 MOV EAX,R15D
1481c7bb9 XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c7bbe CMP EAX,0x1
1481c7bc1 JNZ 0x1481c7bd2
1481c7bc3 MOV RAX,qword ptr [RBX]
1481c7bc6 MOV EDX,0x1
1481c7bcb MOV RCX,RBX
1481c7bce CALL qword ptr [RAX + 0x8]
1481c7bd1 NOP
1481c7bd2 MOV RCX,qword ptr [RBP + 0x310]
1481c7bd9 TEST RCX,RCX
1481c7bdc JZ 0x1481c7be4
1481c7bde CALL 0x140e282f0
1481c7be3 NOP
1481c7be4 MOV EAX,dword ptr [RSI + 0x10]
1481c7be7 MOV dword ptr [RBP + -0x68],EAX
1481c7bea MOV R8D,R13D
1481c7bed LEA RDX,[0x14cf76cf8]
1481c7bf4 LEA RCX,[RBP + 0x320]
1481c7bfb CALL 0x140d169d0
1481c7c00 OR dword ptr [RSP + 0x50],0x4
1481c7c05 LEA RDX,[RBP + 0x320]
1481c7c0c LEA RCX,[RBP + 0x500]
1481c7c13 CALL 0x140ebb430
1481c7c18 MOVUPS XMM1,xmmword ptr [RBP + -0x60]
1481c7c1c MOVUPS XMM0,xmmword ptr [RAX]
1481c7c1f MOVUPS xmmword ptr [RBP + -0x60],XMM0
1481c7c23 MOVUPS xmmword ptr [RAX],XMM1
1481c7c26 MOV EAX,dword ptr [RAX + 0x10]
1481c7c29 MOV dword ptr [RBP + -0x50],EAX
1481c7c2c MOV RBX,qword ptr [RBP + 0x508]
1481c7c33 TEST RBX,RBX
1481c7c36 JZ 0x1481c7c69
1481c7c38 MOV EAX,R15D
1481c7c3b XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c7c40 CMP EAX,0x1
1481c7c43 JNZ 0x1481c7c69
1481c7c45 MOV RAX,qword ptr [RBX]
1481c7c48 MOV RCX,RBX
1481c7c4b CALL qword ptr [RAX]
1481c7c4d MOV EAX,R15D
1481c7c50 XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c7c55 CMP EAX,0x1
1481c7c58 JNZ 0x1481c7c69
1481c7c5a MOV RAX,qword ptr [RBX]
1481c7c5d MOV EDX,0x1
1481c7c62 MOV RCX,RBX
1481c7c65 CALL qword ptr [RAX + 0x8]
1481c7c68 NOP
1481c7c69 MOV RCX,qword ptr [RBP + 0x320]
1481c7c70 TEST RCX,RCX
1481c7c73 JZ 0x1481c7c7b
1481c7c75 CALL 0x140e282f0
1481c7c7a NOP
1481c7c7b MOV byte ptr [RBP + -0x48],0x1
1481c7c7f MOV RCX,qword ptr [R14 + 0x28]
1481c7c83 LEA RAX,[RBP + -0x80]
1481c7c87 CMP RAX,RCX
1481c7c8a JC 0x1481c7cfa
1481c7c8c MOVSXD RDX,dword ptr [R14 + 0x34]
1481c7c90 MOV RAX,RDX
1481c7c93 SHL RAX,0x6
1481c7c97 ADD RAX,RCX
1481c7c9a LEA R8,[RBP + -0x80]
1481c7c9e CMP R8,RAX
1481c7ca1 JNC 0x1481c7cfa
1481c7ca3 MOVSXD RAX,dword ptr [R14 + 0x30]
1481c7ca7 MOV R9,qword ptr [RBP + 0x8c8]
1481c7cae MOV qword ptr [RSP + 0x48],0x40
1481c7cb7 MOV qword ptr [RSP + 0x40],RAX
1481c7cbc MOV qword ptr [RSP + 0x38],RDX
1481c7cc1 MOV qword ptr [RSP + 0x30],RCX
1481c7cc6 LEA RAX,[RBP + -0x80]
1481c7cca MOV qword ptr [RSP + 0x28],RAX
1481c7ccf LEA RAX,[0x14bce6d80]
1481c7cd6 MOV qword ptr [RSP + 0x20],RAX
1481c7cdb MOV R8D,0x63e
1481c7ce1 LEA RDX,[0x14cf27ac0]
1481c7ce8 LEA RCX,[0x14bce6eb8]
1481c7cef CALL 0x140f8dfd0
1481c7cf4 TEST AL,AL
1481c7cf6 JZ 0x1481c7cfa
1481c7cf8 NOP
1481c7cf9 INT3
1481c7cfa MOVSXD RDI,dword ptr [R14 + 0x30]
1481c7cfe LEA EAX,[RDI + 0x1]
1481c7d01 MOV dword ptr [R14 + 0x30],EAX
1481c7d05 CMP EAX,dword ptr [R14 + 0x34]
1481c7d09 JBE 0x1481c7d16
1481c7d0b MOV EDX,EDI
1481c7d0d LEA RCX,[R14 + 0x28]
1481c7d11 CALL 0x1481caa90
1481c7d16 MOV RCX,RDI
1481c7d19 SHL RCX,0x6
1481c7d1d ADD RCX,qword ptr [R14 + 0x28]
1481c7d21 MOV RAX,qword ptr [RBP + -0x80]
1481c7d25 MOV qword ptr [RCX],RAX
1481c7d28 MOV RAX,qword ptr [RBP + -0x78]
1481c7d2c MOV qword ptr [RCX + 0x8],RAX
1481c7d30 MOV RAX,qword ptr [RBP + -0x78]
1481c7d34 TEST RAX,RAX
1481c7d37 JZ 0x1481c7d3d
1481c7d39 INC.LOCK dword ptr [RAX + 0x8]
1481c7d3d MOV EAX,dword ptr [RBP + -0x70]
1481c7d40 MOV dword ptr [RCX + 0x10],EAX
1481c7d43 MOV EAX,dword ptr [RBP + -0x68]
1481c7d46 MOV dword ptr [RCX + 0x18],EAX
1481c7d49 MOV RAX,qword ptr [RBP + -0x60]
1481c7d4d MOV qword ptr [RCX + 0x20],RAX
1481c7d51 MOV RAX,qword ptr [RBP + -0x58]
1481c7d55 MOV qword ptr [RCX + 0x28],RAX
1481c7d59 MOV RAX,qword ptr [RBP + -0x58]
1481c7d5d TEST RAX,RAX
1481c7d60 JZ 0x1481c7d66
1481c7d62 INC.LOCK dword ptr [RAX + 0x8]
1481c7d66 MOV EAX,dword ptr [RBP + -0x50]
1481c7d69 MOV dword ptr [RCX + 0x30],EAX
1481c7d6c MOVZX EAX,byte ptr [RBP + -0x48]
1481c7d70 MOV byte ptr [RCX + 0x38],AL
1481c7d73 MOV EAX,dword ptr [RSI + 0x10]
1481c7d76 ADD dword ptr [R14 + 0x3c],EAX
1481c7d7a MOV RBX,qword ptr [RBP + -0x58]
1481c7d7e TEST RBX,RBX
1481c7d81 JZ 0x1481c7db4
1481c7d83 MOV EAX,R15D
1481c7d86 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c7d8b CMP EAX,0x1
1481c7d8e JNZ 0x1481c7db4
1481c7d90 MOV RAX,qword ptr [RBX]
1481c7d93 MOV RCX,RBX
1481c7d96 CALL qword ptr [RAX]
1481c7d98 MOV EAX,R15D
1481c7d9b XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c7da0 CMP EAX,0x1
1481c7da3 JNZ 0x1481c7db4
1481c7da5 MOV RAX,qword ptr [RBX]
1481c7da8 MOV EDX,0x1
1481c7dad MOV RCX,RBX
1481c7db0 CALL qword ptr [RAX + 0x8]
1481c7db3 NOP
1481c7db4 MOV RBX,qword ptr [RBP + -0x78]
1481c7db8 TEST RBX,RBX
1481c7dbb JZ 0x1481c7dee
1481c7dbd MOV EAX,R15D
1481c7dc0 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c7dc5 CMP EAX,0x1
1481c7dc8 JNZ 0x1481c7dee
1481c7dca MOV RAX,qword ptr [RBX]
1481c7dcd MOV RCX,RBX
1481c7dd0 CALL qword ptr [RAX]
1481c7dd2 MOV EAX,R15D
1481c7dd5 XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c7dda CMP EAX,0x1
1481c7ddd JNZ 0x1481c7dee
1481c7ddf MOV RAX,qword ptr [RBX]
1481c7de2 MOV EDX,0x1
1481c7de7 MOV RCX,RBX
1481c7dea CALL qword ptr [RAX + 0x8]
1481c7ded NOP
1481c7dee MOV RCX,qword ptr [RBP + 0x2e0]
1481c7df5 TEST RCX,RCX
1481c7df8 JZ 0x1481c7e00
1481c7dfa CALL 0x140e282f0
1481c7dff NOP
1481c7e00 XOR ESI,ESI
1481c7e02 MOV RDX,qword ptr [R14 + 0x40]
1481c7e06 LEA RAX,[RSP + 0x60]
1481c7e0b CMP RAX,RDX
1481c7e0e JC 0x1481c7e7e
1481c7e10 MOVSXD R8,dword ptr [R14 + 0x4c]
1481c7e14 LEA RAX,[R8 + R8*0x4]
1481c7e18 LEA RCX,[RDX + RAX*0x4]
1481c7e1c LEA RAX,[RSP + 0x60]
1481c7e21 CMP RAX,RCX
1481c7e24 JNC 0x1481c7e7e
1481c7e26 MOVSXD RAX,dword ptr [R14 + 0x48]
1481c7e2a MOV R9,qword ptr [RBP + 0x8c8]
1481c7e31 MOV qword ptr [RSP + 0x48],0x14
1481c7e3a MOV qword ptr [RSP + 0x40],RAX
1481c7e3f MOV qword ptr [RSP + 0x38],R8
1481c7e44 MOV qword ptr [RSP + 0x30],RDX
1481c7e49 LEA RAX,[RSP + 0x60]
1481c7e4e MOV qword ptr [RSP + 0x28],RAX
1481c7e53 LEA RAX,[0x14bce6d80]
1481c7e5a MOV qword ptr [RSP + 0x20],RAX
1481c7e5f MOV R8D,0x63e
1481c7e65 LEA RDX,[0x14cf27ac0]
1481c7e6c LEA RCX,[0x14bce6eb8]
1481c7e73 CALL 0x140f8dfd0
1481c7e78 TEST AL,AL
1481c7e7a JZ 0x1481c7e7e
1481c7e7c NOP
1481c7e7d INT3
1481c7e7e MOVSXD RDI,dword ptr [R14 + 0x48]
1481c7e82 LEA EAX,[RDI + 0x1]
1481c7e85 MOV dword ptr [R14 + 0x48],EAX
1481c7e89 CMP EAX,dword ptr [R14 + 0x4c]
1481c7e8d JBE 0x1481c7e9a
1481c7e8f MOV EDX,EDI
1481c7e91 LEA RCX,[R14 + 0x40]
1481c7e95 CALL 0x1481ca890
1481c7e9a LEA RDX,[RDI + RDI*0x4]
1481c7e9e MOV RCX,qword ptr [R14 + 0x40]
1481c7ea2 MOVUPS XMM0,xmmword ptr [RSP + 0x60]
1481c7ea7 MOVUPS xmmword ptr [RCX + RDX*0x4],XMM0
1481c7eab MOV EAX,dword ptr [RSP + 0x70]
1481c7eaf MOV dword ptr [RCX + RDX*0x4 + 0x10],EAX
1481c7eb3 CMP R12D,0x13
1481c7eb7 MOV RCX,qword ptr GS:[0x58]
1481c7ec0 MOV EDI,dword ptr [RSP + 0x58]
1481c7ec4 MOV EDX,0x908c
1481c7ec9 LEA R8,[0x14bce6ef0]
1481c7ed0 JL 0x1481c7900
1481c7ed6 MOV R12,qword ptr [RBP + 0x2d8]
1481c7edd MOV EAX,0x1b4e81b5
1481c7ee2 IMUL dword ptr [R12]
1481c7ee6 SAR EDX,0x5
1481c7ee9 MOV EAX,EDX
1481c7eeb SHR EAX,0x1f
1481c7eee ADD EDX,EAX
1481c7ef0 MOVD XMM1,EDX
1481c7ef4 CVTDQ2PS XMM1,XMM1
1481c7ef7 MULSS XMM1,XMM11
1481c7efc ADDSS XMM1,XMM1
1481c7f00 SUBSS XMM1,XMM12
1481c7f05 CVTSS2SI ESI,XMM1
1481c7f09 SAR ESI,0x1
1481c7f0b TEST ESI,ESI
1481c7f0d JLE 0x1481c8116
1481c7f13 LEA RCX,[RBP + 0x1d0]
1481c7f1a CALL 0x140e820a0
1481c7f1f NOP
1481c7f20 MOV dword ptr [RBP + 0x1e8],0x0
1481c7f2a LEA RCX,[RBP + 0x1f0]
1481c7f31 CALL 0x140e820a0
1481c7f36 MOV byte ptr [RBP + 0x208],0x0
1481c7f3d LEA RDX,[0x14cf76b98]
1481c7f44 LEA RCX,[RBP + 0x330]
1481c7f4b CALL 0x140cf7750
1481c7f50 NOP
1481c7f51 LEA RDX,[RBP + 0x330]
1481c7f58 LEA RCX,[RBP + 0x518]
1481c7f5f CALL 0x140ebb430
1481c7f64 MOVUPS XMM1,xmmword ptr [RBP + 0x1d0]
1481c7f6b MOVUPS XMM0,xmmword ptr [RAX]
1481c7f6e MOVUPS xmmword ptr [RBP + 0x1d0],XMM0
1481c7f75 MOVUPS xmmword ptr [RAX],XMM1
1481c7f78 MOV EAX,dword ptr [RAX + 0x10]
1481c7f7b MOV dword ptr [RBP + 0x1e0],EAX
1481c7f81 LEA RCX,[RBP + 0x518]
1481c7f88 CALL 0x140e86d70
1481c7f8d NOP
1481c7f8e MOV RCX,qword ptr [RBP + 0x330]
1481c7f95 TEST RCX,RCX
1481c7f98 JZ 0x1481c7fa0
1481c7f9a CALL 0x140e282f0
1481c7f9f NOP
1481c7fa0 MOV dword ptr [RBP + 0x1e8],ESI
1481c7fa6 MOV R8D,dword ptr [R12]
1481c7faa LEA RDX,[0x14cf76bd0]
1481c7fb1 LEA RCX,[RBP + 0x460]
1481c7fb8 CALL 0x140d169d0
1481c7fbd OR dword ptr [RSP + 0x50],0x80
1481c7fc5 LEA RDX,[RBP + 0x460]
1481c7fcc LEA RCX,[RBP + 0x530]
1481c7fd3 CALL 0x140ebb430
1481c7fd8 MOVUPS XMM1,xmmword ptr [RBP + 0x1f0]
1481c7fdf MOVUPS XMM0,xmmword ptr [RAX]
1481c7fe2 MOVUPS xmmword ptr [RBP + 0x1f0],XMM0
1481c7fe9 MOVUPS xmmword ptr [RAX],XMM1
1481c7fec MOV EAX,dword ptr [RAX + 0x10]
1481c7fef MOV dword ptr [RBP + 0x200],EAX
1481c7ff5 MOV RBX,qword ptr [RBP + 0x538]
1481c7ffc TEST RBX,RBX
1481c7fff JZ 0x1481c8032
1481c8001 MOV EAX,R15D
1481c8004 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c8009 CMP EAX,0x1
1481c800c JNZ 0x1481c8032
1481c800e MOV RAX,qword ptr [RBX]
1481c8011 MOV RCX,RBX
1481c8014 CALL qword ptr [RAX]
1481c8016 MOV EAX,R15D
1481c8019 XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c801e CMP EAX,0x1
1481c8021 JNZ 0x1481c8032
1481c8023 MOV RAX,qword ptr [RBX]
1481c8026 MOV EDX,0x1
1481c802b MOV RCX,RBX
1481c802e CALL qword ptr [RAX + 0x8]
1481c8031 NOP
1481c8032 MOV RCX,qword ptr [RBP + 0x460]
1481c8039 TEST RCX,RCX
1481c803c JZ 0x1481c8044
1481c803e CALL 0x140e282f0
1481c8043 NOP
1481c8044 MOV byte ptr [RBP + 0x208],0x0
1481c804b MOV RCX,qword ptr [R14 + 0x28]
1481c804f LEA RAX,[RBP + 0x1d0]
1481c8056 CMP RAX,RCX
1481c8059 JC 0x1481c80d3
1481c805f MOVSXD RDX,dword ptr [R14 + 0x34]
1481c8063 MOV RAX,RDX
1481c8066 SHL RAX,0x6
1481c806a ADD RAX,RCX
1481c806d LEA R8,[RBP + 0x1d0]
1481c8074 CMP R8,RAX
1481c8077 JNC 0x1481c80d3
1481c8079 MOVSXD RAX,dword ptr [R14 + 0x30]
1481c807d MOV R9,qword ptr [RBP + 0x8c8]
1481c8084 MOV qword ptr [RSP + 0x48],0x40
1481c808d MOV qword ptr [RSP + 0x40],RAX
1481c8092 MOV qword ptr [RSP + 0x38],RDX
1481c8097 MOV qword ptr [RSP + 0x30],RCX
1481c809c LEA RAX,[RBP + 0x1d0]
1481c80a3 MOV qword ptr [RSP + 0x28],RAX
1481c80a8 LEA RAX,[0x14bce6d80]
1481c80af MOV qword ptr [RSP + 0x20],RAX
1481c80b4 MOV R8D,0x63e
1481c80ba LEA RDX,[0x14cf27ac0]
1481c80c1 LEA RCX,[0x14bce6eb8]
1481c80c8 CALL 0x140f8dfd0
1481c80cd TEST AL,AL
1481c80cf JZ 0x1481c80d3
1481c80d1 NOP
1481c80d2 INT3
1481c80d3 MOVSXD RDI,dword ptr [R14 + 0x30]
1481c80d7 LEA EAX,[RDI + 0x1]
1481c80da MOV dword ptr [R14 + 0x30],EAX
1481c80de CMP EAX,dword ptr [R14 + 0x34]
1481c80e2 JBE 0x1481c80ef
1481c80e4 MOV EDX,EDI
1481c80e6 LEA RCX,[R14 + 0x28]
1481c80ea CALL 0x1481caa90
1481c80ef MOV RCX,RDI
1481c80f2 SHL RCX,0x6
1481c80f6 ADD RCX,qword ptr [R14 + 0x28]
1481c80fa LEA RDX,[RBP + 0x1d0]
1481c8101 CALL 0x1481b2fe0
1481c8106 ADD dword ptr [R14 + 0x3c],ESI
1481c810a LEA RCX,[RBP + 0x1d0]
1481c8111 CALL 0x148152560
1481c8116 MOV EAX,0x51eb851f
1481c811b IMUL dword ptr [R12 + 0x10]
1481c8120 SAR EDX,0x7
1481c8123 MOV EAX,EDX
1481c8125 SHR EAX,0x1f
1481c8128 ADD EDX,EAX
1481c812a MOVD XMM1,EDX
1481c812e CVTDQ2PS XMM1,XMM1
1481c8131 MULSS XMM1,XMM11
1481c8136 ADDSS XMM1,XMM1
1481c813a SUBSS XMM1,XMM12
1481c813f CVTSS2SI ESI,XMM1
1481c8143 SAR ESI,0x1
1481c8145 TEST ESI,ESI
1481c8147 JLE 0x1481c83f3
1481c814d LEA RCX,[RBP + -0x40]
1481c8151 CALL 0x140e820a0
1481c8156 NOP
1481c8157 MOV dword ptr [RBP + -0x28],0x0
1481c815e LEA RCX,[RBP + -0x20]
1481c8162 CALL 0x140e820a0
1481c8167 MOV byte ptr [RBP + -0x8],0x0
1481c816b LEA RDX,[0x14cf76d08]
1481c8172 LEA RCX,[RBP + 0x350]
1481c8179 CALL 0x140cf7750
1481c817e NOP
1481c817f LEA RDX,[RBP + 0x350]
1481c8186 LEA RCX,[RBP + 0x548]
1481c818d CALL 0x140ebb430
1481c8192 MOVUPS XMM1,xmmword ptr [RBP + -0x40]
1481c8196 MOVUPS XMM0,xmmword ptr [RAX]
1481c8199 MOVUPS xmmword ptr [RBP + -0x40],XMM0
1481c819d MOVUPS xmmword ptr [RAX],XMM1
1481c81a0 MOV EAX,dword ptr [RAX + 0x10]
1481c81a3 MOV dword ptr [RBP + -0x30],EAX
1481c81a6 MOV RBX,qword ptr [RBP + 0x550]
1481c81ad TEST RBX,RBX
1481c81b0 JZ 0x1481c81e3
1481c81b2 MOV EAX,R15D
1481c81b5 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c81ba CMP EAX,0x1
1481c81bd JNZ 0x1481c81e3
1481c81bf MOV RAX,qword ptr [RBX]
1481c81c2 MOV RCX,RBX
1481c81c5 CALL qword ptr [RAX]
1481c81c7 MOV EAX,R15D
1481c81ca XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c81cf CMP EAX,0x1
1481c81d2 JNZ 0x1481c81e3
1481c81d4 MOV RAX,qword ptr [RBX]
1481c81d7 MOV EDX,0x1
1481c81dc MOV RCX,RBX
1481c81df CALL qword ptr [RAX + 0x8]
1481c81e2 NOP
1481c81e3 MOV RCX,qword ptr [RBP + 0x350]
1481c81ea TEST RCX,RCX
1481c81ed JZ 0x1481c81f5
1481c81ef CALL 0x140e282f0
1481c81f4 NOP
1481c81f5 MOV dword ptr [RBP + -0x28],ESI
1481c81f8 MOV R8D,dword ptr [R12 + 0x10]
1481c81fd LEA RDX,[0x14cf76d20]
1481c8204 LEA RCX,[RBP + 0x360]
1481c820b CALL 0x140d169d0
1481c8210 OR dword ptr [RSP + 0x50],0x8
1481c8215 LEA RDX,[RBP + 0x360]
1481c821c LEA RCX,[RBP + 0x560]
1481c8223 CALL 0x140ebb430
1481c8228 MOVUPS XMM1,xmmword ptr [RBP + -0x20]
1481c822c MOVUPS XMM0,xmmword ptr [RAX]
1481c822f MOVUPS xmmword ptr [RBP + -0x20],XMM0
1481c8233 MOVUPS xmmword ptr [RAX],XMM1
1481c8236 MOV EAX,dword ptr [RAX + 0x10]
1481c8239 MOV dword ptr [RBP + -0x10],EAX
1481c823c MOV RBX,qword ptr [RBP + 0x568]
1481c8243 TEST RBX,RBX
1481c8246 JZ 0x1481c8279
1481c8248 MOV EAX,R15D
1481c824b XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c8250 CMP EAX,0x1
1481c8253 JNZ 0x1481c8279
1481c8255 MOV RAX,qword ptr [RBX]
1481c8258 MOV RCX,RBX
1481c825b CALL qword ptr [RAX]
1481c825d MOV EAX,R15D
1481c8260 XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c8265 CMP EAX,0x1
1481c8268 JNZ 0x1481c8279
1481c826a MOV RAX,qword ptr [RBX]
1481c826d MOV EDX,0x1
1481c8272 MOV RCX,RBX
1481c8275 CALL qword ptr [RAX + 0x8]
1481c8278 NOP
1481c8279 MOV RCX,qword ptr [RBP + 0x360]
1481c8280 TEST RCX,RCX
1481c8283 JZ 0x1481c828b
1481c8285 CALL 0x140e282f0
1481c828a NOP
1481c828b MOV byte ptr [RBP + -0x8],0x0
1481c828f MOV RCX,qword ptr [R14 + 0x28]
1481c8293 LEA RAX,[RBP + -0x40]
1481c8297 CMP RAX,RCX
1481c829a JC 0x1481c830a
1481c829c MOVSXD RDX,dword ptr [R14 + 0x34]
1481c82a0 MOV RAX,RDX
1481c82a3 SHL RAX,0x6
1481c82a7 ADD RAX,RCX
1481c82aa LEA R8,[RBP + -0x40]
1481c82ae CMP R8,RAX
1481c82b1 JNC 0x1481c830a
1481c82b3 MOVSXD RAX,dword ptr [R14 + 0x30]
1481c82b7 MOV R9,qword ptr [RBP + 0x8c8]
1481c82be MOV qword ptr [RSP + 0x48],0x40
1481c82c7 MOV qword ptr [RSP + 0x40],RAX
1481c82cc MOV qword ptr [RSP + 0x38],RDX
1481c82d1 MOV qword ptr [RSP + 0x30],RCX
1481c82d6 LEA RAX,[RBP + -0x40]
1481c82da MOV qword ptr [RSP + 0x28],RAX
1481c82df LEA RAX,[0x14bce6d80]
1481c82e6 MOV qword ptr [RSP + 0x20],RAX
1481c82eb MOV R8D,0x63e
1481c82f1 LEA RDX,[0x14cf27ac0]
1481c82f8 LEA RCX,[0x14bce6eb8]
1481c82ff CALL 0x140f8dfd0
1481c8304 TEST AL,AL
1481c8306 JZ 0x1481c830a
1481c8308 NOP
1481c8309 INT3
1481c830a MOVSXD RDI,dword ptr [R14 + 0x30]
1481c830e LEA EAX,[RDI + 0x1]
1481c8311 MOV dword ptr [R14 + 0x30],EAX
1481c8315 CMP EAX,dword ptr [R14 + 0x34]
1481c8319 JBE 0x1481c8326
1481c831b MOV EDX,EDI
1481c831d LEA RCX,[R14 + 0x28]
1481c8321 CALL 0x1481caa90
1481c8326 MOV RCX,RDI
1481c8329 SHL RCX,0x6
1481c832d ADD RCX,qword ptr [R14 + 0x28]
1481c8331 MOV RAX,qword ptr [RBP + -0x40]
1481c8335 MOV qword ptr [RCX],RAX
1481c8338 MOV RAX,qword ptr [RBP + -0x38]
1481c833c MOV qword ptr [RCX + 0x8],RAX
1481c8340 TEST RAX,RAX
1481c8343 JZ 0x1481c8349
1481c8345 INC.LOCK dword ptr [RAX + 0x8]
1481c8349 MOV EAX,dword ptr [RBP + -0x30]
1481c834c MOV dword ptr [RCX + 0x10],EAX
1481c834f MOV EAX,dword ptr [RBP + -0x28]
1481c8352 MOV dword ptr [RCX + 0x18],EAX
1481c8355 MOV RAX,qword ptr [RBP + -0x20]
1481c8359 MOV qword ptr [RCX + 0x20],RAX
1481c835d MOV RAX,qword ptr [RBP + -0x18]
1481c8361 MOV qword ptr [RCX + 0x28],RAX
1481c8365 TEST RAX,RAX
1481c8368 JZ 0x1481c836e
1481c836a INC.LOCK dword ptr [RAX + 0x8]
1481c836e MOV EAX,dword ptr [RBP + -0x10]
1481c8371 MOV dword ptr [RCX + 0x30],EAX
1481c8374 MOVZX EAX,byte ptr [RBP + -0x8]
1481c8378 MOV byte ptr [RCX + 0x38],AL
1481c837b ADD dword ptr [R14 + 0x3c],ESI
1481c837f MOV RBX,qword ptr [RBP + -0x18]
1481c8383 TEST RBX,RBX
1481c8386 JZ 0x1481c83b9
1481c8388 MOV EAX,R15D
1481c838b XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c8390 CMP EAX,0x1
1481c8393 JNZ 0x1481c83b9
1481c8395 MOV RAX,qword ptr [RBX]
1481c8398 MOV RCX,RBX
1481c839b CALL qword ptr [RAX]
1481c839d MOV EAX,R15D
1481c83a0 XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c83a5 CMP EAX,0x1
1481c83a8 JNZ 0x1481c83b9
1481c83aa MOV RAX,qword ptr [RBX]
1481c83ad MOV EDX,0x1
1481c83b2 MOV RCX,RBX
1481c83b5 CALL qword ptr [RAX + 0x8]
1481c83b8 NOP
1481c83b9 MOV RBX,qword ptr [RBP + -0x38]
1481c83bd TEST RBX,RBX
1481c83c0 JZ 0x1481c83f3
1481c83c2 MOV EAX,R15D
1481c83c5 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c83ca CMP EAX,0x1
1481c83cd JNZ 0x1481c83f3
1481c83cf MOV RAX,qword ptr [RBX]
1481c83d2 MOV RCX,RBX
1481c83d5 CALL qword ptr [RAX]
1481c83d7 MOV EAX,R15D
1481c83da XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c83df CMP EAX,0x1
1481c83e2 JNZ 0x1481c83f3
1481c83e4 MOV RAX,qword ptr [RBX]
1481c83e7 MOV EDX,0x1
1481c83ec MOV RCX,RBX
1481c83ef CALL qword ptr [RAX + 0x8]
1481c83f2 NOP
1481c83f3 MOV EAX,dword ptr [R12 + 0x4]
1481c83f8 CDQ
1481c83f9 SUB EAX,EDX
1481c83fb SAR EAX,0x1
1481c83fd MOVD XMM1,EAX
1481c8401 CVTDQ2PS XMM1,XMM1
1481c8404 MULSS XMM1,XMM11
1481c8409 ADDSS XMM1,XMM1
1481c840d SUBSS XMM1,XMM12
1481c8412 CVTSS2SI ESI,XMM1
1481c8416 SAR ESI,0x1
1481c8418 TEST ESI,ESI
1481c841a JLE 0x1481c86c6
1481c8420 LEA RCX,[RBP]
1481c8424 CALL 0x140e820a0
1481c8429 NOP
1481c842a MOV dword ptr [RBP + 0x18],0x0
1481c8431 LEA RCX,[RBP + 0x20]
1481c8435 CALL 0x140e820a0
1481c843a MOV byte ptr [RBP + 0x38],0x0
1481c843e LEA RDX,[0x14cf76c38]
1481c8445 LEA RCX,[RBP + 0x370]
1481c844c CALL 0x140cf7750
1481c8451 NOP
1481c8452 LEA RDX,[RBP + 0x370]
1481c8459 LEA RCX,[RBP + 0x578]
1481c8460 CALL 0x140ebb430
1481c8465 MOVUPS XMM1,xmmword ptr [RBP]
1481c8469 MOVUPS XMM0,xmmword ptr [RAX]
1481c846c MOVUPS xmmword ptr [RBP],XMM0
1481c8470 MOVUPS xmmword ptr [RAX],XMM1
1481c8473 MOV EAX,dword ptr [RAX + 0x10]
1481c8476 MOV dword ptr [RBP + 0x10],EAX
1481c8479 MOV RBX,qword ptr [RBP + 0x580]
1481c8480 TEST RBX,RBX
1481c8483 JZ 0x1481c84b6
1481c8485 MOV EAX,R15D
1481c8488 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c848d CMP EAX,0x1
1481c8490 JNZ 0x1481c84b6
1481c8492 MOV RAX,qword ptr [RBX]
1481c8495 MOV RCX,RBX
1481c8498 CALL qword ptr [RAX]
1481c849a MOV EAX,R15D
1481c849d XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c84a2 CMP EAX,0x1
1481c84a5 JNZ 0x1481c84b6
1481c84a7 MOV RAX,qword ptr [RBX]
1481c84aa MOV EDX,0x1
1481c84af MOV RCX,RBX
1481c84b2 CALL qword ptr [RAX + 0x8]
1481c84b5 NOP
1481c84b6 MOV RCX,qword ptr [RBP + 0x370]
1481c84bd TEST RCX,RCX
1481c84c0 JZ 0x1481c84c8
1481c84c2 CALL 0x140e282f0
1481c84c7 NOP
1481c84c8 MOV dword ptr [RBP + 0x18],ESI
1481c84cb MOV R8D,dword ptr [R12 + 0x4]
1481c84d0 LEA RDX,[0x14cf76c48]
1481c84d7 LEA RCX,[RBP + 0x380]
1481c84de CALL 0x140d169d0
1481c84e3 OR dword ptr [RSP + 0x50],0x10
1481c84e8 LEA RDX,[RBP + 0x380]
1481c84ef LEA RCX,[RBP + 0x590]
1481c84f6 CALL 0x140ebb430
1481c84fb MOVUPS XMM1,xmmword ptr [RBP + 0x20]
1481c84ff MOVUPS XMM0,xmmword ptr [RAX]
1481c8502 MOVUPS xmmword ptr [RBP + 0x20],XMM0
1481c8506 MOVUPS xmmword ptr [RAX],XMM1
1481c8509 MOV EAX,dword ptr [RAX + 0x10]
1481c850c MOV dword ptr [RBP + 0x30],EAX
1481c850f MOV RBX,qword ptr [RBP + 0x598]
1481c8516 TEST RBX,RBX
1481c8519 JZ 0x1481c854c
1481c851b MOV EAX,R15D
1481c851e XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c8523 CMP EAX,0x1
1481c8526 JNZ 0x1481c854c
1481c8528 MOV RAX,qword ptr [RBX]
1481c852b MOV RCX,RBX
1481c852e CALL qword ptr [RAX]
1481c8530 MOV EAX,R15D
1481c8533 XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c8538 CMP EAX,0x1
1481c853b JNZ 0x1481c854c
1481c853d MOV RAX,qword ptr [RBX]
1481c8540 MOV EDX,0x1
1481c8545 MOV RCX,RBX
1481c8548 CALL qword ptr [RAX + 0x8]
1481c854b NOP
1481c854c MOV RCX,qword ptr [RBP + 0x380]
1481c8553 TEST RCX,RCX
1481c8556 JZ 0x1481c855e
1481c8558 CALL 0x140e282f0
1481c855d NOP
1481c855e MOV byte ptr [RBP + 0x38],0x0
1481c8562 MOV RCX,qword ptr [R14 + 0x28]
1481c8566 LEA RAX,[RBP]
1481c856a CMP RAX,RCX
1481c856d JC 0x1481c85dd
1481c856f MOVSXD RDX,dword ptr [R14 + 0x34]
1481c8573 MOV RAX,RDX
1481c8576 SHL RAX,0x6
1481c857a ADD RAX,RCX
1481c857d LEA R8,[RBP]
1481c8581 CMP R8,RAX
1481c8584 JNC 0x1481c85dd
1481c8586 MOVSXD RAX,dword ptr [R14 + 0x30]
1481c858a MOV R9,qword ptr [RBP + 0x8c8]
1481c8591 MOV qword ptr [RSP + 0x48],0x40
1481c859a MOV qword ptr [RSP + 0x40],RAX
1481c859f MOV qword ptr [RSP + 0x38],RDX
1481c85a4 MOV qword ptr [RSP + 0x30],RCX
1481c85a9 LEA RAX,[RBP]
1481c85ad MOV qword ptr [RSP + 0x28],RAX
1481c85b2 LEA RAX,[0x14bce6d80]
1481c85b9 MOV qword ptr [RSP + 0x20],RAX
1481c85be MOV R8D,0x63e
1481c85c4 LEA RDX,[0x14cf27ac0]
1481c85cb LEA RCX,[0x14bce6eb8]
1481c85d2 CALL 0x140f8dfd0
1481c85d7 TEST AL,AL
1481c85d9 JZ 0x1481c85dd
1481c85db NOP
1481c85dc INT3
1481c85dd MOVSXD RDI,dword ptr [R14 + 0x30]
1481c85e1 LEA EAX,[RDI + 0x1]
1481c85e4 MOV dword ptr [R14 + 0x30],EAX
1481c85e8 CMP EAX,dword ptr [R14 + 0x34]
1481c85ec JBE 0x1481c85f9
1481c85ee MOV EDX,EDI
1481c85f0 LEA RCX,[R14 + 0x28]
1481c85f4 CALL 0x1481caa90
1481c85f9 MOV RCX,RDI
1481c85fc SHL RCX,0x6
1481c8600 ADD RCX,qword ptr [R14 + 0x28]
1481c8604 MOV RAX,qword ptr [RBP]
1481c8608 MOV qword ptr [RCX],RAX
1481c860b MOV RAX,qword ptr [RBP + 0x8]
1481c860f MOV qword ptr [RCX + 0x8],RAX
1481c8613 TEST RAX,RAX
1481c8616 JZ 0x1481c861c
1481c8618 INC.LOCK dword ptr [RAX + 0x8]
1481c861c MOV EAX,dword ptr [RBP + 0x10]
1481c861f MOV dword ptr [RCX + 0x10],EAX
1481c8622 MOV EAX,dword ptr [RBP + 0x18]
1481c8625 MOV dword ptr [RCX + 0x18],EAX
1481c8628 MOV RAX,qword ptr [RBP + 0x20]
1481c862c MOV qword ptr [RCX + 0x20],RAX
1481c8630 MOV RAX,qword ptr [RBP + 0x28]
1481c8634 MOV qword ptr [RCX + 0x28],RAX
1481c8638 TEST RAX,RAX
1481c863b JZ 0x1481c8641
1481c863d INC.LOCK dword ptr [RAX + 0x8]
1481c8641 MOV EAX,dword ptr [RBP + 0x30]
1481c8644 MOV dword ptr [RCX + 0x30],EAX
1481c8647 MOVZX EAX,byte ptr [RBP + 0x38]
1481c864b MOV byte ptr [RCX + 0x38],AL
1481c864e ADD dword ptr [R14 + 0x3c],ESI
1481c8652 MOV RBX,qword ptr [RBP + 0x28]
1481c8656 TEST RBX,RBX
1481c8659 JZ 0x1481c868c
1481c865b MOV EAX,R15D
1481c865e XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c8663 CMP EAX,0x1
1481c8666 JNZ 0x1481c868c
1481c8668 MOV RAX,qword ptr [RBX]
1481c866b MOV RCX,RBX
1481c866e CALL qword ptr [RAX]
1481c8670 MOV EAX,R15D
1481c8673 XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c8678 CMP EAX,0x1
1481c867b JNZ 0x1481c868c
1481c867d MOV RAX,qword ptr [RBX]
1481c8680 MOV EDX,0x1
1481c8685 MOV RCX,RBX
1481c8688 CALL qword ptr [RAX + 0x8]
1481c868b NOP
1481c868c MOV RBX,qword ptr [RBP + 0x8]
1481c8690 TEST RBX,RBX
1481c8693 JZ 0x1481c86c6
1481c8695 MOV EAX,R15D
1481c8698 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c869d CMP EAX,0x1
1481c86a0 JNZ 0x1481c86c6
1481c86a2 MOV RAX,qword ptr [RBX]
1481c86a5 MOV RCX,RBX
1481c86a8 CALL qword ptr [RAX]
1481c86aa MOV EAX,R15D
1481c86ad XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c86b2 CMP EAX,0x1
1481c86b5 JNZ 0x1481c86c6
1481c86b7 MOV RAX,qword ptr [RBX]
1481c86ba MOV EDX,0x1
1481c86bf MOV RCX,RBX
1481c86c2 CALL qword ptr [RAX + 0x8]
1481c86c5 NOP
1481c86c6 MOV EAX,0x55555556
1481c86cb MOV EDI,dword ptr [RSP + 0x78]
1481c86cf IMUL EDI
1481c86d1 MOV EAX,EDX
1481c86d3 SHR EAX,0x1f
1481c86d6 ADD EDX,EAX
1481c86d8 MOVD XMM1,EDX
1481c86dc CVTDQ2PS XMM1,XMM1
1481c86df MULSS XMM1,XMM11
1481c86e4 ADDSS XMM1,XMM1
1481c86e8 SUBSS XMM1,XMM12
1481c86ed CVTSS2SI ESI,XMM1
1481c86f1 SAR ESI,0x1
1481c86f3 TEST ESI,ESI
1481c86f5 JLE 0x1481c8927
1481c86fb LEA RCX,[RBP + 0x210]
1481c8702 CALL 0x140e820a0
1481c8707 NOP
1481c8708 MOV dword ptr [RBP + 0x228],0x0
1481c8712 LEA RCX,[RBP + 0x230]
1481c8719 CALL 0x140e820a0
1481c871e MOV byte ptr [RBP + 0x248],0x0
1481c8725 LEA RDX,[0x14cf76b70]
1481c872c LEA RCX,[RBP + 0x390]
1481c8733 CALL 0x140cf7750
1481c8738 NOP
1481c8739 LEA RDX,[RBP + 0x390]
1481c8740 LEA RCX,[RBP + 0x5a8]
1481c8747 CALL 0x140ebb430
1481c874c MOVUPS XMM1,xmmword ptr [RBP + 0x210]
1481c8753 MOVUPS XMM0,xmmword ptr [RAX]
1481c8756 MOVUPS xmmword ptr [RBP + 0x210],XMM0
1481c875d MOVUPS xmmword ptr [RAX],XMM1
1481c8760 MOV EAX,dword ptr [RAX + 0x10]
1481c8763 MOV dword ptr [RBP + 0x220],EAX
1481c8769 MOV RBX,qword ptr [RBP + 0x5b0]
1481c8770 TEST RBX,RBX
1481c8773 JZ 0x1481c87a6
1481c8775 MOV EAX,R15D
1481c8778 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c877d CMP EAX,0x1
1481c8780 JNZ 0x1481c87a6
1481c8782 MOV RAX,qword ptr [RBX]
1481c8785 MOV RCX,RBX
1481c8788 CALL qword ptr [RAX]
1481c878a MOV EAX,R15D
1481c878d XADD.LOCK dword ptr [RBX + 0xc],EAX
1481c8792 CMP EAX,0x1
1481c8795 JNZ 0x1481c87a6
1481c8797 MOV RAX,qword ptr [RBX]
1481c879a MOV EDX,0x1
1481c879f MOV RCX,RBX
1481c87a2 CALL qword ptr [RAX + 0x8]
1481c87a5 NOP
1481c87a6 MOV RCX,qword ptr [RBP + 0x390]
1481c87ad TEST RCX,RCX
1481c87b0 JZ 0x1481c87b8
1481c87b2 CALL 0x140e282f0
1481c87b7 NOP
1481c87b8 MOV dword ptr [RBP + 0x228],ESI
1481c87be MOV R8D,EDI
1481c87c1 LEA RDX,[0x14cf76b88]
1481c87c8 LEA RCX,[RBP + 0x3a0]
1481c87cf CALL 0x140d169d0
1481c87d4 OR dword ptr [RSP + 0x50],0x20
1481c87d9 LEA RDX,[RBP + 0x3a0]
1481c87e0 LEA RCX,[RBP + 0x5c0]
1481c87e7 CALL 0x140ebb430
1481c87ec MOVUPS XMM1,xmmword ptr [RBP + 0x230]
1481c87f3 MOVUPS XMM0,xmmword ptr [RAX]
1481c87f6 MOVUPS xmmword ptr [RBP + 0x230],XMM0
1481c87fd MOVUPS xmmword ptr [RAX],XMM1
1481c8800 MOV EAX,dword ptr [RAX + 0x10]
1481c8803 MOV dword ptr [RBP + 0x240],EAX
1481c8809 MOV RBX,qword ptr [RBP + 0x5c8]
1481c8810 TEST RBX,RBX
1481c8813 JZ 0x1481c8843
1481c8815 MOV EAX,R15D
1481c8818 XADD.LOCK dword ptr [RBX + 0x8],EAX
1481c881d CMP EAX,0x1
1481c8820 JNZ 0x1481c8843
1481c8822 MOV RAX,qword ptr [RBX]
1481c8825 MOV RCX,RBX
1481c8828 CALL qword ptr [RAX]
1481c882a XADD.LOCK dword ptr [RBX + 0xc],R15D
1481c8830 CMP R15D,0x1
1481c8834 JNZ 0x1481c8843
1481c8836 MOV RAX,qword ptr [RBX]
1481c8839 MOV EDX,R15D
1481c883c MOV RCX,RBX
1481c883f CALL qword ptr [RAX + 0x8]
1481c8842 NOP
1481c8843 MOV RCX,qword ptr [RBP + 0x3a0]
1481c884a TEST RCX,RCX
1481c884d JZ 0x1481c8855
1481c884f CALL 0x140e282f0
1481c8854 NOP
1481c8855 MOV byte ptr [RBP + 0x248],0x0
1481c885c MOV RCX,qword ptr [R14 + 0x28]
1481c8860 LEA RAX,[RBP + 0x210]
1481c8867 CMP RAX,RCX
1481c886a JC 0x1481c88e4
1481c8870 MOVSXD RDX,dword ptr [R14 + 0x34]
1481c8874 MOV RAX,RDX
1481c8877 SHL RAX,0x6
1481c887b ADD RAX,RCX
1481c887e LEA R8,[RBP + 0x210]
1481c8885 CMP R8,RAX
1481c8888 JNC 0x1481c88e4
1481c888a MOVSXD RAX,dword ptr [R14 + 0x30]
1481c888e MOV R9,qword ptr [RBP + 0x8c8]
1481c8895 MOV qword ptr [RSP + 0x48],0x40
1481c889e MOV qword ptr [RSP + 0x40],RAX
1481c88a3 MOV qword ptr [RSP + 0x38],RDX
1481c88a8 MOV qword ptr [RSP + 0x30],RCX
1481c88ad LEA RAX,[RBP + 0x210]
1481c88b4 MOV qword ptr [RSP + 0x28],RAX
1481c88b9 LEA RAX,[0x14bce6d80]
1481c88c0 MOV qword ptr [RSP + 0x20],RAX
1481c88c5 MOV R8D,0x63e
1481c88cb LEA RDX,[0x14cf27ac0]
1481c88d2 LEA RCX,[0x14bce6eb8]
1481c88d9 CALL 0x140f8dfd0
1481c88de TEST AL,AL
1481c88e0 JZ 0x1481c88e4
1481c88e2 NOP
1481c88e3 INT3
1481c88e4 MOVSXD RDI,dword ptr [R14 + 0x30]
1481c88e8 LEA EAX,[RDI + 0x1]
1481c88eb MOV dword ptr [R14 + 0x30],EAX
1481c88ef CMP EAX,dword ptr [R14 + 0x34]
1481c88f3 JBE 0x1481c8900
1481c88f5 MOV EDX,EDI
1481c88f7 LEA RCX,[R14 + 0x28]
1481c88fb CALL 0x1481caa90
1481c8900 MOV RCX,RDI
1481c8903 SHL RCX,0x6
1481c8907 ADD RCX,qword ptr [R14 + 0x28]
1481c890b LEA RDX,[RBP + 0x210]
1481c8912 CALL 0x1481b2fe0
1481c8917 ADD dword ptr [R14 + 0x3c],ESI
1481c891b LEA RCX,[RBP + 0x210]
1481c8922 CALL 0x148152560
1481c8927 MOV EAX,0x66666667
1481c892c IMUL dword ptr [R12 + 0x20]
1481c8931 SAR EDX,0x2
1481c8934 MOV EAX,EDX
1481c8936 SHR EAX,0x1f
1481c8939 ADD EDX,EAX
1481c893b MOVD XMM1,EDX
1481c893f CVTDQ2PS XMM1,XMM1
1481c8942 MULSS XMM1,XMM11
1481c8947 ADDSS XMM1,XMM1
1481c894b SUBSS XMM1,XMM12
1481c8950 CVTSS2SI ESI,XMM1
1481c8954 SAR ESI,0x1
1481c8956 TEST ESI,ESI
1481c8958 JLE 0x1481c8b31
1481c895e LEA RCX,[RBP + 0x250]
1481c8965 CALL 0x140e820a0
1481c896a NOP
1481c896b XOR R15D,R15D
1481c896e MOV dword ptr [RBP + 0x268],R15D
1481c8975 LEA RCX,[RBP + 0x270]
1481c897c CALL 0x140e820a0
1481c8981 MOV byte ptr [RBP + 0x288],R15B
1481c8988 LEA RDX,[0x14cf76d38]
1481c898f LEA RCX,[RBP + 0x3b0]
1481c8996 CALL 0x140cf7750
1481c899b NOP
1481c899c LEA RDX,[RBP + 0x3b0]
1481c89a3 LEA RCX,[RBP + 0x6c8]
1481c89aa CALL 0x140ebb430
1481c89af MOVUPS XMM1,xmmword ptr [RBP + 0x250]
1481c89b6 MOVUPS XMM0,xmmword ptr [RAX]
1481c89b9 MOVUPS xmmword ptr [RBP + 0x250],XMM0
1481c89c0 MOVUPS xmmword ptr [RAX],XMM1
1481c89c3 MOV EAX,dword ptr [RAX + 0x10]
1481c89c6 MOV dword ptr [RBP + 0x260],EAX
1481c89cc LEA RCX,[RBP + 0x6c8]
1481c89d3 CALL 0x140e86d70
1481c89d8 NOP
1481c89d9 MOV RCX,qword ptr [RBP + 0x3b0]
1481c89e0 TEST RCX,RCX
1481c89e3 JZ 0x1481c89eb
1481c89e5 CALL 0x140e282f0
1481c89ea NOP
1481c89eb MOV dword ptr [RBP + 0x268],ESI
1481c89f1 MOV R8D,dword ptr [R12 + 0x20]
1481c89f6 LEA RDX,[0x14cf76d58]
1481c89fd LEA RCX,[RBP + 0x3c0]
1481c8a04 CALL 0x140d169d0
1481c8a09 OR dword ptr [RSP + 0x50],0x40
1481c8a0e LEA RDX,[RBP + 0x3c0]
1481c8a15 LEA RCX,[RBP + 0x5f0]
1481c8a1c CALL 0x140ebb430
1481c8a21 MOVUPS XMM1,xmmword ptr [RBP + 0x270]
1481c8a28 MOVUPS XMM0,xmmword ptr [RAX]
1481c8a2b MOVUPS xmmword ptr [RBP + 0x270],XMM0
1481c8a32 MOVUPS xmmword ptr [RAX],XMM1
1481c8a35 MOV EAX,dword ptr [RAX + 0x10]
1481c8a38 MOV dword ptr [RBP + 0x280],EAX
1481c8a3e LEA RCX,[RBP + 0x5f0]
1481c8a45 CALL 0x140e86d70
1481c8a4a NOP
1481c8a4b MOV RCX,qword ptr [RBP + 0x3c0]
1481c8a52 TEST RCX,RCX
1481c8a55 JZ 0x1481c8a5d
1481c8a57 CALL 0x140e282f0
1481c8a5c NOP
1481c8a5d MOV byte ptr [RBP + 0x288],0x0
1481c8a64 MOV RCX,qword ptr [R14 + 0x28]
1481c8a68 LEA RAX,[RBP + 0x250]
1481c8a6f CMP RAX,RCX
1481c8a72 JC 0x1481c8aec
1481c8a78 MOVSXD RDX,dword ptr [R14 + 0x34]
1481c8a7c MOV RAX,RDX
1481c8a7f SHL RAX,0x6
1481c8a83 ADD RAX,RCX
1481c8a86 LEA R8,[RBP + 0x250]
1481c8a8d CMP R8,RAX
1481c8a90 JNC 0x1481c8aec
1481c8a92 MOVSXD RAX,dword ptr [R14 + 0x30]
1481c8a96 MOV R9,qword ptr [RBP + 0x8c8]
1481c8a9d MOV qword ptr [RSP + 0x48],0x40
1481c8aa6 MOV qword ptr [RSP + 0x40],RAX
1481c8aab MOV qword ptr [RSP + 0x38],RDX
1481c8ab0 MOV qword ptr [RSP + 0x30],RCX
1481c8ab5 LEA RAX,[RBP + 0x250]
1481c8abc MOV qword ptr [RSP + 0x28],RAX
1481c8ac1 LEA RAX,[0x14bce6d80]
1481c8ac8 MOV qword ptr [RSP + 0x20],RAX
1481c8acd MOV R8D,0x63e
1481c8ad3 LEA RDX,[0x14cf27ac0]
1481c8ada LEA RCX,[0x14bce6eb8]
1481c8ae1 CALL 0x140f8dfd0
1481c8ae6 TEST AL,AL
1481c8ae8 JZ 0x1481c8aec
1481c8aea NOP
1481c8aeb INT3
1481c8aec MOVSXD RDI,dword ptr [R14 + 0x30]
1481c8af0 LEA EAX,[RDI + 0x1]
1481c8af3 MOV dword ptr [R14 + 0x30],EAX
1481c8af7 CMP EAX,dword ptr [R14 + 0x34]
1481c8afb JBE 0x1481c8b08
1481c8afd MOV EDX,EDI
1481c8aff LEA RCX,[R14 + 0x28]
1481c8b03 CALL 0x1481caa90
1481c8b08 MOV RCX,RDI
1481c8b0b SHL RCX,0x6
1481c8b0f ADD RCX,qword ptr [R14 + 0x28]
1481c8b13 LEA RDX,[RBP + 0x250]
1481c8b1a CALL 0x1481b2fe0
1481c8b1f ADD dword ptr [R14 + 0x3c],ESI
1481c8b23 LEA RCX,[RBP + 0x250]
1481c8b2a CALL 0x148152560
1481c8b2f JMP 0x1481c8b34
1481c8b31 XOR R15D,R15D
1481c8b34 CMP dword ptr [R12 + 0x30],0x0
1481c8b3a JLE 0x1481c8d0a
1481c8b40 LEA RCX,[RBP + 0x290]
1481c8b47 CALL 0x140e820a0
1481c8b4c NOP
1481c8b4d MOV dword ptr [RBP + 0x2a8],R15D
1481c8b54 LEA RCX,[RBP + 0x2b0]
1481c8b5b CALL 0x140e820a0
1481c8b60 MOV byte ptr [RBP + 0x2c8],0x0
1481c8b67 LEA RDX,[0x14cf76d70]
1481c8b6e LEA RCX,[RBP + 0x3d0]
1481c8b75 CALL 0x140cf7750
1481c8b7a NOP
1481c8b7b LEA RDX,[RBP + 0x3d0]
1481c8b82 LEA RCX,[RBP + 0x608]
1481c8b89 CALL 0x140ebb430
1481c8b8e MOVUPS XMM1,xmmword ptr [RBP + 0x290]
1481c8b95 MOVUPS XMM0,xmmword ptr [RAX]
1481c8b98 MOVUPS xmmword ptr [RBP + 0x290],XMM0
1481c8b9f MOVUPS xmmword ptr [RAX],XMM1
1481c8ba2 MOV EAX,dword ptr [RAX + 0x10]
1481c8ba5 MOV dword ptr [RBP + 0x2a0],EAX
1481c8bab LEA RCX,[RBP + 0x608]
1481c8bb2 CALL 0x140e86d70
1481c8bb7 NOP
1481c8bb8 MOV RCX,qword ptr [RBP + 0x3d0]
1481c8bbf TEST RCX,RCX
1481c8bc2 JZ 0x1481c8bca
1481c8bc4 CALL 0x140e282f0
1481c8bc9 NOP
1481c8bca MOV dword ptr [RBP + 0x2a8],0x5
1481c8bd4 LEA RDX,[0x14cf76d80]
1481c8bdb LEA RCX,[RBP + 0x3e0]
1481c8be2 CALL 0x140cf7750
1481c8be7 NOP
1481c8be8 LEA RDX,[RBP + 0x3e0]
1481c8bef LEA RCX,[RBP + 0x620]
1481c8bf6 CALL 0x140ebb430
1481c8bfb MOVUPS XMM1,xmmword ptr [RBP + 0x2b0]
1481c8c02 MOVUPS XMM0,xmmword ptr [RAX]
1481c8c05 MOVUPS xmmword ptr [RBP + 0x2b0],XMM0
1481c8c0c MOVUPS xmmword ptr [RAX],XMM1
1481c8c0f MOV EAX,dword ptr [RAX + 0x10]
1481c8c12 MOV dword ptr [RBP + 0x2c0],EAX
1481c8c18 LEA RCX,[RBP + 0x620]
1481c8c1f CALL 0x140e86d70
1481c8c24 NOP
1481c8c25 MOV RCX,qword ptr [RBP + 0x3e0]
1481c8c2c TEST RCX,RCX
1481c8c2f JZ 0x1481c8c37
1481c8c31 CALL 0x140e282f0
1481c8c36 NOP
1481c8c37 MOV byte ptr [RBP + 0x2c8],0x0
1481c8c3e MOV RCX,qword ptr [R14 + 0x28]
1481c8c42 LEA RAX,[RBP + 0x290]
1481c8c49 CMP RAX,RCX
1481c8c4c JC 0x1481c8cc6
1481c8c52 MOVSXD RDX,dword ptr [R14 + 0x34]
1481c8c56 MOV RAX,RDX
1481c8c59 SHL RAX,0x6
1481c8c5d ADD RAX,RCX
1481c8c60 LEA R8,[RBP + 0x290]
1481c8c67 CMP R8,RAX
1481c8c6a JNC 0x1481c8cc6
1481c8c6c MOVSXD RAX,dword ptr [R14 + 0x30]
1481c8c70 MOV R9,qword ptr [RBP + 0x8c8]
1481c8c77 MOV qword ptr [RSP + 0x48],0x40
1481c8c80 MOV qword ptr [RSP + 0x40],RAX
1481c8c85 MOV qword ptr [RSP + 0x38],RDX
1481c8c8a MOV qword ptr [RSP + 0x30],RCX
1481c8c8f LEA RAX,[RBP + 0x290]
1481c8c96 MOV qword ptr [RSP + 0x28],RAX
1481c8c9b LEA RAX,[0x14bce6d80]
1481c8ca2 MOV qword ptr [RSP + 0x20],RAX
1481c8ca7 MOV R8D,0x63e
1481c8cad LEA RDX,[0x14cf27ac0]
1481c8cb4 LEA RCX,[0x14bce6eb8]
1481c8cbb CALL 0x140f8dfd0
1481c8cc0 TEST AL,AL
1481c8cc2 JZ 0x1481c8cc6
1481c8cc4 NOP
1481c8cc5 INT3
1481c8cc6 MOVSXD RDI,dword ptr [R14 + 0x30]
1481c8cca LEA EAX,[RDI + 0x1]
1481c8ccd MOV dword ptr [R14 + 0x30],EAX
1481c8cd1 CMP EAX,dword ptr [R14 + 0x34]
1481c8cd5 JBE 0x1481c8ce2
1481c8cd7 MOV EDX,EDI
1481c8cd9 LEA RCX,[R14 + 0x28]
1481c8cdd CALL 0x1481caa90
1481c8ce2 MOV RCX,RDI
1481c8ce5 SHL RCX,0x6
1481c8ce9 ADD RCX,qword ptr [R14 + 0x28]
1481c8ced LEA RDX,[RBP + 0x290]
1481c8cf4 CALL 0x1481b2fe0
1481c8cf9 ADD dword ptr [R14 + 0x3c],0x5
1481c8cfe LEA RCX,[RBP + 0x290]
1481c8d05 CALL 0x148152560
1481c8d0a CMP dword ptr [R12 + 0x1c],0x0
1481c8d10 JNZ 0x1481c8efb
1481c8d16 LEA RCX,[RBP + 0xb0]
1481c8d1d CALL 0x140e820a0
1481c8d22 NOP
1481c8d23 MOV dword ptr [RBP + 0xc8],R15D
1481c8d2a LEA RCX,[RBP + 0xd0]
1481c8d31 CALL 0x140e820a0
1481c8d36 MOV byte ptr [RBP + 0xe8],0x0
1481c8d3d LEA RDX,[0x14cf76da0]
1481c8d44 LEA RCX,[RBP + 0x3f0]
1481c8d4b CALL 0x140cf7750
1481c8d50 NOP
1481c8d51 LEA RDX,[RBP + 0x3f0]
1481c8d58 LEA RCX,[RBP + 0x638]
1481c8d5f CALL 0x140ebb430
1481c8d64 MOVUPS XMM1,xmmword ptr [RBP + 0xb0]
1481c8d6b MOVUPS XMM0,xmmword ptr [RAX]
1481c8d6e MOVUPS xmmword ptr [RBP + 0xb0],XMM0
1481c8d75 MOVUPS xmmword ptr [RAX],XMM1
1481c8d78 MOV EAX,dword ptr [RAX + 0x10]
1481c8d7b MOV dword ptr [RBP + 0xc0],EAX
1481c8d81 LEA RCX,[RBP + 0x638]
1481c8d88 CALL 0x140e86d70
1481c8d8d NOP
1481c8d8e MOV RCX,qword ptr [RBP + 0x3f0]
1481c8d95 TEST RCX,RCX
1481c8d98 JZ 0x1481c8da0
1481c8d9a CALL 0x140e282f0
1481c8d9f NOP
1481c8da0 MULSS XMM11,dword ptr [0x14bcfdb5c]
1481c8da9 ADDSS XMM11,XMM11
1481c8dae SUBSS XMM11,XMM12
1481c8db3 CVTSS2SI EAX,XMM11
1481c8db8 SAR EAX,0x1
1481c8dba MOV dword ptr [RBP + 0xc8],EAX
1481c8dc0 LEA RDX,[0x14cf76db0]
1481c8dc7 LEA RCX,[RBP + 0x400]
1481c8dce CALL 0x140cf7750
1481c8dd3 NOP
1481c8dd4 LEA RDX,[RBP + 0x400]
1481c8ddb LEA RCX,[RBP + 0x650]
1481c8de2 CALL 0x140ebb430
1481c8de7 MOVUPS XMM1,xmmword ptr [RBP + 0xd0]
1481c8dee MOVUPS XMM0,xmmword ptr [RAX]
1481c8df1 MOVUPS xmmword ptr [RBP + 0xd0],XMM0
1481c8df8 MOVUPS xmmword ptr [RAX],XMM1
1481c8dfb MOV EAX,dword ptr [RAX + 0x10]
1481c8dfe MOV dword ptr [RBP + 0xe0],EAX
1481c8e04 LEA RCX,[RBP + 0x650]
1481c8e0b CALL 0x140e86d70
1481c8e10 NOP
1481c8e11 MOV RCX,qword ptr [RBP + 0x400]
1481c8e18 TEST RCX,RCX
1481c8e1b JZ 0x1481c8e23
1481c8e1d CALL 0x140e282f0
1481c8e22 NOP
1481c8e23 MOV byte ptr [RBP + 0xe8],0x0
1481c8e2a MOV R10,qword ptr [R14 + 0x28]
1481c8e2e LEA RAX,[RBP + 0xb0]
1481c8e35 CMP RAX,R10
1481c8e38 JC 0x1481c8eb2
1481c8e3e MOVSXD R11,dword ptr [R14 + 0x34]
1481c8e42 MOV RAX,R11
1481c8e45 SHL RAX,0x6
1481c8e49 ADD RAX,R10
1481c8e4c LEA RCX,[RBP + 0xb0]
1481c8e53 CMP RCX,RAX
1481c8e56 JNC 0x1481c8eb2
1481c8e58 MOVSXD RAX,dword ptr [R14 + 0x30]
1481c8e5c MOV R9,qword ptr [RBP + 0x8c8]
1481c8e63 MOV qword ptr [RSP + 0x48],0x40
1481c8e6c MOV qword ptr [RSP + 0x40],RAX
1481c8e71 MOV qword ptr [RSP + 0x38],R11
1481c8e76 MOV qword ptr [RSP + 0x30],R10
1481c8e7b LEA RAX,[RBP + 0xb0]
1481c8e82 MOV qword ptr [RSP + 0x28],RAX
1481c8e87 LEA RAX,[0x14bce6d80]
1481c8e8e MOV qword ptr [RSP + 0x20],RAX
1481c8e93 MOV R8D,0x63e
1481c8e99 LEA RDX,[0x14cf27ac0]
1481c8ea0 LEA RCX,[0x14bce6eb8]
1481c8ea7 CALL 0x140f8dfd0
1481c8eac TEST AL,AL
1481c8eae JZ 0x1481c8eb2
1481c8eb0 NOP
1481c8eb1 INT3
1481c8eb2 MOVSXD RDI,dword ptr [R14 + 0x30]
1481c8eb6 LEA EAX,[RDI + 0x1]
1481c8eb9 MOV dword ptr [R14 + 0x30],EAX
1481c8ebd CMP EAX,dword ptr [R14 + 0x34]
1481c8ec1 JBE 0x1481c8ece
1481c8ec3 MOV EDX,EDI
1481c8ec5 LEA RCX,[R14 + 0x28]
1481c8ec9 CALL 0x1481caa90
1481c8ece MOV RCX,RDI
1481c8ed1 SHL RCX,0x6
1481c8ed5 ADD RCX,qword ptr [R14 + 0x28]
1481c8ed9 LEA RDX,[RBP + 0xb0]
1481c8ee0 CALL 0x1481b2fe0
1481c8ee5 MOV EAX,dword ptr [RBP + 0xc8]
1481c8eeb ADD dword ptr [R14 + 0x3c],EAX
1481c8eef LEA RCX,[RBP + 0xb0]
1481c8ef6 CALL 0x148152560
1481c8efb MOV EAX,dword ptr [RSP + 0x58]
1481c8eff MOV dword ptr [R14 + 0xd4],EAX
1481c8f06 MOV dword ptr [R14 + 0xd8],R13D
1481c8f0d CMP byte ptr [0x14eab53c8],0x3
1481c8f14 JC 0x1481c8f70
1481c8f16 LEA RDX,[0x14bd0f098]
1481c8f1d LEA RCX,[0x14bd0f08c]
1481c8f24 CMP byte ptr [R14 + 0xd0],0x0
1481c8f2c CMOVNZ RCX,RDX
1481c8f30 MOV qword ptr [RSP + 0x48],RCX
1481c8f35 MOV ECX,dword ptr [R14 + 0x48]
1481c8f39 MOV dword ptr [RSP + 0x40],ECX
1481c8f3d MOV ECX,dword ptr [R14 + 0x3c]
1481c8f41 MOV dword ptr [RSP + 0x38],ECX
1481c8f45 MOV dword ptr [RSP + 0x30],EAX
1481c8f49 MOV dword ptr [RSP + 0x28],R13D
1481c8f4e MOV ECX,dword ptr [R14 + 0x20]
1481c8f52 MOV dword ptr [RSP + 0x20],ECX
1481c8f56 MOV R9D,dword ptr [R14]
1481c8f59 MOV R8D,dword ptr [R14 + 0x4]
1481c8f5d LEA RDX,[0x14cf76a68]
1481c8f64 LEA RCX,[0x14eab53c8]
1481c8f6b CALL 0x140f24ba0
1481c8f70 MOV RAX,R14
1481c8f73 MOV RCX,qword ptr [RBP + 0x810]
1481c8f7a XOR RCX,RSP
1481c8f7d CALL 0x14b880380
1481c8f82 LEA R11,[RSP + 0x990]
1481c8f8a MOV RBX,qword ptr [R11 + 0x58]
1481c8f8e MOVAPS XMM6,xmmword ptr [R11 + -0x10]
1481c8f93 MOVAPS XMM7,xmmword ptr [R11 + -0x20]
1481c8f98 MOVAPS XMM8,xmmword ptr [R11 + -0x30]
1481c8f9d MOVAPS XMM9,xmmword ptr [R11 + -0x40]
1481c8fa2 MOVAPS XMM10,xmmword ptr [R11 + -0x50]
1481c8fa7 MOVAPS XMM11,xmmword ptr [R11 + -0x60]
1481c8fac MOVAPS XMM12,xmmword ptr [R11 + -0x70]
1481c8fb1 MOV RSP,R11
1481c8fb4 POP R15
1481c8fb6 POP R14
1481c8fb8 POP R13
1481c8fba POP R12
1481c8fbc POP RDI
1481c8fbd POP RSI
1481c8fbe POP RBP
1481c8fbf RET
*/
