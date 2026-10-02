/* 14818cfa0 ?ExtractChpackToFolder@UCHPackManager@@QEAA_NAEBVFString@@AEAV2@@Z */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ExtractChpackToFolder_UCHPackManager__QEAA_NAEBVFString__AEAV2__Z
               (longlong param_1,undefined8 *param_2,undefined **param_3)

{
  undefined8 uVar1;
  code *pcVar2;
  undefined4 uVar3;
  char cVar4;
  longlong *plVar5;
  undefined8 *puVar6;
  undefined **ppuVar7;
  int iVar8;
  undefined **ppuVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  int iVar13;
  undefined1 auStack_328 [32];
  undefined1 uStack_308;
  undefined1 uStack_300;
  undefined8 uStack_2f8;
  undefined4 uStack_2f0;
  undefined8 uStack_2e8;
  undefined8 uStack_2e0;
  undefined8 uStack_2d8;
  undefined1 auStack_2c8 [8];
  undefined *puStack_2c0;
  int iStack_2b8;
  int aiStack_2b0 [2];
  undefined *puStack_2a8;
  undefined8 uStack_2a0;
  undefined **ppuStack_298;
  undefined8 uStack_290;
  longlong lStack_288;
  undefined *puStack_280;
  int iStack_278;
  undefined **ppuStack_270;
  int iStack_268;
  undefined *puStack_260;
  int iStack_258;
  longlong lStack_250;
  int iStack_248;
  longlong lStack_240;
  int iStack_238;
  undefined *puStack_230;
  int iStack_228;
  undefined *puStack_220;
  int iStack_218;
  undefined *puStack_210;
  int iStack_208;
  longlong alStack_200 [2];
  longlong alStack_1f0 [2];
  longlong alStack_1e0 [2];
  longlong alStack_1d0 [2];
  undefined *puStack_1c0;
  int iStack_1b8;
  wchar_t *pwStack_1b0;
  undefined4 uStack_1a8;
  undefined8 uStack_1a0;
  int iStack_198;
  wchar_t *pwStack_190;
  undefined4 uStack_188;
  undefined8 uStack_180;
  int iStack_178;
  wchar_t *pwStack_170;
  undefined4 uStack_168;
  undefined8 uStack_160;
  int iStack_158;
  wchar_t *pwStack_150;
  undefined4 uStack_148;
  undefined *puStack_140;
  int iStack_138;
  wchar_t *pwStack_130;
  undefined4 uStack_128;
  undefined *puStack_120;
  int iStack_118;
  wchar_t *pwStack_110;
  undefined4 uStack_108;
  longlong alStack_100 [2];
  longlong alStack_f0 [2];
  longlong alStack_e0 [2];
  longlong alStack_d0 [2];
  longlong alStack_c0 [2];
  undefined8 uStack_b0;
  int aiStack_a8 [2];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined *puStack_80;
  int iStack_78;
  undefined *puStack_70;
  int iStack_68;
  wchar_t *pwStack_60;
  undefined4 uStack_58;
  ulonglong uStack_50;
  
  uStack_50 = _DAT_14ea60b28 ^ (ulonglong)auStack_328;
  func_0x00014106ed90(&puStack_280,param_2,1);
  func_0x0001481919f0(&lStack_250);
  lStack_240 = lStack_250;
  if (iStack_248 == 0) {
    iStack_238 = 0;
  }
  else {
    iStack_238 = iStack_248 + -1;
  }
  puStack_230 = puStack_280;
  if (iStack_278 == 0) {
    iStack_228 = 0;
  }
  else {
    iStack_228 = iStack_278 + -1;
  }
  func_0x0001410569f0(&puStack_2c0,&lStack_240,2);
  iVar8 = iStack_2b8;
  puVar10 = puStack_2c0;
  if (param_3 != &puStack_2c0) {
    *(int *)(param_3 + 1) = iStack_2b8;
    if ((iStack_2b8 == 0) && (*(int *)((longlong)param_3 + 0xc) == 0)) {
      *(undefined4 *)((longlong)param_3 + 0xc) = 0;
    }
    else {
      func_0x000140ca39a0(param_3,iStack_2b8);
      if (iVar8 != 0) {
        func_0x00014b89502e(*param_3,puVar10,(longlong)iVar8 * 2);
      }
    }
  }
  puStack_1c0 = puStack_2c0;
  if (iStack_2b8 == 0) {
    iStack_1b8 = 0;
  }
  else {
    iStack_1b8 = iStack_2b8 + -1;
  }
  pwStack_1b0 = L"manifest.json";
  uStack_1a8 = 0xd;
  func_0x0001410569f0(alStack_1d0,&puStack_1c0,2);
  cVar4 = func_0x0001410676a0(alStack_1d0);
  if (cVar4 == '\0') {
    if (*(char *)(param_1 + 0x28) == '\0') {
      if (2 < DAT_14eab53c8) {
        puVar10 = &UNK_14bce4e94;
        if (iStack_278 != 0) {
          puVar10 = puStack_280;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf62548,puVar10);
      }
    }
    else {
      plVar5 = (longlong *)func_0x000140db7220();
      puVar10 = &UNK_14bce4e94;
      puVar11 = &UNK_14bce4e94;
      if (iStack_2b8 != 0) {
        puVar11 = puStack_2c0;
      }
      (**(code **)(*plVar5 + 0x60))(plVar5,puVar11,1);
      ppuStack_298 = (undefined **)0x0;
      uStack_290 = 0;
      puVar6 = (undefined8 *)func_0x00014107c730(alStack_e0);
      uStack_1a0 = *puVar6;
      if (*(int *)(puVar6 + 1) == 0) {
        iStack_198 = 0;
      }
      else {
        iStack_198 = *(int *)(puVar6 + 1) + -1;
      }
      pwStack_190 = L"7za.exe";
      uStack_188 = 7;
      func_0x0001410569f0(&uStack_b0,&uStack_1a0,2);
      puVar6 = (undefined8 *)func_0x000141089840(alStack_f0);
      uStack_180 = *puVar6;
      if (*(int *)(puVar6 + 1) == 0) {
        iStack_178 = 0;
      }
      else {
        iStack_178 = *(int *)(puVar6 + 1) + -1;
      }
      pwStack_170 = L"Binaries/Win64/7za.exe";
      uStack_168 = 0x16;
      func_0x0001410569f0(auStack_a0,&uStack_180,2);
      puVar6 = (undefined8 *)func_0x000141089840(alStack_100);
      uStack_160 = *puVar6;
      if (*(int *)(puVar6 + 1) == 0) {
        iStack_158 = 0;
      }
      else {
        iStack_158 = *(int *)(puVar6 + 1) + -1;
      }
      pwStack_150 = L"7za.exe";
      uStack_148 = 7;
      func_0x0001410569f0(auStack_90,&uStack_160,2);
      ppuVar7 = ppuStack_298;
      for (iVar8 = (int)uStack_290; iVar8 != 0; iVar8 = iVar8 + -1) {
        if (*ppuVar7 != (undefined *)0x0) {
          func_0x000140e282f0();
        }
        ppuVar7 = ppuVar7 + 2;
      }
      uStack_290._4_4_ = (undefined4)((ulonglong)uStack_290 >> 0x20);
      uStack_290 = CONCAT44(uStack_290._4_4_,3);
      func_0x000140ca3910(&ppuStack_298,3,uStack_290._4_4_);
      puVar6 = &uStack_b0;
      ppuVar7 = ppuStack_298;
      iVar8 = 3;
      do {
        iVar13 = iVar8;
        *ppuVar7 = (undefined *)0x0;
        iVar8 = *(int *)(puVar6 + 1);
        uVar1 = *puVar6;
        *(int *)(ppuVar7 + 1) = iVar8;
        ppuStack_270 = ppuVar7;
        if (iVar8 == 0) {
          *(undefined4 *)((longlong)ppuVar7 + 0xc) = 0;
        }
        else {
          func_0x000140ca39a0(ppuVar7,iVar8,0);
          func_0x00014b89502e(*ppuVar7,uVar1);
        }
        ppuVar7 = ppuVar7 + 2;
        puVar6 = puVar6 + 2;
        iVar8 = iVar13 + -1;
      } while (iVar13 + -1 != 0);
      func_0x00014b880d88(&uStack_b0,iVar13 + 0xf,iVar13 + 2,0x140cf8f40);
      if (alStack_100[0] != 0) {
        func_0x000140e282f0();
      }
      if (alStack_f0[0] != 0) {
        func_0x000140e282f0();
      }
      if (alStack_e0[0] != 0) {
        func_0x000140e282f0();
      }
      puStack_2a8 = (undefined *)0x0;
      uStack_2a0 = 0;
      iVar8 = (int)uStack_290;
      ppuVar9 = ppuStack_298 + (longlong)(int)uStack_290 * 2;
      ppuVar7 = ppuStack_298;
      while( true ) {
        if ((int)uStack_290 != iVar8) {
          auStack_2c8[0] = 0;
          cVar4 = func_0x00014bae4c30(auStack_2c8);
          if (cVar4 != '\0') {
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
        }
        if (ppuVar7 == ppuVar9) {
          if ((1 < DAT_14eab53c8) &&
             (func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf626b8), 1 < DAT_14eab53c8)) {
            puVar6 = (undefined8 *)func_0x00014107c730(alStack_d0);
            if (*(int *)(puVar6 + 1) == 0) {
              puVar11 = &UNK_14bce4e94;
            }
            else {
              puVar11 = (undefined *)*puVar6;
            }
            func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf62738,puVar11);
            if (alStack_d0[0] != 0) {
              func_0x000140e282f0();
            }
            if (1 < DAT_14eab53c8) {
              puVar6 = (undefined8 *)func_0x000141089840(alStack_c0);
              if (*(int *)(puVar6 + 1) != 0) {
                puVar10 = (undefined *)*puVar6;
              }
              func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf62788,puVar10);
              if (alStack_c0[0] != 0) {
                func_0x000140e282f0();
              }
            }
          }
          goto LAB_14818d96c;
        }
        cVar4 = func_0x0001410676a0(ppuVar7);
        if (cVar4 != '\0') break;
        if (2 < DAT_14eab53c8) {
          if (*(int *)(ppuVar7 + 1) == 0) {
            puVar11 = &UNK_14bce4e94;
          }
          else {
            puVar11 = *ppuVar7;
          }
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf62660,puVar11);
        }
        ppuVar7 = ppuVar7 + 2;
      }
      if (&puStack_2a8 != ppuVar7) {
        iVar8 = *(int *)(ppuVar7 + 1);
        puVar11 = *ppuVar7;
        uStack_2a0 = CONCAT44(uStack_2a0._4_4_,iVar8);
        if ((iVar8 == 0) && (uStack_2a0._4_4_ == 0)) {
          uStack_2a0 = 0;
        }
        else {
          func_0x000140ca39a0(&puStack_2a8,iVar8);
          if (iVar8 != 0) {
            func_0x00014b89502e(puStack_2a8,puVar11,(longlong)iVar8 * 2);
          }
        }
      }
      if (2 < DAT_14eab53c8) {
        puVar11 = &UNK_14bce4e94;
        if ((int)uStack_2a0 != 0) {
          puVar11 = puStack_2a8;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf62600,puVar11);
      }
      puVar11 = &UNK_14bce4e94;
      if (iStack_2b8 != 0) {
        puVar11 = puStack_2c0;
      }
      if (*(int *)(param_2 + 1) == 0) {
        puVar12 = &UNK_14bce4e94;
      }
      else {
        puVar12 = (undefined *)*param_2;
      }
      func_0x000140d169d0(&puStack_260,L"x \"%s\" -o\"%s\" -y -aoa -bb1",puVar12,puVar11);
      if (2 < DAT_14eab53c8) {
        puVar11 = &UNK_14bce4e94;
        if (iStack_258 != 0) {
          puVar11 = puStack_260;
        }
        puVar12 = &UNK_14bce4e94;
        if ((int)uStack_2a0 != 0) {
          puVar12 = puStack_2a8;
        }
        func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf627d8,puVar12,puVar11);
      }
      puVar11 = &UNK_14bce4e94;
      if (iStack_258 != 0) {
        puVar11 = puStack_260;
      }
      puVar12 = &UNK_14bce4e94;
      if ((int)uStack_2a0 != 0) {
        puVar12 = puStack_2a8;
      }
      uStack_2d8 = 0;
      uStack_2e0 = 0;
      uStack_2e8 = 0;
      uStack_2f0 = 0;
      uStack_2f8 = 0;
      uStack_300 = 0;
      uStack_308 = 0;
      func_0x00014123afe0(&lStack_288,puVar12,puVar11,0);
      if (lStack_288 == 0) {
        if (1 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf62830);
        }
      }
      else {
        cVar4 = func_0x000141246fa0(&lStack_288);
        uVar3 = _DAT_14bcfdb1c;
        while (cVar4 != '\0') {
          func_0x000141253cb0(uVar3);
          cVar4 = func_0x000141246fa0(&lStack_288);
        }
        aiStack_2b0[0] = 0;
        func_0x000141244830(&lStack_288,aiStack_2b0);
        func_0x000141238aa0(&lStack_288);
        if (aiStack_2b0[0] == 0) {
          puStack_140 = puStack_2c0;
          if (iStack_2b8 == 0) {
            iStack_138 = 0;
          }
          else {
            iStack_138 = iStack_2b8 + -1;
          }
          pwStack_130 = L"manifest.json";
          uStack_128 = 0xd;
          func_0x0001410569f0(alStack_1e0,&puStack_140,2);
          cVar4 = func_0x0001410676a0(alStack_1e0);
          if (cVar4 == '\0') {
            puStack_80 = puStack_2c0;
            if (iStack_2b8 == 0) {
              iStack_78 = 0;
            }
            else {
              iStack_78 = iStack_2b8 + -1;
            }
            puStack_70 = puStack_280;
            if (iStack_278 == 0) {
              iStack_68 = 0;
            }
            else {
              iStack_68 = iStack_278 + -1;
            }
            pwStack_60 = L"manifest.json";
            uStack_58 = 0xd;
            func_0x0001410569f0(alStack_200,&puStack_80,3);
            cVar4 = func_0x0001410676a0(alStack_200);
            if (cVar4 != '\0') {
              puStack_220 = puStack_2c0;
              if (iStack_2b8 == 0) {
                iStack_218 = 0;
              }
              else {
                iStack_218 = iStack_2b8 + -1;
              }
              puStack_210 = puStack_280;
              if (iStack_278 == 0) {
                iStack_208 = 0;
              }
              else {
                iStack_208 = iStack_278 + -1;
              }
              func_0x0001410569f0(&ppuStack_270,&puStack_220,2);
              if (2 < DAT_14eab53c8) {
                ppuVar7 = (undefined **)&UNK_14bce4e94;
                if (iStack_268 != 0) {
                  ppuVar7 = ppuStack_270;
                }
                func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf628f8,ppuVar7);
              }
              plVar5 = (longlong *)func_0x000140db7220();
              ppuVar7 = (undefined **)&UNK_14bce4e94;
              if (iStack_268 != 0) {
                ppuVar7 = ppuStack_270;
              }
              puVar11 = &UNK_14bce4e94;
              if (iStack_2b8 != 0) {
                puVar11 = puStack_2c0;
              }
              uStack_2f8 = CONCAT71(uStack_2f8._1_7_,1);
              uStack_300 = 0;
              uStack_308 = 1;
              (**(code **)(*plVar5 + 0x48))(plVar5,puVar11,ppuVar7,1);
              plVar5 = (longlong *)func_0x000140db7220();
              ppuVar7 = (undefined **)&UNK_14bce4e94;
              if (iStack_268 != 0) {
                ppuVar7 = ppuStack_270;
              }
              (**(code **)(*plVar5 + 0x68))(plVar5,ppuVar7,0,1);
              if (ppuStack_270 != (undefined **)0x0) {
                func_0x000140e282f0();
              }
            }
            if (alStack_200[0] != 0) {
              func_0x000140e282f0();
            }
          }
          puStack_120 = puStack_2c0;
          if (iStack_2b8 == 0) {
            iStack_118 = 0;
          }
          else {
            iStack_118 = iStack_2b8 + -1;
          }
          pwStack_110 = L"manifest.json";
          uStack_108 = 0xd;
          func_0x0001410569f0(alStack_1f0,&puStack_120,2);
          cVar4 = func_0x0001410676a0(alStack_1f0);
          if (cVar4 == '\0') {
            if (1 < DAT_14eab53c8) {
              func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf62980);
            }
          }
          else {
            if (4 < DAT_14eab53c8) {
              puVar11 = &UNK_14bce4e94;
              if (iStack_2b8 != 0) {
                puVar11 = puStack_2c0;
              }
              func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf62a10,puVar11);
            }
            plVar5 = (longlong *)func_0x000140db7220();
            if (*(int *)(param_2 + 1) != 0) {
              puVar10 = (undefined *)*param_2;
            }
            uStack_308 = 0;
            (**(code **)(*plVar5 + 0x38))(plVar5,puVar10,0,0);
          }
          if (alStack_1f0[0] != 0) {
            func_0x000140e282f0();
          }
          if (alStack_1e0[0] != 0) {
            func_0x000140e282f0();
          }
        }
        else if (1 < DAT_14eab53c8) {
          func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf62898);
        }
      }
      if (puStack_260 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
LAB_14818d96c:
      if (puStack_2a8 != (undefined *)0x0) {
        func_0x000140e282f0();
      }
      ppuVar7 = ppuStack_298;
      for (iVar8 = (int)uStack_290; iVar8 != 0; iVar8 = iVar8 + -1) {
        if (*ppuVar7 != (undefined *)0x0) {
          func_0x000140e282f0();
        }
        ppuVar7 = ppuVar7 + 2;
      }
      if (ppuStack_298 != (undefined **)0x0) {
        func_0x000140e282f0(ppuStack_298);
      }
    }
  }
  else if (4 < DAT_14eab53c8) {
    puVar10 = &UNK_14bce4e94;
    if (iStack_278 != 0) {
      puVar10 = puStack_280;
    }
    func_0x000140f24ba0(&DAT_14eab53c8,&UNK_14cf624d8,puVar10);
  }
  if (alStack_1d0[0] != 0) {
    func_0x000140e282f0();
  }
  if (puStack_2c0 != (undefined *)0x0) {
    func_0x000140e282f0();
  }
  if (lStack_250 != 0) {
    func_0x000140e282f0();
  }
  if (puStack_280 != (undefined *)0x0) {
    func_0x000140e282f0();
  }
  func_0x00014b880380(uStack_50 ^ (ulonglong)auStack_328);
  return;
}




/* Resolved referenced strings:
{}
*/
