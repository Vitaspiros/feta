#pragma once

#include <wchar.h>

// Monosyllabic words that actually need an accute accent sometimes or always
const wchar_t* exceptions[]  = {
    L"ή", L"πού", L"πώς",

    L"μού", L"σού", L"τού", L"τής", L"τόν", L"τήν", 
    L"τό",L"μάς", L"σάς", L"τούς", L"τίς", L"τά"
};