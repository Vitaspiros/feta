#include "tables.h"

// startingSyllables extracted from https://synagonism.net/otenet/gr/syltable.html#starting
// Thanks to Nikos Kasseluris at https://synagonism.net

const wchar_t* startingSyllables[] = {
    L"βγ", L"βδ", L"βλ", L"βρ", L"γδ", L"γκ", L"γλ",
    L"γν", L"γρ", L"δρ", L"θλ", L"θν", L"θρ", L"κβ",
    L"κζ", L"κλ", L"κν", L"κρ", L"κτ", L"μν", L"μπ",
    L"ντ", L"πλ", L"πν", L"πρ", L"πτ", L"σβ", L"σθ",
    L"σκ", L"σλ", L"σμ", L"σπ", L"σρ", L"στ", L"σφ",
    L"σχ", L"τζ", L"τμ", L"τρ", L"τσ", L"φθ", L"φλ",
    L"φρ", L"φτ", L"χθ", L"χλ", L"χν", L"χρ", L"χτ"
};

const wchar_t* vowels = L"αεηιουωϊϋ";
const wchar_t* vowelsAccent = L"άέήίόύώΐΰ";
const wchar_t* diphthongs[] = {
    L"ιά", L"ιό", L"ιού", L"ειό", L"ειά", L"ειού", L"οιό", L"οιά", L"οιού",
    L"ια", L"ιο", L"ιου", L"ειο", L"εια", L"ειου", L"οιο", L"οια", L"οιου",
    
    L"αι", L"οι", L"ει", L"υι", L"ου",
    L"αί", L"οί", L"εί", L"υί", L"ού",
};
const wchar_t* digraphs[] = {
    L"μπ", L"ντ", L"γκ", L"τζ", L"τσ", L"τς"
};